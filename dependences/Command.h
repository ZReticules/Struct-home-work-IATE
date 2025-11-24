#pragma once

#include <stdio.h>
#include <conio.h>
#include "str.h"

typedef struct {
	int (*exec)(void *data);
	char *description;
} Command;

#ifdef OPTIMIZE

inline int Command_ret(int val){
	puts("Press any key to return...");
	_getch();
	return val;
}

#else

int Command_ret(int val);

#endif

#define cmd_ret(val) return Command_ret(val)

int Command_select(const Command commands[], unsigned int commands_len, str *inCommand);

int std_command_close(void *data);

int std_command_unknown(void *data);
