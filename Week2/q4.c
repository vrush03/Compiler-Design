#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	FILE *f1,*f2;
	char s[100],s2[100],c;
	int l = 0,ch =0;
	scanf("%s",s);
	f1 = fopen(s,"r");
	
	scanf("%s",s2);
	f2 = fopen(s2,"rw+");
	c = fgetc(f1);
	//printf("%c\n",c );
	while (c != EOF) {

		if (c == '\n' || c == '\t') {
			c = fgetc(f1);
			continue;
		}
		//printf("Out: %c ",c );
		fprintf(f2, "%c",c );
		c = fgetc(f1);
	}
	fclose(f1);
	fclose(f2);
	//printf("Lines :%d  Characters:%d \n",l,ch );
	return 0; 
}