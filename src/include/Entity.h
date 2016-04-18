#ifndef ENTITY_H
#define ENTITY_H

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

class Entity
{   //entities should be used for item pickups, rocks, m_player characters, enemies, etc.  Anything that isn't map but is visible.
protected:
    bool m_isSolid;
    int m_xPosition;
    int m_yPosition;
    double m_direction;
    sf::Sprite m_sprite;
    sf::Texture m_tex;
    int m_health;
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
        return m_sprite;
    }

    bool getSolid()
    {
        return m_isSolid;
    }

    void setSolid(bool val)
    {
        m_isSolid = val;
    }

    int getX()
    {
        return m_xPosition;
    }

    void setX(int val)
    {
        m_xPosition = val;
    }

    int getY()
    {
        return m_yPosition;
    }

    void setY(int val)
    {
        m_yPosition = val;
    }

    float Get_direction()
    {
        return m_direction;
    }

    void Set_direction(float val)
    {
        m_direction = val;
    }
};

#endif // ENTITY_H
