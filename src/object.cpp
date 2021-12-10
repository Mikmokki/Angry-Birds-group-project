#include "object.hpp"
#include "utils.hpp"

Object::Object(std::string texture_file, b2Body *body) : body_(body)
{
    texture_.loadFromFile(texture_file);
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
            continue;
        }
        file << fixture->GetDensity() << s << fixture->GetFriction() << s << fixture->GetRestitution() << s;
        fixture = fixture->GetNext();
    }
}

int Object::TryToDestroy(float power)
{
    if (power < 0.01f)
    {
        return 0;
    }
    destruction_threshold_ = destruction_threshold_ - power;
    if (destructable_ && 0.f > destruction_threshold_)
    {
        destroyed = true;
        return destruction_points_;
    }
    return 0;
}
void Object::MakeSound()
{
    punch_sound_buffer_.loadFromFile("resources/sounds/punch.wav");
    punch_sound_.setBuffer(punch_sound_buffer_);
    punch_sound_.setVolume(100);
    punch_sound_.play();
}