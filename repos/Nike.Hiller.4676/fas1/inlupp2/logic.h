#ifndef __LOGIC_H__
#define __LOGIC_H__

#include <stdlib.h>
#include "hash_table.h"
#include "common.h"

void add_merch(ioopm_hash_table_t *ht_ns, ioopm_hash_table_t *ht_sn, elem_t merch);

void list_merch(ioopm_hash_table_t *ht_ns);

void remove_merch(ioopm_hash_table_t *ht_ns, elem_t merch);

void edit_merch(ioopm_hash_table_t *ht_ns, elem_t new_merch, elem_t orig_key);

void show_stock(elem_t *merch);

void replenish_stock(elem_t merch, elem_t shelf);

void create_cart(ioopm_list_t *cart_list);

void remove_cart(cart_t *cart);

void add_to_cart(cart_t *cart, elem_t merch, int qty);

void remove_from_cart(cart_t *cart, elem_t merch, int qty);

int calc_cost(cart_t *cart);

void checkout_cart(ioopm_list_t *cart_list, cart_t *cart);

#endif
