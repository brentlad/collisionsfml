#include "SFML/Graphics.hpp"
#include <iostream>
#include "../hpp/hitbox.hpp"
#include <vector>
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600),"prototype");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::Event event;

    sf::RectangleShape player;
    player.setPosition(sf::Vector2f(100,100));
    player.setSize(sf::Vector2f(24,30));
    player.setOrigin(player.getSize().x/2,player.getSize().y/2);
    player.setFillColor(sf::Color::Blue);

    sf::RectangleShape wall;
    wall.setPosition(sf::Vector2f(300,300));
    wall.setSize(sf::Vector2f(30,30));
    wall.setOrigin(wall.getSize().x/2,wall.getSize().y/2);
    wall.setFillColor(sf::Color::Red);

    sf::RectangleShape wall2;
    wall2.setPosition(sf::Vector2f(490,300));
    wall2.setSize(sf::Vector2f(30,20));
    wall2.setOrigin(wall2.getSize().x/2,wall2.getSize().y/2);
    wall2.setFillColor(sf::Color::Red);
    float speed = 2;
    sf::Vector2f playerPosition(100,100);

    hitbox tile;
    sf::Clock clock;

    std::vector <sf::RectangleShape> container;

    for(int x=0;x < 10; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            sf::RectangleShape box;
            box.setFillColor(sf::Color::Green);
            box.setSize(sf::Vector2f(30,30));
            box.setPosition(100+30*x,100+30*y);
            box.setOrigin(box.getSize().x/2,
                          box.getSize().y/2);
            container.push_back(box);
        }
    }
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == event.Closed)
            {
                window.close();
            }
        }
        if(clock.getElapsedTime().asMilliseconds() >= 10)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                player.setPosition(player.getPosition().x-speed,player.getPosition().y);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player.setPosition(player.getPosition().x+speed,player.getPosition().y);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                player.setPosition(player.getPosition().x,player.getPosition().y+speed);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                player.setPosition(player.getPosition().x,player.getPosition().y-speed);
            }
            //player.setPosition(playerPosition);
            tile.isCollide(player,wall);
            tile.isCollide(player,wall2);
            clock.restart();
        }
        window.clear();
        for(int p = 0; p< container.size();p++)
        {
            tile.isCollide(player,container[p]);
            window.draw(container[p]);
        }
        window.draw(player);
        window.display();
    }

    return 0;
};
