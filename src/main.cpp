/*#include "mainmenu.h"
#include "mycanvas.h"
#include "sfml_widget.h"

#include <QApplication>
#include <QFrame>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainMenu w;
    w.show();

    /*
    QApplication a(argc, argv);
    QFrame* MainFrame = new QFrame;
    MainFrame->setWindowTitle("Qt SFML");
    MainFrame->resize(400, 400);
    MainFrame->show();
    MyCanvas* SFMLView = new MyCanvas(MainFrame, QPoint(20, 20), QSize(360, 360));
    SFMLView->show();
    */
/*
return a.exec();
}
*/

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

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
            case sf::Event::EventType::Resized:
                sfmlWin.setSize(sf::Vector2u(e.size.width, e.size.width * 9 / 16));
                break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            bird.setPosition(slingMid.first, slingMid.second);
        }
        if (bird.getPosition().y > 0)
        {
        }
        sfmlWin.clear(sf::Color::Green);
        sfmlWin.draw(slingshot);
        sf::Vector2i pos = sf::Mouse::getPosition(sfmlWin);
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
                    sfmlWin.draw(bird);
                    sfmlWin.draw(slingshot);
                    sfmlWin.display();
                    std::cout << bird.getPosition().x << "  " << bird.getPosition().y << std::endl;

                    time++;
                }
            }
        }
        sfmlWin.draw(bird);
        sfmlWin.display();
    }

    return 0;
}