#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "string.h"

/*
 * @file common.c
 * @author Jonathan Lindroth, Ludwig Ridderstolpe
 * @date 10 Oct 2019
 * @brief Common resources for linked_list.c and hash_table.c
 *
 */


bool elem_int_equiv(elem_t a, elem_t b)
{
  return a.i == b.i;
}

bool elem_bool_equiv(elem_t a, elem_t b)
{
  return a.b == b.b;
}

bool elem_float_equiv(elem_t a, elem_t b)
{
  return a.f == b.f;
}

bool elem_str_equiv(elem_t a, elem_t b)
{
  return strcmp(a.charp, b.charp) == 0;
}

bool elem_merch_equiv(elem_t a, elem_t b)
{
  return strcmp(a.merchp->name, b.merchp->name) == 0;
}

bool elem_shelf_equiv(elem_t a, elem_t b)
{
  return strcmp(a.shelfp->loc, b.shelfp->loc) == 0;
}
<<<<<<< HEAD:inlupp2/common.c
=======

bool elem_cart_equiv(elem_t a, elem_t b)
{
  return a.cartp->id == b.cartp->id;
}
>>>>>>> a0dc8116782f60cb9860d66a41cdbcd2b665e18f:inlupp2/src/common.c
