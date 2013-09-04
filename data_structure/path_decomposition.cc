/*************************************************************
 * Filename: PATH_DECOMPOSITION_CC
 * Author: Pira 
 * Date: 2013-09-04 10:50:11
 * Problem: bzoj 2243
 **************************************************************/
#include   <cstdio>
#include   <iostream>
#include   <vector>
using namespace std;
#define N 200010
#define oo 1000000000
/*********************tree code*********************/
vector<int> edge[N];
struct tree
{
	int root,pos,deep,fa,top,mson,val,size;
};
tree p[N];
int temp[N];
/*********************segment tree*********************/
struct node
{
	node *ls,*rs;
	int ans,mark,lc,rc;
	node(){}
	node(const node &a, const node &b)
	{
		ans=a.ans + b.ans - (a.rc == b.lc);
		lc=a.lc;
		rc=b.rc;
	}
	void up()
	{
		ans=ls->ans + rs->ans - (ls->rc == rs->lc);
		lc=ls->lc;
		rc=rs->rc;
	}
	void change(int c)
	{
		lc=rc=mark=c;
		ans=1;
	}
	void down()
	{
		if(mark>=0)
		{
			ls->change(mark);
			rs->change(mark);
			mark=-1;
		}
	}
};
node memPool[N<<2],*root[N],*cur;
int len[N],id;
void init()
{
	id=0;
	cur=memPool;
}
node *newNode(int c)
{
	cur->change(c);
	cur->mark=-1;
	return cur++;
}
void build(int l, int r, node* &now)
{
	if(l+1>=r)
	{
		now=newNode(temp[l]);
		return;
	}
	now=newNode(0);
	int m=(l+r)>>1;
	build(l,m,now->ls);
	build(m,r,now->rs);
	now->up();
}
void update(int a, int b, int c, int l, int r, node *now)
{
	if(a<=l && b+1>=r)
	{
		now->change(c);
		return ;
	}
	int m=(l+r)>>1;
	now->down();
	if(a<m)update(a,b,c,l,m,now->ls);
	if(b>=m)update(a,b,c,m,r,now->rs);
	now->up();
}
node query(int a, int b, int l, int r, node *now)
{
	if(a<=l && b+1>=r)
	{
		return *now;
	}
	int m=(l+r)>>1;
	now->down();
	if(b<m)return query(a,b,l,m,now->ls);
	if(a>=m)return query(a,b,m,r,now->rs);
	return node( query(a,b,l,m,now->ls), query(a,b,m,r,now->rs) );
}
/*********************main part*********************/
void chain(int x)
{
	int &n=len[id];
	int top=x;
	while(x)
	{
		temp[n]=p[x].val;
		p[x].pos=n++;
		p[x].root=id;
		p[x].top=top;
		x=p[x].mson;
	}
	build(0,n,root[id++]);
}
void dfs(int u, int deep)
{
	p[u].size=1;
	p[u].deep=deep;
	p[u].mson=0;
	int n=edge[u].size();
	int v,msize=0;
	for(int i=0; i<n; i++)
	{
		if((v=edge[u][i])!=p[u].fa)
		{
			p[v].fa=u;
			dfs(v,deep+1);
			p[u].size+=p[v].size;
			if(p[v].size>msize)
			{
				if(msize)chain(p[u].mson);
				p[u].mson=v;
				msize=p[v].size;
			}
			else
			{
				chain(v);
			}
		}
	}
}
void change(int u, int v, int c)
{
	while(p[u].top!=p[v].top)
	{
		if(p[ p[u].top ].deep<p[ p[v].top ].deep)
		{
			swap(u,v);
		}
		update(0,p[u].pos,c,0,len[ p[u].root ], root[ p[u].root ]);
		u=p[ p[u].top ].fa;
	}
	if(p[u].pos>p[v].pos)
	{
		swap(u,v);
	}
	update(p[u].pos,p[v].pos,c,0,len[ p[u].root ], root[ p[u].root ]);
}
int answer(int u, int v)
{
	int ret=0,a=-1,b=-1;
	while(p[u].top!=p[v].top)
	{
		if(p[ p[u].top ].deep<p[ p[v].top ].deep)
		{
			swap(u,v);
			swap(a,b);
		}
		node now=query(0,p[u].pos,0,len[ p[u].root ], root[ p[u].root ]);
		ret+=now.ans - (now.rc==a);
		a=now.lc;
		u=p[ p[u].top ].fa;
	}
	if(p[u].pos>p[v].pos)
	{
		swap(u,v);
		swap(a,b);
	}
	node now=query(p[u].pos,p[v].pos,0,len[ p[u].root ], root[ p[u].root ]);
	ret+=now.ans - (now.lc==a) - (now.rc==b);
	return ret;
}
int main(int argc, char *argv[])
{
	int n,m,a,b,c;
	char op[99];
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i++)
	{
		edge[i].clear();
		scanf("%d",&p[i].val);
	}
	for(int i = 1; i < n; i++)
	{
		scanf("%d%d",&a,&b);
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	init();
	dfs(1,1);
	chain(1);
	while(m--)
	{
		scanf("%s%d%d",op,&a,&b);
		if(op[0]=='C')
		{
			scanf("%d",&c);
			change(a,b,c);
		}
		else
		{
			printf("%d\r\n",answer(a,b));
		}
	}
	return 0;
}

