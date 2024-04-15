#include <stdio.h>
#include <stdlib.h>


struct Node_tag {
    int data;
    struct Node_tag* next;
};

void rearrangeNodes(struct Node_tag** head) 
{
    struct Node_tag* negHead = NULL;
    struct Node_tag* zeroHead = NULL;
    struct Node_tag* posHead = NULL;
    
    struct Node_tag* lptr = *head;

    while (lptr != NULL) {
        struct Node_tag* nextNode = lptr->next;
        lptr->next = NULL;

        if (lptr->data < 0) {
            lptr->next = negHead;
            negHead = lptr;
        } else if (lptr->data == 0) {
            lptr->next = zeroHead;
            zeroHead = lptr;
        } else {
            lptr->next = posHead;
            posHead = lptr;
        }

        lptr = nextNode;
    }

    if (negHead != NULL) {
        *head = negHead;
        lptr = negHead;
        while (lptr->next != NULL) {
            lptr = lptr->next;
        }
    }

    if (zeroHead != NULL) {
        if (*head == NULL) {
            *head = zeroHead;
        } else {
            lptr->next = zeroHead;
        }

        lptr = zeroHead;
        while (lptr->next != NULL) {
            lptr = lptr->next;
        }
    }

    if (posHead != NULL) {
        if (*head == NULL) {
            *head = posHead;
        } else {
            lptr->next = posHead;
        }
    }
}
void printList(struct Node_tag* head) {
    struct Node_tag* lptr = head;
    while (lptr != NULL) {
        printf("%d -> ", lptr->data);
        lptr = lptr->next;
    }
    printf("NULL\n");
}

void insertNode(struct Node_tag** head, int data) {
    struct Node_tag*nptr = (struct Node_tag*)malloc(sizeof(struct Node_tag));
   nptr->data = data;
   nptr->next = NULL;

    if (*head == NULL) {
        *head =nptr;
        return;
    }

    struct Node_tag* lptr = *head;
    while (lptr->next != NULL) {
        lptr = lptr->next;
    }

    lptr->next =nptr;
}

void freeList(struct Node_tag* head) {
    struct Node_tag* lptr = head;
    struct Node_tag* next;

    while (lptr != NULL) {
        next = lptr->next;
        free(lptr);
        lptr = next;
    }
}

int main() {
    struct Node_tag* head = NULL;
    insertNode(&head, 30);
    insertNode(&head, -5);
    insertNode(&head, -6);
    insertNode(&head, 20);
    insertNode(&head, -33);
    insertNode(&head, 0);
    insertNode(&head, 44);
    insertNode(&head, 0);
    insertNode(&head, 55);

    printf("Test case:\nInput: ");
    printList(head);
    rearrangeNodes(&head);
    printf("Output: ");
    printList(head);
    freeList(head);

    return 0;
}

