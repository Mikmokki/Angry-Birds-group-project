#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "level.hpp"
#include "object.hpp"
#include "sf_b2_converter.hpp"
#include <math.h>

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

    sf::CircleShape bird2;
    bird2.setRadius(100);
    bird2.setOutlineColor(sf::Color::Red);
    bird2.setOutlineThickness(5);
    bird2.setOrigin(30.0f, 30.0f);
    bird2.setPosition(100, 600);

    sf::RectangleShape gameArea;
    gameArea.setSize(sfmlWin.getDefaultView().getSize());
    gameArea.setFillColor(sf::Color::Magenta);
    gameArea.setOutlineColor(sf::Color::Black);

    sf::View gameView(sfmlWin.getDefaultView());
    //sf::FloatRect viewPort(GameView.getViewport());

    while (sfmlWin.isOpen())
    {

        sf::Event event;
        while (sfmlWin.pollEvent(event))
        {
            float newRes;
            float oldRes;
            auto oldCenter = gameView.getCenter();
            float gameAreaRes = (gameArea.getSize().x / gameArea.getSize().y);

            switch (event.type)
            {
            case sf::Event::EventType::Closed:
                sfmlWin.close();
                break;
            case sf::Event::EventType::Resized:

                //sfmlWin.setSize(sf::Vector2u(event.size.width, event.size.width * 9 / 16));

                newRes = (1.f * event.size.width) / (1.f * event.size.height);

                oldRes = (gameView.getSize().x / gameView.getSize().y);
                //oldRes = (gameArea.getSize().x / gameArea.getSize().y);

                if (newRes > oldRes)
                {
                    float k = gameView.getSize().y / (1.f * event.size.height);

                    gameView.setSize(k * event.size.width, k * event.size.height);
                }
                else
                {
                    float k = gameView.getSize().x / (1.f * event.size.width);

                    gameView.setSize(k * event.size.width, k * event.size.height);
                }

                if (newRes > gameAreaRes)
                {
                    float k = gameArea.getSize().y / (1.f * event.size.height);

                    gameView.setSize(k * event.size.width, k * event.size.height);
                }
                else
                {
                    float k = gameArea.getSize().x / (1.f * event.size.width);

                    gameView.setSize(k * event.size.width, k * event.size.height);
                }

                gameView.setCenter(gameArea.getSize() * 0.5f);

                break;
            case sf::Event::EventType::MouseButtonPressed:

                if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    //GameView.zoom(1.1f);

                    //std::cout << GameView.getViewport().left << " " << GameView.getViewport().top << " "
                    //<< GameView.getViewport().width << " " << GameView.getViewport().height << std::endl;

                    //sfmlWin.setView(gameView);
                    break;
                }

            case sf::Event::EventType::MouseWheelScrolled:
                /* if (event.mouseWheelScroll.delta > 0 ||
                    (gameView.getSize().x <= gameArea.getSize().x * (1.f / 1.1f) ||
                     gameView.getSize().y <= gameArea.getSize().y * (1.f / 1.1f)))
                {
                    gameView.zoom(1 - event.mouseWheelScroll.delta * 0.1f);
                    gameView.move(((sf::Vector2f(bird.getPosition() - sf::Vector2f(gameView.getCenter()))).x) * event.mouseWheelScroll.delta * 0.1f,
                                  ((sf::Vector2f(bird.getPosition() - sf::Vector2f(gameView.getCenter()))).y) * event.mouseWheelScroll.delta * 0.1f);
                } */

                gameView.zoom(1 - event.mouseWheelScroll.delta * 0.1f);
                gameView.move(((sf::Vector2f(bird.getPosition() - sf::Vector2f(gameView.getCenter()))).x) * event.mouseWheelScroll.delta * 0.1f,
                              ((sf::Vector2f(bird.getPosition() - sf::Vector2f(gameView.getCenter()))).y) * event.mouseWheelScroll.delta * 0.1f);

                std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;

                break;

                        case sf::Event::EventType::KeyPressed:

                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    gameView.move(0, -10);
                    break;

                case sf::Keyboard::Down:
                    gameView.move(0, 10);
                    break;

                case sf::Keyboard::Left:
                    gameView.move(-10, 0);
                    break;

                case sf::Keyboard::Right:
                    gameView.move(10, 0);
                    break;

                default:
                    break;
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i pos = sf::Mouse::getPosition(sfmlWin);

            bird.setPosition(sfmlWin.mapPixelToCoords(pos));
        }

        sfmlWin.clear(sf::Color::Green);

        sfmlWin.setView(gameView);

        sfmlWin.draw(gameArea);
        sfmlWin.draw(bird);
        sfmlWin.draw(bird2);
        sfmlWin.display();
    }

    return 0;
}
