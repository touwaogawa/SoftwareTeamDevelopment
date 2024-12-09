/*
 * @file    joyconlib_mcu.c
 * @brief   Joy-Conライブラリ IR/NFC MCU関係
 * @author  K. Morita
 * @remarks
 * The following resources/projects were referenced for this library:
 *  https://github.com/dekuNukem/Nintendo_Switch_Reverse_Engineering
 *  https://github.com/CTCaer/jc_toolkit
 *
 * Copyright (c) 2022 K. Morita, All Rights Reserved.
 * this library is released under the MIT license.
 */
/*
 * jc_toolkit
 * Copyright (c) 2018 CTCaer. All rights reserved.
 * Licensed under the MIT license.
 * See https://github.com/CTCaer/jc_toolkit/blob/master/LICENSE
 */
#include "ir_sensor.h"
#include "joyconlib_types.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

// this function is referenced and modified from jc_toolkit
static u8 mcu_crc8_calc(u8* buf, u8 size)
{
    u8 crc8 = 0x0;

    for (int i = 0; i < size; ++i) {
        crc8 = mcu_crc8_table[(u8)(crc8 ^ buf[i])];
    }
    return crc8;
}

static joycon_err joycon_mcu_open(joyconlib_t* jc, u8 mode)
{
    // this code is referenced and modified from jc_toolkit : nfc_tag_info()
    u8 buf[0x170];
    static int output_buffer_length = 49;
    int error_reading               = 8;
    brcm_hdr* hdr                   = (brcm_hdr*)buf;
    brcm_cmd_01* pkt                = (brcm_cmd_01*)(hdr + 1);
    joycon_err ret                  = JOYCON_ERR_UNKNOWN;
    // Set input report to x31
    while (0 < error_reading--) {
        memset(buf, 0, sizeof(buf));
        ret = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_INPUT, 0x31, 0, NULL);
        if (!ret) {
            size_t sz = output_buffer_length;
            ret       = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_INPUT, JOYCON_ACK_NORMAL, buf, &sz);
            if (!ret)
                goto step1;
        }

        // auto hdr   = (brcm_hdr *)buf;
        // auto pkt   = (brcm_cmd_01 *)(hdr + 1);
        // hdr->cmd   = 1;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;
        // pkt->subcmd          = 0x03;
        // pkt->subcmd_arg.arg1 = 0x31;
        // res                  = hid_write(handle, buf, output_buffer_length);
        // int retries          = 0;
        // while (1) {
        //     res = hid_read_timeout(handle, buf, sizeof(buf), 64);
        //     if (*(u16 *)&buf[0xD] == 0x0380)
        //         goto step1;

        //     retries++;
        //     if (retries > 8 || res == 0)
        //         break;
        // }
        // error_reading++;
        // if (error_reading > 7) {
        //     return JOYCON_ERR_MCU_1ID31;
        // }
    }
    return JOYCON_ERR_MCU_1ID31;

step1:
    // Enable MCU
    error_reading = 8;
    while (0 < error_reading--) {
        memset(buf, 0, sizeof(buf));
        ret = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_MCU_STATE, 0x1, 0, NULL);
        if (!ret) {
            size_t sz = output_buffer_length;
            ret       = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_MCU_STATE, JOYCON_ACK_NORMAL, buf, &sz);
            if (!ret)
                goto step2;
        }
        // auto hdr   = (brcm_hdr *)buf;
        // auto pkt   = (brcm_cmd_01 *)(hdr + 1);
        // hdr->cmd   = 1;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;
        // pkt->subcmd          = 0x22;
        // pkt->subcmd_arg.arg1 = 0x1;
        // res                  = hid_write(handle, buf, output_buffer_length);
        // int retries          = 0;
        // while (1) {
        //     res = hid_read_timeout(handle, buf, sizeof(buf), 64);
        //     if (*(u16 *)&buf[0xD] == 0x2280)
        //         goto step2;

        //     retries++;
        //     if (retries > 8 || res == 0)
        //         break;
        // }
        // error_reading++;
        // if (error_reading > 7) {
        //     return JOYCON_ERR_MCU_2MCUON;
        // }
    }
    return JOYCON_ERR_MCU_2MCUON;

step2:
    // Request MCU mode status
    error_reading = 8;
    while (0 < error_reading--) {
        // Not necessary, but we keep to make sure the MCU is ready.
        memset(buf, 0, sizeof(buf));
        // brcm_hdr *hdr   = (brcm_hdr *)buf;
        // brcm_cmd_01 *pkt   = (brcm_cmd_01 *)(hdr + 1);
        // hdr->cmd   = 0x11;
        // hdr->timer = jc->packnum = (jc->packnum++) & 0xF;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;
        // pkt->subcmd = 0x01;
        // res         = hid_write(handle, buf, output_buffer_length);
        // int retries = 0;
        // while (1) {
        //     res = hid_read_timeout(handle, buf, sizeof(buf), 64);
        //     if (buf[0] == 0x31) {
        // ret = joycon_write(jc, JOYCON_CMD_RAW, 0, output_buffer_length, 0, buf);
#ifdef DEBUG
        printf("Request MCU mode status\n");
#endif
        ret = joycon_write(jc, JOYCON_CMD_MCU, 0x01, 0, 0, NULL);
        if (!ret) {
            // int retries = 0;
            // while (1) {
            size_t sz = sizeof(buf);
            ret       = joycon_read(jc, JOYCON_REPORT_MCU, 0x01, 0x01, buf, &sz);
            if (!ret) {
                // if (buf[49] == 0x01 && buf[56] == 0x06) // MCU state is Initializing
                //  *(u16*)buf[52]LE x04 in lower than 3.89fw, x05 in 3.89
                //  *(u16*)buf[54]LE x12 in lower than 3.89fw, x18 in 3.89
                //  buf[56]: mcu mode state
                // if (buf[49] == 0x01 && buf[56] == 0x01) // MCU state is Standby
                goto step3;
            }
            // retries++;
            // if (retries > 8 )
            // if (retries > 8 || res == 0)
            // break;
        }
        // error_reading++;
        // if (error_reading > 7) {
        //     return JOYCON_ERR_MCU_3MCUONBUSY;
        // }
    }
    return JOYCON_ERR_MCU_3MCUONBUSY;

step3:
    // Set MCU mode
    error_reading = 8;
    while (0 < error_reading--) {
        memset(buf, 0, sizeof(buf));
        // brcm_hdr *hdr   = (brcm_hdr *)buf;
        // brcm_cmd_01 *pkt   = (brcm_cmd_01 *)(hdr + 1);
        hdr->cmd   = 0x01;
        hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;
        pkt->subcmd = 0x21;

        pkt->subcmd_21_21.mcu_cmd    = 0x21; // Set MCU mode cmd
        pkt->subcmd_21_21.mcu_subcmd = 0x00; // Set MCU mode cmd
        pkt->subcmd_21_21.mcu_mode   = mode; // MCU mode - 1: Standby, 4: NFC, 5: IR, 6: Initializing/FW Update?

        buf[48] = mcu_crc8_calc(buf + 12, 36);
        // res         = hid_write(handle, buf, output_buffer_length);
        // int retries = 0;
        // while (1) {
        //     res = hid_read_timeout(handle, buf, sizeof(buf), 64);
        //     if (buf[0] == 0x21) {
#ifdef DEBUG
        printf("set MCU mode\n");
#endif
        ret = joycon_write(jc, JOYCON_CMD_RAW, 0, output_buffer_length, 0, buf);
        if (!ret) {
            // int retries = 0;
            // while (1) {
            size_t sz = sizeof(buf);
            ret       = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_MCU_CONF, JOYCON_ACK_MCU, buf, &sz);
            if (!ret) {
                // *(u16*)buf[18]LE x04 in lower than 3.89fw, x05 in 3.89
                // *(u16*)buf[20]LE x12 in lower than 3.89fw, x18 in 3.89
                // buf[56]: mcu mode state
                if (buf[15] == 0x01 && *(u32*)&buf[22] == 0x01) // Mcu mode is Standby
                    goto step4;
            }
            // retries++;
            // if (retries > 8 || res == 0)
            // if (retries > 8)
            // break;
        }
        // error_reading++;
        // if (error_reading > 7) {
        //     return JOYCON_ERR_MCU_4MCUMODESET;
        // }
    }
    return JOYCON_ERR_MCU_4MCUMODESET;

