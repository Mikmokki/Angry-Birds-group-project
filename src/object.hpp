#ifndef ANGRY_BIRDS_OBJECT
#define ANGRY_BIRDS_OBJECT

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <string>

class Object
{
public:
    Object(std::string texture_file, b2Body *body) : body_(body)
    {
        if (!texture_.loadFromFile(texture_file))
        {
            std::cout << "Texture loading failed" << std::endl; // maybe should throw an error
        }
    };

private:
    sf::Texture texture_;
    b2Body *body_;
};

#endif // ANGRY_BIRDS_OBJECT