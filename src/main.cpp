#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "level.hpp"
#include "bird.hpp"

int main()
{
    sf::RenderWindow sfmlWin(sf::VideoMode(1600, 900), "Angry Birds");
    sf::CircleShape bird;
    bird.setRadius(30);
    bird.setOutlineColor(sf::Color::Red);
    bird.setOutlineThickness(5);
    bird.setOrigin(30.0f, 30.0f);
    bird.setPosition(100, 600);

    b2Vec2 bsp(3.0f, 3.0f);
    Level level("Example level", bsp);

    level.ThrowBird(10, b2Vec2(5.0f, 5.0f));

    b2World *world = level.GetWorld();
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    // The whole world could possibly be drawn like this
    for (int32 i = 0; i < 60; ++i)
    {
        world->Step(timeStep, velocityIterations, positionIterations);
        b2Body *b = world->GetBodyList();
        while (b != nullptr)
        {
            b2Vec2 position = b->GetPosition();
            float angle = b->GetAngle();
            printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
            b = b->GetNext();
        }
    }

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