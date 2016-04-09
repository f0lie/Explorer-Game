#ifndef ENEMY_H
#define ENEMY_H

#include <sprite.h>


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
        void move(){
        char curr = aiMoveSequence[moveIndex];
        switch(curr){
        {
          case 'A':
          case 'a':
          attack(); //TODO implement void method that deals damage to other entities.
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
};

#endif // PLAYER_H
