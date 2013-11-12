#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define FOR(i,l,r) for(int i=l;i<=r;i++)
#define DWN(i,r,l) for(int i=r;i>=l;i--)
#define N 200010
struct suffixarray
{
    int sa[N], rank[N], height[N];
    int s[N], cnt[N];
    int *x, *y, n, m;
    void radixsort()
    {
        REP(i,n)s[i]=x[y[i]];
        REP(i,m)cnt[i]=0;
        REP(i,n)cnt[s[i]]++;
        REP(i,m)cnt[i+1]+=cnt[i];
        DWN(i,n-1,0)sa[--cnt[s[i]]]=y[i];
    }
    bool cmp(int a, int b, int l)
    {
        return y[a]==y[b] && y[a+l]==y[b+l];
    }
    void da(int *str, int len, int cset)
    {
        x = rank, y = height;
        n = len, m = cset;
        REP(i,n)x[i]=str[i], y[i]=i;
        radixsort();
        int j=1,p=0;
        for(;p<n;j*=2,m=p+1)
        {
            p=0;
            FOR(i,n-j,n-1)y[p++]=i;
            REP(i,n)if(sa[i]>=j)y[p++]=sa[i]-j;
            radixsort();
            swap(x,y);
            x[sa[0]]=p=1;
            FOR(i,1,n-1)x[sa[i]]=cmp(sa[i],sa[i-1],j)?p:++p;
        }
        REP(i,n)rank[sa[i]]=i;
        p=0;
        REP(i,n)
        {
            if(p)p--;
            if(rank[i])for(j=sa[rank[i]-1];str[i+p]==str[j+p];p++);
            else p=0;
            height[rank[i]]=p;
        }
    }
};
suffixarray sa;
int main(int argc, char *argv[])
{
	return 0;
}
