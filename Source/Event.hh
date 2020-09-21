#pragma once
#include <vector>
#include <memory>
#include <map>
#include <typeindex>
#include <algorithm>
#include "Module.hh"
#include "Defines.hh"

class IEvent{};

class IEventHandler {
public:
    virtual ~IEventHandler() = default;

    void Exec(IEvent* event) { _Exec(event); };
protected:
    virtual void _Exec(IEvent*) = 0;
};

template <class T, class EventType>
class EventHandler : public IEventHandler {
    friend class Events;
    typedef void (T::*MemberFunction)(EventType*);
public:
    EventHandler(T* instance, MemberFunction func) : mInstance(instance), mFunction(func) {};

    void _Exec(IEvent* event) 
    {
        (mInstance->*mFunction)(static_cast<EventType*>(event));
    }
    
private:
    T* mInstance;
    MemberFunction mFunction;
};

class Events : public IModule {
    using SubList = UnorderedSet<UPtr<IEventHandler>>;
public:
    void Init() {};
    void Shutdown() {};
    void Update() {};

    template<class EventType>
    void Publish(EventType* event) 
    {
        auto& handlers = mSubscribers[typeid(EventType)];

        if(handlers == nullptr)
            return;
        
        for(auto& handler: *handlers) {
            if(handler)
                handler->Exec(event);
        }

        delete event;
    }

    template<class EventType>
    void Publish(UPtr<EventType> event) 
    {
        auto& handlers = mSubscribers[typeid(EventType)];

        if(handlers == nullptr)
            return;
        
        for(auto& handler: *handlers) {
            if(handler)
                handler->Exec(event.get());
        }
    }

    template<class T , class EventType>
    void Subscribe(T* instance, void (T::*mFunction)(EventType*)) 
    {
        auto& handlers = mSubscribers[typeid(EventType)];

        if(handlers == nullptr)
            mSubscribers[typeid(EventType)] = std::make_unique<SubList>();
            
        handlers->emplace(std::make_unique<EventHandler<T, EventType>>(instance, mFunction));
    }

    template<class T , class EventType>
    void Unsubscribe(T* instance, void (T::*mFunction)(EventType*)) {
        auto& handlers = mSubscribers[typeid(EventType)];

        if(handlers == nullptr)
            return;
            
        auto it = std::find_if(handlers->cbegin(), handlers->cend(), [&](const UPtr<IEventHandler>& ptr) {
            return instance == dynamic_cast<EventHandler<T, EventType>*>(ptr.get())->mInstance;
        });

        if (it != handlers->cend())
            handlers->erase(it);
    }

    static Events* Get() {
        return ModuleManager::Get()->GetModule<Events>();
    }

private:
    std::map<std::type_index, UPtr<SubList>> mSubscribers;
};