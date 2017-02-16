#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
	FILE *f1;
	char s[100],c;
	int l = 0,ch =0;
	while(l<3) {
		printf("You have %d Tries Remaining to open the File:\n",3-l );
		scanf("%s",s);
		f1 = fopen(s,"rw");
		if(f1 == NULL) {
			printf("File Open Failed. Enter Valid Name.\n");
			l++;
		}
		else {
			printf("File Opened Successfully!\n");
			break;
		}

	}
	
	
	return 0; 
}