#include <stdio.h>
#include <stdlib.h>
#include "./red-black-tree.h"

int main(void)
{
    root root;
    root.node = NULL;
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
    // printf("%d\n", root.node->left->key);
    printf("%d\n", (* find(&root.node, 20))->key);
    // printf("%d\n", (* find(&root.node, 40))->key);
    printf("%d\n", (* find(&root.node, 10))->key);
    printf("%d\n", (* find(&root.node, 5))->key);
    printf("%d\n", (* find(&root.node, 15))->key);
    printf("%d\n", (* find(&root.node, 30))->key);
    printf("%d\n", (* find(&root.node, 50))->key);
    printf("%d\n", (* find(&root.node, 35))->key);
    printf("%d\n", (* find(&root.node, 45))->key);
    printf("%d\n", (* find(&root.node, 55))->key);
    printf("%d\n", (* find(&root.node, 52))->key);
    printf("%d\n", (* find(&root.node, 60))->key);

    destroy_tree(root.node);
}

void ins(root * root, int key)
{
    node ** o = insert(&root->node, key, NULL);

    insert_fixup(root, * o);
}

void insert_fixup(root * root, node * child)
{
    while (child && child->parent && child->parent->color == RED)
    {
        if (child->parent == child->parent->parent->left) {
            node * y = child->parent->parent->right;
            if (y != NULL && y->color == RED) {
                child->parent->color = BLACK;
                y->color = BLACK;
                child->parent->parent->color = RED;
                child = child->parent->parent;
                continue;
            }
            
            if (child == child->parent->right) {
                // node * tmp;
                child = child->parent;
                left_rotate(root, child);
                // tmp = child->parent;
                // child->parent = child;
                // child = tmp;
            }
            child->parent->color = BLACK;
            child->parent->parent->color = RED;
            right_rotate(root, child->parent->parent);
        } else {
            node * y = child->parent->parent->left;
            if (y != NULL && y->color == RED) {
                child->parent->color = BLACK;
                y->color = BLACK;
                child->parent->parent->color = RED;
                child = child->parent->parent;
                continue;
            }
            
            if (child == child->parent->left) {
                // node * tmp;
                child = child->parent;
                right_rotate(root, child);
                // tmp = child->parent;
                // child->parent = child;
                // child = tmp;
            }
            child->parent->color = BLACK;
            child->parent->parent->color = RED;
            left_rotate(root, child->parent->parent);
        }
    }
    root->node->color = BLACK;
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

void del(root * root, int key)
{
    node ** pz = find(&root->node, key);
    node * z = (* pz);
    node * y = z;
    node * x = NULL;
    node * parent = z->parent;
    int y_original_color = y->color;
    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = * succeeding(&z);
        y_original_color = y->color;
        x = y->right;
        parent = y->parent;
        if (x && y->parent == z) {
            x->parent = y;
            parent = y;
        } else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
            // parent->left = z;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK) {
        del_fixup(root, x, parent);
    }

    free(z);
    z = NULL;
}

void del_fixup(root * root, node * child, node * parent)
{
    while ((!child || child->color == BLACK) || child != root->node) {
        if (child == parent->left) {
            node * w = parent->right;
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                left_rotate(root, parent);
                w = parent->right;
            }
            if (
                (w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)
            ) {
                w->color = RED;
                child = parent;
                parent = child->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left) {
                        w->left->color = BLACK;
                    }
                    w->color = RED;
                    right_rotate(root, w);
                    w = parent->right;
                }
                w->color = parent->color;
                parent->color = BLACK;
                if (w->right) {
                    w->right->color = BLACK;
                }
                left_rotate(root, parent);
                child = root->node;
                break;
            }
        } else {
            node * w = parent->left;
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                right_rotate(root, parent);
                w = parent->left;
            }
            if (
                (w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)
            ) {
                w->color = RED;
                child = parent;
                parent = child->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right) {
                        w->right->color = BLACK;
                    }
                    w->color = RED;
                    left_rotate(root, w);
                    w = parent->left;
                }
                w->color = parent->color;
                parent->color = BLACK;
                if (w->left) {
                    w->left->color = BLACK;
                }
                right_rotate(root, parent);
                child = root->node;
                break;
            }
        }
    }
    child->color = BLACK;
}

node ** minimum(node ** leaf)
{
    if ((* leaf) == NULL) {
        return NULL;
    }
    if ((* leaf)->left == NULL) {
        return leaf;
    }
    return minimum((&(* leaf)->left));
}

node ** maximum(node ** leaf)
{
    if ((* leaf) == NULL) {
        return NULL;
    }
    if ((* leaf)->right == NULL) {
        return leaf;
    }
    return minimum((&(* leaf)->right));
}

node ** succeeding(node ** leaf)
{
    if ((* leaf) == NULL) {
        return leaf;
    }

    if ((* leaf)->right == NULL) {
        return &((* leaf)->right);
    }

    return minimum((&(* leaf)->right));
}

void change_color(node * leaf)
{
    if (leaf->color == RED) {
        leaf->color = BLACK;
    } else {
        leaf->color = RED;
    }
}

void exchange_color(node * leaf1, node * leaf2)
{
    int color1 = leaf1->color;
    leaf1->color = leaf2->color;
    leaf2->color = color1;
}

void left_rotate(root * root, node * leaf)
{
    node * y = leaf->right;
    leaf->right = y->left;
    if (y->left != NULL) {
        y->left->parent = leaf;
    }
    y->parent = leaf->parent;

    if (leaf->parent != NULL) {
        if (leaf->parent->left == leaf) {
            leaf->parent->left = y;
        } else {
            leaf->parent->right = y;
        }
    } else {
        root->node = y;
    }

    y->left = leaf;
    leaf->parent = y;
}

void right_rotate(root * root, node * leaf)
{
    node * y = leaf->left;
    leaf->left = y->right;
    if (y->right != NULL) {
        y->right->parent = leaf;
    }
    y->parent = leaf->parent;
    if (y->parent != NULL) {
        if (y->parent->left == leaf) {
            y->parent->left = y;
        } else {
            y->parent->right = y;
        }
    } else {
        root->node = y;
    }

    y->right = leaf;
    leaf->parent = y;
}

node ** insert(node ** leaf, int key, node * parent)
{
    if (*leaf == NULL) {
        *leaf = (node *) malloc(sizeof(node));
        (*leaf)->key = key;
        (*leaf)->left = NULL;
        (*leaf)->right = NULL;
        (*leaf)->parent = parent;
        (*leaf)->color = RED;
        return leaf;
    } else if (key < (*leaf)->key) {
        return insert(&(*leaf)->left, key, *leaf);
    } else {
        return insert(&(*leaf)->right, key, *leaf);
    }
}

void destroy_tree(node * leaf)
{
    if (leaf != NULL) {
        // printf("%d\n", leaf->key);
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        free(leaf);
        leaf = NULL;
    }
}

void transplant(root * root, node * u, node * v)
{
    if (u->parent == NULL) {
        root->node = v;
    } else if (u->parent->left == u) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}
