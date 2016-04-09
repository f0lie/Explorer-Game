#ifndef ENEMY_H
#define ENEMY_H
#include <math.h>
#include <sprite.h>
#define PI 3.14159265

class Enemy : public sprite
{
    public:
        Enemy();

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
        void Set_player(Player player){
        	toChase = player;
        }
        void stepForward(){
        	if(direction==45)
        		direction+=(1.0-((double)rand(1))*2.0);
        	if(direction==135)
        		direction+=(1.0-((double)rand(1))*2.0);
        	if(direction==225)
        		direction+=(1.0-((double)rand(1))*2.0);
        	if(direction==315)
        		direction+=(1.0-((double)rand(1))*2.0); //Just some stupid tiebreaker code for 45 degree angle chases.
        	direction%=360;
        	if(direction<=45 || direction > 315)
        		xPosition++;
        	else if(direction<=135)
        		yPosition--;
        	else if(direction<=225)
        		xPosition--;
        	else if(direction<=315)
        		yPosition++;
        }
        double toPlayer(){//degrees
        //if y is negative and x isn't +270, both neg add 180, y pos x neg add 90.
        double x= toChase.xPosition - xPosition;
        double y= yPosition - toChase.yPosition;
        double r = (x*x + y*y)^(1.0/2.0);
   	double theta = acos(x/r)*180.0/PI;
        if(y>=0 && x<0) //Uh yeah someone check my work on this logic LOL
        	theta+=90.0;
        if(y<0 && x<0)
        	theta+=180.0;
        if(y<0 && x>=0)
        	theta+=270.0;
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
	        cout<<"lol unidentified move in the array."
        }
        moveIndex++;
        if(moveIndex>=(sizeof(aiMoveSequence)/sizeof(aiMoveSequence[0]))){//If we're now outside the range of good values.
        moveIndex =0;
        }
        }

    private:
        float direction;
        float damageOnContact;
        char *aiMoveSequence;
        int moveIndex;
        Player toChase;
};

#endif // PLAYER_H
