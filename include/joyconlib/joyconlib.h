/*!
 * @file    joyconlib.h
 * @brief   Joy-Conライブラリ ヘッダ
 * @author  K. Morita
 * @remarks
 * The following resources/projects were referenced for this library:
 *  https://github.com/dekuNukem/Nintendo_Switch_Reverse_Engineering
 *  https://github.com/CTCaer/jc_toolkit
 *
 * @copyright
 * Copyright (c) 2022 K. Morita, All Rights Reserved.
 * this library is released under the MIT license, see the end of this file.
 */
#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include <hidapi/hidapi.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

//! エラーコード
typedef enum {
    JOYCON_ERR_NONE             = 0,   //!< 正常終了
    JOYCON_ERR_INVALID_ARGUMENT = -1,  //!< 不正な引数
    JOYCON_ERR_OPEN_FAILED      = -2,  //!< オープン失敗
    JOYCON_ERR_WRITE_FAILED     = -3,  //!< データ送信失敗
    JOYCON_ERR_READ_FAILED      = -4,  //!< データ読込失敗
    JOYCON_ERR_READ_TIMEOUT     = -5,  //!< データ読込タイムアウト
    JOYCON_ERR_READ_NODATA      = -6,  //!< 読込データ無し
    JOYCON_ERR_INVALID_TYPE     = -7,  //!< 不正なタイプ
    JOYCON_ERR_MCU_1ID31        = -11, //!< NFC/IR初期化エラー1
    JOYCON_ERR_MCU_2MCUON       = -12, //!< NFC/IR初期化エラー2
    JOYCON_ERR_MCU_3MCUONBUSY   = -13, //!< NFC/IR初期化エラー3
    JOYCON_ERR_MCU_4MCUMODESET  = -14, //!< NFC/IR初期化エラー4
    JOYCON_ERR_MCU_5MCUSETBUSY  = -15, //!< NFC/IR初期化エラー5
    JOYCON_ERR_MCU_6NFCPOLL     = -16, //!< NFC読み取り準備エラー
    JOYCON_ERR_MCU_NOTAG        = -17, //!< NFCタグ読み取りエラー
    JOYCON_ERR_MCU_NOTSUPPORTED = -18, //!< NFC未サポートのタグ
    JOYCON_ERR_MCU_READ         = -19, //!< NFC読み取りエラー
    JOYCON_ERR_MCU_IRNOREADY    = -21, //!< IR未初期化
    JOYCON_ERR_MCU_6IRMODESET   = -26, //!< IR設定エラー1
    JOYCON_ERR_MCU_7IRSETBUSY   = -27, //!< IR設定中エラー
    JOYCON_ERR_MCU_8IRCFG       = -28, //!< IR設定エラー2
    JOYCON_ERR_MCU_9IRFCFG      = -29, //!< IR設定エラー3
    JOYCON_ERR_UNKNOWN          = -99  //!< 不明エラー
} joycon_err;

//! ジョイコンタイプ
typedef enum {
    JOYCON_L = 0x1, //!< 左
    JOYCON_R = 0x2  //!< 右
} joycon_type;

#pragma pack(push, 1)
/*! @brief ジョイコンボタン
 *
 *  ジョイコンから取得したボタンの情報を保持する。
 *  押されているときに1となる
 */
typedef union {
    u8 byte[3];
    struct {
        u8 Y : 1;       //!< Yボタン（右）
        u8 X : 1;       //!< Xボタン（右）
        u8 B : 1;       //!< Bボタン（右）
        u8 A : 1;       //!< Aボタン（右）
        u8 SR_r : 1;    //!< SRボタン（右）
        u8 SL_r : 1;    //!< SLボタン（右）
        u8 R : 1;       //!< Rボタン（右）
        u8 ZR : 1;      //!< ZRボタン（右）
        u8 Minus : 1;   //!< -ボタン（左）
        u8 Plus : 1;    //!< +ボタン（右）
        u8 RStick : 1;  //!< スティックのボタン（右）
        u8 LStick : 1;  //!< スティックのボタン（左）
        u8 Home : 1;    //!< ホームボタン（右）
        u8 Capture : 1; //!< キャプチャーボタン（左）
        u8 dummy : 1;   //!< 未使用
        u8 grip : 1;    //!< チャージンググリップなどを接続すると1
        u8 Down : 1;    //!< ↓ボタン（左）
        u8 Up : 1;      //!< ↑ボタン（左）
        u8 Right : 1;   //!< →ボタン（左）
        u8 Left : 1;    //!< ←ボタン（左）
        u8 SR_l : 1;    //!< SRボタン（左）
        u8 SL_l : 1;    //!< SLボタン（左）
        u8 L : 1;       //!< Lボタン（左）
        u8 ZL : 1;      //!< ZLボタン（左）
    } btn;
} joycon_btn;

