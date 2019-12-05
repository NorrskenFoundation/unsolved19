#include "logic.h"
#include <stdlib.h>
#include <stdio.h>

void add_merch(ioopm_hash_table_t *ht_ns, ioopm_hash_table_t *ht_sn, elem_t merch) {
  if (!ioopm_hash_table_has_key(ht_ns,ioopm_charp_elem(merch.merchp->name))) {
    ioopm_hash_table_insert(ht_ns, ioopm_charp_elem(merch.merchp->name), merch);
    
    //puts("Merch added to warehouse");
  }
  else {
    //  puts("This merchandise already exists. Nothing changed.");
  }
}

//tested manually, not tested for 20+ items
void list_merch(ioopm_hash_table_t *ht_ns) {
  int index = 1;
  ioopm_list_t* list = ioopm_hash_table_values(ht_ns);
  ioopm_list_iterator_t* itr = ioopm_list_iterator_create(list);
  while(ioopm_iterator_has_next(itr)) {
    printf("[%d] %s\n", index, ioopm_iterator_current(itr).merchp->name);
    ioopm_iterator_next(itr);
    index++;
    if(index%20 == 0 && toupper(*ask_question_string("[C] to continue listing, any other key to return to main menu")) == 'C' ) {
      break;
    }
  }
  ioopm_iterator_destroy(itr);
  ioopm_linked_list_destroy(list);
} 

/*
static void clear_shelf(elem_t* shelf){
  shelf->shelfp->loc = NULL;
  shelf->shelfp->qty = 0;
  }*/
//TODO: make_shelf calloc orsakar memleak
static void clear_shelflist(shelf_list_t* shelflist){
  ioopm_list_iterator_t* itr = ioopm_list_iterator_create(shelflist->llist);
  while(ioopm_iterator_has_next(itr)) {
    ioopm_iterator_remove(itr); 
  }
  ioopm_iterator_destroy(itr);
}

static void free_merch(elem_t merch) {
  clear_shelflist(merch.merchp->shelflist);
  ioopm_linked_list_destroy(merch.merchp->shelflist->llist);
  free(merch.merchp->shelflist);
  free(merch.merchp);
}

void remove_merch(ioopm_hash_table_t *ht_ns, elem_t merch) {
  elem_t* result = &ioopm_charp_elem("Init"); //How can we initialize a temporary result pointer on the stack properly?
  ioopm_hash_table_remove(ht_ns, ioopm_charp_elem(merch.merchp->name), result);
  free_merch(merch);
}
//TODO: Check for existing key in main
//brief: takes a merch and copies values(not list) over to original and then deletes merch_new
//original merch is reinserted into hashtable
void edit_merch(ioopm_hash_table_t *ht_ns, elem_t merch_new, elem_t orig_key) {
  elem_t* orig_merchp = &ioopm_charp_elem("Init");
  ioopm_hash_table_remove(ht_ns, orig_key, orig_merchp);
  orig_merchp->merchp->name = merch_new.merchp->name;
  orig_merchp->merchp->desc = merch_new.merchp->desc;
  orig_merchp->merchp->price = merch_new.merchp->price;
  ioopm_hash_table_insert(ht_ns, ioopm_charp_elem(orig_merchp->merchp->name), *orig_merchp);
  free_merch(merch_new);
}

//Untested. 
void show_stock(elem_t* merch) {
  if(merch->merchp->shelflist->qty > 0) {
    printf("%s - In stock in the following locations\n",merch->merchp->name);
    ioopm_list_iterator_t* itr = ioopm_list_iterator_create(merch->merchp->shelflist->llist); 
    while(ioopm_iterator_has_next(itr)) {
      printf("%s:%d",ioopm_iterator_current(itr).shelfp->loc, ioopm_iterator_current(itr).shelfp->qty);
      ioopm_iterator_next(itr);
    }
    ioopm_iterator_destroy(itr);
  }
  else {
    puts("Not in stock");
  }  
}

//Initiate linked list in shelf with empty shelf structs
void replenish_stock(elem_t merch, elem_t shelf) {
  bool existing = false;
  ioopm_list_t* llist = merch.merchp->shelflist->llist;
  ioopm_list_iterator_t* itr = ioopm_list_iterator_create(llist);
  while(ioopm_iterator_has_next(itr)) {
    if (llist->eq_fun(ioopm_iterator_current(itr), shelf)) {
      ioopm_iterator_current(itr).shelfp->qty+=shelf.shelfp->qty;
      existing = true;
    }
    ioopm_iterator_next(itr);
  }
  ioopm_iterator_destroy(itr);
  if (existing == false) {
    ioopm_linked_list_append(merch.merchp->shelflist->llist, shelf);
  }
}

void create_cart(ioopm_list_t *cart_list);

void remove_cart(cart_t *cart);

void add_to_cart(cart_t *cart, elem_t merch, int qty);

void remove_from_cart(cart_t *cart, elem_t merch, int qty);

int calc_cost(cart_t *cart);

void checkout_cart(ioopm_list_t *cart_list, cart_t *cart);
