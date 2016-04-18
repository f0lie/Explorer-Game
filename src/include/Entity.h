#ifndef ENTITY_H
#define ENTITY_H

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

class Entity
{   //entities should be used for item pickups, rocks, player characters, enemies, etc.  Anything that isn't map but is visible.
protected:
    bool isSolid;
    int xPosition;
    int yPosition;
    double direction;
    sf::Sprite sprite;
    sf::Texture tex;
public:
    Entity(bool isSolid, int x, int y, double dir, std::string fileName);

    sf::Sprite getSprite()
    {
        return sprite;
    }

    void stepForward();

    void stepBackward();

    void up();

    void down();

    void left();

    void right();


    //Getters and setters.
    bool getSolid()
    {
        return isSolid;
    }

    void setSolid(bool val)
    {
        isSolid = val;
    }

    int getX()
    {
        return xPosition;
    }

    void setX(int val)
    {
        xPosition = val;
    }

    int getY()
    {
        return yPosition;
    }

    void setY(int val)
    {
        yPosition = val;
    }

    void attack();

    float Get_direction()
    {
        return direction;
    }

    void Set_direction(float val)
    {
        direction = val;
    }
};

#endif // ENTITY_H
