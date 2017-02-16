#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
	FILE *f1;
	char s[100],c;
	int l = 0,ch =0;
	scanf("%s",s);
	f1 = fopen(s,"rw");
	c = fgetc(f1);
	while (c != EOF) {

		
		if(c == '\n')
			l++;
		ch++;
		c = fgetc(f1);
	}
	printf("Lines :%d  Characters:%d \n",l,ch );
	return 0; 
}