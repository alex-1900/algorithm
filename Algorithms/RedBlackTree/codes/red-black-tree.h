#ifndef __RED_BLACK_TREE__
#define __RED_BLACK_TREE__

#define RED 1
#define BLACK 2

typedef struct _node {
    int key;
    struct _node * left;
    struct _node * right;
    struct _node * parent;
    int color;
} node;

typedef struct _root {
    node * node;
} root;

void insert_fixup(root *, node *);

void del_fixup(root *, node *, node *);

void del(root *, int);

void ins(root *, int);

node ** insert(node **, int, node *);

node ** find(node **, int);

node ** minimum(node **);

node ** succeeding(node **);

node ** maximum(node **);

void transplant(root *, node *, node *);

void left_rotate(root *, node *);

void right_rotate(root *, node *);

void change_color(node *);

void exchange_color(node *, node *);

void destroy_tree(node *);

#endif