/*! @brief ボタンの経過時間
 *
 *  ジョイコンの特定のボタンは押されてからの経過時間を取得できる
 *  単位は10msで最大値は65535(x10ms)
 */
typedef struct {
    u16 L;
    u16 R;
    u16 ZL;
    u16 ZR;
    u16 SL;
    u16 SR;
    u16 Home;
} joycon_elapsed;

/*! @brief ホームボタンのLED設定情報
 *
 *  明るさ，時間，繰り返しなどを指定することで
 *  複雑な点灯パターンを表現できる
 *  指定値はすべて0-15
 */
typedef struct {
    u8 mc_duration : 4; //!< 1サイクルの基準時間 Global Mini Cycle Duration. 8ms - 175ms. Value x0 = 0ms/OFF
    u8 mc_num : 4;      //!< サイクル数 Number of Mini Cycles. 1-15. If number of cycles is > 0 then x0 = x1
    u8 fc_num : 4;      //!< 全サイクルの繰り返し数 Number of Full Cycles. 1-15. Value x0 is repeat forever, but if also Byte x00 High nibble is set to x0, it does the 1st Mini Cycle and then the LED stays on with LED Start Intensity.
    u8 intensity : 4;   //!< LEDの明るさ初期値 LED Start Intensity. Value x0=0% - xF=100%
    struct {
        u8 mc2_intensity : 4;  //!< サイクル 2,4,6,8,10,12,14 のLED明るさ
        u8 mc1_intensity : 4;  //!< サイクル 1,3,5,7,9,11,13 のLED明るさ
        u8 mc1_duration : 4;   //!< サイクル 1,3,5,7,9,11,13 の時間（基準時間に対する倍数） LED Duration Multiplier of Mini Cycle 1,3,... x0 = x1 = x1
        u8 mc1_transition : 4; //!< 前サイクルから自サイクル(1,3,5,7,9,11,13)へのフェードイン/アウト時間（基準時間に対する倍数） Fading Transition Duration to Mini Cycle 1,3,... (Uses PWM). Value is a Multiplier of Global Mini Cycle Duration
        u8 mc2_duration : 4;   //!< サイクル 2,4,6,8,10,12,14 の時間（基準時間に対する倍数） LED Duration Multiplier of Mini Cycle 2,4,... x0 = x1 = x1
        u8 mc2_transition : 4; //!< 前サイクルから自サイクル(2,4,6,8,10,12,14)へのフェードイン/アウト時間（基準時間に対する倍数） Fading Transition Duration to Mini Cycle 2,4,... (Uses PWM). Value is a Multiplier of Global Mini Cycle Duration
    } mc[7];                   //!< 2サイクル*7で14回分の情報
    u8 unused : 4;             //!< 未使用
    u8 mc15_intensity : 4;     //!< サイクル15のLED明るさ
    u8 mc15_duration : 4;      //!< サイクル15の時間（基準時間に対する倍数） LED Duration Multiplier of Mini Cycle 15 x0 = x1 = x1
    u8 mc15_transition : 4;    //!< 前サイクルから自サイクル(15)へのフェードイン/アウト時間（基準時間に対する倍数） Fading Transition Duration to Mini Cycle 15 (Uses PWM). Value is a Multiplier of Global Mini Cycle Duration
} joycon_homeled;
#pragma pack(pop)

//! ホームボタンLED消灯
#define JOYCON_HOMELED_OFF ((joycon_homeled*)0x11)
//! ホームボタンLED点灯
#define JOYCON_HOMELED_ON ((joycon_homeled*)0x11f0f00f)
//! ホームボタンLED点滅
#define JOYCON_HOMELED_BLINK ((joycon_homeled*)0x21f0f00f0f)

