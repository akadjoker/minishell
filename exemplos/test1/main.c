#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char c = '\0';
	printf("\n[MY_SHELL ] ");
	while(c != EOF) {
		c = getchar();
		if(c == '\n')
			printf("[MY_SHELL ] ");
	}
	printf("\n");
	return 0;
}
