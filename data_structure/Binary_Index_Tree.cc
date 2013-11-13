#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
#define N 1010
struct BinaryIndexTree
{
    int w[N];
    int n;
    void init(int len)
    {
        n = len;
        memset(w, 0, (n+1)*sizeof(int) );
    }
    void insert(int x)
    {
        for(;x<=n; x += x&-x)w[x]++;
    }
    int query(int x)
    {
        int ret = 0;
        for(;x>0; x-= x&-x)ret += w[x];
        return ret;
    }
};
struct BinaryIndexTree2D
{
    int w[N][N];
    int n,m;
    void init(int lx, int ly)
    {
        n = lx, m = ly;
        memset( w, 0, sizeof w);
    }
    void insert(int x, int y, int val)
    {
        for(int i = x; i<=n; i += i&-i)
        {
            for(int j = y; j<=m; j += j&-j)
            {
                w[i][j] += val;
            }
        }
    }
    int query(int x, int y)
    {
        int ret = 0;
        for(int i = x; i>0; i -= i&-i)
        {
            for(int j = y; j>0; j -= j&-j)
            {
                ret += w[i][j];
            }
        }
        return ret;
    }
};
int main(int argc, char *argv[])
{
    return 0;
}
