#ifndef ANGRY_BIRDS_OBJECT
#define ANGRY_BIRDS_OBJECT

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <fstream>
#include <string>
#include "converters.hpp"

class Object
{
public:
    Object(std::string texture_file, b2Body *body);

    Object(b2Body *body);

    virtual ~Object() {}

    b2Body *GetBody() { return body_; }

    sf::Sprite &GetSprite() { return sprite_; }

    bool IsDestructable() { return destructable_; }

    virtual void UsePower(){};

    float GetDThreshold() { return destruction_threshold_; }

    bool IsDestroyed() const { return destroyed; }

    virtual int TryToDestroy(float power);

    void SaveState(std::ofstream &file);

    // Get type of the object (for serialization purposes)
    virtual char GetType() = 0;

    void MakeSound();

protected:
    sf::Sprite sprite_;
    sf::Texture texture_;
    bool destructable_ = false;
    float destruction_threshold_ = 0.f;
    int destruction_points_ = 20;
    sf::SoundBuffer punch_sound_buffer_;
    sf::Sound punch_sound_;

private:
    b2Body *body_;
    bool destroyed = false;
};

#endif // ANGRY_BIRDS_OBJECT