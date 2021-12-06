#include "level.hpp"
#include "bird.hpp"
#include "pig.hpp"
#include "ground.hpp"
#include "wall.hpp"
#include <algorithm>
#include <iostream>

Level::Level() : name_(""), bird_starting_position_(b2Vec2(0, 0)) {}

Level::Level(std::string name, b2Vec2 bird_starting_pos) : name_(name), bird_starting_position_(bird_starting_pos)
{
    world_ = new b2World(gravity);
    // Creating ground box
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 0.0f);
    b2Body *groundBody = world_->CreateBody(&groundBodyDef);

    Object *gObj = new Ground(groundBody);

    groundBodyDef.userData;
    objects_.push_back(gObj);
    b2PolygonShape groundBox;
    float ground_w = 50.0f;
    float ground_h = 1.0f;
    groundBox.SetAsBox(ground_w, ground_h);

    b2FixtureDef def;
    def.shape = &groundBox;
    def.density = 0.0f;

    def.userData.pointer = reinterpret_cast<uintptr_t>(gObj);
    groundBody->CreateFixture(&def);

    // Create the bird object
    float BIRD_RADIUS = 0.3f;

    b2BodyDef birdDef;
    birdDef.type = b2_dynamicBody;
    birdDef.position = bird_starting_position_;
    birdDef.linearDamping = 0.5f; // This could be constant and should be adjusted
    birdDef.gravityScale = 0;     // Set gravity scale initially to zero so bird floats on slingshot

    b2Body *body = world_->CreateBody(&birdDef);
    Bird *bird1 = new BoomerangBird(body, BIRD_RADIUS);
    Bird *bird2 = new DroppingBird(body, BIRD_RADIUS);
    Bird *bird3 = new SpeedBird(body, BIRD_RADIUS);
    birds_.push_back(bird1);
    birds_.push_back(bird2);
    birds_.push_back(bird3);

    b2CircleShape birdShape;
    birdShape.m_radius = BIRD_RADIUS;

    b2FixtureDef birdFixture;
    birdFixture.shape = &birdShape;
    birdFixture.density = 1.0f;
    birdFixture.friction = 1.0f;
    birdFixture.restitution = 0.4f;
    birdFixture.userData.pointer = reinterpret_cast<uintptr_t>(GetBird());

    body->CreateFixture(&birdFixture);

    b2BodyDef pigBodyDef;

    pigBodyDef.type = b2_dynamicBody;
    pigBodyDef.position.Set(5.f, 3.f);
    pigBodyDef.linearDamping = 0.5f;

    b2CircleShape pigShape;
    pigShape.m_radius = 0.3f;

    b2Body *pigBody = world_->CreateBody(&pigBodyDef);
    Object *pig_ = new Pig(pigBody, pigShape.m_radius);

    b2FixtureDef pigFixture;
    pigFixture.shape = &pigShape;
    pigFixture.density = 1.0f;
    pigFixture.friction = 1.0f;
    pigFixture.restitution = 0.4f;
    pigFixture.userData.pointer = reinterpret_cast<uintptr_t>(pig_);

    pigBody->CreateFixture(&pigFixture);
    objects_.push_back(pig_);


    b2BodyDef wall_body_def;
    wall_body_def.type = b2_dynamicBody;
    wall_body_def.position.Set(10.f, 5.f);
    wall_body_def.linearDamping = 0.5f;

    b2PolygonShape wall_shape;
    float wall_shape_w = 0.5f;
    float wall_shape_h = 2.5f;
    wall_shape.SetAsBox(wall_shape_w, wall_shape_h);

    b2Body *wall_body = world_->CreateBody(&wall_body_def);
    Object *wall_ = new Wall(wall_body, wall_shape_w, wall_shape_h);

    b2FixtureDef wall_fixture;
    wall_fixture.shape = &wall_shape;
    wall_fixture.density = 1.0f;
    wall_fixture.friction = 0.1f;
    // wall_fixture.restitution = 0.4f;
    wall_fixture.userData.pointer = reinterpret_cast<uintptr_t>(wall_);

    wall_body->CreateFixture(&wall_fixture);
    objects_.push_back(wall_);
}

