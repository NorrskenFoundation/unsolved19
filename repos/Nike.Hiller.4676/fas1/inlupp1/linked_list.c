#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "linked_list.h"
#include "iterator.h"
#include "common.h"

 /**
 * @file linked_list.c
 * @author Ali Hoseini & Nike Hiller
 * @date 26 oct 2019 
 * @brief Simple linked list with dummy nodes.
 */

struct found_extra
{
  int element;
  bool found;
};


ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function func)
{
  
  ioopm_list_t *new_list = calloc(1, sizeof(ioopm_list_t));
  if (new_list)
    {
      new_list->eq_func = func;
      new_list->first = calloc(1, sizeof(link_t));
      new_list->last = new_list->first;
    }

  return new_list;
}

link_t *link_new(elem_t element, link_t *next)
{
  link_t *result = calloc(1,sizeof(struct list));

  if (result)
    {
      result->element = element;
      result->next = next;
    }
  free(next);
  return result;
}


void ioopm_linked_list_destroy(ioopm_list_t *list)
{
  link_t *cursor = list->first;
  while(cursor !=NULL)
    {
      link_t *tmp = cursor;
      cursor = cursor->next;
      free(tmp);
    }
  free(list);
  return;

}



void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t value)
{

  link_t *link = link_new(value, NULL);
  if (list->first->next == NULL)
    {
      list->first->next = link;
      list->last = link;
    }
  else
    {
      link->next = list->first->next;
      list->first->next = link;
    }
}

void ioopm_linked_list_append(ioopm_list_t *list, elem_t value)
{

  link_t *link = link_new(value, NULL);
  if (list->first == list->last)
    {
      list->first->next = link;
      list->last = link;
    }
  else
    {
      list->last->next = link;
      list->last = link;
    }
}


size_t ioopm_linked_list_size(ioopm_list_t *list)
{
  size_t size = 0;
  link_t *cursor = list->first->next;
  while (cursor != NULL)
    {
      ++size;
      cursor = cursor->next;
    }

  return size;
}


void ioopm_linked_list_insert(ioopm_list_t *list, int index, elem_t value)
{

  int length =  ioopm_linked_list_size(list);
  if (index == 0)
    {
      ioopm_linked_list_prepend(list, value);
    }
  else if (index == length)
    {
      ioopm_linked_list_append(list, value);
    }
  else
    {
      link_t *link = link_new(value, NULL);
      link_t *cursor = list->first;
      for (int i = 0; i <= index; ++i)
	{
	  if (i == (index - 1))
	    {
	      link->next = cursor->next;
	      cursor->next = link;
	    }
	}
    }

}


link_t *list_inner_find_previous(link_t *link, int index)
{
  link_t *cursor = link;

  for (int i = 0; i < index; ++i)
    {
      cursor = cursor->next;
    }

  return cursor;
}

elem_t ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
  int length = ioopm_linked_list_size(list);
  if(index > length-1)
    {
      elem_t wrong_index;
      // fix me -1
      wrong_index.int_nr = -1;
      return wrong_index;
    }
  link_t *cursor = list->first;
  if (index == 0)
    {
      list->first = cursor->next;
      elem_t value = cursor->element;
      free(cursor);
      return value;
    }
  else if (index == length-1)
    {
      link_t *link = list->first;
      link_t *prev = list_inner_find_previous(link, index);
      link_t *tmp = prev->next;
      list->last = prev;
      elem_t value = tmp->element;
      prev->next = NULL;
      free(tmp);
      return value;
    }
  else
    {
      link_t *link = list->first;
      link_t *prev = list_inner_find_previous(link, index);
      link_t *tmp = prev;
      elem_t value = tmp->element;
      prev->next = prev->next->next;
      free(tmp);
      return value;
    }
}


elem_t ioopm_linked_list_get(ioopm_list_t *list, int index)
{
  assert(index >= 0 && index < ioopm_linked_list_size(list));
  link_t *cursor = list->first->next;

  for (int i = 0; i < index; ++i)
    {
      cursor = cursor->next;
    }

  return cursor->element;
}

bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element)
{

  for(link_t *cursor = list->first; cursor; cursor = cursor->next){
    if(list->eq_func(cursor->element, element))
      return true;
  }
  return false;
}


bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
  if(ioopm_linked_list_size(list) < 1)
    {
      return true;
    }
  return false;
}


void ioopm_linked_list_clear(ioopm_list_t *list)
{
  while(ioopm_linked_list_size(list))
    {
      ioopm_linked_list_remove(list,0);
    }
}



bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_char_predicate prop, void *extra)
{
  bool result = true;
  for (link_t *cursor = list->first; cursor; cursor = cursor->next)
    {
      result = result && prop(cursor->element, extra);

    }
  return result;
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_char_predicate prop, void *extra)
{
  bool result = false;
  for (link_t *cursor = list->first; cursor; cursor = cursor->next)
    {
      result = !result && prop(cursor->element, extra);

    }
  return result;

}


void apply_change_element(elem_t element, void *extra)
{
  element.int_nr = element.int_nr +100;
}
void apply_print(elem_t element, void *extra)
{
  printf("The element changed to = %d\n", element.int_nr);
}  




void ioopm_linked_apply_to_all(ioopm_list_t *list, ioopm_apply_char_function fun, void *extra)
{
  for (link_t *cursor = list->first; cursor; cursor = cursor->next)
    {
      fun(cursor->element, extra);
    }
}

