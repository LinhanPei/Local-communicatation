#include "LIST.h"

int maxnode = 50;
int maxhead = 10;
struct LIST heads[10];
struct NODE arrays[50];
int used = 0;
int position = 0;

struct LIST* ListCreate()
{
    if(sizeof(heads) == 0)
    {
        for(int i = 0; i < maxhead; i++)
        {
            arrays[i].next = NULL;
            arrays[i].prev = NULL; 
            arrays[i].item = NULL;
            arrays[i].status = 0;
        }
        for(int i = 0; i < maxnode; i++)
        {
            heads[i].current = NULL;
            heads[i].head = NULL;
            heads[i].tail = NULL;
            heads[i].total = 0;
        }
    }
		for (int i = 0; i < maxhead; i++)
		{
			if (heads[i].head == NULL)
			{
				if (i == 0)
					heads[i].head = &arrays[0];
				struct LIST* newList;
				newList = &heads[i];
				return newList;
			}
		}
    return NULL;
}

int ListCount(struct LIST* list)
{
    return list->total;
}

struct PCB* ListFirst(struct LIST* list)
{
    if(list->total == 0)
        return NULL;
    list->current = list->head;
    return list->head->item;
}

struct PCB* ListLast(struct LIST* list)
{
    if(list->total == 0)
        return NULL;
    list->current = list->tail;
    return list->tail->item;
}

struct PCB* ListNext(struct LIST* list)
{
    if(list->current == NULL)
        return NULL;
    list->current = list->current->next;
	if (list->current == NULL)
		return NULL;
    return list->current->item;
}

struct PCB* ListPrev(struct LIST* list)
{
    if(list->current == NULL)
        return NULL;
    list->current = list->current->prev;
	if (list->current == NULL)
		return NULL;
	return list->current->item;
}

struct PCB* ListCurr(struct LIST* list)
{
    if(list->current == NULL)
        return NULL;
    return list->current->item;
}

int ListAdd(struct LIST* list, struct PCB* temp)
{
    if(used >= maxnode)
        return -1;

    for(int i = 0; i < maxnode; i++)
    {
        if(arrays[i].status == 0)
        {
            position = i;
            break;
        }
    }
    arrays[position].item = temp;
	arrays[position].status = 1;
	struct NODE *iter = &arrays[position];
    used++;
    
    if(list->total == 0)
    {
        list->head = iter;
        list->current = iter;
		list->tail = iter;
    }
	else if(list->current == NULL || list->current->next == NULL)
    {   list->tail->next = iter;
        iter->prev = list->tail;
        list->current = iter;
        list->tail = iter;
    }
	else if(list->current->item != NULL && list->current->next->item != NULL)
    {
        list->current->next->prev = iter;
        iter->next = list->current->next;
        list->current->next = iter;
        iter->prev = list->current;
        list->current = iter;
    }
    else
    {
        list->head->prev = iter;
        iter->next = list->head;
        list->head = iter;
        list->current = iter;
    }
    list->total++;
    return 0;
}

int ListInsert(struct LIST* list, struct PCB* temp)
{
    if(used >= maxnode)
        return -1;

    for(int i = 0; i < maxnode; i++)
    {
        if(arrays[i].status == 0)
        {
            position = i;
            break;
        }
    }
	arrays[position].item = temp;
	arrays[position].status = 1;
	struct NODE *iter = &arrays[position];
    used++;

	if (list->total == 0)
	{
		list->head = iter;
		list->current = iter;
		list->tail = iter;
	}
	else if (list->current == NULL || list->current->next == NULL)
	{
		list->tail->next = iter;
		iter->prev = list->tail;
		list->current = iter;
		list->tail = iter;
	}
   else if(list->current->item != NULL && list->current->prev->item != NULL)
    {
        list->current->prev->next = iter;
        iter->prev = list->current->prev;
        list->current->prev = iter;
        iter->next = list->current;
        list->current = iter;
    }
    else
    {
        list->head->prev = iter;
        iter->next = list->head;
        list->head = iter;
        list->current = iter;
    }
    list->total++;
    return 0;
}

