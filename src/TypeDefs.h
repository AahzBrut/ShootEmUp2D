#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

template<typename T>
using Unique = std::unique_ptr<T>;

template<typename T>
using Shared = std::shared_ptr<T>;

template<typename T>
using Weak = std::weak_ptr<T>;

template<typename K, typename V>
using Pair = std::pair<K, V>;

template<typename T>
using List = std::vector<T>;

template<typename Key, typename Value, typename Hasher = std::hash<Key>>
using Dictionary = std::unordered_map<Key, Value, Hasher>;
