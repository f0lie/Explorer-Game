#ifndef ENEMY_H
#define ENEMY_H
#include <math.h>
#include <iostream>
#include "sprite.hpp"
#include "player.hpp"
#define PI 3.14159265

class Enemy : public Sprite
{
	protected:
        float direction;
        float damageOnContact;
        char *aiMoveSequence;
        int moveIndex;
        Player *toChase;
    public:
        Enemy(bool isSolid, int damage, Player *player, int xPosition, int yPosition, double dir)
        : Sprite(isSolid, xPosition, yPosition, dir)    // Call the superclass constructor in the subclass' initialization list.
        {
			damageOnContact = damage;
			toChase = player;
        }

        float Get_direction() {
            return direction;
        }
        void Set_direction(float val) {
            direction = val;
        }
        float Get_damageOnContact() {
            return damageOnContact;
        }
        void Set_damageOnContact(float val) {
            damageOnContact = val;
        }
        char Get_currentMove() {
            return aiMoveSequence[moveIndex];
        }
        void Set_moveSequence(char *sequence) {
            aiMoveSequence = sequence;
        }
        void Set_player(Player *player){
        	toChase = player;
        }
        double toPlayer(){//degrees
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
        void attack(){
		//TODO
		}
        void move(){
        char curr = aiMoveSequence[moveIndex];
        switch(curr){
        {
          case 'A':
          case 'a':
          attack(); //TODO implement void method that deals damage to other entities.
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
	        std::cout<<"lol unidentified move in the array.";
	      //TODO check if any occupying sprites are solid too!
	      if(false ){//if there is a SOLID sprite in the same square.
			stepBackward();
			}
        }
        moveIndex++;
        if(moveIndex>=(sizeof(aiMoveSequence)/sizeof(aiMoveSequence[0]))){//If we're now outside the range of good values.
        moveIndex =0;
        }
        }
	}
};


#endif // PLAYER_H
