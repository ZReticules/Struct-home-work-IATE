#include "dependences/my_macros.h"
#include "dependences/str.h"
#include "dependences/List.h"
#include "dependences/NamedArray.h"
#include "dependences/menu_commands.h"

int main(){
	autodel(List) arrays = new_List(NamedArray, 16);
	autodel(str) in_command = new_str(16);
	unsigned int id_command = 0;
	do {
		id_command = Command_select(menu_commands, MENU_COMMANDS_LEN, &in_command);
	} while(menu_commands[id_command].exec(&arrays));
}