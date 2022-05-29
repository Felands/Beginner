#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <string>
#include <unordered_map>

#include "SDL_mixer.h"

enum class SoundType
{
    SOUND_MUSIC,
    SOUND_SFX
};

class SoundManager
{
public:
    static SoundManager* Instance()
    {
        if(instance == nullptr) {
            instance = new SoundManager();
        }
        return instance;
    }

    bool Load(std::string fileName, std::string id, SoundType type);

    void PlaySound(std::string id, int loop);

    void PlayMusic(std::string id, int loop);

private:
    SoundManager();
    ~SoundManager();
    SoundManager(const SoundManager&);
    SoundManager &operator=(const SoundManager&);

    static SoundManager* instance;
    std::unordered_map<std::string, Mix_Chunk*> sfxs;
    std::unordered_map<std::string, Mix_Music*> musics;
};

#endif
