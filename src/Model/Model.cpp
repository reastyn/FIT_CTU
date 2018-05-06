#include "Model/Model.hpp"

namespace RG {
  namespace Model {
    Model::Model()
      : m_CurrentFloorIdx(0)
    {
      m_Floors.push_back(
          RG::Model::Floor(0, 2,0,0)); // FIXME(vanda, replace by world generation)

      // adding the player
      b2BodyDef* bodyDef = new b2BodyDef;
      bodyDef->type = b2_dynamicBody;
      bodyDef->position.Set(0, 0);
      m_Player = std::make_shared<RG::Model::Entity>("Hrac");
      m_Player->m_Body = m_Floors[m_CurrentFloorIdx].GetPlayerBody(bodyDef);
      b2CircleShape* circle = new b2CircleShape;
      circle->m_p.Set(0,0);
      circle->m_radius = 10;
      m_Player->AddShape(circle);
    }

    Model::~Model() {}

    void Model::Move(float x, float y) { m_Player->Move(b2Vec2(x, y)); }

    const RG::Model::Room& Model::GetCurrentRoom(void) const
    {
      return m_Floors[m_CurrentFloorIdx].GetRoom();
    }

    std::pair<float, float> Model::GetPlayerPosition(void) const
    {
      return std::pair<float, float>{m_Player->GetPosition().x, m_Player->GetPosition().y};
    }

    float Model::GetPlayerRotation(void) const
    {
      return m_Player->GetAngle() * 180 / M_PI;
    }

    float Model::GetPlayerRadius(void) const
    {
      return 0; // FIXME (vanda)
    }

    int Model::GetRoomId(void) const
    {
      return 0; // TODO (vanda)
    }

    int Model::GetFloorLevel(void) const { return m_CurrentFloorIdx; }

    std::vector<bool> Model::GetRoomDoors(int floorID) const
    { 
      // TODO FIXME (vanda)
      // dummy return
      std::vector<bool> dummy;
      for (int i = 0; i < 4; i++) {
        dummy.push_back(true);
      }
      return dummy;
    }
    
    void Model::Step(float time_step) {
      this->m_Floors[this->m_CurrentFloorIdx].Step(time_step);
    }
  }
}
