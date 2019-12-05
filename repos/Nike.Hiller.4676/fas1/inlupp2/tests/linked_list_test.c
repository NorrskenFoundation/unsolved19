#include <string.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include "../src/linked_list.h"
#include "../src/iterator.h"
#include "../src/common.h"

typedef struct link link_t;
typedef struct list ioopm_list_t;

struct link 
{
  elem_t element;
  link_t *next;
};

struct list
{
  link_t *first;
  link_t *last;
  ioopm_eq_function eq_func;
  size_t list_length;
};

struct iterator
{
  link_t *current;
  ioopm_list_t *list;
};


typedef struct link link_t;
typedef struct list ioopm_list_t;


int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}

void test_ioopm_ll_create(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv);  
  CU_ASSERT_PTR_EQUAL(llist->first,llist->last);
  CU_ASSERT_PTR_EQUAL(llist->first->next, NULL);
  ioopm_linked_list_destroy(llist);
}


void test_ioopm_ll_size(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv); 
  CU_ASSERT_EQUAL(llist->list_length, ioopm_linked_list_size(llist));
  ioopm_linked_list_append(llist, int_elem(2));
  ioopm_linked_list_prepend(llist,int_elem(1));
  ioopm_linked_list_append(llist, int_elem(3));
  ioopm_linked_list_prepend(llist,int_elem(4));
  ioopm_linked_list_prepend(llist,int_elem(5));
  CU_ASSERT(ioopm_linked_list_size(llist) == 5);
  ioopm_linked_list_destroy(llist);
  
}


void test_ioopm_ll_clear(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv); 
  ioopm_linked_list_append(llist,int_elem(2));
  ioopm_linked_list_prepend(llist, int_elem(1));
  ioopm_linked_list_append(llist, int_elem(3));
  ioopm_linked_list_prepend(llist,int_elem(4));
  ioopm_linked_list_prepend(llist,int_elem(5));
  ioopm_linked_list_clear(llist);
  CU_ASSERT_EQUAL(llist->first->next, NULL);
  CU_ASSERT(ioopm_linked_list_is_empty(llist) == true);
  ioopm_linked_list_destroy(llist);
}


void test_ioopm_ll_insert(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_insert(llist, 0, int_elem(0));
  ioopm_linked_list_insert(llist, 1, int_elem(1));
  ioopm_linked_list_insert(llist, 2, int_elem(2));
  ioopm_linked_list_insert(llist, 3, int_elem(3));
  CU_ASSERT((llist->eq_func)(llist->first->next->element, int_elem(0)));
  CU_ASSERT((llist->eq_func)(llist->first->next->next->next->element, int_elem(2)));
  CU_ASSERT((llist->eq_func)(llist->last->element, int_elem(3)));
  ioopm_linked_list_destroy(llist);
}

void test_ioopm_ll_is_empty(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv);
  CU_ASSERT_EQUAL(true, ioopm_linked_list_is_empty(llist));
  ioopm_linked_list_append(llist, int_elem(2));
  CU_ASSERT_EQUAL(false, ioopm_linked_list_is_empty(llist));
  ioopm_linked_list_destroy(llist);
}

void test_ioopm_ll_app_prep(void)
{
  
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv); 
  ioopm_linked_list_append(llist,int_elem(4));
  ioopm_linked_list_prepend(llist,int_elem(3));
  ioopm_linked_list_append(llist,int_elem(5));
  ioopm_linked_list_prepend(llist,int_elem(2));
  ioopm_linked_list_prepend(llist,int_elem(1));
  CU_ASSERT_EQUAL(llist->first->next->element.i,1);
  CU_ASSERT_EQUAL(llist->first->next->next->element.i,2); 
  CU_ASSERT_EQUAL(llist->first->next->next->next->element.i,3);
  CU_ASSERT_EQUAL(llist->first->next->next->next->next->element.i,4);
  CU_ASSERT_EQUAL(llist->first->next->next->next->next->next->element.i,5);
  ioopm_linked_list_destroy(llist);
}

