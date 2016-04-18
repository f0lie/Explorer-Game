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
    char *m_aiMoveSequence;
    int m_moveIndex; //index of AI move sequence.
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

    void attack();

    void move();


    //Getters and setters
    double getDirection() const noexcept { return m_direction; }

    void setDirection(float val) { m_direction = val; }

    float getDamage() const noexcept { return m_damageOnContact; }

    void setDamage(float val) { m_damageOnContact = val; }

    char getMove() const noexcept { return m_aiMoveSequence[m_moveIndex]; }

    void setMoveSequence(char *sequence) { m_aiMoveSequence = sequence; }

    void setPlayer(Player *player) { m_toChase = player; }
};


#endif // PLAYER_H
