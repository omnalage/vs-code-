// Write a C program to remove all nodes of data values 
//  less than that of the last node.
#include<stdio.h>
#include<stdlib.h>
typedef struct Node_tag
{
    int data;
    struct Node_tag *next;
} Node;

Node* CreateNode(Node *last, int d)
{
    Node *nptr;
    nptr = (Node*)malloc(sizeof(Node));
    nptr->data = d;
    return nptr;
}
Node* InsertAtStart(Node *last, Node *nptr)
{
    if (last == NULL)
    {
        last = nptr;
        last->next = nptr;
    }
    else
    {
        nptr->next = last->next;
        last->next = nptr;
    
    }
    return last;
}
Node* DeleteNode(Node *last)
{
    Node *p,*q;
    if (last != NULL)
    {
        if (last->next != last)
        {
            p = last;
            while (p->next != last)
            {
                q= p->next;
                if (q->data < last->data)
                {
                    p->next = q->next;
                    free(q);
                }
                else
                {
                    p = p->next;
                }
                q=p->next;
            }
        }
    }
    return last;
}
void printList(Node *last)
{
    Node *ptr,*ptr2;
    ptr = last->next;
    printf("entered print...");
    while (ptr != last)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("%d ", ptr->data);
    printf("\n");
}
int main()
{
    Node *last,*nptr;
    int n,data;
    last = NULL;
    printf("enter no. of elements:");
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&data);
        nptr = CreateNode(last,data);
        last = InsertAtStart(last,nptr);
    }
    printList(last);
    last = DeleteNode(last);
    printList(last);
    return 0;
}
