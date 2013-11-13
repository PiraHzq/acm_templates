void multi_pack(int s, int v, int c, int n)
{
    REP(i,c)
    {
        int l = 0, r = -1, m = (n+c-1)/c;
        FOR(j,0,m)
        {
            int p = j*c + i;
            int now = f1[p] - j*v;
            while(l<=r && w[r]<= now)r--;
            w[++r] = now;
            q[r] = j;
            if(j - q[l]>s)l++;
            f[p] = max( f[p], w[l] + j*v);
        }
    }
}
