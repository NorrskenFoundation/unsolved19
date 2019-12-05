#include "ui.h"

elem_t make_merch(char *name, char *desc, int price) {
  merch_t* merch = calloc(1,sizeof(merch_t));
  shelf_list_t* shelf = calloc(1,sizeof(shelf_list_t)); 
  *shelf = (shelf_list_t) {.qty = 0, .llist = ioopm_linked_list_create(elem_shelf_equiv)};
  *merch = (merch_t) {.name = name, .desc = desc, .shelflist=shelf, .price = price};
  return ioopm_merch_elem(merch); 
}


elem_t make_shelf(char* loc, int qty) {
  shelf_t* shelf = calloc(1,sizeof(merch_t));
  *shelf = (shelf_t) {.qty=qty, .loc=loc}; 
  return ioopm_shelf_elem(shelf); 
}
