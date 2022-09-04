#ifndef BASICCOMPONENTS_HPP
#define BASICCOMPONENTS_HPP

#include <SFML/Graphics.hpp>

struct Transform
{
    float x, y;
    float angle;
};

struct Sprite
{
    sf::Sprite sprite;
};

#endif // BASICCOMPONENTS