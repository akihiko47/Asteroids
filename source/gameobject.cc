#include "window.h"
#include "fpoint.h"
#include "mesh.h"
#include "gameobject.h"
#include <iostream>
#include <cmath>


GameObject::GameObject(Window *parent, const FPoint &pos, const Rect &size, double rad, MeshType meshType)
{
    m_mesh = new Mesh(meshType);
    FPoint meshPos = FPoint(pos.GetX() - m_mesh->GetSize().GetWidth() * 0.5, pos.GetY() - m_mesh->GetSize().GetHeight() * 0.5);
    parent->AddChild(m_mesh, meshPos, size);

    m_borders = FPoint(parent->GetSize().GetWidth(), parent->GetSize().GetHeight());

    m_position = pos;
    m_velocity = FPoint(0, 0);
    m_forward = FPoint(0, -1);
    m_rotation = 0.0;
    m_drag = 1.0;
    m_radius = rad;
}

GameObject::~GameObject()
{
    if (GetMesh()) {DeleteMesh();}
}

Mesh* GameObject::GetMesh() const
{
    return m_mesh;
}

void GameObject::DeleteMesh()
{
    m_mesh->GetParent()->DeleteChild(m_mesh);
    m_mesh = nullptr;
}

double GameObject::GetRotation() const
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

FPoint GameObject::GetPosition() const
{
    return m_position;
}

void GameObject::SetPosition(const FPoint &pos)
{
    m_position = pos;
}

FPoint GameObject::GetVelocity() const
{
    return m_velocity;
}

FPoint GameObject::GetForward() const
{
    return m_forward;
}

void GameObject::SetVelocity(const FPoint &vel)
{
    m_velocity = vel;
}

double GameObject::GetDrag() const
{
    return m_drag;
}

void GameObject::SetDrag(double drag) 
{
    m_drag = drag;
}

double GameObject::GetRadius() const
{
    return m_radius;
}

void GameObject::SetRadius(double rad)
{
    m_radius = rad;
}

void GameObject::OnCollision(GameObject *hit)
{
}

void GameObject::OnScreenLeft()
{
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

void GameObject::EvaluateCollisions(GameObject *objects[], int n) {
    for (int i = 0; i < n; i++) {
        GameObject *obj = objects[i];
        if (!objects[i])
        {
            break;  // что-то пошло не так, обработаем столкновение на следующем кадре
        }

        double dist = sqrt(pow(m_position.GetX() - obj->GetPosition().GetX(), 2.0) + pow(m_position.GetY() - obj->GetPosition().GetY(), 2.0));
        if (dist <= m_radius + obj->GetRadius()) {
            OnCollision(obj);
            obj->OnCollision(this);
            break;
        }
    }
}

void GameObject::Update(double dt)
{   
    // Изменить позицию
    m_position.SetX(m_position.GetX() + m_velocity.GetX() * dt);
    m_position.SetY(m_position.GetY() + m_velocity.GetY() * dt);

    // Изменить вектор направления
    m_forward = Mesh::RotatePoint(FPoint(0, 0), FPoint(0, -1), m_rotation);

    // Изменить положение отображаемой модели
    if (GetMesh())
    {
        FPoint meshPos = FPoint(m_position.GetX() - m_mesh->GetSize().GetWidth() * 0.5, m_position.GetY() - m_mesh->GetSize().GetHeight() * 0.5);
        m_mesh->SetPosition(meshPos);
        m_mesh->SetRotation(m_rotation);
    }

    // Применить трение
    m_velocity = m_velocity * FPoint(m_drag, m_drag);

    // Обновить границы экрана
    if (GetMesh())
    {
        Rect r = GetMesh()->GetParent()->GetSize();
        m_borders = FPoint(r.GetWidth(), r.GetHeight());
    }

    // Проверить нахождение внутри границ экрана
    if (m_position.GetX() < 0 || m_position.GetX() > m_borders.GetX() || m_position.GetY() < 0 || m_position.GetY() > m_borders.GetY())
    {
        OnScreenLeft();
    }
}