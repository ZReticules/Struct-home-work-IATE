#pragma once

#include "str.h"

typedef struct {
	str name, producer, market, unit;
	unsigned int cost, count;
} Product;

Product new_Product();

Product Product_copy(Product *pd);

void Product_print(Product *pd);

void del_Product(Product *pd);
