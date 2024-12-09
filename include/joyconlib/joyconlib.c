/*!
 * @file    joyconlib.c
 * @brief   Joy-Conライブラリ
 * @author  K. Morita
 * @remarks
 * The following resources/projects were referenced for this library:
 *  https://github.com/dekuNukem/Nintendo_Switch_Reverse_Engineering
 *  https://github.com/CTCaer/jc_toolkit
 *
 * Copyright (c) 2022 K. Morita, All Rights Reserved.
 * this library is released under the MIT license.
 */
#include "joyconlib.h"
#include "joyconlib_types.h"
#include <math.h>
#include <stdbool.h>
#include <string.h>
#ifdef DEBUG
#include <stdio.h>
#endif

// the folowing functions are referenced and modified from jc_toolkit
static s16 uint16_to_int16(u16 a)
{
    s16 b;
    char *aPointer = (char*)&a, *bPointer = (char*)&b;
    memcpy(bPointer, aPointer, sizeof(a));
    return b;
}

static inline u16 CLAMP(u16 value, u16 low, u16 high)
{
    return value < low ? low : (value > high ? high : value);
}

// Credit to Hypersect (Ryan Juckett)
// http://blog.hypersect.com/interpreting-analog-sticks/
void AnalogStickCalc(
    float* pOutX,  // out: resulting stick X value
    float* pOutY,  // out: resulting stick Y value
    u16 x,         // in: initial stick X value
    u16 y,         // in: initial stick Y value
    u16 x_calc[3], // calc -X, CenterX, +X
    u16 y_calc[3]  // calc -Y, CenterY, +Y
)
{
    float x_f, y_f;
    // Apply Joy-Con center deadzone. 0xAE translates approx to 15%. Pro controller has a 10% deadzone.
    float deadZoneCenter = 0.15f;
    // Add a small ammount of outer deadzone to avoid edge cases or machine variety.
    float deadZoneOuter = 0.10f;

    // convert to float based on calibration and valid ranges per +/-axis
    x = CLAMP(x, x_calc[0], x_calc[2]);
    y = CLAMP(y, y_calc[0], y_calc[2]);
    if (x >= x_calc[1])
        x_f = (float)(x - x_calc[1]) / (float)(x_calc[2] - x_calc[1]);
    else
        x_f = -((float)(x - x_calc[1]) / (float)(x_calc[0] - x_calc[1]));
    if (y >= y_calc[1])
        y_f = -(float)(y - y_calc[1]) / (float)(y_calc[2] - y_calc[1]);
    else
        y_f = ((float)(y - y_calc[1]) / (float)(y_calc[0] - y_calc[1]));

    // Interpolate zone between deadzones
    float mag = sqrtf(x_f * x_f + y_f * y_f);
    if (mag > deadZoneCenter) {
        // scale such that output magnitude is in the range [0.0f, 1.0f]
        float legalRange    = 1.0f - deadZoneOuter - deadZoneCenter;
        float normalizedMag = fmin(1.0f, (mag - deadZoneCenter) / legalRange);
        float scale         = normalizedMag / mag;
        pOutX[0]            = x_f * scale;
        pOutY[0]            = y_f * scale;
    } else {
        // stick is in the inner dead zone
        pOutX[0] = 0.0f;
        pOutY[0] = 0.0f;
    }
}
// end of referenced functions from jc_toolkit

/* ジョイコンにデータ送信
 *
 *  rumbleも同時に送信する
 *  引数チェックしないので，上位の関数で要確認
 *
 * cmd : コマンド(0でRAWモード，dataをそのまま送る)
 * subcmd : サブコマンド
 * arg1 : サブコマンド引数，後続の引数を使うときはサイズ
 * offset : SPIデータ読み込み時のオフセット，arg1は読み込みサイズを指定
 * data : サブコマンド引数データ，arg1はデータサイズ
 */
