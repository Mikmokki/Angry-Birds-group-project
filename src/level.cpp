#include "level.hpp"
#include "pig.hpp"
#include "ground.hpp"

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
    bird_ = new Bird(body);

    b2CircleShape birdShape;
    birdShape.m_radius = 0.3f;

    b2FixtureDef birdFixture;
    birdFixture.shape = &birdShape;
    birdFixture.density = 1.0f;
    birdFixture.friction = 1.0f;
    birdFixture.restitution = 0.4f;
    birdFixture.userData.pointer = reinterpret_cast<uintptr_t>(bird_);

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

std::istream &operator>>(std::istream &input, b2Vec2 &vector)
{
    float x, y;
    char _;
    input.ignore();       // Ingnore "("
    input >> x >> _ >> y; // Read the coordinates
    if (input)
    {
        vector.Set(x, y);
    }
    else
    {
        input.clear((input.rdstate() & ~std::ios::goodbit) | std::ios::failbit);
    }

    input.ignore(); // Ignore ")"

    return input;
}

std::istream &operator>>(std::istream &input, b2BodyType &type)
{
    int body_type;
    input >> body_type;
    if (input)
    {
        switch (body_type)
        {
        case 0:
            type = b2_staticBody;
            break;
        case 1:
            type = b2_kinematicBody;
            break;
        case 2:
            type = b2_dynamicBody;
            break;
        }
    }
    else
    {
        input.clear((input.rdstate() & ~std::ios::goodbit) | std::ios::failbit);
    }

    return input;
}

Level::Level(std::ifstream &file)
{
    if (file.rdstate() & (file.failbit | file.badbit))
    {
        // output error to stderr stream
        std::cerr
            << "Failed" << std::endl;
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

        world_ = new b2World(gravity);
        bird_starting_position_ = b2Vec2(3, 3); // This might get removed

        // repeat until end of file
        while (!file.eof())
        {
            // read a line from file
            std::string l;
            std::getline(file, l);
            std::stringstream line(l);

            char obj_type;
            file.get(obj_type);
            file.ignore(); // Ignore the following separator

            char _; // character dump
            // Read the body definition
            b2BodyDef body_def;

            b2Vec2 position, linear_velocity;
            b2BodyType body_type;
            float angle, angular_velocity, angular_damping, linear_damping, gravity_scale;
            bool is_awake;
            file >> position >> _ >> angle >> _ >> angular_velocity >> _ >> linear_velocity >> _ >> angular_damping >> _ >> linear_damping >> _ >> gravity_scale >> _ >> body_type >> _ >> is_awake >> _;

            body_def.position = position;
            body_def.angle = angle;
            body_def.angularVelocity = angular_velocity;
            body_def.linearVelocity = linear_velocity;
            body_def.angularDamping = angular_damping;
            body_def.linearDamping = linear_damping;
            body_def.gravityScale = gravity_scale;
            body_def.type = body_type;
            body_def.awake = is_awake;

            std::string tmp;
            // Read fixtures
            std::getline(file, tmp, '\n');
            std::cout << "tmp" << tmp << std::endl;

            switch (obj_type)
            {
            case 'B':
                break;
            case 'G':
                break;
            case 'P':
                break;
            default:
                // Unknown type skip row
                continue;
            }

            std::cout << line.str() << std::endl;
        }
    }
}

void Level::ThrowBird(int angle, b2Vec2 velocity)
{
    b2Body *body = bird_->GetBody();
    body->SetGravityScale(1);
    body->ApplyLinearImpulseToCenter(velocity, true);
}

void Level::ResetBird()
{
    b2Body *body = bird_->GetBody();
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
    sf::RectangleShape slingshot(sf::Vector2f(100.0f, 100.0f));
    sf::Vector2f slingshot_center = utils::B2ToSfCoords(bird_starting_position_);
    sf::Texture slingshot_texture;
    slingshot_texture.loadFromFile("../resources/images/slingshot.png");
    slingshot.setTexture(&slingshot_texture);
    slingshot.setOrigin(50, 50);
    slingshot.setPosition(slingshot_center);
    window.draw(slingshot);

    for (b2ContactEdge *ce = bird_->GetBody()->GetContactList(); ce; ce = ce->next)
    {

        b2Contact *c = ce->contact;

        c->GetFixtureA();

        Object *objA = reinterpret_cast<Object *>(c->GetFixtureA()->GetUserData().pointer);
        Object *objB = reinterpret_cast<Object *>(c->GetFixtureB()->GetUserData().pointer);

        objA->TryToDestroy();
        objB->TryToDestroy();
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

    // Draw bird
    b2Body *body = bird_->GetBody();
    b2Vec2 pos = body->GetPosition();
    sf::Sprite sprite = bird_->GetSprite();
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

void Level::SaveState(std::ofstream &file)
{
    // Write level name to first line
    file << name_ << std::endl;
    // Save bird to second line
    bird_->SaveState(file);
    file << std::endl;
    // Then save all the other objects
    for (auto obj : objects_)
    {
        obj->SaveState(file);
        file << std::endl;
    }
}