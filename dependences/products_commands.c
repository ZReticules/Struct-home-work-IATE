#include <stdio.h>
#include <conio.h>
#include <stddef.h>
#include <stdlib.h>

#include "my_macros.h"
#include "str.h"
#include "List.h"
#include "Product.h"
#include "Command.h"

#include "products_commands.h"

static int products_command_print(void *data){
	List *products = data;
	for(unsigned int i = 0; i < products->len; i++){
		Product *pd = List_get(products, i);
		printf(
			"%d) Name: %.*s, producer: %.*s\n",
			i + 1, pd->name.len, pd->name.c_str,
			pd->producer.len, pd->producer.c_str
		);
	}
	if(products->len == 0)
		puts("No products");
	cmd_ret(1);
}

static int products_command_add(void *data){
	List *products = data;
	Product pd = new_Product();
	while(pd.name.len == 0){
		fputs("Enter product name: ", stdout);
		str_read(&pd.name);
		if(pd.name.len == 0)
			puts("Product name must be not empty, try again!");
	}
	while(pd.producer.len == 0){
		fputs("Enter producer name: ", stdout);
		str_read(&pd.producer);
		if(pd.producer.len == 0)
			puts("Producer name must be not empty, try again!");
	}
	while(pd.market.len == 0){
		fputs("Enter market name: ", stdout);
		str_read(&pd.market);
		if(pd.market.len == 0)
			puts("Market name must be not empty, try again!");
	}
	while(pd.unit.len == 0){
		fputs("Enter units name: ", stdout);
		str_read(&pd.unit);
		if(pd.unit.len == 0)
			puts("Units name must be not empty, try again!");
	}
	autodel(str) in_str = new_str(16);
	fputs("Enter count: ", stdout);
	str_read(&in_str);
	pd.count = strtol(in_str.c_str, NULL, 10);
	fputs("Enter cost: ", stdout);
	str_read(&in_str);
	pd.cost = strtol(in_str.c_str, NULL, 10);
	List_add(products, &pd);
	cmd_ret(1);
}

static int products_command_sort_name(void *data){
	List *products = data;
	autodel(List) copy = List_copy(products);
	
	List_sort(&copy, lambda(int anon_lamb(void *elem1, void *elem2, UNUSED_ARG void *param){
		Product *p1 = elem1, *p2 = elem2;
		return str_cmp(&p1->name, &p2->name);
	}), NULL);

	products_command_print(&copy);
	cmd_ret(1);
}

static int products_command_sort_producer(void *data){
	List *products = data;
	autodel(List) copy = List_copy(products);

	List_sort(&copy, lambda(int anon_lamb(void *elem1, void *elem2, UNUSED_ARG void *param){
		Product *p1 = elem1, *p2 = elem2;
		return str_cmp(&p1->producer, &p2->producer);
	}), NULL);
	products_command_print(&copy);
	cmd_ret(1);
}

static int products_command_change(void *data){
	List *products = data;

	autodel(str) in_str = new_str(16);
	unsigned int ans = 2;
	puts("Enter 1 if you want to choose index of product or 2 if you want to find it by name");
	while(ans > 1){
		str_read(&in_str);
		ans = strtol(in_str.c_str, NULL, 10) - 1;
		if(ans > 1)
			puts("Unexpected answer, please try again");
	}
	Product *pd = NULL;
	if(!ans){
		fputs("Enter index of product: ", stdout);
		ans = products->len;
		while(ans >= products->len){
			str_read(&in_str);
			ans = strtol(in_str.c_str, NULL, 10) - 1;
			if(ans >= products->len)
				fputs("Index out of range, please try again: ", stdout);
		}
		pd = List_get(products, ans);
	} else {
		fputs("Enter name of product: ", stdout);
		str_read(&in_str);
		ans = -1;
		for(unsigned int i = 0; i < products->len; i++){
			pd = List_get(products, i);
			if(!str_cmp(&pd->name, &in_str)){
				ans = i;
				break;
			}
			pd = NULL;
		}
	}
	if(pd == NULL){
		puts("Product not found");
		cmd_ret(1);
	}
	puts("Product found:");
	Product_print(pd);
	puts("Do you want to delete it? Y/N: ");
	char smb = _getch();
	if(smb == 'Y' || smb == 'y'){
		Product pd;
		List_pop(products, ans, &pd);
		del_Product(&pd);
		cmd_ret(1);
	}
	puts("Enter new values for fields or empty string to skip");

	inline void input_strfield(str *str_dest, str *in_str, const char field_name[]){
		str str_buf;
		printf("Old %s: '%.*s', enter new: ", field_name, str_dest->len, str_dest->c_str);
		str_read(in_str);
		if(in_str->len > 0){
			str_buf = *str_dest;
			*str_dest = *in_str;
			*in_str = str_buf;
		}
	}
	
	input_strfield(&pd->name, &in_str, "name");
	input_strfield(&pd->producer, &in_str, "producer");
	input_strfield(&pd->market, &in_str, "market");
	input_strfield(&pd->unit, &in_str, "unit");
	printf("Old cost: %d, enter new: ", pd->cost);
	str_read(&in_str);
	if(in_str.len > 0)
		pd->cost = strtol(in_str.c_str, NULL, 10);
	printf("Old count: %d, enter new: ", pd->count);
	str_read(&in_str);
	if(in_str.len > 0)
		pd->count = strtol(in_str.c_str, NULL, 10);
	cmd_ret(1);
}

static int products_command_product_info(void *data){
	List *products = data;
	fputs("Enter product name: ", stdout);
	autodel(str) searchName = new_str(16);
	str_read(&searchName);
	printf("Products with name '%.*s':\n", searchName.len, searchName.c_str);
	int counter = 0;
	for(unsigned int i = 0; i < products->len; i++){
		Product *pd = List_get(products, i);
		if(!str_cmp(&pd->name, &searchName)){
			printf("%d) ", ++counter);
			Product_print(pd);
		}
	}
	if(!counter)
		puts("Products not found");
	cmd_ret(1);
}

static int products_command_producer_info(void *data){
	List *products = data;
	fputs("Enter producer name: ", stdout);
	autodel(str) search_name = new_str(16);
	str_read(&search_name);
	printf("Products with producer name '%.*s':\n", search_name.len, search_name.c_str);
	int counter = 0;
	for(unsigned int i = 0; i < products->len; i++){
		Product *pd = List_get(products, i);
		if(!str_cmp(&pd->producer, &search_name)){
			printf("%d) ", ++counter);
			Product_print(pd);
		}
	}
	if(!counter)
		puts("Products not found");
	cmd_ret(1);
}

const Command products_commands[] = {
	{products_command_print, (char*)"Print products list"},
	{products_command_add, (char*)"Add new product"},
	{products_command_sort_name, (char*)"Print products list ordered by Product name"},
	{products_command_sort_producer, (char*)"Print products list ordered by Producer name"},
	{products_command_change, (char*)"Change existing product"},
	{products_command_product_info, (char*)"Get full info about existing product"},
	{products_command_producer_info, (char*)"Get full list of products by Producer name"},
	{std_command_close, (char*)"Back"},
	{std_command_unknown, NULL}
};

const size_t PRODUCTS_COMMANDS_LEN = (sizeof(products_commands) / sizeof(products_commands[0]));