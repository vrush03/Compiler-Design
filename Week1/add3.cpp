#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
	FILE *f1,*f2;
	char s[100],c;
	string s2;
	//int l = 0,ch =0;
	scanf("%s",s);
	f1 = fopen(s,"rw");
	f2 = fopen("result","rw+");
	c = fgetc(f1);
	while (c != EOF) {

		s2+=c;
		c = fgetc(f1);
	}
	for(int i=s2.size()-1;i>=0;i--) {
		fprintf(f2, "%c",s2[i] );
	}
	fclose(f2);
	//printf("Lines :%d  Characters:%d \n",l,ch );
	return 0; 
}