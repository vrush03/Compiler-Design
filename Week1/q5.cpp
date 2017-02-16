#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
	FILE *f1,*f2;
	char s[100],s2[100],c1,c2;
	int l = 0,ch =0;
	printf("Enter 1st File:\n");
	scanf("%s",s);
	f1 = fopen(s,"rw");

	printf("Enter 2nd File:\n");
	scanf("%s",s2);
	f2 = fopen(s2,"rw");
	c1 = fgetc(f1);
	c2 = fgetc(f2);
	while(c1!=EOF && c2!=EOF) {
		if (c1!=c2) {
			printf("These Files does not have Equal Content\n");
			return 0;
		}
		
		c1 = fgetc(f1);
		c2 = fgetc(f2);
	}
	printf("These Files have Equal Content\n");
	return 0; 
}