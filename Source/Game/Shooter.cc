#include "Shooter.hh"
#include "Plugins/SDL2_image/SDL2ImgImporter.hh"
#include "Plugins/assimp/AssimpImporter.hh"
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
    Events::Get()->Unsubscribe(this, &Shooter::OnWindowEvent);
    Events::Get()->Unsubscribe(this, &Shooter::OnMouseButton);
    Events::Get()->Unsubscribe(this, &Shooter::OnMouseMove);
    Events::Get()->Unsubscribe(this, &Shooter::OnKeyEvent);
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
    events->Subscribe(this, &Shooter::OnMouseButton);
    events->Subscribe(this, &Shooter::OnWindowEvent);

    mImporter = std::make_unique<AssimpImporter>();
    mImageImporter = std::make_unique<SDL2ImgImporter>();

    // Init Shooter
    mRoot = Node::Create("Root");
    mCamera = std::make_shared<Camera>(1.0f, mWindow->GetAspectRatio(), 0.1f, 100.0f);
    mCamera->SetPosition(Vec3(0.0, 0.0, -1.0));


    // Init Render Stuff
    mRender = std::make_shared<Renderer>();
    auto quadData = VertexBuffer::Create({static_cast<uint32_t>(gQuadData.size()), sizeof(float)});
    quadData->WriteData(0, gQuadData.size() * sizeof(float), gQuadData.data());
    auto quadData2 = VertexBuffer::Create({static_cast<uint32_t>(gQuadData2.size()), sizeof(float)});
    quadData2->WriteData(0, gQuadData2.size() * sizeof(float), gQuadData2.data());
    auto quadUV = VertexBuffer::Create({static_cast<uint32_t>(gQuadUV.size()), sizeof(float)});
    quadUV->WriteData(0, gQuadUV.size() * sizeof(float), gQuadUV.data());
    auto quadNormal = VertexBuffer::Create({static_cast<uint32_t>(gQuadNormal.size()), sizeof(float)});
    quadNormal->WriteData(0, gQuadNormal.size() * sizeof(float), gQuadNormal.data());

    for (size_t i = 0; i < 2; i++)
    {
        mMeshes.emplace_back(std::make_shared<Mesh>());
        mMeshes[i]->mAttributes = VertexAttributes::Create({
            VertexAttribute{0, 3, GL_FLOAT, GL_FALSE, 0},
            VertexAttribute{1, 2, GL_FLOAT, GL_FALSE, 0},
            VertexAttribute{2, 3, GL_FLOAT, GL_FALSE, 0}});

        mMeshes[i]->mVertexData = std::make_shared<VertexData>();
        mMeshes[i]->mVertexData->SetBuffer(0, quadData);

        mMeshes[i]->mVertexData->SetBuffer(1, quadUV);
        mMeshes[i]->mVertexData->SetBuffer(2, quadNormal);

        mMeshes[i]->mIndexBuffer = IndexBuffer::Create({static_cast<uint32_t>(gQuadDataIdx.size())});
        mMeshes[i]->mIndexBuffer->WriteData(0, gQuadDataIdx.size() * sizeof(uint32_t), gQuadDataIdx.data());
    }

    mProgram = Program::Create();
    mProgram->LoadFrom(gVertexShaderSource, gFragmentShaderSource);

    mDeferred = Program::Create();
    mDeferred->LoadFrom(gPassthroughShaderSource, gImageShaderSource);

    auto img = mImageImporter->Import("Resources/Floor/bricks.png");
    mTexture = Texture::Create(img);


    auto mesh = mImporter->ImportMesh("Resources/Floor/Floor.gltf");
    mMeshes.push_back(mesh);
    mMaterial = std::make_shared<DefaultMaterial>();
    mMaterial->SetTexture(mTexture);
    mMaterial->SetProgram(mProgram);

    mRenderable = std::make_shared<Renderable>();
    mRenderable->SetMesh(mesh);
    mRenderable->SetMaterial(mMaterial);

    LoadScene();

    // TODO: MOVE THIS


    glGenTextures(1, &mRenderTexture);
    glBindTexture(GL_TEXTURE_2D, mRenderTexture);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, mWindow->GetWidth(), mWindow->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenTextures(1, &mNormalTexture);
    glBindTexture(GL_TEXTURE_2D, mNormalTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB10_A2, mWindow->GetWidth(), mWindow->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
/*
    glGenRenderbuffers(1, &mDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mWindow->GetWidth(), mWindow->GetHeight());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);
*/

    glGenTextures(1, &mDepthTexture);
    glBindTexture(GL_TEXTURE_2D, mDepthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, mWindow->GetWidth(), mWindow->GetHeight(), 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
/*
    glGenFramebuffers(1, &mFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mRenderTexture, 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, mNormalTexture, 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mDepthTexture, 0);
    GLenum drawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, drawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Error code: " << glGetError() << std::endl;
*/
    mRenderTarget = std::make_shared<Mesh>();
    mRenderTarget->mAttributes = VertexAttributes::Create({
        VertexAttribute{0, 3, GL_FLOAT, GL_FALSE, 0}});

    mRenderTarget->mVertexData = std::make_shared<VertexData>();
    mRenderTarget->mVertexData->SetBuffer(0, quadData2);

    mFrame = std::make_shared<Framebuffer>();
    mFrame->BindTexture(0, mRenderTexture);
    mFrame->BindTexture(1, mNormalTexture);
    mFrame->BindDepthbuffer(mDepthTexture);
    mFrame->Build();
}

void Shooter::LoadScene()
{
}

void Shooter::OnMouseMove(InputMouseMovementEvent* event)
{
    // Looking around
    static float MOUSE_SENS = 0.008f;
    auto quatY = glm::normalize(glm::angleAxis(MOUSE_SENS * event->GetRelative().y, Vec3{1, 0, 0}));
    auto quatX = glm::normalize(glm::angleAxis(-MOUSE_SENS * event->GetRelative().x, Vec3{0, 1, 0}));
    auto res = glm::normalize(mCamera->GetRotation() * quatY * quatX);
    mCamera->SetRotation(res);
}
void Shooter::OnMouseButton(InputMouseButtonEvent* event)
{
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

    float up = .0f;
    if(input->IsKeyPressed(SDLK_SPACE))
        up += 1.f;
    if(input->IsKeyPressed(SDLK_LSHIFT))
        up -= 1.0f;

    mCamera->GetPosition().y += up * delta * MOVEMENT_SPEED;

}

void Shooter::Render()
{
    mFrame->Bind();
    //glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
    glViewport(0,0,mWindow->GetWidth(), mWindow->GetHeight());

    mRender->Clear(0.f, 0.5f, 1.f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    mRender->BindProgram(mMaterial->GetProgram());
    glActiveTexture(GL_TEXTURE0);
    mRender->BindTexture(mMaterial->GetTexture());

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
        mProgram->SetUniform1i("uSampler", 0);
        if(counter <= 0) 
            counter -= mDelta.count() * 1.0f;
        else 
            counter += mDelta.count() * 1.0f;

        counter *= -1.0f;

        mProgram->SetUniformMat4f("uMVP", mvp);
        mRender->DrawIndexed(mesh->mIndexBuffer->GetIndexCount());
    }

    // Begin deferred stage
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,mWindow->GetWidth(), mWindow->GetHeight());
    mRender->Clear(0.0f, 0.0f, 0.0f, 1.0f);

    mRender->BindProgram(mDeferred);
    glDisable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mRenderTexture);
    mDeferred->SetUniform1i("uAlbedo", 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mNormalTexture);
    mDeferred->SetUniform1i("uNormal", 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mDepthTexture);
    mDeferred->SetUniform1i("uDepth", 2);

    mDeferred->SetUniformMat4f("uInvView", mCamera->GetInvView());
    mDeferred->SetUniformMat4f("uInvProj", mCamera->GetInvProjection());
    

    mDeferred->SetUniform3f("uLightPos", Vec3(0.1, 2.5, 5.5));
    mDeferred->SetUniform4f("uLightColor", Vec4(1.0, 0.2, 0.4, 1.0));
    mDeferred->SetUniform1f("uLightBrightness", 100.0f);
    mDeferred->SetUniform1f("uLightRadius", 20.5f);

    mRender->BindVertexAttributes(mRenderTarget->mAttributes);
    auto buffer = mRenderTarget->mVertexData->GetBuffer(0);
    mRender->BindVertexBuffers(0, &buffer, 1);
    mRender->Draw(6);

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