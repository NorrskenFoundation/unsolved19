/* This code adheres to the spaghetti code convention and contains pointers well into the 4th dimenson.
   Although it is tortuos, it passes extensive tests.
 */

#include "logic.h"
#include "hash_functions.h"
#include <stdlib.h>
#include <stdio.h>
static int Cart_Number = 1;

int get_cart_number(){
  return Cart_Number;
}

void add_merch(ioopm_hash_table_t *ht_ns, ioopm_hash_table_t *ht_sn, elem_t merch) {
  if (!ioopm_hash_table_has_key(ht_ns,ioopm_charp_elem(merch.merchp->name))) {
    puts("Merch added to warehouse");
    ioopm_hash_table_insert(ht_ns, ioopm_charp_elem(merch.merchp->name), merch);
  }
  else {
    puts("This merchandise already exists. Nothing changed.");
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


void clear_shelf(elem_t* shelf){
  shelf->shelfp->loc = NULL;
  shelf->shelfp->qty = 0;
  free(shelf->shelfp);
}

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

void remove_merch(ioopm_hash_table_t *ht_ns,ioopm_hash_table_t *ht_sn, elem_t merch) {
  elem_t result;
  ioopm_hash_table_remove(ht_ns, ioopm_charp_elem(merch.merchp->name), &result);
  ioopm_list_iterator_t* itr = ioopm_list_iterator_create(merch.merchp->shelflist->llist);
  while(ioopm_iterator_has_next(itr)) {
    elem_t key = ioopm_charp_elem(ioopm_iterator_current(itr).shelfp->loc);
    ioopm_hash_table_remove(ht_sn, key, &result);
    ioopm_iterator_next(itr);
  }
  ioopm_iterator_destroy(itr);

  free_merch(merch);

}
//TODO: Check for existing key in main
//brief: takes a merch and copies values(not list) over to original and then deletes merch_new
//original merch is reinserted into hashtable
void edit_merch(ioopm_hash_table_t *ht_ns, ioopm_hash_table_t *ht_sn,  elem_t merch_new, elem_t orig_key) {
  elem_t orig_merchp;
  ioopm_hash_table_remove(ht_ns, orig_key, &orig_merchp);
  orig_merchp.merchp->name = merch_new.merchp->name;
  orig_merchp.merchp->desc = merch_new.merchp->desc;
  orig_merchp.merchp->price = merch_new.merchp->price;
  ioopm_hash_table_insert(ht_ns, ioopm_charp_elem(orig_merchp.merchp->name), orig_merchp);
  free_merch(merch_new);
  /*
  elem_t orig_merch;
  ioopm_hash_table_lookup(ht_ns, orig_key, &orig_merch);
  *merch_new.merchp->shelflist = *orig_merch.merchp->shelflist;
  remove_merch(ht_ns, ht_sn, orig_merch);
  add_merch(ht_ns, ht_sn, merch_new);
  */
}

//Untested.
void show_stock(elem_t* merch) {
  if(merch->merchp->shelflist->qty > 0) {
    printf("%s - In stock in the following locations\n",merch->merchp->name);
    ioopm_list_iterator_t* itr = ioopm_list_iterator_create(merch->merchp->shelflist->llist);
    while(ioopm_iterator_has_next(itr)) {
      printf("%s:%d\n",ioopm_iterator_current(itr).shelfp->loc, ioopm_iterator_current(itr).shelfp->qty);
      ioopm_iterator_next(itr);
    }
    ioopm_iterator_destroy(itr);
  }
  else {
    puts("Not in stock");
  }
}

//Initiate linked list in shelf with empty shelf structs
void replenish_stock(ioopm_hash_table_t* htsn ,elem_t merch, elem_t shelf) {
  bool existing = false;
  ioopm_list_t* llist = merch.merchp->shelflist->llist;
  ioopm_list_iterator_t* itr = ioopm_list_iterator_create(llist);
  while(ioopm_iterator_has_next(itr)) {
    if (llist->eq_fun(ioopm_iterator_current(itr), shelf)) {
      ioopm_iterator_current(itr).shelfp->qty+=shelf.shelfp->qty;
      merch.merchp->shelflist->qty += shelf.shelfp->qty;
      existing = true;
    }
    ioopm_iterator_next(itr);
  }
  ioopm_iterator_destroy(itr);
  if (existing == false) {
    ioopm_linked_list_append(merch.merchp->shelflist->llist, shelf);
    merch.merchp->shelflist->qty += shelf.shelfp->qty;
    ioopm_hash_table_insert(htsn, ioopm_charp_elem(shelf.shelfp->loc), ioopm_merch_elem(merch.merchp));
  }
}

void create_cart(ioopm_hash_table_t* ht_carts) {
  cart_t* cartp = calloc(1,sizeof(cart_t));
  *cartp = (cart_t) {.total_cost = 0, .id = Cart_Number, .items=ioopm_hash_table_create(unsigned_int_hash_fun, elem_str_equiv, elem_int_equiv)};
  Cart_Number++;
  ioopm_hash_table_insert(ht_carts, ioopm_int_elem(cartp->id), ioopm_cart_elem(cartp));
}
//does not free elements in cart
void remove_cart(ioopm_hash_table_t* ht_carts , cart_t *cart) {
  /*ioopm_list_t* list = ioopm_hash_table_keys(cart->items);
  ioopm_list_iterator_t* itr = ioopm_list_iterator_create(list)
  while(ioopm_list_iterator_has_next(itr)) {

  } */
  elem_t removed;
  ioopm_hash_table_remove(ht_carts, ioopm_int_elem(cart->id), &removed);
  ioopm_hash_table_destroy(cart->items);
  free(cart);
}

static int total_qty_in_carts(ioopm_hash_table_t* ht_carts, elem_t item_name) {
  ioopm_list_t* allcarts = ioopm_hash_table_values(ht_carts);
  ioopm_list_iterator_t* itr = ioopm_list_iterator_create(allcarts);
  int sum = 0;
  while(ioopm_iterator_has_next(itr)) {
    elem_t result = ioopm_int_elem(0);
    ioopm_hash_table_lookup(ioopm_iterator_current(itr).cartp->items, item_name, &result);
    ioopm_iterator_next(itr);
    sum += result.i;
  }
  ioopm_iterator_destroy(itr);
  ioopm_linked_list_destroy(allcarts);
  return sum;
}
void add_to_cart(ioopm_hash_table_t* ht_carts, cart_t *cart, elem_t merch, int qty) {
  if (total_qty_in_carts(ht_carts, ioopm_charp_elem(merch.merchp->name)) + qty <= merch.merchp->shelflist->qty) {
    elem_t current_qty = ioopm_int_elem(0);
    ioopm_hash_table_lookup(cart->items, ioopm_charp_elem(merch.merchp->name), &current_qty);
    ioopm_hash_table_insert(cart->items, ioopm_charp_elem(merch.merchp->name), ioopm_int_elem(qty+current_qty.i));
    cart->total_cost += qty * (merch.merchp->price);
  }
  else {
    puts("Not enough items in stock");
  }
}
//Untested
void remove_from_cart(cart_t *cart, elem_t merch, int qty) {
    elem_t current_qty = ioopm_int_elem(0);
    ioopm_hash_table_lookup(cart->items, ioopm_charp_elem(merch.merchp->name), &current_qty);
    if (current_qty.i - qty >= 0) {
      ioopm_hash_table_insert(cart->items, ioopm_charp_elem(merch.merchp->name), ioopm_int_elem(current_qty.i - qty));
      cart->total_cost -= qty * (merch.merchp->price);
    }
    else {
      puts("Can't remove that many items from cart. Nothing changed.");
    }

}
void calc_cost(cart_t *cart) {
  printf("Total cost of cart %d is %d\n", cart->id, cart->total_cost);
}
//apply-to-all function
void checkout_cart_aux(elem_t name, elem_t* qty, void* ht_ns) {
  elem_t merch;
  ioopm_hash_table_lookup(ht_ns, name, &merch);

  ioopm_list_t* slist = merch.merchp->shelflist->llist;
  ioopm_list_iterator_t* itr = ioopm_list_iterator_create(slist);

  while(ioopm_iterator_has_next(itr)){
    if(ioopm_iterator_current(itr).shelfp->qty >= qty->i) {
      ioopm_iterator_current(itr).shelfp->qty -= qty->i;
      break;
    }
    else {
      ioopm_iterator_current(itr).shelfp->qty = 0;
      qty->i -= ioopm_iterator_current(itr).shelfp->qty;
      ioopm_iterator_next(itr);
    }
  }
  ioopm_iterator_destroy(itr);
}
//TODO: Set the apply function to the correct cart
void checkout_cart(ioopm_hash_table_t* ht_merch, ioopm_hash_table_t* ht_carts,  cart_t *cart) {
  elem_t elem_cart;
  if(ioopm_hash_table_lookup(ht_carts, ioopm_int_elem(cart->id), &elem_cart)){
  ioopm_hash_table_apply_to_all(cart->items, checkout_cart_aux, ht_merch);
  remove_cart(ht_carts, cart);
  }
  else {
    puts("No such cart in the system. Nothing changed.");
  }
}

