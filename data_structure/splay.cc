/*************************************************************
 * Author: Pira
 * Problem: bzoj1500
 * Date: 2013-11-01-10.14.06
 **************************************************************/
#include <cstdio>
#include <iostream>
using namespace std;
#define N 600010
#define oo 1000000000

struct mark
{
    int mul, add;
    mark(int m=1,int a=0):mul(m),add(a){}
    mark operator*(const mark &m)
    {
        return mark(mul*m.mul,add*m.mul+m.add);
    }
    bool ok(){return mul==1&&add==0;}
};
struct node
{
    node *s[2], *p;
    mark mk;
    int rev;
    int val, sum, sz;
    int ms, lms, rms;
    bool w(){return this==p->s[1];}
    void addIt(const mark &m)
    {
        mk = mk * m;
        val = val*m.mul + m.add;
        sum = sum*m.mul + m.add*sz;
        ms = lms = rms = max(val,sum);
    }
    void revIt()
    {
        rev^=1;
        swap(s[0],s[1]);
        swap(lms,rms);
    }
    void up()
    {
        sz = s[0]->sz + s[1]->sz +1;
        sum = s[0]->sum + s[1]->sum +val;
        ms = max(max(s[0]->ms,s[1]->ms), max(s[0]->rms,0)+val+max(s[1]->lms,0));
        lms = max(s[0]->lms, s[0]->sum + val + max(s[1]->lms,0));
        rms = max(s[1]->rms, s[1]->sum + val + max(s[0]->rms,0));
    }
    void down();
    void sets(node *t, int w){s[w]=t,t->p=this;}
};
node mem[N], *q[N], *root, *cur, *til = mem;
int a[N], top;
void node::down()
{
    if(!mk.ok())
    {
        for(int i=0;i<2;i++)if(s[i]!=til)s[i]->addIt(mk);
        mk = mark();
    }
    if(rev)
    {
        for(int i=0;i<2;i++)if(s[i]!=til)s[i]->revIt();
        rev = 0;
    }
}
node *new_node(int val=0)
{
    node *c = top?q[--top]:cur++;
    c->mk = mark();
    c->rev = 0;
    c->val = val;
    c->p = c->s[0] = c->s[1] = til;
    return c;
}
void erase(node *t)
{
    if(t==til)return;
    q[top++] = t;
    erase(t->s[0]);
    erase(t->s[1]);
}
void zig(node *t)
{
    node *p = t->p;
    p->down();
    t->down();
    int w = t->w();
    p->p->sets(t,p->w());
    p->sets(t->s[!w],w);
    t->sets(p,!w);
    p->up();
}
void splay(node *t, node *f=til)
{
    for(t->down();t->p!=f;)
    {
        if(t->p->p==f)zig(t);
        else if(t->w()==t->p->w())zig(t->p),zig(t);
        else zig(t),zig(t);
    }
    t->up();
    if(f==til)root = t;
}
node *select(int k, node *f=til)
{
    node *t = root;
    int s;
    t->down();
    while((s=t->s[0]->sz)!=k)
    {
        if(k<s)t = t->s[0];
        else k-=s+1, t = t->s[1];
        t->down();
    }
    splay(t,f);
    return t;
}
node *build(int l, int r)
{
    if(l>r)return til;
    int m = (l+r)>>1;
    node *t = new_node(a[m]);
    t->sets(build(l,m-1),0);
    t->sets(build(m+1,r),1);
    t->up();
    return t;
}
node *get(int l, int r)
{
    if(l<1)l=1;
    if(r>root->sz-2)r = root->sz-2;
    return select(r+1,select(l-1))->s[0];
}
void getint(int &a)
{
    char c;
    while(((c=getchar())<'0'||c>'9')&&c!='-');
    int flag = (c=='-')?-1:1;
    if(c=='-')c=getchar();
    for(a=0;c>='0' && c<='9';c=getchar())a = a*10 + c - '0';
    a = a*flag;
}
void init(int n)
{
    for(int i=1;i<=n;i++)getint(a[i]);
    cur = mem;
    top = 0;
    til = new_node();
    til->sz = til->sum = 0;
    til->ms = til->lms = til->rms = -oo;
    root = new_node();
    root->sets(new_node(),1);
    root->s[1]->sets(build(1,n),0);
    splay(root->s[1]);
}
void Insert(int p, int n)
{
    for(int i=1;i<=n;i++)getint(a[i]);
    select(p+1,select(p))->sets(build(1,n),0);
    splay(root->s[1]);
}
void Delete(int p, int n)
{
    erase(select(p+n,select(p-1))->s[0]);
    root->s[1]->s[0] = til;
    splay(root->s[1]);
}
void Same(int p, int n)
{
    int c;
    scanf("%d",&c);
    get(p,p+n-1)->addIt(mark(0,c));
    splay(root->s[1]);
}
void Reverse(int p, int n)
{
    get(p,p+n-1)->revIt();
    splay(root->s[1]);
}
int Sum(int p, int n)
{
    return get(p,p+n-1)->sum;
}
int Msum()
{
    return get(1,root->sz-2)->ms;
}
int main()
{
    int n,m,p,len;
    char op[99];
    getint(n),getint(m);
    init(n);
    while (m--)
    {
        scanf("%s",op);
        if(op[2]!='X')getint(p),getint(len);
        switch(op[2])
        {
        case 'S':
            Insert(p,len);
            break;
        case 'L':
            Delete(p,len);
            break;
        case 'K':
            Same(p,len);
            break;
        case 'V':
            Reverse(p,len);
            break;
        case 'T':
            printf("%d\n",Sum(p,len));
            break;
        default:
            printf("%d\n",Msum());
            break;
        }
    }
    return 0;
}
