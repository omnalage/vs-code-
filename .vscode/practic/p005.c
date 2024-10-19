#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Linked list node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to find the largest value of multiplication of integers of any two nodes
int largestMultiplication(struct Node* head) {
    int maxProduct = INT_MIN;
    struct Node* ptr1 = head;

    // Traverse through each node and find the maximum product
    while (ptr1 != NULL) {
        struct Node* ptr2 = ptr1->next;
        while (ptr2 != NULL) {
            int product = ptr1->data * ptr2->data;
            if (product > maxProduct) {
                maxProduct = product;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    return maxProduct;
}

// Function to free allocated memory of linked list
void freeLinkedList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        freeLinkedList(temp);
    }
}

int main() {
    // Example usage
    struct Node* head = newNode(5);
    head->next = newNode(3);
    head->next->next = newNode(-5);
    head->next->next->next = newNode(8);

    int result = largestMultiplication(head);
    printf("Largest value of multiplication of any two nodes: %d\n", result);

    // Free allocated memory
    freeLinkedList(head);

    return 0;
}
