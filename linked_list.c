#include "linked_list.h"
#include <stdlib.h>

struct list_node *new_node(size_t value) {
    struct list_node *node = malloc(sizeof(struct list_node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

void insert_at_head(struct linked_list *list, size_t value) {
    struct list_node *node = new_node(value);
    node->next = list->head;
    list->head = node;
}

void insert_at_tail(struct linked_list *list, size_t value) {
    struct list_node *node = new_node(value);
    if (list->head == NULL) {
        list->head = node;
        return;
    }
    
    struct list_node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
}

size_t remove_from_head(struct linked_list *list) {
    if (list->head == NULL) {
        return 0;
    }
    
    struct list_node *temp = list->head;
    size_t value = temp->value;
    list->head = list->head->next;
    free(temp);
    return value;
}

size_t remove_from_tail(struct linked_list *list) {
    if (list->head == NULL) {
        return 0;
    }
    
    if (list->head->next == NULL) {
        size_t value = list->head->value;
        free(list->head);
        list->head = NULL;
        return value;
    }
    
    struct list_node *current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    
    size_t value = current->next->value;
    free(current->next);
    current->next = NULL;
    return value;
}

void free_list(struct linked_list *list) {
    struct list_node *current = list->head;
    while (current != NULL) {
        struct list_node *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

// Utility function remains unchanged
void dump_list(FILE *fp, struct linked_list list) {
    fprintf(fp, "[ ");
    for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
        fprintf(fp, "%zu ", cur->value);
    }
    fprintf(fp, "]\n");
}