step4:
    // Request MCU mode status
    error_reading = 8;
    while (0 < error_reading--) {
        // Not necessary, but we keep to make sure the MCU mode changed.
        memset(buf, 0, sizeof(buf));
        // auto hdr   = (brcm_hdr *)buf;
        // auto pkt   = (brcm_cmd_01 *)(hdr + 1);
        // hdr->cmd   = 0x11;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;
        // pkt->subcmd = 0x01;
        // res         = hid_write(handle, buf, output_buffer_length);
        // int retries = 0;
        // while (1) {
        //     res = hid_read_timeout(handle, buf, sizeof(buf), 64);
        //     if (buf[0] == 0x31) {
#ifdef DEBUG
        printf("Request MCU mode status NFC\n");
#endif
        ret = joycon_write(jc, JOYCON_CMD_MCU, 0x01, 0, 0, NULL);
        if (!ret) {
            size_t sz = sizeof(buf);
            ret       = joycon_read(jc, JOYCON_REPORT_MCU, 0x01, mode, buf, &sz);
#ifdef DEBUG
            printf("%02x %02x\n", buf[49], buf[56]);
#endif
            if (!ret) {
                // *(u16*)buf[52]LE x04 in lower than 3.89fw, x05 in 3.89
                // *(u16*)buf[54]LE x12 in lower than 3.89fw, x18 in 3.89
                // if (buf[49] == 0x01 && buf[56] == mode) // Mcu mode is IR
                return JOYCON_ERR_NONE;
            }
            // retries++;
            // if (retries > 8 || res == 0)
            //     break;
        }
        // error_reading++;
        // if (error_reading > 7) {
        //     return JOYCON_ERR_MCU_5MCUSETBUSY;
        // }
    }
    return JOYCON_ERR_MCU_5MCUSETBUSY;
}

static joycon_err joycon_mcu_close(joyconlib_t* jc)
{
    joycon_err ret = JOYCON_ERR_UNKNOWN;
    // this code is referenced and modified from jc_toolkit
    // Disable MCU
    int error_reading = 0;
    u8 buf[49];
    while (ret) {
        memset(buf, 0, sizeof(buf));
        // auto hdr   = (brcm_hdr *)buf;
        // auto pkt   = (brcm_cmd_01 *)(hdr + 1);
        // hdr->cmd   = 1;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;
        // pkt->subcmd          = 0x22;
        // pkt->subcmd_arg.arg1 = 0x00;
        // res                  = hid_write(handle, buf, output_buffer_length);
        // res                  = hid_read_timeout(handle, buf, sizeof(buf), 64);
        ret = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_MCU_STATE, 0x0, 0, NULL);
        if (!ret) {
            size_t sz = 49;
            ret       = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_MCU_STATE, JOYCON_ACK_NORMAL, buf, &sz);
            // if (!ret)
            //     goto stepb;
        }
        // error_reading++;
        if (ret && ++error_reading > 7) {
            goto stepb;
        }
    }

stepb:
    // Set input report back to x30
    error_reading = 0;
    ret           = JOYCON_ERR_UNKNOWN;
    while (ret) {
        memset(buf, 0, sizeof(buf));
        ret = joycon_write(jc, JOYCON_CMD_SUB, JOYCON_SUB_INPUT, JOYCON_REPORT_FULL, 0, NULL);
        if (!ret) {
            size_t sz = 49;
            ret       = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_INPUT, JOYCON_ACK_NORMAL, buf, &sz);
            // if (!ret)
            //     goto stepf;
        }
        // auto hdr   = (brcm_hdr *)buf;
        // auto pkt   = (brcm_cmd_01 *)(hdr + 1);
        // hdr->cmd   = 1;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;
        // pkt->subcmd          = 0x03;
        // pkt->subcmd_arg.arg1 = 0x3f;
        // res                  = hid_write(handle, buf, output_buffer_length);
        // int retries          = 0;
        // while (1) {
        //     res = hid_read_timeout(handle, buf, sizeof(buf), 64);
        //     if (*(u16 *)&buf[0xD] == 0x0380)
        //         goto stepf;

        //     retries++;
        //     if (retries > 8 || res == 0)
        //         break;
        // }
        // error_reading++;
        if (ret && ++error_reading > 7) {
            goto stepf;
        }
    }
stepf:
    return JOYCON_ERR_NONE;
}

/*
 * @fn      joycon_read_nfc
 * @brief   ジョイコンでNFCタグ情報を読み取る
 *  ジョイコン(右)のスティックがリーダーになっている
 *  タグの読み取りに対応しているのは，NTAG213,NTAG215,NTAG216
 *  その他はUIDの読み取りのみ
 * @param[in] jc ジョイコン情報
 * @param[out] nfc NFC情報
 * @return  エラーコード
 */
