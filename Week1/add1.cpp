#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
	FILE *f1,*f2,*f3;
	char s[100],s2[100],s3[100],c1,c2;
	int l = 0,ch =0;
	printf("Enter 1st File:\n");
	scanf("%s",s);
	f1 = fopen(s,"rw");

	printf("Enter 2nd File:\n");
	scanf("%s",s2);
	f2 = fopen(s2,"rw");
	scanf("%s",s3);
	f3 = fopen(s3,"rw+");

	while(!feof(f1) || !feof(f2)) {
		
		
		fscanf(f1,"%s",s);
		printf("%s\n",s );
		fprintf(f3,"%s\n",s);
		fscanf(f2,"%s",s2);
		printf("%s\n",s2 );
		fprintf(f3, "%s\n",s2 );
		
	}
	fclose(f3);
	
	return 0; 
}