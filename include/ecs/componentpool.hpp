#ifndef COMPONENTPOOL_HPP
#define COMPONENTPOOL_HPP

#include <array>

#include <iostream>

#include "entity.hpp"
extern const uint32_t MAX_ENTITIES;
extern const uint32_t MAX_COMPONENTS;

// Non templated base class so that templated ones can be stored in same
// type of container
class ComponentPoolInterface
{
public:
    ComponentPoolInterface() {}
    virtual ~ComponentPoolInterface() = default;
    virtual void purgeEntity(const Entity& entity) = 0;
};

template<class T>
class ComponentPool : public ComponentPoolInterface
{
public:
    void addComponent(const Entity& entity, T component)
    {
        m_arrComponents.at(++m_size) = component;
        m_mapEntityToIndex.insert({entity, m_size});
    }

    void removeComponent(const Entity& entity)
    {
        uint32_t index = m_mapEntityToIndex.at(entity);
        uint32_t lastindex = --m_size;

        // Copy component data from last index to removed index
        m_arrComponents.at(index) = m_arrComponents.at(lastindex);

        // Find the entity in the last index of array
        for (auto entry : m_mapEntityToIndex)
        {
            if (entry.second == lastindex)
            {
                // Assign entity to new array index
                entry.second = index;
                break;
            }
        }

        // Erase index from map
        m_mapEntityToIndex.erase(entity);
    }

    T& getComponent(const Entity& entity)
    {
        return m_arrComponents.at(m_mapEntityToIndex.at(entity));
    }

    void purgeEntity(const Entity& entity) override
    {
        if (m_mapEntityToIndex.find(entity) != m_mapEntityToIndex.end())
        {
            removeComponent(entity);
        }
    }

private:
    std::array<T, MAX_ENTITIES> m_arrComponents;

    size_t m_size{};

    std::unordered_map<Entity, uint32_t> m_mapEntityToIndex;
};

#endif