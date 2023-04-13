#include "head.h"

// Function to create a new BST node
struct node* newNode(int item)
{
    struct node* temp
        = (struct node*)malloc(
            sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a new node with
// given key in BST
struct node* insert(struct node* node, int key)
{
    // If the tree is empty, return a new node
    if (node == NULL)
        return newNode(key);
  
    // Otherwise, recur down the tree
    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
  
    // Return the node pointer
    return node;
}
  
// Function to do inorder traversal of BST
void inorder(struct node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Function to do preorder traversal of BST
void preOrder(struct node* root)
{
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
 
// Function to do postorder traversal of BST
void postOrder(struct node* root)
{
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

// Function that returns the node with minimum
// key value found in that tree
struct node* minValueNode(struct node* node)
{
    struct node* current = node;
  
    // Loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
  
    return current;
}
  
// Function that deletes the key and
// returns the new root
struct node* deleteNode(struct node* root,
                        int key)
{
    // base Case
    if (root == NULL)
        return root;
  
    // If the key to be deleted is
    // smaller than the root's key,
    // then it lies in left subtree
    if (key < root->key) {
        root->left
            = deleteNode(root->left, key);
    }
  
    // If the key to be deleted is
    // greater than the root's key,
    // then it lies in right subtree
    else if (key > root->key) {
  
        root->right
            = deleteNode(root->right, key);
    }
  
    // If key is same as root's key,
    // then this is the node
    // to be deleted
    else {
  
        // Node with only one child
        // or no child
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
  
        // Node with two children:
        // Get the inorder successor(smallest
        // in the right subtree)
        struct node* temp = minValueNode(root->right);
  
        // Copy the inorder successor's
        // content to this node
        root->key = temp->key;
  
        // Delete the inorder successor
        root->right
            = deleteNode(root->right, temp->key);
    }
    return root;
}

