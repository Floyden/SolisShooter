#pragma once
#include "../Module.hh"
#include <bullet/btBulletDynamicsCommon.h>

class PhysicsScene;

class Physics : public IModule {
public:
    virtual ~Physics() {}

    virtual void Init() override;
    virtual void Shutdown() override {};
    virtual void Update() override {};

    //SPtr<RigidBody> CreateBoxCollider();

    void Test();
private:
    UPtr<btCollisionConfiguration> mCollisionConfig;
    UPtr<btCollisionDispatcher> mDispatcher;
    UPtr<btBroadphaseInterface> mBroadPhase;
    UPtr<btConstraintSolver> mSolver;

    UPtr<btDiscreteDynamicsWorld> mDynamicsWorld;
};

