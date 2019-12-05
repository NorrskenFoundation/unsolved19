#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "hash_table.h"
#include "linked_list.h"

#define GROW_FACTOR 2
#define DEFAULT_TABLE_SIZE 16
#define DEFAULT_LOAD_FACTOR_LIMIT 0.75

typedef struct entry entry_t;

struct entry
{
  elem_t key;
  elem_t value;
  entry_t *next;
};

struct hash_table
{
  size_t size;
  size_t no_buckets;
  double load_factor_limit;
  entry_t **buckets;
  ioopm_hash_function hash_fun;
  ioopm_eq_function key_eq;
  ioopm_eq_function val_eq;
};

static int get_bucket(int hash, size_t no_buckets)
{
  return ((hash % no_buckets + no_buckets) % no_buckets);
}

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
  entry_t *entry = malloc(sizeof(entry_t));
  *entry = (entry_t) {.key = key, .value = value, .next = next};
  return entry;
}

static entry_t **find_cur_pp(ioopm_hash_table_t *ht, elem_t key)
{
  int hash = ht->hash_fun(key);
  entry_t **cur_pp = &ht->buckets[get_bucket(hash, ht->no_buckets)];

  while (*cur_pp != NULL
	 && !ht->key_eq((*cur_pp)->key, key))
    cur_pp = &(*cur_pp)->next;

  return cur_pp;
}

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash_fun, ioopm_eq_function key_eq, ioopm_eq_function val_eq)
{
  return ioopm_hash_table_create_advanced(hash_fun, key_eq, val_eq, DEFAULT_TABLE_SIZE, DEFAULT_LOAD_FACTOR_LIMIT);
}

static entry_t **create_bucket_array(size_t no_buckets)
{
  return calloc(no_buckets, sizeof(entry_t*));
}

ioopm_hash_table_t *ioopm_hash_table_create_advanced(ioopm_hash_function hash_fun, ioopm_eq_function key_eq, ioopm_eq_function val_eq, size_t no_buckets, double load_factor_limit)
{
  ioopm_hash_table_t *result = malloc(sizeof(ioopm_hash_table_t));
  result->buckets = create_bucket_array(no_buckets);
  result->size = 0;
  result->hash_fun = hash_fun;
  result->key_eq = key_eq;
  result->val_eq = val_eq;
  result->no_buckets = no_buckets;
  result->load_factor_limit = load_factor_limit;

  return result;
}

static void insert_entries(ioopm_hash_table_t *ht, entry_t **old, size_t old_size)
{
  for (size_t i = 0; i < old_size; ++i) {
    entry_t *entry = old[i];

    while (entry != NULL) {
      entry_t *next = entry->next;
      int hash = ht->hash_fun(entry->key);

      entry_t **cur_pp = &ht->buckets[get_bucket(hash, ht->no_buckets)];

      entry->next = *cur_pp;
      *cur_pp = entry;

      entry = next;
    }
  }
}

