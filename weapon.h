#ifndef WEAPON_H
#define WEAPON_H


class Weapon
{
    public:
        Weapon();

        float Get_range() {
            return range;
        }
        void Set_range(float val) {
            range = val;
        }
        float Get_angleDegrees() {
            return angleDegrees;
        }
        void Set_angleDegrees(float val) {
            angleDegrees = val;
        }
        float Get_distanceInFront() {
            return distanceInFront;
        }
        void Set_distanceInFront(float val) {
            distanceInFront = val;
        }

    private:
        float range;
        float angleDegrees;
        float distanceInFront;
};

#endif // WEAPON_H