joycon_err joycon_write(joyconlib_t* jc, u8 cmd, u8 subcmd, u8 arg1, u32 offset, u8* data)
{
    int res = 0;
    if (cmd) {
        size_t len = (cmd == JOYCON_CMD_RUMBLE) ? 10 : 11;
        u8 buf[49];
        buf[0] = cmd;
        buf[1] = jc->packnum = (jc->packnum + 1) & 0xF;
        buf[2] = buf[6] = jc->rumble[0];
        buf[3] = buf[7] = jc->rumble[1];
        buf[4] = buf[8] = jc->rumble[2];
        buf[5] = buf[9] = jc->rumble[3];
        buf[10]         = subcmd;
        if (subcmd) {
            if (data) {
                memcpy((buf + 11), data, arg1);
                len += arg1;
            } else if (offset) {
                *(u32*)(buf + 11) = offset;
                buf[15]           = arg1;
                len += 5;
            } else if (arg1) {
                buf[11] = arg1;
                len++;
            }
        }
        res = hid_write(jc->handle, buf, len);
    } else {
        res = hid_write(jc->handle, data, arg1);
    }
    if (res < 0)
        return JOYCON_ERR_WRITE_FAILED;

    return JOYCON_ERR_NONE;
}

/* ジョイコンデータ読取
 *
 *  指定した入力レポートのデータを取得するまで一定回数繰り返す
 *
 * id : 期待する入力レポートID(0で無視)
 * subcmd : 期待するサブコマンド(サブコマンドレポート時)，期待するdata[49](MCU)
 * ack : 期待するACK(サブコマンドレポート時)，期待するdata[56](MCU)
 * data : 読み込むデータ
 * sz : dataのサイズ(in), 実際に読み込まれたサイズ(out)
 */
joycon_err joycon_read(joyconlib_t* jc, u8 id, u8 subcmd, u8 ack, u8* data, size_t* sz)
{
    int retries = 0;
    int res     = 0;
    do {
        res = hid_read_timeout(jc->handle, data, *sz, 64);
#ifdef DEBUG
        printf("%02x %5u ", data[0], data[1]);
        printf("%02x   ", data[2]);
        printf("%02x %02x %02x ", data[3], data[4], data[5]);
        printf("%02x %02x %02x ", data[6], data[7], data[8]);
        printf("%02x %02x %02x  ", data[9], data[10], data[11]);
        printf("%02x  ", data[12]);
        printf("%02x  ", data[13]);
        printf("%02x    ", data[14]);
        printf("%02x %02x\n", data[15], data[22]);
#endif
        if (res > 0 && (!id || data[0] == id)) {
            bool flg = true;
            if (id == JOYCON_REPORT_SUBCMD && (data[13] != ack || data[14] != subcmd)) {
                flg = false;
            } else if (id == JOYCON_REPORT_MCU && subcmd) {
                if (data[49] != subcmd || data[56] != ack) {
                    flg = false;
                }
            }
            if (flg) {
                *sz = res;
#ifdef DEBUG
                // printf("\n");
#endif
                return JOYCON_ERR_NONE;
            }
        }
    } while (retries++ < 8 && res > 0);

    switch (res) {
    case -1:
        return JOYCON_ERR_READ_FAILED;
    case 0:
        return JOYCON_ERR_READ_NODATA;
    default:
        break;
    }
#ifdef DEBUG
    printf("timeout\n");
#endif

    return JOYCON_ERR_READ_TIMEOUT;
}

static joycon_err get_spi_data(joyconlib_t* jc, u32 offset, const u16 read_len, u8* test_buf)
{
    joycon_err ret    = JOYCON_ERR_NONE;
    int error_reading = 0;
    while (error_reading < 20) {
        size_t sz = 49;
        u8 buf[sz];
        ret = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_SPI_READ, read_len, offset, NULL);
        if (!ret) {
            ret = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_SPI_READ, JOYCON_ACK_SPI, buf, &sz);
            if (!ret && (sz >= 0x14 + read_len) && (*(u32*)&buf[0xF] == offset)) {
                memcpy(test_buf, buf + 0x14, read_len);
                // for (int i = 0; i < read_len; i++)
                // {
                //     test_buf[i] = buf[0x14 + i];
                // }
                return JOYCON_ERR_NONE;
            }
        }
        error_reading++;
    }
    return ret;
}

