#ifndef ENTITY_H
#define ENTITY_H
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

class Entity
{   //entities should be used for item pickups, rocks, player characters, enemies, etc.  Anything that isn't map but is visible.
    protected:
        bool isSolid;
        int xPosition;
        int yPosition;
        double direction;
        sf::Sprite sprite;
        sf::Texture tex;
    public:
        Entity(bool isSolid, int x, int y, double dir, std::string fileName);
		sf::Sprite getSprite(){
			return sprite;
		}
        bool getSolid() {
             return isSolid;
        }
        void setSolid(bool val) {
            isSolid = val;
        }
        int getX() {
            return xPosition;
        }
        void setX(int val) {
            xPosition = val;
        }
        int getY() {
            return yPosition;
        }
        void setY(int val) {
            yPosition = val;
        }
        void stepForward();
        void stepBackward();
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
};

#endif // ENTITY_H
