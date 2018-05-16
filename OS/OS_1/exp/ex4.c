#include<stdio.h>
int main() {
	
	char* temp = "h\0e\0world!\n";
	int i = 0;
	for(; i!='\n'; i++)
		printf("%c",temp[i]);

	return 0;


}
