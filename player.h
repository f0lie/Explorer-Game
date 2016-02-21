#ifndef PLAYER_H
#define PLAYER_H

#include <sprite.h>


class Player : public sprite
{
    public:
        Player();

        float Get_direction() {
            return _direction;
        }
        void Set_direction(float val) {
            _direction = val;
        }
        int Get_floor() {
            return _floor;
        }
        void Set_floor(int val) {
            _floor = val;
        }
        int Get_score() {
            return _score;
        }
        void Set_score(int val) {
            _score = val;
        }

    private:
        float _direction;
        int _floor;
        int _score;
        //TODO Still need private member to represent a list of items (inventory).
};

#endif // PLAYER_H
