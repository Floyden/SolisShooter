#pragma once
#include "Event.hh"
#include "Math.hh"
namespace Solis
{
    
class InputKeyEvent : public IEvent 
{
public:
    InputKeyEvent() {}

    void SetKeycode(uint32_t keycode);
    uint32_t GetKeycode() const;

    void SetScancode(uint32_t scancode);
    uint32_t GetScancode() const;

    void SetPressed(bool pressed);
    bool IsPressed() const;

    void SetEcho(bool echo);
    bool IsEcho() const;

private:
    uint32_t mKeycode; /// mapped key value
    uint32_t mScancode; /// physical key press
    bool mPressed; /// true if pressed, otherwise released
    bool mEcho; /// true if it was an echo
};

class InputMouseEvent: public IEvent
{
public:
    InputMouseEvent() {};

    void SetPosition(Vec2i pos);
    Vec2i GetPosition() const;

private:
    Vec2i mPos;
};

class InputMouseMovementEvent : public InputMouseEvent
{
public:
    InputMouseMovementEvent() {}

    void SetRelative(Vec2i rel);
    Vec2i GetRelative() const;

    void SetButtonState(uint32_t state);
    uint32_t GetButtonState() const;

private:
    Vec2i mRelPos;
    uint32_t mButtonState;
};

class InputMouseButtonEvent : public InputMouseEvent
{
public:
    InputMouseButtonEvent() {}
    
    void SetButton(uint8_t rel);
    uint8_t GetButton() const;

    void SetPressed(bool val);
    bool GetPressed() const;

    void SetClicks(uint8_t val);
    uint8_t GetClicks() const;
private:
    uint8_t mButton; /// which button on the mouse
    uint8_t mClicks; /// How many clicks were pressed?
    bool mPressed; /// true if it is pressed
};

}