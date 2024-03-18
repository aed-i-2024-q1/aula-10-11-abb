#include <stdio.h>

#include "bst.h"

// TODO: Call destructor when it is implemented

void testSearch() {
    BST* bst = bst_create();
    
    Element contains[] = {50, 43, 3, 48, 61, 58, 70};
    Element notContains[] = {0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 90, 100};

    for (int i = 0; i < 8; i++) {
        printf("%d: %sfound\n", contains[i], bst_search(bst, contains[i]) ? "" : "not ");
    }

    for (int i = 0; i < 12; i++) {
        printf("%d: %sfound\n", notContains[i], bst_search(bst, notContains[i]) ? "" : "not ");
    }
}

void testTraversals() {
    BST* bst = bst_create();

    printf("InOrder: ");
    bst_printInOrder(bst);
    printf("PreOrder: ");
    bst_printPreOrder(bst);
    printf("PostOrder: ");
    bst_printPostOrder(bst);
    printf("\n");
}

void testPrint() {
    BST* bst = bst_create();

    bst_print(bst);
}

int main() {
    testSearch();
    testTraversals();
    testPrint();

    return 0;
}