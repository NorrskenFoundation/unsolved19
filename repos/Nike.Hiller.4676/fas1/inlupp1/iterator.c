#include "iterator.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
#include "common.h"

/**
 * @file iterator.c
 * @author Ali Hoseini & Nike Hiller
 * @date 26 oct 2019 
 * @brief iterator functions
 */


ioopm_iter_t *ioopm_list_iterator_t(ioopm_list_t *list)
{
  ioopm_iter_t *iter = calloc(1, sizeof(ioopm_iter_t));
  iter->current = list->first;
  iter->list = list;
  return iter;
}

bool ioopm_iterator_has_next(ioopm_iter_t *iter)
{
  return (iter->current->next != NULL);
}

elem_t ioopm_iterator_next(ioopm_iter_t *iter)
{
  if (ioopm_iterator_has_next(iter))
    {
      iter->current = iter->current->next;
      return iter->current->element;
    }
  return iter->current->element;
}


void ioopm_iterator_reset(ioopm_iter_t *iter)
{
  iter->current = iter->list->first->next;
}

elem_t ioopm_iterator_current(ioopm_iter_t  *iter)
{
  return iter->current->next->element;

}


void ioopm_iterator_destroy(ioopm_iter_t *iter)
{
  free(iter);
}

