#ifndef ENEMY_H
#define ENEMY_H

#include <math.h>
#include <iostream>
#include <cstring>
#include "Entity.h"
#include "Player.h"

#define PI 3.14159265

class Enemy : public Entity
{
protected:
    float damageOnContact;
    char *aiMoveSequence;
    int moveIndex; //index of AI move sequence.
    Player *toChase;
public:
    Enemy(bool isSolid,
          int damage,
          Player *player,
          int xPosition,
          int yPosition,
          double dir,
          std::string fileName);    // Call the superclass constructor in the subclass' initialization list


    double toPlayer();

    void attack();

    void move();

    void adjustSprite();


    //Getters and setters
    double getDirection()
    {
        return direction;
    }

    void setDirection(float val)
    {
        direction = val;
    }

    float getDamage()
    {
        return damageOnContact;
    }

    void setDamage(float val)
    {
        damageOnContact = val;
    }

    char getMove()
    {
        return aiMoveSequence[moveIndex];
    }

    void setMoveSequence(char *sequence)
    {
        aiMoveSequence = sequence;
    }

    void setPlayer(Player *player)
    {
        toChase = player;
    }
};


#endif // PLAYER_H
