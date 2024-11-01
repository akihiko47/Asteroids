#include <cmath>

class FPoint
{
public:
    FPoint() : m_x(0), m_y(0) {}
    FPoint(double x, double y) : m_x(x), m_y(y) {}
    FPoint(const FPoint &pt) : m_x(pt.GetX()), m_y(pt.GetY()) {}
    FPoint(const Point &pt)  : m_x(pt.GetX()), m_y(pt.GetY()) {}
    FPoint(const Rect &r)    : m_x(r.GetWidth()), m_y(r.GetHeight()) {}
    ~FPoint() {}

    FPoint operator = (const FPoint &pt)
    {
        m_x = pt.GetX();
        m_y = pt.GetY();
        return *this;
    }

    FPoint operator = (const Point &pt)
    {
        m_x = pt.GetX();
        m_y = pt.GetY();
        return *this;
    }

    //////////////////////////////////////////////////////////
    FPoint operator + (const FPoint pt) const
    {
        FPoint res(GetX()+pt.GetX(), GetY()+pt.GetY());
        return res;
    }
    FPoint operator - (const FPoint pt) const
    {
        FPoint res(GetX()-pt.GetX(), GetY()-pt.GetY());
        return res;
    }

    FPoint operator * (const FPoint pt) const
    {
        FPoint res(GetX()*pt.GetX(), GetY()*pt.GetY());
        return res;
    }
    FPoint operator / (const FPoint pt) const
    {
        FPoint res(GetX()/pt.GetX(), GetY()/pt.GetY());
        return res;
    }

    //////////////////////////////////////////////////////////
    FPoint operator + (const Point pt) const
    {
        FPoint res(GetX()+pt.GetX(), GetY()+pt.GetY());
        return res;
    }
    FPoint operator - (const Point pt) const
    {
        FPoint res(GetX()-pt.GetX(), GetY()-pt.GetY());
        return res;
    }

    FPoint operator * (const Point pt) const
    {
        FPoint res(GetX()*pt.GetX(), GetY()*pt.GetY());
        return res;
    }
    FPoint operator / (const Point pt) const
    {
        FPoint res(GetX()/pt.GetX(), GetY()/pt.GetY());
        return res;
    }

    //////////////////////////////////////////////////////////
    FPoint operator + (const Rect &r) const
    {
        FPoint res(GetX()+r.GetWidth(), GetY()+r.GetHeight());
        return res;
    }
    FPoint operator - (const Rect &r) const
    {
        FPoint res(GetX()-r.GetWidth(), GetY()-r.GetHeight());
        return res;
    }

    //////////////////////////////////////////////////////////
    operator Point()
    {
        Point res = Point(std::fmax(m_x, 0.0), std::fmax(m_y, 0.0));
        return res;
    }

    double GetX() const { return m_x; }
    double GetY() const { return m_y; }
    void     SetX(const double x) { m_x = x; }
    void     SetY(const double y) { m_y = y; }

private:
    double m_x;
    double m_y;
};