static joycon_err joycon_load_calibration(joyconlib_t* jc)
{
    // this codes are referenced and modified from jc_toolkit : button_test()

    u8 factory_stick_cal[0x12];
    u8 user_stick_cal[0x16];
    u8 factory_sensor_cal[0x18];
    u8 user_sensor_cal[0x1A];
    s16 sensor_cal[0x2][0x3];
    memset(factory_stick_cal, 0, 0x12);
    memset(user_stick_cal, 0, 0x16);
    memset(factory_sensor_cal, 0, 0x18);
    memset(user_sensor_cal, 0, 0x1A);
    memset(sensor_cal, 0, sizeof(sensor_cal));
    joycon_err ret = get_spi_data(jc, 0x6020, 0x18, factory_sensor_cal);
    if (ret)
        return ret;
    ret = get_spi_data(jc, 0x603D, 0x12, factory_stick_cal);
    if (ret)
        return ret;
    ret = get_spi_data(jc, 0x8010, 0x16, user_stick_cal);
    if (ret)
        return ret;
    ret = get_spi_data(jc, 0x8026, 0x1A, user_sensor_cal);
    if (ret)
        return ret;

    // Stick calibration
    if (jc->type == JOYCON_L) {
        jc->stick_cal_x[1] = ((factory_stick_cal[4] << 8) & 0xF00) | factory_stick_cal[3];
        jc->stick_cal_y[1] = (factory_stick_cal[5] << 4) | (factory_stick_cal[4] >> 4);
        jc->stick_cal_x[0] = jc->stick_cal_x[1] - (((factory_stick_cal[7] << 8) & 0xF00) | factory_stick_cal[6]);
        jc->stick_cal_y[0] = jc->stick_cal_y[1] - ((factory_stick_cal[8] << 4) | (factory_stick_cal[7] >> 4));
        jc->stick_cal_x[2] = jc->stick_cal_x[1] + (((factory_stick_cal[1] << 8) & 0xF00) | factory_stick_cal[0]);
        jc->stick_cal_y[2] = jc->stick_cal_y[1] + ((factory_stick_cal[2] << 4) | (factory_stick_cal[2] >> 4));
    }
    if (jc->type == JOYCON_R) {
        jc->stick_cal_x[1] = ((factory_stick_cal[10] << 8) & 0xF00) | factory_stick_cal[9];
        jc->stick_cal_y[1] = (factory_stick_cal[11] << 4) | (factory_stick_cal[10] >> 4);
        jc->stick_cal_x[0] = jc->stick_cal_x[1] - (((factory_stick_cal[13] << 8) & 0xF00) | factory_stick_cal[12]);
        jc->stick_cal_y[0] = jc->stick_cal_y[1] - ((factory_stick_cal[14] << 4) | (factory_stick_cal[13] >> 4));
        jc->stick_cal_x[2] = jc->stick_cal_x[1] + (((factory_stick_cal[16] << 8) & 0xF00) | factory_stick_cal[15]);
        jc->stick_cal_y[2] = jc->stick_cal_y[1] + ((factory_stick_cal[17] << 4) | (factory_stick_cal[16] >> 4));
    }
    // user L
    if ((user_stick_cal[0] | user_stick_cal[1] << 8) == 0xA1B2) {
        jc->stick_cal_x[1] = ((user_stick_cal[6] << 8) & 0xF00) | user_stick_cal[5];
        jc->stick_cal_y[1] = (user_stick_cal[7] << 4) | (user_stick_cal[6] >> 4);
        jc->stick_cal_x[0] = jc->stick_cal_x[1] - (((user_stick_cal[9] << 8) & 0xF00) | user_stick_cal[8]);
        jc->stick_cal_y[0] = jc->stick_cal_y[1] - ((user_stick_cal[10] << 4) | (user_stick_cal[9] >> 4));
        jc->stick_cal_x[2] = jc->stick_cal_x[1] + (((user_stick_cal[3] << 8) & 0xF00) | user_stick_cal[2]);
        jc->stick_cal_y[2] = jc->stick_cal_y[1] + ((user_stick_cal[4] << 4) | (user_stick_cal[3] >> 4));
    }
    // user R
    if ((user_stick_cal[0xB] | user_stick_cal[0xC] << 8) == 0xA1B2) {
        jc->stick_cal_x[1] = ((user_stick_cal[14] << 8) & 0xF00) | user_stick_cal[13];
        jc->stick_cal_y[1] = (user_stick_cal[15] << 4) | (user_stick_cal[14] >> 4);
        jc->stick_cal_x[0] = jc->stick_cal_x[1] - (((user_stick_cal[17] << 8) & 0xF00) | user_stick_cal[16]);
        jc->stick_cal_y[0] = jc->stick_cal_y[1] - ((user_stick_cal[18] << 4) | (user_stick_cal[17] >> 4));
        jc->stick_cal_x[2] = jc->stick_cal_x[1] + (((user_stick_cal[20] << 8) & 0xF00) | user_stick_cal[19]);
        jc->stick_cal_y[2] = jc->stick_cal_y[1] + ((user_stick_cal[21] << 4) | (user_stick_cal[20] >> 4));
    }

    // Sensor calibration
    // Acc cal origin position
    sensor_cal[0][0] = uint16_to_int16(factory_sensor_cal[0] | factory_sensor_cal[1] << 8);
    sensor_cal[0][1] = uint16_to_int16(factory_sensor_cal[2] | factory_sensor_cal[3] << 8);
    sensor_cal[0][2] = uint16_to_int16(factory_sensor_cal[4] | factory_sensor_cal[5] << 8);
    // Gyro cal origin position
    sensor_cal[1][0] = uint16_to_int16(factory_sensor_cal[0xC] | factory_sensor_cal[0xD] << 8);
    sensor_cal[1][1] = uint16_to_int16(factory_sensor_cal[0xE] | factory_sensor_cal[0xF] << 8);
    sensor_cal[1][2] = uint16_to_int16(factory_sensor_cal[0x10] | factory_sensor_cal[0x11] << 8);
    // user
    if ((user_sensor_cal[0x0] | user_sensor_cal[0x1] << 8) == 0xA1B2) {
        // Acc cal origin position
        sensor_cal[0][0] = uint16_to_int16(user_sensor_cal[2] | user_sensor_cal[3] << 8);
        sensor_cal[0][1] = uint16_to_int16(user_sensor_cal[4] | user_sensor_cal[5] << 8);
        sensor_cal[0][2] = uint16_to_int16(user_sensor_cal[6] | user_sensor_cal[7] << 8);
        // Gyro cal origin position
        sensor_cal[1][0] = uint16_to_int16(user_sensor_cal[0xE] | user_sensor_cal[0xF] << 8);
        sensor_cal[1][1] = uint16_to_int16(user_sensor_cal[0x10] | user_sensor_cal[0x11] << 8);
        sensor_cal[1][2] = uint16_to_int16(user_sensor_cal[0x12] | user_sensor_cal[0x13] << 8);
    }

    // Use SPI calibration and convert them to SI acc unit (m/s^2)
    // オリジナルはuint16_to_int16しているがもともとs16なので不要では？↓に一例
    // acc_cal_coeff[0] = (float)(1.0 / (float)(16384 - uint16_to_int16(sensor_cal[0][0]))) * 4.0f  * 9.8f;
    jc->acc_cal_coeff[0] = (float)(1.0 / (float)(16384 - (sensor_cal[0][0]))) * 4.0f * 9.8f;
    jc->acc_cal_coeff[1] = (float)(1.0 / (float)(16384 - (sensor_cal[0][1]))) * 4.0f * 9.8f;
    jc->acc_cal_coeff[2] = (float)(1.0 / (float)(16384 - (sensor_cal[0][2]))) * 4.0f * 9.8f;

    // Use SPI calibration and convert them to SI gyro unit (rad/s)
    // オリジナルはuint16_to_int16しているがもともとs16なので不要では？↓に一例
    // gyro_cal_coeff[0] = (float)(936.0 / (float)(13371 - uint16_to_int16(sensor_cal[1][0])) * 0.01745329251994);
    jc->gyro_cal_coeff[0] = (float)(936.0 / (float)(13371 - (sensor_cal[1][0])) * 0.01745329251994);
    jc->gyro_cal_coeff[1] = (float)(936.0 / (float)(13371 - (sensor_cal[1][1])) * 0.01745329251994);
    jc->gyro_cal_coeff[2] = (float)(936.0 / (float)(13371 - (sensor_cal[1][2])) * 0.01745329251994);

    // 計算用に保存
    jc->sensor_cal[0] = sensor_cal[1][0];
    jc->sensor_cal[1] = sensor_cal[1][1];
    jc->sensor_cal[2] = sensor_cal[1][2];

    return JOYCON_ERR_NONE;
}

