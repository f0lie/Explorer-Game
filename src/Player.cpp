#include "include/Player.h"

Player::Player(bool isSolid, int xPosition, int yPosition, double dir, std::string fileName)
        : Entity(isSolid, xPosition, yPosition, dir, fileName)    // Call the superclass constructor in the subclass' initialization list.
        {
            m_weaponDamage =1;
            m_weaponRange =1;
            m_floor=1;
            m_score=0;
        }
void Player::attack(){
	//implement.  Play a sound?
}
