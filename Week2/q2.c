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
	
	while (c != EOF) {

		//printf("%c",c );
		if (c == '/') {
			//printf("%c Commenthere\n",c );
			while(c!='\n') {
				c=fgetc(f1);
				printf("%c",c );
				fprintf(f2, "%c",c );
			}
			
		}
		if (c == '\"') {
			
			while(c!='\n') {
				c=fgetc(f1);
				printf("%c",c );
				fprintf(f2, "%c",c );
			}
			//fprintf(f2, "\"\n");
			
		}
		if(c == '#') {
			while (c!='\n') {
				c = fgetc(f1);
				//printf("In: %c ",c );
			}
		}
		//printf(" register");
				
		fprintf(f2, "%c",c );
		c = fgetc(f1);
	}
	fclose(f1);
	fclose(f2);
	//printf("Lines :%d  Characters:%d \n",l,ch );
	return 0; 
}