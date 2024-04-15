#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 8

typedef struct node {
    int size;
    int mark;
    struct node* links[3]; // Array to hold links
} Node;

typedef struct root {
    Node* next;
} Root;

Node* heap[HEAP_SIZE]; // Global array to hold heap nodes

Node* get_new_node(int size) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->size = size;
    temp->mark = 0;
    for (int i = 0; i < 3; i++) {
        temp->links[i] = NULL;
    }
    return temp;
}

void initialize() {
    heap[0] = get_new_node(5);
    heap[1] = get_new_node(1);
    heap[2] = get_new_node(2);
    heap[3] = get_new_node(9);
    heap[4] = get_new_node(10);
    heap[5] = get_new_node(7);
    heap[6] = get_new_node(8);
    heap[7] = get_new_node(3);

    // Establishing connections
    heap[0]->links[0] = heap[1];
    heap[1]->links[0] = heap[2];
    heap[1]->links[1] = heap[3];
    heap[1]->links[2] = heap[4];
    heap[5]->links[0] = heap[1];
    heap[5]->links[1] = heap[6];
    heap[6]->links[0] = heap[3];
    heap[7]->links[0] = heap[6];
    heap[7]->links[1] = heap[4];
}

void print_node(Node* node) {
    if (node == NULL) {
        return;
    }
    printf("Node size = %d", node->size);
    for (int i = 0; i < 3; i++) {
        if (node->links[i] != NULL) {
            printf("-[");
            print_node(node->links[i]);
            printf("]");
        }
    }
}

void print_heap() {
    for (int i = 0; i < HEAP_SIZE; i++) {
        if (heap[i] != NULL) {
            print_node(heap[i]);
            printf("\n");
        }
    }
}

void mark_node(Node* ptr) {
    if (ptr == NULL || ptr->mark == 1) {
        return;
    }
    ptr->mark = 1;
    for (int i = 0; i < 3; i++) {
        mark_node(ptr->links[i]);
    }
}

void mark(Root* value) {
    if (value != NULL && value->next != NULL) {
        mark_node(value->next);
    }
}

void sweep() {
    for (int i = 0; i < HEAP_SIZE; i++) {
        if (heap[i] != NULL && heap[i]->mark == 0) {
            free(heap[i]);
            heap[i] = NULL;
        }
    }
}

void garbage_collector(Root* r1, Root* r2) {
    printf("Mark phase started.......\n");
    mark(r1);
    mark(r2);
    printf("Marking done\n");
    printf("Sweep phase started.......\n");
    sweep();
}

int main() {
    printf("This is the Simulation for mark sweep garbage collector\n");
    printf("Key to navigate the printed table: - indicates connection and [] indicate all the elements connected to the element\n");
    printf("the full heap is: \n");
    initialize();
    print_heap();
    printf("-----------------\n");

    // Initialize roots
    Root* root1 = (Root*)malloc(sizeof(Root));
    root1->next = heap[0];
    Root* root2 = (Root*)malloc(sizeof(Root));
    root2->next = heap[1];

    printf("Heap connected to the roots is: \n");
    printf("root1->");
    print_node(root1->next);
    printf("\nroot2->");
    print_node(root2->next);
    printf("\n-----------------\n");

    garbage_collector(root1, root2);

    printf("the garbage collector was called, let us see the full heap now\n");
    print_heap();

    // Free roots
    free(root1);
    free(root2);

    return 0;
}