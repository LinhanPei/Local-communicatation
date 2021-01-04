#ifndef PCB_H
#define PCB_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LIST.h"
#include "NODE.h"

struct PCB{
    int pid; // ID of this process
    int state; // State of the process. ready = 0, running = 1, send blocked = 2, receive blocked = 3, P block = 4
    char priority; // Priority of the process, with 0, 1 and 2
    char rsvmsg[40]; // Store received message
	char rplmsg[40]; // Store replied message
	int semphore; // The semphore that a process could be call
};

extern int sem[5];
extern int pidIs;

int creat(char priorityIs, struct LIST* ready, struct NODE* running);
int forked(struct LIST* ready, struct NODE* running);
int kill(int removed, struct LIST* p0, struct LIST* p1, struct LIST* p2, struct LIST* s, struct LIST* r, struct NODE* running);
int exitp(struct LIST* p0, struct LIST* p1, struct LIST* p2, struct NODE* running);
int quantum(struct LIST* p0, struct LIST* p1, struct LIST* p2, struct NODE* running);
int send(char msg[40], int pidF, struct LIST* p0, struct LIST* p1, struct LIST* p2, struct LIST* b, struct LIST* r, struct NODE* running);
int receive(struct LIST* p0, struct LIST* p1, struct LIST* p2, struct LIST* r,  struct NODE* running);
int reply(char msg[40], int pidF, struct LIST* p0, struct LIST* p1, struct LIST* p2, struct LIST* b, struct NODE* running);
int newSem(int semIs);
int sP(int semF, struct LIST* p0, struct LIST* p1, struct LIST* p2, struct LIST* b, struct NODE* running);
void sV(int semF, struct LIST* p0, struct LIST* p1, struct LIST* p2, struct LIST* b);
void procinfo(int pidF);
void totalinfo();

void nextrunnging(struct LIST* p0, struct LIST* p1, struct LIST* p2, struct NODE* running);

#endif