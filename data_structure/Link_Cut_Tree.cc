#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define REP(i,n) for(int i=0;i<n;++i)
using namespace std;

//Dynamic Tree

typedef long long int64;
const int MOD = 51061;
const int MAX_N = int(1e5) + 10;

struct Mark {
    int64 add, mul; //x*mul+add
    Mark(int64 add, int64 mul) {
        this->add = add;
        this->mul = mul;
    }
    Mark() {
        mul = 1;
        add = 0;
    }
    bool isId() {
        return mul == 1 && add == 0;
    }
};

Mark operator*(Mark a, Mark b) {
    return Mark((a.add * b.mul + b.add) % MOD, a.mul * b.mul % MOD);
}

struct Node {
    Node*p, *ch[2];
    bool rev;
    Mark m;
    int64 sum, val;
    int size;
    bool isRoot;
    Node*fa;
    Node() {
        sum = 0;
        isRoot = 0;
        size = 0;
    }
    void sc(Node*c, int d) {
        ch[d] = c;
        c->p = this;
    }
    bool d() {
        return this == p->ch[1];
    }
    void upd() {
        sum = (val + ch[0]->sum + ch[1]->sum) % MOD;
        size = 1 + ch[0]->size + ch[1]->size;
    }
    void apply(Mark a) {
        m = m * a;
        sum = (sum * a.mul + a.add * size) % MOD;
        val = (val * a.mul + a.add) % MOD;
    }
    void revIt() {
        rev ^= 1;
        swap(ch[0], ch[1]);
    }
    void relax();
    void setRoot(Node*f);
} Tnull, *null = &Tnull;

void Node::setRoot(Node*f) {
    fa = f;
    isRoot = true;
    p = null;
}

void Node::relax() {
    if (!m.isId()) {
        REP(i,2)
            if (ch[i] != null)
                ch[i]->apply(m);
        m = Mark();
    }
    if (rev) {
        REP(i,2)
            if (ch[i] != null)
                ch[i]->revIt();
        rev = 0;
    }
}

Node mem[MAX_N], *C = mem;

Node*make(int v) {
    C->sum = C->val = v;
    C->rev = 0;
    C->m = Mark();
    C->ch[0] = C->ch[1] = null;
    C->isRoot = true;
    C->p = null;
    C->fa = null;
    return C++;
}

void rot(Node*t) {
    Node*p = t->p;
    p->relax();
    t->relax();
    bool d = t->d();
    p->p->sc(t, p->d());
    p->sc(t->ch[!d], d);
    t->sc(p, !d);
    p->upd();
    if (p->isRoot) {
        p->isRoot = false;
        t->isRoot = true;
        t->fa = p->fa;
    }
}

void pushTo(Node*t) {
    static Node*stk[MAX_N];
    int top = 0;
    while (t != null) {
        stk[top++] = t;
        t = t->p;
    }
    for (int i = top - 1; i >= 0; --i)
        stk[i]->relax();
}

void splay(Node*u, Node*f = null) {
    pushTo(u);
    while (u->p != f) {
        if (u->p->p == f)
            rot(u);
        else
            u->d() == u->p->d() ? (rot(u->p), rot(u)) : (rot(u), rot(u));
    }
    u->upd();
}

Node*v[MAX_N];
vector<int> E[MAX_N];
int n, nQ;

int que[MAX_N], fa[MAX_N], qh = 0, qt = 0;

void bfs() {
    que[qt++] = 0;
    fa[0] = -1;
    while (qh < qt) {
        int u = que[qh++];
        for (vector<int>::iterator e = E[u].begin(); e != E[u].end(); ++e)
            if (*e != fa[u])
                fa[*e] = u, v[*e]->fa = v[u], que[qt++] = *e;
    }
}

Node* expose(Node*u) {
    Node*v;
    for (v = null; u != null; v = u, u = u->fa) {
        splay(u);
        u->ch[1]->setRoot(u);
        u->sc(v, 1);
        v->fa = u;
    }
    return v;
}

void makeRoot(Node*u) {
    expose(u);
    splay(u);
    u->revIt();
}

void addEdge(Node*u, Node*v) {
    makeRoot(v);
    v->fa = u;
}

void delEdge(Node*u, Node*v) {
    makeRoot(u);
    expose(v);
    splay(u);
    u->sc(null, 1);
    u->upd();
    v->fa = null;
    v->isRoot = true;
    v->p = null;
}

void markPath(Node*u, Node*v, Mark m) {
    makeRoot(u);
    expose(v);
    splay(v);
    v->apply(m);
}

int queryPath(Node*u, Node*v) {
    makeRoot(u);
    expose(v);
    splay(v);
    return v->sum;
}

int main() {
    scanf("%d%d", &n, &nQ);
    REP(i,n-1) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    REP(i,n)
        v[i] = make(1);
    bfs();
    REP(i,nQ) {
        char cmd;
        scanf(" ");
        scanf("%c", &cmd);
        int i, j;
        scanf("%d%d", &i, &j);
        Node*u = ::v[--i], *v = ::v[--j];
        if (cmd == '+') {
            int c;
            scanf("%d", &c);
            markPath(u, v, Mark(c, 1));
        } else if (cmd == '*') {
            int c;
            scanf("%d", &c);
            markPath(u, v, Mark(0, c));
        } else if (cmd == '/') {
            printf("%d\n", queryPath(u, v));
        } else {
            int k, l;
            scanf("%d%d", &k, &l);
            delEdge(u, v);
            addEdge(::v[--k], ::v[--l]);
        }
    }
}