joycon_err joycon_read_nfc(joyconlib_t* jc, joycon_nfc_data* nfc)
{
    if (!jc || !nfc)
        return JOYCON_ERR_INVALID_ARGUMENT;
    if (jc->type != JOYCON_R)
        return JOYCON_ERR_INVALID_TYPE;

    // this code is referenced and modified from jc_toolkit : nfc_tag_info()

    /////////////////////////////////////////////////////
    // Kudos to Eric Betts (https://github.com/bettse) //
    // for nfc comm starters                           //
    /////////////////////////////////////////////////////
    u8 buf[0x170];
    u8 buf2[0x170];
    static int output_buffer_length = 49;
    int error_reading               = 0;
    int res_get                     = 0;
    // u8 tag_uid_buf[10];
    // u8 tag_uid_size = 0;
    // u8 ntag_buffer[924];
    // u16 ntag_buffer_pos = 0;
    u8 ntag_pages = 0; // Max 231
    // u8 tag_type         = 0;
    u16 payload_size    = 0;
    bool ntag_init_done = false;
    brcm_hdr* hdr       = (brcm_hdr*)buf;
    brcm_cmd_01* pkt    = (brcm_cmd_01*)(hdr + 1);
    int res;
    joycon_err ret = joycon_mcu_open(jc, 0x04);
    if (ret) {
        joycon_mcu_close(jc);
        return ret;
    }

    memset(nfc, 0, sizeof(joycon_nfc_data));
    // memset(tag_uid_buf, 0, sizeof(tag_uid_buf));
    // memset(ntag_buffer, 0, sizeof(ntag_buffer));

step5:
    // Request NFC mode status
    error_reading = 0;
    while (1) {
        memset(buf, 0, sizeof(buf));
        // auto hdr   = (brcm_hdr *)buf;
        // auto pkt   = (brcm_cmd_01 *)(hdr + 1);
        hdr->cmd   = 0x11;
        hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;

        pkt->subcmd          = 0x02;
        pkt->subcmd_arg.arg1 = 0x04; // 0: Cancel all, 4: StartWaitingReceive
        pkt->subcmd_arg.arg2 = 0x00; // Count of the currecnt packet if the cmd is a series of packets.
        buf[13]              = 0x00;
        buf[14]              = 0x08; // 8: Last cmd packet, 0: More cmd packet should be  expected
        buf[15]              = 0x00; // Length of data after cmd header

        buf[47] = mcu_crc8_calc(buf + 11, 36); // Without the last byte

        res         = hid_write(jc->handle, buf, output_buffer_length - 1);
        int retries = 0;
        while (1) {
            res = hid_read_timeout(jc->handle, buf, sizeof(buf), 64);
            if (buf[0] == 0x31) {

                if (buf[49] == 0x2a && *(u16*)&buf[50] == 0x0500 && buf[55] == 0x31 && buf[56] == 0x0b) // buf[56] == 0x0b: Initializing/Busy
                    break;
                if (buf[49] == 0x2a && *(u16*)&buf[50] == 0x0500 && buf[55] == 0x31 && buf[56] == 0x00) // buf[56] == 0x00: Awaiting cmd
                    goto step6;
            }
            retries++;
            if (retries > 4 || res == 0)
                break;
        }
        error_reading++;
        if (error_reading > 9) {
            res_get = 6;
            goto step9;
        }
    }

step6:
    // Request NFC mode status
    error_reading = 0;
    while (1) {
        memset(buf, 0, sizeof(buf));
        // auto hdr   = (brcm_hdr *)buf;
        // auto pkt   = (brcm_cmd_01 *)(hdr + 1);
        hdr->cmd   = 0x11;
        hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;

        pkt->subcmd          = 0x02;
        pkt->subcmd_arg.arg1 = 0x01; // 1: Start polling, 2: Stop polling,
        pkt->subcmd_arg.arg2 = 0x00; // Count of the currecnt packet if the cmd is a series of packets.
        buf[13]              = 0x00;
        buf[14]              = 0x08; // 8: Last cmd packet, 0: More cmd packet should be expected
        buf[15]              = 0x05; // Length of data after cmd header
        buf[16]              = 0x01; // 1: Enable Mifare support
        buf[17]              = 0x00; // Unknown.
        buf[18]              = 0x00; // Unknown.
        buf[19]              = 0x2c; // Unknown. Some values work (0x07) other don't.
        buf[20]              = 0x01; // Unknown. This is not needed but Switch sends it.

        buf[47] = mcu_crc8_calc(buf + 11, 36); // Without the last byte

        res         = hid_write(jc->handle, buf, output_buffer_length - 1);
        int retries = 0;
        while (1) {
            // if (!enable_NFCScanning)
            //     goto step7;
            res = hid_read_timeout(jc->handle, buf, sizeof(buf), 64);
            if (buf[0] == 0x31) {
                // buf[49] == 0x2a: NFC MCU input report
                // buf[50] shows when there's error?
                // buf[51] == 0x05: NFC
                // buf[54] always 9?
                // buf[55] always x31?
                // buf[56]: MCU/NFC state
                // buf[62]: nfc tag IC
                // buf[63]: nfc tag Type
                // buf[64]: size of following data and it's the last NFC header byte
                if (buf[49] == 0x2a && *(u16*)&buf[50] == 0x0500 && buf[56] == 0x09) { // buf[56] == 0x09: Tag detected
                    nfc->tag_type     = buf[62];                                       // Save tag type
                    nfc->tag_uid_size = buf[64];
                    for (int i = 0; i < nfc->tag_uid_size; i++) {
                        nfc->tag_uid[i] = buf[65 + i]; // Save UID
                    }
                    goto step7;
                } else if (buf[49] == 0x2a)
                    break;
            }
            retries++;
            if (retries > 4 || res == 0) {
                // Application::DoEvents();
                break;
            }
        }
        error_reading++;
        if (error_reading > 100) {
            res_get = 7;
            // if (ntag_init_done)
            //     FormJoy::myform1->txtBox_NFCTag->Text = String::Format("Tag lost!");
            // else
            //     FormJoy::myform1->txtBox_NFCTag->Text = String::Format("No Tag detected!");
            goto step9;
        }
    }

step7:
    // Read NTAG contents
    error_reading = 0;
    while (1) {
        memset(buf2, 0, sizeof(buf2));
        // auto hdr   = (brcm_hdr *)buf2;
        // auto pkt   = (brcm_cmd_01 *)(hdr + 1);
        // hdr->cmd   = 0x11;
        buf2[0] = 0x11;
        buf2[1] = jc->packnum = (jc->packnum + 1) & 0xF;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;

        // pkt->subcmd          = 0x02;
        // pkt->subcmd_arg.arg1 = 0x06; // 6: Read Ntag data, 0xf: Read mifare data
        buf2[10] = 0x02;
        buf2[11] = 0x06; // 6: Read Ntag data, 0xf: Read mifare data
        buf2[12] = 0x00;
        buf2[13] = 0x00;
        buf2[14] = 0x08;
        buf2[15] = 0x13; // Length of data after cmd header

        buf2[16] = 0xd0; // Unknown
        buf2[17] = 0x07; // Unknown or UID lentgh?
        buf2[18] = 0x00; // Only for Mifare cmds or should have a UID?

        buf2[19] = 0x00; // should have a UID?
        buf2[20] = 0x00; // should have a UID?
        buf2[21] = 0x00; // should have a UID?
        buf2[22] = 0x00; // should have a UID?
        buf2[23] = 0x00; // should have a UID?
        buf2[24] = 0x00; // should have a UID?

        buf2[25] = 0x00; // 1: Ntag215 only. 0: All tags, otherwise error x48 (Invalid format error)

        // https://www.tagnfc.com/en/info/11-nfc-tags-specs

        // If the following is selected wrongly, error x3e (Read error)
        switch (ntag_pages) {
        case 0:
            buf2[26] = 0x01;
            break;
            // Ntag213
        case 45:
            // The following 7 bytes should be decided with max the current ntag pages and what we want to read.
            buf2[26] = 0x01; // How many blocks to read. Each block should be <= 60 pages (240 bytes)? Min/Max values are 1/4, otherwise error x40 (Argument error)

            buf2[27] = 0x00; // Block 1 starting page
            buf2[28] = 0x2C; // Block 1 ending page
            buf2[29] = 0x00; // Block 2 starting page
            buf2[30] = 0x00; // Block 2 ending page
            buf2[31] = 0x00; // Block 3 starting page
            buf2[32] = 0x00; // Block 3 ending page
            buf2[33] = 0x00; // Block 4 starting page
            buf2[34] = 0x00; // Block 4 ending page
            break;
            // Ntag215
        case 135:
            // The following 7 bytes should be decided with max the current ntag pages and what we want to read.
            buf2[26] = 0x03; // How many page ranges to read. Each range should be <= 60 pages (240 bytes)? Max value is 4.

            buf2[27] = 0x00; // Block 1 starting page
            buf2[28] = 0x3b; // Block 1 ending page
            buf2[29] = 0x3c; // Block 2 starting page
            buf2[30] = 0x77; // Block 2 ending page
            buf2[31] = 0x78; // Block 3 starting page
            buf2[32] = 0x86; // Block 3 ending page
            buf2[33] = 0x00; // Block 4 starting page
            buf2[34] = 0x00; // Block 4 ending page
            break;
        case 231:
            // The following 7 bytes should be decided with max the current ntag pages and what we want to read.
            buf2[26] = 0x04; // How many page ranges to read. Each range should be <= 60 pages (240 bytes)? Max value is 4.

            buf2[27] = 0x00; // Block 1 starting page
            buf2[28] = 0x3b; // Block 1 ending page
            buf2[29] = 0x3c; // Block 2 starting page
            buf2[30] = 0x77; // Block 2 ending page
            buf2[31] = 0x78; // Block 3 starting page
            buf2[32] = 0xB3; // Block 3 ending page
            buf2[33] = 0xB4; // Block 4 starting page
            buf2[34] = 0xE6; // Block 4 ending page
            break;
        default:
            break;
        }

        buf2[47] = mcu_crc8_calc(buf2 + 11, 36);

        res = hid_write(jc->handle, buf2, output_buffer_length - 1);

        int retries = 0;
        while (1) {
            res = hid_read_timeout(jc->handle, buf2, sizeof(buf2), 64);
            if (buf2[0] == 0x31) {

                if ((buf2[49] == 0x3a || buf2[49] == 0x2a) && buf2[56] == 0x07) {
                    res_get = 9;
                    // FormJoy::myform1->txtBox_NFCTag->Text = String::Format("Error {0:X2}!", buf2[50]);
                    goto step9; ///////////
                } else if (buf2[49] == 0x3a && buf2[51] == 0x07) {
                    if (ntag_init_done) {
                        payload_size = (buf2[54] << 8 | buf2[55]) & 0x7FF;
                        if (buf2[52] == 0x01) {
                            memcpy(nfc->ntag_data + nfc->ntag_data_size, buf2 + 116, payload_size - 60);
                            nfc->ntag_data_size += payload_size - 60;
                        } else {
                            memcpy(nfc->ntag_data + nfc->ntag_data_size, buf2 + 56, payload_size);
                            nfc->ntag_data_size += payload_size;
                        }
                    } else if (buf2[52] == 0x01) {
                        if (nfc->tag_type == 2) {
                            switch (buf2[74]) {
                            case 0:
                                ntag_pages = 135;
                                break;
                            case 3:
                                ntag_pages = 45;
                                break;
                            case 4:
                                ntag_pages = 231;
                                break;
                            default:
                                goto step9; ///////////
                                break;
                            }
                        }
                    }
                    break;
                } else if (buf2[49] == 0x2a && buf2[56] == 0x04) { // finished
                    if (ntag_init_done) {
                        // finished
                        goto step9; ///////////
                    }
                    ntag_init_done = true;

                    memset(buf, 0, sizeof(buf));
                    // auto hdr   = (brcm_hdr *)buf;
                    // auto pkt   = (brcm_cmd_01 *)(hdr + 1);
                    hdr->cmd   = 0x11;
                    hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
                    // hdr->timer = timming_byte & 0xF;
                    // timming_byte++;

                    pkt->subcmd          = 0x02;
                    pkt->subcmd_arg.arg1 = 0x02; // 0: Cancel all, 4: StartWaitingReceive
                    pkt->subcmd_arg.arg2 = 0x00; // Count of the currecnt packet if the cmd is a series of packets.
                    buf[13]              = 0x00;
                    buf[14]              = 0x08; // 8: Last cmd packet, 0: More cmd packet should be  expected
                    buf[15]              = 0x00; // Length of data after cmd header

                    buf[47] = mcu_crc8_calc(buf + 11, 36); // Without the last byte
                    res     = hid_write(jc->handle, buf, output_buffer_length - 1);

                    usleep(200 * 1000);
                    goto step5;
                } else if (buf2[49] == 0x2a)
                    break;
            }
            retries++;
            if (retries > 4 || res == 0)
                break;
        }
        error_reading++;
        if (error_reading > 9) {
            res_get = 8;
            // if (buf[62] == 0x4)
            //     FormJoy::myform1->txtBox_NFCTag->Text = String::Format("Mifare reading is not supported for now..");
            goto step9;
        }
    }

step9:
    joycon_mcu_close(jc);

    // Get error
    switch (res_get) {
    case 6:
        ret = JOYCON_ERR_MCU_6NFCPOLL;
        break;
    case 7:
        ret = JOYCON_ERR_MCU_NOTAG;
        break;
    case 8:
        ret = JOYCON_ERR_MCU_NOTSUPPORTED;
        break;
    case 9:
        ret = JOYCON_ERR_MCU_READ;
        break;
    default:
        ret = JOYCON_ERR_NONE;
        break;
    }
    return ret;
}

/*
 * @fn      joycon_disable_ir
 * @brief   ジョイコンのIRカメラの終了
 *  IRカメラの使用を終了し，通常に戻す
 * @param[in] jc ジョイコン情報
 * @return  エラーコード
 */
