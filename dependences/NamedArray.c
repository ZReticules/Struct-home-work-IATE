#include "NamedArray.h"

#include "Product.h"

NamedArray new_NamedArray(str *name){
	NamedArray res;
	res.name = str_copy(name);
	res.products = new_List(Product, 16);
	return res;
};

NamedArray NamedArray_copy(NamedArray *na){
	NamedArray res;
	res.name = str_copy(&na->name);
	res.products = List_copy(&na->products);
	for(unsigned int i = 0; i < res.products.len; i++){
		Product *pd = List_get(&res.products, i);
		*pd = Product_copy(pd);
	}
	return res;
}

void NamedArray_rename(NamedArray *na, str *newName){
	str_mov(&na->name, newName);
}

void del_NamedArray(NamedArray *na){
	del_str(&na->name);
	for(unsigned int i = 0; i < na->products.len; i++)
		del_Product((Product *)List_get(&na->products, i));
	del_List(&na->products);
};