/*
 * @file    joyconlib_types.h
 * @brief   Joy-Conライブラリ 型定義など
 * @author  K. Morita
 * @remarks
 * The following resources/projects were referenced for this library:
 *  https://github.com/dekuNukem/Nintendo_Switch_Reverse_Engineering
 *  https://github.com/CTCaer/jc_toolkit
 *
 * Copyright (c) 2022 K. Morita, All Rights Reserved.
 * this library is released under the MIT license.
 */
#pragma once
#include "joyconlib.h"

// コマンド
enum {
    JOYCON_CMD_RAW    = 0x0,
    JOYCON_CMD_SUB    = 0x01,
    JOYCON_CMD_RUMBLE = 0x10,
    JOYCON_CMD_MCU    = 0x11
};
// サブコマンド
enum {
    JOYCON_SUB_INFO      = 0x02,
    JOYCON_SUB_INPUT     = 0x03, // arg1
    JOYCON_SUB_ELAPSE    = 0x04,
    JOYCON_SUB_SPI_READ  = 0x10, // offset, size
    JOYCON_SUB_MCU_CONF  = 0x21,
    JOYCON_SUB_MCU_STATE = 0x22,
    JOYCON_SUB_LED_SET   = 0x30, // arg1
    JOYCON_SUB_LED_READ  = 0x31,
    JOYCON_SUB_HOME_SET  = 0x38, // < 25Byte
    JOYCON_SUB_IMU       = 0x40, // arg1 on/off
    JOYCON_SUB_RUMBLE    = 0x48  // arg1 on/off
};
// 入力レポートID / ACK
enum {
    JOYCON_REPORT_SUBCMD = 0x21,
    JOYCON_REPORT_FULL   = 0x30,
    JOYCON_REPORT_MCU    = 0x31,

    JOYCON_ACK_NORMAL = 0x80,
    JOYCON_ACK_ELAPSE = 0x83,
    JOYCON_ACK_SPI    = 0x90,
    JOYCON_ACK_MCU    = 0xA0,
    JOYCON_ACK_LED    = 0xB0
};
// ベンダー，プロダクトID
enum {
    JOYCON_VENDER   = 0x57E,
    JOYCON_ID_LEFT  = 0x2006,
    JOYCON_ID_RIGHT = 0x2007,
    JOYCON_ID_PRO   = 0x2009,
    JOYCON_ID_GRIP  = 0x200E
};

#pragma pack(push, 1)
typedef union {
    struct
    {
        u8 fw_major;
        u8 fw_minor;
        u8 type;
        u8 unknown;
        u8 mac[6];
        u8 unknown2;
        u8 color;
    } info;
    joycon_elapsed elapse;
    struct
    {
        u32 offset;
        u8 size;
        u8 data[33];
    } spi;
    u8 led;
    u8 byte[35];
} joycon_sub_report;

typedef struct
{
    u8 id;
    u8 timer;
    u8 batcon;
    joycon_btn btn;
    u8 lana[3];
    u8 rana[3];
    u8 vib;
    union {
        struct
        {
            u8 ack;
            u8 id;
            joycon_sub_report data;
        } subcmd;
        struct
        {
            s16 acc_x;
            s16 acc_y;
            s16 acc_z;

            s16 gyro_x;
            s16 gyro_y;
            s16 gyro_z;
        } axis[3];
    } sub;
} joycon_report;

// the folowing structures are referenced and modified from jc_toolkit
typedef struct
{
    u8 cmd;
    u8 timer;
    u8 rumble_l[4];
    u8 rumble_r[4];
} brcm_hdr;

typedef struct
{
    u8 subcmd;
    union {
        struct
        {
            u32 offset;
            u8 size;
        } spi_data;

        struct
        {
            u8 arg1;
            u8 arg2;
        } subcmd_arg;

        struct
        {
            u8 mcu_cmd;
            u8 mcu_subcmd;
            u8 mcu_mode;
        } subcmd_21_21;

        struct
        {
            u8 mcu_cmd;
            u8 mcu_subcmd;
            u8 no_of_reg;
            u16 reg1_addr;
            u8 reg1_val;
            u16 reg2_addr;
            u8 reg2_val;
            u16 reg3_addr;
            u8 reg3_val;
            u16 reg4_addr;
            u8 reg4_val;
            u16 reg5_addr;
            u8 reg5_val;
            u16 reg6_addr;
            u8 reg6_val;
            u16 reg7_addr;
            u8 reg7_val;
            u16 reg8_addr;
            u8 reg8_val;
            u16 reg9_addr;
            u8 reg9_val;
        } subcmd_21_23_04;

        struct
        {
            u8 mcu_cmd;
            u8 mcu_subcmd;
            u8 mcu_ir_mode;
            u8 no_of_frags;
            u16 mcu_major_v;
            u16 mcu_minor_v;
        } subcmd_21_23_01;
    };
} brcm_cmd_01;

typedef struct
{
    u8 ir_res_reg;
    u16 ir_exposure;
    u8 ir_leds;            // Leds to enable, Strobe/Flashlight modes
    u16 ir_leds_intensity; // MSByte: Leds 1/2, LSB: Leds 3/4
    u8 ir_digital_gain;
    u8 ir_ex_light_filter;
    u32 ir_custom_register; // MSByte: Enable/Disable, Middle Byte: Edge smoothing, LSB: Color interpolation
    u16 ir_buffer_update_time;
    u8 ir_hand_analysis_mode;
    u8 ir_hand_analysis_threshold;
    u32 ir_denoise; // MSByte: Enable/Disable, Middle Byte: Edge smoothing, LSB: Color interpolation
    u8 ir_flip;
} ir_image_config;
#pragma pack(pop)

typedef struct
{
    u8 hf0;
    u8 hf1;
    u8 lf2;
    float freq;
    int round;
} joycon_freq_t;
extern joycon_freq_t joycon_freq_table[160];

enum {
    JOYCON_FREQ_HIGH_DEFAUILT = 96,
    JOYCON_FREQ_LOW_DEFAUILT  = 64
};

typedef struct
{
    u8 ha1;
    u8 la2;
    u8 la3;
    float amp;
    float round;
} joycon_amp_t;
extern joycon_amp_t joycon_amp_table[101];

extern joycon_err joycon_write(joyconlib_t *jc, u8 cmd, u8 subcmd, u8 arg1, u32 offset, u8 *data);
extern joycon_err joycon_read(joyconlib_t *jc, u8 id, u8 subcmd, u8 ack, u8 *data, size_t *sz);

#if 0
// ToDo
    JOYCON_COMBINE = 0x3

extern joyconlib_t *joycon_combine(joyconlib_t *ja, joyconlib_t *jb);
extern joycon_err joycon_play_rumble_raw(joyconlib_t* jc, u8* buf, size_t sz, u16 hz, void (*callback)(void*),void* data);
#endif