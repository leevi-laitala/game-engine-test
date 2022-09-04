#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <array>
#include <queue>
#include <iostream>

#include "componentmanager.hpp"
#include "entity.hpp"

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    Entity add();
    void destroy(const Entity& id);
    Signature& getSignature(const Entity& id);
    void enableComponent(const Entity& id, const uint32_t& component);
    void disableComponent(const Entity& id, const uint32_t& component);

private:
    std::array<Signature, MAX_ENTITIES> m_arrSignatures{};
    std::queue<Entity> m_queAvailableEntities{};
};



EntityManager::EntityManager()
{
    for (uint32_t i = 0; i < MAX_ENTITIES; ++i)
    {
        m_queAvailableEntities.push(i);
    }
}

EntityManager::~EntityManager()
{
}

Entity EntityManager::add()
{
    if (m_queAvailableEntities.size() != 0)
    {
        Entity e = m_queAvailableEntities.front();
        m_queAvailableEntities.pop();
        std::cout << "[EMgr] Created entity with id: " << e << std::endl;
        return e;
    }

    return 0;
}

void EntityManager::destroy(const Entity& id)
{
    m_arrSignatures[id].reset();
    m_queAvailableEntities.push(id);
}

Signature& EntityManager::getSignature(const Entity& id)
{
    return m_arrSignatures.at(id);
}

void EntityManager::enableComponent(const Entity& id, const uint32_t& component)
{
    m_arrSignatures.at(id).set(component, true);
}

#endif // ENTITYMANAGER_HPP