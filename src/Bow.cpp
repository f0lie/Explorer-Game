#include "include/Bow.h"

Bow::Bow(bool isSolid, Player *player, int xPosition, int yPosition, double dir, std::string fileName)
        : Pickup(isSolid, player, xPosition, yPosition, dir, fileName){ //Just call super.
}
void Bow::pickUp(){
	m_toPickup->setRange(50);
}
void Bow::attack(){
}//Nothing.  Must implement attack though.
