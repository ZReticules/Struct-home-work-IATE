#include "List.h"

#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "my_macros.h"

PREMAIN
static void List_premain(){
	srand(time(NULL));
};

List _new_List(unsigned int elemSize, unsigned int cap){
	List result;
	result.cap = cap;
	result.data = malloc(cap * elemSize);
	result.len = 0;
	result.elemSize = elemSize;
	return result;
}

void * List_add(List *list, void *elem){
	int elem_index = list->len;
	list->len += 1;
	if(list->cap == list->len){
		list->data = realloc(list->data, (list->cap + 16) * list->elemSize);
		list->cap += 16;
	}
	void *dest = &list->data[elem_index * list->elemSize];
	memcpy(dest, elem, list->elemSize);
	return dest;
}

void * List_get(List *list, unsigned int index){
	return index >= list->len ? NULL : &list->data[index * list->elemSize];
}

typedef struct {
	int (*comparator)(void *elem1, void *elem2, void *param);
	void *param;
	char *buf;
} _ListSortContext;

static void _List_sort(List *list, int start, int end, _ListSortContext *ctx){
	if(end - start <= 1)
		return;
	int i = start, j = end - 1;
	int base = rand() % (end - start) + start;
	void *base_elem = List_get(list, base);
	while(i != j){
		void *elem_i = List_get(list, i);
		int cmp_result = ctx->comparator(base_elem, elem_i, ctx->param);
		while(i != base && (cmp_result == 1 || cmp_result == 0)){
			i += 1;
			elem_i = List_get(list, i);
			cmp_result = ctx->comparator(base_elem, elem_i, ctx->param);
		}
		void *elem_j = List_get(list, j);
		cmp_result = ctx->comparator(base_elem, elem_j, ctx->param);
		while(j != base && (cmp_result == -1 || cmp_result == 0)){
			j -= 1;
			elem_j = List_get(list, j);
			cmp_result = ctx->comparator(base_elem, elem_j, ctx->param);
		}
		if(i != j){
			if(i == base)
				base = j;
			else if(j == base)
				base = i;
			memcpy(ctx->buf, elem_i, list->elemSize);
			memcpy(elem_i, elem_j, list->elemSize);
			memcpy(elem_j, ctx->buf, list->elemSize);
		}
	}
	_List_sort(list, start, base, ctx);
	_List_sort(list, base + 1, end, ctx);
}

void List_sort(List *list, int (*comparator)(void *elem1, void *elem2, void *param), void *param){
	char buf[list->elemSize];
	_List_sort(list, 0, list->len, &(_ListSortContext){comparator, param, (char*)&buf});
}

List List_copy(List *list){
	List res = _new_List(list->elemSize, list->cap);
	res.len = list->len;
	memcpy(res.data, list->data, res.elemSize * res.len);
	return res;
}

void List_pop(List *list, unsigned int index, void *dest){
	void *elem = List_get(list, index);
	if(dest != NULL)
		memcpy(elem, dest, list->elemSize);
	list->len -= 1;
	if(list->len != index)
		memmove(elem, elem + list->elemSize, (list->len - index) * list->elemSize);
}

void del_List(List *list){
	free(list->data);
	list->data = NULL;
	list->elemSize = 0;
	list->cap = 0;
	list->len = 0;
}
