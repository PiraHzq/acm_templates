void ST()
{  
    int i,j,k;  
    for(j=1;(1<<j)<=n;++j)  
        for(i=1;i+(1<<j)-1<=n;++i)  
        {  
            k=i+(1<<(j-1));  
            f[i][j]=max(f[i][j-1],f[k][j-1]);  
        }  
}  
int Query(int l,int r)  
{  
    int m=0;  
    while(l+(1<<m)<r-(1<<m)+1)++m;  
    r=r-(1<<m)+1;  
    return max(f[l][m],f[r][m]);  
}
//二维RMQ
int log2(int x)  
{  
    int k=0;  
    while((1<<(k+1))<x)++k;  
    return k;  
}  
void ST()  
{  
    int i,j,u,v,logn=log2(n),logm=log2(m);  
    for(u=0;u<=logn;++u)  
        for(v=0;v<=logm;++v)  
            if(u+v)for(i=1;i+(1<<u)-1<=n;++i)  
                for(j=1;j+(1<<v)-1<=m;++j)  
                if(v==0)f[i][j][u][v]=max(f[i][j][u-1][v],f[i+(1<<(u-1))][j][u-1][v]);  
                else f[i][j][u][v]=max(f[i][j][u][v-1],f[i][j+(1<<(v-1))][u][v-1]);  
}  
int get(int r1,int c1,int r2,int c2)  
{  
    int k=log2(r2-r1+1),t=log2(c2-c1+1);  
    int a=max(f[r1][c1][k][t],f[r1][c2-(1<<t)+1][k][t]);  
    int b=max(f[r2-(1<<k)+1][c1][k][t],f[r2-(1<<k)+1][c2-(1<<t)+1][k][t]);  
    return max(a,b);  
}  
