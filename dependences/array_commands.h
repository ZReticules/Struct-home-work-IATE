#pragma once

#include <stddef.h>
#include "List.h"
#include "Command.h"

typedef struct {
	List *arrays;
	int index;
} ArrayCommandContext;

extern const Command array_commands[];
extern const size_t ARRAY_COMMANDS_LEN;