#define JOYCON_LED_1_ON (0x01)    //!< led 1 点灯
#define JOYCON_LED_2_ON (0x02)    //!< led 2 点灯
#define JOYCON_LED_3_ON (0x04)    //!< led 3 点灯
#define JOYCON_LED_4_ON (0x08)    //!< led 4 点灯
#define JOYCON_LED_1_BLINK (0x10) //!< led 1 点滅
#define JOYCON_LED_2_BLINK (0x20) //!< led 2 点滅
#define JOYCON_LED_3_BLINK (0x40) //!< led 3 点滅
#define JOYCON_LED_4_BLINK (0x80) //!< led 4 点滅

/*! @brief スティックの位置情報
 *
 *  ジョイコン縦持ちで左右がx，上下がy
 *  範囲は -1.0 ～ 1.0
 */
typedef struct {
    float x;
    float y;
} joycon_stick;

/*! @brief 6軸センサー情報
 *
 *  ジョイコンの6軸センサーは，3つの加速度センサーとジャイロセンサーからなる
 *  各軸の向きなどは下記を参照
 *  https://github.com/dekuNukem/Nintendo_Switch_Reverse_Engineering/blob/master/imu_sensor_notes.md
 *
 *  単位は加速度センサーが @f$m/s^2@f$ ，ジャイロセンサーが @f$rad/s@f$ で，
 *  静止状態が0，ただし重力があるので重力（下）方向が約 @f$\pm 9.8m/s^2@f$ となる
 *  ジャイロは加速度の+方向を見て時計回りが+
 */
typedef struct {
    float acc_x;  //!< 加速度値 x
    float acc_y;  //!< 加速度値 y
    float acc_z;  //!< 加速度値 z
    float gyro_x; //!< ジャイロ値 x
    float gyro_y; //!< ジャイロ値 y
    float gyro_z; //!< ジャイロ値 z
} joycon_axis;

/*! @brief ジョイコン情報
 *
 *  内容を書き換えると動作しなくなることもあるので，
 *  読み取り専用として取り扱うこと
 */
typedef struct {
    hid_device* handle;  //!< ハンドル
    joycon_type type;    //!< タイプ
    u8 led_bk;           //!< オープン時のLED状態
    u8 packnum;          //!< 同期用
    u8 rumble[4];        //!< 振動
    u8 battery;          //!< バッテリー残量4段階
    joycon_btn button;   //!< ボタン
    joycon_stick stick;  //!< スティック
    joycon_axis axis[3]; //!< 6軸センサー，5ms間隔の取得値3つ分

    u16 stick_cal_x[3];      //!< 補正情報
    u16 stick_cal_y[3];      //!< 補正情報
    float acc_cal_coeff[3];  //!< 補正情報
    float gyro_cal_coeff[3]; //!< 補正情報
    s16 sensor_cal[3];       //!< 補正情報

    u8 ir_enable;      //!< IRセンサー使用中
    u8 ir_max_frag_no; //!< 必要領域
    u16 ir_resolution; //!< 解像度
    u16 ir_exposure;   //!< シャッター速度
} joyconlib_t;

//! NFCタイプ: NTAG
#define JOYCON_NFC_TYPE_NTAG (0x02)
//! NFCタイプ: MIFARE
#define JOYCON_NFC_TYPE_MIFARE (0x04)

/*! @brief NFCデータ
 *
 *  NFCから読み取ったデータを保存する
 */
typedef struct {
    u8 tag_type;       //!< タイプ
    u8 tag_uid_size;   //!< UIDのサイズ
    u8 tag_uid[10];    //!< UID
    u8 ntag_data_size; //!< NTAGデータサイズ
    u8 ntag_data[924]; //!< NTAGデータ
} joycon_nfc_data;

//! IRカメラ解像度
typedef enum {
    JOYCON_IR320X240 = 320, //!< 320 x 240 ピクセル
    JOYCON_IR160X120 = 160, //!< 160 x 120 ピクセル
    JOYCON_IR80X60   = 80,  //!< 80 x 60 ピクセル
    JOYCON_IR40X30   = 40   //!< 40 x 30 ピクセル
} joycon_ir_resolution;

