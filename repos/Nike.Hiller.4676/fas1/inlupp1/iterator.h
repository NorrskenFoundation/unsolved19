#ifndef __ITERATOR_H__
#define __ITERATOR_H__
#include <stdbool.h>
#include "common.h"
#include "linked_list.h"

/**
 * @file iterator.h
 * @author Ali Hoseini & Nike Hiller
 * @date 26 oct 2019 
 * @brief Simple iterator for linked list.
 */



struct iter
{
  link_t *current;
  ioopm_list_t *list;
};

typedef struct iter ioopm_iter_t;

ioopm_iter_t *ioopm_list_iterator_t(ioopm_list_t *list);
/// @brief Checks if there are more elements to iterate over
/// @param iter the iterator
/// @return true if
/// PRE: none empty list
bool ioopm_iterator_has_next(ioopm_iter_t *iter);

/// @brief Step the iterator forward one step
/// @param iter the iterator
/// @return the next element if it exist, else return current elemnt
elem_t ioopm_iterator_next(ioopm_iter_t *iter);

/// NOTE: REMOVE IS OPTIONAL TO IMPLEMENT 
/// @brief Remove the current element from the underlying list
/// @param iter the iterator
/// @return the removed element
elem_t ioopm_iterator_remove(ioopm_iter_t *iter);

/// NOTE: INSERT IS OPTIONAL TO IMPLEMENT 
/// @brief Insert a new element elem_to the underlying list making the current element it's next
/// @param iter the iterator
/// @param element the element to be inserted
void ioopm_iterator_insert(ioopm_iter_t *iter, elem_t element);

/// @brief Reposition the iterator at the start of the underlying list
/// @param iter the iterator
void ioopm_iterator_reset(ioopm_iter_t *iter);

/// @brief Return the current element from the underlying list
/// @param iter the iterator
/// @return the current element
elem_t ioopm_iterator_current(ioopm_iter_t *iter);

/// @brief Destroy the iterator and return its resources
/// @param iter the iterator
void ioopm_iterator_destroy(ioopm_iter_t *iter);

#endif
