#include <iostream>

#include "include/engine.hpp"

#include "include/ecs/systems/basicrenderers.hpp"

class Demo : public Engine
{
public:
    Demo() {}
    ~Demo() {}

    void onCreate() override
    {
        std::cout << "onCreate()" << std::endl;
        systemRegister<Renderer>();

        m_textureManager.load("assets/balloon.png", "balloon");
        m_textureManager.load("assets/heart.png", "heart");

        m_eventManager.addCallback(sf::Event::Closed, [&](const sf::Event&){ m_window.close(); });
        m_eventManager.addMouseButtonCallback(sf::Mouse::Button::Left, [&](const sf::Event&){ sceneSwitch("game"); });

        auto scene = sceneNew("test", true);
        auto game = sceneNew("game");

        sceneRegisterComponent<Transform>();
        sceneRegisterComponent<Sprite>();

        sceneRegisterComponent<Transform>("game");
        sceneRegisterComponent<Sprite>("game");

        Signature s;
        s.set(componentGetSignatureFromScene<Sprite>());
        s.set(componentGetSignatureFromScene<Transform>());
        systemSetSignature<Renderer>(s);

        Entity entity = sceneCreateEntity();
        Entity heart = sceneCreateEntity("game");

        sf::Sprite spr;
        spr.setTexture(*m_textureManager.get("balloon"));
        sceneAttachComponent("test", entity, Sprite{ .sprite = spr });
        sceneAttachComponent("test", entity, Transform{ .x = 0, .y = 0, .angle = 0 });

        sceneAttachComponent("game", heart, Sprite{ .sprite = spr });
        sceneAttachComponent("game", heart, Transform{ .x = 0, .y = 0, .angle = 0 });
    }

    void onUpdate(const float& deltaTime) override
    {
        systemGet<Renderer>()->draw(deltaTime);
    }

    void onEnd() override
    {
        std::cout << "onEnd()" << std::endl;
    }
};

int main(void)
{
    Demo demo;
    demo.run();

    return 0;
}
