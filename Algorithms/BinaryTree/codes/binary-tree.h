#ifndef __BINARY_TREE__
#define __BINARY_TREE__

#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node * left;
    struct _node * right;
} node;

void destroy_tree(node *);

void ins(node **, int);

void del(node **, int);

node ** find(node **, int);

node ** succeeding(node **);

#endif
