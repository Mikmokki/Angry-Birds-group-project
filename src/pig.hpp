#ifndef ANGRY_BIRDS_PIG
#define ANGRY_BIRDS_PIG

#include "object.hpp"

class Pig : public Object
{
public:
    Pig(b2Body *body, float b2_radius) : Object("resources/images/pig.png", body)
    {
        int w = sprite_.getTextureRect().width;
        int h = sprite_.getTextureRect().height;

        sprite_.setScale(b2_radius * 2.0f * scale / (1.0f * w), b2_radius * 2.0f * scale / (1.0f * h));
        sprite_.setOrigin(w / 2.f, h / 2.f);
        destruction_points_ = 500;
        destructable_ = true;
        destruction_threshold_ = 100.0f;
    };

    virtual char GetType() { return 'P'; };
    void MakeSound()
    {
        punch_sound_buffer_.loadFromFile("resources/sounds/punch.wav");
        punch_sound_.setBuffer(punch_sound_buffer_);
        punch_sound_.setVolume(20);
        pig_sound_buffer_.loadFromFile("resources/sounds/pig.wav");
        pig_sound_.setBuffer(pig_sound_buffer_);
        pig_sound_.setVolume(20);
        punch_sound_.play();
        pig_sound_.play();
    }

private:
    sf::SoundBuffer pig_sound_buffer_;
    sf::Sound pig_sound_;
};

#endif // ANGRY_BIRDS_PIG