joycon_err joycon_disable_ir(joyconlib_t* jc)
{
    if (!jc)
        return JOYCON_ERR_INVALID_ARGUMENT;
    jc->ir_enable      = 0;
    jc->ir_max_frag_no = 0;
    jc->ir_resolution  = 0;
    jc->ir_exposure    = 0;
    return joycon_mcu_close(jc);
}

// this function is referenced and modified from jc_toolkit
// static int ir_sensor_auto_exposure(int white_pixels_percent)
static joycon_err ir_sensor_auto_exposure(joyconlib_t* jc, u16 exposure)
{
    // int res;
    u8 buf[49] = { 0 };
    // u16 new_exposure = 0;
    // int old_exposure = jc->ir_exposure;

    // Calculate new exposure;
    // if (white_pixels_percent == 0)
    //     old_exposure += 10;
    // else if (white_pixels_percent > 5)
    //     old_exposure -= (white_pixels_percent / 4) * 20;

    // old_exposure                                = CLAMP(old_exposure, 0, 600);
    // FormJoy::myform1->numeric_IRExposure->Value = old_exposure;
    // new_exposure                                = old_exposure * 31200 / 1000;
    u16 new_exposure = exposure * 31200 / 1000;

    // memset(buf, 0, sizeof(buf));
    brcm_hdr* hdr    = (brcm_hdr*)buf;
    brcm_cmd_01* pkt = (brcm_cmd_01*)(hdr + 1);
    hdr->cmd         = 0x01;
    hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
    // hdr->timer = timming_byte & 0xF;
    // timming_byte++;
    pkt->subcmd = 0x21;

    pkt->subcmd_21_23_04.mcu_cmd    = 0x23; // Write register cmd
    pkt->subcmd_21_23_04.mcu_subcmd = 0x04; // Write register to IR mode subcmd
    pkt->subcmd_21_23_04.no_of_reg  = 0x03; // Number of registers to write. Max 9.

    pkt->subcmd_21_23_04.reg1_addr = 0x3001; // R: 0x0130 - Set Exposure time LSByte
    pkt->subcmd_21_23_04.reg1_val  = new_exposure & 0xFF;
    pkt->subcmd_21_23_04.reg2_addr = 0x3101; // R: 0x0131 - Set Exposure time MSByte
    pkt->subcmd_21_23_04.reg2_val  = (new_exposure & 0xFF00) >> 8;
    pkt->subcmd_21_23_04.reg3_addr = 0x0700; // R: 0x0007 - Finalize config - Without this, the register changes do not have any effect.
    pkt->subcmd_21_23_04.reg3_val  = 0x01;

    buf[48] = mcu_crc8_calc(buf + 12, 36);
    // res     = hid_write(handle, buf, sizeof(buf));

    joycon_err ret = joycon_write(jc, JOYCON_CMD_RAW, 0, sizeof(buf), 0, buf);
    if (!ret)
        jc->ir_exposure = exposure;

    return ret;
}

joycon_err joycon_read_ir(joyconlib_t* jc, u8* image, size_t size, u16 exposure, joycon_ir_result* result)
{
    if (!jc || !image)
        return JOYCON_ERR_INVALID_ARGUMENT;
    if (!jc->ir_enable)
        return JOYCON_ERR_MCU_IRNOREADY;
    if (size < jc->ir_max_frag_no * 300)
        return JOYCON_ERR_INVALID_ARGUMENT;
    if (exposure > 600)
        return JOYCON_ERR_INVALID_ARGUMENT;

    if (exposure && exposure != jc->ir_exposure)
        ir_sensor_auto_exposure(jc, exposure);

    if (result) {
        memset(result, 0, sizeof(joycon_ir_result));
    }

    // following code is referenced and modified from jc_toolkit
    //////
    // TODO: Should we send subcmd x21 with 'x230102' to disable IR mode before disabling MCU?

    u8 buf[49];
    u8 buf_reply[0x170];
    // u8 *buf_image             = new u8[19 * 4096]; // 8bpp greyscale image.
    // uint16_t bad_signal       = 0;
    // int error_reading         = 0;
    // float noise_level         = 0.0f;
    // int avg_intensity_percent = 0.0f;
    int previous_frag_no = 0;
    int got_frag_no      = 0;
    int missed_packet_no = 0;
    bool missed_packet   = false;
    int initialization   = 1;
    // int initialization        = 2;
    // int max_pixels           = ((jc->ir_max_frag_no < 218 ? jc->ir_max_frag_no : 217) + 1) * 300;
    // int white_pixels_percent = 0;

    memset(image, 0, size);

    memset(buf, 0, sizeof(buf));
    memset(buf_reply, 0, sizeof(buf_reply));
    brcm_hdr* hdr    = (brcm_hdr*)buf;
    brcm_cmd_01* pkt = (brcm_cmd_01*)(hdr + 1);
    hdr->cmd         = 0x11;
    pkt->subcmd      = 0x03;
    buf[48]          = 0xFF;

    // First ack
    hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
    buf[14]                  = 0x0;
    buf[47]                  = mcu_crc8_calc(buf + 11, 36);
    joycon_err ret           = joycon_write(jc, JOYCON_CMD_RAW, 0, sizeof(buf), 0, buf);

    // IR Read/ACK loop for fragmented data packets.
    // It also avoids requesting missed data fragments, we just skip it to not complicate things.
    while (initialization) {
        memset(buf_reply, 0, sizeof(buf_reply));
        // hid_read_timeout(handle, buf_reply, sizeof(buf_reply), 200);
        size_t sz = sizeof(buf_reply);
        ret       = joycon_read(jc, JOYCON_REPORT_MCU, 0, 0, buf_reply, &sz);

        // Check if new packet
        // if (buf_reply[0] == 0x31
        if (!ret && buf_reply[49] == 0x03) {
            got_frag_no = buf_reply[52];
            if (got_frag_no == (previous_frag_no + 1) % (jc->ir_max_frag_no + 1)) {

                previous_frag_no = got_frag_no;

                // ACK for fragment
                hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
                buf[14]                  = previous_frag_no;
                buf[47]                  = mcu_crc8_calc(buf + 11, 36);
                // hid_write(handle, buf, sizeof(buf));
                ret = joycon_write(jc, JOYCON_CMD_RAW, 0, sizeof(buf), 0, buf);

                memcpy(image + (300 * got_frag_no), buf_reply + 59, 300);

                // Auto exposure.
                // TODO: Fix placement, so it doesn't drop next fragment.
#if 0                
                if (enable_IRAutoExposure && initialization < 2 && got_frag_no == 0) {
                    white_pixels_percent = (int)((*(u16 *)&buf_reply[55] * 100) / max_pixels);
                    ir_sensor_auto_exposure(white_pixels_percent);
                }

                // Status percentage
                ir_status << std::fixed << std::setprecision(0) << (float)got_frag_no / (float)(ir_max_frag_no + 1) * 100.0f;
                ir_status << "% - ";

                // debug
                // printf("%02X Frag: Copy\n", got_frag_no);

#endif
                // Check if final fragment. Draw the frame.
                if (got_frag_no == jc->ir_max_frag_no) {
                    // Update Viewport
                    // elapsed_time2 = sw->ElapsedMilliseconds - elapsed_time2;
                    // FormJoy::myform1->setIRPictureWindow(buf_image, true);

                    // debug
                    // printf("%02X Frag: Draw -------\n", got_frag_no);

                    // Stats/IR header parsing
                    // buf_reply[53]: Average Intensity. 0-255 scale.
                    // buf_reply[54]: Unknown. Shows up only when EXFilter is enabled.
                    // *(u16*)&buf_reply[55]: White pixels (pixels with 255 value). Max 65535. Uint16 constraints, even though max is 76800.
                    // *(u16*)&buf_reply[57]: Pixels with ambient noise from external light sources (sun, lighter, IR remotes, etc). Cleaned by External Light Filter.
                    if (result) {
                        result->avg_intensity = buf_reply[53];
                        result->unknown       = buf_reply[54];
                        result->white_pixels  = *(u16*)&buf_reply[55];
                        result->noise_pixels  = *(u16*)&buf_reply[57];
                    }
                    /* noise_level                        = (float)(*(u16 *)&buf_reply[57]) / ((float)(*(u16 *)&buf_reply[55]) + 1.0f);
                    white_pixels_percent               = (int)((*(u16 *)&buf_reply[55] * 100) / max_pixels);
                    avg_intensity_percent              = (int)((buf_reply[53] * 100) / 255);
                    FormJoy::myform1->lbl_IRHelp->Text = String::Format("Amb Noise: {0:f2},  Int: {1:D}%,  FPS: {2:D} ({3:D}ms)\nEXFilter: {4:D},  White Px: {5:D}%,  EXF Int: {6:D}",
                        noise_level, avg_intensity_percent, (int)(1000 / elapsed_time2), elapsed_time2, *(u16 *)&buf_reply[57], white_pixels_percent, buf_reply[54]);

                    elapsed_time2 = sw->ElapsedMilliseconds; */

                    if (initialization)
                        initialization--;
                }
            }
            // Repeat/Missed fragment
            else if (got_frag_no || previous_frag_no) {
                // Check if repeat ACK should be send. Avoid writing to image buffer.
                if (got_frag_no == previous_frag_no) {
                    // debug
                    // printf("%02X Frag: Repeat\n", got_frag_no);

                    // ACK for fragment
                    hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
                    buf[14]                  = got_frag_no;
                    buf[47]                  = mcu_crc8_calc(buf + 11, 36);
                    ret                      = joycon_write(jc, JOYCON_CMD_RAW, 0, sizeof(buf), 0, buf);

                    missed_packet = false;
                }
                // Check if missed fragment and request it.
                else if (missed_packet_no != got_frag_no && !missed_packet) {
                    if (jc->ir_max_frag_no != 0x03) {
                        // debug
                        // printf("%02X Frag: Missed %02X, Prev: %02X, PrevM: %02X\n", got_frag_no, previous_frag_no + 1, previous_frag_no, missed_packet_no);

                        // Missed packet
                        hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
                        // Request for missed packet. You send what the next fragment number will be, instead of the actual missed packet.
                        buf[12] = 0x1;
                        buf[13] = previous_frag_no + 1;
                        buf[14] = 0;
                        buf[47] = mcu_crc8_calc(buf + 11, 36);
                        ret     = joycon_write(jc, JOYCON_CMD_RAW, 0, sizeof(buf), 0, buf);

                        buf[12] = 0x00;
                        buf[13] = 0x00;

                        memcpy(image + (300 * got_frag_no), buf_reply + 59, 300);

                        previous_frag_no = got_frag_no;
                        missed_packet_no = got_frag_no - 1;
                        missed_packet    = true;
                    }
                    // Check if missed fragment and res is 30x40. Don't request it.
                    else {
                        // debug
                        // printf("%02X Frag: Missed but res is 30x40\n", got_frag_no);

                        // ACK for fragment
                        hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
                        buf[14]                  = got_frag_no;
                        buf[47]                  = mcu_crc8_calc(buf + 11, 36);
                        ret                      = joycon_write(jc, JOYCON_CMD_RAW, 0, sizeof(buf), 0, buf);

                        memcpy(image + (300 * got_frag_no), buf_reply + 59, 300);

                        previous_frag_no = got_frag_no;
                    }
                }
                // Got the requested missed fragments.
                else if (missed_packet_no == got_frag_no) {
                    // debug
                    // printf("%02X Frag: Got missed %02X\n", got_frag_no, missed_packet_no);

                    // ACK for fragment
                    hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
                    buf[14]                  = got_frag_no;
                    buf[47]                  = mcu_crc8_calc(buf + 11, 36);
                    ret                      = joycon_write(jc, JOYCON_CMD_RAW, 0, sizeof(buf), 0, buf);

                    memcpy(image + (300 * got_frag_no), buf_reply + 59, 300);

                    previous_frag_no = got_frag_no;
                    missed_packet    = false;
                }
                // Repeat of fragment that is not max fragment.
                else {
                    // debug
                    // printf("%02X Frag: RepeatWoot M:%02X\n", got_frag_no, missed_packet_no);

                    // ACK for fragment
                    hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
                    buf[14]                  = got_frag_no;
                    buf[47]                  = mcu_crc8_calc(buf + 11, 36);
                    ret                      = joycon_write(jc, JOYCON_CMD_RAW, 0, sizeof(buf), 0, buf);
                }

                // Status percentage
                // ir_status << std::fixed << std::setprecision(0) << (float)got_frag_no / (float)(ir_max_frag_no + 1) * 100.0f;
                // ir_status << "% - ";

            }

            // Streaming start
            else {
                // ACK for fragment
                hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
                buf[14]                  = got_frag_no;
                buf[47]                  = mcu_crc8_calc(buf + 11, 36);
                ret                      = joycon_write(jc, JOYCON_CMD_RAW, 0, sizeof(buf), 0, buf);

                memcpy(image + (300 * got_frag_no), buf_reply + 59, 300);

                // debug
                // printf("%02X Frag: 0 %02X\n", buf_reply[52], previous_frag_no);

                previous_frag_no = 0;
            }

        }
        // Empty IR report. Send Ack again. Otherwise, it fallbacks to high latency mode (30ms per data fragment)
        else if (buf_reply[0] == 0x31) {
            // ACK for fragment
            hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;

            // Send ACK again or request missed frag
            if (buf_reply[49] == 0xFF) {
                buf[14] = previous_frag_no;
            } else if (buf_reply[49] == 0x00) {
                buf[12] = 0x1;
                buf[13] = previous_frag_no + 1;
                buf[14] = 0;
                // printf("%02X Mode: Missed next packet %02X\n", buf_reply[49], previous_frag_no + 1);
            }

            buf[47] = mcu_crc8_calc(buf + 11, 36);
            ret     = joycon_write(jc, JOYCON_CMD_RAW, 0, sizeof(buf), 0, buf);

            buf[12] = 0x00;
            buf[13] = 0x00;
        }
    }

    return ret;
}

