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
#include "converter.hpp"

int main()
{
    sf::RenderWindow sfmlWin(sf::VideoMode(1600, 900), "Angry Birds");
    b2Vec2 gravity(0.0f, -0.3f);
    b2World *world = new b2World(gravity);

    // Creating a ground body //
    b2BodyDef groundBodyDef;                                // Define the ground body
    groundBodyDef.position.Set(20.0f, 40.0f);               // Set position
    b2Body *groundBody = world->CreateBody(&groundBodyDef); // Create the ground body

    b2PolygonShape groundBox; // The gound body polygon is defined to be a box
    float ground_w = 4.f;
    float ground_h = 2.f;
    groundBox.SetAsBox(ground_w, ground_h); // Creates a 200 x 20 box
    // Connecting these two together will form a Fixture
    groundBody->CreateFixture(&groundBox, 0.0f); // Defines the shape density
        // The SFML representation of the ground
    sf::RectangleShape ground;
    ground.setSize(sf::Vector2f(ground_w * 60, ground_h * 60));
    ground.setOutlineColor(sf::Color::Black);
    ground.setOutlineThickness(5);
    ground.setOrigin(ground_w * 30, ground_h * 30);
    ground.setPosition(b2ToSfCoords(groundBody->GetPosition()));

    // Creating the dynamic box in box2d //
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody; // By default bodies are static
    bodyDef.position.Set(2.0f, 1.0f);
    b2Body *body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox; // Exact same as in ground body
    float box_w = 1.0f;
    float box_h = 1.0f;
    dynamicBox.SetAsBox(box_w, box_h);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f; // Physical parameters are defined in the fixture
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    // The SFML representation of the dynamic box
    sf::RectangleShape box;
    box.setSize(sf::Vector2f(box_w * 60, box_h * 60));
    box.setOutlineColor(sf::Color::Red);
    box.setOutlineThickness(5);
    box.setOrigin(box_w * 30, box_h * 30);
    box.setPosition(b2ToSfCoords(body->GetPosition()));

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    sf::CircleShape bird;
    bird.setRadius(30);
    bird.setOutlineColor(sf::Color::Red);
    bird.setOutlineThickness(5);
    bird.setOrigin(30.0f, 30.0f);
    bird.setPosition(100, 600);

    int i = 0;

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
            sf::Vector2i pos = sf::Mouse::getPosition(sfmlWin);
            bird.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
            // sf::Vector2i mouseV(static_cast<float>(pos.x), static_cast<float>(pos.y));
            body->SetLinearVelocity(b2Vec2(0.f, 0.f));
            body->SetTransform(sfToB2Coords(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y))), 1.0f);
            bodyDef.position.Set(sfToB2Coords(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y))).x, sfToB2Coords(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y))).y);
            world->Step(timeStep, velocityIterations, positionIterations);
            // std::cout << pos.y << std::endl;
        }

        world->Step(timeStep, velocityIterations, positionIterations);
        ground.setPosition(b2ToSfCoords(groundBody->GetPosition()));
        box.setPosition(b2ToSfCoords(body->GetPosition()));
        // std::cout << b2ToSfCoords(body->GetPosition()).x << ", " << b2ToSfCoords(body->GetPosition()).y << "   " << body->GetPosition().x << ", " << body->GetPosition().y << std::endl;
        // box.setPosition(0, 0);

        sfmlWin.clear(sf::Color::Green);
        // sfmlWin.draw(bird);
        sfmlWin.draw(ground);
        sfmlWin.draw(box);
        sfmlWin.display();
        if (i >= 2000)
        {
            std::cout << (groundBody->GetPosition()).x << ", " << (groundBody->GetPosition()).y << std::endl;
            std::cout << body->GetPosition().x << ", " << body->GetPosition().y << std::endl;
            //return 0;
        }
        i++;
    }

    return 0;
}
