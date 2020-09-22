#pragma once
#include <cstdint>
#include <vector>
#include "Math.hh"

namespace Solis
{

static const std::vector<float> gTriangleData = {
    -1.0f, -1.0f,
    1.0f, -1.0f,
    0.0f,  1.0f,
};

static const std::vector<float> gTriangleData2 = {
    -1.0f, 1.0f,
    0.0f,  -1.0f,
    1.0f, 1.0f,
};

static const std::vector<uint32_t> gTriangleIdx = {
    1, 0, 2
};

static const std::vector<float> gQuadData = {
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
};

static const std::vector<float> gQuadUV = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f, 
};

static const std::vector<float> gQuadColor = {
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};

static const std::vector<uint32_t> gQuadDataIdx = {
    0, 1, 2,
    0, 2, 3 
};

static const std::vector<float> gCubeData = {
    0.0f, 0.0f, 0.0f, 
    1.0f, 0.0f, 0.0f, 
    0.0f, 1.0f, 0.0f, 
    1.0f, 1.0f, 0.0f, 
    0.0f, 0.0f, 1.0f, 
    1.0f, 0.0f, 1.0f, 
    0.0f, 1.0f, 1.0f, 
    1.0f, 1.0f, 1.0f, 

};

static const std::vector<uint32_t> gCubeDataIdx = {
    0, 1, 2, 
    0, 1, 2, 
    0, 1, 2, 
    0, 1, 2, 
    0, 1, 2, 
    0, 1, 2,
    0, 1, 2, 
    0, 1, 2, 
    0, 1, 2, 
    0, 1, 2, 
    0, 1, 2, 
    0, 1, 2, 
};

static const Vec3 gBlack(0.0f);
static const Vec3 gWhite(1.0f);
static const Vec3 gBrown(0.48f, 0.24f, 0.0f);
static const Vec3 gBeige(0.996f, 0.988f, 0.813f);

static std::vector<uint8_t> gLevel = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 0, 1, 1, 0,
    0, 0, 0, 1, 0, 0, 1, 0,
    0, 0, 0, 1, 1, 1, 1, 0,
    0, 0, 1, 1, 0, 1, 0, 0,
    0, 1, 1, 0, 0, 1, 1, 0,
    0, 0, 1, 1, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

static const char* gVertexShaderSource =
    "#version 330 core\n" 
    "uniform mat4 uMVP;\n"
    "uniform vec3 uPos;\n"
    "layout(location = 0) in vec3 inPos;\n" 
    "layout(location = 1) in vec2 inUV;\n" 
    "out vec2 uvs;\n"
    "void main() {\n"
    "   gl_Position = uMVP * vec4(inPos + uPos, 1.0);\n" 
    "   uvs = inUV;\n"
    "}";

static const char* gFragmentShaderSource =
    "#version 330 core\n" 
    "uniform sampler2D uSampler;"
    "in vec2 uvs;"
    "out vec3 color;" 
    "void main() {"
    "   vec4 tex = texture(uSampler, uvs);"
    "   color = tex.rgb;"
    "}";
    
} // namespace Solis