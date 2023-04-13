#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *left, *right;
};

struct node* newNode(int);

struct node* insert(struct node* , int );

void inorder(struct node*);

void preOrder(struct node* );

void postOrder(struct node*);

struct node* deleteNode(struct node*,
                        int );

struct node* minValueNode(struct node*);