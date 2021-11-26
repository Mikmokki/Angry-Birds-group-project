#ifndef O_CREATOR
#define O_CREATOR

#include <tuple>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "converter.hpp"

std::tuple<b2Body *, sf::Sprite> CreateWall(b2World *world, int TEXTURE_SCALE, float pos_x, float pos_y)
{
    b2BodyDef wall_body_def;
    wall_body_def.type = b2_dynamicBody;
    wall_body_def.position.Set(pos_x, pos_y);
    b2Body *wall_body = world->CreateBody(&wall_body_def);

    b2PolygonShape wall_shape;
    float wall_w = 1.f;
    float wall_h = 10.f;
    wall_shape.SetAsBox(wall_w, wall_h);

    b2FixtureDef wall_fixture;
    wall_fixture.shape = &wall_shape;
    wall_fixture.density = 10.0f;
    wall_fixture.friction = 10.3f;
    b2MassData wall_mass_data;
    wall_mass_data.mass = 100.0f;
    wall_mass_data.center = b2Vec2(wall_w / 2.0f, wall_h / 2.0f);
    wall_mass_data.I = -20.0f;
    wall_body->SetMassData(&wall_mass_data);
    wall_body->CreateFixture(&wall_fixture);

    sf::Texture wall_texture;
    wall_texture.loadFromFile("../resources/sprites/box");
    sf::Sprite wall;

    wall.setScale(wall_w * TEXTURE_SCALE / (1.0f * wall_texture.getSize().x), wall_h * TEXTURE_SCALE / (1.0f * wall_texture.getSize().y));
    wall.setOrigin(wall_texture.getSize().x / 2.0f, wall_texture.getSize().y / 2.0f);
    wall.setPosition(b2ToSfCoords(wall_body->GetPosition()));
    wall.setRotation(wall_body->GetAngle());
    wall.setTexture(wall_texture);

    return std::make_tuple(wall_body, wall);
}

#endif