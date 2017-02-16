#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
	FILE *f1;
	char s[100],c;
	int l = 0,ch =0;
	scanf("%s",s);
	f1 = fopen(s,"rw");
	fseek(f1,0,SEEK_END);
	int ans = ftell(f1);
	printf("Size: %d Bytes\n",ans );
	return 0; 
}