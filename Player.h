#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <SFML/Audio.hpp>

class Player : public Entity
{
    public:
        Player(bool isSolid, int xPosition, int yPosition, double dir, std::string fileName);
		void attack();
		void adjustSprite();
		//TODO update texture based on weapon damage and direction.
		//Getters and setters.
        int Get_floor() {
            return floor;
        }
        void Set_floor(int val) {
            floor = val;
        }
        int Get_score() {
            return score;
        }
        void Set_score(int val) {
            score = val;
        }
        int getDamage(){
			return weaponDamage;
		}
		void setDamage(int d){
			weaponDamage =d;
		}
		int getRange(){
			return weaponRange;
		}
		void setRange(int r){
			weaponRange =r;
		}

    protected:
        int floor;
        int score;
        int weaponRange;
        int weaponDamage;
        //TODO Represent list of items (inventory) with a vector?  Do we need consumable items/weapon switching?
};

#endif // PLAYER_H
