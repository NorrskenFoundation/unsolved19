#include <stdlib.h>
#include <stdio.h>
#include "common.h"

/*
 * @file hash_functions.c
 * @author Jonathan Lindroth, Ludwig Ridderstolpe
 * @date 03 Oct 2019
 * @brief Hash functions that primarily extracts primitive datatypes of the elem_t union and converts to unsigned long.
 */

int merch_hash_fun(elem_t key){
  int result = 0;
  char *str = key.charp;
  do
    {
      result = result * 31 + *str;
    }
  while (*++str != '\0');
  return result;  
}

int str_hash_fun(elem_t key)
{
  int result = 0;
  char *str = key.charp;
  do
    {
      result = result * 31 + *str;
    }
  while (*++str != '\0');
  return result;
}


int unsigned_int_hash_fun(elem_t key)
{
  return (int) key.u;
}


int bool_hash_fun(elem_t key)
{
  return (int) key.b;
  
}


int float_hash_fun(elem_t key)
{
  return (int)(key.f);
}

