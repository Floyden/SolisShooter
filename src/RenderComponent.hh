#pragma once
#include "Component.hh"
#include "Render/Mesh.hh"

class Material {

};

class Renderable {
public:
    void SetMesh(Mesh* mesh);
    Mesh* GetMesh() const;
    void SetMaterial(Material*);
    Material* GetMaterial() const;
};

class RenderComponent : public IComponent {
public:
    void SetRenderable(Renderable* );
    Renderable* GetRenderable();

private:
    SPtr<Renderable> mInner;
};