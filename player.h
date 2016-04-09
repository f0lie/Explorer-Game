#ifndef PLAYER_H
#define PLAYER_H

#include <sprite.h>


class Player : public sprite
{
    public:
        Player();

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

    private:
        float direction;
        int floor;
        int score;
        //TODO Still need private member to represent a list of items (inventory).
};

#endif // PLAYER_H