//! IR取得画像の情報
typedef struct {
    u8 avg_intensity; //!< 平均強度(0-255) Average Intensity. 0-255 scale.
    u8 unknown;       //!< 不明 Unknown. Shows up only when EXFilter is enabled.
    u16 white_pixels; //!< 白(255値)ピクセルの数，最大値は65535 White pixels (pixels with 255 value). Max 65535. Uint16 constraints, even though max is 76800.
    u16 noise_pixels; //!< 環境ノイズのピクセル数 Pixels with ambient noise from external light sources (sun, lighter, IR remotes, etc). Cleaned by External Light Filter.
} joycon_ir_result;

/*!
 * @brief   ジョイコンを開く
 *
 *  あらかじめPCにジョイコンをBluetooth接続しておく必要がある
 * @param[out] jc オープンしたジョイコンの情報を保持する
 *  joyconlib_t構造体変数へのポインタ
 * @param[in] type オープンするジョイコンのタイプを
 *  JOYCON_R（右）か
 *  JOYCON_L（左）で指定する。
 * @return  エラーコード
 */
extern joycon_err joycon_open(joyconlib_t* jc, joycon_type type);
/*!
 * @brief   ジョイコンを閉じる
 *
 *  振動を止め，homeledを消灯し，ledを復元する
 * @param[in] jc ジョイコン情報
 * @return  エラーコード
 */
extern joycon_err joycon_close(joyconlib_t* jc);

/*!
 * @brief   ジョイコンの状態（ボタン，スティック，6軸センサー）を取得する
 *
 *  取得した状態はそれぞれ，jc->button，jc->stick，jc->axis に保存されている
 *  詳細はjoyconlib_tを参照のこと
 * @param[in,out] jc ジョイコン情報
 * @return  エラーコード
 */
extern joycon_err joycon_get_state(joyconlib_t* jc);

/*!
 * @brief   ジョイコンを振動する
 *
 *  振動周波数はデフォルト値に固定で強さ(振幅)のみを指定する
 *  内部的に @code joycon_rumble_raw(jc, 96, amp, 64, amp) @endcode を呼び出しているだけである
 * @param[in] jc ジョイコン情報
 * @param[in] amp 強さ(0-100，0でoff)
 * @return  エラーコード
 */
extern joycon_err joycon_rumble(joyconlib_t* jc, int amp);
/*!
 * @brief   ジョイコンを振動する
 *
 *  高/低帯域の周波数と振幅を指定する
 *  指定値と周波数，振幅の関係は @ref rumbletable "別表" の通り
 * @param[in] jc ジョイコン情報
 * @param[in] hfreq 高帯域周波数(33-159)
 * @param[in] hamp 高帯域振幅(0-100)
 * @param[in] lfreq 低帯域周波数(1-127)
 * @param[in] lamp 低帯域振幅(0-100)
 * @return  エラーコード
 */
extern joycon_err joycon_rumble_raw(joyconlib_t* jc, int hfreq, int hamp, int lfreq, int lamp);

/*!
 * @brief   ジョイコンの特定ボタンの経過時間を取得する
 *
 *  ボタンが押されてからの経過時間を10ms単位で取得する
 *  最大値は65535(*10ms)で，それ以上は計測されない
 *  取得できるボタンは L,R,ZL,ZR,SL,SR,Home で，
 *  押すと0になる
 * @param[in] jc ジョイコン情報
 * @param[out] etime 経過時間情報
 * @return  エラーコード
 */
extern joycon_err joycon_get_button_elapsed(joyconlib_t* jc, joycon_elapsed* etime);
/*!
 * @brief   ジョイコンのLEDを設定する
 *
 *  4つのLEDに対して，点灯か点滅を指定できる
 *  マクロが用意されており，|で結合して指定する
 *  点灯が優先される
 * @param[in] jc ジョイコン情報
 * @param[in] led LED情報
 * @return  エラーコード
 */
extern joycon_err joycon_set_led(joyconlib_t* jc, u8 led);
/*!
 * @brief   ジョイコンhomeボタンのLEDを設定する
 *
 *  点灯/点滅に対する細かい指定ができる
 *  詳細はjoycon_homeledを参照のこと
 *  単純な点灯/点滅を指定するためのマクロが用意されている
 * @param[in] jc ジョイコン情報
 * @param[in] data LED情報
 * @return  エラーコード
 */
