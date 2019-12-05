#ifndef __COMMON_H_
#define __COMMON_H_
#include <stdbool.h>

/**
 * @file common.h
 * @author Ali Hoseini & Nike Hiller
 * @date 26 oct 2019 
 * @brief common resources for linked list and hash table
 */


typedef union elem  elem_t;
union elem
{
  int int_nr;
  char *string;
  unsigned int unsigned_nr;
  bool bool_nr;
  float float_nr;
  void *pointer;
};

#define int_elem(x) (elem_t) { .int_nr=(x) }
#define char_elem(x) (elem_t) { .string=(x) }
#define unsigned_elem(x) (elem_t) { .unsigned_nr=(x) }
#define bool_elem(x) (elem_t) { .bool_nr=(x) }
#define float_elem(x) (elem_t) { .float_nr=(x) }
#define void_elem(x) (elem_t) { .pointer=(x) }

#define ioopm_int_str_list_insert(ht, i, s) \
   ioopm_linked_list_insert(ht, int_elem(i), ptr_elem(s))

typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);

typedef unsigned long(*ioopm_hash_function)(elem_t elem);

/// @brief Compare the values of two int elements
/// @param a element to compare
/// @param b element compared to
/// @return true if a and b is equals else returns false
bool compare_int_elements(elem_t a, elem_t b);

/// @brief Compare the values of two string elements
/// @param a element to compare
/// @param b element compared to
/// @return true if a and b is equals else returns false
bool compare_string_elements(elem_t a, elem_t b);

/// @brief Compare two boolean elements
/// @param a element to compare
/// @param b element compared to
/// @return true if a and b is equals else returns false
int compare_bool_elements(elem_t a, elem_t b);

/// @brief Compare two float elements
/// @param a element to compare
/// @param b element compared to
/// @return true if a and b is equals else returns false
int compare_float_elements(elem_t a, elem_t b);

/// @brief Extracts string and hashes it 
/// @param keys to be hashed
/// @return hash code
unsigned long hash_function(elem_t key);

/// @brief Extracts int and hashes it 
/// @param keys to be hashed
/// @return hash code
unsigned long extract_int_hash_key(elem_t key);
#endif
