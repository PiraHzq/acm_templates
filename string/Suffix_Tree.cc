#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
#define N 1010
#define oo 1000000000
struct node
{
    node *parent, *link, *go[27];
    int a, b, len;
};
node mem[N<<1], *root, *cur, *last;
node *newNode(int a = 0, int b = 0, int len = 0, node *parent = 0, node *link = 0)
{
    memset( cur->go, 0, sizeof cur->go);
    cur->a = a;
    cur->b = b;
    cur->len = len;
    cur->parent = parent;
    cur->link = link;
    return cur++;
}
void init()
{
    cur = mem;
    last = root = newNode( 0, 0, 0, cur, cur);
}
node *find_lcp(node *p, int len, int pos, int type, char *s)
{
    len -= p->len;
    while( len>0 )
    {
        int c = s[ pos - len + 1] - 'a';
        node *e = p->go[c];
        if(!e)return p;
        int l, i, j;
        if( type )
        {
            i = e->a;
            j = pos - len + 1;
            l = 0;
            while( s[i]== s[j] && i<= e->b)i++, j++, l++;
        }
        else l = min( e->b - e->a + 1, len);
        if( e->a + l <= e->b ) 
        {
            node *q = newNode( e->a, e->a + l - 1, p->len + l, p);
            p->go[c] = q;
            q->go[ s[ e->a + l ] - 'a' ] = e;
            e->parent = q;
            e->a += l;
            return q;
        }
        len -= l, p = e;
    }
    return p;
}
void suffix_tree(char *s)
{
    int n = strlen(s);
    s[n] = 'a' + 26;
    init();
    for( int i = 0; i<=n; i++)
    {
        node *p = last->link;
        last = p = find_lcp( p, n - i + 1, n, 1, s);
        p->go[ s[ i + p->len ]-'a'] = newNode( i + p->len, n, n - i + 1, p);
        while( !p->link )
        {
            p->link = find_lcp( p->parent->link, p->len - 1, p->b, 0, s);
            p = p->link;
        }
    }
}
char s[N];
ll ans;
void dfs(node *rt, int &ma, int &mb)
{
    int minl = oo, maxl = -oo, leaf = 1;
    for(int i = 0; i<27; i++)
        if( rt->go[i])
        {
            dfs( rt->go[i], minl, maxl);
            leaf = 0;
        }
    ma = min( ma, minl);
    mb = max( mb, maxl);
    if( leaf )
    {
        ma = min( ma, rt->len);
        mb = max( mb, rt->len);
    }
    else
    {
        int now = min( rt->len, maxl - minl) - rt->parent->len;
        if( now>0 )ans += now;
    }
}
int main(int argc, char *argv[])
{
    freopen("a","r",stdin);
    while( scanf("%s", s)!=EOF )
    {
        if( s[0]=='#' )break;
        suffix_tree(s);
        ans = 0;
        int a, b;
        dfs(root, a, b);
        printf("%lld\n", ans);
    }
    return 0;
}

