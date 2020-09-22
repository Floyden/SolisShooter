#pragma once
#include <assimp/scene.h>
#include "Defines.hh"
#include "Scene/Node.hh"

namespace Solis
{

class AssimpImporter
{
public:
    AssimpImporter();
    ~AssimpImporter();

    SPtr<Node> ImportScene(const String& path);
};

} //namespace Solis