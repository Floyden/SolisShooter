#include "Window.hh"

namespace Solis {

UPtr<Window> Window::Create()
{
    UPtr<Window> window(new Window());
    window->mWindow = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if ( window->mWindow == nullptr )
        return nullptr;
        
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    /*auto surface = */SDL_GetWindowSurface(window->mWindow);
    SDL_UpdateWindowSurface(window->mWindow);
    window->mContext = SDL_GL_CreateContext(window->mWindow);
    SDL_GL_MakeCurrent(window->mWindow, window->mContext);

    glewExperimental = true;
    if ( glewInit() )
        return nullptr;

    return window;
}
Window::~Window()
{
    Destroy();
}

void Window::Destroy() 
{
    if(!mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }
}
void Window::SwapWindow() {
    SDL_GL_SwapWindow(mWindow);
}

uint32_t Window::GetWidth() const {
    return SDL_GetWindowSurface(mWindow)->w;
}

uint32_t Window::GetHeight() const {
    return SDL_GetWindowSurface(mWindow)->h;
}

float Window::GetAspectRatio() const {
    return static_cast<float>(GetWidth()) / static_cast<float>(GetHeight());
}

void Window::ProcessEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            mCloseRequested = true;
            break;

        case SDL_WINDOWEVENT:
            _HandleWindowEvents(event.window);
            break;

        case SDL_MOUSEWHEEL:
            break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            _HandleMouseButtonEvents(event.button);
            break;

        case SDL_MOUSEMOTION:
            _HandleMouseMotionEvents(event.motion);
            break;

        case SDL_KEYUP:
        case SDL_KEYDOWN:
            _HandleKeyEvents(event.key);
            break;

        case SDL_TEXTINPUT:
        case SDL_TEXTEDITING:
            // Dump it for now
            break;

        case SDL_AUDIODEVICEADDED:
            break;

        default:
            std::cout << "Window::ProcessEvent: unhandled event type: " << event.type << std::endl;
            break;
        }
    }
}
void Window::_HandleKeyEvents(SDL_KeyboardEvent event)
{
    mLastTimestamp = event.timestamp;
    auto keycode = event.keysym.sym;
    auto scancode = event.keysym.scancode;

    if(keycode == 0 && scancode == 0)
    {
        std::cout << "Window::_HandleKeyEvents: keycode and scancode were zero, is this a bug?" << std::endl;
        return;
    }
    
    UPtr<InputKeyEvent> res(new InputKeyEvent());
    res->SetKeycode(keycode);
    res->SetScancode(scancode);
    res->SetEcho(event.repeat != 0);
    res->SetPressed(event.state);

    Events::Get()->Publish(std::move(res));
}

void Window::_HandleMouseMotionEvents(SDL_MouseMotionEvent event)
{
    UPtr<InputMouseMovementEvent> res(new InputMouseMovementEvent());
    res->SetPosition(Vec2i(event.x, event.y));
    res->SetRelative(Vec2i(event.xrel, event.yrel));
    res->SetButtonState(event.state);
    
    Events::Get()->Publish(std::move(res));
}

void Window::_HandleMouseButtonEvents(SDL_MouseButtonEvent event)
{
    UPtr<InputMouseButtonEvent> res(new InputMouseButtonEvent());
    res->SetPosition(Vec2i(event.x, event.y));
    res->SetButton(event.button);
    res->SetPressed(event.state);
    res->SetClicks(event.clicks);
    
    Events::Get()->Publish(std::move(res));
}
void Window::_HandleWindowEvents(SDL_WindowEvent event)
{
    switch (event.event)
    {
    case SDL_WINDOWEVENT_FOCUS_LOST:
        mFocused = false;
        SendWindowEvent(WindowEventType::FocusLost);
        break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
        mFocused = true;
        SendWindowEvent(WindowEventType::FocusGained);
        break;
    case SDL_WINDOWEVENT_ENTER:
        SendWindowEvent(WindowEventType::Enter);
        break;
    case SDL_WINDOWEVENT_LEAVE:
        SendWindowEvent(WindowEventType::Leave);
        break;
    default:
        std::cout << "Unhandled Window Event: " << event.event << std::endl;
        break;
    }
}
void Window::SendWindowEvent(WindowEventType type)
{
    UPtr<WindowEvent> event(new WindowEvent());
    event->type = type;
    Events::Get()->Publish(std::move(event));
}

}