int ListAppend(struct LIST* list, struct PCB* temp)
{
    if(used >= maxnode)
        return -1;

    for(int i = 0; i < maxnode; i++)
    {
        if(arrays[i].status == 0)
        {
            position = i;
            break;
        }
    }
	arrays[position].item = temp;
	arrays[position].status = 1;
	struct NODE *iter = &arrays[position];
    used++;

    if(list->total == 0)
    {
        list->head = iter;
        list->tail = iter;
        list->current = iter;
    }
    else
    {
        list->tail->next = iter;
        iter->prev = list->tail;
        list->current = iter;
        list->tail = iter;
    }
    list->total++;
    return 0;
}

int ListPrepend(struct LIST* list, struct PCB* temp)
{
    if(used >= maxnode)
        return -1;

    for(int i = 0; i < maxnode; i++)
    {
        if(arrays[i].status == 0)
        {
            position = i;
            break;
        }
    }
	arrays[position].item = temp;
	arrays[position].status = 1;
	struct NODE *iter = &arrays[position];
    used++;

    if(list->total == 0)
    {
        list->head = iter;
        list->tail = iter;
        list->current = iter;
    }
    else
    {
        list->head->prev = iter;
        iter->next = list->head;
        list->head = iter;
        list->current = iter;
    }

    list->total++;
    return 0;
}

struct PCB* ListRemove(struct LIST* list)
{
    if(list->current == NULL)
        return NULL;
    struct NODE* iter = list->current;
    if(iter->next == NULL && list->total > 1)
    {
        iter->prev->next = NULL;
        iter->prev = NULL;
        list->current = NULL;
    }
    else if(list->total == 1)
    {
        list->head = NULL;
        list->tail = NULL;
		list->current = NULL;
    }
	else if (iter->prev == NULL)
	{
		list->head = iter->next;
		iter->next->prev = NULL;
		list->current = iter->next;
	}
    else
    {
        list->current = iter->next;
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
    }
    iter->status = 0;
    list->total--;
    used--;
    return iter->item;
}

void ListConcat(struct LIST* list1, struct LIST* list2)
{
	if (list1->head == NULL)
	{
		list1->head = list2->head;
		list1->tail = list2->tail;
   }
	else
	{
		list1->tail->next = list2->head;
		if (list2->head != NULL)
		{
			list2->head->prev = list1->tail;
			list1->tail = list2->tail;
		}
	}
	list1->total = list2->total + list1->total;
	list2->head = NULL;
	list2->current = NULL;
	list2->tail = NULL;
	list2->total = 0;
}

void itemFree(struct NODE* itemF)
{
        itemF->item = NULL;
        itemF->prev = NULL;
        itemF->status = 0;
}

void ListFree(struct LIST* list, void (*itemFree)(struct NODE*))
{
	list->current = list->head;
	for (int i = 0; i < list->total; i++)
	{
		(*itemFree)(list->current);
		list->current = list->current->next;
	}
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
	list->total = 0;
}

struct PCB* ListTrim(struct LIST* list)
{
    if(list->total == 0)
        return NULL;

    struct NODE* iter = list->tail;
    if(list->total == 1)
    {
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
    }
    else
    {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        list->current = list->tail;
    }
    iter->status = 0;
    list->total--;
    used--;
    return iter->item;
}

int compare(struct NODE* becompared, void* arg)
{
	if (becompared->item == arg)
		return 1;
	else
		return 0;
}

struct PCB* ListSearch(struct LIST* list, int (*comparator)(struct NODE*,  void* ), void* comparisonArg)
{
	struct NODE* iter = list->head;
	for (int i = 0; i < list->total; i++)
	{
		if ((*comparator)(iter, comparisonArg) == 1)
		{
			if (iter->prev != NULL)
				list->current = iter->prev;
			return iter->item;
		}
		iter = iter->next;
	}
	return NULL;
}
