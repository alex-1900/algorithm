#include <stdio.h>
#include <stdlib.h>
#include "./binary-tree.h"

node ** _getleafmost(node **);

int main(void)
{
    node * root = NULL;
    ins(&root, 20);
    ins(&root, 40);
    ins(&root, 10);
    ins(&root, 5);
    ins(&root, 15);
    ins(&root, 30);
    ins(&root, 50);
    ins(&root, 35);
    ins(&root, 45);
    ins(&root, 55);
    ins(&root, 52);
    ins(&root, 60);

    del(&root, 40);
    printf("%d\n", (* find(&root, 45))->right->key);

    destroy_tree(root);
}

void ins(node **leaf, int key)
{
    if (*leaf == NULL) {
        *leaf = (node *) malloc(sizeof(node));
        (*leaf)->key = key;
        (*leaf)->left = NULL;
        (*leaf)->right = NULL;
    } else if (key < (*leaf)->key) {
        ins(&(*leaf)->left, key);
    } else {
        ins(&(*leaf)->right, key);
    }
}

node ** find(node ** leaf, int key)
{
    if (key == (* leaf)->key) {
        return leaf;
    } else if (key < (* leaf)->key) {
        return find(&(* leaf)->left, key);
    } else {
        return find(&(* leaf)->right, key);
    }
}

void del(node ** leaf, int key)
{
    node ** operator = find(leaf, key);
    // empty case
    if ((* operator)->left == NULL && (* operator)->right == NULL) {
        free(* operator);
        (* operator) = NULL;
    }

    // only left case
    else if ((* operator)->left != NULL && (* operator)->right == NULL) {
        node * leaf = (* operator)->left;
        free(* operator);
        (* operator) = leaf;
    }

    // only right case
    else if ((* operator)->left == NULL && (* operator)->right != NULL) {
        node * right = (* operator)->right;
        free(* operator);
        (* operator) = right;
    }

    // tow leaves case
    else {
        node ** succeed = succeeding(operator);
        node * swapSucceed = (* succeed);
        (* succeed) = (* succeed)->right;
        swapSucceed->left = (* operator)->left;
        swapSucceed->right = (* operator)->right;
        free(* operator);
        (* operator) = swapSucceed;
    }

    operator = NULL;
}

node ** succeeding(node ** leaf)
{
    if ((* leaf)->right == NULL) {
        return &(* leaf)->right;
    }

    return _getleafmost(&(* leaf)->right);
}

void destroy_tree(node * leaf)
{
    if (leaf != NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        free(leaf);
        leaf = NULL;
    }
}

node ** _getleafmost(node ** leaf)
{
    if ((* leaf)->left == NULL) {
        return leaf;
    }
    return _getleafmost(&(* leaf)->left);
}
