#include "sound_system.h"
#include <iostream>

/*##################################################*/
/*class AudioClip*/
/*##################################################*/

/*##################################################*/
/*class AudioSource*/
/*##################################################*/

/*##################################################*/
/*class AudioListener*/
/*##################################################*/

/*##################################################*/
/*class SoundSystem*/
/*##################################################*/

// シングルトンインスタンスを取得する静的メソッド
SoundSystem& SoundSystem::GetInstance()
{
    static SoundSystem instance; // ローカル静的変数でインスタンスを保持
    return instance;
}

bool SoundSystem::InitSystem()
{
    FMOD_RESULT result;
    // FMODシステムの初期化
    result = FMOD::System_Create(&mSystem);
    if (result != FMOD_OK) {
        std::cerr << "FMOD system creation failed!" << std::endl;
        return false;
    }

    result = mSystem->init(256, FMOD_INIT_NORMAL, 0);
    if (result != FMOD_OK) {
        std::cerr << "FMOD system initialization failed!" << std::endl;
        return false;
    }
    return true;
}

SoundSystem::SoundSystem()
    : mSystem(nullptr)
{
}
bool SoundSystem::InitSystem()
{
    // FMODシステムの初期化
    FMOD_RESULT result;
    result = FMOD::System_Create(&mSystem);
    if (result != FMOD_OK) {
        std::cerr << "FMOD system creation failed!" << std::endl;
        return false;
    }
    return true;
}