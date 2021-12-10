#ifndef ANGRY_BIRDS_BIRD
#define ANGRY_BIRDS_BIRD

#include "object.hpp"
#include <string>
class Bird : public Object
{
public:
    Bird(b2Body *body, std::string texture_file, float b2_radius) : Object(texture_file, body)
    {
        body_ = body;
        int w = sprite_.getTextureRect().width;
        int h = sprite_.getTextureRect().height;

        sprite_.setScale(b2_radius * 2.0f * scale / (1.0f * w), b2_radius * 2.0f * scale / (1.0f * h));

        sprite_.setOrigin(w / 2, h / 2);
    };
    void MakeSound()
    {

        if (!soundBuffer.loadFromFile("resources/sounds/kukko.wav"))
        {
            std::cout << "bird failed to load sound " << std::endl;
            return;
        }

        sound.setBuffer(soundBuffer);
        sound.setVolume(50);
        sound.play();

        std::cout << "tried to make sound " << sound.getStatus() << std::endl;
        return;
    }
    void Throw()
    {
        thrown_ = true;
    }
    bool IsThrown()
    {
        return thrown_;
    }
    void NewPower()
    {
        if (!power_used)
        {
            power_used = true;
            power_left_ = max_power_;
        }
    }
    virtual void UsePower(){};
    virtual char GetType() = 0;

protected:
    const float bird_scale_ = 0.1f; // Maybe could be replaced by levels scale and bodys radius
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    int max_power_ = 20;
    int power_left_ = 0;
    b2Body *body_;
    bool power_used = false;
    bool thrown_ = false;
};

class BoomerangBird : public Bird
{
public:
    BoomerangBird(b2Body *body, float b2_r) : Bird(body, "resources/images/bird.png", b2_r){};
    virtual void UsePower()
    {
        if (power_left_ > 0)
        {
            power_left_--;
            body_->SetAngularVelocity(40);
            body_->SetLinearVelocity(body_->GetLinearVelocity() - b2Vec2(0.5, 0.5));
        }
    };
    virtual char GetType() { return 'B'; };
};

class DroppingBird : public Bird
{
public:
    DroppingBird(b2Body *body, float b2_r) : Bird(body, "resources/images/bird2.png", b2_r){};
    virtual void UsePower()
    {
        if (power_left_ > 0)
        {
            power_left_--;
            body_->SetLinearVelocity(body_->GetLinearVelocity() - b2Vec2(0, 2));
        }
    };
    virtual char GetType() { return 'D'; };
};

class SpeedBird : public Bird
{
public:
    SpeedBird(b2Body *body, float b2_r) : Bird(body, "resources/images/bird3.png", b2_r){};
    virtual void UsePower()
    {
        if (power_left_ >= max_power_ - 2)
        {
            power_left_--;
            body_->SetLinearVelocity(body_->GetLinearVelocity() + body_->GetLinearVelocity());
        }
    };
    virtual char GetType() { return 'S'; };
};

#endif // ANGRY_BIRDS_BIRD
