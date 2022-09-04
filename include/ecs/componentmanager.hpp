#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP

#include <array>
#include <unordered_map>
#include <typeinfo>
#include <memory>

#include "componentpool.hpp"

class ComponentManager
{
public:
    template<class T>
    void registerComponent()
    {
        const char* name = typeid(T).name();

        // Check if pool for given component already exists
        if (m_mapNameToIndex.find(name) != m_mapNameToIndex.end())
        {
            std::cout << "[CMgr] Component " << name << " already registered" << std::endl;
            return;
        }


        m_arrComponentPools[m_size] = std::make_shared<ComponentPool<T>>();
        std::cout << "[CMgr] Registering component " << name << " with id of " << m_size << std::endl;
        m_mapNameToIndex.insert({name, m_size});

        m_size++;

        printComponents();
    }

    template<class T>
    void addComponent(const Entity& entity, T component)
    {
        std::cout << "[CMgr] Adding component " << typeid(T).name() << " to entity " << entity << std::endl;
        getPool<T>()->addComponent(entity, component);
    }

    void printComponents()
    {
        std::cout << "[CMgr] m_size = " << m_size << " | Currently registered: " << std::endl;
        for (auto const& pair : m_mapNameToIndex)
        {
            std::cout << "\tComponent: " << pair.first << " with index " << pair.second << "\n";
        }
    }

    template<class T>
    void removeComponent(const Entity& entity)
    {
        getPool<T>()->removeComponent(entity);
    }

    template<class T>
    T& getComponent(const Entity& entity)
    {
        return getPool<T>()->getComponent(entity);
    }

    void purgeComponentsForEntity(const Entity& entity)
    {
        for (auto const& index : m_arrComponentPools)
        {
            index->purgeEntity(entity);
        }
    }

    template<class T>
    size_t getComponentIndex()
    {
        const char* name = typeid(T).name();
        if (m_mapNameToIndex.find(name) == m_mapNameToIndex.end())
        {
            throw std::range_error("accessing nonexisting pair in map");
        } else
        {
            return m_mapNameToIndex.at(name);
        }
    }

private:
    template<class T>
    std::shared_ptr<ComponentPool<T>> getPool()
    {
        const char* name = typeid(T).name();
        size_t index = m_mapNameToIndex.at(name);
        return std::static_pointer_cast<ComponentPool<T>>(m_arrComponentPools.at(index));
    }


private:
    std::array<std::shared_ptr<ComponentPoolInterface>, MAX_COMPONENTS> m_arrComponentPools{};
    std::unordered_map<const char*, size_t> m_mapNameToIndex{};

    size_t m_size{};
};

#endif // COMPONENTMANAGER_HPP