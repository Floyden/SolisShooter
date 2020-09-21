#pragma once
#include "Math.hh"

using namespace Solis::Math;

class ICollider {
public:
    virtual Vector3 GetPosition() const = 0;
    virtual void SetPosition(const Vector3& pos) = 0; 

    virtual Quaternion GetRotation() const = 0;
    virtual void SetRotation(const Quaternion& quat) = 0;

    virtual void SetMass(float mass) = 0;
    virtual float GetMass() const = 0;
protected:

};