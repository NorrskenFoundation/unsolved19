#include <CUnit/Basic.h>
#include "../src/common.h"
#include "../src/logic.h"
#include "../src/hash_functions.h"
#include "../src/ui.h"
int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}


void test_add_merch(void)
{
  merch_t merch = {.name = "Books", .desc = "Cheap books", .shelflist=NULL, .price = 100};
  elem_t merchp = ioopm_merch_elem(&merch);
  merch_t merch2 = {.name = "Movies", .desc = "Good movies", .shelflist=NULL, .price = 100};
  elem_t merchp2 = ioopm_merch_elem(&merch2);
  ioopm_hash_table_t *htns = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  add_merch(htns, NULL, merchp);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(htns, ioopm_charp_elem("Books")));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(htns, merchp));
  add_merch(htns, NULL, merchp2);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(htns, ioopm_charp_elem("Movies")));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(htns, merchp2));
  add_merch(htns, NULL, merchp);
  CU_ASSERT(ioopm_hash_table_size(htns) == (size_t) 2);
  ioopm_hash_table_destroy(htns);

}

void test_remove_merch(void)
{

  //merch_t merch = {.name = "Books", .desc = "Cheap books", .shelflist=NULL, .price = 100};
  //elem_t merchp = ioopm_merch_elem(&merch);
  elem_t merchp = make_merch("Books", "Cheap books", 100);
  ioopm_hash_table_t *htns = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  ioopm_hash_table_t *htsn = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  add_merch(htns, NULL, merchp);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(htns, ioopm_charp_elem("Books")));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(htns, merchp));
  remove_merch(htns, htsn, merchp);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(htns, ioopm_charp_elem("Books")));
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(htns, merchp));
  ioopm_hash_table_destroy(htns);
  ioopm_hash_table_destroy(htsn);
}
void test_edit_merch(void)
{
  elem_t merchp = make_merch("Books", "Cheap books", 100);
  elem_t merchp2 = make_merch("Movies", "Good movies",100);
  ioopm_hash_table_t *htns = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  ioopm_hash_table_t *htsn = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  add_merch(htns, NULL, merchp);
  add_merch(htns, NULL, merchp2);
  elem_t merchp3 = make_merch("Bookies", "Expensive books", 101);
  edit_merch(htns, htsn, merchp3, ioopm_charp_elem("Books"));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(htns, ioopm_charp_elem("Books")));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(htns, ioopm_charp_elem("Bookies")));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(htns, merchp2));
  remove_merch(htns, htsn, merchp);
  remove_merch(htns, htsn, merchp2);
  ioopm_hash_table_destroy(htns);
  ioopm_hash_table_destroy(htsn);
}
void test_replenish_stock(void)
{
  elem_t merchp = make_merch("Books", "Cheap books", 100);
  elem_t merchp2 = make_merch("Movies", "Good movies",100);
  ioopm_hash_table_t *htns = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  ioopm_hash_table_t *htsn = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  add_merch(htns, NULL, merchp);
  add_merch(htns, NULL, merchp2);
  elem_t newshelf = make_shelf("A25",0);
  elem_t replenish = make_shelf("A25", 100);
  replenish_stock(htsn,merchp, newshelf);
  replenish_stock(htsn,merchp, replenish);
  CU_ASSERT(ioopm_linked_list_get(merchp.merchp->shelflist->llist, 0).shelfp->qty == 100);
  remove_merch(htns, htsn, merchp);
  remove_merch(htns, htsn, merchp2);
  clear_shelf(&newshelf);
  clear_shelf(&replenish);
  ioopm_hash_table_destroy(htns);
  ioopm_hash_table_destroy(htsn);
}

void test_create_cart(void)
{
  ioopm_hash_table_t* ht_carts = ioopm_hash_table_create(unsigned_int_hash_fun, elem_int_equiv, elem_cart_equiv);
  create_cart(ht_carts);
  create_cart(ht_carts);
  elem_t result;
  ioopm_hash_table_lookup(ht_carts,ioopm_int_elem(1), &result);
  cart_t* cart1 = result.cartp;
  ioopm_hash_table_lookup(ht_carts,ioopm_int_elem(2), &result);
  cart_t* cart2 = result.cartp;
  CU_ASSERT_FALSE(cart1 == cart2);
  CU_ASSERT_TRUE(elem_cart_equiv(ioopm_cart_elem(cart1), ioopm_cart_elem(cart1)));
  CU_ASSERT_FALSE(elem_cart_equiv(ioopm_cart_elem(cart1), ioopm_cart_elem(cart2)));
  CU_ASSERT(ioopm_cart_elem(cart1).cartp->id == 1);
  CU_ASSERT(ioopm_cart_elem(cart2).cartp->id == 2);
  remove_cart(ht_carts, cart1);
  remove_cart(ht_carts, cart2);
  ioopm_hash_table_destroy(ht_carts);

}

