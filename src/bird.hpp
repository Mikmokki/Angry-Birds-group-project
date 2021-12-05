#ifndef ANGRY_BIRDS_BIRD
#define ANGRY_BIRDS_BIRD

#include "object.hpp"
#include <string>
class Bird : public Object
{
public:
    Bird(b2Body *body, std::string texture_file) : Object(texture_file, body)
    {
        sprite_.setScale(bird_scale_, bird_scale_);
        body_ = body;
        int h = sprite_.getTextureRect().height;
        int w = sprite_.getTextureRect().width;

        sprite_.setOrigin(h * bird_scale_ / 2, w * bird_scale_ / 2); // Set origin to center
    };
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

protected:
    const float bird_scale_ = 0.1f; // Maybe could be replaced by levels scale and bodys radius
    int max_power_ = 20;
    int power_left_ = 0;
    b2Body *body_;
    bool power_used = false;
    bool thrown_ = false;
};

class BoomerangBird : public Bird
{
public:
    BoomerangBird(b2Body *body) : Bird(body, "../resources/images/bird.png"){};
    virtual void UsePower()
    {
        if (power_left_ > 0)
        {
            power_left_--;
            body_->SetAngularVelocity(40);
            body_->SetLinearVelocity(body_->GetLinearVelocity() - b2Vec2(0.5, 0.5));
        }
    };
};
class DroppingBird : public Bird
{
public:
    DroppingBird(b2Body *body) : Bird(body, "../resources/images/bird2.png"){};
    virtual void UsePower()
    {
        if (power_left_ > 0)
        {
            power_left_--;
            body_->SetLinearVelocity(body_->GetLinearVelocity() - b2Vec2(0, 2));
        }
    };
};

class SpeedBird : public Bird
{
public:
    SpeedBird(b2Body *body) : Bird(body, "../resources/images/bird3.png"){};
    virtual void UsePower()
    {
        if (power_left_ >= max_power_ - 2)
        {
            power_left_--;
            body_->SetLinearVelocity(body_->GetLinearVelocity() + body_->GetLinearVelocity());
        }
    };
};

#endif // ANGRY_BIRDS_BIRD