#include <SFML\Graphics.hpp>
#include <Box2D\box2d.h>
#include <iostream>

int main()
{
    std::cout << "Homo";
    sf::RenderWindow sfmlWin(sf::VideoMode(600, 360), "Hello World SFML Window");
    std::cout << "tiainen" << std::endl;
    b2Vec2 gravity(0.0f, 9.8f);
    std::cout << "gravity" << std::endl;
    b2World *world = new b2World(gravity);
    std::cout << "maailma" << std::endl;
    while (sfmlWin.isOpen())
    {

        sf::Event e;
        while (sfmlWin.pollEvent(e))
        {

            switch (e.type)
            {
            case sf::Event::EventType::Closed:
                sfmlWin.close();
                break;
            }
        }

        sfmlWin.clear();
        //sfmlWin.draw();
        sfmlWin.display();
    }

    return 0;
}