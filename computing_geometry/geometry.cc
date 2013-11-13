#include   <iostream>
#include   <cstdio>
#include   <cmath>
using namespace std;
#define PI acos(-1.0)
#define EPS 1e-10
typedef double db;

/**========================考虑误差======================*/
db add(db a, db b)
{
    if(abs(a+b)<EPS*(abs(a)+abs(b)))return 0;
    return a+b;
}
bool zero(db a)
{
    return abs(a)<EPS;
}
db sqr(db a)
{
    return a*a;
}
/**========================向量（点）类型定义=========================*/
struct point
{
    db x,y;

    point(){}
    point(db x, db y):x(x),y(y){}

    point operator+ (const point &p)const
    {
        return point(add(x,p.x),add(y,p.y));
    }
    point operator- (const point &p)const
    {
        return point(add(x,-p.x),add(y,-p.y));
    }
    point operator* (db k)const
    {
        return point(x*k,y*k);
    }
    db operator* (const point &p)const
    {
        return add(x*p.y,-y*p.x);
    }
    db operator/ (const point &p)const
    {
        return add(x*p.x,y*p.y);
    }
    bool operator< (const point &p)const
    {
        return x<p.x||(x==p.x&&y<p.y);
    }
    bool operator==(const point &p)const 
    {
        return zero(x-p.x) && zero(y-p.y);
    }
    db dis2_to_p(const point &p)const
    {
        return sqr(add(x,-p.x))+sqr(add(y,-p.y));
    }
    db dis_to_p(const point &p)const
    {
        return sqrt(dis2_to_p(p));
    }
    bool read()
    {
        return ~scanf("%lf%lf",&x,&y);
    }
    void write()
    {
        printf("( %.3lf , %.3lf )\n",x,y);
    }
};
/**========================线段类定义=========================*/
struct segment
{
    point p1,p2;

    segment(){}
    segment(const point &p1, const point &p2):p1(p1),p2(p2){}
    segment(db x1, db y1, db x2, db y2):p1(x1,y1),p2(x2,y2){}

    point operator* (const segment &l)const
    {
        return p1+(p2-p1)*( ((l.p2-l.p1)*(l.p1-p1)) / ((l.p2-l.p1)*(p2-p1)) );
    }
    bool operator< (const segment &l)const
    {
        return p1<l.p1;
    }
    bool p_on_seg(const point &p)const
    {
        return zero( (p1-p)*(p2-p) ) && (p1-p)/(p2-p)<=0;
    }
    bool seg_int_seg(const segment &seg)const
    {
        if( max(p1.x,p2.x)<min(seg.p1.x,seg.p2.x) ||
            max(p1.y,p2.y)<min(seg.p1.y,seg.p2.y) ||
            min(p1.x,p2.x)>max(seg.p1.x,seg.p2.x) ||
            min(p1.y,p2.y)>max(seg.p1.y,seg.p2.y) )return 0;

        return    ( (p1-seg.p1)*(seg.p2-seg.p1) )* 
                ( (p2-seg.p1)*(seg.p2-seg.p1) )<=0 &&
                ( (seg.p1-p1)*(p2-p1) )* 
                ( (seg.p2-p1)*(p2-p1) )<=0;
    }
    bool seg_int_line(const segment &line)const
    {
        return    ( (p1-line.p1)*(line.p2-line.p1) )* 
                ( (p2-line.p1)*(line.p2-line.p1) )<=0;
    }
    int line_int_line(const segment &line)const
    {
        //相交
        if( !zero( (p2-p1)*(line.p2-line.p1) ) ) return 1;
        //共线
        if( zero( (p1-line.p1)*(p2-line.p1) ) &&
            zero( (p1-line.p2)*(p2-line.p2) ) ) return -1;
        //平行
        return 0;
    }
    bool read()
    {
        return p1.read()&&p2.read();
    }
    void write()
    {
        printf("( %.2lf, %.2lf ) -> ( %.2lf, %.2lf )\n",p1.x,p1.y,p2.x,p2.y);
    }
};

int main()
{
    freopen("a","r",stdin);
    //freopen("wa","w",stdout);

    return 0;
}
