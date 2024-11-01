enum class GameObjectType {
    Player,
    Asteroid,
    Bullet,
    Particle
};

class GameObject
{
public:
    GameObject(Window *parent, const FPoint &pos, const Rect &size, double rad, MeshType meshType);
    virtual ~GameObject();

    virtual void           Update(double dt);
    virtual void           OnCollision(GameObject *hit) = 0;
    virtual GameObjectType GetType() const = 0;
    virtual void           OnScreenLeft();

    Mesh*  GetMesh()     const;
    void   DeleteMesh();
    void   EvaluateCollisions(GameObject *objects[] , int n);
    double GetRotation() const;
    void   SetRotation(double phi);
    void   Rotate(double dphi);
    FPoint  GetPosition() const;
    void   SetPosition(const FPoint &pos);
    FPoint  GetVelocity() const;
    void   SetVelocity(const FPoint &vel);
    FPoint  GetForward()  const;
    double GetDrag()     const;
    void   SetDrag(double drag);
    double GetRadius()   const;
    void   SetRadius(double rad);
    
private:
    Mesh  *m_mesh;

    FPoint  m_position;
    FPoint  m_velocity;
    FPoint  m_forward;
    double m_rotation;
    double m_drag;

    double m_radius;  // для расчета столкновений

    FPoint  m_borders;  // границы экрана по x и y
};