/*!
 * @brief   ジョイコンを開く。
 *  あらかじめPCにジョイコンをBluetooth接続しておく必要がある。
 * @param[out] jc オープンしたジョイコンの情報を保持する
 *  joyconlib_t構造体変数へのポインタ
 * @param[in] type オープンするジョイコンのタイプを
 *  JOYCON_R（右）か
 *  JOYCON_L（左）で指定する。
 * @return  エラーコード
 */
joycon_err joycon_open(joyconlib_t* jc, joycon_type type)
{
    if (!jc)
        return JOYCON_ERR_INVALID_ARGUMENT;

    memset(jc, 0, sizeof(joyconlib_t));
    switch (type) {
    case JOYCON_R:
        jc->handle = hid_open(JOYCON_VENDER, JOYCON_ID_RIGHT, NULL);
        break;
    case JOYCON_L:
        jc->handle = hid_open(JOYCON_VENDER, JOYCON_ID_LEFT, NULL);
        break;
    default:
        jc->handle = NULL;
    }
    if (!(jc->handle))
        return JOYCON_ERR_OPEN_FAILED;

    // type
    jc->type = type;

    // 状態取得
    // LED
    joycon_err ret = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_LED_READ, 0, 0, NULL);
    if (ret)
        return ret;
    size_t sz = 49;
    u8 buf[sz];
    ret = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_LED_READ, JOYCON_ACK_LED, buf, &sz);
    if (ret)
        return ret;
    else
        jc->led_bk = buf[15];
    // キャリブレーションstick/sensor
    ret = joycon_load_calibration(jc);
    if (ret)
        return ret;

    // IMU on
    ret = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_IMU, 0x01, 0, NULL);
    if (!ret) {
        sz  = 49;
        ret = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_IMU, JOYCON_ACK_NORMAL, buf, &sz);
        if (ret)
            return ret;
    }
    // rumble on
    ret = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_RUMBLE, 0x01, 0, NULL);
    if (!ret) {
        sz  = 49;
        ret = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_RUMBLE, JOYCON_ACK_NORMAL, buf, &sz);
        if (ret)
            return ret;
    }
    // rumble data reset
    jc->rumble[0] = 0x00;
    jc->rumble[1] = 0x01;
    jc->rumble[2] = 0x40;
    jc->rumble[3] = 0x40;
    // input on
    ret = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_INPUT, JOYCON_REPORT_FULL, 0, NULL);
    if (!ret) {
        sz  = 49;
        ret = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_INPUT, JOYCON_ACK_NORMAL, buf, &sz);
        if (ret)
            return ret;
    }

    return JOYCON_ERR_NONE;
}

