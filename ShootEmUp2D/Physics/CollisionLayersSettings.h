#pragma once

#pragma once
#include <bitset>

enum class CollisionLayer {
    None,
    Player,
    PlayerBullet,
    Enemy,
    EnemyBullet,
    LastLayer,
};

inline CollisionLayer CollisionLayerFromString(const std::string& str) {
    if (str == "None") { return CollisionLayer::None; }
    if (str == "Player") { return CollisionLayer::Player; }
    if (str == "PlayerBullet") { return CollisionLayer::PlayerBullet; }
    if (str == "Enemy") { return CollisionLayer::Enemy; }
    if (str == "EnemyBullet") { return CollisionLayer::EnemyBullet; }
    return CollisionLayer::None;
}

constexpr auto LayersCount = static_cast<int>(CollisionLayer::LastLayer);

class CollisionLayersSettings {
    static std::bitset<LayersCount> layers[LayersCount];
    static bool initialized;

    static void SetLayersCollides(CollisionLayer firstLayer, CollisionLayer secondLayer) {
        layers[static_cast<int>(firstLayer)].set(static_cast<int>(secondLayer));
        layers[static_cast<int>(secondLayer)].set(static_cast<int>(firstLayer));
    }

    static void Init() {
        SetLayersCollides(CollisionLayer::Player, CollisionLayer::EnemyBullet);
        SetLayersCollides(CollisionLayer::Enemy, CollisionLayer::PlayerBullet);
        SetLayersCollides(CollisionLayer::Player, CollisionLayer::Enemy);
    }

public:
    CollisionLayersSettings() = delete;
    ~CollisionLayersSettings() = delete;

    static bool IsLayersCollides(CollisionLayer firstLayer, CollisionLayer secondLayer) {
        if (!initialized) {
            Init();
            initialized = true;
        }
        return layers[static_cast<int>(firstLayer)].test(static_cast<int>(secondLayer));
    }
};
