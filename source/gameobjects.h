#include "gameobject.h"
#include <iostream>


#define BULLET_LIFETIME 5

class Player : public GameObject
{
public:
    Player(Window *parent, const Point &pos, const Rect &size, double rad, MeshType meshType) : 
        GameObject(parent, pos, size, rad, meshType),
        m_health(4),
        m_hitCooldown(2),
        m_timeSinceLastHit(0),
        m_canTakeDamage(true) {}
    ~Player() {}

    GameObjectType GetType() const {return GameObjectType::Player;}

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

    int GetHealth() const {return m_health;}

private:
    int    m_health;            // здоровье игрока
    double m_hitCooldown;       // время неуязвимости после столкновения (сек)
    double m_timeSinceLastHit;  // время с последнего столкновения (сек)
    bool   m_canTakeDamage;     // может ли игрок получать урон
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

class Asteroid : public GameObject
{
public:
    Asteroid(Window *parent, const Point &pos, const Rect &size, double rad, MeshType meshType) : 
        GameObject(parent, pos, size, rad, meshType) {}
    ~Asteroid() {}

    GameObjectType GetType() const {return GameObjectType::Asteroid;}

    void OnCollision(GameObject *hit) {}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

class Bullet : public GameObject
{
public:
    Bullet(Window *parent, const Point &pos, const Rect &size, double rad, MeshType meshType) :
        GameObject(parent, pos, size, rad, meshType),
        m_maxLifeTime(BULLET_LIFETIME),
        m_lifetime(0) {}
    ~Bullet() {}

    GameObjectType GetType() const {return GameObjectType::Bullet;}

    void OnCollision(GameObject *hit) {}

    void Update(double dt)
    {   
        GameObject::Update(dt);

        m_lifetime += dt;
        if (m_lifetime >= m_maxLifeTime && GetMesh())
        {
            DeleteMesh();
        }
    }

private:
    double m_maxLifeTime;
    double m_lifetime;
};