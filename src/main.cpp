#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "level.hpp"
#include "bird.hpp"

int main()
{
    sf::RenderWindow sfmlWin(sf::VideoMode(1600, 900), "Angry Birds", sf::Style::Titlebar | sf::Style::Close);
    sfmlWin.setFramerateLimit(60);

    b2Vec2 bsp(3.0f, 3.0f);
    Level level("Example level", bsp);

    b2World *world = level.GetWorld();

    level.ThrowBird(10, b2Vec2(5.0f, 5.0f));

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    while (sfmlWin.isOpen())
    {

        std::cout << "Open" << std::endl;
        sf::Event event;
        while (sfmlWin.pollEvent(event))
        {

            switch (event.type)
            {
            case sf::Event::EventType::Closed:
                sfmlWin.close();
                break;
                /*
            case sf::Event::EventType::Resized:
                sfmlWin.setSize(sf::Vector2u(event.size.width, event.size.width * 9 / 16));
                break;
            */
            }
        }
        std::cout << "Polled" << std::endl;
        /*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i pos = sf::Mouse::getPosition(sfmlWin);
            bird.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
        }
        */
        //sfmlWin.clear(sf::Color::Green);
        //sfmlWin.draw(bird);
        //sfmlWin.display();
        world->Step(timeStep, velocityIterations, positionIterations);
        std::cout << "Step World" << std::endl;
        level.RenderLevel(sfmlWin);
        std::cout << "Full circle" << std::endl;
    }

    return 0;
}