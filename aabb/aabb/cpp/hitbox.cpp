#include "../hpp/hitbox.hpp"
#include <iostream>

hitbox::hitbox()
{

};

hitbox::~hitbox(){};

void hitbox::handleResponse(sf::RectangleShape& firstObject,
                            float pushX, float pushY)
{
   firstObject.setPosition(firstObject.getPosition().x - pushX, firstObject.getPosition().y - pushY);
};

bool hitbox::isCollide(sf::RectangleShape& firstObject,
                       sf::RectangleShape& secondObject)
{
    delta.x = firstObject.getPosition().x - secondObject.getPosition().x;
    delta.y = firstObject.getPosition().y - secondObject.getPosition().y;

    intersect.x = abs(delta.x) - (firstObject.getSize().x/2 +
                                  secondObject.getSize().x/2);
    intersect.y = abs(delta.y) - (firstObject.getSize().y/2 +
                                  secondObject.getSize().y/2);

    if(intersect.x < 0.0f && intersect.y < 0.0f)
    {
        collision = true;
        if(intersect.x > intersect.y)
        {
            //check smaller axis if x
            if(delta.x < 0.0f)
            {
                //std::cout<<"right"<<std::endl;
                handleResponse(firstObject,-intersect.x,0);
            }

            if(delta.x > 0.0f)
            {
                //std::cout<<"left"<<std::endl;
                handleResponse(firstObject,intersect.x,0);
            }
        }

        if(intersect.x < intersect.y)
        {
            if(delta.y < 0.0f)
            {
                //std::cout<<"bottom"<<std::endl;
                handleResponse(firstObject,0,-intersect.y);
            }

            if(delta.y > 0.0f)
            {
                //std::cout<<"top"<<std::endl;
                handleResponse(firstObject,0,intersect.y);
            }
        }
    }
};