// this function is referenced and modified from jc_toolkit
static joycon_err ir_sensor(joyconlib_t* jc, ir_image_config* ir_cfg)
{
    u8 buf[0x170];
    static int output_buffer_length = 49;
    int error_reading               = 0;
    int res_get                     = 0;
    brcm_hdr* hdr                   = (brcm_hdr*)buf;
    brcm_cmd_01* pkt                = (brcm_cmd_01*)(hdr + 1);
    joycon_err ret                  = joycon_mcu_open(jc, 0x05);
    if (ret) {
        joycon_mcu_close(jc);
        return ret;
    }

    // step5:
    // Set IR mode and number of packets for each data blob. Blob size is packets * 300 bytes.
    error_reading = 0;
    while (1) {
        memset(buf, 0, sizeof(buf));
        // auto hdr   = (brcm_hdr *)buf;
        // auto pkt   = (brcm_cmd_01 *)(hdr + 1);
        hdr->cmd   = 0x01;
        hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;

        pkt->subcmd                      = 0x21;
        pkt->subcmd_21_23_01.mcu_cmd     = 0x23;
        pkt->subcmd_21_23_01.mcu_subcmd  = 0x01; // Set IR mode cmd
        pkt->subcmd_21_23_01.mcu_ir_mode = 0x07; // IR mode - 2: No mode/Disable?, 3: Moment, 4: Dpd (Wii-style pointing), 6: Clustering,
        // 7: Image transfer, 8-10: Hand analysis (Silhouette, Image, Silhouette/Image), 0,1/5/10+: Unknown
        pkt->subcmd_21_23_01.no_of_frags = jc->ir_max_frag_no; // Set number of packets to output per buffer
        pkt->subcmd_21_23_01.mcu_major_v = 0x0500;             // Set required IR MCU FW v5.18. Major 0x0005.
        pkt->subcmd_21_23_01.mcu_minor_v = 0x1800;             // Set required IR MCU FW v5.18. Minor 0x0018.

        buf[48] = mcu_crc8_calc(buf + 12, 36);
        // res         = hid_write(handle, buf, output_buffer_length);
        // int retries = 0;
        // while (1) {
        //     res = hid_read_timeout(handle, buf, sizeof(buf), 64);
        //     if (buf[0] == 0x21) {
        ret = joycon_write(jc, JOYCON_CMD_RAW, 0, output_buffer_length, 0, buf);
        if (!ret) {
            size_t sz = sizeof(buf);
            ret       = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_MCU_CONF, JOYCON_ACK_MCU, buf, &sz);
            if (!ret) {
                // Mode set Ack
                if (buf[15] == 0x0b)
                    goto step6;
            }
            // retries++;
            // if (retries > 8 || res == 0)
            //     break;
        }
        error_reading++;
        if (error_reading > 7) {
            res_get = 6;
            goto step10;
        }
    }

step6:
    // Request IR mode status
#if 0    
    error_reading = 0;
    while (0) { // Not necessary
        memset(buf, 0, sizeof(buf));
        auto hdr   = (brcm_hdr *)buf;
        auto pkt   = (brcm_cmd_01 *)(hdr + 1);
        hdr->cmd   = 0x11;
        hdr->timer = timming_byte & 0xF;
        timming_byte++;

        pkt->subcmd          = 0x03;
        pkt->subcmd_arg.arg1 = 0x02;

        buf[47]     = mcu_crc8_calc(buf + 11, 36);
        buf[48]     = 0xFF;
        res         = hid_write(handle, buf, output_buffer_length);
        int retries = 0;
        while (1) {
            res = hid_read_timeout(handle, buf, sizeof(buf), 64);
            if (buf[0] == 0x31) {
                // mode set to 7: Image transfer
                if (buf[49] == 0x13 && *(u16 *)&buf[50] == 0x0700)
                    goto step7;
            }
            retries++;
            if (retries > 4 || res == 0)
                break;
        }
        error_reading++;
        if (error_reading > 7) {
            res_get = 7;
            goto step10;
        }
    }
