#pragma once
#include "../Math.hh"

namespace Solis
{

class Camera 
{
public:
    Camera(float pFov, float pAspect, float pNear, float pFar) :
        mRotation(1.0, 0.0, 0.0, 0.0)
    {
        mProjection = glm::perspective(pFov, pAspect, pNear, pFar);
    }

    const Vec3& GetPosition() const 
    {
        return mPosition;
    }

    Vec3& GetPosition()
    {
        return mPosition;
    }

    void SetPosition(const Vec3& pos) 
    {
        mPosition = pos;
    }

    const Quaternion& GetRotation() const 
    {
        return mRotation;
    }

    Quaternion& GetRotation()
    {
        return mRotation;
    }

    void SetRotation(const Quaternion& rot) 
    {
        mRotation = rot;
    }

    Matrix4 GetView() const 
    {
        return glm::lookAt(
            mPosition,
            mPosition + mRotation * Vec3(0,0,1),
            Vec3(0,1,0));
    }

    Matrix4 GetProjection() const 
    {
        return mProjection;
    }

private:
    bool mDirty;
    Vec3 mPosition;
    Quaternion mRotation;
    Matrix4 mProjection;

};

} // namespace Solis