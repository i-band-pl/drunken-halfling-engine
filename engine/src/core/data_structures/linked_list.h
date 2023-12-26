#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"

typedef struct node {
  void* data;
  struct node* pNext;
} Node;

typedef struct {
  u32 size;
  Node* head;
} LinkedList;

DHAPI LinkedList* linked_list_create();
DHAPI void linked_list_push(LinkedList* list, void* data, size_t data_size);
DHAPI void* linked_list_get_at(LinkedList* list, int index);
DHAPI void* linked_list_pop();
DHAPI void linked_list_print(LinkedList* list);
DHAPI void linked_list_free();