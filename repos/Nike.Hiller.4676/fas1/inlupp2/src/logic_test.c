#include <CUnit/Basic.h>
#include "common.h"
#include "logic.h"
#include "hash_functions.h"
#include "ui.h"
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
  add_merch(htns, NULL, merchp);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(htns, ioopm_charp_elem("Books")));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(htns, merchp));
  remove_merch(htns, merchp);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(htns, ioopm_charp_elem("Books")));
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(htns, merchp));
  ioopm_hash_table_destroy(htns);
}
void test_edit_merch(void)
{
  elem_t merchp = make_merch("Books", "Cheap books", 100);
  elem_t merchp2 = make_merch("Movies", "Good movies",100);
  ioopm_hash_table_t *htns = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  add_merch(htns, NULL, merchp);
  add_merch(htns, NULL, merchp2); 
  elem_t merchp3 = make_merch("Bookies", "Expensive books", 101);   
  edit_merch(htns, merchp3, ioopm_charp_elem("Books"));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(htns, ioopm_charp_elem("Books")));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(htns, ioopm_charp_elem("Bookies")));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(htns, merchp2));
  remove_merch(htns, merchp);
  remove_merch(htns, merchp2);
  ioopm_hash_table_destroy(htns);
}
void test_replenish_stock(void)
{
  elem_t merchp = make_merch("Books", "Cheap books", 100);
  elem_t merchp2 = make_merch("Movies", "Good movies",100);
  ioopm_hash_table_t *htns = ioopm_hash_table_create(merch_hash_fun, elem_str_equiv, elem_merch_equiv);
  add_merch(htns, NULL, merchp);
  add_merch(htns, NULL, merchp2); 
  elem_t newshelf = make_shelf("A25",0);
  elem_t replenish = make_shelf("A25", 100);
  replenish_stock(merchp, newshelf);
  replenish_stock(merchp, replenish);
  CU_ASSERT(ioopm_linked_list_get(merchp.merchp->shelflist->llist, 0).shelfp->qty == 100)
  remove_merch(htns, merchp);
  remove_merch(htns, merchp2);
  ioopm_hash_table_destroy(htns);
}



int main()
{
  CU_pSuite test_suite_ll = NULL;
  CU_pSuite test_suite_itr = NULL;
  
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();
  
  test_suite_ll = CU_add_suite("Test Suite Linked List", init_suite, clean_suite);
  if (NULL == test_suite_ll)
    {
      CU_cleanup_registry();
      return CU_get_error();
    } 

  if (
      (NULL == CU_add_test(test_suite_ll, "add_merch", test_add_merch))   ||
      (NULL == CU_add_test(test_suite_ll, "edit_merch", test_edit_merch))   ||      
      (NULL == CU_add_test(test_suite_ll, "replenish_stock", test_replenish_stock))   ||      
      (NULL == CU_add_test(test_suite_ll, "remove_merch", test_remove_merch))   
      // (NULL == CU_add_test(test_suite_ll, "ll_clear", test_ioopm_ll_clear))      
      
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  

  test_suite_itr = CU_add_suite("Test Suite Iterator", init_suite, clean_suite);
  if (NULL == test_suite_itr)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (
      (NULL == CU_add_test(test_suite_itr, "add_merch", test_add_merch))
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
