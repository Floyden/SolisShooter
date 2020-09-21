
#include "Input.hh"

namespace Solis
{
    
void Input::Init() 
{
    Events::Get()->Subscribe(this, &Input::OnKeyEvent);
    Events::Get()->Subscribe(this, &Input::OnMouseButtonEvent);
}

void Input::Shutdown()
{
    Events::Get()->Unsubscribe(this, &Input::OnKeyEvent);
    Events::Get()->Unsubscribe(this, &Input::OnMouseButtonEvent);
}

Input* Input::Get()
{
    return ModuleManager::Get()->GetModule<Input>();
}

bool Input::IsKeyPressed(int keycode) const
{
    const std::lock_guard<std::mutex> _guard(mMutex);
    return mPressedKeys.find(keycode) != mPressedKeys.end();
}

void Input::OnKeyEvent(InputKeyEvent* key)
{
    const std::lock_guard<std::mutex> _guard(mMutex);
    if(key && !key->IsEcho() && key->GetKeycode() != 0)
    {
        if(key->IsPressed())
            mPressedKeys.insert(key->GetKeycode());
        else
            mPressedKeys.erase(key->GetKeycode());
        
    }
}

void Input::OnMouseButtonEvent(InputMouseButtonEvent* key)
{
    const std::lock_guard<std::mutex> _guard(mMutex);
    std::cout << "Input::OnMouseButtonEvent dummy" << std::endl;

}

} // namespace Solis
