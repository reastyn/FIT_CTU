#include "Model/Floor.hpp"

sf::RenderWindow m_window(sf::VideoMode(800, 600), "Debug Draw", sf::Style::Default, sf::ContextSettings{0u, 0u, 4u, 1u, 1u, 0u, false});
DebugDraw debugDraw( &m_window );

namespace RG {
  namespace Model {
    Floor::Floor(unsigned int level, unsigned int rooms, unsigned int pos_X,
        unsigned int pos_Y)
      : m_X(pos_X)
        , m_Y(pos_Y)
        , m_Level(level)
        , m_ScreenHeight(1080)
        , m_ScreenWidth(1920)
        , center_x(-16000)
        , center_y(-16000)
        , size( 100000 )
    {
      m_World = std::make_shared<b2World>(b2Vec2{ 0.0f, 0.0f });

      m_World->SetDebugDraw(&debugDraw);
      debugDraw.SetFlags( b2Draw::e_shapeBit );
      view.reset(sf::FloatRect(center_x, center_y, size, size));

      m_window.setView(view);

      m_WallWidth = 0.076389 * m_ScreenWidth;
      m_WallHeight = 0.1267 * m_ScreenHeight;
      m_DoorWidth = 0.0625 * m_ScreenWidth;
      m_RoomHeight = m_ScreenHeight - 2 * m_WallHeight;
      m_RoomWidth = m_ScreenWidth - 2 * m_WallWidth;

      for (unsigned int i = 0; i < rooms; ++i) {
        RG::Model::Room* tmp_room = new RG::Model::Room(i, 0);
        b2BodyDef* room_bodyDef = new b2BodyDef;
        room_bodyDef->type = b2_dynamicBody;
        room_bodyDef->position.Set(0 * m_ScreenWidth, i * m_ScreenHeight);
        tmp_room->m_Body = m_World->CreateBody(room_bodyDef);

        tmp_room->SetDoors({ !!(i % 2), 0, !(i % 2), 0 }); // FIXME (vanda)
        tmp_room->AddWalls(m_ScreenWidth, m_ScreenHeight, m_DoorWidth,
            m_WallWidth, m_WallHeight);

        m_Rooms.insert({ 0, { { i, tmp_room } } }); // FIXME (vanda)
      }
    }

    Floor::~Floor() {}

    unsigned int Floor::GetLevel(void) const { return m_Level; }

    const RG::Model::Room& Floor::GetRoom(void) const
    {
      auto it_row = m_Rooms.find(m_X);
      auto it_col = it_row->second.find(m_Y);
      return *(it_col->second);
    }

    b2Body* Floor::GetPlayerBody(b2BodyDef* bodyDef)
    {
      return m_World->CreateBody(bodyDef);
    }

    void Floor::Step(float time_step)
    {
      m_window.clear({0,0,0,255});
      this->m_World->Step(time_step, 8, 3);
      this->m_World->ClearForces();
      sf::Event event;
      while(m_window.pollEvent(event))
      {
          if (event.type == sf::Event::KeyPressed)
          {
              if (event.key.code == sf::Keyboard::Left) {
                  center_x += 1000;
              }
              if (event.key.code == sf::Keyboard::Right) {
                  center_x -= 1000;
              }
              if (event.key.code == sf::Keyboard::Down) {
                  center_y -= 1000;
              }
              if (event.key.code == sf::Keyboard::Up) {
                  center_y += 1000;
              }
              if (event.key.code == sf::Keyboard::Add) {
                  size *= 1.5;
              }
              if (event.key.code == sf::Keyboard::Subtract) {
                  size /= 1.5;
              }
          }
      }
      view.setCenter( center_x, center_y );
      view.setSize( size, size );
      m_window.setView( view );
      m_World->DrawDebugData();
      m_window.display();
    }

    void Floor::UpdateID(b2Vec2 v)
    {
      m_X = (v.x - m_WallWidth) / m_RoomWidth;
      m_Y = (v.y - m_WallHeight) / m_RoomHeight;
    }
  }
}
