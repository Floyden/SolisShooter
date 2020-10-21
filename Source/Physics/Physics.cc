#include "Physics.hh"
#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <iostream>

namespace Solis
{

void Physics::Init()
{
    mCollisionConfig = std::make_unique<btDefaultCollisionConfiguration>();
    mDispatcher = std::make_unique<btCollisionDispatcher>(mCollisionConfig.get());

    mBroadPhase = std::make_unique<btDbvtBroadphase>();
    
    mSolver = std::make_unique<btSequentialImpulseConstraintSolver>();

    mDynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(mDispatcher.get(), mBroadPhase.get(), mSolver.get(), mCollisionConfig.get());
}
/*
SPtr<RigidBody> Physics::CreateRigidBody()
{
    SPtr<RigidBody> res = std::make_shared<RigidBody>();
    return res;
}*/

void Physics::Test()
{

    btBoxShape boxShape(btVector3(0.5f, 0.5f, 0.5f));
    btCollisionObject boxObject;
    boxObject.setCollisionShape(&boxShape);
    boxObject.getWorldTransform().setOrigin(btVector3(0.0f, 0.0f, 0.0f));

    btRigidBody boxBody(0.0, nullptr, nullptr);
    boxBody.setCollisionShape(&boxShape);

    //mDynamicsWorld->addCollisionObject(&boxObject);
    mDynamicsWorld->addRigidBody(&boxBody);

    btVector3 from(1.0f, 0.0f, 0.0f);
    btVector3 to(-1.0f, 0.0f, 0.0f);
    btCollisionWorld::ClosestRayResultCallback result1(from, to);
    mDynamicsWorld->rayTest(from, to, result1);

    to.setX(2.0f);
    btCollisionWorld::ClosestRayResultCallback result2(from, to);
    mDynamicsWorld->rayTest(from, to, result2);

    if(result1.hasHit() && !result2.hasHit())
    {
        std::cout << "ayy it works" << std::endl;
    }

    mDynamicsWorld->removeCollisionObject(&boxObject);
}   

} // namespace Solis