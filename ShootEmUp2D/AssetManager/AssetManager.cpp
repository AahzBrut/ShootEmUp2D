#include "AssetManager/AssetManager.h"
#include <raylib.h>

#include <memory>
#include <ranges>

#include "Logger.h"

AssetManager::AssetManager() {
    LOG("AssetManager created.");
}

AssetManager::~AssetManager() {
    Clear();
    LOG("AssetManager destroyed.");
}

void AssetManager::Clear() {
    for (const auto &value: std::views::values(textures)) {
        UnloadTexture(*value);
    }
    for (const auto &value: std::views::values(soundEffects)) {
        UnloadSound(*value);
    }
    for (const auto &value: std::views::values(musicTrucks)) {
        UnloadMusicStream(*value);
    }
    for (const auto &value: std::views::values(fonts)) {
        UnloadFont(*value);
    }
    textures.clear();
    soundEffects.clear();
    musicTrucks.clear();
    fonts.clear();
}

void AssetManager::ClearUnused() {
    for (auto iterator = textures.begin(); iterator != textures.end();) {
        if (iterator->second.unique()) {
            UnloadTexture(*iterator->second);
            iterator = textures.erase(iterator);
        } else {
            ++iterator;
        }
    }

    for (auto iterator = soundEffects.begin(); iterator != soundEffects.end();) {
        if (iterator->second.unique()) {
            UnloadSound(*iterator->second);
            iterator = soundEffects.erase(iterator);
        } else {
            ++iterator;
        }
    }

    for (auto iterator = musicTrucks.begin(); iterator != musicTrucks.end();) {
        if (iterator->second.unique()) {
            UnloadMusicStream(*iterator->second);
            iterator = musicTrucks.erase(iterator);
        } else {
            ++iterator;
        }
    }

    for (auto iterator = fonts.begin(); iterator != fonts.end();) {
        if (iterator->second.unique()) {
            UnloadFont(*iterator->second);
            iterator = fonts.erase(iterator);
        } else {
            ++iterator;
        }
    }
}

void AssetManager::LoadTexture(const String &assetId, const String &path) {
    const auto asset = std::make_shared<Texture2D>(::LoadTexture(path.c_str()));
    textures[assetId] = asset;
    LOG("Texture loaded: '{}' from '{}'", assetId, path);
}

void AssetManager::LoadSound(const String &assetId, const String &path) {
    const auto asset = std::make_shared<Sound>(::LoadSound(path.c_str()));
    soundEffects[assetId] = asset;
}

void AssetManager::LoadMusic(const String &assetId, const String &path) {
    const auto asset = std::make_shared<Music>(LoadMusicStream(path.c_str()));
    musicTrucks[assetId] = asset;
}

void AssetManager::LoadFont(const String &assetId, const String &path) {
    const auto asset = std::make_shared<Font>(::LoadFont(path.c_str()));
    fonts[assetId] = asset;
}
