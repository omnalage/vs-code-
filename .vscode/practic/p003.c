#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to check if two binary trees are exactly identical
bool areIdentical(struct TreeNode* root1, struct TreeNode* root2) {
    // Base cases: if both trees are empty, they are identical
    if (root1 == NULL && root2 == NULL) {
        return true;
    }

    // If one tree is empty and the other is not, they are not identical
    if (root1 == NULL || root2 == NULL) {
        return false;
    }

    // Check if the data of the current nodes is the same
    if (root1->data != root2->data) {
        return false;
    }

    // Recursively check the left and right subtrees
    return (areIdentical(root1->left, root2->left) && areIdentical(root1->right, root2->right));
}

// Function to create a new node
struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int main() {
    // Example usage:

    // Create two binary trees
    struct TreeNode* root1 = newNode(1);
    root1->left = newNode(2);
    root1->right = newNode(3);
    root1->left->left = newNode(4);
    root1->left->right = newNode(5);

    struct TreeNode* root2 = newNode(1);
    root2->left = newNode(2);
    root2->right = newNode(3);
    root2->left->left = newNode(4);
    root2->left->right = newNode(5);

    // Check if the trees are exactly identical
    if (areIdentical(root1, root2)) {
        printf("The trees are exactly identical.\n");
    } else {
        printf("The trees are not exactly identical.\n");
    }

    return 0;
}