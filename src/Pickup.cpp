#include "include/Pickup.h"

Pickup::Pickup(bool isSolid, Player *player, int xPosition, int yPosition, double dir, std::string fileName)
        : Entity(isSolid, xPosition, yPosition, dir, fileName)
{
    m_toPickup = player;
}

double Pickup::distanceToPlayer(){
		int x = m_toPickup->getX() - m_xPosition;
		int y = m_toPickup->getY() - m_yPosition;
		return sqrt(x*x + y*y);
	}
void Pickup::checkPickup(){
		if(distanceToPlayer() < 25){
			m_health =0;
			pickUp();
		}
	}
void Pickup::adjustSprite(){}
