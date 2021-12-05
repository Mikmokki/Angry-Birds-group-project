#include "level.hpp"
#include "bird.hpp"
#include "pig.hpp"
#include "ground.hpp"
#include <algorithm>
#include "math.h"

#define M_PI 3.14159265358979323846f

Level::Level() : name_(""), bird_starting_position_(b2Vec2(0, 0)) {}

Level::Level(std::string name, b2Vec2 bird_starting_pos) : name_(name), bird_starting_position_(bird_starting_pos)
{
    world_ = new b2World(gravity);
    // Creating ground box
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body *groundBody = world_->CreateBody(&groundBodyDef);

    Object *gObj = new Ground(groundBody);

    groundBodyDef.userData;
    objects_.push_back(gObj);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    b2FixtureDef def;
    def.shape = &groundBox;
    def.density = 0.0f;
    def.userData.pointer = reinterpret_cast<uintptr_t>(gObj);
    groundBody->CreateFixture(&def);

    // Create the bird object
    b2BodyDef birdDef;
    birdDef.type = b2_dynamicBody;
    birdDef.position = bird_starting_position_;
    birdDef.linearDamping = 0.5f; // This could be constant and should be adjusted
    birdDef.gravityScale = 0;     // Set gravity scale initially to zero so bird floats on slingshot

    b2Body *body = world_->CreateBody(&birdDef);
    Bird *bird1 = new BoomerangBird(body);
    Bird *bird2 = new SpeedBird(body);
    Bird *bird3 = new DroppingBird(body);
    birds_.push_back(bird1);
    birds_.push_back(bird2);
    birds_.push_back(bird3);

    b2CircleShape birdShape;
    birdShape.m_radius = 0.3f;

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

    b2Body *pigBody = world_->CreateBody(&pigBodyDef);
    Object *pig_ = new Pig(pigBody);

    b2CircleShape pigShape;
    pigShape.m_radius = 0.3f;

    b2FixtureDef pigFixture;
    pigFixture.shape = &pigShape;
    pigFixture.density = 1.0f;
    pigFixture.friction = 1.0f;
    pigFixture.restitution = 0.4f;
    pigFixture.userData.pointer = reinterpret_cast<uintptr_t>(pig_);

    pigBody->CreateFixture(&pigFixture);
    objects_.push_back(pig_);
}

void Level::ThrowBird(int angle, b2Vec2 velocity)
{
    // if (birds_.size() == 0)
    // {
    //     level_ended_ = true;
    // }
    // if (!IsLevelEnded())
    // {
    b2Body *body = GetBird()->GetBody();
    body->SetGravityScale(1);
    body->ApplyLinearImpulseToCenter(velocity, true);
    GetBird()->Throw();
    // }
}
bool level_set_up = false; // at the beginning ResetBird is called once when level is ready.
void Level::ResetBird()
{
    // if (birds_.size() == 0)
    // {
    //     level_ended_ = true;
    // }
    // else
    // {
    if (level_set_up)
    {
        birds_.pop_front();
    }
    else
    {
        level_set_up = true;
    }
    if (birds_.size() > 0)
    {
        b2Body *body = GetBird()->GetBody();
        body->SetGravityScale(0);
        body->SetTransform(bird_starting_position_, 0);
    }
    // }
}

sf::Vector2f toSFVector(b2Vec2 original)
{
    return sf::Vector2f(original.x * scale, 800 - (original.y * scale));
}

b2Vec2 toB2Vector(sf::Vector2f original)
{
    return b2Vec2(original.x / scale, 900 - (original.y / scale));
}
bool ObjectRemover(Object *obj)
{
    return obj->IsDestroyed();
}

bool Level::DrawLevel(sf::RenderWindow &window)
{
    // if (birds_.size() == 0)
    // {
    //     level_ended_ = true;
    // }
    // if (!level_ended_)
    // {
    // Draw slingshot
    sf::RectangleShape slingshot(sf::Vector2f(100.0f, 100.0f));
    sf::Vector2f slingshot_center = toSFVector(bird_starting_position_);
    sf::Texture slingshot_texture;
    slingshot_texture.loadFromFile("../resources/images/slingshot.png");
    slingshot.setTexture(&slingshot_texture);
    slingshot.setOrigin(50, 50);
    slingshot.setPosition(slingshot_center);
    window.draw(slingshot);

    for (b2ContactEdge *ce = GetBird()->GetBody()->GetContactList(); ce; ce = ce->next)
    {

        b2Contact *c = ce->contact;

        c->GetFixtureA();

        Object *objA = reinterpret_cast<Object *>(c->GetFixtureA()->GetUserData().pointer);
        Object *objB = reinterpret_cast<Object *>(c->GetFixtureB()->GetUserData().pointer);

        std::cout << GetScore() << std::endl;
        score_ = score_ + objA->TryToDestroy();
        std::cout << GetScore() << std::endl;
        score_ = score_ + objB->TryToDestroy();
        std::cout << GetScore() << std::endl;
    }

    /* for (b2Body *bPtr = world_->GetBodyList(); bPtr; bPtr = bPtr++)
    {
        Object *obj = reinterpret_cast<Object *>(bPtr->GetFixtureList()->GetUserData().pointer);

        if (obj->IsDestroyed())
        {
            world_->DestroyBody(bPtr);
        }
    } */

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
        score_ = score_ + (birds_.size()-1) * 1000;
    }
    // Draw box2d objects
    bool moving = false;
    for (auto it : objects_)
    {
        b2Body *body = it->GetBody();
        b2Vec2 pos = body->GetPosition();
        sf::Sprite sprite = it->GetSprite();
        sprite.setPosition(toSFVector(pos));
        window.draw(sprite);
        moving = moving || body->IsAwake();
    }

    // Draw bird
    // if (!IsLevelEnded())
    // {
    b2Body *body = GetBird()->GetBody();
    b2Vec2 pos = body->GetPosition();
    sf::Sprite sprite = GetBird()->GetSprite();
    sprite.setPosition(toSFVector(pos));
    window.draw(sprite);
    moving = moving || body->IsAwake();
    // }
    return moving;
    // }
    // else
    //     return false;
}

std::tuple<float, float> Level::DrawArrow(sf::RenderWindow &window)
{
    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f slingshot_center = toSFVector(bird_starting_position_);

    sf::Vector2f difference = mouse_position - slingshot_center;

    if (difference.x < 0)
    {
        float direction;
        if (difference.y > 0)
        {
            direction = 90 + atan(difference.x / difference.y) * 180 / M_PI; // Tämä kans convertteriks
        }
        else if (difference.y == 0)
        {
            direction = 0;
        }
        else
        {
            direction = 270 + atan(difference.x / difference.y) * 180 / M_PI;
        }

        float rotation = -direction;

        float length = std::min(sqrt(pow(difference.x, 2) + pow(difference.y, 2)), static_cast<double>(100.0));

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