#endif
    // step7:
    // Write to registers for the selected IR mode
    error_reading = 0;
    while (1) {
        memset(buf, 0, sizeof(buf));
        // auto hdr   = (brcm_hdr *)buf;
        // brcm_cmd_01 *pkt = (brcm_cmd_01 *)(buf + 10);
        hdr->cmd   = 0x01;
        hdr->timer = jc->packnum = (jc->packnum + 1) & 0xF;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;
        pkt->subcmd = 0x21;

        pkt->subcmd_21_23_04.mcu_cmd    = 0x23; // Write register cmd
        pkt->subcmd_21_23_04.mcu_subcmd = 0x04; // Write register to IR mode subcmd
        pkt->subcmd_21_23_04.no_of_reg  = 0x06; // Number of registers to write. Max 9.

        pkt->subcmd_21_23_04.reg1_addr = 0x2e00; // R: 0x002e - Set Resolution based on sensor binning and skipping
        pkt->subcmd_21_23_04.reg1_val  = ir_cfg->ir_res_reg;
        pkt->subcmd_21_23_04.reg2_addr = 0x3001; // R: 0x0130 - Set Exposure time LSByte - (31200 * us /1000) & 0xFF - Max: 600us, Max encoded: 0x4920.
        pkt->subcmd_21_23_04.reg2_val  = ir_cfg->ir_exposure & 0xFF;
        pkt->subcmd_21_23_04.reg3_addr = 0x3101; // R: 0x0131 - Set Exposure time MSByte - ((31200 * us /1000) & 0xFF00) >> 8
        pkt->subcmd_21_23_04.reg3_val  = (ir_cfg->ir_exposure & 0xFF00) >> 8;
        // pkt->subcmd_21_23_04.reg4_addr = 0x3201; // R: 0x0132 - Enable Max exposure Time - 0: Manual exposure, 1: Max exposure
        // pkt->subcmd_21_23_04.reg4_val  = 0x00;
        pkt->subcmd_21_23_04.reg5_addr = 0x1000;   // R: 0x0010 - Set IR Leds groups state - Only 3 LSB usable
        pkt->subcmd_21_23_04.reg5_val  = 0b000000; // Both Far/Narrow 75° and Near/Wide 130° Led groups are enabled.
#if 0
        pkt->subcmd_21_23_04.reg5_val  = ir_cfg->ir_leds;
        pkt->subcmd_21_23_04.reg6_addr = 0x2e01; // R: 0x012e - Set digital gain LSB 4 bits of the value - 0-0xff
        pkt->subcmd_21_23_04.reg6_val  = (ir_cfg->ir_digital_gain & 0xF) << 4;
        pkt->subcmd_21_23_04.reg7_addr = 0x2f01; // R: 0x012f - Set digital gain MSB 4 bits of the value - 0-0x7
        pkt->subcmd_21_23_04.reg7_val  = (ir_cfg->ir_digital_gain & 0xF0) >> 4;
        pkt->subcmd_21_23_04.reg8_addr = 0x0e00; // R: 0x00e0 - External light filter - LS o bit0: Off/On, bit1: 0x/1x, bit2: ??, bit4,5: ??.
        pkt->subcmd_21_23_04.reg8_val  = ir_cfg->ir_ex_light_filter;
        pkt->subcmd_21_23_04.reg9_addr = 0x4301; // R: 0x0143 - ExLF/White pixel stats threshold - 200: Default
        pkt->subcmd_21_23_04.reg9_val  = 0xc8;

        buf[48] = mcu_crc8_calc(buf + 12, 36);

        ret = joycon_write(jc, JOYCON_CMD_RAW, 0, output_buffer_length, 0, buf);
        // res     = hid_write(handle, buf, output_buffer_length);

        // Request IR mode status, before waiting for the x21 ack
        memset(buf, 0, sizeof(buf));
        hdr->cmd   = 0x11;
        hdr->timer = jc->packnum = (jc->packnum++) & 0xF;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;
        pkt->subcmd          = 0x03;
        pkt->subcmd_arg.arg1 = 0x02;
        buf[47]              = mcu_crc8_calc(buf + 11, 36);
        buf[48]              = 0xFF;
        // res                  = hid_write(handle, buf, output_buffer_length);

        // int retries = 0;
        // while (1) {
        //     res = hid_read_timeout(handle, buf, sizeof(buf), 64);
        //     if (buf[0] == 0x21) {
        ret = joycon_write(jc, JOYCON_CMD_RAW, 0, output_buffer_length, 0, buf);
        if (!ret) {
            int sz = sizeof(buf);
            ret    = joycon_read(jc, JOYCON_REPORT_SUBCMD, 0, 0, buf, &sz);
            if (!ret) {
                // Registers for mode 7: Image transfer set
                if (buf[15] == 0x13 && *(u16 *)&buf[16] == 0x0700)
                    goto step8;
            }
            // retries++;
            // if (retries > 8 || res == 0)
            //     break;
        }
        error_reading++;
        if (error_reading > 7) {
            res_get = 8;
            goto step10;
        }
    }

step8:
    // Write to registers for the selected IR mode
    error_reading = 0;
    while (1) {
        memset(buf, 0, sizeof(buf));
        // auto hdr   = (brcm_hdr *)buf;
        // brcm_cmd_01 *pkt = (brcm_cmd_01 *)(buf + 10);
        hdr->cmd   = 0x01;
        hdr->timer = jc->packnum = (jc->packnum++) & 0xF;
        // hdr->timer = timming_byte & 0xF;
        // timming_byte++;
        pkt->subcmd = 0x21;

        pkt->subcmd_21_23_04.mcu_cmd    = 0x23; // Write register cmd
        pkt->subcmd_21_23_04.mcu_subcmd = 0x04; // Write register to IR mode subcmd
        pkt->subcmd_21_23_04.no_of_reg  = 0x08; // Number of registers to write. Max 9.

        pkt->subcmd_21_23_04.reg1_addr = 0x1100; // R: 0x0011 - Leds 1/2 Intensity - Max 0x0F.
        pkt->subcmd_21_23_04.reg1_val  = (ir_cfg.ir_leds_intensity >> 8) & 0xFF;
        pkt->subcmd_21_23_04.reg2_addr = 0x1200; // R: 0x0012 - Leds 3/4 Intensity - Max 0x10.
        pkt->subcmd_21_23_04.reg2_val  = ir_cfg.ir_leds_intensity & 0xFF;
        pkt->subcmd_21_23_04.reg3_addr = 0x2d00; // R: 0x002d - Flip image - 0: Normal, 1: Vertically, 2: Horizontally, 3: Both
        pkt->subcmd_21_23_04.reg3_val  = ir_cfg.ir_flip;
        pkt->subcmd_21_23_04.reg4_addr = 0x6701; // R: 0x0167 - Enable De-noise smoothing algorithms - 0: Disable, 1: Enable.
        pkt->subcmd_21_23_04.reg4_val  = (ir_cfg.ir_denoise >> 16) & 0xFF;
        pkt->subcmd_21_23_04.reg5_addr = 0x6801; // R: 0x0168 - Edge smoothing threshold - Max 0xFF, Default 0x23
        pkt->subcmd_21_23_04.reg5_val  = (ir_cfg.ir_denoise >> 8) & 0xFF;
        pkt->subcmd_21_23_04.reg6_addr = 0x6901; // R: 0x0169 - Color Interpolation threshold - Max 0xFF, Default 0x44
        pkt->subcmd_21_23_04.reg6_val  = ir_cfg.ir_denoise & 0xFF;
#endif
        // pkt->subcmd_21_23_04.reg6_addr = 0x1100; // R: 0x0011 - Leds 1/2 Intensity - Max 0x0F.
        // pkt->subcmd_21_23_04.reg6_val  = 0x0F;
        // pkt->subcmd_21_23_04.reg7_addr = 0x1200; // R: 0x0012 - Leds 3/4 Intensity - Max 0x10.
        // pkt->subcmd_21_23_04.reg7_val  = 0x10;
        pkt->subcmd_21_23_04.reg4_addr = 0x0400; // R: 0x0004 - LSB Buffer Update Time - Default 0x32
        if (ir_cfg->ir_res_reg == 0x69)
            pkt->subcmd_21_23_04.reg4_val = 0x2d; // A value of <= 0x2d is fast enough for 30 x 40, so the first fragment has the updated frame.
        else
            pkt->subcmd_21_23_04.reg4_val = 0x32; // All the other resolutions the default is enough. Otherwise a lower value can break hand analysis.
        pkt->subcmd_21_23_04.reg6_addr = 0x0700;  // R: 0x0007 - Finalize config - Without this, the register changes do not have any effect.
        pkt->subcmd_21_23_04.reg6_val  = 0x01;

        buf[48] = mcu_crc8_calc(buf + 12, 36);
        // res     = hid_write(handle, buf, output_buffer_length);

        // int retries = 0;
        // while (1) {
        //     res = hid_read_timeout(handle, buf, sizeof(buf), 64);
        //     if (buf[0] == 0x21) {

        ret = joycon_write(jc, JOYCON_CMD_RAW, 0, output_buffer_length, 0, buf);
        if (!ret) {
            size_t sz = sizeof(buf);
            ret       = joycon_read(jc, JOYCON_REPORT_SUBCMD, JOYCON_SUB_MCU_CONF, JOYCON_ACK_MCU, buf, &sz);
            if (!ret) {
                // Registers for mode 7: Image transfer set
                if (buf[15] == 0x13 && *(u16*)&buf[16] == 0x0700)
                    goto step9;
                // If the Joy-Con gets to reply to the previous x11 - x03 02 cmd before sending the above,
                // it will reply with the following if we do not send x11 - x03 02 again:
                else if (buf[15] == 0x23) // Got mcu mode config write.
                    goto step9;
            }
            // retries++;
            // if (retries > 8 || res == 0)
            //     break;
        }
        error_reading++;
        if (error_reading > 7) {
            res_get = 9;
            goto step10;
        }
    }

