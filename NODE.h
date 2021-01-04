#ifndef NODE_H
#define NODE_H
#include <stdlib.h>
#include <stdio.h>
#include "PCB.h"


struct NODE{
    struct NODE* next;
    struct PCB* item;
    struct NODE* prev;
    int status;
};


#endif // NODE_H_INCLUDED
