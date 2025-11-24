#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stddef.h>

#include "my_macros.h"
#include "str.h"
#include "List.h"
#include "NamedArray.h"
#include "Command.h"
#include "array_commands.h"

#include "menu_commands.h"


static int menu_command_new_array(void *data){
	List *arrays = data;
	autodel(str) name = new_str(16);
	puts("Enter name of new array:");
	while(name.len == 0){
		str_read(&name);
		if(name.len == 0){
			puts("Array name can`t be empty, try again!"); 
			continue;
		}
		for(unsigned int i = 0; i < arrays->len; i++){
			NamedArray *na = List_get(arrays, i);
			if(str_cmp(&name, &na->name) == 0){
				str_clear(&name);
				puts("Array with this name already exists, try again!");
				break;
			}
		}
	}
	NamedArray new = new_NamedArray(&name);
	List_add(arrays, &new);
	puts("Array created succesfully! Now you can edit it in main menu.");
	cmd_ret(1);
}

static int menu_command_edit_array(void *data){
	List *arrays = data;
	autodel(str) in_command = new_str(16);
	unsigned int id_command = 0, array_index = 0;
	do {
		if(!arrays->len){
			puts("Zero arrays available");
			cmd_ret(1);
		}
		puts("Select index of one of available arrays:");
		for(unsigned int i = 0; i < arrays->len; i++){
			NamedArray *na = List_get(arrays, i);
			printf("%d) %.*s\n", i + 1, na->name.len, na->name.c_str);
		}
		do {
			str_read(&in_command);
			array_index = strtol(in_command.c_str, NULL, 10) - 1;
			if(array_index > arrays->len)
				fputs("Index out of range, please try again: ", stdout);
		} while(array_index > arrays->len);
		puts("Do you want to delete it? Y/N:");
		char smb = _getch();
		if(smb == 'Y' || smb == 'y'){
			NamedArray na;
			List_pop(arrays, array_index, &na);
			del_NamedArray(&na);
			cmd_ret(1);
		}
		id_command = Command_select(array_commands, ARRAY_COMMANDS_LEN, &in_command);
	} while(array_commands[id_command].exec(&(ArrayCommandContext){arrays, array_index}));
	cmd_ret(1);
}

const Command menu_commands[] = {
	{menu_command_new_array, (char*)"Create new array"},
	{menu_command_edit_array, (char*)"Edit existing array"},
	{std_command_close, (char*)"Exit"},
	{std_command_unknown, NULL}
};

const size_t MENU_COMMANDS_LEN = sizeof(menu_commands)/sizeof(menu_commands[0]);