class GameObject
{
public:
    GameObject(Window *parent, const Point &pos, const Rect &size, MeshType meshType);
    ~GameObject();

    void Update(double dt);

    double GetRotation();
    void   SetRotation(double phi);
    void   Rotate(double dphi);
    Point  GetPosition();
    void   SetPosition(const Point &pos);
    Point  GetVelocity();
    void   SetVelocity(const Point &vel);
    Point  GetForward();
    double GetDrag();
    void   SetDrag(double drag);
    
private:
    Mesh  *m_mesh;

    Point m_position;
    Point m_velocity;
    Point m_forward;
    double m_rotation;
    double m_drag;

    Point m_borders;  // границы экрана по x и y
};