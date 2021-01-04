#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdio.h>
#include "NODE.h"

struct LIST{
    struct NODE* current;
    struct NODE* head;
    struct NODE* tail;
    int total;
};

extern int maxnode;
extern int maxhead;
extern struct LIST heads[10];
extern struct NODE arrays[50];
extern int used;
extern int position;

struct LIST* ListCreate();
int ListCount(struct LIST* list);
struct PCB* ListFirst(struct LIST* list);
struct PCB* ListLast(struct LIST* list);
struct PCB* ListNext(struct LIST* list);
struct PCB* ListPrev(struct LIST* list);
struct PCB* ListCurr(struct LIST* list);
int ListAdd(struct LIST* list, struct PCB* temp);
int ListInsert(struct LIST* list, struct PCB* temp);
int ListAppend(struct LIST* list, struct PCB* temp);
int ListPrepend(struct LIST* list, struct PCB* temp);
struct PCB* ListRemove(struct LIST* list);
void ListConcat(struct LIST* list1, struct LIST* list2);
void itemFree(struct NODE* itemF);
void ListFree(struct LIST* list, void(*itemFree)(struct NODE*));
struct PCB* ListTrim(struct LIST* list);
int compare(struct NODE* becompared, void* arg);
struct PCB* ListSearch(struct LIST* list, int(*comparator)(struct NODE*, void*), void* comparisonArg);

#endif // LIST_H_INCLUDED
