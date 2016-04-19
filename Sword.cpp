#include "include/Sword.h"

Sword::Sword(bool isSolid, Player *player, int xPosition, int yPosition, double dir, std::string fileName)
        : Pickup(isSolid, player, xPosition, yPosition, dir, fileName){ //Just call super.
}
void Sword::pickUp(){
	m_toPickup->setDamage(25);
}
void Sword::attack(){
}//Nothing.  Must implement attack though.
