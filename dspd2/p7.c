#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    int priority;
    struct Node *next;
} Node;

Node *createNode(int data, int priority)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

void insert(Node **head, int data, int priority)
{
    Node *newNode = createNode(data, priority);
    if (*head == NULL || priority < (*head)->priority)
    {
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        Node *current = *head;
        while (current->next != NULL && current->next->priority <= priority)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}
void display(Node *head)
{
    if (head == NULL)
    {
        printf("Priority queue is empty.\n");
        return;
    }
    printf("Priority queue elements:\n");
    while (head != NULL)
    {
        printf("Data: %d, Priority: %d\n", head->data, head->priority);
        head = head->next;
    }
}

int main()
{
    Node *priorityQueue = NULL;
    int data, priority;
    char choice;

    do
    {
        printf("Enter data to insert: ");
        scanf("%d", &data);
        printf("Enter priority: ");
        scanf("%d", &priority);
        insert(&priorityQueue, data, priority);

        printf("Do you want to insert more elements? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    display(priorityQueue);

    Node *current = priorityQueue;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}