/*
 * @fn      joycon_close
 * @brief   ジョイコンを閉じる
 *  振動を止め，homeledを消灯し，ledを復元する
 * @param[in] jc ジョイコン情報
 * @return  エラーコード
 */
joycon_err joycon_close(joyconlib_t* jc)
{
    if (!jc)
        return JOYCON_ERR_INVALID_ARGUMENT;

    // disable ir
    if(jc->ir_enable)
        joycon_disable_ir(jc);
    // stop rumble
    joycon_rumble(jc, 0);
    // homeled off
    joycon_set_homeled(jc, JOYCON_HOMELED_OFF);
    // restore led
    joycon_set_led(jc, jc->led_bk);
    // close device
    hid_close(jc->handle);
    // clear memory
    memset(jc, 0, sizeof(joyconlib_t));

    return JOYCON_ERR_NONE;
}

/* 入力レポートを構造体に展開
 */
static joycon_err joycon_decode_state(joyconlib_t* jc, u8* buf_reply, size_t sz)
{
    switch (buf_reply[0]) {
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
        if (sz > 48) {
            for (int i = 0; i < 3; i++) {
                int d = 12 * i;
                // this codes are referenced and modified from jc_toolkit : button_test()

                // The controller sends the sensor data 3 times with a little bit different values. Skip them
                jc->axis[i].acc_x = (float)(uint16_to_int16(buf_reply[13 + d] | ((buf_reply[14 + d] << 8) & 0xFF00))) * jc->acc_cal_coeff[0];
                jc->axis[i].acc_y = (float)(uint16_to_int16(buf_reply[15 + d] | ((buf_reply[16 + d] << 8) & 0xFF00))) * jc->acc_cal_coeff[1];
                jc->axis[i].acc_z = (float)(uint16_to_int16(buf_reply[17 + d] | ((buf_reply[18 + d] << 8) & 0xFF00))) * jc->acc_cal_coeff[2];

                // オリジナルはuint16_to_int16しているがもともとs16なので不要では？↓に一例
                //   jc->axis[i].gyro_x = (float)(uint16_to_int16(buf_reply[19] | (buf_reply[20] << 8) & 0xFF00) - uint16_to_int16(jc->sensor_cal[0])) * jc->gyro_cal_coeff[0];
                jc->axis[i].gyro_x = (float)(uint16_to_int16(buf_reply[19 + d] | ((buf_reply[20 + d] << 8) & 0xFF00)) - (jc->sensor_cal[0])) * jc->gyro_cal_coeff[0];
                jc->axis[i].gyro_y = (float)(uint16_to_int16(buf_reply[21 + d] | ((buf_reply[22 + d] << 8) & 0xFF00)) - (jc->sensor_cal[1])) * jc->gyro_cal_coeff[1];
                jc->axis[i].gyro_z = (float)(uint16_to_int16(buf_reply[23 + d] | ((buf_reply[24 + d] << 8) & 0xFF00)) - (jc->sensor_cal[2])) * jc->gyro_cal_coeff[2];
            }
        }
    case 0x21:
        if (sz > 12) {
            jc->battery = (buf_reply[2] >> 5);

            jc->button.byte[0] = buf_reply[3];
            jc->button.byte[1] = buf_reply[4];
            jc->button.byte[2] = buf_reply[5];

            if (jc->type == JOYCON_L) {
                AnalogStickCalc(
                    &(jc->stick.x),
                    &(jc->stick.y),
                    buf_reply[6] | (u16)((buf_reply[7] & 0xF) << 8),
                    (buf_reply[7] >> 4) | (buf_reply[8] << 4),
                    jc->stick_cal_x,
                    jc->stick_cal_y);
            }
            if (jc->type == JOYCON_R) {
                AnalogStickCalc(
                    &(jc->stick.x),
                    &(jc->stick.y),
                    buf_reply[9] | (u16)((buf_reply[10] & 0xF) << 8),
                    (buf_reply[10] >> 4) | (buf_reply[11] << 4),
                    jc->stick_cal_x,
                    jc->stick_cal_y);
            }
        }
    default:
        break;
    }
    return JOYCON_ERR_NONE;
}

