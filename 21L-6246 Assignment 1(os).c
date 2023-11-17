#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>

#define	SIZE_ARG	16
#define	SIZE_command	256


char command[SIZE_command];				// string holder for the command
char *argv[SIZE_ARG];			// an array for command and arguments
pid_t pid;										//global variable for the child process ID
char j;												// global for loop counter

void get_command();								// get command string from the user
void convert_command();						// convert the command string to the required format by execvp()
void c_shell();								// to start the shell
void log_maintain(int s);			// signal handler to add log statements

int main(){
	// tie the handler to the SGNCHLD signal
	signal(SIGCHLD, log_maintain);

	// start the shell
	c_shell();

	return 0; 
}

void c_shell(){
	while(1){
		// getting the command from user in shell
		get_command();

		//  empty commands check
		if(!strcmp("", command)) continue;
//............................................................................\\
		// checking  for "exit" command to terminate the shell execution
                if(!strcmp("exit", command)) break;

		// fit the command into *argv[]
		// we have to parse thr command as the command may have other arguments also
		convert_command();

		// fork and execute the command
		pid = fork();
		if(-1 == pid){
			printf("failed to create a child\n");
		}
		else if(0 == pid){
			// child
			// execute a command
			execvp(argv[0], argv);
		}
		else{
			//  parent
			// wait for the command to finish if "&" is not present
			if(argv[j]==NULL) 
			waitpid(pid, NULL, 0);
		}
	}
}

void get_command(){
	// get command from user
	printf("<Shell by Aroz>( ͡° ͜ʖ ͡°)\t");
	// fget is taking input from standard input keyboard and storing in command character array or string
	fgets(command, SIZE_command, stdin);
	// remove trailing newline
	if ((strlen(command) > 0) && (command[strlen (command) - 1] == '\n'))
	// the command string have '\n' have at the end of line (end cursor)
        	command[strlen (command) - 1] = '\0';
       // replace end line cursor with null terminator 	
	//printf("%s\n", command);
}

void convert_command(){
	// spliting string(command) into argv
	char *ptr;
	j = 0;
	// here we are doing tokenization
	ptr = strtok(command, " ");
	while(ptr != NULL){
		//printf("%s\n", ptr);
		argv[j] = ptr;
		j++;
		ptr = strtok(NULL, " ");
		//we place null after tokenizing each argument 
		//if ptr pointer contains null then it means we have more to tokenize
	}

	// check for "&"
	if(!strcmp("&", argv[j-1])){
	 argv[j-1] = NULL;
	argv[j] = "&";
	}else{
	 argv[j] = NULL;
	}
	
}

void log_maintain(int s){
	//printf("[LOG] child proccess terminated.\n");
	FILE *pFile;
        pFile = fopen("log.txt", "a");
        if(pFile==NULL)
         perror("Error in  opening file.");
        else 
        fprintf(pFile, "[LOG] :child proccess terminated.\n");
        fclose(pFile);
}