step9:
    return JOYCON_ERR_NONE;
step10:
    joycon_mcu_close(jc);

    switch (res_get) {
    case 6:
        return JOYCON_ERR_MCU_6IRMODESET;
        break;
    case 7:
        return JOYCON_ERR_MCU_7IRSETBUSY;
        break;
    case 8:
        return JOYCON_ERR_MCU_8IRCFG;
        break;
    case 9:
        return JOYCON_ERR_MCU_9IRFCFG;
        break;
    default:
        return JOYCON_ERR_UNKNOWN;
    }
}

/*
 * @fn      joycon_enable_ir
 * @brief   ジョイコンのIRカメラの準備
 *  IRカメラを使用するための設定を行う
 * @param[in] jc ジョイコン情報
 * @param[in] resolution 解像度
 * @param[in] exposure 露出時間（シャッター速度）
 *  0 - 600 (us,$0 - 1/1666.66s$)で指定する
 * @return  エラーコード
 */
joycon_err joycon_enable_ir(joyconlib_t* jc, joycon_ir_resolution resolution, u16 exposure)
{
    if (!jc)
        return JOYCON_ERR_INVALID_ARGUMENT;
    if (jc->type != JOYCON_R)
        return JOYCON_ERR_INVALID_TYPE;

    ir_image_config ir_new_config;
    // Resolution config register and no of packets expected
    // The sensor supports a max of Binning [4 x 2] and max Skipping [4 x 4]
    // The maximum reduction in resolution is a combined Binning/Skipping [16 x 8]
    // The bits control the matrices used. Skipping [Bits0,1 x Bits2,3], Binning [Bits4,5 x Bit6]. Bit7 is unused.
    switch (resolution) {
    case JOYCON_IR320X240:
        ir_new_config.ir_res_reg = 0b00000000; // Full pixel array
        jc->ir_max_frag_no       = 0xff;
        break;
    case JOYCON_IR160X120:
        ir_new_config.ir_res_reg = 0b01010000; // Sensor Binning [2 X 2]
        jc->ir_max_frag_no       = 0x3f;
        break;
    case JOYCON_IR80X60:
        ir_new_config.ir_res_reg = 0b01100100; // Sensor Binning [4 x 2] and Skipping [1 x 2]
        jc->ir_max_frag_no       = 0x0f;
        break;
    case JOYCON_IR40X30:
        ir_new_config.ir_res_reg = 0b01101001; // Sensor Binning [4 x 2] and Skipping [2 x 4]
        jc->ir_max_frag_no       = 0x03;
        break;
    default:
        return JOYCON_ERR_INVALID_ARGUMENT;
    }

    // Exposure time (Shutter speed) is in us. Valid values are 0 to 600us or 0 - 1/1666.66s
    if (exposure > 600)
        return JOYCON_ERR_INVALID_ARGUMENT;
    ir_new_config.ir_exposure = (u16)(exposure * 31200 / 1000);

    joycon_err ret = ir_sensor(jc, &ir_new_config);
    if (!ret) {
        jc->ir_enable     = 1;
        jc->ir_resolution = resolution;
        jc->ir_exposure   = exposure;
    }
    return ret;
}

#if 0
// this function is referenced and modified from jc_toolkit
int get_ir_registers(int start_reg, int reg_group)
{
    int res;
    u8 buf[0x170];
    static int output_buffer_length = 49;
    int error_reading               = 0;
    int res_get                     = 0;

    // Get the IR registers
    error_reading        = 0;
    int pos_ir_registers = start_reg;
    while (1) {
    repeat_send:
        memset(buf, 0, sizeof(buf));
        auto hdr = (brcm_hdr*)buf;
        auto pkt = (brcm_cmd_01*)(hdr + 1);
        memset(buf, 0, sizeof(buf));
        hdr->cmd   = 0x11;
        hdr->timer = timming_byte & 0xF;
        timming_byte++;
        pkt->subcmd          = 0x03;
        pkt->subcmd_arg.arg1 = 0x03;

        buf[12] = 0x1; // seems to be always 0x01

        buf[13] = pos_ir_registers; // 0-4 registers page/group
        buf[14] = 0x00;             // offset. this plus the number of registers, must be less than x7f
        buf[15] = 0x7f;             // Number of registers to show + 1

        buf[47] = mcu_crc8_calc(buf + 11, 36);

        res = hid_write(handle, buf, output_buffer_length);

        int tries = 0;
        while (1) {
            res = hid_read_timeout(handle, buf, sizeof(buf), 64);
            if (buf[49] == 0x1b && buf[51] == pos_ir_registers && buf[52] == 0x00) {
                error_reading = 0;
                printf("--->%02X, %02X : %02X:\n", buf[51], buf[52], buf[53]);
                for (int i = 0; i <= buf[52] + buf[53]; i++)
                    if ((i & 0xF) == 0xF)
                        printf("%02X | ", buf[54 + i]);
                    else
                        printf("%02X ", buf[54 + i]);
                printf("\n");
                break;
            }
            tries++;
            if (tries > 8) {
                error_reading++;
                if (error_reading > 5) {
                    return 1;
                }
                goto repeat_send;
            }
        }
        pos_ir_registers++;
        if (pos_ir_registers > reg_group) {
            break;
        }
    }
    printf("\n");

    return 0;
}

// this function is referenced and modified from jc_toolkit
static int ir_sensor_config_live(joyconlib_t* jc, ir_image_config* ir_cfg)
{
    int res;
    u8 buf[49];

    memset(buf, 0, sizeof(buf));
    brcm_hdr* hdr    = (brcm_hdr*)buf;
    brcm_cmd_01* pkt = (brcm_cmd_01*)(hdr + 1);
    hdr->cmd         = 0x01;
    hdr->timer = jc->packnum = (jc->packnum++) & 0xF;
    // hdr->timer = timming_byte & 0xF;
    // timming_byte++;
    pkt->subcmd = 0x21;

    pkt->subcmd_21_23_04.mcu_cmd    = 0x23; // Write register cmd
    pkt->subcmd_21_23_04.mcu_subcmd = 0x04; // Write register to IR mode subcmd
    pkt->subcmd_21_23_04.no_of_reg  = 0x09; // Number of registers to write. Max 9.

    pkt->subcmd_21_23_04.reg1_addr = 0x3001; // R: 0x0130 - Set Exposure time LSByte
    pkt->subcmd_21_23_04.reg1_val  = ir_cfg.ir_exposure & 0xFF;
    pkt->subcmd_21_23_04.reg2_addr = 0x3101; // R: 0x0131 - Set Exposure time MSByte
    pkt->subcmd_21_23_04.reg2_val  = (ir_cfg.ir_exposure & 0xFF00) >> 8;
    pkt->subcmd_21_23_04.reg3_addr = 0x1000; // R: 0x0010 - Set IR Leds groups state
    pkt->subcmd_21_23_04.reg3_val  = ir_cfg.ir_leds;
    pkt->subcmd_21_23_04.reg4_addr = 0x2e01; // R: 0x012e - Set digital gain LSB 4 bits
    pkt->subcmd_21_23_04.reg4_val  = (ir_cfg.ir_digital_gain & 0xF) << 4;
    pkt->subcmd_21_23_04.reg5_addr = 0x2f01; // R: 0x012f - Set digital gain MSB 4 bits
    pkt->subcmd_21_23_04.reg5_val  = (ir_cfg.ir_digital_gain & 0xF0) >> 4;
    pkt->subcmd_21_23_04.reg6_addr = 0x0e00; // R: 0x00e0 - External light filter
    pkt->subcmd_21_23_04.reg6_val  = ir_cfg.ir_ex_light_filter;
    pkt->subcmd_21_23_04.reg7_addr = (ir_cfg.ir_custom_register & 0xFF) << 8 | (ir_cfg.ir_custom_register >> 8) & 0xFF;
    pkt->subcmd_21_23_04.reg7_val  = (ir_cfg.ir_custom_register >> 16) & 0xFF;
    pkt->subcmd_21_23_04.reg8_addr = 0x1100; // R: 0x0011 - Leds 1/2 Intensity - Max 0x0F.
    pkt->subcmd_21_23_04.reg8_val  = (ir_cfg.ir_leds_intensity >> 8) & 0xFF;
    pkt->subcmd_21_23_04.reg9_addr = 0x1200; // R: 0x0012 - Leds 3/4 Intensity - Max 0x10.
    pkt->subcmd_21_23_04.reg9_val  = ir_cfg.ir_leds_intensity & 0xFF;

    buf[48] = mcu_crc8_calc(buf + 12, 36);
    res     = hid_write(jc->handle, buf, sizeof(buf));

    // Important. Otherwise we gonna have a dropped packet.
    usleep(15 * 1000);

    pkt->subcmd_21_23_04.no_of_reg = 0x06; // Number of registers to write. Max 9.

    pkt->subcmd_21_23_04.reg1_addr = 0x2d00; // R: 0x002d - Flip image - 0: Normal, 1: Vertically, 2: Horizontally, 3: Both
    pkt->subcmd_21_23_04.reg1_val  = ir_cfg.ir_flip;
    pkt->subcmd_21_23_04.reg2_addr = 0x6701; // R: 0x0167 - Enable De-noise smoothing algorithms - 0: Disable, 1: Enable.
    pkt->subcmd_21_23_04.reg2_val  = (ir_cfg.ir_denoise >> 16) & 0xFF;
    pkt->subcmd_21_23_04.reg3_addr = 0x6801; // R: 0x0168 - Edge smoothing threshold - Max 0xFF, Default 0x23
    pkt->subcmd_21_23_04.reg3_val  = (ir_cfg.ir_denoise >> 8) & 0xFF;
    pkt->subcmd_21_23_04.reg4_addr = 0x6901; // R: 0x0169 - Color Interpolation threshold - Max 0xFF, Default 0x44
    pkt->subcmd_21_23_04.reg4_val  = ir_cfg.ir_denoise & 0xFF;
    pkt->subcmd_21_23_04.reg5_addr = 0x0400; // R: 0x0004 - LSB Buffer Update Time - Default 0x32
    if (ir_cfg.ir_res_reg == 0x69)
        pkt->subcmd_21_23_04.reg5_val = 0x2d; // A value of <= 0x2d is fast enough for 30 x 40, so the first fragment has the updated frame.
    else
        pkt->subcmd_21_23_04.reg5_val = 0x32; // All the other resolutions the default is enough. Otherwise a lower value can break hand analysis.
    pkt->subcmd_21_23_04.reg6_addr = 0x0700;  // R: 0x0007 - Finalize config - Without this, the register changes do not have any effect.
    pkt->subcmd_21_23_04.reg6_val  = 0x01;

    buf[48] = mcu_crc8_calc(buf + 12, 36);
    res     = hid_write(jc->handle, buf, sizeof(buf));

    // get_ir_registers(0,4); // Get all register pages
    // get_ir_registers((ir_cfg.ir_custom_register >> 8) & 0xFF, (ir_cfg.ir_custom_register >> 8) & 0xFF); // Get all registers based on changed register's page

    return res;
}

