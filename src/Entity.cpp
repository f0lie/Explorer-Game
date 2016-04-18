#include "include/Entity.h"

Entity::Entity(bool isSolid, int x, int y, double dir, std::string fileName)
{
    isSolid = isSolid;
    m_xPosition = x;
    m_yPosition = y;
    m_direction = dir;
    if (!m_tex.loadFromFile("media/" + fileName))
        std::cout << "Failed to load texture " + fileName;
    m_sprite.setTexture(m_tex);
    m_health = 100;
}

void Entity::stepForward()
{
    int a = 0;
    if (rand() % 2)a++;
    else a--;
    if (m_direction == 45)
        m_direction += a;
    if (m_direction == 135)
        m_direction += a;
    if (m_direction == 225)
        m_direction += a;
    if (m_direction == 315)
        m_direction += a; //Just some stupid tiebreaker code for 45 degree angle decisions.
    m_direction = (int) m_direction % 360;
    if (m_direction <= 45 || m_direction > 315)
        m_xPosition++;
    else if (m_direction <= 135)
        m_yPosition--;
    else if (m_direction <= 225)
        m_xPosition--;
    else if (m_direction <= 315)
        m_yPosition++;
    adjustSprite();
}

void Entity::stepBackward()
{
    fixDirection();
    if (m_direction <= 45 || m_direction > 315)
        m_xPosition--;
    else if (m_direction <= 135)
        m_yPosition++;
    else if (m_direction <= 225)
        m_xPosition++;
    else if (m_direction <= 315)
        m_yPosition--;
    adjustSprite();
}

void Entity::fixDirection()
{
    if (m_direction < 0)
        m_direction *= -1.0; //Must be positive direction.
    m_direction = (double) ((int) m_direction % 360); //Must be between 0 and 360
    int a = 0;
    if (rand() % 2)
        a++;
    else
        a--; //Add or subract 1 if it's 45 degrees to a right angle.
    if (m_direction == 45)
        m_direction += a;
    if (m_direction == 135)
        m_direction += a;
    if (m_direction == 225)
        m_direction += a;
    if (m_direction == 315)
        m_direction += a; //Just some stupid tiebreaker code for 45 degree angle decisions.
}

void Entity::up()
{
    m_direction = 90.0;
    m_yPosition--;
    keepOnGrid();
    adjustSprite();
}

void Entity::down()
{
    m_direction = 270.0;
    m_yPosition++;
    keepOnGrid();
    adjustSprite();
}

void Entity::left()
{
    m_direction = 180.0;
    m_xPosition--;
    keepOnGrid();
    adjustSprite();
}

void Entity::right()
{
    m_direction = 0.0;
    m_xPosition++;
    keepOnGrid();
    adjustSprite();
}

void Entity::keepOnGrid()
{
    if (m_xPosition < 4)
        m_xPosition = 4;
    if (m_xPosition > 796)
        m_xPosition = 796;
    if (m_yPosition < 10)
        m_yPosition = 10;
    if (m_yPosition > 590)
        m_yPosition = 590;
}
