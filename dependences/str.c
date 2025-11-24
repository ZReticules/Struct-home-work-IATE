#include "str.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>

str new_str(unsigned int cap){
	str result;
	result.cap = cap;
	result.len = 0;
	result.c_str = malloc((cap + 1) * sizeof(char));
	result.c_str[0] = '\0';
	return result;
}

void str_realloc(str *s, unsigned int new_cap){
	s->c_str = realloc(s->c_str, (new_cap + 1) * sizeof(char));
	s->cap = new_cap;
	s->c_str[new_cap] = '\0';
}

void str_add_char(str *s, char smb){
	if(s->len < s->cap){
		str_realloc(s, s->cap + 16);
		s->cap += 16;
	}
	s->c_str[s->len++] = smb;
	s->c_str[s->len] = '\0';
}

void str_clear(str *s){
	s->c_str[0] = '\0';
	s->len = 0;
}

void str_read(str *s){
	str_clear(s);
	for(char smb = getchar(); smb != '\n'; smb = getchar())
		str_add_char(s, smb);
}

void str_print(str *s){
	fputs(s->c_str, stdout);
}

str str_copy(str *s){
	str result = new_str(s->cap);
	result.cap = s->cap;
	result.len = s->len;
	memcpy(result.c_str, s->c_str, (s->len + 1) * sizeof(char));
	return result;
}

void str_mov(str *dest, str *src){
	if(dest->cap < src->cap)
		str_realloc(dest, src->cap);
	dest->cap = src->cap;
	dest->len = src->len;
	memcpy(dest->c_str, src->c_str, (src->len + 1) * sizeof(char));
}

int str_cmp(str *a, str *b){
	int min_len = a->len > b->len ? a->len : b->len;
	int result = memcmp(a->c_str, b->c_str, min_len);
	if(result != 0 || a->len == b->len)
		return result;
	return a->len > b->len ? 1 : -1;
}

void del_str(str *s){
	s->cap = 0;
	s->len = 0;
	free(s->c_str);
	s->c_str = NULL;
}