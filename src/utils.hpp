#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <box2d/box2d.h>
#include "converters.hpp"

std::istream &operator>>(std::istream &input, b2Vec2 &vector);

std::istream &operator>>(std::istream &input, b2BodyType &type);

std::ostream &operator<<(std::ostream &output, const b2Vec2 &vector);

namespace utils
{
    std::ofstream OpenFileSafe(const std::string filename);
}