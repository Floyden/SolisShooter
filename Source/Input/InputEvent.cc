#include "InputEvent.hh"

namespace Solis
{

void InputKeyEvent::SetKeycode(uint32_t keycode)
{
    mKeycode = keycode;
}

uint32_t InputKeyEvent::GetKeycode() const
{
    return mKeycode;
}

void InputKeyEvent::SetScancode(uint32_t scancode)
{
    mScancode = scancode;
}

uint32_t InputKeyEvent::GetScancode() const
{
    return mScancode;
}

void InputKeyEvent::SetPressed(bool pressed)
{
    mPressed = pressed;
}

bool InputKeyEvent::IsPressed() const
{
    return mPressed;
}

void InputKeyEvent::SetEcho(bool echo)
{
    mEcho = echo;
}

bool InputKeyEvent::IsEcho() const
{
    return mEcho;
}

void InputMouseEvent::SetPosition(Vec2i pos)
{
    mPos = pos;
}

Vec2i InputMouseEvent::GetPosition() const
{
    return mPos;
}

void InputMouseMovementEvent::SetRelative(Vec2i rel)
{
    mRelPos = rel;
}

Vec2i InputMouseMovementEvent::GetRelative() const
{
    return mRelPos;
}

void InputMouseMovementEvent::SetButtonState(uint32_t state)
{
    mButtonState = state;
}

uint32_t InputMouseMovementEvent::GetButtonState() const
{
    return mButtonState;
}

void InputMouseButtonEvent::SetButton(uint8_t button)
{
    mButton = button;
}

uint8_t InputMouseButtonEvent::GetButton() const
{
    return mButton;
}

void InputMouseButtonEvent::SetPressed(bool val)
{
    mPressed = val;
}

bool InputMouseButtonEvent::GetPressed() const
{
    return mPressed;
}

void InputMouseButtonEvent::SetClicks(uint8_t val)
{
    mClicks = val;
}

uint8_t InputMouseButtonEvent::GetClicks() const
{
    return mClicks;
}
} // namespace Solis