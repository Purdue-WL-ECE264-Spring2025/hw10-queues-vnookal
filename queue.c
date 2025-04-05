#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
    size_t serialized_state = serialize(state);
    insert_at_tail(&q->data, serialized_state);
}

struct game_state dequeue(struct queue *q) {
    size_t serialized_state = remove_from_head(&q->data);
    return deserialize(serialized_state);
}

int number_of_moves(struct game_state start) {
    struct queue q = { .data.head = NULL };
    struct linked_list visited = { .head = NULL };
    
    enqueue(&q, start);
    
    while (q.data.head != NULL) {
        struct game_state current = dequeue(&q);
        size_t current_id = serialize(current);
        
        int is_visited = 0;
        for (struct list_node *node = visited.head; node != NULL; node = node->next) {
            if (node->value == current_id) {
                is_visited = 1;
                break;
            }
        }
        
        if (!is_visited) {
            insert_at_head(&visited, current_id);
            
            int is_solved = 1;
            int expected_value = 1;
            
            for (int row = 0; row < 4 && is_solved; row++) {
                for (int col = 0; col < 4 && is_solved; col++) {
                    if (row == 3 && col == 3) {
                        if (current.tiles[row][col] != 0) {
                            is_solved = 0;
                        }
                    } 
                    else {
                        if (current.tiles[row][col] != expected_value) {
                            is_solved = 0;
                        }
                        expected_value++;
                    }
                }
            }
            
            if (is_solved) {
                free_list(visited);
                return current.num_steps;
            }
            
            struct game_state new_state;
            
            if (current.empty_row > 0) {
                new_state = current;
                move_down(&new_state);
                enqueue(&q, new_state);
            }
            
            if (current.empty_row < 3) {
                new_state = current;
                move_up(&new_state);
                enqueue(&q, new_state);
            }
            
            if (current.empty_col > 0) {
                new_state = current;
                move_right(&new_state);
                enqueue(&q, new_state);
            }
            
            if (current.empty_col < 3) {
                new_state = current;
                move_left(&new_state);
                enqueue(&q, new_state);
            }
        }
    }
    
    free_list(visited);
    visited.head = NULL;
    return -1;
}
