/*************************************************************
 * Filename: PRIME_CC
 * Author: Pira 
 * Date: 2013-09-23 14:19:56
 **************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
#define N 100010
#define M 1000010

int p[N];
bool a[M];
void Prime(bool a[], int p[], int n, int &num)
{
	memset(a, 0, n*sizeof(bool));
	num = 0;
	for(int i = 2; i < n; ++i) 
	{
		if( !a[i] ) p[ num++ ] = i;
		for(int j = 0; j<num && i*p[j]<n; ++j)
		{
			a[ i*p[j] ] = 1;
			if( !(i%p[j]) ) break;
		}
	}
}
int main(int argc, char *argv[])
{
	int n;
	Prime(a, p, 1000000, n);//Generate prime numbers less than 1 million
	return 0;
}
