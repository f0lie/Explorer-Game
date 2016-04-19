#include "include/Enemy.h"

Enemy::Enemy(bool isSolid, int damage, Player *player, int xPosition, int yPosition, double dir, std::string fileName)
        : Entity(isSolid, xPosition, yPosition, dir, fileName)
{
    m_damageOnContact = damage;
    m_toChase = player;
    m_moveIndex = 0;
}

double Enemy::toPlayer()
{//degrees
    double x = m_toChase->getX() - m_xPosition;
    double y = m_yPosition - m_toChase->getY();
    if(x==0){
		if(y<0)
			return 270.0;
		else
			return 90.0;
	}
	double theta = atan2(y,x)/3.14159265*180.0;
	if(y<0){
		theta = 90.0-theta;
		if(x>0)
			theta = 90.0-theta;
	}
	while(theta<=0.0)
		theta+=360.0;
    return theta;
}

void Enemy::attack()
{
    //TODO
}

void Enemy::adjustSprite()
{
    fixDirection();
    if (m_direction <= 45 || m_direction > 315)
    {
        if (!m_tex.loadFromFile("media/right_e.png"))
            std::cout << "Failed to load texture right_e.png";
        m_sprite.setTexture(m_tex);
    }
    else if (m_direction <= 135)
    {
        if (!m_tex.loadFromFile("media/back_e.png"))
            std::cout << "Failed to load texture back_e.png";
        m_sprite.setTexture(m_tex);
    }
    else if (m_direction <= 225)
    {
        if (!m_tex.loadFromFile("media/left_e.png"))
            std::cout << "Failed to load texture left_e.png";
        m_sprite.setTexture(m_tex);
    }
    else
    {
        if (!m_tex.loadFromFile("media/front_e.png"))
            std::cout << "Failed to load texture front_e.png";
        m_sprite.setTexture(m_tex);
    }
}

void Enemy::move()
{
    char curr = m_aiMoveSequence.at(m_moveIndex);
    switch (curr)
    {
        {
            case 'A':
                case 'a':
                    attack();
            break;
            case 'C':
                case 'c':
					m_direction = toPlayer();
            stepForward();
            break;
            case 'U':
                case 'u':
                    m_direction = 90; //Our coordinate grid starts at 0,0 in the top left corner.  Until someone changes it.
            m_yPosition -= 1;
            break;
            case 'D':
                case 'd':
                    m_direction = 270;
            m_yPosition += 1;
            break;
            case 'L':
                case 'l':
                    m_direction = 180;
            m_xPosition -= 1;
            break;
            case 'R':
                case 'r':
                    m_direction = 0;
            m_xPosition += 1;
            break;
            default:
                break;
            //TODO collision!
            if (false)
            {//if there is a SOLID m_sprite or SOLID map tile in the same square.
                stepBackward();
            }
        }
    }
    m_moveIndex++;
    if (m_moveIndex >= m_aiMoveSequence.size())
    {
        m_moveIndex = 0;
    }
}
