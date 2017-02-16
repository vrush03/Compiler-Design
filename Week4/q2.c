#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *keywords[32] = {"auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};
char spec_char[6] = {'(',')','{','}',';',','};
char operator_sym[10] = {'=','<','>','!','+','-','/','*','&','|'};
char identifier_sym[37] = {'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};
const int alphanum=0, specialchar=1, operator=2;
int id_count=0;
char *datatype[6] = {"double", "int", "char", "float", "void", "func"};
int cur_flag = -1;

typedef struct symboltable
{
    int index;
    char *name;
    char *type;
    int size;
    char scope;
    int arg_no;
    int args[10];
    char *returntype;
    struct symboltable *next;
}symtable;

symtable **array;

void insert (symtable entry)
{
    int len=strlen(entry.name);
    if (array[len%8]==NULL)
    {
        array[len%8]=malloc(sizeof(symtable));
        *(array[len%8]) = entry;
        array[len%8]->next=NULL;
    }
    else
    {
        symtable *temp=array[len%8];
        while (temp->next != NULL)
            temp=temp->next;
        temp->next = malloc(sizeof(symtable));
        *(temp->next) = entry;
        temp->next->next=NULL;
    }

}

void print_sym_table()
{
    int i;
    symtable *temp;
    printf("\nIndex\tName\tType\tSize\tScope\tNArgs\tArguments\tReturn Type\n");
    for (i=0;i<8;i++)
    {
        temp = array[i];
        while (temp != NULL)
        {
            printf("%d\t%s\t%s",temp->index, temp->name, temp->type);
            if (strcmp(temp->type,"func")==0)
            {
               printf("\t\t%c\t%d\t",temp->scope,temp->arg_no);
               if (temp->arg_no==0)printf("NULL");
               else
               {
                   int p;
                   for (p=0;p<temp->arg_no;p++)
                       printf("<id, %d> ", temp->args[p]);
               }
               printf("\t%s\n", temp->returntype);
            }

            else printf("\t%d\t%c\n", temp->size, temp->scope);

            temp = temp->next;
        }
    }
}

int search_sym_table(char *buffer)
{
    int i;
    symtable *temp;
    temp = array[strlen(buffer)%8];
    while (temp!=NULL)
    {
        if (strcmp(temp->name, buffer)==0)
            return temp->index;
        temp=temp->next;
    }
    return -1;
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
    if (is_found(c, spec_char, 6))return specialchar;
    else if (is_found(c, operator_sym, 10))return operator;
    else if (is_found(c, identifier_sym, 37))return alphanum;
    else return -1;
}

void handle_exceptions(char c, FILE *src)
{
    if (c == '\"')
    {
        char prev = c;
       
        c = fgetc(src);
        // if (c == '\\')
        //   c = fgetc(src);

        while (c!='\"' )
        {
            //printf("%c %c\n",c,prev );
            //prev=c;
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

int look_for_function(char *buffer,char *source, FILE *src)
{
    long n = ftell(src);
    FILE *new = fopen(source,"r");
    fseek(new, (int)n, SEEK_SET);
    char c=fgetc(new);
    while ((c==' ' || c=='\t') && c!=EOF)
    {
        c=fgetc(new);
    }
    if (c!='(')return 0;
    symtable entry;
    entry.index = ++id_count;
    entry.name=malloc(strlen(buffer));
    entry.type=malloc(10);
    entry.returntype=malloc(10);
    strcpy(entry.name,buffer);
    strcpy(entry.type,"func");
    strcpy(entry.returntype, datatype[cur_flag]);
    entry.arg_no=0;
    entry.scope='g';
    char *newbuf=malloc(20);
    int j, dataflag;
    do
    {
      j=find_token(newbuf, new);
      if (j == 0)
      {
          int b = is_found_string(newbuf, datatype, 5);
          if (b >= 0)
          {
              dataflag = b;
          } 
          else
          {
             symtable entryarg;
             entryarg.index = ++id_count;
             entryarg.name=malloc(strlen(newbuf));
             entryarg.type=malloc(10);
             strcpy(entryarg.name, newbuf);
             strcpy(entryarg.type, datatype[dataflag]);
             entryarg.scope = 'l';
             entryarg.size = cur_flag == 0?16:(cur_flag == 1?4:(cur_flag == 2?1:(cur_flag == 3?8:0)));
             entryarg.arg_no=0;
             insert(entryarg);
             entry.args[entry.arg_no++] = entryarg.index;
          }
      }  
    }while (strcmp(newbuf, ")")!=0);
    insert(entry);
    cur_flag=5;
    fclose(new);
    return 1;
}

int main()
{
    FILE *src;
    char source[10];
    int i;
    array=malloc(8*sizeof(symtable*));
    for (i=0;i<8;i++)
        array[i]=NULL;
    //printf("Enter source file: ");
    scanf("%s",source);
    symtable entry;
    src = fopen(source,"r");
    char buffer[50];
    do
    {
        int class = find_token(buffer, src);
        if(buffer[0]==EOF)break;
        switch (class)
        {
            case 2:printf("<%s> ",buffer);
                   break;
            case 1:if (strcmp(buffer, ";")==0 || strcmp(buffer, "{")==0)cur_flag=-1;
                       printf("<%s> ",buffer);
                   break;
            case 0:if (is_found_string(buffer, keywords, 32)>=0)
                   {
                       printf("<%s> ", buffer);
                       int n;
                       if ((n=is_found_string(buffer, datatype, 5))>=0)
                       {
                           cur_flag = n;
                       }
                   }
                   else if (is_identifier(buffer))
                   {
                       if (cur_flag>=0)
                       {
                           if (look_for_function(buffer, source, src))
                           {
                           }
                           else if (cur_flag != 5)
                           {
                               entry.index = ++id_count;
                               entry.name = malloc(strlen(buffer));
                               strcpy(entry.name, buffer);
                               entry.type = malloc(10);
                               strcpy(entry.type, datatype[cur_flag]);
                               entry.size = cur_flag == 0?16:(cur_flag == 1?4:(cur_flag == 2?1:(cur_flag == 3?8:0)));
                               entry.scope = 'l';
                               insert(entry);
                           }
                       }
                       int idno=search_sym_table(buffer);
                       if (idno >= 0)printf("<id,%d>",idno);
                   } 
                   break;
            default:break;
        }
    }while (buffer[0] != EOF);
    print_sym_table();
    fclose(src);
    return 1;
}
