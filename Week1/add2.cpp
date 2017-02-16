#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
	FILE *f1;
	char s[100],c,prev;
	int l = 0,ch =0,bl = 0,sp = 0;
	scanf("%s",s);
	f1 = fopen(s,"rw");
	c = fgetc(f1);
	prev = c;
	while (c != EOF) {
		
		if(c == ' ')
			sp++;
		if(c == ';')
			l++;
		if(prev == '\n' && c == '\n')
			bl++;	
		prev = c;
		c = fgetc(f1);
	}
	printf("Semi Colon Lines :%d  Blank Spaces :%d  Blank Lines :%d \n",l,sp,bl );
	return 0; 
}