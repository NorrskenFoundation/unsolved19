#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "common.h"
#include "linked_list.h"
#define No_Buckets 17

//-----------------TESTS---------------------------
void test_ioopm_hash_table_is_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_string_elements, extract_int_hash_key);
  elem_t elem_1 = int_elem(10);
  elem_t elem_2= int_elem(11);
  elem_t elem_3= int_elem(12);
  elem_t string_1 = char_elem("nike");
  elem_t string_2 = char_elem("foo");
  elem_t string_3 = char_elem("Bonnie");
  ioopm_hash_table_insert(ht, elem_1, string_1);
  ioopm_hash_table_insert(ht, elem_2, string_2);
  ioopm_hash_table_insert(ht, elem_3, string_3);

  if (ioopm_hash_table_is_empty(ht) == false)
  {
    puts("ioopm_hash_table_is_empty works!\n");
  }
  else
  {
    puts("something is broken in ioopm_hash_table_is_empt!\n");
  }
  ioopm_hash_table_destroy(ht);
  return;
}


void test_ioopm_hash_table_remove_empty_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int_elements, extract_int_hash_key);
  elem_t elem_1 = int_elem(10);
  elem_t elem_2 = int_elem(11);
  elem_t elem_3 = int_elem(12);
  elem_t string_1 = char_elem("nike");
  elem_t string_2 = char_elem("foo");
  elem_t string_3 = char_elem("Bonnie");
  ioopm_hash_table_insert(ht, elem_1, string_1);
  ioopm_hash_table_insert(ht, elem_2, string_2);
  ioopm_hash_table_insert(ht, elem_3, string_3);


  ioopm_hash_table_remove(ht, elem_2);
  if (!ioopm_hash_table_lookup(ht, elem_2).success)
    {
      printf("ioopm_hash_table_remove_empty_key works!\n");
    }
  else
    {
      printf("ioopm_hash_table_remove_empty_key doesn't work!\n");
    }
  ioopm_hash_table_destroy(ht);
  return;
}
void test_ioopm_hash_table_remove_first()
{ 
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int_elements, extract_int_hash_key);
  elem_t elem_1 = int_elem(10);
  elem_t elem_2= int_elem(11);
  elem_t elem_3= int_elem(12);
  elem_t string_1 = char_elem("nike");
  elem_t string_2 = char_elem("foo");
  elem_t string_3 = char_elem("Bonnie");
  ioopm_hash_table_insert(ht, elem_1, string_1);
  ioopm_hash_table_insert(ht, elem_2, string_2);
  ioopm_hash_table_insert(ht, elem_3, string_3);

  if (ioopm_hash_table_lookup(ht, elem_1).success)
  {
    ioopm_hash_table_remove(ht, elem_1);
    
  }

  if (!ioopm_hash_table_lookup(ht, elem_1).success && ioopm_hash_table_lookup(ht, elem_2).success
     )
  {
    puts("ioopm_hash_table_remove_first works, we removed 10!\n");
    ioopm_hash_table_destroy(ht);
  }
  else
    {
  puts("somthings is wrong in ioopm_hash_table_remove_first!\n");
    }
}


void test_ioopm_hash_table_remove_middle()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int_elements, extract_int_hash_key);
  //elem_t elem_1 = int_elem(10);
  elem_t elem_2= int_elem(11);
  elem_t elem_3= int_elem(12);
  //elem_t string_1 = char_elem("nike");
  elem_t string_2 = char_elem("foo");
  elem_t string_3 = char_elem("Bonnie");
  //ioopm_hash_table_insert(ht, elem_1, string_1);
  ioopm_hash_table_insert(ht, elem_2, string_2);
  ioopm_hash_table_insert(ht, elem_3, string_3);



  if (ioopm_hash_table_lookup(ht, elem_2).success)
  {
    ioopm_hash_table_remove(ht, elem_2);
    
  }

  if (!ioopm_hash_table_lookup(ht, elem_2).success && ioopm_hash_table_lookup(ht, elem_3).success)
  {
    puts("ioopm_hash_table_remove_middle works, we removed 11!\n");
    ioopm_hash_table_destroy(ht);
    return;
  }
  puts("ioopm_hash_table_remove_middle doesn't works! \n");

  return;
}
void test_ioopm_hash_table_remove_last()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int_elements, extract_int_hash_key);
  elem_t elem_1 = int_elem(10);
  elem_t elem_2 = int_elem(11);
  elem_t elem_3 = int_elem(12);
  elem_t string_1 = char_elem("nike");
  elem_t string_2 = char_elem("foo");
  elem_t string_3 = char_elem("Bonnie");
  ioopm_hash_table_insert(ht, elem_1, string_1);
  ioopm_hash_table_insert(ht, elem_2, string_2);
  ioopm_hash_table_insert(ht, elem_3, string_3);



  if (ioopm_hash_table_lookup(ht, elem_3).success)
  {
    ioopm_hash_table_remove(ht, elem_3);
    
  }

  if (!ioopm_hash_table_lookup(ht, elem_3).success)
  {
    puts("ioopm_hash_table_remove_last works, we removed 12!\n");
    ioopm_hash_table_destroy(ht);
    return;
  }
  puts("ioopm_hash_table_remove_last doesn't work!");

  return;
}

