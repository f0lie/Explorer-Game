#ifndef PICKUP_H
#define PICKUP_H

#include <math.h>
#include <iostream>
#include <cstring>
#include "Entity.h"
#include "Player.h"
#define PI 3.14159265

class Pickup : public Entity
{
protected:
    float m_damageOnContact;
    char *m_aiMoveSequence;
    int m_moveIndex; //index of AI move sequence.
    Player *m_toPickup;
public:
    Pickup(bool isSolid,
          Player *player,
          int xPosition,
          int yPosition,
          double dir,
          std::string fileName);    // Call the superclass constructor in the subclass' initialization list 

    double toPlayer();
	void checkPickup();
	virtual void pickUp() = 0;
	double distanceToPlayer();
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

    void setPlayer(Player *player)
    {
        m_toPickup = player;
    }
    
};


#endif // PLAYER_H
