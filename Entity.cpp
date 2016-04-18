#include "Entity.h"

Entity::Entity(bool isSolid, int x, int y, double dir, std::string fileName){
	isSolid=isSolid;
	xPosition=x;
	yPosition=y;
	direction = dir;
	if(!tex.loadFromFile("media/" + fileName))
		std::cout<<"Failed to load texture "+fileName;
	sprite.setTexture(tex);
	health = 100;
}

void Entity::stepForward(){
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
        direction+=a; //Just some stupid tiebreaker code for 45 degree angle decisions.
       direction= (int)direction%360;
       if(direction<=45 || direction > 315)
        xPosition++;
    else if(direction<=135)
        yPosition--;
   	else if(direction<=225)
       	xPosition--;
   	else if(direction<=315)
       	yPosition++;
    adjustSprite();
}

void Entity::stepBackward(){
        	fixDirection();
        	if(direction<=45 || direction > 315)
        		xPosition--;
        	else if(direction<=135)
        		yPosition++;
        	else if(direction<=225)
        		xPosition++;
        	else if(direction<=315)
        		yPosition--;
        	adjustSprite();
}
void Entity::fixDirection(){
	if(direction<0)
		direction*=-1.0; //Must be positive direction.
	direction = (double)((int)direction % 360); //Must be between 0 and 360
	int a=0;
	if(rand()%2)
		a++;
	else 
		a--; //Add or subract 1 if it's 45 degrees to a right angle.
		if(direction==45)
			direction+=a;
       if(direction==135)
        direction+=a;
       if(direction==225)
        direction+=a;
       if(direction==315)
        direction+=a; //Just some stupid tiebreaker code for 45 degree angle decisions.
}

void Entity::up(){
	direction = 90.0;
	yPosition--;
	keepOnGrid();
	adjustSprite();
}
void Entity::down(){
	direction = 270.0;
	yPosition++;
	keepOnGrid();
	adjustSprite();
}
void Entity::left(){
	direction = 180.0;
	xPosition--;
	keepOnGrid();
	adjustSprite();
}
void Entity::right(){
	direction = 0.0;
	xPosition++;
	keepOnGrid();
	adjustSprite();
}
void Entity::keepOnGrid(){
	if (xPosition <4)
		xPosition = 4;
	if (xPosition>796)
		xPosition = 796;
	if (yPosition <10)
		yPosition = 10;
	if (yPosition>590)
		yPosition = 590;
}
