#ifndef BASICRENDERERS_HPP
#define BASICRENDERERS_HPP

#include <SFML/Graphics.hpp>

#include "../system.hpp"
#include "../components/basiccomponents.hpp"

class Engine;

struct Renderer : public System
{
    void draw(const float& deltaTime)
    {
        sf::RenderWindow *window = engine->getWindow();

        for (auto const& entity : m_mapEntities.at(engine->sceneGetName()))
        {
            auto& transformComp = engine->componentGetFromScene<Transform>(entity);
            auto& sprComp = engine->componentGetFromScene<Sprite>(entity);

            transformComp.x = sf::Mouse::getPosition(*window).x;
            transformComp.y = sf::Mouse::getPosition(*window).y;

            sprComp.sprite.setPosition(transformComp.x, transformComp.y);

            window->draw(sprComp.sprite);
        }
    }
};

#endif // BASICRENDERERS_HPP