#include "level.hpp"
#include "bird.hpp"
#include "wall.hpp"
#include "ground.hpp"
#include "converters.hpp"

Level::Level() : name_(""), bird_starting_position_(b2Vec2(0, 0)) {}

Level::Level(std::string name, b2Vec2 bird_starting_pos) : name_(name), bird_starting_position_(bird_starting_pos)
{
    world_ = new b2World(gravity);
    // Creating ground box
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body *groundBody = world_->CreateBody(&groundBodyDef);
    objects_.push_back(new Ground(groundBody));
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    hovering_object_ = 0;
}

void Level::ThrowBird(int angle, b2Vec2 velocity)
{
    std::cout << "Throw Bird!" << std::endl;
    b2BodyDef birdDef;
    birdDef.type = b2_dynamicBody;
    birdDef.angle = angle;
    birdDef.position = bird_starting_position_;
    birdDef.linearVelocity = velocity;
    birdDef.linearDamping = 0.5f; // This could be constant and should be adjusted

    b2Body *body = world_->CreateBody(&birdDef);
    float bird_w = 1.0f;
    float bird_h = 1.0f;
    Object *obj = new Bird(body, bird_w, bird_w, 0);
    objects_.push_back(obj);

    b2CircleShape birdShape;
    birdShape.m_radius = 0.3;

    b2FixtureDef birdFixture;
    birdFixture.shape = &birdShape;
    birdFixture.density = 1.0f;
    birdFixture.friction = 1.0f;

    body->CreateFixture(&birdFixture);
}

void Level::AddObject(sf::RenderWindow &window)
{
    if (hovering_object_ == 1)
    {
        b2BodyDef hover_obj_bodydef;
        hover_obj_bodydef.type = b2_dynamicBody;
        hover_obj_bodydef.position = utils::SfToB2Coords(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
        hover_obj_bodydef.linearDamping = 0.5f; // This could be constant and should be adjusted

        b2Body *body = world_->CreateBody(&hover_obj_bodydef);
        // body->SetTransform(body->GetWorldCenter(), hover_rotation_ * (M_PI / 180.0f));

        float bird_w = 1.0f;
        float bird_h = 1.0f;

        b2CircleShape hover_obj_shape;
        // hover_obj_shape.SetAsBox(bird_w, bird_h, b2Vec2(bird_w / 2, bird_h / 2), (hover_rotation_ * (M_PI / 180.0f)));
        hover_obj_shape.m_radius = 0.3f;

        b2FixtureDef body_fixture;
        body_fixture.shape = &hover_obj_shape;
        body_fixture.density = 1.0f;
        body_fixture.friction = 1.0f;

        body->CreateFixture(&body_fixture);

        Object *obj = new Bird(body, bird_w, bird_w, hover_rotation_);
        objects_.push_back(obj);

        hover_rotation_ = 0;
    }
    else if (hovering_object_ == 2)
    {
        b2BodyDef hover_obj_bodydef;
        hover_obj_bodydef.type = b2_dynamicBody;
        std::cout << sf::Mouse::getPosition().x << "," << sf::Mouse::getPosition().y << std::endl;
        hover_obj_bodydef.position = utils::SfToB2Coords(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
        // hover_obj_bodydef.angle = 1.0f * hover_rotation_ * (M_PI / 180.0f);
        hover_obj_bodydef.linearDamping = 0.5f; // This could be constant and should be adjusted

        std::cout << "Rotation: " << hover_rotation_ << " to radians " << (hover_rotation_ * (M_PI / 180.0f)) << std::endl;

        b2Body *body = world_->CreateBody(&hover_obj_bodydef);
        // body->SetTransform(hover_obj_bodydef.position, -1.0f * hover_rotation_ * (M_PI / 180.0f));
        float wall_w = 1.f;
        float wall_h = 10.f;

        b2PolygonShape hover_obj_shape;
        hover_obj_shape.SetAsBox(wall_w, wall_h, b2Vec2(wall_w, wall_h), (-1.0f * hover_rotation_ * (M_PI / 180.0f)));

        b2FixtureDef hover_wall_fixture;
        hover_wall_fixture.shape = &hover_obj_shape;
        hover_wall_fixture.density = 10.0f;
        hover_wall_fixture.friction = 10.3f;
        b2MassData wall_mass_data;
        wall_mass_data.mass = 100.0f;
        wall_mass_data.center = b2Vec2(wall_w / 2.0f, wall_h / 2.0f);
        wall_mass_data.I = -20.0f;

        body->SetMassData(&wall_mass_data);
        body->CreateFixture(&hover_wall_fixture);

        Object *obj = new Wall(body, wall_w, wall_h, hover_rotation_);
        objects_.push_back(obj);

        hover_rotation_ = 0;
    }
}

sf::Vector2f toSFVector(b2Vec2 original)
{
    return sf::Vector2f(original.x * scale, 800 - (original.y * scale));
}

b2Vec2 toB2Vector(sf::Vector2f original)
{
    return b2Vec2(original.x / scale, 900 - (original.y / scale));
}

bool Level::RenderLevel(sf::RenderWindow &window)
{
    bool moving = false;
    sf::Sprite h_object;
    sf::Texture h_object_image;

    // h_object.setFillColor(sf::Color(255, 255, 255, 128));
    h_object.setColor(sf::Color(255, 255, 255, 128));

    switch (hovering_object_)
    {
    case 1:
        h_object_image.loadFromFile("../resources/images/bird.png");
        // h_object.setSize(sf::Vector2f(30, 30));
        h_object.setScale(1.0f * 64.0f / (1.0f * h_object_image.getSize().x), 1.0f * 64.0f / (1.0f * h_object_image.getSize().y));
        h_object.setOrigin(h_object_image.getSize().x / 2, h_object_image.getSize().y / 2);
        h_object.setPosition(0, 0);
        h_object.setTexture(h_object_image);
        break;
    case 2:
        h_object_image.loadFromFile("../resources/images/box.png");
        // h_object.setSize(sf::Vector2f(300, 300));
        h_object.setScale(1.0f * 64.0f / (1.0f * h_object_image.getSize().x), 10.0f * 64.0f / (1.0f * h_object_image.getSize().y));
        h_object.setOrigin(h_object_image.getSize().x / 2, h_object_image.getSize().y / 2);
        h_object.setPosition(0, 0);
        h_object.setTexture(h_object_image);
        break;
    default:
        h_object_image.loadFromFile("");
        h_object.setTexture(h_object_image);
        break;
    }

    window.clear(sf::Color::White);
    for (auto it : objects_)
    {
        b2Body *body = it->GetBody();
        b2Vec2 pos = body->GetPosition();
        sf::Sprite sprite = it->GetSprite();
        sprite.setPosition(utils::B2ToSfCoords(pos));
        std::cout << "Drawing rotation: " << (-1.0f * utils::RadiansToDegrees(body->GetAngle())) << std::endl;
        sprite.setRotation(sprite.getRotation() + -1.0f * utils::RadiansToDegrees(body->GetAngle()));
        window.draw(sprite);
        //std::cout << "Draw angle: " << body->GetAngle() << "  Position: " << pos.x << ", " << pos.y << std::endl;
        moving = moving || body->IsAwake();
    }

    sf::Vector2i m = sf::Mouse::getPosition(window);
    h_object.setPosition(m.x, m.y);
    h_object.setRotation(hover_rotation_);

    window.draw(h_object);
    window.display();
    return moving;
}