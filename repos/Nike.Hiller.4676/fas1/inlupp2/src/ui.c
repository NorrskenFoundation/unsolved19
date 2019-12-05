#include "ui.h"
#include "utils.h"
#include "logic.h"

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


void print_menu() {
  printf("[A] Add merch\n[L] List merch\n[R] Remove merch\n[E] Edit merch\n[S] Show stock\n[P] Replenish\n[C] Create cart\n[M] Remove cart\n[D] Add to cart\n[O] Calculate cost\n[T] Checkout\n[U] Remove from cart\n[Q] Quit\n");
}


char ask_question_menu() {
  print_menu();

  char *input = ask_question_string("what do you want to do?");
  char choice = toupper(input[0]);
  return choice;
}

void event_loop(ioopm_hash_table_t *htns, ioopm_hash_table_t *htsn, ioopm_hash_table_t *cart_ht)
{
  char choice = ask_question_menu();

  while(choice != 'Q')
    {
      if (choice == 'A') //add merch
        {
          char *name = ask_question_string("what is the name of you merch?");
          char *desc = ask_question_string("describe your merch?");
          int price = ask_question_int("what is the price of your item?");
          elem_t new_merch = make_merch(name, desc, price);
          add_merch(htns, htsn, new_merch);
          choice = ask_question_menu();
        }
      else if (choice == 'L') //list merch
        {
          list_merch(htns);
          choice = ask_question_menu();
        }
      else if (choice == 'R') //remove merch
        {
          char *rm_merch = ask_question_string("what merch do you want to remove?");
          elem_t merch;
          if (!ioopm_hash_table_lookup(htns, ioopm_charp_elem(rm_merch), &merch))
            {
              puts("merch does not exits");
            }
          else
            {
              remove_merch(htns, htsn, merch);
            }
          choice = ask_question_menu();
        }
      else if (choice == 'E') //edit merch
        {
          char *merch_name = ask_question_string("what merch do you want to edit?");
          elem_t merch;
          if(!ioopm_hash_table_lookup(htns, ioopm_charp_elem(merch_name), &merch))
            {
              puts("merch does not exists");
            }
          else
            {
              char *name = ask_question_string("what is the new name of you merch?");
              char *desc = ask_question_string("describe your merch?");
              int price = ask_question_int("what is the price of your item?");
              elem_t new_merch = make_merch(name, desc, price);
              elem_t result;
              if(ioopm_hash_table_lookup(htns, ioopm_charp_elem(name), &result))
                {
                  puts("changing name to exisiting merch is not allowed");
                }
              else
                {
                  edit_merch(htns, htsn, new_merch, ioopm_charp_elem(merch.merchp->name));
                }
              choice = ask_question_menu();
            }
        }
      else if (choice == 'S') //show stock
        //todo, the qnt is 0 when start so get segfault
        //when should we add quantity to stock?
        {
          char *name = ask_question_string("what merch do you want to show?");
          elem_t merch;
          if(!ioopm_hash_table_lookup(htns, ioopm_charp_elem(name), &merch))
            {
              puts("merch does not exist");
            }
          else
            {
              show_stock(&merch);
              choice = ask_question_menu();
            }
        }
      else if (choice == 'P') //replenish
        //todo how do we get the shelf?
        //get segfault on line 106 in logic
        //how do I get the merch from the name?
        {
          char *name = ask_question_string("what merch do you want to increase the stock for?");
          elem_t merch;
          if(!ioopm_hash_table_lookup(htns, ioopm_charp_elem(name), &merch))
            {
              puts("the merch does not exist");
            }
          else
            {
              char *loc = ask_question_string("what storage location to you wish to replenish on?");
              int qty = ask_question_int("how many items do you wish to add to shelf?");
              elem_t shelf = make_shelf(loc, qty);
              replenish_stock(htsn, merch, shelf);
            }
          choice = ask_question_menu();
        }
      else if (choice == 'C') //create cart
        {
          create_cart(cart_ht);
          printf("Cart created, ID = %d \n", get_cart_number() - 1);
          choice = ask_question_menu();
        }
      else if (choice == 'M') //remove cart
        {
          int cart_id = ask_question_int("what cart do you want to remove?");
          elem_t cart;
          if(ioopm_hash_table_lookup(cart_ht, ioopm_int_elem(cart_id), &cart)) {
            remove_cart(cart_ht, cart.cartp);   
          }
          else {
            puts("The cart does not exist");
          }
          choice = ask_question_menu();
        }
      else if (choice == 'D') //add to cart
        {
          elem_t merch;
          elem_t cart;
          char *name = ask_question_string("what merch do you want to add to cart?");
          int cart_id = ask_question_int("what cart do you want to add to?");
          if(!ioopm_hash_table_lookup(htns, ioopm_charp_elem(name), &merch)) {
            puts("This merch does not exist in warehouse");   
          }
          else if(!ioopm_hash_table_lookup(cart_ht, ioopm_int_elem(cart_id), &cart)) {
            puts("The cart does not exist in the warehouse");
          }
          else {
            int qty = ask_question_int("how many items do you want to add?");
            add_to_cart(cart_ht, cart.cartp, merch, qty);
          }
          choice = ask_question_menu();
        }
      else if (choice == 'U') //add to cart
        {
          elem_t merch;
          elem_t cart;
          char *name = ask_question_string("what merch do you want to remove from cart?");
          int cart_id = ask_question_int("what cart do you want to remove from?");
          if(!ioopm_hash_table_lookup(htns, ioopm_charp_elem(name), &merch)) {
            puts("This merch does not exist in warehouse");   
          }
          else if(!ioopm_hash_table_lookup(cart_ht, ioopm_int_elem(cart_id), &cart)) {
            puts("The cart does not exist in the warehouse");
          }
          else {
            int qty = ask_question_int("how many items do you want to remove?");
            remove_from_cart(cart.cartp, merch, qty);
          }
          choice = ask_question_menu();
        }
      else if (choice == 'O') //Calculate cost
        {
          elem_t cart;
          int cart_id = ask_question_int("what cart do you want to check cost for?");
          if(!ioopm_hash_table_lookup(cart_ht, ioopm_int_elem(cart_id), &cart)) {
            puts("This cart does not exist in the warehouse");
          }
          else {
            calc_cost(cart.cartp);
          }
          choice = ask_question_menu();
        }
      else if (choice == 'T') //Checkout
        {
          elem_t cart;
          int cart_id = ask_question_int("what cart do you want to checkout?");
          if(!ioopm_hash_table_lookup(cart_ht, ioopm_int_elem(cart_id), &cart)) {
            puts("This cart does not exist in the warehouse");
          }
          else {
            checkout_cart(htns, cart_ht, cart.cartp);
          }
          
          choice = ask_question_menu();
        }
      else {
        puts("not valid input, try again");
        choice = ask_question_menu();
      }
    }
}

