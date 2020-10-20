#pragma once
#include <typeinfo>
#include <iostream>
#include "Defines.hh"

/**
 * Represent a module. 
 * There can be only one module for each class inhereting from IModule
 */
class IModule{
public:
    virtual ~IModule() = default;
    virtual void Init() {};
    virtual void Shutdown() {};
    virtual void Update() {};
};

class ModuleManager {
    static ModuleManager* sSingleton;
public:
    ModuleManager() 
    {
        sSingleton = this;
    }

    /// Add a module to the manager. Does not initialize the module.
    template<class T>
    T* AddModule() 
    {
        auto module = std::make_unique<T>();
        auto ptr = module.get();
        mModules.emplace(std::move(module));
        mOrder.push_back(ptr);
        return ptr;
    }

    /// Shutdown and remove the module if it exists
    template<class T>
    void RemoveModule() 
    {
        for (auto it = mModules.begin(); it != mModules.end(); ++it){
            auto res = dynamic_cast<T*>((*it).get());
            if(res != nullptr) {
                res->Shutdown();
                mModules.erase(it);
                return;
            }
        }
    }

    /// Get the module T. Return nullptr if none exists.
    template<class T>
    T* GetModule() 
    {
        for (auto it = mModules.begin(); it != mModules.end(); ++it){
            auto res = dynamic_cast<T*>((*it).get());
            if(res != nullptr) 
                return res;
        }

        std::cout << "Warning: could not find module " << typeid(T).name() << std::endl;
        return nullptr;
    }

    /// Initialize all modules in the order they were added
    void Init() {
        for (auto it = mOrder.begin(); it != mOrder.end(); it++)
            (*it)->Init();
        
    }

    /// Shutdown all modules in the reverse order they were added
    void Shutdown() {
        for (auto rit = mOrder.rbegin(); rit != mOrder.rend(); rit++)
            (*rit)->Shutdown();
    }

    /// Static function to get a module.
    /// Do not call this function before calling Init or after calling Shutdown.
    /*template<class T>
    static T* Get() {
        return sSingleton->GetModule<T>();
    }*/

    static ModuleManager* Get() {
        return sSingleton;
    }

private:
    UnorderedSet<UPtr<IModule>> mModules;
    Deque<IModule*> mOrder;
};