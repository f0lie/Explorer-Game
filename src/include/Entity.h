#ifndef ENTITY_H
#define ENTITY_H

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

class Entity
{   //entities should be used for item pickups, rocks, player characters, enemies, etc.  Anything that isn't map but is visible.
protected:
    bool m_isSolid;
    int m_xPosition;
    int m_yPosition;
    double m_direction;
    sf::Sprite m_sprite;
    sf::Texture m_tex;
public:
    Entity(bool isSolid, int x, int y, double dir, std::string fileName);

    sf::Sprite getSprite() const noexcept { return m_sprite; }

    virtual void attack() = 0;

    void stepForward();

    void stepBackward();

    void up();

    void down();

    void left();


    void right();

    //Getters and setters.
    bool getSolid() const noexcept { return m_isSolid; }

    void setSolid(bool val) { m_isSolid = val; }

    int getX() const noexcept { return m_xPosition; }

    void setX(int val) { m_xPosition = val; }

    int getY() const noexcept { return m_yPosition; }

    void setY(int val) { m_yPosition = val; }

    double getDirection() const noexcept { return m_direction; }

    void setDirection(float val) { m_direction = val; }
};

#endif // ENTITY_H
