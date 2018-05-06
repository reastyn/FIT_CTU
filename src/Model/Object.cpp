#include "Model/Object.hpp"

namespace RG {
  namespace Model {
    Object::Object(b2BodyDef* body, std::string name)
      : m_Body(NULL)
        , m_BodyDef(body)
        , m_Name(name)
    {
    }

    Object::~Object() {}

    std::string Object::GetName(void) const { return m_Name; }

    b2Vec2 Object::GetPosition(void) const
    {
      return m_Body ? m_Body->GetPosition() : b2Vec2(0, 0);
    }

    float Object::GetAngle(void) const { return m_Body ? m_Body->GetAngle() : 0; }

    void Object::AddShape(b2Shape* shapeDef)
    {
      // Define the dynamic body fixture.
      b2FixtureDef fixtureDef;
      fixtureDef.shape = shapeDef;

      // Set the box density to be non-zero, so it will be dynamic.
      fixtureDef.density = 1.0f;

      // Override the default friction.
      fixtureDef.friction = 0.8f;

      // Add the shape to the body.
      m_Body->CreateFixture(&fixtureDef);
    }
  }
}
