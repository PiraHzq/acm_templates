//一条回路问题
#include<cstdio>  
#include<cstring>  
using namespace std;  
const int mm=15511;  
typedef long long LL;  
struct hashTable  
{  
    int h[mm],s[mm],p[mm],t;  
    LL v[mm];  
    void insert(int w,LL val)  
    {  
        int i,id=w%mm;  
        for(i=h[id];i>=0;i=p[i])  
        if(s[i]==w)  
        {  
            v[i]+=val;  
            return;  
        }  
        v[t]=val,s[t]=w,p[t]=h[id],h[id]=t++;  
    }  
    void clear()  
    {  
        t=0,memset(h,-1,sizeof(h));  
    }  
}f[2];  
bool g[22][22];  
int i,j,k,n,m,em,g1,g2;  
bool ok(int s)  
{  
    if(s==1)return g[i+1][j];  
    if(s==2)return g[i][j+1];  
    if(s==3)return g[i+1][j]&&g[i][j+1];  
}  
int Link(int s,bool flag)  
{  
    int n=1,w,x=3<<(j<<1),a=(flag?1:2)<<(j<<1);  
    while(n)  
    {  
        if(flag)a<<=2,x<<=2;  
        else a>>=2,x>>=2;  
        w=s&x;  
        if(w)n+=(w==a)?1:-1;  
    }  
    return s^x;  
}  
void Work(int s,LL val)  
{  
    int e,w=j<<1,ss=(s>>w)&15;  
    if(ss==9)return;  
    if(!ss)  
    {  
        if(ok(3))f[g2].insert(s|(9<<w),val);  
    }  
    else if(!(ss&3)||!(ss&12))  
    {  
        if(ss&3)e=1,ss|=ss<<2;  
        else e=0,ss|=ss>>2;  
        if(ok(1+!e))f[g2].insert(s,val);  
        if(ok(1+e))f[g2].insert(s^(ss<<w),val);  
    }  
    else if(ss==6)f[g2].insert(s^(ss<<w),val);  
    else f[g2].insert(Link(s^(ss<<w),ss==5),val);  
}  
void end()  
{  
    while(n--)  
    for(em=m-1;em>=0;--em)  
        if(g[n][em])return;  
}  
LL PlugDP()  
{  
    end();  
    f[0].clear();  
    f[0].insert(0,1);  
    for(g2=i=0;i<=n;++i)  
    {  
        for(k=0;k<f[g2].t;++k)f[g2].s[k]<<=2;  
        for(j=0;j<m;++j)  
            if(g[i][j])for(g1=g2,g2=!g2,f[g2].clear(),k=0;k<f[g1].t;++k)  
            {  
                if(i==n&&j==em)  
                    if(((f[g1].s[k]>>(j<<1))&15)==9)return f[g1].v[k];  
                    else continue;  
                Work(f[g1].s[k],f[g1].v[k]);  
            }  
    }  
    return 0;  
}  
char c;  
int main()  
{  
    scanf("%d%d",&n,&m);  
    memset(g,0,sizeof(g));  
    for(i=0;i<n;++i)  
        for(j=0;j<m;++j)  
            scanf(" %c",&c),g[i][j]=(c=='.');  
    printf("%I64d\n",PlugDP());  
    return 0;  
}  
//一条路径问题
#include<cstdio>  
#include<cstring>  
#define mm 100007  
#define mn 11  
#define getRP(a,b) ((a)<<((b)<<1))  
struct hash  
{  
    int h[mm],s[mm],p[mm],d[mm],t;  
    int push(int x,int v)  
    {  
        int i,c=x%mm;  
        for(i=h[c];i>=0;i=p[i])  
        if(s[i]==x)  
        {  
            if(v>d[i])d[i]=v;  
            return i;  
        }  
        d[t]=v,s[t]=x,p[t]=h[c],h[c]=t;  
        return t++;  
    }  
    void clear()  
    {  
        t=0;  
        memset(h,-1,sizeof(h));  
    }  
}f[2];  
int g[mn][mn];  
int i,j,k,g1,g2,x,y,z,s,n,m,ans;  
int eat(bool f,bool l)  
{  
    int a=getRP(z,j+f),b=getRP(3^z,j+f),c=getRP(3,j+f),n=1;  
    s=s^getRP(x,j)^getRP(y,j+1);  
    while(n)  
    {  
        if(f)a<<=2,b<<=2,c<<=2;  
        else a>>=2,b>>=2,c>>=2;  
        x=s&c;  
        if(x==a)++n;  
        if(x==b)--n;  
    }  
    return l?(s|c):((s^b)|a);  
}  
bool ok(int c)  
{  
    if(c==1)return g[i+1][j];  
    if(c==2)return g[i][j+1];  
    if(c==3)return g[i+1][j]&&g[i][j+1];  
    return 0;  
}  
void move(int v)  
{  
    int w=v+g[i][j];  
    if(!x&&!y)  
    {  
        if(ok(1))f[g2].push(s|getRP(3,j),w);  
        if(ok(2))f[g2].push(s|getRP(3,j+1),w);  
        if(ok(3))f[g2].push(s|getRP(9,j),w);  
        f[g2].push(s,v);  
    }  
    else if(!x||!y)  
    {  
        z=x+y;  
        if(ok(x?1:2))f[g2].push(s,w);  
        if(ok(x?2:1))f[g2].push(s^getRP(z,j)^getRP(z,j+1),w);  
        if(z<3)f[g2].push(eat(z==1,1),w);  
        else if((s^getRP(x,j)^getRP(y,j+1))==0&&w>ans)ans=w;  
    }  
    else if(x==y)  
    {  
        if((z=x)<3)f[g2].push(eat(z==1,0),w);  
        else if((s^getRP(x,j)^getRP(y,j+1))==0&&w>ans)ans=w;  
    }  
    else if(x>2||y>2)  
    {  
        z=x<y?x:y;  
        f[g2].push(eat(z==1,1),w);  
    }  
    else if(x==2&&y==1)f[g2].push(s^getRP(x,j)^getRP(y,j+1),w);  
}  
int PlugDP()  
{  
    f[0].clear();  
    f[0].push(0,0);  
    for(g1=1,g2=i=0;i<n;++i)  
    {  
        for(j=0;j<f[g2].t;++j)f[g2].s[j]<<=2;  
        for(j=0;j<m;++j)  
            if(g[i][j])for(g1=!g1,g2=!g2,f[g2].clear(),k=0;k<f[g1].t;++k)  
            {  
                s=f[g1].s[k],x=(s>>(j<<1))&3,y=(s>>((j+1)<<1))&3;  
                move(f[g1].d[k]);  
            }  
    }  
    return ans;  
}  
int main()  
{  
    int t;  
    scanf("%d",&t);  
    while(t--)  
    {  
        scanf("%d%d",&n,&m);  
        memset(g,0,sizeof(g));  
        for(ans=i=0;i<n;++i)  
            for(j=0;j<m;++j)  
            {  
                scanf("%d",&g[i][j]);  
                if(g[i][j]>ans)ans=g[i][j];  
            }  
        printf("%d\n",PlugDP());  
    }  
    return 0;  
}  
