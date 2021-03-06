#ifndef __TEST_H__
#define __TEST_H__

#include "bst.h"
#include "avl.h"
#include "hash_table.h"

int test();
int test_insert(int size, int cycle);

int deleted_in_file(int number);
void efficiency(int len_table);
unsigned long int tick(void);

#endif