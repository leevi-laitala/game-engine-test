#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "ecs/scene.hpp"
#include "ecs/system.hpp"

#include "resourcemanager.hpp"
#include "eventmanager.hpp"

class Engine
{
public:
    Engine()
        : m_window(sf::VideoMode(1280, 720), "SFML Game Engine Test")
        , m_eventManager(&m_window)
    {}

    virtual ~Engine()
    {}

    virtual void onCreate() = 0;
    virtual void onUpdate(const float& deltaTime) = 0;
    virtual void onEnd() = 0;

    //void init();
    void run()
    {
        //m_window.setFramerateLimit(30);

        sf::Clock dtClock;
        sf::Time dtTime = dtClock.restart();
        float deltaTime;

        onCreate();

        while (m_window.isOpen())
        {
            dtTime = dtClock.restart();
            deltaTime = dtTime.asSeconds();

            m_window.clear();

            m_eventManager.processEvents();

            onUpdate(deltaTime);

            m_window.display();
        }

        onEnd();
    }

// Scene management
public:
    std::shared_ptr<Scene> sceneNew(const char* name, bool makeActive = false)
    {
        m_mapScenes.insert({name, std::make_shared<Scene>()});

        if (makeActive == true)
        {
            sceneSwitch(name);
        }

        return m_mapScenes.at(name);
    }

    Entity sceneCreateEntity(const char* name = "")
    {
        auto scene = sceneGet(name);
        return scene->addEntity();
    }

    void sceneSwitch(const char* name = "")
    {
        m_activeSceneName = name;

        //for (auto const& system : m_mapSystems)
        //{
        //    system.second->m_setEntities.clear();
        //}

        //auto currentScene = sceneGet(m_activeSceneName);
        //currentScene->getEntityManager()->
    }

    // Call without argument returns active scene
    std::shared_ptr<Scene> sceneGet(const char* name = "")
    {
        if (*name == 0) // If no argument given
        {
            return m_mapScenes.at(m_activeSceneName);
        } else
        {
            return m_mapScenes.at(name);
        }
    }

    const char* sceneGetName()
    {
        return m_activeSceneName;
    }

    template<class T>
    void sceneAttachComponent(const char* name, const Entity& entity, T component)
    {
        auto scene = sceneGet(name);
        scene->attach(entity, component);

        auto signature = scene->getEntityManager()->getSignature(entity);
        signature.set(componentGetSignatureFromScene<T>(name), true);
        systemUpdateSignature(entity, signature);
    }

    template<class T>
    void sceneRegisterComponent(const char* name = "")
    {
        auto scene = sceneGet(name);
        scene->getComponentManager()->registerComponent<T>();
    }

    template<class T>
    T& componentGetFromScene(const Entity& entity, const char* name = "")
    {
        auto scene = sceneGet(name);
        return scene->getComponentManager()->getComponent<T>(entity);
    }

    template<class T>
    size_t componentGetSignatureFromScene(const char* name = "")
    {
        auto scene = sceneGet(name);
        return scene->getComponentManager()->getComponentIndex<T>();
    }

// System management
protected:
    template<class T>
    std::shared_ptr<T> systemRegister()
    {
        const char* name = typeid(T).name();

        auto system = std::make_shared<T>();
        system->engine = this;
        m_mapSystems.insert({name, system});

        std::cout << "[Engi] Registered system " << name << std::endl;
        return system;
    }

    template<class T>
    std::shared_ptr<T> systemGet()
    {
        const char* name = typeid(T).name();
        //std::cout << "[Engi] Getted system " << name << std::endl;
        return std::static_pointer_cast<T>(m_mapSystems.at(name));
    }

    template<class T>
    void systemSetSignature(const Signature& s)
    {
        const char* name = typeid(T).name();
        std::cout << "[Engi] Set signature " << s << " for component " << name << std::endl;
        m_mapSignatures.insert({name, s});
    }

    // Update systems with entitys new signature
    void systemUpdateSignature(const Entity& entity, Signature signature)
    {
        for (auto const& item : m_mapSystems)
        {
            if ((signature & m_mapSignatures.at(item.first)) == m_mapSignatures.at(item.first))
            {
                item.second->m_mapEntities[sceneGetName()];
                item.second->m_mapEntities.at(sceneGetName()).insert(entity);
            } else
            {
                item.second->m_mapEntities.at(sceneGetName()).erase(entity);
            }
        }
    }

    // Remove entity from systems
    void systemEntityPurge(const Entity& entity)
    {
        for (auto const& item : m_mapSystems)
        {
            item.second->m_mapEntities.at(sceneGetName()).erase(entity);
        }
    }

// System variables
protected:
    std::unordered_map<const char*, std::shared_ptr<System>> m_mapSystems{};
    std::unordered_map<const char*, Signature> m_mapSignatures{};

// Window management
public:
    sf::RenderWindow* getWindow()
    {
        return &m_window;
    }

// Resource handling
protected:
    sf::RenderWindow m_window;
    ResourceManager<sf::Texture, const char*> m_textureManager;

// Event handling
protected:
    EventManager m_eventManager;

// Misc
protected:
    std::unordered_map<const char*, std::shared_ptr<Scene>> m_mapScenes{};
    const char* m_activeSceneName;
};

#endif // ENGINE_HPP