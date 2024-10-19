#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node* next;
}node;
#define max 50
typedef struct hash
{
    int hash_size;
    node* hash_table[max];
}hash;
node* createnode(int val)
{
    node* nptr=(node*)malloc(sizeof(node));
    nptr->data=val;
    nptr->next=NULL;
    return nptr;
}
node* insertnode(node* head,int val)
{
    
    node* nptr=createnode(val);
   nptr->next=head;
   head=nptr;
   return head;
}
void initializehash(hash* h,int size)
{
    
    h->hash_size=size;
    for(int i=0;i<size;i++)
    {
        h->hash_table[i]=NULL;
    }
    
}
int getHashIndex(int val,hash* h)
{
    return val%h->hash_size;
}
void hash_insert(hash* h,int val)
{
    int k=getHashIndex(val,h);
   h->hash_table[k]= insertnode(h->hash_table[k],val);
    
    return ;
}
void display(hash *h)
{
    for(int i=0;i<h->hash_size;i++)
    {
        node* temp=h->hash_table[i];
        if(temp)
        {
             printf("index %d :",i);
            while(temp!=NULL)
          {
            printf(" %d ",temp->data);
            temp=temp->next;
          }
        
          printf("\n");
            
        }
     
    }
    
}
void delete(hash* h,int val)
{
    int k=getHashIndex(val,h);
    node* temp=h->hash_table[k];
    if(temp==NULL)
    {
        printf("error ");
    }
    else
    {
        node* prev=NULL;
        while(temp!=NULL&&temp->data!=val)
        {
            prev=temp;
            temp=temp->next;
        }
        if(prev==NULL)
        {
            
            h->hash_table[k]=temp->next;
            free(temp);
        }
        else if(temp==NULL)
        {
            printf("error ");
            
        }
        else
        {
            prev->next=temp->next;
            free(temp);
        }
        
        
        
    }
    return ;
}
void search(hash* h,int val)
{
    int k=getHashIndex(val,h);
    
    node* temp=h->hash_table[k];
    if(temp==NULL)
    {
        printf("no such element exists");
        
    }
    else{
        while(temp!=NULL&&temp->data!=val)
        {
            temp=temp->next;
        }
        if(temp)
        {
            printf("element index is %d ",k);
        }
        else
        {
            
             printf("no such element exists");
        }
        
        
        
    }
    return ;
    
}


int main()
{
    
    
    hash hash1;
   
    int size;
    printf("enter the size of hash:");
    scanf("%d",&size);
    initializehash(&hash1,size);
    hash_insert(&hash1,9);
     hash_insert(&hash1,5);
      hash_insert(&hash1,3);
      
      hash_insert(&hash1,13);
     
      display(&hash1);
      delete(&hash1,3);
      
       display(&hash1);
       search(&hash1,9);
    
    
    return 0;
    
}