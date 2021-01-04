#include "PCB.h"

int sem[5] = { -1, -1, -1, -1, -1 }; //Semaphore
int pidIs = 0;

int creat(char priorityIs, struct LIST* ready, struct NODE* running)
{ 
    struct PCB temp;
    temp.pid = pidIs;
	pidIs++;
    temp.priority = priorityIs;
	strcpy(temp.rplmsg, "!");
	strcpy(temp.rsvmsg, "!");
	temp.semphore = -1;
    if(ListPrepend(ready, &temp) == -1)
	{
		return 0;
	}

	if(temp.pid == 0)
	{
		running = ready->current;
		if(ready->current == NULL)
			printf("FFFF\n");
		temp.state = 1;
	}
	else
		temp.state = 0;
	
    return 1;
}
int forked(struct LIST* ready, struct NODE* running)
{   
    struct PCB temp;
    if(running->item->pid != 0)
    {
        temp.pid = pidIs++;
        temp.priority = running->item->priority;
        temp.state = 0;
        if(ListAppend(ready, &temp) == -1)
            return 0;
        return temp.pid;
    }
    return 0;
}

int kill(int removed, struct LIST* p0, struct LIST* p1, struct LIST* p2, struct LIST* s, struct LIST* r, struct NODE* running)
{
	if (removed == running->item->pid)
	{
		if (exitp(p0, p1, p2, running))
			return 1;
		else
			return 0;
	}
    for(int i = 0; i < maxnode; i++)
    {
        if(arrays[i].status == 1)
        {
            if(removed == arrays[i].item->pid)
            {
                if(arrays[i].item->state == 2 || arrays[i].item->state == 4)
                {
                    s->current = &arrays[i];
					if (ListRemove(s) != NULL)
						return 1;
                }
                else if(arrays[i].item->state == 3)
                {
                    r->current =& arrays[i];
					if (ListRemove(r) != NULL)
						return 1;
                }
                else if(arrays[i].item->priority == '0')
                {
                    p0->current = &arrays[i];
					if (ListRemove(p0) != NULL)
					{
						return 1;
					}
                }
                else if(arrays[i].item->priority == '1')
                {
                    p1->current = &arrays[i];
					if (ListRemove(p1) != NULL)
					{
						return 1;
					}
                }
                else if(arrays[i].item->priority == '2')
                {
                    p2->current = &arrays[i];
					if (ListRemove(p2) != NULL)
					{
						return 1;
					}
                }
            }
        }
    }
    return 0;
}

int exitp(struct LIST* p0, struct LIST* p1, struct LIST* p2, struct NODE* running)
{
    if(running->item->priority == '0')
    {
        p0->current = running;
        if(ListRemove(p0) != NULL)
		{
			nextrunnging(p0, p1, p2, running);
			return 1;
		}
    }
    else if(running->item->priority == '1')
    {
        p1->current = running;
        if(ListRemove(p1) != NULL)
		{
			nextrunnging(p0, p1, p2, running);
			return 1;
		}
    }
    else if(running->item->priority == '2')
    {
        p2->current = running;
        if(ListRemove(p2) != NULL)
		{
			nextrunnging(p0, p1, p2, running);
			return 1;
		}
    }
    return 0;
}

int quantum(struct LIST* p0, struct LIST* p1, struct LIST* p2, struct NODE* running)
{
	running->item->state = 0;
	nextrunnging(p0, p1, p2, running);
	if (running != NULL)
		return running->item->pid;
	else
		return -1;
}

int send(char msg[40], int pidF, struct LIST* p0, struct LIST* p1, struct LIST* p2, struct LIST* b, struct LIST* r, struct NODE* running)
{
	for (int i = 0; i < maxnode; i++)
	{
		if (arrays[i].status == 1)
		{
			if (arrays[i].item->pid == pidF)
			{
				struct PCB* temp;
				strcpy(arrays[i].item->rsvmsg, msg);
				if (running->item->priority == '0')
				{
					p0->current = running;
					temp = ListRemove(p0);
					ListPrepend(b, temp);
					nextrunnging(p0, p1, p2, running);
				}
				else if (running->item->priority == '1')
				{
					p1->current = running;
					temp = ListRemove(p1);
					ListPrepend(b, temp);
					nextrunnging(p0, p1, p2, running);
				}
				else if (running->item->priority == '2')
				{
					p2->current = running;
					temp = ListRemove(p2);
					ListPrepend(b, temp);
					nextrunnging(p0, p1, p2, running);
				}
				b->head->item->state = 2;

				if (arrays[i].item->state == 3)
				{
					r->current = &arrays[i];
					struct PCB* temp1 = ListRemove(r);
					if (temp1->priority == '0')
						ListPrepend(p0, temp1);
					else if (temp1->priority == '1')
						ListPrepend(p1, temp1);
					else if (temp1->priority == '2')
						ListPrepend(p2, temp1);
					temp1->state = 0;
				}
				return 1;
			}
		}
	}
	return 0;
}

int receive(struct LIST* p0, struct LIST* p1, struct LIST* p2, struct LIST* r,  struct NODE* running)
{
	if (strcmp(running->item->rsvmsg, "!") != 0)
	{
		printf("This process has received message: %s\n", running->item->rsvmsg);
		strcpy(running->item->rsvmsg, "!");
		return 1;
	}
	else
	{
		struct PCB* temp;
		if (running->item->priority == '0')
		{
			p0->current = running;
			temp = ListRemove(p0);
			ListPrepend(r, temp);
			nextrunnging(p0, p1, p2, running);
		}
		else if (running->item->priority == '1')
		{
			p1->current = running;
			temp = ListRemove(p1);
			ListPrepend(r, temp);
			nextrunnging(p0, p1, p2, running);
		}
		else if (running->item->priority == '2')
		{
			p2->current = running;
			temp = ListRemove(p2);
			ListPrepend(r, temp);
			nextrunnging(p0, p1, p2, running);
		}
		r->head->item->state = 3;
		return 1;
	}
	return  0;
}