void Level::ThrowBird(int angle, b2Vec2 velocity)
{
    if (birds_.size() == 0)
    {
        level_ended_ = true;
    }
    if (!IsLevelEnded())
    {
        b2Body *body = GetBird()->GetBody();
        body->SetGravityScale(1);
        body->ApplyLinearImpulseToCenter(velocity, true);
        GetBird()->MakeSound();
        GetBird()->Throw();
    }
}
void Level::ResetBird()
{
    if (birds_.size() > 1)
    {
        birds_.pop_front();
    }
    b2Body *body = GetBird()->GetBody();
    body->SetGravityScale(0);
    body->SetTransform(bird_starting_position_, 0);
}

bool ObjectRemover(Object *obj)
{
    return obj->IsDestroyed();
}

bool Level::DrawLevel(sf::RenderWindow &window)
{

    // Draw slingshot
    sf::RectangleShape peliAlue(sf::Vector2f(1.f * viewwidth, 1.f * viewheight));
    peliAlue.setFillColor(sf::Color::Blue);
    window.draw(peliAlue);

    sf::RectangleShape slingshot(sf::Vector2f(100.0f, 100.0f));
    slingshot.setFillColor(sf::Color::Cyan);
    sf::Vector2f slingshot_center = utils::B2ToSfCoords(bird_starting_position_);
    sf::Texture slingshot_texture;
    slingshot_texture.loadFromFile("../resources/images/slingshot.png");
    slingshot.setTexture(&slingshot_texture);
    slingshot.setOrigin(50, 50);
    slingshot.setPosition(slingshot_center);
    window.draw(slingshot);

    for (b2ContactEdge *ce = GetBird()->GetBody()->GetContactList(); ce; ce = ce->next)
    {

        b2Contact *c = ce->contact;

        Object *objA = reinterpret_cast<Object *>(c->GetFixtureA()->GetUserData().pointer);
        Object *objB = reinterpret_cast<Object *>(c->GetFixtureB()->GetUserData().pointer);

        score_ = score_ + objA->TryToDestroy();
        score_ = score_ + objB->TryToDestroy();
    }

    for (auto ob : objects_)
    {
        if (ob->IsDestroyed())
        {
            world_->DestroyBody(ob->GetBody());
        }
    }

    objects_.remove_if(ObjectRemover);
    if (std::all_of(objects_.begin(), objects_.end(), [](Object *obj)
                    { return !obj->IsDestructable(); }) &&
        !IsLevelEnded())
    {
        level_ended_ = true;
        score_ = score_ + (birds_.size() - 1) * 1000;
    }
    // Draw box2d objects
    bool moving = false;
    for (auto it : objects_)
    {
        b2Body *body = it->GetBody();
        b2Vec2 pos = body->GetPosition();
        sf::Sprite sprite = it->GetSprite();
        sprite.setPosition(utils::B2ToSfCoords(pos));
        window.draw(sprite);
        moving = moving || body->IsAwake();
    }

    b2Body *body = GetBird()->GetBody();
    b2Vec2 pos = body->GetPosition();
    sf::Sprite sprite = GetBird()->GetSprite();
    sprite.setPosition(utils::B2ToSfCoords(pos));
    window.draw(sprite);
    moving = moving || body->IsAwake();
    return moving;
}

std::tuple<float, float> Level::DrawArrow(sf::RenderWindow &window)
{
    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f slingshot_center = utils::B2ToSfCoords(bird_starting_position_);

    sf::Vector2f difference = mouse_position - slingshot_center;

    if (difference.x < 0)
    {
        float direction;
        if (difference.y > 0)
        {
            direction = 90 + utils::RadiansToDegrees(atan(difference.x / difference.y));
        }
        else if (difference.y == 0)
        {
            direction = 0;
        }
        else
        {
            direction = 270 + utils::RadiansToDegrees(atan(difference.x / difference.y));
        }

        float rotation = -direction;

        float length = std::min(sqrt(pow(difference.x, 2) + pow(difference.y, 2)), 100.0);

        sf::RectangleShape line(sf::Vector2f(length, 5));
        line.setFillColor(sf::Color(0, 0, 0));
        line.setPosition(slingshot_center.x, slingshot_center.y);
        line.setRotation(180 + rotation);
        window.draw(line);
        line.setSize(sf::Vector2f(length / 3, 4));
        line.setRotation(150 + rotation);
        window.draw(line);
        line.setRotation(210 + rotation);
        window.draw(line);
        return {direction, length};
    }
    else
    {
        return {0, 0};
    }
}
