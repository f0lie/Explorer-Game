#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.hpp"
#include "weapon.hpp"


class Player : public Sprite
{
    public:
        Player(bool isSolid, int xPosition, int yPosition, double dir)
        : Sprite(isSolid, xPosition, yPosition, dir)    // Call the superclass constructor in the subclass' initialization list.
        {
            weapon = new Weapon(1,1); //initialize with a "fist" range 1 damage 1
        }
		void up(){
			direction = 90; //Our coordinate grid starts at 0,0 in the top left corner.  Until someone changes it.
			yPosition-=1;
			if(false){//if there is a SOLID sprite in the same square.
			stepBackward();
			}
			//check if any occupying sprites are solid
		}
		void down(){
			direction = 270; //Our coordinate grid starts at 0,0 in the top left corner.  Until someone changes it.
			yPosition+=1;
			if(false){//if there is a SOLID sprite in the same square.
			stepBackward();
			}
			//check if any occupying sprites are solid
		}
		void left(){
			direction = 180; //Our coordinate grid starts at 0,0 in the top left corner.  Until someone changes it.
			xPosition-=1;
			if(false){//if there is a SOLID sprite in the same square.
			stepBackward();
			}
			//check if any occupying sprites are solid
		}
		void right(){
			direction = 0; //Our coordinate grid starts at 0,0 in the top left corner.  Until someone changes it.
			xPosition+=1;
			if(false){//if there is a SOLID sprite in the same square.
			stepBackward();
			}
			//check if any occupying sprites are solid
		}
		void attack(){
			//TODO implement attacking directionally in front based on weapon range.
		}

        float Get_direction() {
            return direction;
        }
        void Set_direction(float val) {
            direction = val;
        }
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

    protected:
        float direction;
        int floor;
        int score;
        Weapon *weapon;
        //TODO Still need private member to represent a list of items (inventory).
};

#endif // PLAYER_H
