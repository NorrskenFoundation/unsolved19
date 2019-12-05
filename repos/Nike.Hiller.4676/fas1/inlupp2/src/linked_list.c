#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
#include "iterator.h"
#include "common.h"

/*
 * @file linked_list.c
 * @author Jonathan Lindroth, Ludwig Ridderstolpe
 * @date 10 Oct 2019
 * @brief Simple linked list with O(1) access to first and last element.
 *        This file also contains an implementation of an iterator.
 *
 */

/*
 * REFACTOR: 
 * Linked list to be formulated with iterators instead
 * Iterator removed to be expressed with pointer to pointer logic
 */

/////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// LINKED LIST
///
/////////////////////////////////////////////////////////////////////////////////////////////////////

static link_t* link_create(elem_t element, link_t *next)
{
  link_t *result = calloc(1,sizeof(link_t));
  if (result != NULL)
    {
      result->element = element;
      result->next = next;
    }
  return result;
}


static link_t *list_inner_find_previous(link_t *link, int index)
{
  link_t *cursor = link;
  for (int i = 0; i < index; ++i)
    {
      cursor = cursor->next;
    }
  return cursor;
}


static int list_inner_adjust_index(int index, int upper_bound)
{
  if (index > upper_bound || index < 0)
    {
      return 0;
    }
  return index;
}


bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
  return (list->list_length == 0);
}


ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function eq_fun)
{
  ioopm_list_t *result = calloc(1,sizeof(ioopm_list_t));
  if (result)
    {
      result->first = result->last = calloc(1, sizeof(struct link)); //Construct sentinel link
      result -> eq_fun = eq_fun;
    }
  return result;
}


void ioopm_linked_list_insert(ioopm_list_t *list, int index, elem_t element)
{
  int list_size = ioopm_linked_list_size(list);
  int valid_index = list_inner_adjust_index(index, list_size);
  if (index == list_size)
    { 
    list->last->next = link_create(element, NULL);
    list->last = list->last->next;
    }
  else
    {
      link_t *prev = list_inner_find_previous(list->first, valid_index);
      prev->next = link_create(element, prev->next);
    }
  list->list_length ++;
}


void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t element)
{
  ioopm_linked_list_insert(list, 0, element);
}


void ioopm_linked_list_append(ioopm_list_t *list, elem_t value)
{
  link_t *new_element = calloc(1, sizeof(link_t));
  new_element->element = value;
  new_element->next = NULL;
  (list->last)->next = new_element;
  (list->last) = new_element;
  list->list_length += 1;
}

size_t ioopm_linked_list_size(ioopm_list_t *list)
{
  return list->list_length;
}


elem_t ioopm_linked_list_get(ioopm_list_t *list, int index)
{
  int valid_index = list_inner_adjust_index(index, ioopm_linked_list_size(list));
  link_t *prev = list_inner_find_previous(list->first, valid_index);  
  return prev->next->element;
}


bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element)
{
  link_t *cursor = list->first;
  for (size_t i = 0; i < ioopm_linked_list_size(list); i++)
    {
      cursor = cursor->next;
      if ((list->eq_fun)(cursor->element, element) == 1)
        {
          return true;
        }
    }
  return false;
}

elem_t ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
  int valid_index = list_inner_adjust_index(index, ioopm_linked_list_size(list));
  link_t *prev = list_inner_find_previous(list->first, valid_index);
  link_t *tmp = prev->next;
  elem_t value_removed = tmp->element;
  prev->next = prev->next->next; 
  free(tmp);
  list->list_length --;
  return value_removed;
}


void ioopm_linked_list_clear(ioopm_list_t *list)
{
  while (ioopm_linked_list_size(list))
    {
      ioopm_linked_list_remove(list, 0);
    }
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
  while(list->list_length > 0)
    {
      ioopm_linked_list_remove(list, 0);
    }
  free(list->first); 
  free(list);
}


bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_predicate prop, void *extra)
{
  bool result = true;
  for (link_t *cursor = list->first->next; cursor; cursor = cursor->next)
     {
       result = result && prop (cursor->element, cursor->element, extra);
     }
  return result;
}


bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_predicate prop, void *extra)
{
  bool result = false;
  for (link_t *cursor = list->first->next; cursor; cursor = cursor->next)
     {
       result = result || prop (cursor->element, cursor->element, extra);
     }
  return result;
}


void ioopm_linked_apply_to_all(ioopm_list_t *list, ioopm_apply_function fun, void *extra)
{
  for (link_t *cursor = list->first->next; cursor; cursor = cursor->next)
     {
       fun(cursor->element, &(cursor->element), extra);
     }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// ITERATORS
///
/////////////////////////////////////////////////////////////////////////////////////////////////////


ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *list)
{
  ioopm_list_iterator_t *result = calloc(1,sizeof(struct iterator));
  result->current = list->first;
  result->list = list; 
  return result;
}


bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter)
{
  return iter->current->next != NULL;
}


option_t ioopm_iterator_next(ioopm_list_iterator_t *iter)
{
  if (ioopm_iterator_has_next(iter))
    {
      iter->current = iter->current->next;
      option_t next = Success(iter->current->element); 
      return next;
    }
  else
    {
      return Failure();
    }
}


void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
{
  iter->current = iter->list->first;  
}


elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter)
{
  return iter->current->next->element;
}


void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
  free(iter);
}


/// FIX: Pointer to pointer logic
option_t ioopm_iterator_remove(ioopm_list_iterator_t *iter)
{
  if (ioopm_iterator_has_next(iter))
    {
      link_t *to_remove = iter->current->next;
      elem_t removed = to_remove -> element;
      iter->current->next = to_remove->next; 
      free(to_remove); 
      iter->list->list_length -= 1;  
      return Success(removed);
    }
  else
    {
      return Failure();
    }
}

/// FIX: Pointer to pointer logic
void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t element)
{
  
  link_t *new = calloc(1, sizeof(struct link));
  new->element = element;
  new->next = iter->current->next;
  iter->current->next = new;
  iter->list->list_length += 1;   
}
