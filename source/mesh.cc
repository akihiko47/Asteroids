#include "window.h"
#include "mesh.h"
#include <iostream>
#include <cmath>

int Mesh::m_meshLength[] = {5, 4, 4};
Point Mesh::m_meshPlayer[] = {Point(5, 23), Point(15, 3), Point(25, 23), Point(15, 18), Point(5, 23)};


Mesh::Mesh(MeshType meshType)
{
    m_ClassName = __FUNCTION__;
    m_meshType = meshType;
    m_rotation = 0.0;
    m_Color = RGB(1,1,1);
    m_thickness = 1.0;
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
    cr->SetColor(m_Color);
    cr->SetLineWidth(m_thickness);

    Rect mysize = GetInteriorSize();
    uint16_t x = mysize.GetWidth(), y = mysize.GetHeight();
    uint16_t s = x < y ? x : y;
    Point center = Point(s * 0.5, s * 0.5);

    switch (m_meshType)
    {
        case MeshType::Player:
            Point pts[5];
            for (int i = 0; i < 5; i++) {
                pts[i] = RotatePoint(center, m_meshPlayer[i], m_rotation);
            }
            cr->Polyline(5, pts);
            break;
    }
    
}