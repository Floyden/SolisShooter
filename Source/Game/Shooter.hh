#pragma once
#include "Game.hh"
#include "Scene/SceneNode.hh"
#include "Scene/Camera.hh"
#include "Render/Mesh.hh"
#include "Event.hh"
#include "Math.hh"
#include "Input/InputEvent.hh"
#include <array>

namespace Solis
{
    
struct InputEvent;
struct RenderComponent;

class Shooter : public Game {
public:
    Shooter();
    ~Shooter();

    void Init() override;
    void Update(float delta) override;
    void Render() override;
    void RunMainLoop() override;

    void OnKeyEvent(InputKeyEvent*);
    void OnMouseMove(InputMouseMovementEvent*);
    void OnWindowEvent(WindowEvent*);

private:
    void UpdateInput(float delta);

    std::vector<RenderComponent*> mRenderComponents;
    int mSelectedTile;
    
    // Render Resources
    SPtr<Renderer> mRender;
    
    SPtr<Program> mProgram;
    SPtr<Texture> mTexture;
    std::vector<SPtr<Mesh>> mMeshes;

    SPtr<Camera> mCamera;
    SharedNode mRoot;
};

} // namespace Solis