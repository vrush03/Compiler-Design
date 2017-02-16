#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *keywords[32] = {"auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};

int isPresent (char s[]) {
	int i;
	for (i=0;i<32;i++) {
		if (strcmp(s,keywords[i]) == 0)
			return 1;
	}
	return 0;
}
int main(int argc, char const *argv[])
{
	FILE *f1,*f2;
	char s[100],s2[100],c,final[1000][1000],k=0;
	//int l = 0,ch =0;
	scanf("%s",s);
	f1 = fopen(s,"r");
	
	scanf("%s",s2);
	f2 = fopen(s2,"rw+");
	c = fgetc(f1);
	//printf("%c\n",c );
	while (!feof(f1)) {
		fscanf(f1,"%s",s);
		if (isPresent(s)) {
			int i;
			for (i=0;i<strlen(s);i++) {
				s[i] = s[i] + ('A' - 'a');
			}
			strcpy(final[k++],s);
			//printf("%s\n",s );
		}	
	
	}
	for (int i=0;i<k;i++) {
		printf("%s\n",final[i] );
	}
	fclose(f1);
	fclose(f2);
	//printf("Lines :%d  Characters:%d \n",l,ch );
	return 0; 
}