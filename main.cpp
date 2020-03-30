#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

std::vector <bool> getCollisionType(sf::RectangleShape player,
                               sf::RectangleShape box)
{
    bool LEFT   = false;
    bool TOP    = false;
    bool RIGHT  = false;
    bool BOTTOM = false;

    std::vector <bool> collisionType = {LEFT,TOP,RIGHT,BOTTOM};
    float deltaX = player.getPosition().x - box.getPosition().x;
    float deltaY = player.getPosition().y - box.getPosition().y;

    float intersectX = abs(deltaX) - (player.getSize().x/2 + box.getSize().x/2);
    float intersectY = abs(deltaY) - (player.getSize().y/2 + box.getSize().y/2);

    if(intersectX < 0.0f && intersectY < 0.0f)
    {
        if(intersectX > intersectY)
        {
            //check smaller axis if x
            if(deltaX < 0)
            {
                //std::cout<<"right"<<std::endl;
                collisionType[2] = true;
            }

            if(deltaX > 0)
            {
                //std::cout<<"left"<<std::endl;
                collisionType[0] = true;
            }
        }

        if(intersectX < intersectY)
        {
            if(deltaY < 0)
            {
                //std::cout<<"bottom"<<std::endl;
                collisionType[3] = true;
            }

            if(deltaY > 0)
            {
                //std::cout<<"top"<<std::endl;
                collisionType[1] = true;
            }
        }
    }

    return collisionType;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,700),"collision");

    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::Event event;

    sf::Vector2f playerPosition(100,100);
    sf::RectangleShape player;
    player.setFillColor(sf::Color::Blue);
    player.setSize(sf::Vector2f(20,40));
    player.setOrigin(player.getSize().x/2,
                     player.getSize().y/2);

    sf::Vector2f boxPosition(100,100);
    sf::RectangleShape box;
    box.setPosition(boxPosition);
    box.setFillColor(sf::Color::Green);
    box.setSize(sf::Vector2f(30,30));
    box.setOrigin(box.getSize().x/2,
                  box.getSize().y/2);

    int speed = 2;
    std::vector <bool> hitDirection;
    while(window.isOpen())
    {
        //controls
        hitDirection = getCollisionType(player,box);
        getCollisionType(player,box);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
           !hitDirection[0]
           )
        {
            playerPosition.x -= speed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
           !hitDirection[2])
        {
            playerPosition.x += speed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
           !hitDirection[3])
        {
            playerPosition.y += speed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
           !hitDirection[1]
           )
        {
            playerPosition.y -= speed;
        }

        player.setPosition(playerPosition);
        while(window.pollEvent(event))
        {
            if(event.type == event.Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(box);
        window.draw(player);
        window.display();
    }
    return 0;
}
