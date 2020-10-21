
#include "Input.hh"
#include "SDL_mouse.h"

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

bool Input::IsButtonPressed(int button) const
{
    const std::lock_guard<std::mutex> _guard(mMutex);
    return (mButtonMask & (1 << button)) != 0;
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

void Input::OnMouseButtonEvent(InputMouseButtonEvent* button)
{
    const std::lock_guard<std::mutex> _guard(mMutex);
    if(button && button->GetButton() != 0)
    {
        if(button->GetPressed()) 
            mButtonMask |= SDL_BUTTON(button->GetButton());
        else
            mButtonMask &= ~SDL_BUTTON(button->GetButton());
    }
}

} // namespace Solis
