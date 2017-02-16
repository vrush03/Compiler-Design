#include <stdio.h>
#include <stdlib.h>

char buffer[1000];
int lookahead=0;

void S();
void A();
void B();
void Ad();

void error()
{
    printf("Error\n");
    exit(0);
}

void S()
{
    if (buffer[lookahead]=='a')
    {
        lookahead++;
        printf("Pointing to %c\n", buffer[lookahead]);
        A();
        if (buffer[lookahead]=='c')
        {
            lookahead++;
            printf("Pointing to %c\n", buffer[lookahead]);
            B();
            if (buffer[lookahead]=='e')
            {
                lookahead++;
                printf("Pointing to %c\n", buffer[lookahead]);
                return;
            }
            else error();
        }
        else error();
    }
    else error();
}

void B()
{
    if (buffer[lookahead]=='d')
    {
        lookahead++;
        printf("Pointing to %c\n", buffer[lookahead]);
        return;
    }
}

void A()
{
    if (buffer[lookahead]=='b')
    {
        lookahead++;
        printf("Pointing to %c\n", buffer[lookahead]);
        Ad();
    }
    else error();
}

void Ad()
{
    if (buffer[lookahead]=='b')
    {
        lookahead++;
        printf("Pointing to %c\n", buffer[lookahead]);
        Ad();
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
    printf("Pointing to %c\n", buffer[lookahead]);
    S();
    if (buffer[lookahead]=='$')
        printf("Success\n");
    else 
        error();
}
