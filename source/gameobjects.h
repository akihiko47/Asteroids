#include "gameobject.h"
#include <iostream>


class Player : public GameObject
{
public:
    Player(Window *parent, const Point &pos, const Rect &size, double rad, MeshType meshType) : GameObject(parent, pos, size, rad, meshType)
    {
        m_health           = 4;
        m_hitCooldown      = 2.0;
        m_timeSinceLastHit = 0.0;
        m_canTakeDamage    = true;
    }
    ~Player() {}

    GameObjectType GetType() 
    {
        return GameObjectType::Player;
    }

    void OnCollision(GameObject *hit)
    {
        if (hit->GetType() == GameObjectType::Asteroid && m_canTakeDamage)
        {
            m_health -= 1;
            if (m_health < 0)
            {
                m_health = 0;
            }

            m_canTakeDamage = false;
            m_timeSinceLastHit = 0.0;
        }
    }

    void Update(double dt)
    {
        GameObject::Update(dt);

        if (!m_canTakeDamage) 
        {
            m_timeSinceLastHit += dt;
            if (m_timeSinceLastHit >= m_hitCooldown) 
            {
                m_canTakeDamage = true;
            }
        }
    }

    int GetHealth()
    {
        return m_health;
    }

private:
    int    m_health;            // здоровье игрока
    double m_hitCooldown;       // время неуязвимости после столкновения (сек)
    double m_timeSinceLastHit;  // время с последнего столкновения (сек)
    bool   m_canTakeDamage;     // может ли игрок получать урон
};


class Asteroid : public GameObject
{
public:
    Asteroid(Window *parent, const Point &pos, const Rect &size, double rad, MeshType meshType) : GameObject(parent, pos, size, rad, meshType) {}
    ~Asteroid() {}

    GameObjectType GetType() 
    {
        return GameObjectType::Asteroid;
    }

    void OnCollision(GameObject *hit)
    {
        
    }
};