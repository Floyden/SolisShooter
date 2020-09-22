#include "AssimpImporter.hh"
#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <assimp/postprocess.h> 
#include <assimp/DefaultLogger.hpp> 

namespace Solis
{
using namespace Assimp;

AssimpImporter::AssimpImporter()
{
    DefaultLogger::create("", Logger::VERBOSE);
}

AssimpImporter::~AssimpImporter()
{
    DefaultLogger::kill();
}

SPtr<Node> AssimpImporter::ImportScene(const String& path)
{
    Importer importer;
    const aiScene* scene = importer.ReadFile(path, 
        aiProcess_CalcTangentSpace);

}

} //namespace Solis
