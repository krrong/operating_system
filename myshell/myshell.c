#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utility.c"


int main(){
	// input string
	char command[30];
	char* history[100];

	// index of history
	int count = 0;

	// shell start
	while(1)
	{
		// print prompt
		printf("12161095_shell$ ");

		// input command
		fgets(command, sizeof(command), stdin);

		// end of command make \n->\0
		command[strlen(command)-1] = '\0';

		// make_history
		make_history(command, history, count);
		count++;
		
		// command == quit
		if(!strcmp("quit", command))
		{
			printf("myshell developed by seokjinkang(12161095)\n");
			break;
		}

		// command == history
		else if(!strcmp("history", command))
		{
			print_history(history, count);
		}

		// command == help
		else if(!strcmp("help", command))
		{
			print_help();
		}

		// background exec
		else if(command[strlen(command) -1] == '&')
		{	
			command[strlen(command) - 1] = '\0';
			do_background(command);
		}

		// exec
		else
		{
			do_exec(command);
		}
	}

}