extern joycon_err joycon_set_homeled(joyconlib_t* jc, joycon_homeled* data);

/*!
 * @brief   ジョイコン振動による演奏
 *
 *  簡易MML演奏データを読みと取り，音階に対応する振動周波数の振動により演奏する
 *  指定できる振動周波数が音階と正確にに一致しないため，多少音程はずれる
 *
 *  演奏が終了するまで関数も終了しない
 *  ただしコールバック関数による終了は指示できる @n
 *  コールバック関数は int callback(void* data) で作成し，
 *  戻り値0で演奏終了，0以外で継続するようにする
 *
 *  MMLに指定できる文字は，CDEFGAB,R,L,O,<,>,T,V，小文字も使える（意味は同じ） @n
 *  音階はド〜シ(CDEFGAB)，シャープ(#,+)，フラット(-)，休符(R) @n
 *  音符は全音符〜64分音符(1,2,4,8,16,32,64)で音階の後に付ける
 *  省略するとLで指定した値を用いる，初期値は4，付点(.)は32分音符まで @n
 *  オクターブ(O)は1-6だが実用的な範囲は3-5，初期値は4，
 *  <で1オクターブ上げ，>で1オクターブ下げる @n
 *  テンポ(T)は30-240，初期値は120
 *  音量(V)は0-100，初期値は50 @n
 *  MML(Music Macro Language)の詳細はWeb検索で
 * @param[in] jc ジョイコン情報
 * @param[in] mml 簡易MMLによる演奏データ
 * @param[in] sz mmlのサイズ
 * @param[in] callback コールバック関数，NULLの場合は呼び出されない
 * @param[in] data コールバック関数に渡す引数
 * @return  エラーコード
 */
extern joycon_err joycon_play_rumble(joyconlib_t* jc, char* mml, size_t sz, int (*callback)(void*), void* data);

/*!
 * @brief   ジョイコンのIRカメラの準備
 *
 *  IRカメラを使用するための設定を行う
 * @param[in] jc ジョイコン情報
 * @param[in] resolution 解像度
 *  詳細はjoycon_ir_resolutionを参照
 * @param[in] exposure 露出時間（シャッター速度）
 *  0 - 600 (us,@f$0 - 1/1666.66s@f$)で指定する
 * @return  エラーコード
 */
extern joycon_err joycon_enable_ir(joyconlib_t* jc, joycon_ir_resolution resolution, u16 exposure);
/*!
 * @brief   ジョイコンのIRカメラの終了
 *
 *  IRカメラの使用を終了し，通常に戻す
 * @param[in] jc ジョイコン情報
 * @return  エラーコード
 */
extern joycon_err joycon_disable_ir(joyconlib_t* jc);
/*!
 * @brief   ジョイコンでIR画像を読み取る
 *
 *  ジョイコン(右)の下部がIRカメラになっており，
 *  対象に向けて実行することで画像を取得する
 *  画像の読み取りには時間がかかるので注意
 *  （最大解像度で4s程度，最小で0.1s程度）
 * @param[in] jc ジョイコン情報
 * @param[out] image 画像データ保存先
 *  保存に必要なサイズはjc->ir_max_frag_no*300である
 * @param[in] size imageのサイズ
 * @param[in] exposure 露出時間(0-600), 0で指定しない（前回と同じ）
 * @param[out] result 読み取った画像情報の保存先, 必要ない場合はNULLを指定する
 * @return  エラーコード
 */
extern joycon_err joycon_read_ir(joyconlib_t* jc, u8* image, size_t size, u16 exposure, joycon_ir_result* result);

/*!
 * @brief   ジョイコンでNFCタグ情報を読み取る
 *
 *  ジョイコン(右)のスティックがNFCリーダーになっており，
 *  スティックにNFCカード等をかざして実行すると読み取る
 *  タグの読み取りに対応しているのは，NTAG213,NTAG215,NTAG216
 *  その他はUIDの読み取りのみ
 * @param[in] jc ジョイコン情報
 * @param[out] nfc NFC情報
 * @return  エラーコード
 */
extern joycon_err joycon_read_nfc(joyconlib_t* jc, joycon_nfc_data* nfc);

#ifdef __cplusplus
}
#endif
/*
MIT License

Copyright (c) 2022 K. Morita

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
