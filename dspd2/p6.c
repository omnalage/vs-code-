#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

int isComposite(int num)
{
    if (num < 2)
    {
        return 0;
    }
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return 1;
        }
    }
    return 0;
}

void removeCompositeAndSort(struct Node **head_ref)
{
    struct Node *current = *head_ref;
    while (current != NULL)
    {
        struct Node *next_node = current->next;
        if (isComposite(current->data))
        {
            if (current->prev != NULL)
            {
                current->prev->next = current->next;
            }
            else
            {
                *head_ref = current->next;
            }
            if (current->next != NULL)
            {
                current->next->prev = current->prev;
            }
            free(current);
        }
        current = next_node;
    }

    int swapped;
    struct Node *last = NULL;
    struct Node *temp;

    if (*head_ref == NULL)
    {
        return;
    }

    do
    {
        swapped = 0;
        current = *head_ref;

        while (current->next != last)
        {
            if (current->data > current->next->data)
            {
                int temp_data = current->data;
                current->data = current->next->data;
                current->next->data = temp_data;

                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

void insertEnd(struct Node **head_ref, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL)
    {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    struct Node *last = *head_ref;
    while (last->next != NULL)
    {
        last = last->next;
    }

    last->next = new_node;
    new_node->prev = last;
}

void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main()
{
    struct Node *head = NULL;
    int n, data;
    
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    
    printf("Enter the data for each node in ascending order: ");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &data);
        insertEnd(&head, data);
    }

    printf("List: ");
    printList(head);

    removeCompositeAndSort(&head);

    printf("Final List: ");
    printList(head);

    return 0;
}
