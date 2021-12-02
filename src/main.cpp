#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "level.hpp"
#include "object.hpp"
#include "sf_b2_converter.hpp"
#include <math.h>

/*
int main()
{
    sf::RenderWindow sfmlWin(sf::VideoMode(1600, 900), "Angry Birds");
    b2Vec2 gravity(0.0f, 9.8f);
    b2World *world = new b2World(gravity);
    std::pair<double, double> slingMid(200, 580);
    sf::RectangleShape bird;
    sf::Texture birdImage;
    birdImage.loadFromFile("../resources/images/bird.png");
    bird.setSize(sf::Vector2f(30, 30));
    bird.setOrigin(15.0f, 15.0f);
    bird.setPosition(slingMid.first, slingMid.second);
    bird.setTexture(&birdImage);
    sf::RectangleShape slingshot(sf::Vector2f(100.0f, 100.0f));
    sf::Texture slingshotImage;
    slingshotImage.loadFromFile("../resources/images/slingshot.png");
    slingshot.setTexture(&slingshotImage);
    slingshot.setPosition(200, 600);
    slingshot.setOrigin(50.0f, 50.0f);
    sf::Vertex line[2] = {};

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
                }

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

if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
{
    bird.setPosition(slingMid.first, slingMid.second);
    gameView.setCenter(bird.getPosition().x, gameView.getCenter().y);
}
if (bird.getPosition().y > 0)
{
}

sfmlWin.clear(sf::Color::Green);
sfmlWin.draw(gameArea);
sfmlWin.draw(slingshot);
sf::Vector2f pos = sfmlWin.mapPixelToCoords(sf::Mouse::getPosition(sfmlWin));
//std::cout << pos.x << "  " << pos.y << std::endl;
if (slingMid.first - pos.x > 0)
{

    double rotation;
    double direction;

    if (pos.y - slingMid.second > 0)
    {
        direction = 90 - atan((slingMid.first - pos.x) / (pos.y - slingMid.second)) * 180 / M_PI;
        rotation = -direction;
    }
    else if (pos.y - slingMid.second == 0)
    {
        direction = 0;
        rotation = 0;
    }
    else
    {
        direction = -90 + atan((slingMid.first - pos.x) / (slingMid.second - pos.y)) * 180 / M_PI;
        rotation = -direction;
    };
    double length = std::min(sqrt(pow(slingMid.first - pos.x, 2) + pow(pos.y - slingMid.second, 2)), 100.0);
    sf::RectangleShape line(sf::Vector2f(length, 5));
    sf::RectangleShape line2(sf::Vector2f(length / 3, 4));
    sf::RectangleShape line3(sf::Vector2f(length / 3, 4));

    line.setPosition(slingMid.first, slingMid.second);
    line2.setPosition(slingMid.first, slingMid.second);
    line3.setPosition(slingMid.first, slingMid.second);
    line.setFillColor(sf::Color(0, 0, 0));
    line2.setFillColor(sf::Color(0, 0, 0));
    line3.setFillColor(sf::Color(0, 0, 0));
    line.rotate(180 + rotation);
    line2.rotate(150 + rotation);
    line3.rotate(210 + rotation);
    sfmlWin.draw(line);
    sfmlWin.draw(line2);
    sfmlWin.draw(line3);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int time = 0;
        double gravity = 0.001;
        while (bird.getPosition().y <= slingMid.second + 200)
        {

            sfmlWin.clear(sf::Color::Green);
            bird.move(cos((direction)*M_PI / 180) * length / 100, -sin((direction)*M_PI / 180) * length / 100 + time * gravity);
            gameView.setCenter(bird.getPosition().x, gameView.getCenter().y);
            sfmlWin.setView(gameView);
            sfmlWin.draw(gameArea);
            sfmlWin.draw(slingshot);
            sfmlWin.draw(bird);
            sfmlWin.display();
            std::cout << bird.getPosition().x << "  " << bird.getPosition().y << std::endl;

            time++;
        }
    }
}

sfmlWin.setView(gameView);
sfmlWin.draw(bird);
sfmlWin.display();
}

return 0;
}
*/

#include "game.hpp"

int main()
{
    Game game = Game();
    game.LoadLevel("");
    game.Start();

    return 0;
}