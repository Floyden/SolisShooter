#pragma once
#include "Component.hh"
#include "Math.hh"
#include <vector>

namespace Solis
{

class Node {
public:

    static SPtr<Node> Create(const String& name) 
    {
        auto res = SPtr<Node>(new Node());
        res->mEntity = Entity::Create(name);
        return res;
    }

    const String& GetName() const 
    {
        return mEntity->GetName();
    }

    void AddChild(Node* child) 
    {
        mChildren.push_back(child);
        child->SetParent(this);
    }

private:
    explicit Node() : mParent(nullptr), mEntity(nullptr) {};

    void SetParent(Node* parent) { mParent = parent; }

    Node* mParent;
    Vector<Node*> mChildren;
    Transform mTransform;

    // Wraps around entity, 
    SharedEntity mEntity;
};

} // namespace Solis