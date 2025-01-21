#pragma once
#include "Logger.h"
#include "raylib.h"
#include "TypeDefs.h"


class AssetManager {
    using String = std::string;

    Dictionary<String, Shared<Texture2D> > textures;
    Dictionary<String, Shared<Sound> > soundEffects;
    Dictionary<String, Shared<Music> > musicTrucks;
    Dictionary<String, Shared<Font> > fonts;

public:
    AssetManager();
    ~AssetManager();

    void Clear();
    void ClearUnused();

    void LoadTexture(const String &assetId, const String &path);
    void LoadSound(const String &assetId, const String &path);
    void LoadMusic(const String &assetId, const String &path);
    void LoadFont(const String &assetId, const String &path);

    Shared<Texture2D> GetTexture(const String &assetId) { return textures[assetId]; }
    Shared<Sound> GetSoundEffect(const String &assetId) { return soundEffects[assetId]; }
    Shared<Music> GetMusic(const String &assetId) { return musicTrucks[assetId]; }
    Shared<Font> GetFont(const String &assetId) { return fonts[assetId]; }
};
