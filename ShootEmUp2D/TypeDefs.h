#pragma once
#include <memory>
#include <unordered_map>

template<typename T>
using Unique = std::unique_ptr<T>;

template<typename T>
using Shared = std::shared_ptr<T>;

template<typename T>
using Weak = std::weak_ptr<T>;

template<typename Key, typename Value, typename Hasher = std::hash<Key>>
using Dictionary = std::unordered_map<Key, Value, Hasher>;
