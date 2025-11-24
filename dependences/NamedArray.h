#pragma once

#include "str.h"
#include "List.h"

typedef struct {
	str name;
	List products;
} NamedArray;

NamedArray new_NamedArray(str *name);

NamedArray NamedArray_copy(NamedArray *na);

void NamedArray_rename(NamedArray *na, str *newName);

void del_NamedArray(NamedArray *na);