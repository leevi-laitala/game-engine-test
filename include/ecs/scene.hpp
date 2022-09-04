#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>

#include "entitymanager.hpp"
#include "componentmanager.hpp"

class Scene
{
public:
    Scene();
    ~Scene();

    Entity addEntity();

    void destroyEntity(const Entity& entity);
    
    template<class T>
    void attach(const Entity& entity, T component);

    std::shared_ptr<ComponentManager> getComponentManager();
    std::shared_ptr<EntityManager> getEntityManager();

//private:
public:
    std::shared_ptr<EntityManager> m_entityManager;
    std::shared_ptr<ComponentManager> m_componentManager;
};



Scene::Scene()
{
    m_entityManager = std::make_shared<EntityManager>();
    m_componentManager = std::make_shared<ComponentManager>();
}

Scene::~Scene()
{
}

Entity Scene::addEntity()
{
    return m_entityManager->add();
}

void Scene::destroyEntity(const Entity& entity)
{
    m_entityManager->destroy(entity);
    m_componentManager->purgeComponentsForEntity(entity);
}

template<class T>
void Scene::attach(const Entity& entity, T component)
{
    std::cout << "[Scen] Attaching component " << typeid(T).name() << " to entity " << entity << std::endl;
    // Register component, it wont do anything if duplicate
    //m_componentManager->registerComponent<T>();

    m_componentManager->addComponent<T>(entity, component);

    size_t index = m_componentManager->getComponentIndex<T>();
    m_entityManager->enableComponent(entity, index);
}

std::shared_ptr<ComponentManager> Scene::getComponentManager()
{
    return std::static_pointer_cast<ComponentManager>(m_componentManager);
}

std::shared_ptr<EntityManager> Scene::getEntityManager()
{
    return std::static_pointer_cast<EntityManager>(m_entityManager);
}

#endif