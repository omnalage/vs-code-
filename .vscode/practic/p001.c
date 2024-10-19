#include <stdio.h>
#include <stdlib.h>

struct Node
{
      int data;
      struct Node *next;
};

void linkedListTraversal(struct Node *ptr)
{
      while (ptr != NULL)
      {
            printf("list:- %d\n", ptr->data);
            ptr = ptr->next;
      }
}

int main()
{
      struct Node *n1;
      struct Node *n2;
      struct Node *n3;
      struct Node *n4;

      // Allocate memory for nodes in the linked list in Heap
      n1 = (struct Node *)malloc(sizeof(struct Node));
      n2 = (struct Node *)malloc(sizeof(struct Node));
      n3 = (struct Node *)malloc(sizeof(struct Node));
      n4 = (struct Node *)malloc(sizeof(struct Node));

      // Link first and n2 nodes
      n1->data = 10;
      n1->next = n2;

      // Link n2 and n3 nodes
      n2->data = 20;
      n2->next = n3;

      // Link n3 and n4 nodes
      n3->data = 30;
      n3->next = n4;

      // Terminate the list at the n3 node
      n4->data = 40;
      n4->next = NULL;

      linkedListTraversal(n1);
      return 0;
}
