#include "include/Entity.h"

Entity::Entity(bool isSolid, int x, int y, double dir, std::string fileName)
{
    isSolid = isSolid;
    xPosition = x;
    yPosition = y;
    direction = dir;
    if (!tex.loadFromFile("media/" + fileName))
        std::cout << "Failed to load texture " + fileName;
    sprite.setTexture(tex);
}

void Entity::stepForward()
{
    int a = 0;
    if (rand() % 2)a++;
    else a--;
    if (direction == 45)
        direction += a;
    if (direction == 135)
        direction += a;
    if (direction == 225)
        direction += a;
    if (direction == 315)
        direction += a; //Just some stupid tiebreaker code for 45 degree angle decisions.
    direction = (int) direction % 360;
    if (direction <= 45 || direction > 315)
        xPosition++;
    else if (direction <= 135)
        yPosition--;
    else if (direction <= 225)
        xPosition--;
    else if (direction <= 315)
        yPosition++;
}

void Entity::attack()
{
    //Is overridden by Players and Enemies anyway
}

void Entity::stepBackward()
{
    int a = 0;
    if (rand() % 2)a++;
    else a--;
    if (direction == 45)
        direction += a;
    if (direction == 135)
        direction += a;
    if (direction == 225)
        direction += a;
    if (direction == 315)
        direction += a; //Just some stupid tiebreaker code for 45 degree angle decisions.
    direction = (int) direction % 360;
    if (direction <= 45 || direction > 315)
        xPosition--;
    else if (direction <= 135)
        yPosition++;
    else if (direction <= 225)
        xPosition++;
    else if (direction <= 315)
        yPosition--;
}


void Entity::up()
{
    direction = 90.0;
    yPosition--;
}

void Entity::down()
{
    direction = 270.0;
    yPosition++;
}

void Entity::left()
{
    direction = 180.0;
    xPosition--;
}

void Entity::right()
{
    direction = 0.0;
    xPosition++;
}
