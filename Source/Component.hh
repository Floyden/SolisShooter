#pragma once
#include <map>
#include <vector>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <iostream>

#include "Module.hh"

class Entity;

class IComponent {
public:
    IComponent() {}
    virtual ~IComponent() = default;

    Entity* GetParent() { return mParent; };
    const Entity* GetParent() const { return mParent; }
    void SetParent(Entity* parent) { mParent = parent; }

    virtual void Init() {};
    virtual void Update(float delta) {};

private:
    Entity* mParent;
};

class ComponentManager : public IModule {
    template<class T>
    using ComponentSet = UnorderedSet<SPtr<T>>;
public:
    ComponentManager() {};
    ~ComponentManager() {};

    /// Create a new component T for the entity
    template<class T, class... Args>
    T* AddComponent(int entity, Args&&...  args) 
    {
        auto& tId = typeid(T);
        auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
        mComponentMap[tId].insert(ptr);
        mEntityComponents[entity][tId] = ptr;

        return ptr.get();
    }

    /// Remove the component T from the entity
    template<class T>
    void RemoveComponent(int entity) 
    {
        auto& tId = typeid(T);
        auto ptr = mEntityComponents[entity][tId];

        mEntityComponents[entity].erase(tId);
        mComponentMap[tId].erase(ptr);
    }

    /// Remove all components of an enetiy
    void RemoveEntityComponents(int entity) 
    {
        auto components = mEntityComponents[entity];
        for(auto& pair: components)
            mComponentMap[pair.first].erase(pair.second);
        mEntityComponents.erase(entity);
    }

    /// Gets the compnent T from the entity. Returns nullptr if it doesnt have the component.
    template<class T>
    T* GetComponent(int entity) 
    {
        auto ptr = dynamic_cast<T*>(mEntityComponents[entity][typeid(T)].get());

        if(ptr)
            return ptr;

        std::cout << "Warning: Could not find any component of type " << typeid(T).name() <<
            " for the entity " << entity << std::endl;

        return nullptr;    
    }

    template<class T>
    bool HasComponent(int entity)
    {
        return mEntityComponents[entity].find(typeid(T)) != mEntityComponents[entity].end();
    }

    template<class T>
    ComponentSet<IComponent>& GetComponents() 
    {
        return mComponentMap[typeid(T)];
    }

    static ComponentManager* Get() 
    {
        return ModuleManager::Get()->GetModule<ComponentManager>();
    }

private:
    // <ComponentType, List of components>
    std::map<std::type_index, ComponentSet<IComponent>> mComponentMap;
    // <EntityId, map of owned Components>
    std::map<int, UnorderedMap<std::type_index, SPtr<IComponent>>> mEntityComponents;
};

using SharedEntity = SPtr<Entity>;

class Entity {
    friend class ComponentManager;
public:
    static SharedEntity Create(const String& name) {
        return std::make_shared<Entity>(name);
    }

    Entity(const String& name) : mName(name)
    {
        static int G_ENTITYID = 0;
        mId = ++G_ENTITYID;
    }

    ~Entity()
    {
        ComponentManager::Get()->RemoveEntityComponents(mId);
    }

    template<class T, class... Args>
    T* AddComponent(Args&&...  args) 
    {
        auto component = ComponentManager::Get()->AddComponent<T>(mId, std::forward<Args>(args)...);
        component->SetParent(this);
        return component;
    }

    template<class T>
    void RemoveComponent() 
    {
        ComponentManager::Get()->RemoveComponent<T>(mId);
    }

    template<class T>
    T* GetComponent() 
    {
        return ComponentManager::Get()->GetComponent<T>(mId);
    }

    template<class T>
    bool HasComponent() 
    {
        return ComponentManager::Get()->HasComponent<T>(mId);
    }

    String& GetName() { return mName; }
    const String& GetName() const { return mName; }
    
private:
    int mId;
    String mName;
};
