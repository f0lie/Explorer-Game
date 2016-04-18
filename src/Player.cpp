#include "include/Player.h"

Player::Player(bool isSolid, int xPosition, int yPosition, double dir, std::string fileName)
        : Entity(isSolid, xPosition, yPosition, dir,
                 fileName)    // Call the superclass constructor in the subclass' initialization list.
{
    weaponDamage = 1;
    weaponRange = 1;
    floor = 1;
    score = 0;
    health = 100;
}

void Player::attack()
{
    //TODO implement damage functions.
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sword_miss.wav"))
        std::cout << "can't find sword_miss.wav";
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
}

void Player::adjustSprite()
{
    fixDirection();
    direction = (int) direction % 360;
    std::string fileName = "media/";
    if (direction <= 45 || direction > 315)
        fileName += "right";
    else if (direction <= 135)
        fileName += "back";
    else if (direction <= 225)
        fileName += "left";
    else
        fileName += "front";
    if (weaponRange > 10) //Change to if(activeSlot == bow) later?
        fileName += "_b";
    else if (weaponDamage > 5) //Change to if(activeSlot == sword) later?
        fileName += "_s";
    fileName += ".png";
    if (!tex.loadFromFile(fileName))
        std::cout << "Failed to load texture " + fileName;
    sprite.setTexture(tex);
}
