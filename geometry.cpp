struct Point
{
    int x,y;
    Point(){}
    Point(int _x,int _y):x(_x),y(_y){}
    void read()
    {
        cin >> x >> y;
    }
};
struct Vector
{
    int x,y;
    Point u,v;
    Vector(){}
    Vector(Point _a,Point _b):x(_b.x-_a.x),y(_b.y-_a.y),u(_a),v(_b){}
    Vector(int _a,int _b):x(_a),y(_b),u(0,0),v(0,0){}
    int orientation(Point a)
    {
        Vector other =Vector(u,a); 
        if (*this*other < 0)
            return -1;
        else if (*this*other == 0)
            return 0;
        else
            return 1;
    }
    int operator * (const Vector &other)
    {
        return this->x*other.y-this->y*other.x;
    }
};
struct Segment
{
    Point a,b;
    Vector u;
    Vector us;
    Segment(){}
    Segment(Point _a,Point _b):a(_a),b(_b),u(_a,_b),us(_b,_a){}
    bool inSeg(Point x)
    {
        bool cross = (u*Vector(a,x)==0);
        if (cross&&(x.x>=min(a.x,b.x)&&x.x<=max(a.x,b.x))&&(x.y>=min(a.y,b.y)&&x.y<=max(a.y,b.y)))
            return true;
        return false;
    }
    bool operator / (const Segment &other)
    {
        if ((this->u.orientation(other.a)> 0&& this->u.orientation(other.b)>0))
            return false;
        else if ((this->u.orientation(other.a)<0&& this->u.orientation(other.b)<0))
            return false;
        return true;
    }
    bool operator ^ (const Segment &other)
    {
        Segment s1 = *this;
        Segment s2 = other;
        if (s1.u*s2.u==0)
        {
            if (s1.u.orientation(s2.a)==0&&s1.u.orientation(s2.b)==0)
            {
                int mnx1,mnx2,mny1,mny2,mxx1,mxx2,mxy1,mxy2;
                mnx1=mnx2=mny1=mny1=1e18;
                mxx1=mxx2=mxy1=mxy1=-1e18;
                mnx1=min(s1.a.x,s1.b.x);
                mnx2=min(s2.a.x,s2.b.x);
                mny1=min(s1.a.y,s1.b.y);
                mny2=min(s2.a.y,s2.b.y);
                mxx1=max(s1.a.x,s1.b.x);
                mxx2=max(s2.a.x,s2.b.x);
                mxy1=max(s1.a.y,s1.b.y);
                mxy2=max(s2.a.y,s2.b.y);
                return ((mnx2<=mxx1&&mny2<=mxy1)&&(mnx1<=mxx2&&mny1<=mxy2)?true:false);
            }
            else
                return false;
        }
        else
        {
            if (s1/s2 && s2/s1)
                return true;
            else
                return false;
        }
    }
};


