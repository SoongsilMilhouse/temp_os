#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

static char * strstrip(char * str);
int main()
{
	char* str = (char *)malloc(sizeof(char) * 50);
	char* temp = "id .:. action:pipe_id:co";
	char* p;
	int i;
	strcpy(str,temp);
	printf("-------start for -------\n");
	for(i=0; i<26 ;i++) {
		printf("%c", str[i]);	
	}	
	printf("\n");
	printf("-------end for ------\n");
	p = strchr(str,':');
	*p = '\0';
	i = strlen(str);	
	printf("strlen(str) = %d\n", i);
	printf("p??? = %c\n", *p);
	
	printf("----- before strstrip!!!!!!!!!!!!!! -------\n");
	printf("-------start for -------\n");
	for(i=0; i<26 ;i++) {
		printf("%c", str[i]);	
	}	
	printf("\n");
	printf("-------end for ------\n");
	strstrip(str);

	printf("after strstrip!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1\n");
	printf("-------start for -------\n");
	for(i=0; i<26 ;i++) {
		printf("%c", str[i]);	
	}	
	strstrip(str);
	printf("second strstrip!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1\n");
	for(i=0; i<26 ;i++) {
		printf("%c", str[i]);	
	}	
	printf("\n");
	printf("-------end for ------\n");
	printf("main ---- str = %s\n",str);
//	printf("p    ---- str = %s\n", p);
	free(str);
	return 0;
}
static char * strstrip(char * str) {

	//char* tempStr = (char *)malloc(sizeof(char)*50);
	char* start;
	int count = 0, count_for=0;
	int i;
	//strcpy(tempStr, str);
	//printf("tempStr = %s\n", tempStr);
	printf("str = %s\n", str);
	int len = strlen(str);
	int len2 = 0;
	printf("len = %d\n",len);
	
	while(len--) {
		count++;
		printf("count = %d\n", count);
		printf("result of isspace : %d\n", isspace(str[len]));
		if(!isspace (str[len])){
			printf("i'm in isspace!\n");
			break;
		}
		str[len] = '\0';
	}
	printf("out of while\n");

	for (start = str; *start && isspace (*start); start++) {
		count_for++;
		printf("count_for:%d\n", count_for);
	}
	len2= strlen(start);
	printf("strlen(start)=%d\n", len2);
	printf("bf memmove start = %s\n", start);
	if(!memmove(str, start, strlen(start)+1))
		printf("error in memmove\n");

	printf("str = %s\n", str);
	printf("start = %s\n", start);
	return str;	
}
