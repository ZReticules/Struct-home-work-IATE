#include "Command.h"

#include <stdio.h>
#include <stdlib.h>

#include "str.h"
#include "List.h"
#include "my_macros.h"

#ifndef OPTIMIZE

int Command_ret(int val){
	puts("Press any key to return...");
	_getch();
	return val;
}

#endif

int Command_select(const Command commands[], unsigned int commands_len, str *inCommand){
	unsigned int id_command;
	puts("Availible commands:");
	for(unsigned int i = 0; i < commands_len - 1; i++)
		printf("%d. %s\n", i + 1, commands[i].description);
	str_read(inCommand);
	id_command = strtol(inCommand->c_str, NULL, 10) - 1;
	if(id_command >= commands_len)
		id_command = commands_len - 1;
	return id_command;
}

int std_command_close(UNUSED_ARG void *data){
	puts("Return to prevous...");
	return 0;
}

int std_command_unknown(UNUSED_ARG void *data){
	puts("Unknown command, please try again!");
	return 1;
}