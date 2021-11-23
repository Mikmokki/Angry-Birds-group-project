#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "level.hpp"
#include "object.hpp"

int main()
{
    sf::RenderWindow sfmlWin(sf::VideoMode(1600, 900), "Angry Birds");
    b2Vec2 gravity(0.0f, 9.8f);
    b2World *world = new b2World(gravity);
    sf::CircleShape bird;
    bird.setRadius(30);
    bird.setOutlineColor(sf::Color::Red);
    bird.setOutlineThickness(5);
    bird.setOrigin(30.0f, 30.0f);
    bird.setPosition(100, 600);
    std::string asdf("asdf");
    Level level(asdf);
    std::cout << level.GetName();
    Object object();

    while (sfmlWin.isOpen())
    {

        sf::Event event;
        while (sfmlWin.pollEvent(event))
        {

            switch (event.type)
            {
            case sf::Event::EventType::Closed:
                sfmlWin.close();
                break;
            case sf::Event::EventType::Resized:
                sfmlWin.setSize(sf::Vector2u(event.size.width, event.size.width * 9 / 16));
                break;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i pos = sf::Mouse::getPosition(sfmlWin);
            bird.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
        }
        sfmlWin.clear(sf::Color::Green);
        sfmlWin.draw(bird);
        sfmlWin.display();
    }

    return 0;
}
