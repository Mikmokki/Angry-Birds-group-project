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
#include <math.h>

int main()
{
    sf::RenderWindow sfmlWin(sf::VideoMode(1600, 900), "Angry Birds");
    b2Vec2 gravity(0.0f, 9.8f);
    b2World *world = new b2World(gravity);
    sf::RectangleShape bird;
    sf::Texture birdImage;
    birdImage.loadFromFile("../resources/images/bird.png");
    bird.setSize(sf::Vector2f(30, 30));
    bird.setOrigin(15.0f, 15.0f);
    bird.setPosition(200, 580);
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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

            // slingshot.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            //   bird.setPosition(100, 600);
        }
        if (bird.getPosition().y > 0)
        {
        }
        sfmlWin.clear(sf::Color::Green);
        sfmlWin.draw(slingshot);
        sf::Vector2i pos = sf::Mouse::getPosition(sfmlWin);
        std::cout << pos.x << "  " << pos.y << std::endl;
        sf::Vertex line[2] =
            {
                sf::Vertex(sf::Vector2f(200, 580)),
                sf::Vertex(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))};
        sfmlWin.draw(line, 2, sf::Lines);
        sfmlWin.draw(bird);
        sfmlWin.display();
    }

    return 0;
}
