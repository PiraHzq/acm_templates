点稀疏算法：
struct point  
{  
    int x,y;  
}map[maxn];  
int i,j,k,n,L,W,high,low,best,maxl;  
inline bool cmp(point a,point b)  
{  
    return a.x<b.x||(a.x==b.x&&a.y<b.y);  
}  
inline void max(int a)  
{  
    if(a>best)best=a;  
}  
int main()  
{  
    while(scanf("%d%d",&L,&W)!=EOF)  
    {  
        scanf("%d",&n);  
        for(i=0;i<n;++i)scanf("%d%d",&map[i].x,&map[i].y);  
        map[n].x=map[n].y=0;  
        map[++n].x=L,map[n].y=W;  
        map[++n].x=L,map[n].y=0;  
        map[++n].x=0,map[n++].y=W;  
        sort(map,map+n,cmp);  
        for(best=i=0;i<n;++i)  
        {  
            for(low=0,high=W,maxl=L-map[i].x,j=i+1;j<n;++j)  
                if(low<=map[j].y&&map[j].y<=high)  
                {  
                    if(maxl*(high-low)<=best)break;  
                    max((map[j].x-map[i].x)*(high-low));  
                    if(map[j].y==map[i].y)break;  
                    if(map[j].y>map[i].y)high=map[j].y;else low=map[j].y;  
                }  
            for(low=0,high=W,maxl=map[i].x,j=i-1;j>=0;--j)  
                if(low<=map[j].y&&map[j].y<=high)  
                {  
                    if(maxl*(high-low)<=best)break;  
                    max((map[i].x-map[j].x)*(high-low));  
                    if(map[j].y==map[i].y)break;  
                    if(map[j].y>map[i].y)high=map[j].y;else low=map[j].y;  
                }  
        }  
        printf("%d/n",best);  
    }  
}

点密集格点算法：
int l[maxn],r[maxn],h[maxn],s[maxn][maxn]={0},now,ans,lm,rm,i,j,k,n,m;  
int main()  
{  
    scanf("%d%d",&n,&m);  
    for(i=0;i<m;++i)h[i]=0,l[i]=1,r[i]=m;  
    for(ans=0,i=1;i<=n;++i)  
    {  
        for(k=lm=0,j=1;j<=m;++j)  
        {  
            scanf("%d",&now),k+=now,s[i][j]=s[i-1][j]+k;  
            if(now)  
            {  
                h[j]=h[j]+1;  
                if(lm>l[j])l[j]=lm;  
            }  
            else h[j]=0,l[j]=1,r[j]=m,lm=j+1;  
        }  
        for(j=rm=m;j>0;--j)  
            if(h[j])  
            {  
                if(r[j]>rm)r[j]=rm;  
                now=s[i][r[j]]+s[i-h[j]][l[j]-1]-s[i-h[j]][r[j]]-s[i][l[j]-1];  
                if(now>ans)ans=now;  
            }  
            else rm=j-1;  
    }  
    printf("%d/n",ans);  
}  
