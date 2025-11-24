#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "my_macros.h"
#include "str.h"
#include "List.h"
#include "NamedArray.h"
#include "Command.h"
#include "products_commands.h"

#include "array_commands.h"


static int array_command_rename(void *data){
	ArrayCommandContext *ctx = data;
	List *arrays = ctx->arrays;
	int index = ctx->index;
	NamedArray *na;

	autodel(str) new_name = new_str(16);
	puts("Enter new name of array:");
	while(new_name.len == 0){
		str_read(&new_name);
		if(new_name.len == 0)
			puts("Array name can`t be empty, try again!"); 
	}
	for(unsigned int i = 0; i < arrays->len; i++){
		na = List_get(arrays, i);
		if(str_cmp(&new_name, &na->name) == 0){
			puts("Array with this name already exists! Do you want to replace it? Y/N");
			char smb = _getch();
			if(smb == 'Y' || smb == 'y'){
				del_NamedArray(na);
				List_pop(arrays, index, na);
				NamedArray_rename(na, &new_name);
				puts("Array renamed succesfully!");
			} 
			cmd_ret(1);
		}
	}
	na = List_get(arrays, index);
	NamedArray_rename(na, &new_name);
	puts("Array renamed succesfully!");
	cmd_ret(1);
}

static int array_command_edit(void *data){
	ArrayCommandContext *ctx = data;
	List *arrays = ctx->arrays;
	int index = ctx->index;
	NamedArray *na = List_get(arrays, index);

	autodel(str) in_command = new_str(16);
	unsigned int id_command = 0;
	do {
		id_command = Command_select(products_commands, PRODUCTS_COMMANDS_LEN, &in_command);
	} while(products_commands[id_command].exec(&na->products));
	cmd_ret(1);
};

const Command array_commands[] = {
	{array_command_rename, (char*)"Change name"},
	{array_command_edit, (char*)"Edit products"},
	{std_command_close, (char*)"Back"},
	{std_command_unknown, NULL}
};

const size_t ARRAY_COMMANDS_LEN = (sizeof(array_commands) / sizeof(array_commands[0]));