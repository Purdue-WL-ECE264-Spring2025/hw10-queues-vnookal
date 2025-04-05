#include "linked_list.h"
#include <stdlib.h>

struct list_node *new_node(size_t value) {
    struct list_node *new = malloc(sizeof(struct list_node));
    if (new == NULL) return NULL;
    
    new->value = value;
    new->next = NULL;
    return new;
}

void insert_at_head(struct linked_list *list, size_t value) {
    struct list_node *new = new_node(value);
    new->next = list->head;
    list->head = new;
}

void insert_at_tail(struct linked_list *list, size_t value) {
    struct list_node *new = new_node(value);
    
    if (list->head == NULL) {
        list->head = new;
        return;
    }
    
    struct list_node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new;
}

size_t remove_from_head(struct linked_list *list) {
    if (list->head == NULL) return 0;
    
    struct list_node *to_remove = list->head;
    size_t value = to_remove->value;
    
    list->head = to_remove->next;
    free(to_remove);
    
    return value;
}

size_t remove_from_tail(struct linked_list *list) {
    if (list->head == NULL) return 0;
    
    // Single node case
    if (list->head->next == NULL) {
        size_t value = list->head->value;
        free(list->head);
        list->head = NULL;
        return value;
    }
    
    struct list_node *prev = NULL;
    struct list_node *current = list->head;
    
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    
    size_t value = current->value;
    prev->next = NULL;
    free(current);
    
    return value;
}

void free_list(struct linked_list list) {
    struct list_node *current = list.head;
    
    while (current != NULL) {
        struct list_node *next = current->next;
        free(current);
        current = next;
    }
}

// Utility function remains unchanged
void dump_list(FILE *fp, struct linked_list list) {
    fprintf(fp, "[ ");
    for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
        fprintf(fp, "%zu ", cur->value);
    }
    fprintf(fp, "]\n");
}
