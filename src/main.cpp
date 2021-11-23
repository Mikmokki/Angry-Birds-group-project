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
    sf::CircleShape bird;
    bird.setRadius(30);
    bird.setOutlineColor(sf::Color::Red);
    bird.setOutlineThickness(5);
    bird.setOrigin(30.0f,30.0f);
    bird.setPosition(100, 600);
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
                sfmlWin.setSize(sf::Vector2u(e.size.width,e.size.width*9/16));
                break;
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
           sf::Vector2i pos = sf::Mouse::getPosition(sfmlWin);
           bird.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
        }
        sfmlWin.clear(sf::Color::Green);
        sfmlWin.draw(bird);
        sfmlWin.display();
    }

    return 0;
}
