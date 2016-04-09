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
        float Get_damage() {
            return damage;
        }
        void Set_damage(float val) {
            damage = val;
        }

    private:
        float range;
        float damage;
};

#endif // WEAPON_H
