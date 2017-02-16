#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void E();
void T();
void Td();
void Ed();
void F();
char operator_sym[10] = {'=','<','>','!','+','-','/','*','&','|'};
char identifier_sym[37] = {'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};

char cur_token[100];
char buffer[1000];
int lookahead = 0;
void error () {
    printf("Error\n");
}


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
    char c = buffer[lookahead++];
    
    int this = get_char_class(c);
    //printf("%c %d\n",c,this );
    int k=0;
    while (get_char_class(c) == this && c!=EOF && c!='\0') {
        cur_token[k++]=c;
        c = buffer[lookahead++];
    }
    cur_token[k] = '\0';
    //printf("<%s>\n",cur_token );
    lookahead--;
}

void E() {
    
    T();
    Ed();
}

void T() {
    
    F();
    Td();
}

void Ed() {

    if (strcmp(cur_token,"+") == 0) {
        
        getNextToken();
        printf("Pointing to %s\n",cur_token );
        T();
        Ed();
    }

}

void Td() {
    
    if (strcmp(cur_token,"*") == 0) {
        getNextToken();
        printf("Pointing to %s\n",cur_token );
        F();
        T();
    }
}
void F() {
    if (strcmp(cur_token,"(") == 0) {
        getNextToken();
        printf("Pointing to %s\n",cur_token );
        E();
        if (strcmp(cur_token,")") == 0) {
            getNextToken();
            printf("Pointing to %s\n",cur_token );
            return;
        }
        else {
            error();
            exit(0);
        }
    }
    else if (is_identifier(cur_token)) {
        
        getNextToken();
        printf("Pointing to %s\n",cur_token );
    }
    else {
        error();
        exit(0);
    }

}
int main()
{
    int count = 0;
    char filename[20];
    FILE *inputfile;
    printf("Enter filename: ");
    scanf("%s", filename);
    inputfile = fopen(filename, "r");
    char c;
    int i;
    do
    {
        c = fgetc(inputfile);
        buffer[count++]=c;
    }while (c!=EOF && c!='\n');
    buffer[count-1]='$';
    buffer[count]='\0';
    getNextToken();
    printf("Pointing to %s\n",cur_token);
    E();
    if (strcmp(cur_token,"$")==0)
        printf("Success\n");
    else 
        error();
}
