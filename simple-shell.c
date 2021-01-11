#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LINE		80 /* 80 chars per line, per command */
#define MAX_HIST        10

char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */

int commands = 0;
int curr = 0;

int main(void)
{   
	
	int should_run = 1;
	int i, upper;

	char **hist_arr;
	hist_arr = malloc(MAX_HIST * sizeof(char *));

	for(i=0; i<MAX_HIST; i++)
	{
		hist_arr[i] = malloc(MAX_HIST * sizeof(char));
		hist_arr[i][0] = '\0';
	}
		
    while (should_run == 1)
    {
    	int hist = 0;
    	int is_empty = 0;


        printf("osh>");
        fflush(stdout);
        
	    char str[MAX_LINE/2 + 1]; // Temp input
	   
	    char end[] = {'&', '\0'}; //'&' char
	    char check[10]; //Intialize compare string;

	    fgets(str, MAX_LINE/2 + 1, stdin); //Take input

	    int size = (unsigned)strlen(str); //Get size of input
	 
	    check[0] = str[size-2]; //Store last char of input

	    int ampersand = strcmp(end, check); //Zero if '&' at the end of the input


		char *temp;
	    temp = str;
	    char check_first = *temp; //Grab 1st character of input
	    

	    if((strcmp("\n", str) == 0)) //If command is empty
	    	is_empty = 1;


	    if((check_first != '!') && (strcmp("history\n", str) != 0) && (strcmp("\n", str) != 0)) //History array to store all valid commands
	  	{	
	   		curr = commands % MAX_HIST;
	   		strcpy(hist_arr[curr], str);
	   		commands++;
	   	}

	   	int counter = 0;
	   	char *token;
	    token = strtok(str, " ");
	    args[0] = token;
	    counter++;

	   	while(token != NULL)
	   	{
	   		token = strtok(NULL, " ");
	   		if(token == NULL)
	   			args[counter] = "\0";
	   		else
	   		{
	   			args[counter] = token;
	   			counter++;
	   		}   		
	   	}

	    if ((strcmp(args[0], "exit\n")) == 0) //if exit - close program
	    {
	    	should_run = 0;
	    }

	    if ((strcmp(args[0], "history\n")) == 0) //if history then print history by latest first
	    {
	    	hist = 1;
	    	if(commands<=MAX_HIST)
	    	{
	    		for(i=commands; i>=0; i--)
	    		{
	    			printf("%s", hist_arr[i]);
	    		}
	    	}

	    	else if(commands>MAX_HIST)
	    	{
	    		for(i=curr; i>=0; i--)
	    		{
	    			printf("%s", hist_arr[i]);
	    		}

	    		for(i=MAX_HIST-1; i>curr; i--)
	    		{
	    			printf("%s", hist_arr[i]);
	    		}
	    	}
	    }

	    char str1[MAX_LINE/2 + 1];
	    strcpy(str1, str);

	    temp = str1;
	    check_first = *temp;
	    if(check_first == '!')
	    {
	    	temp++;
	    	char check2 = *temp;
	    	if(isdigit(check2))
	    	{
	    		temp++;
	    		char check3 = *temp;
	    		int check4 = -1;
	    		if(isdigit(check3))
	    		{
	    			check4 = check3 - '0';

	    			if(check4 >= 0)
	    			{
	    				char *new = str1 + 1;
	    				int num;
						sscanf(new, "%d", &num);

						if(commands>=num)
						{
							printf("Executing command: %s", hist_arr[num-1]);

							counter = 0;

				    		strcpy(str, hist_arr[num-1]);
				    		size = (unsigned)strlen(str);
				    		
				    		check[0] = str[size-2];
				    		ampersand = strcmp(end, check);
				    		
				    		token = strtok(str, " ");
						    args[0] = token;
						    counter++;

						   	while(token != NULL)
						   	{
						   		token = strtok(NULL, " ");
						   		if(token == NULL)
						   			args[counter] = "\0";
						   		else
						   		{
						   			args[counter] = token;
						   			counter++;
						   		}   		
						   	}
						}

						else
						{
							printf("%s\n", "Command doesn't exist!");
							hist = 1;
						}
	    			}		    			
	    		}
	    		else
	    		{
	    			char *new = str1 + 1;
    				int num;
					sscanf(new, "%d", &num);

					if(commands>=num)
					{
						printf("Executing command: %s", hist_arr[num-1]);

						counter = 0;

			    		strcpy(str, hist_arr[num-1]);
			    		size = (unsigned)strlen(str);
			    		
			    		check[0] = str[size-2];
			    		ampersand = strcmp(end, check);
			    		
			    		token = strtok(str, " ");
					    args[0] = token;
					    counter++;

					   	while(token != NULL)
					   	{
					   		token = strtok(NULL, " ");
					   		if(token == NULL)
					   			args[counter] = "\0";
					   		else
					   		{
					   			args[counter] = token;
					   			counter++;
					   		}   		
					   	}
					}


					else
					{
						printf("%s\n", "Command doesn't exist!");
						hist = 1;
					}
	    		}		
	    	}
	    }


	    if((strcmp(args[0], "!!\n")) == 0) //if !! then execute the latest command in history
	    { 
	    	if(commands == 0)
	    	{
	    		printf("No Command in History\n");
	    		hist = 1;
	    	}
	    	else
	    	{
	    		counter = 0;

	    		strcpy(str, hist_arr[curr]);
	    		size = (unsigned)strlen(str);
	    		
	    		check[0] = str[size-2];
	    		ampersand = strcmp(end, check);
	    		
	    		token = strtok(str, " ");
			    args[0] = token;
			    counter++;

			   	while(token != NULL)
			   	{
			   		token = strtok(NULL, " ");
			   		if(token == NULL)
			   			args[counter] = "\0";
			   		else
			   		{
			   			args[counter] = token;
			   			counter++;
			   		}   		
			   	}
	    		
	    		printf("Executing command: %s", hist_arr[curr]);
	    	}
	    }




	    if(should_run == 1 && hist == 0 && is_empty == 0)
	    {
		   	pid_t pid;

			pid = fork();

			if(pid < 0)
			{
				fprintf(stderr, "Fork Failed");
				return 1;
			}

			else if (pid == 0)
			{
				execvp(args[0], args);
				exit(0);
			}

			else
			{
				
				int status = 0;

				if(ampersand != 0)
				{
					waitpid(pid, &status, 0);
					printf("Waiting for child to exit..\n");
				}

				if(status == 0)
				{
					printf("Child Terminated Normally\n");
				}

				if(status == 1)
				{
					printf("Child Terminated with an Error!\n");
				}
			}
	    }	   	
	}		

	return 0;
}
