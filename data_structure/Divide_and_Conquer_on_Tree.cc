#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define FOR(i,l,r) for(int i=l;i<=r;i++)
#define DWN(i,r,l) for(int i=r;i>=l;i--)
#define N 20010
int head[N], ver[N], cost[N], next[N];
int dis[N], del[N], sz[N], q[N], fa[N];
int K, ans, edge;
void init(int n)
{
    REP(i,n+1)head[i] = 0, del[i] = 0;
    ans = 0, edge = 2;
}
void addedge(int u, int v, int c)
{
    ver[edge] = v, cost[edge]= c, next[edge] =head[u], head[u] = edge++;
    ver[edge] = u, cost[edge]= c, next[edge] =head[v], head[v] = edge++;
}
int findroot(int u)
{
    int v, r = 0, root = u;
    fa[ q[r++] = u ] = 0;
    REP(l,r)
        for(int e = head[u=q[l]];e;e=next[e])
            if(!del[v=ver[e]] && v != fa[u])
                fa[ q[r++] = v ] = u;
    int msz = 1e9;
    DWN(i,r-1,0)
    {
        sz[ u = q[i] ] = 1;
        int now = 0;
        for(int e = head[u];e;e=next[e])
            if(!del[v=ver[e]] && v != fa[u])
                sz[u] += sz[v], now = max(now, sz[v]);
        now = max(now, r - sz[u]);
        if(now<msz)msz = now, root = u;
    }
    return root;
}
int counts(int s, int t)
{
    int ret = 0;
    while(s<t)
    {
        while(s<t && dis[s]+dis[t]>K)t--;
        ret += t-s++;
    }
    return ret;
}
int recover(int u, int s, int d)
{
    if(d>K)return 0;
    int v, r = 0;
    fa[ q[r++] = u ] = 0;
    dis[s] = d;
    REP(l,r)
        for(int e = head[u=q[l]];e;e=next[e])
            if(!del[v=ver[e]] && v != fa[u])
            {
                dis[s+r] = dis[s+l] + cost[e];
                if(dis[s+r]>K)continue;
                fa[ q[r++] = v ] = u;
            }
    sort(dis+s, dis+s+r);
    return r;
}
int dfs(int u, int s, int d)
{
    int v, root = findroot(u);
    int n, tot = 1;
    del[root] = 1;
    for(int e = head[root];e;e=next[e])
        if(!del[v=ver[e]])
        {
            n = dfs(v, s+tot, cost[e]);
            ans -= counts(s+tot, s+tot+n-1);
            tot += n;
        }
    dis[s] = 0;

    sort(dis+s, dis+s+tot);
    ans += counts(s, s+tot-1);
    del[root] = 0;
    return recover(u,s,d);
}
void getint(int &a)
{
    char c;
    while(!isdigit(c=getchar()));
    for(a=0;isdigit(c);c=getchar())a = a*10 + c-'0';
}
int main(int argc, char **argv)
{
    freopen("a","r",stdin);
    int n, a, b, c;
    while(scanf("%d%d",&n,&K)!=EOF)
    {
        if(n==0&&K==0)break;
        init(n);
        REP(i,n-1)
        {
            getint(a);
            getint(b);
            getint(c);
            addedge(a,b,c);
        }
        dfs(1,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