void test_add_to_cart(void){
  ioopm_hash_table_t* ht_carts = ioopm_hash_table_create(unsigned_int_hash_fun, elem_int_equiv, elem_cart_equiv);
  create_cart(ht_carts);
  create_cart(ht_carts);
  elem_t result;
  ioopm_hash_table_lookup(ht_carts,ioopm_int_elem(3), &result);
  cart_t* cart1 = result.cartp;
  ioopm_hash_table_lookup(ht_carts,ioopm_int_elem(4), &result); //Global cart counter increases, so key increases(4)
  cart_t* cart2 = result.cartp;

  elem_t merchp = make_merch("Books", "Cheap books", 100);
  elem_t merchp2 = make_merch("Movies", "Good movies",100);
  ioopm_hash_table_t *htns = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  ioopm_hash_table_t *htsn = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  add_merch(htns, NULL, merchp);
  add_merch(htns, NULL, merchp2);
  elem_t newshelf = make_shelf("A25",0);
  elem_t replenish = make_shelf("A25", 100);
  replenish_stock(htsn,merchp, newshelf);
  replenish_stock(htsn,merchp, replenish);
  elem_t cart_result;

  add_to_cart(ht_carts, cart1, merchp, 50);
  ioopm_hash_table_lookup(cart1->items, ioopm_charp_elem("Books"), &cart_result);
  CU_ASSERT(cart_result.i == 50);

  add_to_cart(ht_carts, cart1, merchp, 0);
  ioopm_hash_table_lookup(cart1->items, ioopm_charp_elem("Books"), &cart_result);
  CU_ASSERT(cart_result.i == 50);

  add_to_cart(ht_carts, cart2, merchp, 30);
  ioopm_hash_table_lookup(cart2->items, ioopm_charp_elem("Books"), &cart_result);
  CU_ASSERT(cart_result.i == 30);

  add_to_cart(ht_carts, cart2, merchp, 30); //Should not be done since we try to put 110 elem in cart, but have only 100
  ioopm_hash_table_lookup(cart2->items, ioopm_charp_elem("Books"), &cart_result);
  CU_ASSERT(cart_result.i == 30);


  remove_cart(ht_carts, cart1);
  remove_cart(ht_carts, cart2);
  ioopm_hash_table_destroy(ht_carts);

  remove_merch(htns, htsn, merchp);
  remove_merch(htns, htsn, merchp2);
  clear_shelf(&newshelf);
  clear_shelf(&replenish);
  ioopm_hash_table_destroy(htns);
  ioopm_hash_table_destroy(htsn);
}

void test_remove_from_cart(void) {
  ioopm_hash_table_t* ht_carts = ioopm_hash_table_create(unsigned_int_hash_fun, elem_int_equiv, elem_cart_equiv);
  create_cart(ht_carts);
  create_cart(ht_carts);
  elem_t result;
  ioopm_hash_table_lookup(ht_carts,ioopm_int_elem(5), &result);
  cart_t* cart1 = result.cartp;
  ioopm_hash_table_lookup(ht_carts,ioopm_int_elem(6), &result); //Global cart counter increases, so key increases(4)
  cart_t* cart2 = result.cartp;

  elem_t merchp = make_merch("Books", "Cheap books", 100);
  elem_t merchp2 = make_merch("Movies", "Good movies",100);
  ioopm_hash_table_t *htns = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  ioopm_hash_table_t *htsn = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  add_merch(htns, NULL, merchp);
  add_merch(htns, NULL, merchp2);
  elem_t newshelf = make_shelf("A25",0);
  elem_t replenish = make_shelf("A25", 100);
  replenish_stock(htsn,merchp, newshelf);
  replenish_stock(htsn,merchp, replenish);
  elem_t cart_result;

  add_to_cart(ht_carts, cart1, merchp, 50);
  add_to_cart(ht_carts, cart1, merchp, 0);
  add_to_cart(ht_carts, cart2, merchp, 30);
  add_to_cart(ht_carts, cart2, merchp, 30); //Should not be done since we try to put 110 elem in cart, but have only 100
  ioopm_hash_table_lookup(cart2->items, ioopm_charp_elem("Books"), &cart_result);

  remove_from_cart(cart1, merchp, 40);
  ioopm_hash_table_lookup(cart1->items, ioopm_charp_elem("Books"), &cart_result);
  CU_ASSERT(cart_result.i == 10);
  remove_from_cart(cart1, merchp, 40); //should change nothing
  remove_from_cart(cart2, merchp, 30);
  ioopm_hash_table_lookup(cart2->items, ioopm_charp_elem("Books"), &cart_result);
  CU_ASSERT(cart_result.i == 0);
  remove_cart(ht_carts, cart1);
  remove_cart(ht_carts, cart2);
  ioopm_hash_table_destroy(ht_carts);

  remove_merch(htns, htsn, merchp);
  remove_merch(htns, htsn, merchp2);
  clear_shelf(&newshelf);
  clear_shelf(&replenish);
  ioopm_hash_table_destroy(htns);
  ioopm_hash_table_destroy(htsn);
}

