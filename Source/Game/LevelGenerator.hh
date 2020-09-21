#pragma once
#include <vector>
#include <cstdint>

namespace LevelGenerator {

    std::vector<float> FromVec(const std::vector<uint8_t>& level, uint32_t width, uint32_t height);

};