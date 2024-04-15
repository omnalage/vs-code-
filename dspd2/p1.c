#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void removeNegativeNodes(struct Node** ptr) {
    struct Node* lptr = *ptr;
    struct Node* prev = NULL;


    while (lptr != NULL) {
        if (lptr->data <= 0) {
            if (prev == NULL) {
                *ptr = lptr->next;
                free(lptr);
                lptr = *ptr;
            } else {
                prev->next = lptr->next;
                free(lptr);
                lptr = prev->next;
            }
        } else {
            prev = lptr;
            lptr = lptr->next;
        }
    }
}

void printList(struct Node* ptr) {
    struct Node* lptr = ptr;
    while (lptr != NULL) {
        printf("%d -> ", lptr->data);
        lptr = lptr->next;
    }
    printf("NULL\n");
}

void insertNode(struct Node** ptr, int data) {
    struct Node* nptr = (struct Node*)malloc(sizeof(struct Node));
    nptr->data = data;
    nptr->next = NULL;

    if (*ptr == NULL) {
        *ptr = nptr;
        return;
    }

    struct Node* lptr = *ptr;
    while (lptr->next != NULL) {
        lptr = lptr->next;
    }

    lptr->next = nptr;
}
void freeList(struct Node* ptr) {
    struct Node* lptr = ptr;
    struct Node* next;

    while (lptr != NULL) {
        next = lptr->next;
        free(lptr);
        lptr = next;
    }
}

int main() {
    struct Node* ptr1 = NULL;
    insertNode(&ptr1, 30);
    insertNode(&ptr1, -5);
    insertNode(&ptr1, -6);
    insertNode(&ptr1, 20);
    insertNode(&ptr1, -3);
    insertNode(&ptr1, 44);
    insertNode(&ptr1, 0);
    insertNode(&ptr1, 55);

    printf("case 1:\n Input: ");
    printList(ptr1);
    removeNegativeNodes(&ptr1);
    printf("Output: ");
    printList(ptr1);
    freeList(ptr1);

    struct Node*ptr2 = NULL;
    insertNode(&ptr2, -20);
    insertNode(&ptr2, -5);
    insertNode(&ptr2, -6);
    insertNode(&ptr2, 25);
    insertNode(&ptr2, 0);
    insertNode(&ptr2, 33);
    insertNode(&ptr2, -45);

    printf("case 2:\n  Input: ");
    printList(ptr2);
    removeNegativeNodes(&ptr2);
    printf("Output: ");
    printList(ptr2);
    freeList(ptr2);

    return 0;
}
