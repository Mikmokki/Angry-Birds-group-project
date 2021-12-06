#ifndef ANGRY_BIRDS_OBJECT
#define ANGRY_BIRDS_OBJECT

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <string>
#include "converters.hpp"

class Object
{
public:
    Object(std::string texture_file, b2Body *body) : body_(body)
    {
        if (!texture_.loadFromFile(texture_file))
        {
            std::cout << "Texture loading failed" << std::endl; // maybe should throw an error
        }
        sprite_.setTexture(texture_);
    };

    Object(b2Body *body) : body_(body){};

    virtual ~Object() {}

    b2Body *GetBody() { return body_; }

    sf::Sprite &GetSprite() { return sprite_; }

    bool IsDestructable() { return destructable_; }

    virtual void UsePower(){};

    float GetDThreshold() { return destruction_threshold_; }

    bool IsDestroyed() const { return destroyed; }

    int TryToDestroy()
    {
        if (destructable_)
        {
            destroyed = true;
            return destruction_points_;
        }
        return 0;
    }

    void MakeSound() { return; }

protected:
    sf::Sprite sprite_;
    sf::Texture texture_;
    bool destructable_ = false;
    float destruction_threshold_ = 0;
    int destruction_points_ = 100;

private:
    b2Body *body_;
    bool destroyed = false;
};

#endif // ANGRY_BIRDS_OBJECT