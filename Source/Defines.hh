#pragma once
#include <memory>
#include <vector>
#include <string>

#include <unordered_set>
#include <unordered_map>

template<typename T>
using Vector = std::vector<T>;

template<typename T>
using SPtr = std::shared_ptr<T>;

template<typename T>
using UPtr = std::unique_ptr<T>;

template<typename T, typename H = std::hash<T>, typename E = std::equal_to<T>>
using UnorderedSet = std::unordered_set<T, H, E>;

template<typename K, typename V, typename H = std::hash<K>, typename E = std::equal_to<K>>
using UnorderedMap = std::unordered_map<K, V, H, E>;

using String = std::string;