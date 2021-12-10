#include "level.hpp"
#include "pig.hpp"
#include "ground.hpp"
#include "utils.hpp"
#include "wall.hpp"
#include <algorithm>
#include <iostream>

Level::Level() : name_("") {}

Level::Level(std::string name) : name_(name)
{

    std::list<int> high_scores(1290); // should be read from the file
    high_scores_ = high_scores;
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
    birdDef.position = bird_starting_position;
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
std::vector<int> Level::CountBirdTypes()
{
    int boomerang_count = 0;
    int dropping_count = 0;
    int speed_count = 0;
    for (const auto &bird : birds_)
    {
        if (BoomerangBird *v = dynamic_cast<BoomerangBird *>(bird))
        {
            boomerang_count++;
        }
        if (DroppingBird *v = dynamic_cast<DroppingBird *>(bird))
        {
            dropping_count++;
        }
        if (SpeedBird *v = dynamic_cast<SpeedBird *>(bird))
        {
            speed_count++;
        }
    }
    std::vector<int> counts{boomerang_count, dropping_count, speed_count};
    return counts;
}

int Level::CountPigs()
{
    int pig_count = 0;
    for (const auto &obj : objects_)
    {
        if (Pig *v = dynamic_cast<Pig *>(obj))
        {
            pig_count++;
        }
    }
    return pig_count;
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
        level_number_ = std::stoi(name_.substr(5, name_.size() - 3));
        // Read highscores from second line
        std::string high_scores_string;
        std::getline(file, high_scores_string);
        std::stringstream hs_ss(high_scores_string);

        std::list<int> high_scores;
        std::string high_score;
        std::getline(hs_ss, high_score, ';');
        while (hs_ss.good())
        {
            high_scores.push_back(std::stoi(high_score));
            std::getline(hs_ss, high_score, ';');
        }

        high_scores_ = high_scores;

        // Read bird list from third line
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
                        bird = new BoomerangBird(body, fixture_def.shape->m_radius);
                        break;
                    case 'D':
                        bird = new DroppingBird(body, fixture_def.shape->m_radius);
                        break;
                    case 'S':
                        bird = new SpeedBird(body, fixture_def.shape->m_radius);
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
                Pig *p = new Pig(body, fixture_def.shape->m_radius);
                fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(p);
                objects_.push_back(p);
                break;
            }
            case 'W':
            {
                b2Vec2 dimensions = utils::DimensionsFromPolygon(static_cast<const b2PolygonShape *>(fixture_def.shape));
                Wall *w = new Wall(body, dimensions.x, dimensions.y);
                fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(w);
                objects_.push_back(w);
                break;
            }
            default:
                // Unknown type skip row
                continue;
            }

            body->CreateFixture(&fixture_def);
        }
        for (int i = 1; i < 4; i++)
        {
            star_tresholds_.push_back(((birds_.size() - CountPigs()) * 1000 + CountPigs() * 500) / i);
        }
    }
}

void Level::ThrowBird(int angle, b2Vec2 velocity)
{
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
    if (birds_.front()->IsThrown())
    {
        level_ended_ = true;
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
        sprite.setRotation(utils::RadiansToDegrees(body->GetAngle()) * -1.0f);
        window.draw(sprite);
        moving = moving || body->IsAwake();
    }

    b2Body *body = GetBird()->GetBody();
    b2Vec2 pos = body->GetPosition();
    sf::Sprite sprite = GetBird()->GetSprite();
    sprite.setPosition(utils::B2ToSfCoords(pos));
    sprite.setRotation(utils::RadiansToDegrees(-body->GetAngle()));
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
    // Write highscores on second line
    for (auto high_score : high_scores_)
    {
        file << high_score << ";";
    }
    file << std::endl;
    // Write available birds on the third line
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

int Level::GetHighScore()
{
    high_scores_.sort();
    high_scores_.reverse();
    int high_score = high_scores_.front();
    return high_score;
}

std::list<int> Level::UpdateHighScore()
{
    high_scores_.sort();
    if (high_scores_.size() > 10)
    {
        auto it = high_scores_.begin();
        while (it != high_scores_.end())
        {
            if (score_ > *it)
            {
                (*it) = score_;
                break;
            }
            it++;
        }
    }
    else
    {
        high_scores_.push_back(score_);
    }
    return high_scores_;
}