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
    float m_damageOnContact;
    std::vector<char> m_aiMoveSequence;
    unsigned int m_moveIndex; //index of AI move sequence.
    Player *m_toChase;
public:
    Enemy(bool isSolid,
          int damage,
          Player *player,
          int xPosition,
          int yPosition,
          double dir,
          std::string fileName);    // Call the superclass constructor in the subclass' initialization list


    double toPlayer();
	int xOffset(){return 4;}
	int yOffset(){return 8;}
    void attack();

    void move();

    void adjustSprite();


    //Getters and setters
    double getDirection()
    {
        return m_direction;
    }

    void setDirection(float val)
    {
        m_direction = val;
    }

    float getDamage()
    {
        return m_damageOnContact;
    }

    void setDamage(float val)
    {
        m_damageOnContact = val;
    }

    char getMove()
    {
        return m_aiMoveSequence[m_moveIndex];
    }

    void setMoveSequence(std::vector<char> s)
    {
        m_aiMoveSequence = s;
    }

    void setPlayer(Player *player)
    {
        m_toChase = player;
    }
};


#endif // PLAYER_H
