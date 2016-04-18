#ifndef BOW_H
#define BOW_H
#include "Pickup.h"
class Bow : public Pickup
{
public:
Bow(bool isSolid, Player *player, int xPosition, int yPosition, double dir, std::string fileName);
void pickUp();
void attack();
};

#endif // BOW_H
