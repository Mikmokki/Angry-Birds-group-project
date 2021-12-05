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

namespace utils
{
    // Tries to open a file with the provided filename+suffix
    // If there is a file with the name it adds seq number to the filename
    // for example "filename(0).ab"
    std::ofstream OpenFileSafe(const std::string filename)
    {
        std::stringstream full_filename;
        full_filename << filename << "." << file_suffix;

        std::ifstream file(full_filename.str());
        int sequence_number = 0;
        while (file.good())
        {
            full_filename.clear();
            full_filename.str(""); // Empty the stringstream
            full_filename << filename << "(" << sequence_number << ")." << file_suffix;
            file = std::ifstream(full_filename.str());
            sequence_number++;
        }

        return std::ofstream(full_filename.str());
    }
}