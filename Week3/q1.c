#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *keywords[32] = {"auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};
char spec_char[8] = {'(',')','{','}',';',',','[',']'};
char operator_sym[10] = {'=','<','>','!','+','-','/','*','&','|'};
char identifier_sym[37] = {'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};
const int alphanum=0, specialchar=1, operator=2;

int is_found(char c, char array[], int len)
{
	int i;
	for (i=0;i<len;i++)
		if (c == array[i])return 1;
	return 0;
}

int is_keyword(char *string)
{
	int i;
	for (i=0;i<32;i++)
	{
		if (strcmp(string,keywords[i])==0)
		{
			return 1;
		}
	}
	return 0;
}

int get_char_class(char c)
{
	if (is_found(c, spec_char, 8))return specialchar;
	else if (is_found(c, operator_sym, 10))return operator;
	else if (is_found(c, identifier_sym, 37))return alphanum;
	else return -1;
}

void handle_exceptions(char c, FILE *src)
{
	if (c == '\"')
		{
			c = fgetc(src);
            while (c!='\"')
            {
                c = fgetc(src);
            }
		}
		else if (c == '\'')
        {
            c = fgetc(src);
            while (c!='\'')
            {
                c = fgetc(src);
            }
        }
        else if (c == '#')
        {
        	while(c!='\n')
        		c = fgetc(src);
        }
        else if (c=='\n')
        {
        	printf("\n");
        }
}

int find_token(char *buffer, FILE *src)
{
	char c = fgetc(src);
	int this_class = get_char_class(c);
	int k=0;
	if (c == EOF)
	{
		buffer[0] = EOF;
		return -1;
	}
	if (this_class<0)
	{
		handle_exceptions(c, src);
        return this_class;
	}
	if (this_class == 1)
	{
		buffer[0] = c;
		buffer[1] = '\0';
		return this_class;
	}
	while (get_char_class(c) == this_class && c != EOF)
	{
			buffer[k++] = c;
			c = fgetc(src);
	}
	buffer[k]='\0';
	fseek(src, -1, SEEK_CUR);
	
	return this_class;
}

int main()
{
    FILE *src,*src2;
    char source[10];
    int count=0;
    scanf("%s",source);
    src = fopen(source,"r");
    //src2 = fopen(source,"r");
    //fgetc(src2);
    char buffer[50],buffer2[1000];
    do
    {
    	int class = find_token(buffer, src);
    	//int class2 = find_token(buffer2, src2);
    	if(buffer[0]==EOF)break;
    	switch (class)
    	{
    		case 2:printf("<%s> ",buffer);
    					     break;
 			case 1:printf("<%s> ",buffer);
 						  break;
 			case 0:if (is_keyword(buffer))
 						  {
 						  	  printf("<%s> ", buffer);
 						  }
 					else {
 						printf("<id,%d>\n",count );
 						count++;
 						}
 					break;
 					
 			default:break;
    	}
    }while (buffer[0] != EOF);
    return 1;
}