#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void S();
void T();
void Td();

char operator_sym[10] = {'=','<','>','!','+','-','/','*','&','|'};
char identifier_sym[37] = {'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};
char buffer[100];
char p=0;
char cur_token[100];
int is_found(char c, char array[], int len)
{
    int i;
    for (i=0;i<len;i++)
        if (c == array[i])return 1;
    return 0;
}

int is_found_string(char *string, char *arr[], int n)
{
    int i;
    for (i=0;i<n;i++)
    {
        if (strcmp(string,arr[i])==0)
        {
            return i;
        }
    }
    return -1;
}

int get_char_class(char c)
{
    if (is_found(c, operator_sym, 10))return 1;
    else if (is_found(c, identifier_sym, 37))return 2;
    else if (c == '$')
    	return 3;
}


int is_identifier(char *buffer)
{
    int len = strlen(buffer);
    int i;
    for (i=0;i<len;i++)
    {
        if (!((buffer[i]>=65 && buffer[i]<91) || (buffer[i]>=97 && buffer[i]<123) || (buffer[i]=='_')))
            return 0;
    }
    return 1;
}

void getNextToken() {
	char c = buffer[p++];
	
	int this = get_char_class(c);
	//printf("%c %d\n",c,this );
	int k=0;
	while (get_char_class(c) == this && c!=EOF && c!='\0') {
		cur_token[k++]=c;
		c = buffer[p++];
	}
	cur_token[k] = '\0';
	//printf("<%s>\n",cur_token );
	p--;
}
void error () {
	printf("Error\n");
}

void Td() {
	
	if (buffer[p] == ',') {
		p++;
		printf("Pointing to %c\n",buffer[p] );
		S();
		Td();
	}
}

void T(){
	
	S();
	Td();

}


void S() {
	if (buffer[p]=='a')
    {
        p++;
        printf("Pointing at %c\n",buffer[p]);
        return;
    }
    if (buffer[p] == 'b') {
    	p++;
    	printf("Pointing at %c\n",buffer[p] );
    	return;
    }
    if (buffer[p]=='(')
    {
        p++;
        printf("Pointing at %c\n",buffer[p]);

        T();
        
        //printf("Pointing at %c\n",buffer[p]);
        if (buffer[p]==')')
        {
            p++;
            printf("Pointing at %c\n",buffer[p]);

            return;
        }
        else {
        	error();
        	
        	return;
        }
        
    }
}

int main(int argc, char const *argv[])
{
	FILE *src;
    char source[10];
    int i;
    scanf("%s",source);
	src = fopen(source,"r");

	char c;
	do {
		c = fgetc(src);
		buffer[i++]=c;
	}while (c!=EOF && c!='\n');
	buffer[i-1]='$';
	//buffer[i]='\0';
	//printf("%s\n",buffer );
	printf("Pointing to %c\n",buffer[p] );
	S();
	//getNextToken();
	if (buffer[p] == '$')
		printf("Success\n");
    else 
    	error();
	return 0;
}