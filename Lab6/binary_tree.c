#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "stack.h"
#include "queue.h"
#include "binary_tree.h"

BTNode *initNode(int value) {
    BTNode *node = (BTNode *) malloc(sizeof(BTNode));

    if (node == NULL) {
        return NULL;
    }
    node->data = value;
    node->left = node->right = node->parent = NULL;

    return node;
}

void destroyTree(BTNode **root) {
    if (*root == NULL) {
        return;
    }

    // Sterg subarborele stang
    destroyTree(&(*root)->left);

    // Sterg subarborele drept
    destroyTree(&(*root)->right);

    // Sterg nodul curent
    free(*root);

    *root = NULL;
}

int isLeaf(BTNode *node) {
    return (node->left == NULL
            && node->right == NULL);
}

int getNodeDegrees(BTNode *node) {
    return (node->left != NULL) + (node->right != NULL);
}

BTNode *insertNode(BTNode *root, int value) {
    
    if (root == NULL)
    {
        BTNode * nod = initNode(value);
        root = nod;
        return nod;
    }

    if (root->data > value)
    {
        if(root->left != NULL) 
            return insertNode(root->left,value);
        else 
        {
            BTNode * nod = initNode(value);
            nod->parent = root;
            root->left = nod;
            return nod;
        }
    }
    else
    {
        if(root->right != NULL)
            return insertNode(root->right,value);
        else
        {
            BTNode * nod = initNode(value);
            nod->parent = root;
            root->right = nod;
            return nod;
        }
    }
}

BTNode *searchNode(BTNode *root, int value) {
    
    if (root == NULL) return NULL;

    if (root->data == value) return root;

    if (root->data > value) return searchNode(root->left,value);
    else return searchNode(root->right,value);
}

int removeNode(BTNode **root, BTNode *node) {

//frunza
    if (node->left == NULL && node->right == NULL)
    {
        if (node->parent->left == node) 
            node->parent->left = NULL;
        else node->parent->right = NULL;

        free(node);
        return 0;
    }

//nod cu un copil
    if (node->left == NULL)
    {
        if (node->parent->left == node) 
        {
            node->right->parent = node->parent;
            node->parent->left = node->right;
            free(node);
            return 0;
        }

        else
        {
            node->right->parent = node->parent;
            node->parent->right = node->right;
            free(node);
            return 0;
        }
    }
    else if (node->right == NULL)
    {
        if (node->parent->left == node) 
        {
            node->left->parent = node->parent;
            node->parent->left = node->left;
            free(node);
            return 0;
        }

        else
        {
            node->left->parent = node->parent;
            node->parent->right = node->left;
            free(node);
            return 0;
        }
    }

// nod cu 2 copii
    BTNode * to_replace = node->right;

    while (to_replace->left != NULL)
        to_replace = to_replace->left;

    BTNode *to_replace_parent = to_replace->parent;

/* incercare esuata sa fiu barbat bine
//1
    to_replace_parent->left = to_replace->right;
    to_replace->right->parent = to_replace_parent;

//2
    to_replace->right = node->right;
    node->right->parent = to_replace;

//3

    to_replace->parent = node->parent;

    if (node->parent->left == node) 
        node->parent->left = to_replace;
    else node->parent->right = to_replace;

//4     
    to_replace->left = node->left;
    node->left->parent = to_replace;
*/
    node->data = to_replace->data;
    removeNode(root,to_replace);

    return 0;
}

void printInOrder(BTNode *root) {
    
    if (root == NULL)
        return;

    printInOrder(root->left);
    printf("%d ",root->data);
    printInOrder(root->right);

}

void printPreOrder(BTNode *root) {
    
    if (root == NULL)
        return;

    printf("%d ",root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder(BTNode *root) {
    
    if (root == NULL)
        return;

    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ",root->data);
}

size_t getHeight(BTNode *root) {
    
    if (root == NULL) return 0;

    size_t hl = getHeight(root->left);
    size_t hr = getHeight(root->right);

    if (hl>=hr) return hl+1;
    return hr+1;
}

int isBSTreeBalanced(BTNode *root) {
    
    if (root == NULL) return 1;

    size_t hl = getHeight(root->left);
    size_t hr = getHeight(root->right);

    if (abs(hl-hr)>1) return 0;

    return isBSTreeBalanced(root->left) * isBSTreeBalanced(root->right);
}


