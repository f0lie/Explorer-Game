#include "include/Enemy.h"

 Enemy::Enemy(bool isSolid, int damage, Player *player, int xPosition, int yPosition, double dir, std::string fileName)
 : Entity(isSolid, xPosition, yPosition, dir, fileName){
	damageOnContact = damage;
	toChase = player;
	moveIndex =0;
}
double Enemy::toPlayer(){//degrees
        //if y is negative and x isn't +270, both neg add 180, y pos x neg add 90.
        double x= toChase->getX() - xPosition;
        double y= yPosition - toChase->getY();
        double r = sqrt(x*x + y*y);
   	double theta = acos(x/r)*180.0/PI;
        if(y>=0 && x<0) //Uh yeah someone check my work on this logic LOL
        	theta+=90.0;
        if(y<0 && x<0)
        	theta+=180.0;
        if(y<0 && x>=0)
        	theta+=270.0;
 }

void Enemy::attack(){
	//TODO
}
void Enemy::adjustSprite(){
	fixDirection();
    if(direction<=45 || direction > 315){
		if(!tex.loadFromFile("media/right_e.png"))
			std::cout<<"Failed to load texture right_e.png";
		sprite.setTexture(tex);
	}
    else if(direction<=135){
		if(!tex.loadFromFile("media/back_e.png"))
			std::cout<<"Failed to load texture back_e.png";
		sprite.setTexture(tex);
	}
   	else if(direction<=225){
		if(!tex.loadFromFile("media/left_e.png"))
			std::cout<<"Failed to load texture left_e.png";
		sprite.setTexture(tex);
	}
   	else{
		if(!tex.loadFromFile("media/front_e.png"))
			std::cout<<"Failed to load texture front_e.png";
		sprite.setTexture(tex);
	}
}

void Enemy::move(){
        char curr = aiMoveSequence[moveIndex];
        switch(curr){
        {
          case 'A':
          case 'a':
          attack(); 
          break;
          case 'C':
          case 'c':
          Set_direction(toPlayer());
          stepForward();
          break;
          case 'U':
          case 'u':
          direction = 90; //Our coordinate grid starts at 0,0 in the top left corner.  Until someone changes it.
          yPosition-=1;
          break;
          case 'D':
          case 'd':
          direction = 270;
          yPosition+=1;
          break;
          case 'L':
          case 'l':
          direction = 180;
          xPosition-=1;
          break;
          case 'R':
          case 'r':
          direction = 0;
          xPosition+=1;
          break;
	      default:
			break;
	      //TODO collision!
	      if(false ){//if there is a SOLID sprite in the same square.
			stepBackward();
			}
        }
        }
        moveIndex++;
        if(moveIndex>=strlen(aiMoveSequence)){//TODO find out why it always goes to 5.
        moveIndex =0;
        }
        //std::cout<<moveIndex<<" "; //FOR DEBUGGING
	}
