#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdbool.h>
#include <stddef.h>
#include "linked_list.h"
#include "common.h"

/**
 * @file hash_table.h
 * @author Axel Bergström, Andreas Larsson
 * @date 03 Okt 2019
 * @brief Hash table that maps keys of a type of 'elem_t' to values of type 'elem_t'
 *
 */




/// @brief Create a new hash table
/// @param hash_fun function used to hash keys
/// @param key_eq function used to check if keys are equal key_eq(a, b) should imply hash_fun(a) == hash_fun(b)
/// @param val_eq function used to check if values are equal
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash_fun, ioopm_eq_function key_eq, ioopm_eq_function val_eq);

/// @brief Create a new hash table
/// @param hash_fun function used to hash keys
/// @param key_eq function used to check if keys are equal key_eq(a, b) should imply hash_fun(a) == hash_fun(b)
/// @param val_eq function used to check if values are equal
/// @param no_buckets initial nuber of buckets in new table
/// @param load_factor_limits maximum allowed ration of entries to numbber of buckets, hash table will grow if this limit is exceeded
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create_advanced(ioopm_hash_function hash_fun, ioopm_eq_function key_eq, ioopm_eq_function val_eq, size_t no_buckets, double load_factor_limit);

/// @brief Delete a hash table and free its memory.
///        Elements are not freed.
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @param result pointer to location which will be updated to contain the
///               found value if the operation succeeds
/// @return false if operation failed, true if operation succeeded
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

/// @brief remove a mapping from key to a value if the key exists
/// @param ht hash table operated upon
/// @param key key to remove
/// @param result pointer to location which will be updated to contain the
///               removed value if the operation succeeds
/// @return false if operation failed, true if operation succeeded
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

/// @brief returns the number of key => value entries in the hash table
/// @param ht hash table operated upon
/// @return the number of key => value entries in the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);

/// @brief checks if the hash table is empty
/// @param ht hash table operated upon
/// @return true is size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief clear all the entries in a hash table.
///        the elements will not be freed.
/// @param ht hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);

/// @brief return a list of the keys for all entries in a hash map
///        (in no particular order, but same as ioopm_hash_table_values)
/// @param ht hash table operated upon
/// @return an linked list of keys for hash table ht
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht);

/// @brief return a list of the values for all entries in a hash map
///        (in no particular order, but same as ioopm_hash_table_keys)
/// @param ht hash table operated upon
/// @return a linked list of values for hash table ht
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht);

/// @brief check if a hash table has an entry with a given key
/// @param ht hash table operated upon
/// @param key the key sought
/// @return true if key is in ht, else false
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if a hash table has an entry with a given value
/// @param ht hash table operated upon
/// @param value the value sought
/// @return true if value is in ht, else false
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
/// @return true if pred is satisfied for all values
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *args);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
/// @return true if pred is satisfied for any value
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *args);

/// @brief apply a function to all entries in a hash table
/// @param ht hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *args);

/// @brief hash function for null terminated strings
/// @param str the string to be hashed
/// @return a hash value for the string
int ioopm_string_knr_hash(elem_t str);

#endif
