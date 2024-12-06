#include <FMOD/fmod.hpp>
#include <FMOD/fmod_errors.h>
#include <iostream>
int main()
{
    FMOD::System* system   = nullptr;
    FMOD::Sound* sound     = nullptr;
    FMOD::Channel* channel = nullptr;
    FMOD_RESULT result;

    // FMODシステムの初期化
    result = FMOD::System_Create(&system);
    if (result != FMOD_OK) {
        std::cerr << "FMOD system creation failed!" << std::endl;
        return -1;
    }

    result = system->init(512, FMOD_INIT_NORMAL, 0);
    if (result != FMOD_OK) {
        std::cerr << "FMOD system initialization failed!" << std::endl;
        return -1;
    }

    // サウンドファイルの読み込み
    result = system->createSound("Tropical_Waves.mp3", FMOD_DEFAULT, 0, &sound);
    if (result != FMOD_OK) {
        std::cerr << "Failed to load sound!" << std::endl;
        return -1;
    }

    // サウンドの再生
    result = system->playSound(sound, nullptr, false, &channel);
    if (result != FMOD_OK) {
        std::cerr << "Failed to play sound!" << std::endl;
        return -1;
    }

    // サウンドが再生されている間ループ
    std::cout << "Press Enter to stop..." << std::endl;
    std::cin.get(); // ユーザーの入力を待つ

    // クリーンアップ
    sound->release();
    system->close();
    system->release();

    return 0;
}
