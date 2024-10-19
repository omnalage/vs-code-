#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to check if there is a path with the given sum
bool hasPathSum(struct TreeNode* root, int sum) {
    // Base case: if the tree is empty
    if (root == NULL) {
        return false;
    }

    // If the current node is a leaf and its value equals the remaining sum
    if (root->left == NULL && root->right == NULL && sum - root->data == 0) {
        return true;
    }

    // Recur for the left and right subtrees with the updated sum
    return hasPathSum(root->left, sum - root->data) || hasPathSum(root->right, sum - root->data);
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

    // Create a binary tree
    struct TreeNode* root = newNode(5);
    root->left = newNode(4);
    root->right = newNode(8);
    root->left->left = newNode(11);
    root->left->left->left = newNode(7);
    root->left->left->right = newNode(2);
    root->right->left = newNode(13);
    root->right->right = newNode(4);
    root->right->right->right = newNode(1);

    // Given sum
    int sum = 22;

    // Check if there is a path with the given sum
    if (hasPathSum(root, sum)) {
        printf("There is a path with the sum %d.\n", sum);
    } else {
        printf("There is no path with the sum %d.\n", sum);
    }

    return 0;
}