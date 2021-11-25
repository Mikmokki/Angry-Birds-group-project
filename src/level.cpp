#include "level.hpp"

Level::Level(std::string name, b2Vec2 bird_starting_pos) : name_(name), bird_starting_position_(bird_starting_pos)
{
    world_ = new b2World(gravity);
    // Creating ground box
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body *groundBody = world_->CreateBody(&groundBodyDef);
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

    b2Body *body = world_->CreateBody(&birdDef);
    Object *obj = new Object("../src/bird.png", body);
    objects_.push_back(obj);

    b2CircleShape birdShape;
    birdShape.m_radius = 1;

    b2FixtureDef birdFixture;
    birdFixture.shape = &birdShape;
    birdFixture.density = 1.0f;
    birdFixture.friction = 0.3f;

    body->CreateFixture(&birdFixture);
}

sf::Vector2f toSFVector(b2Vec2 original)
{
    return sf::Vector2f(original.x * scale, 900 - (original.y * scale));
}

b2Vec2 toB2Vector(sf::Vector2f original)
{
    return b2Vec2(original.x / scale, 900 - (original.y / scale));
}

void Level::RenderLevel(sf::RenderWindow &window)
{
    std::cout << objects_.size() << std::endl;

    for (auto it : objects_)
    {
        std::cout << "Render start" << std::endl;
        b2Body *body = it->GetBody();
        std::cout << "Body: " << it->GetBody()->GetType() << std::endl;
        b2Vec2 pos = body->GetPosition();
        std::cout << pos.x << " , " << pos.y << std::endl;
        //sf::Sprite sprite(it->GetTexture());
        //sf::Sprite sprite = it->GetSprite();
        sf::Texture t;
        t.loadFromFile("../src/bird.png");
        sf::Sprite sprite(t);
        sprite.scale(1 / 10.0f, 1 / 10.0f);
        //std::cout << sprite.getTextureRect().height << ", " << sprite.getTextureRect().width << std::endl;
        sprite.setOrigin(sprite.getTextureRect().height / 20.0f, sprite.getTextureRect().width / 20.0f);
        //sprite2.setTexture(t);
        //std::cout << sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
        //sprite2.scale(sf::Vector2f(0.5f, 0.5f));
        //sprite2.setOrigin(10.0f, 10.0f);
        sprite.setPosition(toSFVector(pos));
        //std::cout << sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
        window.clear(sf::Color::White);
        window.draw(sprite);
        //window.draw(sprite2);
    }
    window.display();
}