void test_ioopm_ll_get(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv);
  ioopm_linked_list_insert(llist, 0, int_elem(0));
  ioopm_linked_list_insert(llist, 1, int_elem(1));
  ioopm_linked_list_insert(llist, 2, int_elem(2));
  ioopm_linked_list_insert(llist, 3, int_elem(3));
  CU_ASSERT_EQUAL(llist->first->next->element.i, ioopm_linked_list_get(llist,0).i);
  CU_ASSERT_EQUAL(llist->last->element.i, ioopm_linked_list_get(llist,3).i);
  ioopm_linked_list_destroy(llist);
}

void test_ioopm_ll_contains(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv); 
  ioopm_linked_list_append(llist,int_elem(4));
  ioopm_linked_list_prepend(llist,int_elem(3));
  ioopm_linked_list_append(llist,int_elem(5));
  ioopm_linked_list_prepend(llist,int_elem(2));
  ioopm_linked_list_prepend(llist,int_elem(1));
  CU_ASSERT_TRUE(ioopm_linked_list_contains(llist, int_elem(1)));    
  CU_ASSERT_TRUE(ioopm_linked_list_contains(llist, int_elem(5)));
  CU_ASSERT_TRUE(ioopm_linked_list_contains(llist, int_elem(3)));
  CU_ASSERT_FALSE(ioopm_linked_list_contains(llist, int_elem(0)));
  CU_ASSERT_FALSE(ioopm_linked_list_contains(llist, int_elem(6)));
  ioopm_linked_list_destroy(llist);
}

void test_ioopm_ll_remove(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv); 
  ioopm_linked_list_append(llist,int_elem(4));
  ioopm_linked_list_prepend(llist,int_elem(3));
  ioopm_linked_list_append(llist,int_elem(5));
  ioopm_linked_list_prepend(llist,int_elem(2));
  ioopm_linked_list_prepend(llist,int_elem(1));
  CU_ASSERT_EQUAL(1,ioopm_linked_list_remove(llist,0).i);
  CU_ASSERT_EQUAL(5,ioopm_linked_list_remove(llist,3).i);

  //IndexOutOfBounds should remove linked_list[0]
  CU_ASSERT_EQUAL(2,ioopm_linked_list_remove(llist,10).i); 

  ioopm_linked_list_destroy(llist);
}

/*
void test_ioopm_ll_all(void)
{
  int div = 3;
  ioopm_list_t *llist = ioopm_linked_list_create(); 
  ioopm_linked_list_append(llist,15);
  ioopm_linked_list_prepend(llist,12);
  ioopm_linked_list_append(llist,9);
  ioopm_linked_list_prepend(llist,6);
  ioopm_linked_list_prepend(llist,3); 
  CU_ASSERT_TRUE(ioopm_linked_list_all(llist, divisible_by,(void*) &div));
  ioopm_linked_list_clear(llist);
  ioopm_linked_list_append(llist,15);
  ioopm_linked_list_prepend(llist,12);
  ioopm_linked_list_append(llist,2); //Not div by 3
  ioopm_linked_list_prepend(llist,6);
  ioopm_linked_list_prepend(llist,3);
  CU_ASSERT_FALSE(ioopm_linked_list_all(llist, divisible_by,(void*) &div));
  ioopm_linked_list_destroy(llist);
}

void test_ioopm_ll_any(void)
{
  int div = 3;
  ioopm_list_t *llist = ioopm_linked_list_create(); 
  ioopm_linked_list_append(llist,15);
  ioopm_linked_list_prepend(llist,12);
  ioopm_linked_list_append(llist,9);
  ioopm_linked_list_prepend(llist,6);
  ioopm_linked_list_prepend(llist,3); 
  CU_ASSERT_TRUE(ioopm_linked_list_all(llist, divisible_by,(void*) &div));
  ioopm_linked_list_clear(llist);
  ioopm_linked_list_append(llist,15);
  ioopm_linked_list_prepend(llist,12);
  ioopm_linked_list_append(llist,2); //Not div by 3
  ioopm_linked_list_prepend(llist,6);
  ioopm_linked_list_prepend(llist,3);
  CU_ASSERT_FALSE(ioopm_linked_list_all(llist, divisible_by,(void*) &div));
  ioopm_linked_list_destroy(llist);
}

void test_ioopm_ll_apply(void)
{
  int incr = 2;
  ioopm_list_t *llist = ioopm_linked_list_create(); 
  ioopm_linked_list_append(llist,4);
  ioopm_linked_list_prepend(llist,3);
  ioopm_linked_list_append(llist,5);
  ioopm_linked_list_prepend(llist,2);
  ioopm_linked_list_prepend(llist,1);
  ioopm_linked_apply_to_all(llist, add, (void*) &incr);
  CU_ASSERT_EQUAL(llist->first->next->element, 3);
  CU_ASSERT_EQUAL(llist->last->element, 7);
  ioopm_linked_list_destroy(llist);
}
*/

