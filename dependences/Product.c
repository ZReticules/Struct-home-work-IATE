#include "Product.h"

#include <stdio.h>

#include "str.h"

Product new_Product(){
	Product res;
	res.name = new_str(16);
	res.producer = new_str(16);
	res.market = new_str(16);
	res.unit = new_str(8);
	res.cost = 0;
	res.count = 0;
	return res;
}

Product Product_copy(Product *pd){
	Product res;
	res.name = str_copy(&pd->name);
	res.producer = str_copy(&pd->producer);
	res.market = str_copy(&pd->market);
	res.unit = str_copy(&pd->unit);
	res.cost = pd->cost;
	res.count = pd->count;
	return res;
}

void Product_print(Product *pd){
	printf(
		"Name: %.*s\n"\
		"\tProducer: %.*s\n"\
		"\tMarket: %.*s\n"\
		"\tCost: %d\n"\
		"\tCount: %d %.*s.\n",
		pd->name.len, pd->name.c_str,
		pd->producer.len, pd->producer.c_str,
		pd->market.len, pd->market.c_str,
		pd->cost, pd->count,
		pd->unit.len, pd->unit.c_str
	);
}

void del_Product(Product *pd){
	del_str(&pd->name);
	del_str(&pd->producer);
	del_str(&pd->market);
	del_str(&pd->unit);
	pd->cost = 0;
	pd->count = 0;
}
