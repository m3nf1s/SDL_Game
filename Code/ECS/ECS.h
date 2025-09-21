#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = size_t;

inline ComponentID GetComponentTypeID();

template<typename T>
inline ComponentID GetComponentTypeID() noexcept;

constexpr size_t MAX_COMPONENTS = 32;

using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array <Component*, MAX_COMPONENTS>;

class Component
{
public:
    explicit Component() = default;
    virtual ~Component() = default;

    virtual void Init();
    virtual	void Update();
    virtual	void Draw();

    Entity* entity = nullptr;
};

class Entity
{
public:
    void Update();
    void Draw();
    void Destroy();

    bool IsActive() const;

    template <typename T>
    bool HasComponent() const;

    template <typename T,  typename... TArgs>
    T& AddComponent(TArgs&& ... mArgs);

    template<typename T>
    T& GetComponent() const;

private:
    bool m_active = true;
    std::vector<std::unique_ptr<Component>> m_components;

    ComponentArray m_component_array;
    ComponentBitSet m_component_bitset;
};

class Manager
{
public:
    void Update();
    void Draw();
    void Refresh();
    Entity& AddEntity();

private:
    std::vector<std::unique_ptr<Entity>> m_entities;
};

/////////////////////////////////////////////////////////////
// Definition of functions and methods
/////////////////////////////////////////////////////////////

inline ComponentID GetComponentTypeID()
{
    static ComponentID last_ID = 0;
    return last_ID++;
}

template<typename T>
inline ComponentID GetComponentTypeID() noexcept
{
    static ComponentID typeID = GetComponentTypeID();
    return typeID;
}

template <typename T>
bool Entity::HasComponent() const
{
    return m_component_bitset[GetComponentTypeID<T>()];
}

template <typename T, typename... TArgs>
T& Entity::AddComponent(TArgs&& ... mArgs)
{
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

    ComponentID typeID = GetComponentTypeID<T>();

    if (m_component_bitset[typeID])
    {
        throw std::runtime_error("Component already exist");
    }

    if (typeID > MAX_COMPONENTS)
    {
        throw std::out_of_range("Component type ID is out of range");
    }

    std::unique_ptr<T> component_uptr = std::make_unique<T>(std::forward<TArgs>(mArgs)...);
    component_uptr->entity = this;

    m_components.emplace_back(std::move(component_uptr));

    T* component_ptr = static_cast<T*>(m_components.back().get());

    m_component_array[typeID] = component_ptr;
    m_component_bitset[typeID] = true;

    component_ptr->Init();

    return *component_ptr;
}

template<typename T>
T& Entity::GetComponent() const
{
    Component* ptr = m_component_array[GetComponentTypeID<T>()];
    return *static_cast<T*>(ptr);
}