#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    struct node *left,*parent,*right;
    int val;char color;
} Node;


void paren(Node *root) {
    printf( "( ");
    if ( root != NULL ) {
        printf( "%d %c ",root->val, root->color);
        paren(root->left);
        paren(root->right);
    }
    printf( ") ");
}
void leftRotate(Node **root, Node **x) {

    Node *y = (*x)->right;
    Node *b = y->left;

    if (*x == (*root)) {
        *root = y;
        y->parent = NULL;
    } else {
        if (*x == (*x)->parent->left) {
            (*x)->parent->left = y;
        } else {
            (*x)->parent->right = y;
        }
        y->parent = (*x)->parent;
    }

    (*x)->right = b;
    if (b)
        b->parent = *x;

    y->left = *x;
    (*x)->parent = y;
}

void rightRotate(Node **root, Node **x) {

    Node *y = (*x)->left;
    Node *b = y->right;

    if (*x == *root) {
        *root = y;
        y->parent = NULL;
    } else {
        if ((*x) == (*x)->parent->left) {
            (*x)->parent->left = y;
        } else {
            (*x)->parent->right = y;
        }
        y->parent = (*x)->parent;
    }

    (*x)->left = b;
    if (b)
        b->parent = *x;

    y->right = (*x);
    (*x)->parent = y;
}

void insertRedBlack(Node **root, int val) {
    // printf("insert %d\n ", val);
    // rotations need to take care of parent pointer
    Node *newNode = malloc(sizeof(Node));
    newNode->val = val;
    newNode->parent = newNode->left = newNode->right = NULL;
    newNode->color = 'R';
    if ( *root == NULL ) {
        *root = newNode;
        newNode->color = 'B';
    } else {
        Node *cur = *root;
        while ( cur ) {
            if (val < cur->val) {
                if (cur->left == NULL) {
                    newNode->parent = cur;
                    cur->left = newNode;
                    break;
                } else {
                    cur = cur->left;
                }
            } else {
                if (cur->right == NULL) {
                    newNode->parent = cur;
                    cur->right = newNode;
                    break;
                } else {
                    cur = cur->right;
                }
            }

        }
    }

    Node *z = newNode;
    while ( z->parent && z->parent->color == 'R') {
        Node *parent = z->parent;
        Node *grandparent = z->parent->parent;

        if ( grandparent->left == parent) {
            if ( grandparent->right && grandparent->right->color == 'R') {
                grandparent->right->color = 'B';
                grandparent->left->color = 'B';
                grandparent->color = 'R';
                z = grandparent;
            } else {
                if ( parent->right == z) {
                    leftRotate(root, &parent);
                    z = parent;
                    parent = z->parent;
                } 
                rightRotate(root,&grandparent);
                grandparent->color = 'R';
                parent->color = 'B';
            }
        }  else {
            if(grandparent->left && grandparent->left->color == 'R') {
                grandparent->left->color = 'B';
                grandparent->right->color = 'B';
                grandparent->color = 'R';
                z = grandparent;
            } else {
                if(parent->left == z) {
                    rightRotate(root,&parent);
                    z = parent;
                    parent = z->parent;
                }
                leftRotate(root, &grandparent);
                grandparent->color = 'R';
                parent->color = 'B';
            }
        }
    }
    if ( (*root)->color == 'R' ) 
        (*root)->color = 'B';
}
int main() {
    char BUF[1024];
    Node *root = NULL;
    while (fgets(BUF, 1024, stdin) != NULL) {
        int n = atoi(BUF);
        if ( n == 0 ) 
            return 0;
        insertRedBlack(&root, n);
        paren(root);
        printf("\n");
    }
    return 0;
}