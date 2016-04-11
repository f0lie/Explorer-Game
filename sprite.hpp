#ifndef SPRITE_H
#define SPRITE_H
#include <cstdlib>

class Sprite
{   //prites should be used for item pickups, rocks, player characters, enemies, etc.  Anything that isn't map but is visible.
    protected:
        bool isSolid;
        int xPosition;
        int yPosition;
        double direction;
    public:
        Sprite(bool isSolid, int xPosition, int yPosition, double dir)
		{
			xPosition=xPosition;
			yPosition=yPosition;
			isSolid=isSolid;
			direction = dir;
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
        void stepForward(){
			int a=0;
			if(rand()%2)a++;
			else a--;
        	if(direction==45)
        		direction+=a;
        	if(direction==135)
        		direction+=a;
        	if(direction==225)
        		direction+=a;
        	if(direction==315)
        		direction+=a; //Just some stupid tiebreaker code for 45 degree angle chases.
        	direction= (int)direction%360;
        	if(direction<=45 || direction > 315)
        		xPosition++;
        	else if(direction<=135)
        		yPosition--;
        	else if(direction<=225)
        		xPosition--;
        	else if(direction<=315)
        		yPosition++;
        }
        void stepBackward(){
        	int a=0;
			if(rand()%2)a++;
			else a--;
        	if(direction==45)
        		direction+=a;
        	if(direction==135)
        		direction+=a;
        	if(direction==225)
        		direction+=a;
        	if(direction==315)
        		direction+=a; //Just some stupid tiebreaker code for 45 degree angle chases.
        	direction= (int)direction%360;
        	if(direction<=45 || direction > 315)
        		xPosition--;
        	else if(direction<=135)
        		yPosition++;
        	else if(direction<=225)
        		xPosition++;
        	else if(direction<=315)
        		yPosition--;
        }
};

#endif // SPRITE_H
