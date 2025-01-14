#pragma once
#include "../../common/src/component.h"
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_errors.h>

class AudioClip {
public:
    AudioClip(const char* file);
    FMOD::Sound* sound;

private:
};

class AudioSource : public Component {
public:
private:
};

class AudioListener : public Component {
public:
private:
};

// シングルトンパターンクラス
class SoundSystem {
public:
    static SoundSystem& GetInstance()
    {
        static SoundSystem instance; // ローカル静的変数でインスタンスを保持
        return instance;
    }

    // プログラムの最初で呼ぶ初期化関数
    bool InitSystem();

    // mSystemのgetter
    FMOD::System* GetSystem() const;

private:
    // コンストラクタをプライベートにすることで外部でインスタンス化できないように
    SoundSystem();
    FMOD::System* mSystem;

    // コピーコンストラクタと代入演算子を削除して、インスタンスの複製を防ぐ
    SoundSystem(const SoundSystem&)            = delete;
    SoundSystem& operator=(const SoundSystem&) = delete;
};