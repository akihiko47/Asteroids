#include "gameobject.h"
#include <iostream>

class Player : public GameObject
{
public:
    Player(Window *parent, const Point &pos, const Rect &size, double rad, MeshType meshType) : GameObject(parent, pos, size, rad, meshType) {}
    ~Player() {}

    void OnCollision(GameObject *hit) {
        std::cout << "Collision!" << "\n";
    }
};

class Asteroid : public GameObject
{
public:
    Asteroid(Window *parent, const Point &pos, const Rect &size, double rad, MeshType meshType) : GameObject(parent, pos, size, rad, meshType) {}
    ~Asteroid() {}

    void OnCollision(GameObject *hit) {
        std::cout << "Collision with asteroid!" << "\n";
    }
};