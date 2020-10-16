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
        mInvProjection = glm::inverse(mProjection);
        mNear = pNear;
        mFar = pFar;
        mFov = pFov;
        mAspect = pAspect;
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

    Matrix4 GetInvView() const 
    {
        return glm::inverse(GetView());
    }

    Matrix4 GetProjection() const 
    {
        return mProjection;
    }

    Matrix4 GetInvProjection() const 
    {
        return mInvProjection;
    }

    float GetNear() const
    {
        return mNear;
    }

    float GetFar() const
    {
        return mFar;
    }

    float GetFov() const
    {
        return mFov;
    }

    float GetAspectRatio() const
    {
        return mAspect;
    }

private:
    bool mDirty;
    Vec3 mPosition;
    Quaternion mRotation;
    Matrix4 mProjection;

    Matrix4 mInvProjection;

    float mNear;
    float mFar;
    float mFov;
    float mAspect;

};

} // namespace Solis