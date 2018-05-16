#include<stdio.h>

int main() 
{
	int S[] = { 5,3,2,2,7};

	int i;
	int j;
	int k ;
	int temp;
	int len = sizeof(S) / sizeof(*S);

	printf("len = %d\n", len);
	for(i = 0; i < len -1 ; i++) {
		for(j = 0; j<len-1-i ; j++) {
			if(S[j] > S[j+1]) {
				temp = S[j];
				S[j] = S[j+1];
				S[j+1] = temp;
			}
		}
	}
	for(k = 0; k < len; k++)
		printf("%d ",S[k]);
	

}
