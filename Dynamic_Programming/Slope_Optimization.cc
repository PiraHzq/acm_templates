#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define FOR(i,l,r) for(int i=l;i<=r;i++)
#define N 1010
int f[N][N];
int a[N], s[N], ss[N], q[N];
#define GX(i) (s[i-1])  //对应第 i 个点的 x 坐标
#define GY(i,j) (f[i-1][j-1]+ss[i-1])   //对应第 i 个点的 y 坐标
#define G(i,j,k) (GY(i,j) - (k)*GX(i))  //对应第 i 个点斜率为 k 的值
double slope(int p, int q, int j) // p q 两点的斜率
{
    return (double)(GY(q,j)-GY(p,j))/(GX(q)-GX(p));
}
int main(int argc, char **argv)
{
    int n, m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        if(n==0&&m==0)break;
        m++;
        ss[0] = s[0] = 0;
        FOR(i,1,n)
        {
            scanf("%d",&a[i]);
            s[i] = s[i-1] + a[i];
            ss[i] = ss[i-1] + a[i]*s[i];
        }
        REP(i,n+1)
            REP(j,m+1)
                f[i][j] = 1e9;
        f[0][0] = 0;
        FOR(j,1,m)
        {
            int l = 0, r = -1;
            FOR(i,1,n)
            {
                while(l<r && slope(q[r-1],q[r],j)>slope(q[r],i,j))r--;
                q[++r] = i;
                while(l<r && G(q[l],j,s[i])>=G(q[l+1],j,s[i]))l++;
                f[i][j] = G(q[l],j,s[i])+ s[i-1]*s[i] - ss[i-1];
            }
        }
        printf("%d\n",f[n][m]);
    }
    return 0;
}

