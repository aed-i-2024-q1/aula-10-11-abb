#include "bst.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    Element key;
    struct Node* left;
    struct Node* right;
} Node;

struct BST {
    Node* root;
};

Node* createNode(Element key) {
    Node* node = malloc(sizeof(Node));

    node->key = key;
    node->left = NULL;
    node->right = NULL;

    return node;
}

BST* bst_create() {
    BST* bst = malloc(sizeof(BST));

    bst->root = NULL;

    return bst;
}

void bst_destroyRecur(Node* node) {
    if (node == NULL) {
        return;
    }
    bst_destroyRecur(node->left);
    bst_destroyRecur(node->right);
    free(node);
}

void bst_destroy(BST* bst) {
    bst_destroyRecur(bst->root);
    free(bst);
}

/**
 * Versao recursiva do algoritmo de inserção
* Caso base 1: a árvore é vazia, cria um novo nó
* Caso base 2: a chave já exista, termine
* Caso recursivo 1: se a chave for menor que a chave da raiz atual, 
*                   recursão à esquerda
* Caso recursivo 2: se a chave for maior que a chave da raiz atual,
*                   recursão à direita
*/
Node* bst_insertRecur(Node* node, Element key) {
    if (node == NULL) {
        return createNode(key);
    }
    if (key < node->key) {
        node->left = bst_insertRecur(node->left, key);
    } else if (key > node->key) {
        node->right = bst_insertRecur(node->right, key);
    }

    return node;
}

/**
 * Versão iterativa do algoritmo de inserção.
 * Utiliza dois ponteiros de percurso para achar a posição 
 * a inserir.
*/
void bst_insertIter(BST* bst, Element key) {
    if (bst->root == NULL) {
        bst->root = createNode(key);

        return;
    }

    Node* parent = NULL;
    Node* cur = bst->root;

    while (cur != NULL) {
        if (cur->key == key) {
            return;
        } else if (key < cur->key) {
            parent = cur;
            cur = cur->left;
        } else if (key > cur->key) {
            parent = cur;
            cur = cur->right;
        }
    }

    if (key < parent->key) {
        parent->left = createNode(key);
    } else if (key > parent->key){
        parent->right = createNode(key);
    }
}

/**
 * Função da API para inserção. Pode chamar
 * ou a versão recursiva, ou a iterativa, 
 * a critério do projetista
*/
void bst_insert(BST* bst, Element key) {
    bst->root = bst_insertRecur(bst->root, key);
    // bst_insertIter(bst, key);
}

Node* bst_successor(Node* node) {
    Node* cur = node->right;

    while (cur->left != NULL) {
        cur = cur->left;
    }

    return cur;
}

/**
 * Versão recursiva do algoritmo de remoção
 * Caso base 1: a árvore é vazia ou a chave não existe, retorne
 * Caso base 2: caso a chave seja encontrada, remova
 *    Caso base 2.1: se a raiz atual apenas 1 filho,
 *                   a raiz atual é substituída pelo filho
 *    Caso base 2.2: se a raiz atual não tem filhos
 *                   remova a raiz atual
 *    Caso base 2.3: se a raiz atual tem filhos à esquerda e à direita,
 *                   ache o sucessor, substitua a raiz atual pelo sucessor
 *                   e remova o sucessor
 * Caso recursivo 1: se a chave for menor que a chave da raiz atual,
 *                  recursão à esquerda
 * Caso recursivo 2: se a chave for maior que a chave da raiz atual,
 *                 recursão à direita
*/
Node* bst_removeRecur(Node* node, Element key) {
    if (node == NULL) {
        return node;
    }
    if (key < node->key) {
        node->left = bst_removeRecur(node->left, key);
    } else if (key > node->key) {
        node->right = bst_removeRecur(node->right, key);
    } else {
        if (node->left == NULL) {
            Node* trash = node;

            node = node->right;
            free(trash);
        } else if (node->right == NULL) {
            Node* trash = node;

            node = node->left;
            free(trash);
        } else {
            Node* successor = bst_successor(node);

            node->key = successor->key;
            node->right = bst_removeRecur(node->right, successor->key);
        }
    }

    return node;
}

