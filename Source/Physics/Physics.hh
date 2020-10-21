#pragma once
#include "../Module.hh"
//#include "RigidBody.hh"
#include <bullet/btBulletDynamicsCommon.h>


namespace Solis
{

class Physics : public IModule {
public:
    virtual ~Physics() {}

    virtual void Init() override;
    virtual void Shutdown() override {};
    virtual void Update() override {};

    //SPtr<RigidBody> CreateRigidBody();

    void Test();

    btDiscreteDynamicsWorld* GetDynamicsWorld() { return mDynamicsWorld.get(); }
private:
    UPtr<btCollisionConfiguration> mCollisionConfig;
    UPtr<btCollisionDispatcher> mDispatcher;
    UPtr<btBroadphaseInterface> mBroadPhase;
    UPtr<btConstraintSolver> mSolver;

    UPtr<btDiscreteDynamicsWorld> mDynamicsWorld;
};

} // namespace Solis


