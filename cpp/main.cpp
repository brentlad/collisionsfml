#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

std::vector <bool> getCollisionType(sf::RectangleShape player,
                               sf::RectangleShape box)
{
    bool LEFT   = false;
    bool TOP    = false;
    bool RIGHT  = false;
    bool BOTTOM = false;
    std::vector <bool> collisionType = {LEFT,TOP,RIGHT,BOTTOM};

    float deltaX = (player.getPosition().x + 15) - box.getPosition().x;
    float deltaY = (player.getPosition().y + 15) - box.getPosition().y;

    sf::Vector2f objectOne = player.getPosition();
    sf::Vector2f objectTwo = box.getPosition();


    //checks box bound
    std::cout<<deltaY<<std::endl;
    if((objectOne.x + 15) >= objectTwo.x &&
       (objectOne.x - 15) <= (objectTwo.x + 30) &&
       (objectOne.y - 15) <= (objectTwo.y + 30) &&
       (objectOne.y + 15) >= objectTwo.y
       )
    {

        if(deltaX > 0 && deltaX < 2)
        {
            collisionType[2] = true;
        }

        if(deltaX > 52)
        {
            collisionType[0] = true;
        }

        if(deltaY > 0 && deltaY < 2)
        {
            collisionType[3] = true;
        }

        if(deltaY > 52)
        {
            collisionType[1] = true;
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
    player.setOrigin(15,15);
    player.setFillColor(sf::Color::Blue);
    player.setSize(sf::Vector2f(30,30));

    sf::Vector2f boxPosition(300,300);
    sf::RectangleShape box;
    box.setPosition(boxPosition);
    box.setFillColor(sf::Color::Green);
    box.setSize(sf::Vector2f(30,30));

    int speed = 2;
    std::vector <bool> hitDirection;
    float pop = 0.2;
    while(window.isOpen())
    {
        //controls
        hitDirection = getCollisionType(player,box);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)&&
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