int reply(char msg[40], int pidF, struct LIST* p0, struct LIST* p1, struct LIST* p2, struct LIST* b, struct NODE* running)
{
	for (int i = 0; i < maxnode; i++)
	{
		if (arrays[i].status == 1)
		{
			if (arrays[i].item->pid == pidF)
			{
				strcpy(arrays[i].item->rsvmsg, msg);
				if (arrays[i].item->state == 2)
				{
					b->current = &arrays[i];
					struct PCB* temp1 = ListRemove(b);
					if (temp1->priority == '0')
						ListPrepend(p0, temp1);
					else if (temp1->priority == '1')
						ListPrepend(p1, temp1);
					else if (temp1->priority == '2')
						ListPrepend(p2, temp1);
					temp1->state = 0;
					return 1;
				}
				else
					return 0;
			}
		}
	}
	return 0;
}

int newSem(int semIs)
{
	if (semIs <= 4)
	{
		if (sem[semIs] == -1)
		{
			sem[semIs] = 0;
			return 1;
		}
	}
	return 0;
}

int sP(int semF, struct LIST* p0, struct LIST* p1, struct LIST* p2, struct LIST* b, struct NODE* running)
{
	if (semF <= 4)
	{
		struct PCB* temp;
		if (running->item->priority == '0')
		{
			p0->current = running;
			temp = ListRemove(p0);
			temp->semphore = semF;
			temp->state = 4;
			ListPrepend(b, temp);
			nextrunnging(p0, p1, p2, running);
		}
		else if (running->item->priority == '1')
		{
			p1->current = running;
			temp = ListRemove(p1);
			temp->semphore = semF;
			temp->state = 4;
			ListPrepend(b, temp);
			nextrunnging(p0, p1, p2, running);
		}
		else if (running->item->priority == '2')
		{
			p2->current = running;
			temp = ListRemove(p2);
			temp->semphore = semF;
			temp->state = 4;
			ListPrepend(b, temp);
			nextrunnging(p0, p1, p2, running);
		}
		return 1;
	}
	return 0;
}

void sV(int semF, struct LIST* p0, struct LIST* p1, struct LIST* p2, struct LIST* b)
{
	for (int i = 0; i < maxnode; i++)
	{
		if (arrays[i].status == 1)
		{
			if (arrays[i].item->semphore == semF)
			{
				struct PCB* temp;
				if (arrays[i].item->priority == '0')
				{
					b->current = &arrays[i];
					temp = ListRemove(b);
					temp->semphore = -1;
					temp->state = 0;
					ListPrepend(p0, temp);
				}
				else if (arrays[i].item->priority == '1')
				{
					b->current = &arrays[i];
					temp = ListRemove(b);
					temp->semphore = -1;
					temp->state = 0;
					ListPrepend(p1, temp);
				}
				else if (arrays[i].item->priority == '2')
				{
					b->current = &arrays[i];
					temp = ListRemove(b);
					temp->semphore = -1;
					temp->state = 0;
					ListPrepend(p2, temp);
				}
			}
		}
	}
}

void procinfo(int pidF)
{
	int out = 0;
	for (int i = 0; i < maxnode; i++)
	{
		if (arrays[i].status == 1)
		{
			if (arrays[i].item->pid == pidF)
			{
				printf("The ID of this Process is %d\n", arrays->item->pid);
				printf("The priority of this Process is %c\n", arrays->item->priority);
				printf("The state of this Process is %d, where ready = 0, running = 1, send blocked = 2, receive blocked = 3, P block = 4\n\n", arrays->item->state);
				out = 1;
				break;
			}
		}
	}

	if (out == 0)
		printf("Cannot find the process ID\n");
}

void totalinfo()
{
	for (int i = 0; i < maxnode; i++)
	{
		if (arrays[i].status == 1)
		{
			printf("The ID of this Process is %d\n", arrays->item->pid);
			printf("The priority of this Process is %c\n", arrays->item->priority);
			printf("The state of this Process is %d, where ready = 0, running = 1, send blocked = 2, receive blocked = 3, P block = 4\n\n", arrays->item->state);
		}
	}
}

void nextrunnging(struct LIST* p0, struct LIST* p1, struct LIST* p2, struct NODE* running)
{
	if (ListCount(p0) > 1)
	{
		running = p0->head;
		running->item->state = 1;
	}
	else if (ListCount(p1) != 0)
	{
		running = p1->head;
		running->item->state = 1;
	}
	else if (ListCount(p2) != 0)
	{
		running = p2->head;
		running->item->state = 1;
	}
	else if (p0->head->item->pid == 0)
	{
		running = p0->head;
		running->item->state = 1;
	}
	else
		running = NULL;

	if (running != NULL)
	{
		if (strcmp(running->item->rsvmsg, "!") != 0)
			printf("This process has received message: %s\n", running->item->rsvmsg);
		if(strcmp(running->item->rplmsg, "!") != 0)
			printf("This process has a replied message: %s\n", running->item->rplmsg);
		strcpy(running->item->rsvmsg, "!");
		strcpy(running->item->rplmsg, "!");
	}
}
