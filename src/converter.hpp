#ifndef ANGRY_BIRDS_SF_B2_CONVERTER
#define ANGRY_BIRDS_SF_B2_CONVERTER
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

const float playAreaHeightInSf = 1600.f;
const float pixelsPerMeter = 30.f;

sf::Vector2f b2ToSfCoords(const b2Vec2 b2Vektori)
{
    return sf::Vector2f(pixelsPerMeter * b2Vektori.x, playAreaHeightInSf - (pixelsPerMeter * b2Vektori.y));
}
b2Vec2 sfToB2Coords(const sf::Vector2f sfVektori)
{
    return b2Vec2(sfVektori.x / pixelsPerMeter, (playAreaHeightInSf - sfVektori.y) / pixelsPerMeter);
}

#endif
