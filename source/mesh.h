enum class MeshType {
    Player,
    Asteroid1,
    Asteroid2
};

class Mesh : public Window
{
public:
    Mesh(MeshType meshType);
    ~Mesh();

    void   OnDraw(Context *cr);

    RGB    GetColor();
    void   SetColor(RGB Color);
    double GetThickness();
    void   SetThickness(double thickness);
    double GetRotation();
    void   SetRotation(double phi);
    Point  RotatePoint(const Point &o, const Point &p, double phi);  // Вращение точки p вокруг точки o на градус phi (рад)

    MeshType GetMeshType();
    void     SetMeshType(MeshType meshType);
    
private:
    MeshType m_meshType;

    RGB    m_Color;
    double m_thickness;
    double m_rotation;
    bool   m_fill;

    static int   m_meshLength[];
    static Point m_meshPlayer[];
    static Point m_meshAsteroid1[];
};
