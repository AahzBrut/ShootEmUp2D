#include "AudioManager.h"

#include "Logger.h"


void AudioManager::PlaySoundEffect(const Shared<Sound> &sound) {
    sounds.emplace_back(sound, LoadSoundAlias(*sound));
    PlaySound(sounds.back().second);
}

void AudioManager::Update() {
    for (auto iterator = sounds.begin(); iterator != sounds.end();) {
        if (!IsSoundPlaying(iterator->second)) {
            UnloadSoundAlias(iterator->second);
            iterator = sounds.erase(iterator);
        } else {
            ++iterator;
        }
    }
}