// this function is referenced and modified from jc_toolkit
private:
System::Int32 prepareSendIRConfig(bool startNewConfig)
{
    String ^ error_msg;
    ir_image_config ir_new_config = { 0 };
    int res                       = 0;

    this->lbl_IRStatus->Text = "Status: Configuring";
    Application::DoEvents();

    // The IR camera lens has a FoV of 123�. The IR filter is a NIR 850nm wavelength pass filter.

    // Resolution config register and no of packets expected
    // The sensor supports a max of Binning [4 x 2] and max Skipping [4 x 4]
    // The maximum reduction in resolution is a combined Binning/Skipping [16 x 8]
    // The bits control the matrices used. Skipping [Bits0,1 x Bits2,3], Binning [Bits4,5 x Bit6]. Bit7 is unused.
    if (startNewConfig) {
        if (this->radioBtn_IR240p->Checked) {
            ir_image_width           = 320;
            ir_image_height          = 240;
            ir_new_config.ir_res_reg = 0b00000000; // Full pixel array
            ir_max_frag_no           = 0xff;
        } else if (this->radioBtn_IR120p->Checked) {
            ir_image_width           = 160;
            ir_image_height          = 120;
            ir_new_config.ir_res_reg = 0b01010000; // Sensor Binning [2 X 2]
            ir_max_frag_no           = 0x3f;
        } else if (this->radioBtn_IR60p->Checked) {
            ir_image_width           = 80;
            ir_image_height          = 60;
            ir_new_config.ir_res_reg = 0b01100100; // Sensor Binning [4 x 2] and Skipping [1 x 2]
            ir_max_frag_no           = 0x0f;
        } else if (this->radioBtn_IR30p->Checked) {
            ir_image_width           = 40;
            ir_image_height          = 30;
            ir_new_config.ir_res_reg = 0b01101001; // Sensor Binning [4 x 2] and Skipping [2 x 4]
            ir_max_frag_no           = 0x03;
        } else {
            return 8;
        }
    }

    // Enable IR Leds. Only the following configurations are supported.
    if (this->chkBox_IRBrightLeds->Checked == true && this->chkBox_IRDimLeds->Checked == true)
        ir_new_config.ir_leds = 0b000000; // Both Far/Narrow 75� and Near/Wide 130� Led groups are enabled.
    else if (this->chkBox_IRBrightLeds->Checked == true && this->chkBox_IRDimLeds->Checked == false)
        ir_new_config.ir_leds = 0b100000; // Only Far/Narrow 75� Led group is enabled.
    else if (this->chkBox_IRBrightLeds->Checked == false && this->chkBox_IRDimLeds->Checked == true)
        ir_new_config.ir_leds = 0b010000; // Only Near/Wide 130� Led group is enabled.
    else if (this->chkBox_IRBrightLeds->Checked == false && this->chkBox_IRDimLeds->Checked == false)
        ir_new_config.ir_leds = 0b110000; // Both groups disabled

    // IR Leds Intensity
    ir_new_config.ir_leds_intensity = ((u8)this->trackBar_IRBrightLeds->Value << 8) | (u8)this->trackBar_IRDimLeds->Value;

    // IR Leds Effects
    if (this->chkBox_IRFlashlight->Checked)
        ir_new_config.ir_leds |= 0b01;
    if (this->chkBox_IRStrobe->Checked)
        ir_new_config.ir_leds |= 0b10000000;

    // External Light filter (Dark-frame subtraction). Additionally, disable if leds in flashlight mode.
    if ((this->chkBox_IRExFilter->Checked || this->chkBox_IRStrobe->Checked) && this->chkBox_IRExFilter->Enabled)
        ir_new_config.ir_ex_light_filter = 0x03;
    else
        ir_new_config.ir_ex_light_filter = 0x00;

    // Flip image. Food for tracking camera movement when taking selfies :P
    if (this->chkBox_IRSelfie->Checked)
        ir_new_config.ir_flip = 0x02;
    else
        ir_new_config.ir_flip = 0x00;

    // Exposure time (Shutter speed) is in us. Valid values are 0 to 600us or 0 - 1/1666.66s
    ir_new_config.ir_exposure = (u16)(this->numeric_IRExposure->Value * 31200 / 1000);
    if (!this->chkBox_IRAutoExposure->Checked && enable_IRVideoPhoto) {
        enable_IRAutoExposure         = false;
        ir_new_config.ir_digital_gain = (u8)this->trackBar_IRGain->Value;
    } else {
        enable_IRAutoExposure         = true;
        ir_new_config.ir_digital_gain = 1; // Disable digital gain for auto exposure
    }

    // De-noise algorithms
    if (this->chkBox_IRDenoise->Checked)
        ir_new_config.ir_denoise = 0x01 << 16;
    else
        ir_new_config.ir_denoise = 0x00 << 16;
    ir_new_config.ir_denoise |= ((u8)this->numeric_IRDenoiseEdgeSmoothing->Value & 0xFF) << 8;
    ir_new_config.ir_denoise |= (u8)this->numeric_IRDenoiseColorInterpolation->Value & 0xFF;

    // Initialize camera
    if (startNewConfig) {
        // Configure the IR camera and take a photo or stream.
        res = ir_sensor(ir_new_config);

        // Get error
        switch (res) {
        case 1:
            error_msg = "1ID31";
            break;
        case 2:
            error_msg = "2MCUON";
            break;
        case 3:
            error_msg = "3MCUONBUSY";
            break;
        case 4:
            error_msg = "4MCUMODESET";
            break;
        case 5:
            error_msg = "5MCUSETBUSY";
            break;
        case 6:
            error_msg = "6IRMODESET";
            break;
        case 7:
            error_msg = "7IRSETBUSY";
            break;
        case 8:
            error_msg = "8IRCFG";
            break;
        case 9:
            error_msg = "9IRFCFG";
            break;
        default:
            break;
        }
        if (res > 0)
            this->lbl_IRStatus->Text = "Status: Error " + error_msg + "!";
    }
    // Change camera configuration
    else {
        ir_new_config.ir_custom_register = ((u16)this->numeric_IRCustomRegAddr->Value) | ((u8)this->numeric_IRCustomRegVal->Value << 16);
        res                              = ir_sensor_config_live(ir_new_config);
    }

    return res;
}
#endif