#include "linked_list.h"
#include <stdlib.h>

struct list_node *new_node(size_t value) { 
    struct list_node *node = malloc(sizeof(struct list_node));
    node->next = NULL;
    node->value = value;
    return node;
}

void insert_at_head(struct linked_list *list, size_t value) {
    struct list_node *new_node_ptr = new_node(value);
    new_node_ptr->next = list->head;
    list->head = new_node_ptr;
}

void insert_at_tail(struct linked_list *list, size_t value) {
    if (list->head != NULL) {
        struct list_node *new_node_ptr = new_node(value);
        struct list_node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node_ptr;
    } else {
        struct list_node *new_node_ptr = new_node(value);
        list->head = new_node_ptr;
    }
}

size_t remove_from_head(struct linked_list *list) { 
    if (list->head == NULL) {
        return 0;
    }
    size_t value = list->head->value;
    struct list_node *node_to_remove = list->head;
    list->head = node_to_remove->next;
    free(node_to_remove);
    return value;
}

size_t remove_from_tail(struct linked_list *list) { 
    if (list->head == NULL) {
        return 0;
    }
    struct list_node *current = list->head;
    struct list_node *previous = NULL;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    size_t value = current->value;
    if (previous != NULL) {
        previous->next = NULL;
    }
    free(current);
    return value;
}

void free_list(struct linked_list list) {
    struct list_node *current = list.head;
    struct list_node *next_node = NULL;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

void dump_list(FILE *fp, struct linked_list list) {
    fprintf(fp, "[ ");
    for (struct list_node *current = list.head; current != NULL; current = current->next) {
        fprintf(fp, "%zu ", current->value);
    }
    fprintf(fp, "]\n");
}
