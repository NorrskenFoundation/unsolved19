#include <stdbool.h>
#include <stdlib.h>
#include "linked_list.h"
#include "common.h"


 /**
 * @file hash_table.h
 * @author Ali Hoseini & Nike Hiller
 * @date 26 oct 2019 
 * @brief Simple hash table that maps integers keys tp strings values.
 */

typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;
typedef struct iter iter_t;
typedef bool(*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void(*ioopm_apply_function)(elem_t key, elem_t value, void *extra);
typedef unsigned long(*ioopm_hash_function)(elem_t key);

struct option
{
  bool success;
  elem_t value;
};

//bool predicate(int key, char *value, void *extra);
//void apply(int key, char **value, void *extra);
//void apply_print_h(int key, char**value, void *extra);
ioopm_hash_table_t *ioopm_hash_table_dynamic(ioopm_eq_function eq_func, ioopm_hash_function hash_func, double load_factor, size_t capacity);

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_eq_function eq_func, ioopm_hash_function hash_func);

/// @brief Delete a hash table and free its memory
/// param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the element maped to the key
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the element mapped to the key 
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);

/// @brief returns the number of key => value entries in the hash table
/// @param h hash table operated upon
/// @return the number of key => value entries in the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *h);

/// @brief checks if the hash table is empty
/// @param h hash table operated upon
/// @return true is size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *h);

/// @brief clear all the entries in a hash table
/// @param h hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *h);

/// @brief return the keys for all entries in a hash map (in particular order)
/// @param h hash table operated upon
/// @return a linked list of keys for hash table h
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *h);

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param h hash table operated upon
/// @return an linked list of  values for hash table h
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *h);

/// @brief check if a hash table has an entry with a given key
/// @param h hash table operated upon
/// @param key the key sought
bool ioopm_hash_table_has_key(ioopm_hash_table_t *h,ioopm_predicate key_equiv, elem_t key);

/// @brief check if a hash table has an entry with a given value
/// @param h hash table operated upon
/// @param value the value sought
bool ioopm_hash_table_has_value(ioopm_hash_table_t *h,ioopm_predicate value_equiv, elem_t value);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred

bool ioopm_hash_table_all(ioopm_hash_table_t *h, ioopm_predicate red, void *arg);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_any(ioopm_hash_table_t *h, ioopm_predicate  pred, void *arg);

/// @brief apply a function to all entries in a hash table
/// @param h hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *h, ioopm_apply_function apply_fun, void *arg);
