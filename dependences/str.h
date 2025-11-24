#pragma once

typedef struct {
	int cap;
	int len;
	char *c_str;
} str;

str new_str(unsigned int cap);

void str_realloc(str *s, unsigned int new_cap);

void str_add_char(str *s, char smb);

void str_clear(str *s);

void str_read(str *s);

void str_print(str *s);

str str_copy(str *s);

void str_mov(str *dest, str *src);

int str_cmp(str *a, str *b);

void del_str(str *s);