#ifndef BST_H
#define BST_H

#include <stdbool.h>

#include "element.h"

typedef struct BST BST;

BST* bst_create();
void bst_destroy(BST* bst);
bool bst_search(BST* bst, Element key);
void bst_insert(BST* bst, Element key);
void bst_remove(BST* bst, Element key);
void bst_print(BST* bst); 
void bst_printInOrder(BST* bst);
void bst_printPreOrder(BST* bst);
void bst_printPostOrder(BST* bst);

#endif