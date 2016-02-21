#ifndef WEAPON_H
#define WEAPON_H


class Weapon
{
    public:
        Weapon();

        float Get_range() {
            return _range;
        }
        void Set_range(float val) {
            _range = val;
        }
        float Get_angleDegrees() {
            return _angleDegrees;
        }
        void Set_angleDegrees(float val) {
            _angleDegrees = val;
        }
        float Get_distanceInFront() {
            return _distanceInFront;
        }
        void Set_distanceInFront(float val) {
            _distanceInFront = val;
        }

    private:
        float _range;
        float _angleDegrees;
        float _distanceInFront;
};

#endif // WEAPON_H
