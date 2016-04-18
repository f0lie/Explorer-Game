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
    int health;
public:
    Entity(bool isSolid, int x, int y, double dir, std::string fileName);

    void stepForward();

    void stepBackward();

    void up();

    void down();

    void left();

    void right();

    virtual void adjustSprite() = 0;

    virtual void attack() = 0;

    void fixDirection();

    void keepOnGrid();

    //Getters and setters.
    sf::Sprite getSprite()
    {
        return sprite;
    }

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
