#include<cstdio>  
#define mm 55555  
#define mn 333  
int U[mm],D[mm],L[mm],R[mm],C[mm];  
int H[mn],S[mn],id[22][22];  
bool v[mn];  
int n,m,size,ans;  
void prepare(int r,int c)  
{  
    for(int i=0;i<=c;++i)  
    {  
        S[i]=0;  
        D[i]=U[i]=i;  
        L[i+1]=i;  
        R[i]=i+1;  
    }  
    R[c]=0;  
    while(r)H[r--]=-1;  
}  
int f()  
{  
    int i,j,c,ret=0;  
    for(c=R[0];c;c=R[c])v[c]=1;  
    for(c=R[0];c;c=R[c])  
        if(v[c])for(v[c]=0,++ret,i=D[c];i!=c;i=D[i])  
            for(j=R[i];j!=i;j=R[j])v[C[j]]=0;  
    return ret;  
}  
void remove(int c)  
{  
    for(int i=D[c];i!=c;i=D[i])  
        R[L[i]]=R[i],L[R[i]]=L[i];  
}  
void resume(int c)  
{  
    for(int i=U[c];i!=c;i=U[i])  
        R[L[i]]=L[R[i]]=i;  
}  
void Dance(int k)  
{  
    if(k+f()>=ans)return;  
    if(!R[0])  
    {  
        ans=k;  
        return;  
    }  
    int i,j,c,tmp=mm;  
    for(i=R[0];i;i=R[i])  
        if(S[i]<tmp)tmp=S[c=i];  
    for(i=D[c];i!=c;i=D[i])  
    {  
        remove(i);  
        for(j=R[i];j!=i;j=R[j])remove(j);  
        Dance(k+1);  
        for(j=L[i];j!=i;j=L[j])resume(j);  
        resume(i);  
    }  
}  
void Link(int r,int c)  
{  
    ++S[C[++size]=c];  
    D[size]=D[c];  
    U[D[c]]=size;  
    U[size]=c;  
    D[c]=size;  
    if(H[r]<0)H[r]=L[size]=R[size]=size;  
    else  
    {  
        R[size]=R[H[r]];  
        L[R[H[r]]]=size;  
        L[size]=H[r];  
        R[H[r]]=size;  
    }  
}  
int main()  
{  
    int i,j,k,l,mr,mc,r;  
    while(scanf("%d%d",&n,&m)!=-1)  
    {  
        for(size=0,i=1;i<=n;++i)  
            for(j=1;j<=m;++j)  
            {  
                scanf("%d",&k);  
                id[i][j]=(k)?++size:0;  
            }  
        scanf("%d%d",&mr,&mc);  
        prepare(n*m,size);  
        for(i=r=1;i<=n-mr+1;++i)  
            for(j=1;j<=m-mc+1;++j,++r)  
                for(k=i;k<i+mr;++k)  
                    for(l=j;l<j+mc;++l)  
                        if(id[k][l])Link(r,id[k][l]);  
        ans=n*m;  
        Dance(0);  
        printf("%d\n",ans);  
    }  
    return 0;  
}  
