#include<cstdio>  
#define mm 555555  
#define mn 999  
int U[mm],D[mm],L[mm],R[mm],C[mm];  
int H[mn],S[mn];  
int id[33][33];  
int n,m,p,size,T,ans;  
void remove(int c)  
{  
    L[R[c]]=L[c],R[L[c]]=R[c];  
    for(int i=D[c];i!=c;i=D[i])  
        for(int j=R[i];j!=i;j=R[j])  
            U[D[j]]=U[j],D[U[j]]=D[j],--S[C[j]];  
}  
void resume(int c)  
{  
    L[R[c]]=R[L[c]]=c;  
    for(int i=U[c];i!=c;i=U[i])  
        for(int j=L[i];j!=i;j=L[j])  
            ++S[C[U[D[j]]=D[U[j]]=j]];  
}  
void Dance(int k)  
{  
    if(k>=ans)return;  
    if(!R[0])  
    {  
        ans=k;  
        return;  
    }  
    int i,j,tmp,c;  
    for(tmp=mm,i=R[0];i;i=R[i])  
        if(S[i]<tmp)tmp=S[c=i];  
    remove(c);  
    for(i=D[c];i!=c;i=D[i])  
    {  
        for(j=R[i];j!=i;j=R[j])remove(C[j]);  
        Dance(k+1);  
        for(j=L[i];j!=i;j=L[j])resume(C[j]);  
    }  
    resume(c);  
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
void prepare(int r,int c)  
{  
    for(int i=0;i<=c;++i)  
    {  
        S[i]=0;  
        U[i]=D[i]=i;  
        R[i]=i+1;  
        L[i+1]=i;  
    }  
    R[c]=0;  
    while(r)H[r--]=-1;  
}  
int main()  
{  
    int i,j,k,x1,y1,x2,y2;  
    scanf("%d",&T);  
    while(T--)  
    {  
        scanf("%d%d%d",&n,&m,&p);  
        for(size=i=0;i<n;++i)  
            for(j=0;j<m;++j)id[i][j]=++size;  
        prepare(p,size);  
        for(k=1;k<=p;++k)  
        {  
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);  
            for(i=x1;i<x2;++i)  
                for(j=y1;j<y2;++j)Link(k,id[i][j]);  
        }  
        ans=mm;  
        Dance(0);  
        if(ans<mm)printf("%d\n",ans);  
        else puts("-1");  
    }  
    return 0;  
}  
