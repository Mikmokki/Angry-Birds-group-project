#include "level.hpp"

Level::Level(std::string name, b2Vec2 bird_starting_pos) : name_(name), world_(gravity), bird_starting_position_(bird_starting_pos)
{
    // Creating ground box
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body *groundBody = world_.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
};

void Level::ThrowBird(int angle, b2Vec2 velocity)
{
    b2BodyDef birdDef;
    birdDef.type = b2_dynamicBody;
    birdDef.angle = angle;
    birdDef.position = bird_starting_position_;
    birdDef.linearVelocity = velocity;

    b2Body *body = world_.CreateBody(&birdDef);
    Object obj("", body);
    objects_.push_back(&obj);

    b2CircleShape birdShape;
    birdShape.m_radius = 1;

    b2FixtureDef birdFixture;
    birdFixture.shape = &birdShape;
    birdFixture.density = 1.0f;
    birdFixture.friction = 0.3f;

    body->CreateFixture(&birdFixture);
}