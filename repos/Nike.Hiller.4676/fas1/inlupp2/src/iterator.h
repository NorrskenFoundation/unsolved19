#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <stdbool.h>
#include "common.h"

/*
 * @file iterator.h
 * @author Jonathan Lindroth, Ludwig Ridderstolpe
 * @date 10 Oct 2019
 * @brief Simple iterator
 *
 */


typedef struct iterator ioopm_list_iterator_t;

/// @brief Create an iterator for a given list
/// @param the list to be iterated over
/// @return an iteration positioned at the start of list
ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *list);

/// @brief Checks if there are more elements to iterate over
/// @param iter the iterator
/// @return true if
bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter);

/// @brief Step the iterator forward one ste
/// @param iter the iterator
/// @return the next element, false otherwise
option_t ioopm_iterator_next(ioopm_list_iterator_t *iter);

/// @brief Remove the current element from the underlying list
/// @param iter the iterator
/// @return the removed element, false otherwise
option_t ioopm_iterator_remove(ioopm_list_iterator_t *iter);

/// @brief Insert a new element into the underlying list making the current element it's next
/// @param iter the iterator
/// @param element the element to be inserted
void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t element);

/// @brief Reposition the iterator at the start of the underlying list
/// @param iter the iterator
void ioopm_iterator_reset(ioopm_list_iterator_t *iter);

/// @brief Return the current element from the underlying list
/// @param iter the iterator
/// @return the current element
elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter);

/// @brief Destroy the iterator and return its resources
/// @param iter the iterator
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter);

#endif