/*
 * @fn      joycon_get_state
 * @brief   ジョイコンの状態（ボタン，スティック，6軸センサー）を取得する
 * @param[in,out] jc ジョイコン情報
 * @return  エラーコード
 */
joycon_err joycon_get_state(joyconlib_t* jc)
{
    if (!jc)
        return JOYCON_ERR_INVALID_ARGUMENT;

    size_t sz = 49;
    u8 buf[sz];
    int ret = joycon_read(jc, 0, 0, 0, buf, &sz);
    if (ret)
        return ret;

    joycon_decode_state(jc, buf, sz);

    return JOYCON_ERR_NONE;
}

/*
 * @fn      joycon_get_button_elapsed
 * @brief   ジョイコンの特定ボタンの経過時間を取得する
 *  ボタンが押されてからの経過時間を10ms単位で取得する
 *  最大値は65535(*10ms)で，それ以上は計測されない
 *  取得できるボタンは L,R,ZL,ZR,SL,SR,Home で，
 *  押すと0になる
 * @param[in] jc ジョイコン情報
 * @param[out] etime 経過時間情報
 * @return  エラーコード
 */
joycon_err joycon_get_button_elapsed(joyconlib_t* jc, joycon_elapsed* etime)
{
    if (!jc)
        return JOYCON_ERR_INVALID_ARGUMENT;

    joycon_err ret = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_ELAPSE, 0, 0, NULL);
    if (!ret) {
        size_t sz = 49;
        u8 buf[sz];
        ret = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_ELAPSE, JOYCON_ACK_ELAPSE, buf, &sz);
        if (ret)
            return ret;
        if (sz >= 28)
            *etime = *(joycon_elapsed*)(buf + 15);
        else {
            memset(etime, 0, sizeof(joycon_elapsed));
            return JOYCON_ERR_READ_NODATA;
        }
    }
    return JOYCON_ERR_NONE;
}

