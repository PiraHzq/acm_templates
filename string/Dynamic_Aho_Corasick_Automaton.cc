/* for hdu 4787
 * 下面为暴力根号的方法，查询比较多时适用， 查询 O(len)， 更新为 O( sqrt(len)*len )
 * 如果更新比较多，就分为  log(n)  个自动机，这样查询和更新都是  O( log(n)*len )
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define N 100010
#define M 5000010
struct AC_Automaton
{
    struct node
    {
        node *fail, *go[2];
        bool has[2]; // 记录是否有子节点方便构图
        int val, sum;
    };
    node mem[N], *q[N], *root, *cur;
    node *new_node()
    {
        memset(cur->go, 0, sizeof cur->go);
        memset(cur->has, 0, sizeof cur->has);
        cur->val = 0;
        return cur++;
    }
    void init()
    {
        root = cur = mem;
        root->fail = root;
        new_node();
        build();
    }
    void addword(char *s)
    {
        node *t = root;
        for(;*s;s++)
        {
            int w = *s - '0';
            if(!t->has[w])
                t->go[w] = new_node(), t->has[w] = 1;
            t = t->go[w];
        }
        t->val = 1;
        build();
    }
    void build()
    {
        for(node *t = mem; t!=cur;t++)t->sum = t->val;
        int r = 0;
        REP(i,2)
        if(root->has[i])q[r++] = root->go[i], root->go[i]->fail = root;
        else root->go[i] = root;
        REP(l,r)
        {
            node *t = q[l];
            REP(i,2)
            if(t->has[i])q[r++]=t->go[i],t->go[i]->fail = t->fail->go[i];
            else t->go[i] = t->fail->go[i];
            t->sum += t->fail->sum;
        }
    }
    void merge(AC_Automaton &ac)
    { // 合并 ac 到当前自动机里，并清空 ac
        int r = 0;
        ac.q[r] = ac.root;
        q[r++] = root;
        REP(l,r)
        {
            node *x = ac.q[l], *y = q[l];
            y->val |= x->val;
            REP(i,2)
            if(x->has[i])
            {
                if(!y->has[i])
                    y->go[i] = new_node(), y->has[i] = 1;
                ac.q[r] = x->go[i];
                q[r++] = y->go[i];
            }
        }
        ac.init();
        build();
    }
    int count(char *s)
    {
        int ret = 0;
        for(node *t = root;*s;s++)
        {
            t = t->go[*s - '0'];
            ret += t->sum;
        }
        return ret;
    }
    bool find(char *s)
    {
        node *t = root;
        for(;*s;s++)
        {
            int w =*s - '0';
            if(t->has[w])t = t->go[w];
            else return 0;
        }
        return t->val;
    }
    int size(){return cur-mem;}
};
AC_Automaton large, small;
char s[M];
int main()
{
    freopen("a","r",stdin);
    int t, n, cs = 0;
    scanf("%d",&t);
    while(t--)
    {
        printf("Case #%d:\n",++cs);
        scanf("%d",&n);
        int L = 0;
        large.init();
        small.init();
        while(n--)
        {
            scanf("%s", s);
            int len = strlen(s+1);
            rotate(s+1, s+1 + L%len, s+1+len);
            if(s[0]=='+')
            {
                if(large.find(s+1))continue;
                small.addword(s+1);
                if(small.size()>500) // 选定一个合适的大小，比如根号 n
                    large.merge(small);
            }
            else
            {
                L = large.count(s+1) + small.count(s+1);
                printf("%d\n",L);
            }
        }
    }
    return 0;
}
