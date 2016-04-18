#include "include/Player.h"

Player::Player(bool isSolid, int xPosition, int yPosition, double dir, std::string fileName)
        : Entity(isSolid, xPosition, yPosition, dir,
                 fileName)    // Call the superclass constructor in the subclass' initialization list.
{
    weaponDamage = 1;
    weaponRange = 1;
    floor = 1;
    score = 0;
    m_health = 100;
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
    m_direction = (int) m_direction % 360;
    std::string fileName = "media/";
    if (m_direction <= 45 || m_direction > 315)
        fileName += "right";
    else if (m_direction <= 135)
        fileName += "back";
    else if (m_direction <= 225)
        fileName += "left";
    else
        fileName += "front";
    if (weaponRange > 10) //Change to if(activeSlot == bow) later?
        fileName += "_b";
    else if (weaponDamage > 5) //Change to if(activeSlot == sword) later?
        fileName += "_s";
    fileName += ".png";
    if (!m_tex.loadFromFile(fileName))
        std::cout << "Failed to load texture " + fileName;
    m_sprite.setTexture(m_tex);
}