/*
 * @fn      joycon_set_led
 * @brief   ジョイコンのLEDを設定する
 *  4つのLEDに対して，点灯か点滅を指定できる
 *  マクロが用意されており，|で結合して指定する
 *  点灯が優先される
 * @param[in] jc ジョイコン情報
 * @param[in] led LED情報
 * @return  エラーコード
 */
joycon_err joycon_set_led(joyconlib_t* jc, u8 led)
{
    if (!jc)
        return JOYCON_ERR_INVALID_ARGUMENT;

    joycon_err ret = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_LED_SET, led, 0, NULL);
    if (!ret) {
        size_t sz = 49;
        u8 buf[sz];
        ret = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_LED_SET, JOYCON_ACK_NORMAL, buf, &sz);
    }
    return ret;
}

/*
 * @fn      joycon_set_homeled
 * @brief   ジョイコンhomeボタンのLEDを設定する
 *  点灯/点滅に対する細かい指定ができる
 *  詳細はjoycon_homeledを参照のこと
 *  単純な点灯/点滅を指定するためのマクロが用意されている
 * @param[in] jc ジョイコン情報
 * @param[in] data LED情報
 * @return  エラーコード
 */
joycon_err joycon_set_homeled(joyconlib_t* jc, joycon_homeled* data)
{
    if (!jc || !data)
        return JOYCON_ERR_INVALID_ARGUMENT;
    if (jc->type != JOYCON_R)
        return JOYCON_ERR_INVALID_TYPE;

    joycon_err ret;
    size_t sz = 49;
    u8 buf[sz];
    switch ((s64)data) {
    case (s64)JOYCON_HOMELED_OFF:
        buf[0] = 0x11;
        ret    = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_HOME_SET, 1, 0, buf);
        break;
    case (s64)JOYCON_HOMELED_ON:
        buf[0] = 0x11;
        buf[1] = 0xf0;
        buf[2] = 0xf0;
        buf[3] = 0x0f;
        ret    = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_HOME_SET, 4, 0, buf);
        break;
    case (s64)JOYCON_HOMELED_BLINK:
        buf[0] = 0x21;
        buf[1] = 0xf0;
        buf[2] = 0xf0;
        buf[3] = 0x0f;
        buf[4] = 0x0f;
        ret    = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_HOME_SET, 5, 0, buf);
        break;
    default:
        ret = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_HOME_SET, sizeof(joycon_homeled), 0, (u8*)data);
    }
    if (!ret) {
        ret = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_HOME_SET, JOYCON_ACK_NORMAL, buf, &sz);
    }
    return ret;
}
