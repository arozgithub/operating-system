
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, char* argv[])
{
	int num = atoi(argv[1]);
	
	pid_t pid = fork();
	
	if(pid == 0)
	{
		char n[32];
		sprintf(n,"%d", num);
		
		execl("./ch", "./ch", n, NULL);
		
		perror("execl"); // If execl fails
        	exit(1);
	}
	else
	{
		wait(NULL);
	}
	return 0;
}
