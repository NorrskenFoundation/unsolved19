#ifndef __LOGIC_H__
#define __LOGIC_H__

#include <stdlib.h>
#include "hash_table.h"
#include "common.h"

/**
 * @file logic.h
 * @author Nike Hiller, Jonathan Lindroth
 * @date 04 November 2019
 * @brief Business logic for a simple webstore
 *
 */

/// @brief Inserts merch into ht_ns 
/// @param ht_ns hash table where merch is to be inserted
/// @param ht_sn unused parameter
/// @param merch merch to be inserted 
void add_merch(ioopm_hash_table_t *ht_ns, ioopm_hash_table_t *ht_sn, elem_t merch);

/// @brief list all merch in ht_ns 
/// @param ht_ns hash table to be printed 
void list_merch(ioopm_hash_table_t *ht_ns);

/// @brief Remove merch from ht_ns and delete its content 
/// @param ht_ns hash table that merch will be removed from 
/// @param ht_sn hash table that merch will be removed from
/// @param merch merch to be removed
void remove_merch(ioopm_hash_table_t *ht_ns,ioopm_hash_table_t *ht_sn, elem_t merch);

/// @brief Edits attributes of merch that orig_key maps to 
/// @param ht_ns hash table that contains merch to be edited 
/// @param ht_sn unused
/// @param new_merch merch containing the new values of the attributes to be inserted
void edit_merch(ioopm_hash_table_t *ht_ns, ioopm_hash_table_t* ht_sn, elem_t new_merch, elem_t orig_key);

/// @brief List all storage locations and corresponding quantities for a particular merch
/// @param merch merch that will be listed
void show_stock(elem_t *merch);

/// @brief Increase the stock of a merch by at least one
/// @param ht_sn hash table that contains merch to be replenished 
/// @param merch merch to be replenished
/// @param shelf shelf to be replenished
void replenish_stock(ioopm_hash_table_t *ht_sn ,elem_t merch, elem_t shelf);

/// @brief Creates a new empty shopping cart
/// @param cart_ht hash table where cart will be stored 
void create_cart(ioopm_hash_table_t *cart_ht);

/// @brief Removes shopping cart for the system
/// @param cart_ht hash table where cart will be stored
/// @param cart cart ro be removed
void remove_cart(ioopm_hash_table_t *ht_carts, cart_t *cart);

/// @brief Add some quantity of a merch to a specific shopping cart
/// @param ht_carts hash table where cart is stored
/// @param cart where merch will be inserted
/// @param merch merch to be inserted
/// @param qty quantity of merch to be added
void add_to_cart(ioopm_hash_table_t* ht_carts, cart_t *cart, elem_t merch, int qty);

/// @brief Remove zero or more items of some merch from a particular cart
/// @param cart cart to be removed from
/// @param merch merch to be removed from
/// @param qty quantity of merch to be removed
void remove_from_cart(cart_t *cart, elem_t merch, int qty);

/// @brief Calculate the cost of a shoppin cart
/// @param cart cart to be calculate
void calc_cost(cart_t *cart);

/// @brief Decreases the stock for the merches in the cart and removes the shopping cart
/// @param ht_ns the hash table that stores the merch to be decreased 
/// @param ht_carts the hash table that stores the carts
/// @param cart cart to be deleted
void checkout_cart(ioopm_hash_table_t* ht_ns, ioopm_hash_table_t* ht_carts, cart_t *cart);

/// @brief Removes all data from a shelf
/// @param shelf shelf to be cleared
void clear_shelf(elem_t* shelf);

/// @brief Get the unique cart ID for the next cart created
int get_cart_number();
#endif
