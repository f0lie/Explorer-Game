#include "Player.h"

Player::Player(bool isSolid, int xPosition, int yPosition, double dir, std::string fileName)
        : Entity(isSolid, xPosition, yPosition, dir, fileName)    // Call the superclass constructor in the subclass' initialization list.
        {
            weaponDamage =1;
            weaponRange =1;
            floor=1;
            score=0;
        }
void Player::attack(){
	//implement.  Play a sound?
}
