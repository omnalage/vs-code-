/* tree is a non linear data structure is use for ideal for representing hieraclical data
 in a tree with a n node thre are (n-1)edegs
 
 types of binary tree :-
        1) full or strict binary tree:-all node have either 0 or 2 children
        2)perfect binary tree :-internal node have 2 children and all leaf node are on same level
        3)complete binary tree:-all leves are completely fill except possibaly the last leve and last level must have left alive
        4) Degenerate binary tree:- parent node has exactly one child
        5) skewed tree:- tree which are aline either right or left
*/


// structure of node for tree
#include <stdio.h>
#include <malloc.h>
struct node {
       int data;
       struct node* left;
       struct node* right; 
};


int main(){
       struct node *p;
       p= (struct node* )malloc(sizeof(struct node));
       
       return 0;
}
