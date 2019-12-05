#include "common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file common.c
 * @author Ali Hoseini & Nike Hiller
 * @date 26 oct 2019 
 * @brief common resources for linked list and hash table
 */


bool compare_int_elements(elem_t a, elem_t b)
{
  return (b.int_nr - a.int_nr) == 0;
}

bool compare_string_elements(elem_t a, elem_t b)
{
  return strcmp(a.string, b.string) == 0;
}

int compare_bool_elements(elem_t a, elem_t b)
{
  return a.bool_nr -  b.bool_nr;
}

int compare_float_elements(elem_t a, elem_t b)
{
  return a.float_nr - b.float_nr;
}


unsigned long hash_function(elem_t key)
{
  unsigned long result = 0;
  char *str = key.string;
  do
  {
    result = result * 31 + *str;
  }
  while (*++str != '\0');
  return result;
}

unsigned long extract_int_hash_key(elem_t key)
{
  unsigned long result = key.int_nr;
  return result;
}
