#include "linked_list.h"
#include "iterator.h"
#include "common.h"
#include "CUnit/Basic.h"


int init_suite_ITERATOR()
{
  return 0;
}

int clean_suite_ITERATOR(void)
{
  return 0;
}

ioopm_list_t *generate_iter_list()
{
  ioopm_list_t *list = ioopm_linked_list_create(compare_int_elements);
  ioopm_linked_list_prepend(list, int_elem(100));
  ioopm_linked_list_prepend(list, int_elem(200));
  ioopm_linked_list_prepend(list, int_elem(300));
  return list;
}
void test_ITERATOR_HAS_NEXT()
{
  ioopm_list_t *list = ioopm_linked_list_create(compare_int_elements);
  ioopm_linked_list_prepend(list, int_elem(100));
  ioopm_iter_t *iterator = ioopm_list_iterator_t(list);
  CU_ASSERT(ioopm_iterator_has_next(iterator));
  ioopm_linked_list_append(list, int_elem(101));
  CU_ASSERT(ioopm_iterator_has_next(iterator));
  ioopm_linked_list_destroy(list);
  ioopm_iterator_destroy(iterator);
}

void test_ITERATOR_RESET()
{
  ioopm_list_t *list = generate_iter_list();
  ioopm_iter_t *iterator = ioopm_list_iterator_t(list);
  ioopm_iterator_reset(iterator);
  elem_t element = ioopm_iterator_next(iterator);
  CU_ASSERT(element.int_nr  == 200);
  ioopm_linked_list_destroy(list);
  ioopm_iterator_destroy(iterator);
}
void test_ITERATOR_CURRENT()
{
  ioopm_list_t *list =  generate_iter_list();
  ioopm_iter_t *iterator = ioopm_list_iterator_t(list);
  elem_t element = ioopm_iterator_current(iterator);
  CU_ASSERT_TRUE(element.int_nr == 300);
  ioopm_linked_list_destroy(list);
  ioopm_iterator_destroy(iterator);
}

void initIteratorSuite(CU_pSuite *pSuite_ITERATOR)
{
  *pSuite_ITERATOR = CU_add_suite(
      "this suite tests iterator functions",
      init_suite_ITERATOR,
      clean_suite_ITERATOR
    );
  CU_add_test(*pSuite_ITERATOR, "testing has_next", test_ITERATOR_HAS_NEXT);
  CU_add_test(*pSuite_ITERATOR, "testing current", test_ITERATOR_CURRENT);
  CU_add_test(*pSuite_ITERATOR, "testing reset", test_ITERATOR_RESET);
}


int main()
{
  CU_pSuite iterSuite = NULL;
  // see if CU 
  if (CUE_SUCCESS != CU_initialize_registry())
  {
    CU_get_error();
    return 1;
  }
  initIteratorSuite(&iterSuite);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}




