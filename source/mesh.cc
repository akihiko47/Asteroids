#include "window.h"
#include "mesh.h"
#include <iostream>
#include <cmath>

Point Mesh::m_meshPlayer[12] =    {Point(0.25, 0.8), Point(0.5, 0.2), Point(0.75, 0.8), Point(0.5, 0.7), Point(0.25, 0.8), Point(0.25, 0.8), Point(0.25, 0.8), Point(0.25, 0.8), Point(0.25, 0.8), Point(0.25, 0.8), Point(0.25, 0.8), Point(0.25, 0.8)};
Point Mesh::m_meshAsteroid1[12] = {Point(0.3, 0.4), Point(0.4, 0.2), Point(0.7, 0.2), Point(0.8, 0.5), Point(0.7, 0.8), Point(0.3, 0.8), Point(0.1, 0.5), Point(0.3, 0.4), Point(0.3, 0.4), Point(0.3, 0.4), Point(0.3, 0.4), Point(0.3, 0.4)};
Point Mesh::m_meshAsteroid2[12] = {Point(0.3, 0.3), Point(0.4, 0.4), Point(0.5, 0.2), Point(0.7, 0.2), Point(0.8, 0.4), Point(0.8, 0.6), Point(0.7, 0.6), Point(0.6, 0.8), Point(0.3, 0.8), Point(0.2, 0.7), Point(0.2, 0.5), Point(0.3, 0.3)};
Point Mesh::m_meshAsteroid3[12] = {Point(0.3, 0.2), Point(0.4, 0.2), Point(0.8, 0.4), Point(0.8, 0.5), Point(0.7, 0.6), Point(0.5, 0.6), Point(0.5, 0.7), Point(0.4, 0.8), Point(0.3, 0.8), Point(0.2, 0.6), Point(0.2, 0.4), Point(0.3, 0.2)};


Mesh::Mesh(MeshType meshType)
{
    m_ClassName = __FUNCTION__;
    m_meshType = meshType;
    m_rotation = 0.0;
    m_Color = RGB(1,1,1);
    m_thickness = 1.0;
    m_active = true;
}

Mesh::~Mesh()
{
}

RGB Mesh::GetColor()
{
    return m_Color;
}

void Mesh::SetColor(RGB color) {
    m_Color = color;
}

double Mesh::GetThickness()
{
    return m_thickness;
}

void Mesh::SetThickness(double thickness)
{
    m_thickness = thickness;
}

double Mesh::GetRotation()
{
    return m_rotation;
}

void Mesh::SetRotation(double phi)
{
    m_rotation = phi;
}

MeshType Mesh::GetMeshType() {
    return m_meshType;
}

void Mesh::SetMeshType(MeshType meshType) {
    m_meshType = meshType;
}

bool Mesh::GetActive()
{
    return m_active;
}

void Mesh::SetActive(bool state)
{
    m_active = state;
}

Point Mesh::RotatePoint(const Point &o, const Point &p, double phi) {
    double s = sin(phi);
    double c = cos(phi);

    double xnew = p.GetX() - o.GetX();
    double ynew = p.GetY() - o.GetY();

    double xr = xnew * c - ynew * s;
    double yr = xnew * s + ynew * c;

    xr = xr + o.GetX();
    yr = yr + o.GetY();

    Point res = Point(xr, yr);

    return res;
}

void Mesh::OnDraw(Context *cr)
{   
    if (!m_active)
    {
        return;
    }

    cr->SetColor(m_Color);
    cr->SetLineWidth(m_thickness);

    Rect mysize = GetInteriorSize();
    uint16_t x = mysize.GetWidth(), y = mysize.GetHeight();
    uint16_t s = x < y ? x : y;
    Point center = Point(x * 0.5, y * 0.5);

    Point pts[12];
    switch (m_meshType)
    {
        case MeshType::Player:
            for (int i = 0; i < 12; i++) {
                pts[i] = RotatePoint(center, m_meshPlayer[i] * Point(x, y), m_rotation);
            }
            break;
        
        case MeshType::Asteroid1:
            for (int i = 0; i < 12; i++) {
                pts[i] = RotatePoint(center, m_meshAsteroid1[i] * Point(x, y), m_rotation);
            }
            break;
        
        case MeshType::Asteroid2:
            for (int i = 0; i < 12; i++) {
                pts[i] = RotatePoint(center, m_meshAsteroid2[i] * Point(x, y), m_rotation);
            }
            break;

        case MeshType::Asteroid3:
            for (int i = 0; i < 12; i++) {
                pts[i] = RotatePoint(center, m_meshAsteroid3[i] * Point(x, y), m_rotation);
            }
            break;
    }
    cr->Polyline(12, pts);
}