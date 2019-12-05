#ifndef __UI_H__
#define __UI_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"
#include "hash_table.h"
#include "linked_list.h"

/**
 * @file ui.h
 * @author Nike Hiller, Jonathan Lindroth
 * @date 04 November 2019
 * @brief Front end for a simple webstore
 *
 */

/// @brief Text user interface  
/// @param ht_ns initial data structure mapping name to merch elements
/// @param ht_sn initial data structure mapping shelf to merch elements
/// @param cart_ht initial data structure mapping cart ID's to cart elements
void event_loop(ioopm_hash_table_t *htns, ioopm_hash_table_t *htsn, ioopm_hash_table_t *cart_ht);


/// @brief Creates merch element   
/// @param name name of merchendise
/// @param desc description of merchandise
/// @param price price of single item of merchandise
elem_t make_merch(char *name, char *desc, int price);


/// @brief Creates shelf element  
/// @param loc location of shelf in warehouse
/// @param qty amount of items of merch on shelf
elem_t make_shelf(char* loc, int qty);

#endif
