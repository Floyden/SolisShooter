#include "LevelGenerator.hh"
#include "../Math.hh"

using namespace Solis;

namespace LevelGenerator {

std::vector<float> FromVec(const std::vector<uint8_t>& level, uint32_t width, uint32_t height)
{
    std::vector<float> result;

    for (size_t i = 0; i < level.size(); i++)
    {
        if(level[i] == 0)
            continue;
        
        int xPos = i % width;
        int yPos = i % height;

        // Quad
        std::vector<float> temp = {
            // Position                     /**/ uvs         /**/ normals
            0.0f + xPos, 0.0f + yPos, 0.0f, /**/ 0.0f, 0.0f, /**/ 0.0f, 0.0f, 1.0f,
            1.0f + xPos, 0.0f + yPos, 0.0f, /**/ 1.0f, 0.0f, /**/ 0.0f, 0.0f, 1.0f,
            0.0f + xPos, 1.0f + yPos, 0.0f, /**/ 0.0f, 1.0f, /**/ 0.0f, 0.0f, 1.0f,
            1.0f + xPos, 1.0f + yPos, 0.0f, /**/ 1.0f, 1.0f, /**/ 0.0f, 0.0f, 1.0f,
        };

        result.reserve(temp.size());

        std::copy(temp.begin(), temp.end(), result.end());
    }

    return result;
}

}