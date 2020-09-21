#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Solis
{
using Matrix2 = glm::mat2;
using Matrix3 = glm::mat3;
using Matrix4 = glm::mat4;

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;

using Vec2i = glm::ivec2;
using Vec3i = glm::ivec3;
using Vec4i = glm::ivec4;

using Quaternion = glm::quat;

    
struct Transform
{
    Vec3 position;
    Quaternion rotation;
    Vec3 scale;

    void SetPosition(const Vec3& _position) { position = _position; }
    void SetRoatation(const Quaternion& _rotation) { rotation = _rotation; }
    void SetScale(const Vec3& _scale) { scale = _scale; }

    void Move(const Vec3& _position) { position += _position; }
    void Roatate(const Quaternion& _rotation) { rotation *= _rotation; }
    void Scale(const Vec3& _scale) { scale += _scale; }

    Vec3& GetPosition() { return position; }
    const Vec3& GetPosition() const { return position; }

    Quaternion& GetRoatation() { return rotation; }
    const Quaternion& GetRoatation() const { return rotation; }

    Vec3& GetScale() { return scale; }
    const Vec3& GetScale() const { return scale; }
};

};
