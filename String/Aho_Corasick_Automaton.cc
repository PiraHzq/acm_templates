#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define FOR(i,l,r) for(int i=l;i<=r;i++)
#define DWN(i,r,l) for(int i=r;i>=l;i--)
#define N 1010
const int oo = 1e9;
struct node
{
    node *fail, *go[4];
    int val;
};
node mem[N], *root = mem, *cur;
int cg[333];//字符转换规则，记得初始化
node *new_node()
{
    memset(cur->go, 0, sizeof cur->go);
    cur->val = 0;
    cur->fail = root;
    return cur++;
}
void init()
{
    cur = mem;
    root = new_node();
}
void addword(char *s)
{
    node *t = root;
    for(;*s;s++)
    {
        int w = cg[(int)*s];
        if(!t->go[w])
            t->go[w] = new_node();
        t = t->go[w];
    }
    t->val = 1;
}
queue<node*> q;
void build()
{
    while(!q.empty())q.pop();
    REP(i,4)
        if(root->go[i])q.push(root->go[i]);
        else root->go[i] = root;
    while(!q.empty())
    {
        node *t = q.front();
        q.pop();
        REP(i,4)
            if(t->go[i])q.push(t->go[i]),t->go[i]->fail = t->fail->go[i];
            else t->go[i] = t->fail->go[i];
        t->val |= t->fail->val;//较短子串的值累加，必须放在外面
    }
}
int main(int argc, char *argv[])
{
	return 0;
}
