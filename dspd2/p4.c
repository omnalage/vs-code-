#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

int findLoopLengthAndConvertToCLL(struct Node *list)
{
    if (list == NULL || list->next == NULL)
    {
        return 0;
    }

    struct Node *slow = list, *fast = list;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {

            int length = 1;
            struct Node *temp = slow->next;

            while (temp != slow)
            {
                length++;
                temp = temp->next;
            }

            struct Node *start = list;
            struct Node *loopStart = list;

            for (int i = 0; i < length; i++)
            {
                loopStart = loopStart->next;
            }

            while (start != loopStart)
            {
                start = start->next;
                loopStart = loopStart->next;
            }

            struct Node *lastNode = loopStart;
            while (lastNode->next != loopStart)
            {
                lastNode = lastNode->next;
            }

            list = loopStart;
            lastNode->next = list;

            return length;
        }
    }

    return 0;
}

void printList(struct Node *list, int count)
{
    if (list == NULL || count == 0)
    {
        printf("Empty List\n");
        return;
    }

    struct Node *temp = list;
    for (int i = 0; i < count; i++)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{

    struct Node *list = NULL;

    int values[] = {20, 55, 70, 40, 33, 90, 11};
    int n = sizeof(values) / sizeof(values[0]);

    struct Node *lastNode = NULL;
    for (int i = 0; i < n; i++)
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = values[i];
        newNode->next = NULL;

        if (list == NULL)
        {
            list = newNode;
            lastNode = newNode;
        }
        else
        {
            lastNode->next = newNode;
            lastNode = newNode;
        }
    }

    lastNode->next = list->next->next->next;

    printf("Input: ");
    printList(list, n);

    int loopLength = findLoopLengthAndConvertToCLL(list);

    printf("Output: %d (length of the loop)\n", loopLength);
    printf("Output: ");

    printList(list, n);

    struct Node *current = list;
    struct Node *nextNode;
    do
    {
        free(current);
        nextNode = current->next;
        current = nextNode;
    } while (current != NULL);

    return 0;
}