void test_ioopm_hash_table_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int_elements, extract_int_hash_key);
  elem_t elem_1 = int_elem(10);
  elem_t elem_2 = int_elem(11);
  elem_t elem_3 = int_elem(12);
  elem_t string_1 = char_elem("nike");
  elem_t string_2 = char_elem("foo");
  elem_t string_3 = char_elem("Bonnie");
  ioopm_hash_table_insert(ht, elem_1, string_1);
  ioopm_hash_table_insert(ht, elem_2, string_2);
  ioopm_hash_table_insert(ht, elem_3, string_3);



  if (ioopm_hash_table_size(ht) == 3)
  {
    printf("ioopm_hash_table_size works!\n");
  }
  else
  {
    printf("something went wrong in ioopm_hash_table_size!\n");
  }
  ioopm_hash_table_destroy(ht);
  return;
}

void test_ioopm_hash_table_clear()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int_elements, extract_int_hash_key);
  elem_t elem_1 = int_elem(10);
  elem_t elem_2= int_elem(11);
  elem_t elem_3= int_elem(12);
  elem_t string_1 = char_elem("nike");
  elem_t string_2 = char_elem("foo");
  elem_t string_3 = char_elem("Bonnie");
  ioopm_hash_table_insert(ht, elem_1, string_1);
  ioopm_hash_table_insert(ht, elem_2, string_2);
  ioopm_hash_table_insert(ht, elem_3, string_3);
  
  ioopm_hash_table_clear(ht);

  if(ioopm_hash_table_is_empty(ht))
  {
    puts("iooom_hash_table_clear works!\n");
  }
  else
  {

    puts("something is wrong in iooom_hash_table_clear!\n");

  }
  ioopm_hash_table_destroy(ht);
  return;
}

bool predicate_1(elem_t key,elem_t value, void *extra)
{
  elem_t* param = extra;
  return key.int_nr == (*param).int_nr;
}

void test_ioopm_hash_table_has_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_dynamic(compare_int_elements, extract_int_hash_key, 0.75, No_Buckets);
  ioopm_hash_table_insert(ht, int_elem(1), char_elem("foo"));

  if (ioopm_hash_table_has_key(ht, predicate_1, int_elem(1)) == true && ioopm_hash_table_has_key(ht, predicate_1,int_elem(5)) == false)
  {
    puts("ioopm_hash_table_has_key works!\n");
  }
  else
  {
    puts("somthings is wrong in ioopm_hash_table_has_key!\n");
  }
  ioopm_hash_table_destroy(ht);
}

bool predicate_2(elem_t key,elem_t value, void *extra)
{
  elem_t* param = extra;
 
  return strcmp(value.string, (*param).string) == 0;
}

void test_ioopm_hash_table_has_value()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_string_elements, extract_int_hash_key);
  ioopm_hash_table_insert(ht, int_elem(1), char_elem("foo"));
  
  if (ioopm_hash_table_has_value(ht, predicate_2, char_elem("foo")))
  {
    puts("ioopm_hash_table_has_value works!\n");
  }
  else
  {
    puts("somthings is wrong in ioopm_hash_table_has_value!\n");
  }
  ioopm_hash_table_destroy(ht);
}


void test_ioopm_hash_table_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int_elements, extract_int_hash_key);
  elem_t elem_1 = int_elem(10);
  elem_t elem_2 = int_elem(11);
  elem_t elem_3 = int_elem(12);
  elem_t string_1 = char_elem("nike");
  elem_t string_2 = char_elem("foo");
  elem_t string_3 = char_elem("Bonnie");
  ioopm_hash_table_insert(ht, elem_1, string_1);
  ioopm_hash_table_insert(ht, elem_2, string_2);
  ioopm_hash_table_insert(ht, elem_3, string_3);
  

  if (ioopm_hash_table_has_key(ht, predicate_1, int_elem(10)) == true && ioopm_hash_table_has_key(ht, predicate_1,int_elem(11)) == true && ioopm_hash_table_has_key(ht, predicate_1,int_elem(12)) == true)
  {
    puts("ioopm_hash_table_all works!\n");
  }
  else
  {
    puts("somthings is wrong in ioopm_hash_table_all!\n");
  }
  ioopm_hash_table_destroy(ht);
}


