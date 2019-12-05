#include "linked_list.h"
#include "CUnit/Basic.h"
#include "common.h"

int init_suite_LIST()
{
  return 0;
}

int clean_suite_LIST(void)
{
  return 0;
}

ioopm_list_t *generate_list()
{
  ioopm_list_t *list = ioopm_linked_list_create(compare_int_elements);
  ioopm_linked_list_insert(list, 0, int_elem(100));
  ioopm_linked_list_insert(list, 1, int_elem(200));
  ioopm_linked_list_insert(list, 2, int_elem(300));

  return list;

}


void test_LIST_CREATE()
{
  ioopm_list_t *new_list = ioopm_linked_list_create(compare_int_elements);
  CU_ASSERT(new_list != NULL);
  ioopm_linked_list_destroy(new_list);
}

void test_LIST_GET()
{
 ioopm_list_t *list = generate_list();
  elem_t elem_test1 = ioopm_linked_list_get(list, 0);
  CU_ASSERT_TRUE(elem_test1.int_nr == 100);
  elem_t elem_test2 = ioopm_linked_list_get(list, 1);
  CU_ASSERT_TRUE(elem_test2.int_nr == 200);
  elem_t elem_test3 = ioopm_linked_list_get(list, 2);
  CU_ASSERT_TRUE(elem_test3.int_nr == 300);
  ioopm_linked_list_destroy(list);
}


void test_LIST_CONTAINS()
{
 ioopm_list_t *list = generate_list();
 CU_ASSERT_TRUE(ioopm_linked_list_contains(list, int_elem(200)));
 ioopm_linked_list_destroy(list);
}


void test_LIST_APPEND()
{
 ioopm_list_t *list = generate_list();
 ioopm_linked_list_append(list, int_elem(400));
 elem_t value = ioopm_linked_list_get(list,3);
  size_t size  = ioopm_linked_list_size(list);
 CU_ASSERT_TRUE(value.int_nr  == 400);
 CU_ASSERT_TRUE(size == 4);
  ioopm_linked_list_destroy(list);
}

void test_LIST_PREPEND()
{
 ioopm_list_t *list = generate_list();
 ioopm_linked_list_prepend(list, int_elem(50));
 elem_t value = ioopm_linked_list_get(list,0);
  size_t size  = ioopm_linked_list_size(list);
 CU_ASSERT_TRUE(value.int_nr  == 50);
 CU_ASSERT_TRUE(size == 4);
 ioopm_linked_list_destroy(list);
}

void test_LIST_INSERT()
{
  ioopm_list_t *list = generate_list();
  ioopm_linked_list_insert(list, 0, int_elem(500));
  ioopm_linked_list_insert(list, 4, int_elem(700));
  elem_t value_1 = ioopm_linked_list_get(list, 0);
  elem_t value_2 = ioopm_linked_list_get(list, 4);
  size_t size  = ioopm_linked_list_size(list);
  CU_ASSERT_TRUE(value_1.int_nr == 500);
  CU_ASSERT_TRUE(value_2.int_nr == 700);
  CU_ASSERT_TRUE(size == 5);
  ioopm_linked_list_destroy(list);
}


void test_LIST_REMOVE()
{
  ioopm_list_t *list = generate_list();
  elem_t value = ioopm_linked_list_remove(list, 2);
  size_t size  = ioopm_linked_list_size(list);
  CU_ASSERT_TRUE(value.int_nr == 300);
  CU_ASSERT_TRUE(size == 2);
  ioopm_linked_list_destroy(list);
}

void test_LIST_IS_EMPTY()
{
  ioopm_list_t *list = generate_list();
  ioopm_linked_list_clear(list);
  CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));
  ioopm_linked_list_destroy(list);
}

void test_LIST_CLEAR()
{
  ioopm_list_t *list = generate_list();
  ioopm_linked_list_clear(list);
  CU_ASSERT(ioopm_linked_list_is_empty(list) == true);
  ioopm_linked_list_destroy(list);
}


void initListSuite(CU_pSuite *pSuite_LIST)
{
  *pSuite_LIST = CU_add_suite(
      "this suite tests list functions",
      init_suite_LIST,
      clean_suite_LIST
    );
  CU_add_test(*pSuite_LIST, "testing create list", test_LIST_CREATE);
  CU_add_test(*pSuite_LIST, "testing list get", test_LIST_GET);
  CU_add_test(*pSuite_LIST, "testing list contains", test_LIST_CONTAINS);
  CU_add_test(*pSuite_LIST, "testing list append and size", test_LIST_APPEND);
  CU_add_test(*pSuite_LIST, "testing list prepend", test_LIST_PREPEND);
  CU_add_test(*pSuite_LIST, "testing list insert", test_LIST_INSERT);
  CU_add_test(*pSuite_LIST, "testing list remove", test_LIST_REMOVE);
  CU_add_test(*pSuite_LIST, "testing list empty", test_LIST_IS_EMPTY);
  CU_add_test(*pSuite_LIST, "testing list clear", test_LIST_CLEAR);
}


int main()
{
  CU_pSuite listSuite = NULL;
  // see if CU 
  if (CUE_SUCCESS != CU_initialize_registry())
  {
    CU_get_error();
    return 1;
  }
  initListSuite(&listSuite);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