void test_checkout_cart(void) {
  ioopm_hash_table_t* ht_carts = ioopm_hash_table_create(unsigned_int_hash_fun, elem_int_equiv, elem_cart_equiv);
  create_cart(ht_carts);
  create_cart(ht_carts);
  elem_t result;
  ioopm_hash_table_lookup(ht_carts,ioopm_int_elem(7), &result);
  cart_t* cart1 = result.cartp;
  ioopm_hash_table_lookup(ht_carts,ioopm_int_elem(8), &result); //Global cart counter increases, so key increases(4)
  cart_t* cart2 = result.cartp;

  elem_t merchp = make_merch("Books", "Cheap books", 100);
  elem_t merchp2 = make_merch("Movies", "Good movies",100);
  ioopm_hash_table_t *htns = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  ioopm_hash_table_t *htsn = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  add_merch(htns, NULL, merchp);
  add_merch(htns, NULL, merchp2);
  elem_t newshelf = make_shelf("A25",0);
  elem_t replenish = make_shelf("A25", 100);
  replenish_stock(htsn,merchp, newshelf);
  replenish_stock(htsn,merchp, replenish);

  add_to_cart(ht_carts, cart1, merchp, 50);
  add_to_cart(ht_carts, cart1, merchp, 0);
  add_to_cart(ht_carts, cart2, merchp, 30);
  add_to_cart(ht_carts, cart2, merchp, 30); //Should not be done since we try to put 110 elem in cart, but have only 100
  CU_ASSERT(ioopm_hash_table_size(ht_carts) == 2);
  checkout_cart(htns, ht_carts, cart1);
  //ioopm_hash_table_lookup(cart1->items, ioopm_charp_elem("Books"), & cart_result);
  CU_ASSERT(ioopm_hash_table_size(ht_carts) == 1);
  //remove_cart(cart1);
  remove_cart(ht_carts, cart2);
  ioopm_hash_table_destroy(ht_carts);

  remove_merch(htns, htsn, merchp);
  remove_merch(htns, htsn, merchp2);
  clear_shelf(&newshelf);
  clear_shelf(&replenish);
  ioopm_hash_table_destroy(htns);
  ioopm_hash_table_destroy(htsn);
}

int main()
{
  CU_pSuite test_suite_logic = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  test_suite_logic = CU_add_suite("Test Suite Logic", init_suite, clean_suite);
  if (NULL == test_suite_logic)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (
      (NULL == CU_add_test(test_suite_logic, "add_merch", test_add_merch))   ||
      (NULL == CU_add_test(test_suite_logic, "edit_merch", test_edit_merch))   ||
      (NULL == CU_add_test(test_suite_logic, "replenish_stock", test_replenish_stock))   ||
      (NULL == CU_add_test(test_suite_logic, "remove_merch", test_remove_merch))   ||
      (NULL == CU_add_test(test_suite_logic, "create_cart", test_create_cart))      ||
      (NULL == CU_add_test(test_suite_logic, "add_to_cart", test_add_to_cart)) ||
      (NULL == CU_add_test(test_suite_logic, "remove_from_cart", test_remove_from_cart)) ||
      (NULL == CU_add_test(test_suite_logic, "checkout_cart", test_checkout_cart))
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }


  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
