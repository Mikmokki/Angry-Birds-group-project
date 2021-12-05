#include "utils.hpp"

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

std::ostream &operator<<(std::ostream &output, const b2Vec2 &vector)
{
    output << "(" << vector.x << ":" << vector.y << ")";
    return output;
}
