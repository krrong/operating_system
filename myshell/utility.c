#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "myshell.h"

void make_history(char command[], char** history, int i)
{
	char* newstrptr;
	int l = 0;

	l = strlen(command);
	newstrptr = (char*)malloc(sizeof(char*) * (l + 1));
	strcpy(newstrptr, command);
	history[i] = newstrptr;
}


void print_history(char** history, int count)
{
	if(count < 9)
	{
		for(int i=0; i<count; ++i)
		{
			printf("%d : %s\n", i+1, history[i]);
		}
	}
	else
	{
		for(int i=10; i>0; --i)
		{
			printf("%d : %s\n", count - i + 1, history[count -i]);
		}
	}
}

void print_help()
{
	printf("myshell is a simple shell\n");
	printf("-b\n");
	printf("This flag forces a ``break'' from option processing, causing any further shell arguments to be treated as non-option arguments. The remaining arguments will not be interpreted as shell options. This may be used to pass options to a shell script without confusion or possible subterfuge. The shell will not run a set-user-ID script without this option.\n\n");
	printf("-c\n");
	printf("Commands are read from the(single) following argument which must be present.Any remaining arguments are placed in argv\n\n");
	printf("-e\n");
	printf("The shell exits if any invoked command terminates abnormally or yields a non-zero exit status.\n\n");
	printf("-f\n");
	printf("The shell will start faster, because it will neither search for nor execute commands from the file .cshrc in the invoker's home directory. Note: if the environment variable HOME is not set, fast startup is the default.\n\n");
	printf("-i\n");
	printf("The shell is interactive and prompts for its top-level input, even if it appears not to be a terminal. Shells are interactive without this option if their inputs and outputs are terminals\n\n");
	printf("-l\n");

	printf("The shell is a login shell (only applicable if -l is the only flag specified).\n\n");
	printf("-m\n");
	printf("Read .cshrc regardless of its owner and group. This option is dangerous and should only be used by su(1).\n\n");
	printf("-n\n");
	printf("Commands are parsed, but not executed. This aids in syntactic checking of shell scripts. When used interactively, the shell can be terminated by pressing control-D (end-of-file character), since exit will not work.\n\n");
	printf("-s\n");
	printf("Command input is taken from the standard input.\n\n");
	printf("-t\n");
	printf("A single line of input is read and executed. A backslash (`\' ) may be used to escape the newline at the end of this line and continue onto another line.\n\n");
	printf("-V\n");
	printf("Causes the verbose variable to be set even before .cshrc is executed.\n\n");
	printf("-v\n");
	printf("Causes the verbose variable to be set, with the effect that command input is echoed after history substitution.\n\n");
	printf("-X\n");
	printf("Causes the echo variable to be set even before .cshrc is executed.\n\n");
	printf("-x\n");
	printf("Causes the echo variable to be set, so that commands are echoed immediately before execution.\n");
}

void do_exec(char command[])
{

	char* arg[7];
	char* str;
	char* save;
	int argv;
	int stat;

	char slice[] = " ";
	int pid = 0;
	
	argv = 0;

	str = strtok_r(command, slice, &save);
	while (str != NULL)
	{
		arg[argv++] = str;
		str = strtok_r(NULL, slice, &save);
	}

	arg[argv] = (char*)0;
	
	

	pid = fork();
	
	// child process
	if(pid == 0)
	{
		execvp(arg[0], arg);
		exit(0);
	}
	
	// parent process
	if(pid > 0)
	{
//		wait(NULL);
//		waitpid(-1, &stat, 0);
//		sleep(1);
		pid = waitpid(pid, &stat, 0);

		//pid = wait(&stat);
//		if(WIFEXITED(stat))
//		{
//			printf("exit not back\n");
//		}
//		if(WIFSIGNALED(stat))
//		{
//			printf("killed not back\n");
//		}
	}
	
	// error
	if(pid < 0)
	{
		printf("fork error!\n");
		exit(-1);
	}
	
}

void do_background(char command[])
{
	char* arg[7];
	char* str;
	char* save;
	int argv;
	int stat;

	char slice[] = " ";
	int pid= 0;

	argv = 0;

	str = strtok_r(command, slice, &save);
	while(str != NULL)
	{
		arg[argv++] = str;
		str = strtok_r(NULL, slice, &save);
	}

	arg[argv] = (char*)0;

	
	pid = fork();
	
	// child process
	if(pid == 0)
	{
		execvp(arg[0], arg);
		exit(0);
	}

	// parent process
	if(pid>0) 
	{
		pid = waitpid(pid, &stat, WNOHANG);
		;
		//pid = wait(&stat);
//		if(WIFEXITED(stat))
//		{
//			printf("exit\n");
//		}
//		if(WIFSIGNALED(stat))
//		{
//			printf("killed\n");
//		}
	}
	
	// error
	if(pid < 0)
	{
		printf("fork error!\n");
		exit(-1);
	}
	
}
