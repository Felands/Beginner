#include "SoundManager.h"
#include "log.h"

SoundManager *SoundManager::instance = nullptr;

SoundManager::SoundManager()
{
    Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

bool SoundManager::Load(std::string fileName, std::string id, SoundType type)
{
    if (type == SoundType::SOUND_MUSIC) {
        Mix_Music* music = Mix_LoadMUS(fileName.c_str());
        if(music == nullptr) {
            LOG_ERR("Could not load music: ERROR - ", Mix_GetError());
            return false;
        }
        musics[id] = music;
        return true;
    } else if (type == SoundType::SOUND_SFX) {
        Mix_Chunk* chunk = Mix_LoadWAV(fileName.c_str());
        if(chunk == 0) {
            LOG_ERR("Could not load SFX: ERROR - ", Mix_GetError());
            return false;
        }
        sfxs[id] = chunk;
        return true;
    }
    return false;
}

void SoundManager::PlayMusic(std::string id, int loop)
{
    Mix_PlayMusic(musics[id], loop);
}

void SoundManager::PlaySound(std::string id, int loop)
{
    Mix_PlayChannel(-1, sfxs[id], loop);
}

SoundManager::~SoundManager()
{
    Mix_CloseAudio();
}
