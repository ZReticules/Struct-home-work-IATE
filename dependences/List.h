#pragma once

typedef struct {
	unsigned int cap, len, elemSize;
	char *data;
} List;

List _new_List(unsigned int elemSize, unsigned int cap);

#define new_List(type, size) _new_List(sizeof(type), size)

void * List_add(List *list, void *elem);

void * List_get(List *list, unsigned int index);

void List_sort(List *list, int (*comparator)(void *elem1, void *elem2, void *param), void *param);

List List_copy(List *list);

void List_pop(List *list, unsigned int index, void *dest);

void del_List(List *list);