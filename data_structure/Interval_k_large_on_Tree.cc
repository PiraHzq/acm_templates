#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define FOR(i,l,r) for(int i=l;i<=r;i++)
#define DWN(i,r,l) for(int i=r;i>=l;i--)
#define N 200010
struct node
{
    node *ls, *rs;
    int sz;
};
node mem[N*20], *rt[N], *cur;
node *new_node()
{
    cur->ls = cur->rs = mem;
    cur->sz = 0;
    return cur++;
}
void init()
{
    cur = mem;
    new_node();
    rt[0] = new_node();
}
void update(node *x, node *&y, int l, int r, int p)
{
    y = new_node();
    y->sz = x->sz + 1;
    if(l+1>=r)return;
    int m = (l+r)>>1;
    if(p<m)
    {
        y->rs = x->rs;
        update(x->ls, y->ls, l, m, p);
    }
    else
    {
        y->ls = x->ls;
        update(x->rs, y->rs, m, r, p);
    }
}
int query(node *x, node *y, node *a, node *b, int l, int r, int k)
{
    if(l+1>=r)return l;
    int m = (l+r)>>1, now = y->ls->sz + x->ls->sz - a->ls->sz - b->ls->sz;
    if(now>=k)
        return query(x->ls, y->ls, a->ls, b->ls, l, m, k);
    return query(x->rs, y->rs, a->rs, b->rs, m, r, k-now);
}
vector<int> e[N];
int q[N], d[N], dep[N], pos[N], fa[N], a[N], b[N], id[N*2], nds;
int f[N][20];
void Simulation_dfs(int u, int n, int w)
{
    int v, r = 0;
    init();
    update(rt[0],rt[u], 0, w, a[u]);
    FOR(i,1,n)d[i] = e[i].size()-1;
    fa[ q[++r] = u] = 0;
    dep[u] = 1;
    nds = 0;
    while(r)
    {
        u = q[r];
        id[pos[u] = nds++] = u;
        while(d[u]>=0)
            if((v = e[u][d[u]--])!= fa[u])
            {
                fa[ q[++r] = v ] =u;
                dep[v] = dep[u] + 1;
                update(rt[u],rt[v],0,w,a[v]);
                goto end;
            }
        r--;
        end:;
    }
}
void init_rmq()
{
    REP(i,nds)f[i][0] = id[i];
    for(int j = 1;(1<<j)<nds;++j)
        REP(i,nds-(1<<j)+1)
        {
            int k = i + (1<<(j-1));
            if(dep[ f[i][j-1] ]<dep[ f[k][j-1] ])
                f[i][j] = f[i][j-1];
            else f[i][j] = f[k][j-1];
        }
}
int rmq(int l, int r)
{
    if(l>r)swap(l,r);
    int m = 0;
    while(l+(1<<m)<r-(1<<m)+1)m++;
    r = r-(1<<m)+1;
    if( dep[ f[l][m] ]<dep[ f[r][m] ])return f[l][m];
    return f[r][m];
}
int main(int argc, char **argv)
{
    int n, m, w, u, v, k;
    scanf("%d%d", &n, &m);
    FOR(i,1,n)
    {
        scanf("%d",&a[i]);
        b[i-1] = a[i];
        e[i].clear();
    }
    REP(i,n-1)
    {
        scanf("%d%d",&u,&v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    sort(b, b+n);
    w = unique(b,b+n) - b;
    FOR(i,1,n)a[i] = lower_bound(b,b+w,a[i]) - b;
    Simulation_dfs(1, n, w);
    init_rmq();
    REP(i,m)
    {
        scanf("%d%d%d", &u, &v, &k);
        int lca = rmq(pos[u],pos[v]);
        printf("%d\n",b[query(rt[u],rt[v],rt[lca],rt[fa[lca]],0,w,k)]);
    }
    return 0;
}

