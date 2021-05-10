#include <sys/types.h>				//Header file containing fork() operation
#include <sys/wait.h>				//Header file for wait() operation
#include <unistd.h>				
#include <stdio.h>				
#include <stdlib.h>				
#include <string.h>				
#define CHARSIZE 10				

//Variable declarations
char read_pipemsg[CHARSIZE];			
char* msg_from_commandline;
char character;



//Child function declaration
void ChildFunction(void)
{	
	//Reading input from the user for pipe operation
	printf("Enter Y/N to read & write from Pipe communication:\n");
	scanf("%c", &character);
	//Pipe variable
	int fd[2];
	//Checking if pipe created
	if( pipe(fd) < 0)
	{	
		perror("Pipe could not be created\n");
	}
	else
	{	//Checking pipe operation input from user
		if( character == 'Y')
		{	
			printf("%c selected, so pipe write in progress.\n", character);	
			//Creating a subchild to manage pipe operation	
			int sub_child = fork();
			//Checking if subchild is created
			if( sub_child == 0)
			{	
				printf("The pid of the subchild is : %d\n", sub_child);
				//Closing the reader of the pipe
				close(fd[0]);
				//Writing into the pipe
				write(fd[1], msg_from_commandline,(strlen(msg_from_commandline)));
				//Closing the writer of the pipe as writing is finished
				close(fd[1]);
				exit(0);
			}
			else if( sub_child < 1)
			{
				perror("subchild creation failed!!\n");
			}
			else
			{
				printf("The parent of subchild is active with pid: %d\n", getpid());
			}
		
		//Reading from the pipe
		read(fd[0], read_pipemsg, CHARSIZE);
		printf("'%s' was read from pipe.\n", read_pipemsg);
		printf("The subchild process ended with pid:%d\n", sub_child);
		}
		//Child process is completed but parent is still active
		printf("Sub child exiting but child process is still active\n");
	}
}



//Main function declaration with command line arguments
int main(int argc, char *argv[])
{	
	int status;
	//Chekcing and rejecting if none/ more than 1 argument at command line
	if( argc != 2)
	{
		printf("Please enter only one valid string for pipe reading!\n");
		exit(0);
	}
	else
	{	
		//Printing the commandline arguments for reference
		printf("printing argv[1], ie the pipe msg: %s\n",argv[1]);
	}
	//Storing the commandline argument as a message for pipe
	msg_from_commandline = argv[1];
	printf("Im a Parent process:%d\n", getpid());
	pid_t child = fork();
	printf("fork returned with pid:%d\n", child);
	
	//Check if child is created
	if( child < 0 )
	{
		perror("fork failed to generate child process.\n");
	}
	if( child == 0)
	{	//Child process is created
		printf("The child processes created with pid:%d\n", getpid());	
		//Calling child function to perform pipe operation through sub-child.
		ChildFunction();
	}
	else if( child > 0)
	{	
		//Parent process in execution
		printf("This is the parent process waiting for child process to end\n");
		//Waiting for the child process to exit waitpid(pid, statloc, options)
		waitpid( -1, &status, 0);
		printf("Parent process exiting\n");
		exit(0);
	}

//Calling EXECVE to get a command prompt to view the active processes
printf("Initializing the command prompt to check active processes. 'exit' by command\n");
//Defining the path for execve function
char* a[2] = {"/bin/sh", NULL};
execve( a[0], a, NULL);
return 0;
}

	
	
	
