#include   <cstdio>
#include   <iostream>
using namespace std;
#define N 200010
#define oo 1000000000

struct node
{
    node *son[2];
    int size,key;
};
node mem[N], *cur, *til=mem;
int pool[N], top;
node *newNode(int val)
{
    node *ret = top? mem + pool[ --top ] : cur++;
    ret->key = val;
    ret->size = 1;
    ret->son[0] = ret->son[1] = til;
    return ret++;
}
void dump(node *x)
{
    pool[ top++ ] = x-mem;
}
void initAll()
{
    top = 0;
    cur = mem;
    til = newNode(0);
    til->size = 0;
}


struct SizeBalancedTree
{
    node *root;
    SizeBalancedTree():root(til){}

    void rotate(node *&x, int c)
    {
        node *y = x->son[!c];
        x->son[!c] = y->son[c];
        y->son[c] = x;
        y->size = x->size;
        x->size = x->son[0]->size + x->son[1]->size + 1;
        x=y;
    }
    void maintain(node *&x, int c)
    {
        node *&y = x->son[c];
        if( y->son[c]->size > x->son[!c]->size )
        {
            rotate( x , !c );
        }
        else if( y->son[!c]->size > x->son[!c]->size )
        {
            rotate( y , c );
            rotate( x , !c );
        }
        else return;

        maintain( x->son[0] , 0 );
        maintain( x->son[1] , 1 );
        maintain( x , 0 );
        maintain( x , 1 );
    }
    void insert(int val)
    {
        insert( root, val );
    }
    void insert(node *&x, int val)
    {
        if( x == til )
        {
            x = newNode( val );
        }
        else
        {
            x->size++;
            insert( x->son[ val >= x->key ] , val );
            maintain( x , val >= x->key );
        }
    }
    bool find(int val)
    {
        node *x = root;
        do
        {
            if( val == x->key )
            {
                return true;
            }
            x = x->son[ val > x->key ];
        }
        while( x!= til );
        return false;
    }
    void erase(int val)
    {
        if( find( val ) )
        {
            erase( root , val );
        }
    }
    int erase(node *&x, int val)
    {
        x->size--;
        node *&y = x->son[ val > x->key ];
        if( val == x->key || y == til )
        {
            int ret = x->key;
            if( y == til )
            {
                dump( x );
                x = x->son[ val <= x->key ];
            }
            else
            {
                x->key = erase( y , val );
            }
            return ret;
        }
        else
        {
            return erase( y ,val );
        }
    }
    void pre_suc(int &pre, int &suc, int val)
    {
        node *x = root;
        pre = -oo, suc = oo;
        do
        {
            if( val == x->key )
            {
                pre = suc = val;
                return ;
            }
            if( val > x->key )
            {
                pre = max( pre , x->key );
            }
            else
            {
                suc = min( suc , x->key );
            }
            x = x->son[ val >= x->key ];
        }
        while( x != til );
    }
    int below(int val)
    {
        node *x = root;
        int ret = 0;
        do
        {
            if( val >= x->key )
            {
                ret += x->son[0]->size + 1;
            }
            x = x->son[ val >= x->key ];
        }
        while( x != til );
        return ret;
    }
};
int main()
{
    return 0;
}
