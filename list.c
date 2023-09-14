#include <stdlib.h>
#include <stdio.h>

# define DEFAULT_CAPACITY 8

typedef struct List {
  void** items;
  int capacity;
  int length;
} List;

List* List_create() {
  List* list = malloc(sizeof(List));
  list->items = malloc(DEFAULT_CAPACITY * sizeof(void*));
  list->capacity = DEFAULT_CAPACITY;
  list->length = 0;
  return list;
}

void* List_get(List* list, int i) {
  if(i < 0 || i >= list->length) return NULL;
  return *(list->items + i);
}

void List_expand(List* list) {
  int new_capacity = list->capacity * 2; // double the capacity
  list->capacity = new_capacity;
  list->items = realloc(list->items, new_capacity * sizeof(void*));
}

void List_append(List* list, void* item) {
  if(list->capacity == list->length) List_expand(list);
  *(list->items + list->length) = item;
  list->length++;
}

void* List_pop(List* list) {
  if(list->length == 0) return NULL;
  list->length--; // decrement the length
  void* popped_item = *(list->items + list->length);
  *(list->items + list->length) = NULL;
  return popped_item;
}

void List_set(List* list, void* value, int i) {
  if(i < 0 || i >= list->length) return;
  *(list->items + i) = value;
}

void List_free(List* list) {
  free(list->items);
  free(list);
}

int main() {
  List* list = List_create();

  printf("just initialized list!\n\n");
  printf("length: %d\n", list->length);
  printf("capacity: %d\n\n", list->capacity);

  int intNum = 95;
  List_append(list, &intNum);
  printf("appended int %d\n", intNum);

  float floatNum = 123.25;
  List_append(list, &floatNum);
  printf("appended float %.2f\n", floatNum);

  double doubleNum = 3223789.712374;
  List_append(list, &doubleNum);
  printf("appended double %lf\n\n", doubleNum);

  printf("length: %d\n", list->length);
  printf("capacity: %d\n\n", list->capacity);

  printf("element at index 0: %d\n", *((int *)List_get(list, 0)));
  printf("element at index 1: %.2f\n", *((float *)List_get(list, 1)));
  printf("element at index 2: %lf\n\n", *((double *)List_get(list, 2)));

  float newFloat = 50.30;
  List_set(list, &newFloat, 1);
  printf("updated element at index 1 to be %.2f\n", newFloat);

  void* poppedDouble = List_pop(list);
  printf("popped an item from the list: %lf\n\n", *((double *) poppedDouble));
  printf("length: %d\n", list->length);
  printf("capacity: %d\n\n", list->capacity);

  printf("element at index 0: %d\n", *((int *)List_get(list, 0)));
  printf("element at index 1: %.2f\n", *((float *)List_get(list, 1)));
  printf("element at index 2: %p\n\n", List_get(list, 2));

  for(int i = 0; i < 50; i++) {
    List_append(list, &i);
  }

  printf("appended 50 elements\n\n");

  printf("length: %d\n", list->length);
  printf("capacity: %d\n\n", list->capacity);

  List_free(list);
}
