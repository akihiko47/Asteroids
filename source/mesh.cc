#include "window.h"
#include "mesh.h"
#include <iostream>

int Mesh::m_meshLength[] = {5, 4, 4};
Point Mesh::m_meshPlayer[] = {Point(0, 20), Point(10, 0), Point(20, 20), Point(10, 15), Point(0, 20)};

Mesh::Mesh(MeshType meshType)
{
    m_meshType = meshType;
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

void Mesh::OnDraw(Context *cr)
{
    cr->SetColor(m_Color);

    uint16_t n = m_meshLength[(int)m_meshType];
    Rect mysize = GetInteriorSize();
    uint16_t x = mysize.GetWidth(), y = mysize.GetHeight();
    uint16_t s = x < y ? x : y;

    std::cout << "x = " << x << "\n";
    std::cout << "y = " << y << "\n";
    std::cout << "s = " << s << "\n";

    switch (m_meshType)
    {
        case MeshType::Player:
            cr->Polyline(n, m_meshPlayer);
            break;
    }
    
}