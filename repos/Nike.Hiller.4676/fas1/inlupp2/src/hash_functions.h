#ifndef __HASH_FUNCTIONS_H__
#define __HASH_FUNCTIONS_H__

#include "hash_table.h"

/*
 * @file hash_functions.h
 * @author Jonathan Lindroth, Ludwig Ridderstolpe
 * @date 1 Sep 2019
 * @brief Hash functions
 *
 */

int merch_hash_fun(elem_t key);

/// @brief extracts the containing string and hashes it by its ASCII value
/// and provided algorithm
/// @param key to be hashed 
/// @return the produced hash code
int str_hash_fun(elem_t key);

/// @brief extracts the containing integer value 
/// @param key to be hashed
/// @return the produced hash code
int unsigned_int_hash_fun(elem_t key);

/// @brief extracts and converts bool to integer
/// @param key to be hashed
/// @return the produced hash code
int bool_hash_fun(elem_t key);

/// @brief extracts and truncates float
/// @param the list to be iterated over
/// @return the produced hash code
int float_hash_fun(elem_t key);

#endif
