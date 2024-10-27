#include "window.h"
#include "mesh.h"
#include "gameobject.h"
#include <iostream>
#include <cmath>

GameObject::GameObject(Window *parent, const Point &pos, const Rect &size, MeshType meshType)
{
    m_mesh = new Mesh(meshType);
    Point meshPos = Point(pos.GetX() - m_mesh->GetSize().GetWidth() * 0.5, pos.GetY() - m_mesh->GetSize().GetHeight() * 0.5);
    parent->AddChild(m_mesh, meshPos, size);

    m_borders = Point(parent->GetSize().GetWidth(), parent->GetSize().GetHeight());

    m_position = pos;
    m_velocity = Point(0, 0);
    m_forward = Point(0, -1);
    m_rotation = 0.0;
    m_drag = 0.99;
}

GameObject::~GameObject()
{
}

double GameObject::GetRotation()
{
    return m_rotation;
}

void GameObject::SetRotation(double phi)
{
    m_rotation = phi;
}

void GameObject::Rotate(double dphi)
{
    m_rotation += dphi;
}

Point GameObject::GetPosition() 
{
    return m_position;
}

void GameObject::SetPosition(const Point &pos)
{
    m_position = pos;
}

Point GameObject::GetVelocity()
{
    return m_velocity;
}

Point GameObject::GetForward()
{
    return m_forward;
}

void GameObject::SetVelocity(const Point &vel)
{
    m_velocity = vel;
}

double GameObject::GetDrag()
{
    return m_drag;
}

void GameObject::SetDrag(double drag) 
{
    m_drag = drag;
}

void GameObject::Update(double dt)
{   
    // Изменить позицию
    m_position.SetX(m_position.GetX() + m_velocity.GetX() * dt);
    m_position.SetY(m_position.GetY() + m_velocity.GetY() * dt);

    // Изменить вектор направления
    m_forward = m_mesh->RotatePoint(Point(0, 0), Point(0, -1), m_rotation);

    // Изменить положение отображаемой модели
    Point meshPos = Point(m_position.GetX() - m_mesh->GetSize().GetWidth() * 0.5, m_position.GetY() - m_mesh->GetSize().GetHeight() * 0.5);
    m_mesh->SetPosition(meshPos);
    m_mesh->SetRotation(m_rotation);

    // Применить трение
    m_velocity = m_velocity * Point(m_drag, m_drag);

    // Проверить границы экрана
    if (m_position.GetX() < 0)
    {
        m_position.SetX(m_borders.GetX());
    }
    else if (m_position.GetX() > m_borders.GetX()) 
    {
        m_position.SetX(0);
    }
    else if (m_position.GetY() < 0)
    {
        m_position.SetY(m_borders.GetY());
    }
    else if (m_position.GetY() > m_borders.GetY())
    {
        m_position.SetY(0);
    }

}