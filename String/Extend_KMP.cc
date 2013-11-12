#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define FOR(i,l,r) for(int i=l;i<=r;i++)
#define N 1000010
int s[N], p[N];
int a[N], b[N];
int extend_kmp(int p[], int a[], int n, int s[] , int b[], int m)
{//p表示模式串
    int k = 0;
    FOR(i,1,n-1)
    {
        if( k>0 && a[i-k] < a[k] + k - i )
            a[i] = a[i-k];
        else
        {
            int j = k>0?a[k] + k - i: 0;
            if(j<0)j =0;
            while( i+j<n && p[j] == p[i+j] ) j++;
            a[ k = i ] = j;
        }
    }
    k = 0;
    REP(i,m)
    {
        if(k>0 && a[i-k] < b[k] + k - i)
            b[i] = a[i-k];
        else
        {
            int j = k>0?b[k]+k-i:0;
            if(j<0)j=0;
            while( i+j<m && p[j] == s[i+j] )j++;
            b[ k = i] = j;
            if(j>=n)return i+1;
        }
    }
    return -1;
}
int main(int argc, char **argv)
{
    int t, n, m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        REP(i,n)scanf("%d",&s[i]);
        REP(i,m)scanf("%d",&p[i]);
        printf("%d\n",extend_kmp(p,a,m, s, b,n));
    }
    return 0;
}