void test_ioopm_hash_table_any()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int_elements, extract_int_hash_key);
  elem_t elem_1 = int_elem(10);
  elem_t elem_2 = int_elem(11);
  elem_t elem_3 = int_elem(12);
  elem_t string_1 = char_elem("nike");
  elem_t string_2 = char_elem("foo");
  elem_t string_3 = char_elem("Bonnie");
  ioopm_hash_table_insert(ht, elem_1, string_1);
  ioopm_hash_table_insert(ht, elem_2, string_2);
  ioopm_hash_table_insert(ht, elem_3, string_3);

  if (ioopm_hash_table_has_key(ht, predicate_1, int_elem(10)) == true && ioopm_hash_table_has_key(ht, predicate_1,int_elem(5)) == false)
  {
    puts("ioopm_hash_table_any works!\n");
  }
  else
  {
    puts("somthings is wrong in ioopm_hash_table_any!\n");
  }
  ioopm_hash_table_destroy(ht);
}

void apply_print_elem(elem_t key, elem_t value, void *extra)
{
  printf("The key is: %d The value is: %s\n", key.int_nr, value.string);
}  


void test_ioopm_hash_table_apply_to_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int_elements, extract_int_hash_key);
  
  elem_t elem_1 = int_elem(10);
  elem_t elem_2 = int_elem(11);
  elem_t elem_3 = int_elem(12);
  elem_t string_1 = char_elem("nike");
  elem_t string_2 = char_elem("foo");
  elem_t string_3 = char_elem("Bonnie");
  ioopm_hash_table_insert(ht, elem_1, string_1);
  ioopm_hash_table_insert(ht, elem_2, string_2);
  ioopm_hash_table_insert(ht, elem_3, string_3);

  ioopm_hash_table_apply_to_all(ht, apply_print_elem, NULL);
  printf("ioopm_hash_table_apply_to_all works!\n");

  ioopm_hash_table_destroy(ht);
}


bool test_ioopm_hash_table_keys()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int_elements, extract_int_hash_key);
  elem_t elem_1 = int_elem(10);
  //elem_t elem_2 = int_elem(11);
  //elem_t elem_3 = int_elem(12);
  //elem_t string_1 = char_elem("nike");
  elem_t string_2 = char_elem("foo");
  //elem_t string_3 = char_elem("Bonnie");
  ioopm_hash_table_insert(ht, elem_1, string_2);
  //ioopm_hash_table_insert(ht, elem_2, string_2);
  //ioopm_hash_table_insert(ht, elem_3, string_3);

  ioopm_list_t *keys = ioopm_hash_table_keys(ht);

  link_t *cursor = keys->first->next;

  while (cursor != NULL)
  {
    if (cursor->element.int_nr == 10)
    {
      printf("ioopm_hash_tabel_keys works and it has key %d!\n",elem_1.int_nr);
      ioopm_hash_table_destroy(ht);
      ioopm_linked_list_destroy(keys);
      return true;
    }
    cursor = cursor->next;
  }
  printf("ioopm_hash_tabel_keys doesnt works or there is no key!\n");
   ioopm_hash_table_destroy(ht);
   ioopm_linked_list_destroy(keys);
  return false;
}



bool test_ioopm_hash_table_values()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int_elements, extract_int_hash_key);
  elem_t elem_1 = int_elem(10);
  //elem_t elem_2= int_elem(11);
  //elem_t elem_3= int_elem(12);
  //elem_t elem_2 = int_elem(100);
  elem_t string_2 = char_elem("foo");
  //elem_t string_3 = char_elem("Bonnie");
  ioopm_hash_table_insert(ht, elem_1, string_2);
  //ioopm_hash_table_insert(ht, elem_2, string_2);
  //ioopm_hash_table_insert(ht, elem_3, string_3);


  ioopm_list_t *values = ioopm_hash_table_values(ht);

  link_t *cursor = values->first->next;

  while (cursor != NULL)
    {
      if (strcmp(cursor->element.string, string_2.string) == 0)
    {
      
      printf("ioopm_hash_tabel_value works and it has values %s!\n",string_2.string);
      ioopm_hash_table_destroy(ht);
      ioopm_linked_list_destroy(values);
      return true;
    }
        cursor = cursor->next;	

    }
   printf("ioopm_hash_tabel_value doesn't works or there is no value!\n");
   ioopm_hash_table_destroy(ht);
   ioopm_linked_list_destroy(values);
   return false;
   
   
}


int main ()
{
  test_ioopm_hash_table_is_empty();
  test_ioopm_hash_table_remove_empty_key();
  test_ioopm_hash_table_remove_first();
  test_ioopm_hash_table_remove_middle();
  test_ioopm_hash_table_remove_last();
  test_ioopm_hash_table_apply_to_all();
  test_ioopm_hash_table_any();
  test_ioopm_hash_table_all();
  test_ioopm_hash_table_keys();
  test_ioopm_hash_table_values();
  test_ioopm_hash_table_size();
  test_ioopm_hash_table_clear();
  test_ioopm_hash_table_has_key();
  test_ioopm_hash_table_has_value();

  return 0;
}
