#include <stdlib.h>
#include <stdio.h>
#include "PCB.h"
#include "LIST.h"
#include "NODE.h"

int main()
{
    struct LIST* ready0 = ListCreate(); // list for priority 0
    struct LIST* ready1 = ListCreate(); // list for priority 1
    struct LIST* ready2 = ListCreate(); // list for priority 2
    struct LIST* blocked = ListCreate(); // list for send and PV blocked
    struct LIST* recvblocked = ListCreate();  // list for receive blocked
    struct NODE* running = NULL;

    char command;
	char message[40];
    char pri;
    int pidF;
	int semF;
    creat(0, ready0, running);

    while(1)
    {
		message[0] = '!';
		printf("Please enetr the command: ");
        if((command = getchar()) != EOF)
        {
			while ((getchar()) != '\n');
            if(command == 'C')
            {
                printf("Please enter priority in one of 0, 1, 2: ");
                if(scanf("%c", &pri) != 0)
				{
                    if(pri == '0')
                        if(creat(pri, ready0, running) == 0)
                            printf("Create process faild\n");
                    if(pri == '1')
                        if(creat(pri, ready1, running) == 0)
                            printf("Create process faild\n");
                    if(pri == '2')
                        if(creat(pri, ready2, running) == 0)
                            printf("Create process faild\n");
                }
				else
					printf("Error, please enter one of 0, 1, 2\n");
            }
            else if(command == 'F')
            {
                if(running != NULL)
                {
                    if (running->item->priority == '0')
                        if(forked(ready0, running) == 0)  
                            printf("Fork process faild\n");
                    if (running->item->priority == '1')
                        if(forked(ready1, running) == 0)  
                            printf("Fork process faild\n");
                    if (running->item->priority == '2')
                        if(forked(ready2, running) == 0)  
                            printf("Fork process faild\n");
                }
				else 
					printf("There is no running process\n");
            }
            else if(command == 'K')
            {
				printf("Please enter the PID that you want to remove: ");
                if(scanf("%d", &pidF) != 0)
				{
					if (pidF == 0)
						printf("Cannot remove the initial process\n");
					else
						if (kill(pidF, ready0, ready1, ready2, blocked, recvblocked, running) == 0)
							printf("Cannot find the process\n");
				}
            }
            else if(command == 'E')
            {
                if(running != NULL)
                {
                    if(running->item->pid == 0)
                        printf("Cannot remove the initial process\n");
                    else 
						if (exitp(ready0, ready1, ready2, running) == 0)
							printf("Cannot remove the process\n");
                }
				else
					printf("No running process\n");
            }
            else if(command == 'Q')
            {
				if (running != NULL)
				{
					int out = quantum(ready0, ready1, ready2, running);
					if (out >= 0)
						printf("The current running process is: %d\n", out);
				}
				printf("No running process\n");
			}
            else if(command == 'S')
            {
				if (running != NULL)
				{
					printf("Please enter the ID of process which you want to send: ");
					if (scanf("%d", &pidF) >= 0)
					{
						while ((getchar()) != '\n');
						printf("Please enter message (less than 40 digits): ");
						fgets(message, 40, stdin);
						if (send(message, pidF, ready0, ready1, ready2, blocked, recvblocked, running) == 0)
							printf("Send failed\n");
					}
					else
						printf("Error input\n");
				}
				else
					printf("No running process\n");
            }
            else if(command == 'R')
            {
				if (running != NULL)
				{
					if (receive(ready0, ready1, ready2, recvblocked, running) == 0)
						printf("Receive failed");
				}
				else
					printf("No running process\n");
            }
            else if(command == 'Y')
            {
				if (running != NULL)
				{
					printf("Please enter the ID of process which you want to reply: ");
					if (scanf("%d", &pidF) >= 0)
					{
						while ((getchar()) != '\n');
						printf("Please enter message (less than 40 digits): ");
						fgets(message, 40, stdin);
						if (reply(message, pidF, ready0, ready1, ready2, blocked, running) == 0)
							printf("Reply failed\n");
					}
					else
						printf("Error input\n");
				}
				else
					printf("No running process\n");
            }
            else if(command == 'N')
            {
				printf("Please enter the ID of semphore (0 to 4): ");
				if (scanf("%d", &semF) >= 0)
				{
					if (newSem(semF) == 0)
						printf("Cannot set exist semphore\n");
				}
				else
					printf("Wrong input\n");
            }
            else if(command == 'P')
            {
				if (running != NULL)
				{
					printf("Pleae enter the ID of semphore that you want to call P in this process (0 to 4): ");
					scanf("%d", &semF);
					if (sP(semF, ready0, ready1, ready2, blocked, running) == 0)
						printf("Error to put semphore\n");
				}
				else
					printf("No running process\n");
            }
            else if(command == 'V')
            {
			if (running != NULL)
			{
				printf("Pleae enter the ID of semphore that you want to call V in this process (0 to 4): ");
				scanf("%d", &semF);
				sV(semF, ready0, ready1, ready2, blocked);
			}
			else
				printf("No running process\n");
            }
            else if(command == 'I')
            {
				printf("Please enter the PID that you want to print: ");
				if (scanf("%d", &pidF) != 0)
					procinfo(pidF);
				else
					printf("Wrong input\n");
            }
            else if(command == 'T')
            {
				totalinfo();
			}
        }
		else 
            printf("Wrong command\n");

        if(ListCount(ready0) == 0)
        {
            printf("End Simulation.\n");
			break;
        }
    }
	printf("Exit System\n");
    return 0;
}
