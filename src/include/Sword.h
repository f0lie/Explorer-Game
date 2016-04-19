#ifndef SWORD_H
#define SWORD_H
#include "Pickup.h"
class Sword : public Pickup
{
public:
Sword(bool isSolid, Player *player, int xPosition, int yPosition, double dir, std::string fileName);
void pickUp();
void attack();
};

#endif // SWORD_H
