#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "converter.hpp"

int main()
{
    const int DEBUG = 0; // Debug output: 0 = none; 1 = ground; 2 = bird; 3 = wall
    sf::RenderWindow sfmlWin(sf::VideoMode(1600, 900), "Angry Birds");
    b2Vec2 gravity(0.0f, -0.3f);
    b2World *world = new b2World(gravity);

    float TEXTURE_SCALE = 64.0f; // This scales the png sprites in SFML to fit the box2d simulation

    // Creating a ground body //
    b2BodyDef ground_body_def;                                 // Define the ground body
    ground_body_def.position.Set(26.0f, 25.0f);                // Set position
    b2Body *ground_body = world->CreateBody(&ground_body_def); // Create the ground body

    b2PolygonShape ground_shape; // The gound body polygon is defined to be a box
    float ground_w = 26.f;
    float ground_h = 2.f;
    ground_shape.SetAsBox(ground_w, ground_h); // Creates a 200 x 20 box
    // Connecting these two together will form a Fixture
    ground_body->CreateFixture(&ground_shape, 0.0f); // Defines the shape density

    // The SFML representation of the ground
    sf::Texture ground_texture;
    ground_texture.loadFromFile("../resources/sprites/grass");
    sf::Sprite ground;
    ground_texture.setRepeated(true);
    ground.setScale(ground_w * TEXTURE_SCALE / (1.0f * ground_texture.getSize().x), ground_h * TEXTURE_SCALE / (1.0f * ground_texture.getSize().y));

    ground.setOrigin(ground_texture.getSize().x / 2.0f, ground_texture.getSize().y / 2.0f);
    ground.setPosition(b2ToSfCoords(ground_body->GetPosition()));
    ground.setTexture(ground_texture);

    // Creating the dynamic bird //
    b2BodyDef bird_body_def;
    bird_body_def.type = b2_dynamicBody; // By default bodies are static
    bird_body_def.position.Set(2.0f, 1.0f);
    b2Body *bird_body = world->CreateBody(&bird_body_def);

    b2PolygonShape bird_shape; // Exact same as in ground body
    float bird_w = 1.0f;
    float bird_h = 1.0f;
    bird_shape.SetAsBox(bird_w, bird_h);

    b2FixtureDef bird_fixture;
    bird_fixture.shape = &bird_shape;
    bird_fixture.density = 1.0f; // Physical parameters are defined in the fixture
    bird_fixture.friction = 0.3f;
    bird_fixture.restitution = 0.4f; // The bird bounces!
    bird_body->CreateFixture(&bird_fixture);
    // The SFML representation of the dynamic bird
    sf::Texture bird_texture;
    bird_texture.loadFromFile("../resources/sprites/bird_1");
    sf::Sprite bird;

    bird.setScale(bird_w * TEXTURE_SCALE / (1.0f * bird_texture.getSize().x), bird_h * TEXTURE_SCALE / (1.0f * bird_texture.getSize().y));
    bird.setOrigin(bird_texture.getSize().x / 2.0f, bird_texture.getSize().y / 2.0f);
    bird.setPosition(b2ToSfCoords(bird_body->GetPosition()));
    bird.setTexture(bird_texture);

    // Create the dynamic wall //
    b2BodyDef wall_body_def;
    wall_body_def.type = b2_dynamicBody;
    wall_body_def.position.Set(30.0f, 35.0f);
    b2Body *wall_body = world->CreateBody(&wall_body_def);

    b2PolygonShape wall_shape;
    float wall_w = 1.f;
    float wall_h = 10.f;
    wall_shape.SetAsBox(wall_w, wall_h);

    b2FixtureDef wall_fixture;
    wall_fixture.shape = &wall_shape;
    wall_fixture.density = 10.0f;
    wall_fixture.friction = 10.3f;
    b2MassData wall_mass_data;
    wall_mass_data.mass = 100.0f;
    wall_mass_data.center = b2Vec2(wall_w / 2.0f, wall_h / 2.0f);
    wall_mass_data.I = -20.0f;
    wall_body->SetMassData(&wall_mass_data);
    wall_body->CreateFixture(&wall_fixture);

    sf::Texture wall_texture;
    wall_texture.loadFromFile("../resources/sprites/box");
    sf::Sprite wall;

    wall.setScale(wall_w * TEXTURE_SCALE / (1.0f * wall_texture.getSize().x), wall_h * TEXTURE_SCALE / (1.0f * wall_texture.getSize().y));
    wall.setOrigin(wall_texture.getSize().x / 2.0f, wall_texture.getSize().y / 2.0f); // box.setOrigin(box_w * 30, box_h * 30);
    wall.setPosition(b2ToSfCoords(wall_body->GetPosition()));
    wall.setRotation(wall_body->GetAngle());
    wall.setTexture(wall_texture);

    const float TIME_STEP = 1.0f / 1200.0f;
    int32 velocity_iterations = 6;
    int32 position_iterations = 2;

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
            bird_body->SetLinearVelocity(b2Vec2(0.f, 0.f));
            bird_body->SetTransform(sfToB2Coords(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y))), 1.0f);
            bird_body_def.position.Set(sfToB2Coords(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y))).x, sfToB2Coords(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y))).y);
            bird_body->SetLinearVelocity(b2Vec2(5.f, 0.f));
            world->Step(TIME_STEP, velocity_iterations, position_iterations);
            // std::cout << pos.y << std::endl;
        }

        world->Step(TIME_STEP, velocity_iterations, position_iterations);
        ground.setPosition(b2ToSfCoords(ground_body->GetPosition()));
        bird.setPosition(b2ToSfCoords(bird_body->GetPosition()));
        bird.setRotation(-bird_body->GetAngle() * (180.0f / 3.14f));
        wall.setPosition(b2ToSfCoords(wall_body->GetPosition()));
        wall.setRotation(-wall_body->GetAngle() * (180.0f / 3.14f));
        // std::cout << b2ToSfCoords(body->GetPosition()).x << ", " << b2ToSfCoords(body->GetPosition()).y << "   " << body->GetPosition().x << ", " << body->GetPosition().y << std::endl;
        // box.setPosition(0, 0);

        sfmlWin.clear(sf::Color::White);
        // sfmlWin.draw(bird);
        sfmlWin.draw(ground);
        sfmlWin.draw(bird);
        sfmlWin.draw(wall);
        sfmlWin.display();

        switch (DEBUG)
        {
        case 1:
            std::cout << b2ToSfCoords(ground_body->GetPosition()).x << ", " << b2ToSfCoords(ground_body->GetPosition()).y << std::endl;
            break;
        case 2:
            std::cout << bird_body->GetPosition().x << ", " << bird_body->GetPosition().y << std::endl;
            break;
        case 3:
            std::cout << b2ToSfCoords(wall_body->GetPosition()).x << ", " << b2ToSfCoords(wall_body->GetPosition()).y << " Rotation: " << wall_body->GetAngle() << std::endl;
            break;
        default:
            break;
        }
        // std::cout << b2ToSfCoords(ground_body->GetPosition()).x << ", " << b2ToSfCoords(ground_body->GetPosition()).y << std::endl;
        // std::cout << body->GetPosition().x << ", " << body->GetPosition().y << std::endl;
        // std::cout << b2ToSfCoords(wall_body->GetPosition()).x << ", " << b2ToSfCoords(wall_body->GetPosition()).y << " Rotation: " << wall_body->GetAngle() << std::endl;
    }

    return 0;
}
