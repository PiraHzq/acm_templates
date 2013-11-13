//询问大平面里维护少数点，询问矩形内内信息
struct retange  
{  
    int x1,y1,x2,y2;  
    retange(){}  
    retange(int x1, int y1, int x2, int y2):x1(x1),y1(y1),x2(x2),y2(y2){}  
    bool cover(const retange &a)const  
    {  
        if(x1>a.x1||x2<a.x2||y1>a.y1||y2<a.y2)return 0;  
        return 1;  
    }  
    bool interset(const retange &a)const  
    {  
        if(x1>a.x2||y1>a.y2||a.x1>x2||a.y1>y2)return 0;  
        return 1;  
    }  
    bool ok()  
    {  
        return x1>=x2&&y1>=y2;  
    }  
    int mx()  
    {  
        return (x1+x2)>>1;  
    }  
    int my()  
    {  
        return (y1+y2)>>1;  
    }  
    void rd(char *s)  
    {  
        sscanf(s,"%d%d%d%d",&x1,&x2,&y1,&y2);  
    }  
};  
struct Node  
{  
    retange r;  
    Node *son[4];  
    LL sum;  
}TNode,*nil=&TNode;  
Node mem[N],*C=mem;  
Node* Create(retange r)  
{  
    C->r=r;  
    C->sum=0;  
    REP(i,4)C->son[i]=nil;  
    return C++;  
}  
void Update(int x, int y, int n, Node *now)  
{  
    now->sum+=n;  
    while(1)  
    {  
        int mx=now->r.mx();  
        int my=now->r.my();  
        if(x<=mx)  
        {  
            if(y<=my)  
            {  
                if(now->son[0]==nil)  
                    now->son[0]=Create(retange(now->r.x1,now->r.y1,mx,my));  
                now=now->son[0];  
            }  
            else  
            {  
                if(now->son[1]==nil)  
                    now->son[1]=Create(retange(now->r.x1,my+1,mx,now->r.y2));  
                now=now->son[1];  
            }  
        }  
        else  
        {  
            if(y<=my)  
            {  
                if(now->son[2]==nil)  
                    now->son[2]=Create(retange(mx+1,now->r.y1,now->r.x2,my));  
                now=now->son[2];  
            }  
            else  
            {  
                if(now->son[3]==nil)  
                    now->son[3]=Create(retange(mx+1,my+1,now->r.x2,now->r.y2));  
                now=now->son[3];  
            }  
        }  
        now->sum+=n;  
        if(now->r.ok())break;  
    }  
}  
LL Query(retange r, Node *now)  
{  
    if(r.cover(now->r))return now->sum;  
    LL ret=0;  
    REP(i,4)  
        if(now->son[i]!=nil&&now->son[i]->r.interset(r))  
            ret+=Query(r,now->son[i]);  
    return ret;  
}  
