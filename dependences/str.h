#pragma once
#include <string.h>
#include "my_macros.h"

typedef struct {
	int cap;
	int len;
	char *c_str;
} str;

str new_str(unsigned int cap);

void str_realloc(str *s, unsigned int new_cap);

void str_add_char(str *s, char smb);

void str_add_chars(str *s, char *chs, int len);

static inline void str_add_str(str *s, str *s2){
	str_add_chars(s, s2->c_str, s2->len);
}

static inline void str_add_nchars(str *s, char *chs){
	str_add_chars(s, chs, strlen(chs));
}

#define str_add(s, arg, args...) _Generic((arg),\
		char *: _Generic((DEFAULT_IF_NONE(_G_TYPE(void), ##args)),\
			void: str_add_nchars,\
			default: str_add_chars\
		),\
		char: str_add_char,\
		str *: str_add_str\
	)(s, arg, ##args)

void str_clear(str *s);

void str_read(str *s);

void str_print(str *s);

str str_copy(str *s);

void str_mov(str *dest, str *src);

int str_cmp(str *a, str *b);

void del_str(str *s);
