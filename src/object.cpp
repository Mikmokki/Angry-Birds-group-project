#include "object.hpp"
#include "utils.hpp"

Object::Object(std::string texture_file, b2Body *body) : body_(body)
{
    if (!texture_.loadFromFile(texture_file))
    {
        std::cout << "Texture loading failed" << std::endl; // maybe should throw an error
    }
    sprite_.setTexture(texture_);
}

Object::Object(b2Body *body) : body_(body){};

void Object::SaveState(std::ofstream &file)
{
    const char s = ';'; // separator
    file << GetType() << s;
    // first save all box2d attributes
    file << body_->GetPosition() << s << body_->GetAngle() << s
         << body_->GetAngularVelocity() << s << body_->GetLinearVelocity() << s
         << body_->GetAngularDamping() << s << body_->GetLinearDamping() << s
         << body_->GetGravityScale() << s << body_->GetType() << s
         << body_->IsAwake() << s;

    b2Fixture *fixture = body_->GetFixtureList();
    while (fixture != nullptr)
    {
        b2Shape::Type shape_type = fixture->GetType();
        b2Shape *shape_data = fixture->GetShape();
        file << shape_type << s;
        switch (shape_type)
        {
        case b2Shape::Type::e_circle:
            b2CircleShape *circle;
            circle = static_cast<b2CircleShape *>(shape_data);
            file << circle->m_p << s << circle->m_radius << s;
            break;
        case b2Shape::Type::e_polygon:
            b2PolygonShape *polygon;
            polygon = static_cast<b2PolygonShape *>(shape_data);
            file << polygon->m_centroid << s;
            for (auto vertex : polygon->m_vertices)
            {
                file << vertex << s;
            }
            for (auto normal : polygon->m_normals)
            {
                file << normal << s;
            }
            file << polygon->m_count << s << polygon->m_radius << s;
            break;
        default:
            std::cout << "Unknown type for shape" << std::endl;
            continue;
        }
        file << fixture->GetDensity() << s << fixture->GetFriction() << s << fixture->GetRestitution() << s;
        fixture = fixture->GetNext();
    }
}