void test_ioopm_itr_create(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv); 
  ioopm_linked_list_append(llist,int_elem(4));
  ioopm_linked_list_prepend(llist,int_elem(3));
  ioopm_linked_list_append(llist,int_elem(5));
  ioopm_linked_list_prepend(llist,int_elem(2));
  ioopm_linked_list_prepend(llist,int_elem(1));
  ioopm_list_iterator_t *itr = ioopm_list_iterator_create(llist);
  CU_ASSERT_EQUAL(itr->list, llist);
  CU_ASSERT_EQUAL(itr->current, llist->first);
  ioopm_iterator_destroy(itr);
  ioopm_linked_list_destroy(llist);
  
}


void test_ioopm_itr_has_next(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv); 
  ioopm_linked_list_prepend(llist,int_elem(3));
  ioopm_linked_list_prepend(llist,int_elem(2));
  ioopm_linked_list_prepend(llist,int_elem(1));
  ioopm_list_iterator_t *itr = ioopm_list_iterator_create(llist);
  CU_ASSERT_TRUE(ioopm_iterator_has_next(itr));
  ioopm_iterator_next(itr);
  ioopm_iterator_next(itr);
  CU_ASSERT_TRUE(ioopm_iterator_has_next(itr));
  ioopm_iterator_next(itr);
  CU_ASSERT_FALSE(ioopm_iterator_has_next(itr));  
  ioopm_iterator_destroy(itr);
  ioopm_linked_list_destroy(llist);
  
}


void test_ioopm_itr_next(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv); 
  ioopm_linked_list_prepend(llist,int_elem(3));
  ioopm_linked_list_prepend(llist,int_elem(2));
  ioopm_linked_list_prepend(llist,int_elem(1));    
  ioopm_list_iterator_t *itr = ioopm_list_iterator_create(llist);
  CU_ASSERT_EQUAL(1, ioopm_iterator_next(itr).value.i);
  CU_ASSERT_EQUAL(2, ioopm_iterator_next(itr).value.i);
  CU_ASSERT_EQUAL(3, ioopm_iterator_next(itr).value.i);
  ioopm_iterator_destroy(itr);
  ioopm_linked_list_destroy(llist);
  
}


void test_ioopm_itr_reset(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv); 
  ioopm_linked_list_prepend(llist,int_elem(3));
  ioopm_linked_list_prepend(llist,int_elem(2));
  ioopm_linked_list_prepend(llist,int_elem(1));    
  ioopm_list_iterator_t *itr = ioopm_list_iterator_create(llist);
  ioopm_iterator_next(itr);
  ioopm_iterator_next(itr);
  ioopm_iterator_reset(itr);
  CU_ASSERT_EQUAL(itr->current->element.i,0);
  ioopm_iterator_destroy(itr);
  ioopm_linked_list_destroy(llist);
  
}

void test_ioopm_itr_current(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv); 
  ioopm_linked_list_prepend(llist,int_elem(3));
  ioopm_linked_list_prepend(llist,int_elem(2));
  ioopm_linked_list_prepend(llist,int_elem(1));    
  ioopm_list_iterator_t *itr = ioopm_list_iterator_create(llist);
  CU_ASSERT_EQUAL(1, ioopm_iterator_current(itr).i);
  ioopm_iterator_next(itr);
  CU_ASSERT_EQUAL(2, ioopm_iterator_current(itr).i);
  ioopm_iterator_next(itr);
  CU_ASSERT_EQUAL(3, ioopm_iterator_current(itr).i);
  ioopm_linked_list_destroy(llist);
  ioopm_iterator_destroy(itr);
}