static void resize_if_too_full(ioopm_hash_table_t *ht)
{
  double load_factor = (double) ht->size / (double) ht->no_buckets;

  if (load_factor < ht->load_factor_limit)
    return;

  entry_t **old = ht->buckets;
  size_t old_no_buckets = ht->no_buckets;

  ht->no_buckets = GROW_FACTOR * ht->no_buckets;
  ht->buckets = create_bucket_array(ht->no_buckets);

  insert_entries(ht, old, old_no_buckets);

  free(old);
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
  entry_t **cur_pp = find_cur_pp(ht, key);

  if (*cur_pp != NULL) {
    (*cur_pp)->value = value;
  } else {
    *cur_pp = entry_create(key, value, *cur_pp);
    ht->size += 1;
    resize_if_too_full(ht);
  }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{
  entry_t **cur_pp = find_cur_pp(ht, key);

  if (*cur_pp != NULL) {
    *result = (*cur_pp)->value;
    return 1;
  }
  return 0;
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{
  entry_t **cur_pp = find_cur_pp(ht, key);
  entry_t *cur = *cur_pp;

  if (cur != NULL) {
    *result = cur->value;
    *cur_pp = cur->next;
    free(cur);

    ht->size -= 1;
    return 1;
  }
  return 0;
}

static void free_entry_list_iterative(entry_t *entry)
{
  while (entry != NULL) {
    entry_t *next = entry->next;
    free(entry);
    entry = next;
  }
}

//static void free_entry_list_recursive(entry_t *entry)
//{
//  if (entry != NULL) {
//    entry_t *next = entry->next;
//    free(entry);
//    free_entry_list_recursive(next);
//  }
//}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  for (size_t i = 0; i < ht->no_buckets; ++i)
    free_entry_list_iterative(ht->buckets[i]);

  free(ht->buckets);
  free(ht);
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  return ht->size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  return ht->size == 0;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for (size_t i = 0; i < ht->no_buckets; ++i) {
    free_entry_list_iterative(ht->buckets[i]);
    ht->buckets[i] = NULL;
  }

  ht->size = 0;
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  ioopm_list_t *list = ioopm_linked_list_create(ht->key_eq);

  for (size_t i = 0; i < ht->no_buckets; ++i) {
    entry_t *entry = ht->buckets[i];

    while (entry != NULL) {
      ioopm_linked_list_append(list, entry->key);
      
      entry = entry->next;
    }
  }

  return list;
}

ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  ioopm_list_t *list = ioopm_linked_list_create(ht->val_eq);

  for (size_t i = 0; i < ht->no_buckets; ++i) {
    entry_t *entry = ht->buckets[i];

    while (entry != NULL) {
      ioopm_linked_list_append(list, entry->value);
      
      entry = entry->next;
    }
  }

  return list;
}

struct eq_to {
  ioopm_eq_function eq;
  elem_t val;
};

static bool key_eq(elem_t key, elem_t value, struct eq_to *args)
{
  return args->eq(args->val, key);
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
  struct eq_to args = {.eq = ht->key_eq, .val = key};
  return ioopm_hash_table_any(ht, (ioopm_predicate) key_eq, &args);
}

static bool val_eq(elem_t key, elem_t value, struct eq_to *args)
{
  return args->eq(args->val, value);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
  struct eq_to args = {.eq = ht->key_eq, .val = value};
  return ioopm_hash_table_any(ht, (ioopm_predicate) val_eq, &args);
}

static bool entry_list_any(entry_t *entry, ioopm_predicate pred, void *args)
{
  while (entry != NULL) {
    if (pred(entry->key, entry->value, args))
      return true;

    entry = entry->next;
  }

  return false;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *args)
{
  for (size_t i = 0; i < ht->no_buckets; ++i)
    if (entry_list_any(ht->buckets[i], pred, args))
      return true;
    
  return false;
}

static bool entry_list_all(entry_t *entry, ioopm_predicate pred, void *args)
{
  while (entry != NULL) {
    if (!pred(entry->key, entry->value, args))
      return false;

    entry = entry->next;
  }

  return true;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *args)
{
  for (size_t i = 0; i < ht->no_buckets; ++i)
    if (!entry_list_all(ht->buckets[i], pred, args))
      return false;
    
  return true;
}

static void entry_list_apply(entry_t *entry, ioopm_apply_function apply_fun, void *args)
{
  while (entry != NULL) {
    apply_fun(entry->key, &entry->value, args);
    entry = entry->next;
  }
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *args)
{
  for (size_t i = 0; i < ht->no_buckets; ++i)
    entry_list_apply(ht->buckets[i], apply_fun, args);
}

int ioopm_string_knr_hash(elem_t str)
{
  unsigned long result = 0;
  do
    {
      result = result * 31 + *str.charp;
    }
  while (*++str.charp != '\0');
  return result;
}
