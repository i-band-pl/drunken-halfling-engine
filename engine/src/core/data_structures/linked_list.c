#include "linked_list.h"

LinkedList* linked_list_create() {
  LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
  list->size = 0;
  list->head = NULL;
  return list;
}
void linked_list_push(LinkedList* list, void* data, size_t data_size) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = malloc(data_size);
  newNode->pNext = list->head;

  newNode->data = data;
  list->head = newNode;
}

void* linked_list_get_at(LinkedList* list, int index) {
  return NULL;
  /*
  u32 i = 0;
  Node* current = list->head;
  while (current != NULL) {
  }
  */
}

void* linked_list_pop() {
  return NULL;
}

void linked_list_print(LinkedList* list) {
  Node* current = list->head;
  while (current != NULL) {
    printf("%d\n", *(int*)current->data);
    current = current->pNext;
  }
}

void linked_list_free() {
}