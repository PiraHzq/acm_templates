#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define N 250010
struct node
{
    node *parent, *next, *go[26];
    int len, sum;
};
node mem[N*2], *head[N], *root, *last, *cur;
node *new_node(int len=0)
{
    memset(cur->go, 0, sizeof cur->go);
    cur->len = len;
    cur->next = head[len];
    head[len] = cur;
    return cur++;
}
void init()
{
    memset(head, 0, sizeof head);
    cur = mem;
    root = last = new_node();
}
void extend(int w)
{
    node *p = last;
    node *np = new_node(p->len + 1);
    while(p && !p->go[w])
    {
        p->go[w] = np;
        p = p->parent;
    }
    if(!p)np->parent = root;
    else
    {
        node *q = p->go[w];
        if(p->len + 1==q->len)
            np->parent = q;
        else
        {
            node *nq = new_node(p->len + 1);
            memcpy(nq->go, q->go, sizeof q->go);
            nq->parent = q->parent;
            q->parent = nq;
            np->parent = nq;
            while(p && p->go[w] ==q)
            {
                p->go[w] = nq;
                p = p->parent;
            }
        }
    }
    last = np;
}
char s[N];
int ans[N];
int main(int argc, char **argv)
{
    scanf("%s",s);
    int len = strlen(s);
    init();
    for(char *c = s; *c; c++)
        extend(*c - 'a');
    node *t = root;
    for(char *c = s;*c;c++)
    {
        t = t->go[*c - 'a'];
        t->sum = 1;
    }
    memset(ans, 0, sizeof ans);
    for(int i = len; i>0; i--)
    {
        for(t = head[i];t;t = t->next)
        {
            ans[ t->len ] = max(ans[t->len], t->sum);
            if(t->parent)
                t->parent->sum += t->sum;
        }
        ans[i] = max( ans[i], ans[i+1]);
    }
    for(int i=1;i<=len;i++)
        printf("%d\n",ans[i]);
    return 0;
}

