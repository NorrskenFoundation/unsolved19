<<<<<<< HEAD:inlupp2/common.h
=======

>>>>>>> a0dc8116782f60cb9860d66a41cdbcd2b665e18f:inlupp2/src/common.h
#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

/**
 * @file iterator.h
 * @author Axel Bergström, Andreas Larsson
 * @date 03 Okt 2019
 * @brief Common definition for hash_table.h, linked_list.h, and iterator.h
 *
 */

/// @typedef Union of the types int, unsigned, bool, float, char*, and void*
///          The union members are called i, u, b, f, charp, and voidp.
///          Convenience macros are provided to construct an element of a specific type.
///          Theese macros are called 'ioopm_*_elem' where '*' is one of
///          int, unsigned, bool, float, charp, or voidp.
typedef union elem elem_t;
typedef struct merch merch_t;
typedef struct shelf shelf_t;
typedef struct shelf_list shelf_list_t;
typedef struct cart cart_t; 
typedef struct link link_t;
typedef struct list ioopm_list_t;
<<<<<<< HEAD:inlupp2/common.h

=======
typedef struct hash_table ioopm_hash_table_t;
>>>>>>> a0dc8116782f60cb9860d66a41cdbcd2b665e18f:inlupp2/src/common.h

union elem
{
  int i;
  unsigned int u;
  bool b;
  float f;
  char *charp;
  void *voidp;
  merch_t *merchp;
  shelf_t *shelfp;
<<<<<<< HEAD:inlupp2/common.h
=======
  cart_t *cartp;
>>>>>>> a0dc8116782f60cb9860d66a41cdbcd2b665e18f:inlupp2/src/common.h
};

struct merch {
  char* name;
  char* desc;
  shelf_list_t* shelflist; 
  int price;
};

struct cart {
  ioopm_hash_table_t* items;
  int total_cost;
  int id;
};

struct shelf {
  char* loc;
  int qty;
};

struct shelf_list {
  ioopm_list_t* llist;
  int qty;
};
/// @typedef predicate used in some functions on the hash table and linked list types
typedef bool(*ioopm_predicate)(elem_t key, elem_t value, void *extra);

/// @typedef apply function used in some functions on the hash table and linked list types
typedef void(*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);

/// @typedef function used to compare two elem_t:s
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);

/// @typedef function used to give a hash value for a elem_t
typedef int(*ioopm_hash_function)(elem_t elem);

struct link 
{
  elem_t element;
  link_t *next;
};



struct list
{
  link_t *first;
  link_t *last;
  ioopm_eq_function eq_fun;
  size_t list_length;
};

#define ioopm_int_elem(e) ((elem_t) {.i = e})
#define ioopm_unsigned_elem(e) ((elem_t) {.u = e})
#define ioopm_bool_elem(e) ((elem_t) {.b = e})
#define ioopm_float_elem(e) ((elem_t) {.f = e})
#define ioopm_charp_elem(e) ((elem_t) {.charp = e})
#define ioopm_voidp_elem(e) ((elem_t) {.voidp = e})
#define int_elem(in) (elem_t) { .i=(in) }
#define str_elem(s) (elem_t) { .charp=(s) }
#define ioopm_merch_elem(e) (elem_t) {.merchp = e}
#define ioopm_shelf_elem(e) (elem_t) {.shelfp = e}
<<<<<<< HEAD:inlupp2/common.h
=======
#define ioopm_cart_elem(e) (elem_t) {.cartp = e}
>>>>>>> a0dc8116782f60cb9860d66a41cdbcd2b665e18f:inlupp2/src/common.h
// ----------- linked list j --------------//

typedef struct option option_t;
struct option
{
  bool success;
  elem_t value;
};

#define Success(v)      (option_t) { .success = true, .value = v };
#define Failure()       (option_t) { .success = false };
#define Successful(o)   (o.success == true)
#define Unsuccessful(o) (o.success == false)

/// @brief Compare the values of two int elements
/// @param a the element to compare
/// @param b the element compared to
/// @return positive if a is larger, 0 if equal and negative otherwise
bool elem_int_equiv(elem_t a, elem_t b);

/// @brief Compare the values of two bool elements
/// @param a the element to compare
/// @param b the element compared to
/// @return positive if a is larger, 0 if equal and negative otherwise
bool elem_bool_equiv(elem_t a, elem_t b);

/// @brief Compare the values of two float elements
/// @param a the element to compare
/// @param b the element compared to
/// @return positive if a is larger, 0 if equal and negative otherwise
bool elem_float_equiv(elem_t a, elem_t b);

/// @brief Compare the ASCII values of two string elements
/// @param a the element to compare
/// @param b the element compared to
/// @return positive if first unmatched character is less than second, 0 if the strings are equivalent and negative otherwise
bool elem_str_equiv(elem_t a, elem_t b);

bool elem_merch_equiv(elem_t a, elem_t b);

bool elem_shelf_equiv(elem_t a, elem_t b);

<<<<<<< HEAD:inlupp2/common.h
=======
bool elem_cart_equiv(elem_t a, elem_t b);

>>>>>>> a0dc8116782f60cb9860d66a41cdbcd2b665e18f:inlupp2/src/common.h
#endif
