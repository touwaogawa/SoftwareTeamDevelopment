#include <FMOD/fmod.hpp>
#include <FMOD/fmod_errors.h>
#include <SDL2/SDL.h> // SDL2のヘッダーを追加
#include <iostream>

FMOD::System* fmod_system = nullptr;
FMOD::Sound* sound        = nullptr;
FMOD::Channel* channel    = nullptr;

FMOD_VECTOR listenerPosition = { 0.0f, 0.0f, 0.0f }; // リスナーの位置
FMOD_VECTOR soundPosition    = { 0.0f, 0.0f, 0.0f }; // 音源の初期位置
FMOD_VECTOR listenerVelocity = { 0.0f, 0.0f, 0.0f }; // リスナーの速度
FMOD_VECTOR soundVelocity    = { 0.0f, 0.0f, 0.0f }; // 音源の速度（音源が前進中）

FMOD::Reverb3D* reverb     = nullptr;
FMOD_VECTOR reverbPosition = { 0.0f, 0.0f, 0.0f }; // リバーブゾーンの位置
float minDistance          = 5.0f;
float maxDistance          = 20.0f;

void checkFMODResult(FMOD_RESULT result)
{
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
    }
}

int main()
{
    // FMODシステムの初期化
    FMOD_RESULT result = FMOD::System_Create(&fmod_system);
    checkFMODResult(result);
    result = fmod_system->init(512, FMOD_INIT_NORMAL, nullptr);
    checkFMODResult(result);

    // サウンドの作成（3Dサウンド）
    result = fmod_system->createSound("Tropical_Waves.mp3", FMOD_3D, nullptr, &sound);
    checkFMODResult(result);

    // リスナーの位置と速度を設定
    result = fmod_system->set3DListenerAttributes(0, &listenerPosition, &listenerVelocity, nullptr, nullptr);
    checkFMODResult(result);

    // サウンドを再生
    result = fmod_system->playSound(sound, nullptr, false, &channel);
    checkFMODResult(result);

    // リバーブゾーンの作成
    result = fmod_system->createReverb3D(&reverb);
    checkFMODResult(result);

    result = reverb->set3DAttributes(&reverbPosition, minDistance, maxDistance);
    checkFMODResult(result);

    FMOD_REVERB_PROPERTIES reverbProps = FMOD_PRESET_GENERIC;
    result                             = reverb->setProperties(&reverbProps);
    checkFMODResult(result);

    // サウンドの初期位置を設定
    result = channel->set3DAttributes(&soundPosition, &soundVelocity);
    checkFMODResult(result);

    // メインループ
    float time = 0.0f;
    while (time < 100.0f) {
        // 音源が進んでいく（移動する）
        soundPosition.z    = 0.0f; // 音源がリスナーに向かって移動
        listenerVelocity.x = 0.0f; // リスナーが動く速度（例えば、前進）
        reverbProps.WetLevel -= 1;
        reverbProps.DecayTime += 10;
        reverbProps.Density -= 2.0f;

        // 位置と速度を更新
        result = fmod_system->set3DListenerAttributes(0, &listenerPosition, &listenerVelocity, nullptr, nullptr);
        checkFMODResult(result);
        result = channel->set3DAttributes(&soundPosition, &soundVelocity);
        checkFMODResult(result);

        // FMODシステムを更新
        result = fmod_system->update();
        checkFMODResult(result);

        // 進行状況を更新
        time += 0.1f;

        // 100ミリ秒ごとにループを一時停止（SDL_Delay相当）
        SDL_Delay(100);
    }

    // システムを終了
    fmod_system->release();

    return 0;
}
