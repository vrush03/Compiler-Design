#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
	FILE *f1;
	char s[100],c;
	int l = 0,ch =0;
	scanf("%s",s);
	f1 = fopen(s,"rw");
	c = fgetc(f1);
	
	while(1) {	
		
		printf("Enter q to Quit, c to Continue:\n");
		scanf(" %c",&c);
		if(c == 'q')
			break;
		else {
			int cnt = 0;
			while(cnt<5) {
				fscanf(f1,"%s",s);
				printf("%s\n",s);
				cnt++;
			}
		}

	}
	
	return 0; 
}