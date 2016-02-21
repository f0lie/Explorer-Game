#ifndef SPRITE_H
#define SPRITE_H


class sprite
{   //Sprites should be used for item pickups, rocks, player characters, enemies, etc.  Anything that isn't map but is visible.
    public:
        sprite();

        boolean Getsolid() {
             return solid;
        }
        void Setsolid(boolean val) {
            solid = val;
        }
        int GetxPosition() {
            return xPosition;
        }
        void SetxPosition(int val) {
            xPosition = val;
        }
        int GetyPosition() {
            return yPosition;
        }
        void SetyPosition(int val) {
            yPosition = val;
        }

    private:
        boolean _isSolid;
        int _xPosition;
        int _yPosition;
};

#endif // SPRITE_H
