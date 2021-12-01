#include "level.hpp"
#include "bird.hpp"
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
}

void Level::ThrowBird(int angle, b2Vec2 velocity)
{
    b2BodyDef birdDef;
    birdDef.type = b2_dynamicBody;
    birdDef.angle = angle;
    birdDef.position = bird_starting_position_;
    birdDef.linearVelocity = velocity;
    birdDef.linearDamping = 0.5f; // This could be constant and should be adjusted

    b2Body *body = world_->CreateBody(&birdDef);
    Object *obj = new Bird(body);
    objects_.push_back(obj);

    b2CircleShape birdShape;
    birdShape.m_radius = 0.3;

    b2FixtureDef birdFixture;
    birdFixture.shape = &birdShape;
    birdFixture.density = 1.0f;
    birdFixture.friction = 1.0f;

    body->CreateFixture(&birdFixture);
}

bool Level::RenderLevel(sf::RenderWindow &window)
{
    bool moving = false;
    window.clear(sf::Color::White);
    for (auto it : objects_)
    {
        b2Body *body = it->GetBody();
        b2Vec2 pos = body->GetPosition();
        sf::Sprite sprite = it->GetSprite();
        sprite.setPosition(utils::B2ToSfCoords(pos));
        window.draw(sprite);
        moving = moving || body->IsAwake();
    }
    window.display();
    return moving;
}
