struct node
{
    node *ls, *rs;
    int num;
};
node mem[N*11], *root[N], *cur, *til = mem;
node *newNode()
{
    cur->num = 0;
    cur->ls = cur->rs = til;
    return cur++;
}
void init()
{
    cur = mem;
    til = newNode();
}
void insert(node *x, node *&y, int l, int r, int p)
{
    y = newNode();
    y->num = x->num + 1;
    int m = (l+r)>>1;
    if( l+1>=r )return;
    if( p<m )
    {
        y->rs = x->rs;
        insert(x->ls, y->ls, l, m, p);
    }
    else
    {
        y->ls = x->ls;
        insert(x->rs, y->rs, m, r, p);
    }
}
void update(node *&rt, int l, int r, int p, int val)
{
    if( rt==til )rt = newNode();
    rt->num += val;
    int m = (l+r)>>1;
    if( l+1>=r )return;
    if( p<m )
        update( rt->ls, l, m, p, val);
    else
        update( rt->rs, m, r, p, val);
}
struct answer
{
    node *t[N];
    int n;
    answer():n(0){}
    void push(node *now){ t[n++] = now; }
    void left(){ REP(i,n)t[i] = t[i]->ls; }
    void right(){ REP(i,n)t[i] = t[i]->rs; }
    int value(){ int ret = 0;REP(i,n)ret += t[i]->ls->num; return ret; }
};
struct command
{
    int o, l, r, k;
    void read()
    {
        char op[9];
        scanf("%s%d%d",op,&l,&r);
        o = op[0]=='Q';
        if(o)scanf("%d",&k);
    }
};
struct BinaryIndexTree
{
    node *t[N];
    int n, m;
    void init(int la, int lb)
    {
        n = la, m = lb;
        REP(i,n+1)t[i] = newNode();
    }
    void insert(int x, int p, int val)
    {
        for(;x<=n;x+=x&-x)update(t[x], 0, m, p, val);
    }
    void query(int x, answer &ans)
    {
        for(;x>0;x-=x&-x)ans.push(t[x]);
    }
};
BinaryIndexTree bit;
int query(int l, int r, int k, int n)
{
    answer x, y;
    bit.query(l-1, x);
    bit.query(r, y);
    x.push(root[l-1]);
    y.push(root[r]);
    l = 0, r = n;
    while( l+1<r )
    {
        int m = (l+r)>>1;
        int sum = y.value() - x.value();
        if( k<=sum ) r = m, x.left(), y.left();
        else k -= sum, l = m, x.right(), y.right();
    }
    return l;
}
command cmd[N];
int a[N], b[N];
int main(int argc, char *argv[])
{
    int t, n, m, w;
    scanf("%d",&t);
    while( t-- )
    {
        scanf("%d%d",&n,&m);
        w = 0;
        FOR(i,1,n)
        {
            scanf("%d",&a[i]);
            b[w++] = a[i];
        }
        REP(i,m)
        {
            cmd[i].read();
            if(!cmd[i].o)b[w++] = cmd[i].r;
        }
        sort( b, b+w);
        w = unique( b, b+w) - b;
        init();
        bit.init( n, w);
        root[0] = newNode();
        FOR(i,1,n)
        {
            a[i] = lower_bound( b, b+w, a[i]) -b;
            insert(root[i-1], root[i], 0, w, a[i]);
        }
        REP(i,m)
        {
            if( cmd[i].o )
                printf("%d\n",b[query( cmd[i].l, cmd[i].r, cmd[i].k, w)]);
            else
            {
                bit.insert(cmd[i].l,a[ cmd[i].l ], -1);
                a[ cmd[i].l ] = lower_bound( b, b+w, cmd[i].r) - b;
                bit.insert(cmd[i].l,a[ cmd[i].l ], 1);
            }
        }
    }
    return 0;
}
