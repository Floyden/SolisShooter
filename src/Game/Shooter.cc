#include "Shooter.hh"
#include "RandomThings.hh"
#include "Image.hh"
#include "Input/Input.hh"

namespace Solis
{

struct TransformComponent : public IComponent {
    Vec2 pos;
};

struct RenderComponent : public IComponent {
};

Shooter::Shooter()
{
}

Shooter::~Shooter()
{

}

void Shooter::Init()
{
    mWindow = Solis::Window::Create();

    //Init Modules
    mModules = std::make_unique<ModuleManager>();
    mModules->AddModule<ComponentManager>();
    auto events = mModules->AddModule<Events>();
    mModules->AddModule<Input>();
    mModules->Init();
    
    events->Subscribe(this, &Shooter::OnKeyEvent);
    events->Subscribe(this, &Shooter::OnMouseMove);
    events->Subscribe(this, &Shooter::OnWindowEvent);


    // Init Shooter
    mRoot = Node::Create("Root");
    mCamera = std::make_shared<Camera>(1.0f, mWindow->GetAspectRatio(), 0.1f, 100.0f);
    mCamera->SetPosition(Vec3(0.0, 0.0, -1.0));


    // Init Render Stuff
    mRender = std::make_shared<Renderer>();
    auto quadData = VertexBuffer::Create({static_cast<uint32_t>(gQuadData.size()), sizeof(float)});
    quadData->WriteData(0, gQuadData.size() * sizeof(float), gQuadData.data());
    auto quadUV = VertexBuffer::Create({static_cast<uint32_t>(gQuadUV.size()), sizeof(float)});
    quadUV->WriteData(0, gQuadUV.size() * sizeof(float), gQuadUV.data());

    for (size_t i = 0; i < 2; i++)
    {
        mMeshes.emplace_back(std::make_shared<Mesh>());
        mMeshes[i]->mAttributes = VertexAttributes::Create({
            VertexAttribute{0, 3, GL_FLOAT, GL_FALSE, 0},
            VertexAttribute{1, 2, GL_FLOAT, GL_FALSE, 0}});

        mMeshes[i]->mVertexData = std::make_shared<VertexData>();
        mMeshes[i]->mVertexData->SetBuffer(0, quadData);

        mMeshes[i]->mVertexData->SetBuffer(1, quadUV);

        mMeshes[i]->mIndexBuffer = IndexBuffer::Create({static_cast<uint32_t>(gQuadDataIdx.size())});
        mMeshes[i]->mIndexBuffer->WriteData(0, gQuadDataIdx.size() * sizeof(uint32_t), gQuadDataIdx.data());
    }

    mProgram = Program::Create();
    mProgram->LoadFrom(gVertexShaderSource, gFragmentShaderSource);

    auto img = Image::FromFile("resources/Chess.png");
    mTexture = Texture::Create(img);
}

void Shooter::OnMouseMove(InputMouseMovementEvent* event)
{
    // Looking around
    static float MOUSE_SENS = 0.005f;
    auto quatY = glm::normalize(glm::angleAxis(MOUSE_SENS * event->GetRelative().y, Vec3{1, 0, 0}));
    auto quatX = glm::normalize(glm::angleAxis(-MOUSE_SENS * event->GetRelative().x, Vec3{0, 1, 0}));
    auto res = glm::normalize(mCamera->GetRotation() * quatY * quatX);
    mCamera->SetRotation(res);
}

void Shooter::OnWindowEvent(WindowEvent* event)
{/*
    switch (event->type)
    {
    case WindowEventType::Enter:
        SDL_ShowCursor(SDL_FALSE);
        break;
    case WindowEventType::Leave:
        SDL_ShowCursor(SDL_TRUE);
        break;
    default:
        break;
    }*/
}

void Shooter::OnKeyEvent(InputKeyEvent* event)
{
    static bool isToggled = false;
    if(event->GetKeycode() == SDLK_ESCAPE && !event->IsEcho())
    {
        if(isToggled) {
            SDL_ShowCursor(SDL_FALSE);
            SDL_CaptureMouse(SDL_TRUE);
        } else {
            SDL_ShowCursor(SDL_TRUE);
            SDL_CaptureMouse(SDL_FALSE);
        }
    }
}

void Shooter::Update(float delta)
{
    mWindow->ProcessEvents();
    mRunMainLoop = !mWindow->CloseRequested();

    UpdateInput(delta);
}

void Shooter::UpdateInput(float delta)
{
    static const float MOVEMENT_SPEED = 10.f;
    auto input = Input::Get();

    Vec2i movVec(0);
    if(input->IsKeyPressed(SDLK_w))
        movVec.y += 1;
    if(input->IsKeyPressed(SDLK_s))
        movVec.y -= 1;
    if(input->IsKeyPressed(SDLK_a))
        movVec.x += 1;
    if(input->IsKeyPressed(SDLK_d))
        movVec.x -= 1;

    Vec3 dir(0);
    dir += glm::normalize(mCamera->GetRotation() * Vec3(0, 0, 1)) * static_cast<float>(movVec.y);
    dir += glm::normalize(mCamera->GetRotation() * Vec3(1, 0, 0)) * static_cast<float>(movVec.x);
    dir.y = 0;

    mCamera->GetPosition() += dir * delta * MOVEMENT_SPEED;
}

void Shooter::Render()
{
    mRender->Clear(0.f, 0.5f, 1.f, 1.0f);

    mRender->BindProgram(mProgram);
    mRender->BindTexture(mTexture);

    auto mvp = mCamera->GetProjection() * mCamera->GetView();

    for (auto& mesh: mMeshes)
    {
        mRender->BindVertexAttributes(mesh->mAttributes);
        for (auto& attr: mesh->mAttributes->GetAttributes())
        {
            auto loc = attr.location;
            auto buffer = mesh->mVertexData->GetBuffer(loc);
            mRender->BindVertexBuffers(loc, &buffer, 1);
        }

        mRender->BindIndexBuffer(mesh->mIndexBuffer);
        

        static double counter = 0;
       // mProgram->SetUniform3f("uPos", Vec3( cos(counter), 0.0f, 2.0f * (sin(counter) + 1.0f) ));
        mProgram->SetUniform3f("uPos", Vec3( 1.0, 0.0f, 1.0f) );
        if(counter <= 0) 
            counter -= mDelta.count() * 1.0f;
        else 
            counter += mDelta.count() * 1.0f;

        counter *= -1.0f;

        mProgram->SetUniformMat4f("uMVP", mvp);
        mRender->DrawIndexed(gQuadDataIdx.size());
    }

    mWindow->SwapWindow();
}

void Shooter::RunMainLoop()
{
    std::cout << mWindow->GetAspectRatio() << std::endl;
    mRunMainLoop = true;
    mLastFrame = std::chrono::steady_clock::now();

    while (mRunMainLoop) {

        // Update everything
        mNow = std::chrono::steady_clock::now();
        mDelta = mNow - mLastFrame;
        mLastFrame = mNow;
    
        Update(mDelta.count());
        Render();        
    }
}

} // namespace Solis