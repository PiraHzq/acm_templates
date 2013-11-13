#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
#define N 220010
char s[N],str[N];
int ans[N];
int Manacher(char src[], char tmp[], int len[])
{
    int i,j,k,rightmost,n=strlen(src),ret=0;
    tmp[0]='$';
    tmp[1]='#';
    for(i=0;i<n;++i)
    {
        tmp[i*2+2]=src[i];//i*2+2 为原串的 i 为中心的最长回文
        tmp[i*2+3]='#';
    }
    n=n*2+2;
    tmp[n]='\0';
    for(i=0;i<n;++i)len[i]=0;
    rightmost=k=0;
    for(i=1;i<n;++i)
    {
        if(rightmost>=i)len[i]=min(len[2*k-i],rightmost-i);
        else len[i]=0;
        for(j=len[i]+1;tmp[i+j]==tmp[i-j];++j)++len[i];
        if(i+len[i]>rightmost)
        {
            rightmost=i+len[i];
            k=i;
        }
        ret=max(ret,len[i]);
    }
    return ret;
}
int main()
{
    while(~scanf("%s",str))
        printf("%d\n",Manacher(str,s,ans));
    return 0;
}
