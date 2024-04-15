#include <stdio.h>
#include <stdlib.h>

#define MAX_PRIORITY 5

typedef struct Node
{
      int data;
      struct Node *next;
} Node;

typedef struct
{
      Node *front[MAX_PRIORITY];
      Node *rear[MAX_PRIORITY];
} PriorityQueue;

void initPriorityQueue(PriorityQueue *pq)
{
      for (int i = 0; i < MAX_PRIORITY; i++)
      {
            pq->front[i] = NULL;
            pq->rear[i] = NULL;
      }
}

Node *createNode(int data)
{
      Node *newNode = (Node *)malloc(sizeof(Node));
      if (newNode == NULL)
      {
            printf("Memory allocation failed.\n");
            exit(1);
      }
      newNode->data = data;
      newNode->next = NULL;
      return newNode;
}

void enqueue(PriorityQueue *pq, int data, int priority)
{
      Node *newNode = createNode(data);
      if (pq->front[priority] == NULL)
      {
            pq->front[priority] = newNode;
            pq->rear[priority] = newNode;
      }
      else
      {
            pq->rear[priority]->next = newNode;
            pq->rear[priority] = newNode;
      }
}

void display(PriorityQueue pq)
{
      printf("Priority queue elements:\n");
      for (int i = 0; i < MAX_PRIORITY; i++)
      {
            Node *current = pq.front[i];
            if (current == NULL)
                  continue;
            printf("Priority %d: ", i);
            while (current != NULL)
            {
                  printf("%d ", current->data);
                  current = current->next;
            }
            printf("\n");
      }
}

int main()
{
      PriorityQueue pq;
      initPriorityQueue(&pq);
      int data, priority;
      char choice;

      do
      {
            printf("Enter data to insert: ");
            scanf("%d", &data);
            printf("Enter priority (0 to %d): ", MAX_PRIORITY - 1);
            scanf("%d", &priority);
            if (priority < 0 || priority >= MAX_PRIORITY)
            {
                  printf("Invalid priority! Please enter a priority between 0 and %d.\n", MAX_PRIORITY - 1);
                  continue;
            }
            enqueue(&pq, data, priority);

            printf("Do you want to insert more elements? (y/n): ");
            scanf(" %c", &choice);
      } while (choice == 'y' || choice == 'Y');

      display(pq);
      
      for (int i = 0; i < MAX_PRIORITY; i++)
      {
            Node *current = pq.front[i];
            while (current != NULL)
            {
                  Node *temp = current;
                  current = current->next;
                  free(temp);
            }
      }
      return 0;
}