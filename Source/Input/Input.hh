#pragma once
#include "InputEvent.hh"
#include "Module.hh"
#include <set>
#include <mutex>
#include <thread>

namespace Solis
{


class Input : public IModule
{
public:
    Input() {};

    void Init();
    void Shutdown();

    static Input* Get();

    bool IsKeyPressed(int keycode) const;
    bool IsButtonPressed(int button) const;

private:
    void OnKeyEvent(InputKeyEvent* key);
    void OnMouseButtonEvent(InputMouseButtonEvent* key);

    std::set<int> mPressedKeys;
    int mButtonMask = 0;
    
    mutable std::mutex mMutex;
};
    
} // namespace Solis

