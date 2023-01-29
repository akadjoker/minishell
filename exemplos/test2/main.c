#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef void (*sighandler_t)(int);
char c = '\0';

void handle_signal(int signo)
{
	printf("\n[minishell] %d",signo);
	fflush(stdout);
}

int main()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_signal);
	printf("[minishell] ");
	while(c != EOF) {
		c = getchar();
		if(c == '\n')
			printf("[minishell] ");
	}
	printf("\n");
	return 0;
}