/**
 * Versão iterativa do algoritmo de remoção
 * Utiliza dois ponteiros de percurso para achar a posição 
 * a remover.
 * Procurar a chave a ser removida
 * Caso 1: a árvore é vazia, retorne
 * Caso 2: a chave não existe, retorne
 * Caso 3: a chave é encontrada
 *   Caso 3.1: se a raiz atual apenas 1 filho,
 *            a raiz atual é substituída pelo filho
 *  Caso 3.2: se a raiz atual não tem filhos
 *           remova a raiz atual
 * Caso 3.3: se a raiz atual tem filhos à esquerda e à direita,
 *          ache o sucessor, substitua a raiz atual pelo sucessor
 *         e remova o sucessor
*/
void bst_removeIter(BST* bst, Element key) {
    Node* parent = NULL;
    Node* cur = bst->root;

    while (cur != NULL) {
        if (cur->key == key) {
            break;
        } else if (key < cur->key) {
            parent = cur;
            cur = cur->left;
        } else {
            parent = cur;
            cur = cur->right;
        }
    }

    if (cur == NULL) {
        return;
    }

    if (cur->left == NULL) {
        if (parent == NULL) {
            bst->root = cur->right;
        } else if (parent->left == cur) {
            parent->left = cur->right;
        } else {
            parent->right = cur->right;
        }
        free(cur);
    } else if (cur->right == NULL) {
        if (parent == NULL) {
            bst->root = cur->left;
        } else if (parent->left == cur) {
            parent->left = cur->left;
        } else {
            parent->right = cur->left;
        }
        free(cur);
    } else {
        Node* successor = cur->right;
        parent = cur;

        while (successor->left != NULL) {
            parent = successor;
            successor = successor->left;
        }

        cur->key = successor->key;

        if (parent->left == successor) {
            parent->left = successor->right;
        } else {
            parent->right = successor->right;
        }

        free(successor);
    }
}

void bst_remove(BST* bst, Element key) {
    bst->root = bst_removeRecur(bst->root, key);
    // bst_removeIter(bst, key);
}


bool bst_searchRecur(Node* node, Element key) {
    if (node == NULL) {
        return false;
    }
    if (node->key == key) {
        return true;
    }
    if (key < node->key) {
        return bst_searchRecur(node->left, key);
    } 
    
    return bst_searchRecur(node->right, key);
}

bool bst_search(BST* bst, Element key) {
    return bst_searchRecur(bst->root, key);
}

void bst_printInOrderRecur(Node* node) {
    if (node == NULL) {
        return;
    }
    bst_printInOrderRecur(node->right);
    element_print(node->key);
    printf(" ");
    bst_printInOrderRecur(node->left);
    
}

void bst_printInOrder(BST* bst) {
    bst_printInOrderRecur(bst->root);
    printf("\n");
}

void printPreOrderRecur(Node* node) {
    if (node == NULL) {
        return;
    }
    element_print(node->key);
    printf(" ");
    printPreOrderRecur(node->left);
    printPreOrderRecur(node->right);
}

void bst_printPreOrder(BST* bst) {
    printPreOrderRecur(bst->root);
    printf("\n");
}

void printPostOrderRecur(Node* node) {
    if (node == NULL) {
        return;
    }
    printPostOrderRecur(node->left);
    printPostOrderRecur(node->right);
    element_print(node->key);
    printf(" ");
}

void bst_printPostOrder(BST* bst) {
    printPostOrderRecur(bst->root);
    printf("\n");
}

void bst_printDiagram(Node* node, int level) {
  if (node == NULL) {
      return;
  }
  for (int i = 0; i < level; i++) {
    printf("  ");
  }
  element_print(node->key);
  printf("\n");
  bst_printDiagram(node->left, level + 1);  
  bst_printDiagram(node->right, level + 1);
}

void bst_print(BST* bst) {
  bst_printDiagram(bst->root, 0);
}