#ifndef HITBOX_HPP
#define HTIBOX_HPP
#include "SFML/Graphics.hpp"
#include <vector>

class hitbox
{
public:
    hitbox();
    ~hitbox();
    bool isCollide(sf::RectangleShape& firstObject,
                   sf::RectangleShape& secondObject);
    void handleResponse(sf::RectangleShape& firstObject, float pushX,
                        float pushY);
private:
    bool collision;
    sf::Vector2f delta;
    sf::Vector2f intersect;
};
#endif // HITBOX_HPP
