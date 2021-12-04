#ifndef ANGRY_BIRDS_OBJECT
#define ANGRY_BIRDS_OBJECT

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <fstream>
#include <string>

class Object
{
public:
    Object(std::string texture_file, b2Body *body);

    Object(b2Body *body);

    b2Body *GetBody() { return body_; }

    sf::Sprite &GetSprite() { return sprite_; }

    bool IsDestructable() { return destructable_; }

    float GetDThreshold() { return destructionThreshold; }

    bool IsDestroyed() const { return destroyed; }

    void TryToDestroy()
    {
        if (destructable_)
            destroyed = true;
    }

    void SaveState(std::ofstream &file);

    // Get type of the object (for serialization purposes)
    virtual char GetType() = 0;

protected:
    sf::Sprite sprite_;
    sf::Texture texture_;
    bool destructable_ = false;
    float destructionThreshold = 0;

private:
    b2Body *body_;
    bool destroyed = false;
};

#endif // ANGRY_BIRDS_OBJECT