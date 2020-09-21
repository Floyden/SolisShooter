#pragma once
#include "Component.hh"

class SceneNode {

private:
    SPtr<Entity> mEntity;

    SceneNode* mParent;
    UnorderedSet<SceneNode*> mChildren;
};

class Scene {

private:

};