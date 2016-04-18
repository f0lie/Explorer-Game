#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"


class Player : public Entity
{
protected:
    int m_floor;
    int m_score;
    int m_weaponRange;
    int m_weaponDamage;
    //TODO Represent list of items (inventory) with a vector?  Do we need consumable items/weapon switching?
public:
    Player(bool isSolid, int xPosition, int yPosition, double dir, std::string fileName);

    void attack();

    //TODO update texture based on weapon damage and direction.
    //Getters and setters.
    int Get_floor() const noexcept { return m_floor; }

    void Set_floor(int val) { m_floor = val; }

    int Get_score() const noexcept { return m_score; }

    void Set_score(int val) { m_score = val; }

    int getDamage() const noexcept { return m_weaponDamage; }

    void setDamage(int d) { m_weaponDamage = d; }

    int getRange() const noexcept { return m_weaponRange; }

    void setRange(int r) { m_weaponRange = r; }


};

#endif // PLAYER_H
