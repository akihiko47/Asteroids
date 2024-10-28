enum class GameObjectType {
    Player,
    Asteroid,
    Bullet
};

class GameObject
{
public:
    GameObject(Window *parent, const Point &pos, const Rect &size, double rad, MeshType meshType);
    virtual ~GameObject();

    virtual void Update(double dt);
    virtual void OnCollision(GameObject *hit) = 0;
    virtual GameObjectType GetType() = 0;

    void   EvaluateCollisions(GameObject *objects[] , int n);
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
    double GetRadius();
    void   SetRadius(double rad);
    
private:
    Mesh  *m_mesh;

    Point m_position;
    Point m_velocity;
    Point m_forward;
    double m_rotation;
    double m_drag;

    double m_radius;  // для расчета столкновений

    Point m_borders;  // границы экрана по x и y
};