#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "common.h"
#include "linked_list.h"
#include "hash_table.h"
#include "hash_functions.h"
#include "ui.h"
#include "logic.h"

<<<<<<< HEAD:inlupp2/main.c
int main() {
  ioopm_hash_table_t *htns = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  merch_t merch = {.name = "Books", .desc = "Cheap books", .list=NULL, .price = 100};
  elem_t merchp = ioopm_merch_elem(&merch);
  merch_t merch2 = {.name = "Movies", .desc = "Good movies", .list=NULL, .price = 100};
  elem_t merchp2 = ioopm_merch_elem(&merch2);
  add_merch(htns, NULL, merchp);
  add_merch(htns, NULL, merchp2);
  list_merch(htns);
  ioopm_hash_table_destroy(htns);
=======

int main() {
  ioopm_hash_table_t *htns = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  ioopm_hash_table_t *htsn = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  ioopm_hash_table_t *ht_carts = ioopm_hash_table_create(unsigned_int_hash_fun, elem_int_equiv, elem_cart_equiv);
  event_loop(htns, htsn, ht_carts);
  ioopm_hash_table_destroy(htns);
  ioopm_hash_table_destroy(htsn);
  ioopm_hash_table_destroy(ht_carts);
>>>>>>> a0dc8116782f60cb9860d66a41cdbcd2b665e18f:inlupp2/src/main.c
  return 0;
}
