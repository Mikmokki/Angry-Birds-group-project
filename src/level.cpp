#include "level.hpp"
#include "pig.hpp"
#include "ground.hpp"
#include "utils.hpp"
#include <algorithm>
#include <iostream>

Level::Level() : name_("") {}

Level::Level(std::string name) : name_(name)
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
    groundBox.SetAsBox(50.0f, 1.0f);

    b2FixtureDef def;
    def.shape = &groundBox;
    def.density = 0.0f;

    def.userData.pointer = reinterpret_cast<uintptr_t>(gObj);
    groundBody->CreateFixture(&def);

    // Create the bird object
    b2BodyDef birdDef;
    birdDef.type = b2_dynamicBody;
    birdDef.position = bird_starting_position;
    birdDef.linearDamping = 0.5f; // This could be constant and should be adjusted
    birdDef.gravityScale = 0;     // Set gravity scale initially to zero so bird floats on slingshot

    b2Body *body = world_->CreateBody(&birdDef);
    Bird *bird1 = new BoomerangBird(body);
    Bird *bird2 = new DroppingBird(body);
    Bird *bird3 = new SpeedBird(body);
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

Level::Level(std::ifstream &file)
{
    if (file.rdstate() & (file.failbit | file.badbit))
    {
        std::cerr << "Failed" << std::endl; // output error to stderr stream
    }
    else
    {
        // Read level name from the first line
        if (!file.eof())
        {
            std::string name;
            std::getline(file, name);
            name_ = name;
        }

        // Get bird list from second line
        std::string bird_list;
        std::getline(file, bird_list);

        world_ = new b2World(gravity);

        while (!file.eof())
        {
            char obj_type;
            file.get(obj_type);
            file.ignore(); // Ignore the following separator

            char _; // character dump
            // Read the body definition
            b2BodyDef body_def;

            file >> body_def.position >> _ >> body_def.angle >> _ >> body_def.angularVelocity >> _ >> body_def.linearVelocity >> _ >> body_def.angularDamping >> _ >> body_def.linearDamping >> _ >> body_def.gravityScale >> _ >> body_def.type >> _ >> body_def.awake >> _;

            b2Body *body = world_->CreateBody(&body_def);

            std::string fixture_str;
            // Read fixtures
            std::getline(file, fixture_str, '\n');
            std::stringstream fixture(fixture_str);
            b2FixtureDef fixture_def;

            int shape_type;
            fixture >> shape_type >> _;
            // The shapes need to live in the outer scope here so the fixture can see them
            b2CircleShape circle;
            b2PolygonShape polygon;
            switch (shape_type)
            {
            case b2Shape::Type::e_circle:
            {
                fixture >> circle.m_p >> _ >> circle.m_radius >> _;
                fixture_def.shape = &circle;
                break;
            }
            case b2Shape::Type::e_polygon:
            {
                fixture >> polygon.m_centroid >> _;

                for (int i = 0; i < 8; i++)
                {
                    b2Vec2 vertex;
                    fixture >> vertex >> _;
                    polygon.m_vertices[i] = vertex; // Update array in place since c++ only supports array copying with memcpy
                }
                for (int i = 0; i < 8; i++)
                {
                    b2Vec2 normal;
                    fixture >> normal >> _;
                    polygon.m_normals[i] = normal;
                }

                fixture >> polygon.m_count >> _ >> polygon.m_radius >> _;

                fixture_def.shape = &polygon;
                break;
            }
            default:
                std::cerr << "Reading Level file failed, unknown shape on a fixture" << std::endl;
                break;
            }

            fixture >> fixture_def.density >> _ >> fixture_def.friction >> _ >> fixture_def.restitution >> _;

            switch (obj_type)
            {
            case 'B':
            case 'D':
            case 'S':
            {
                for (auto type : bird_list)
                {
                    Bird *bird;
                    switch (type)
                    {
                    case 'B':
                        bird = new BoomerangBird(body);
                        break;
                    case 'D':
                        bird = new DroppingBird(body);
                        break;
                    case 'S':
                        bird = new SpeedBird(body);
                        break;
                    default:
                        // Unknown bird
                        continue;
                    }
                    birds_.push_back(bird);
                    fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(bird);
                }
                break;
            }
            case 'G':
            {
                Ground *g = new Ground(body);
                fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(g);
                objects_.push_back(g);
                break;
            }
            case 'P':
            {
                Pig *p = new Pig(body);
                fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(p);
                objects_.push_back(p);
                break;
            }
            default:
                // Unknown type skip row
                continue;
            }

            body->CreateFixture(&fixture_def);
        }
    }
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
    body->SetTransform(bird_starting_position, 0);
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
    sf::Vector2f slingshot_center = utils::B2ToSfCoords(bird_starting_position);
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
    sf::Vector2f slingshot_center = utils::B2ToSfCoords(bird_starting_position);

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

void Level::SaveState(std::ofstream &file)
{
    // Write level name to first line
    file << name_ << std::endl;
    // Save available birds on the second line
    for (auto bird : birds_)
    {
        file << bird->GetType();
    }
    file << std::endl;
    // Save bird to second line
    GetBird()->SaveState(file);
    file << std::endl;
    // Then save all the other objects
    for (auto obj : objects_)
    {
        obj->SaveState(file);
        file << std::endl;
    }
}