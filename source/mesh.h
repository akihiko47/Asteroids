enum class MeshType {
    Player,
    Asteroid1,
    Asteroid2,
    Asteroid3,
    Bullet
};

class Mesh : public Window
{
public:
    Mesh(MeshType meshType);
    ~Mesh();

    void   OnDraw(Context *cr);

    RGB    GetColor();
    void   SetColor(RGB Color);
    double GetThickness()  const;
    void   SetThickness(double thickness);
    double GetRotation()   const;
    void   SetRotation(double phi);
    bool   GetActive()     const;
    void   SetActive(bool state);                                    // Включение и отключение отрисовки

    MeshType GetMeshType() const;
    void     SetMeshType(MeshType meshType);

    static Point RotatePoint(const Point &o, const Point &p, double phi);  // Вращение точки p вокруг точки o на градус phi (рад)
    
private:
    MeshType m_meshType;

    RGB    m_Color;
    double m_thickness;
    double m_rotation;
    bool   m_fill;
    bool   m_active;

    static int   m_meshLength[];
    static Point m_meshPlayer[];
    static Point m_meshAsteroid1[];
    static Point m_meshAsteroid2[];
    static Point m_meshAsteroid3[];
    static Point m_meshBullet[];
};
