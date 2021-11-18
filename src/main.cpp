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

#include <SFML\Graphics.hpp>
#include <box2d\box2d.h>
#include <iostream>

int main()
{
    std::cout << "Puna";
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