void test_ioopm_itr_insert(void)
{
  ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv); 
  ioopm_linked_list_append(llist, int_elem(1));
  ioopm_linked_list_append(llist, int_elem(2));
  ioopm_linked_list_append(llist, int_elem(3));
  ioopm_list_iterator_t *itr = ioopm_list_iterator_create(llist);
  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(1)));
  ioopm_iterator_next(itr);

  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(2)));
  ioopm_iterator_insert(itr, int_elem(999));
  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(999)));

  ioopm_iterator_next(itr);
  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(2)));
  ioopm_iterator_next(itr);
  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(3)));

  ioopm_iterator_reset(itr);

  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(1)));
  ioopm_iterator_insert(itr, int_elem(998));
  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(998)));

  ioopm_iterator_next(itr);
  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(1)));
  ioopm_iterator_next(itr);
  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(999)));
  ioopm_iterator_next(itr);
  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(2)));
  ioopm_iterator_next(itr);
  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(3)));
  
  ioopm_iterator_destroy(itr);
  ioopm_linked_list_destroy(llist);
}


void test_ioopm_itr_remove(void)
{
 ioopm_list_t *llist = ioopm_linked_list_create(elem_int_equiv); 
  ioopm_linked_list_append(llist, int_elem(1));
  ioopm_linked_list_append(llist, int_elem(2));
  ioopm_linked_list_append(llist, int_elem(3));
  ioopm_list_iterator_t *itr = ioopm_list_iterator_create(llist);

  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(1)));
  ioopm_iterator_next(itr);

  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(2)));
  ioopm_iterator_remove(itr);
  CU_ASSERT((llist->eq_func)( ioopm_iterator_current(itr), int_elem(3)));
  ioopm_iterator_remove(itr);
  CU_ASSERT_FALSE(ioopm_iterator_has_next(itr));

  ioopm_iterator_destroy(itr);
  ioopm_linked_list_destroy(llist);
  
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
      (NULL == CU_add_test(test_suite_ll, "ll_create", test_ioopm_ll_create))       ||
      (NULL == CU_add_test(test_suite_ll, "ll_clear", test_ioopm_ll_clear))         ||
      (NULL == CU_add_test(test_suite_ll, "ll_size", test_ioopm_ll_size))           || 
      (NULL == CU_add_test(test_suite_ll, "ll_insert", test_ioopm_ll_insert))       ||
      (NULL == CU_add_test(test_suite_ll, "ll_is_empty", test_ioopm_ll_is_empty))   ||   
      (NULL == CU_add_test(test_suite_ll, "ll_app_prep", test_ioopm_ll_app_prep))   ||
      (NULL == CU_add_test(test_suite_ll, "ll_get", test_ioopm_ll_get))             || 
      (NULL == CU_add_test(test_suite_ll, "ll_contains", test_ioopm_ll_contains))   ||
      (NULL == CU_add_test(test_suite_ll, "ll_remove", test_ioopm_ll_remove))     //||
      //(NULL == CU_add_test(test_suite_ll, "ll_all", test_ioopm_ll_all))           || 
      //(NULL == CU_add_test(test_suite_ll, "ll_any", test_ioopm_ll_any))           ||
      //(NULL == CU_add_test(test_suite_ll, "ll_apply", test_ioopm_ll_apply))      

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
      (NULL == CU_add_test(test_suite_itr, "ll_iter_create", test_ioopm_itr_create))     ||
      (NULL == CU_add_test(test_suite_itr, "ll_iter_has_next", test_ioopm_itr_has_next)) ||
      (NULL == CU_add_test(test_suite_itr, "ll_iter_next", test_ioopm_itr_next))         ||
      (NULL == CU_add_test(test_suite_itr, "ll_iter_reset", test_ioopm_itr_reset))       ||
      (NULL == CU_add_test(test_suite_itr, "ll_iter_current", test_ioopm_itr_current))   ||  
      (NULL == CU_add_test(test_suite_itr, "ll_iter_insert", test_ioopm_itr_insert))     || 
      (NULL == CU_add_test(test_suite_itr, "ll_iter_remove", test_ioopm_itr_remove)) 
      
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
