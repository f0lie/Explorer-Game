#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.hpp"

int main()
{ //TODO classes to make.  Floor?  Maybe floor is a 2d array of Tiles that all have a texture?  idk dudes.
    //BEGIN STARTUP CODE
    sf::RenderWindow window(sf::VideoMode(600, 400), "SFML works!");
    sf::CircleShape shape(60.f);
    shape.setFillColor(sf::Color::Green);
	Player *player = new Player(true, 1, 1, 0.0);//solid, starting at (1,1) facing right.
    // while (window.isOpen())
    {
		//BEGIN MAIN GAME LOOP
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player->up();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player->left();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player->down();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player->right();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			player->attack();
		}
		
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();//SHUTDOWN CODE
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
