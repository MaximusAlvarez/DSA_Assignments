#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
struct node {
    int data;
    int bst;
    struct node *left,*right;
};
typedef struct node* BSTp;
void create(BSTp *tree){
    scanf(" (");
    int element;
    if(scanf("%d",&element)){
        BSTp newnode = (BSTp)malloc(sizeof(struct node));
        newnode->data = element;
        newnode->left = NULL;
        newnode->right = NULL;
        *tree = newnode;
        create(&((*tree)->left));
        create(&((*tree)->right));
    }
    scanf(" )");
}
int findMin(BSTp tree){
    if(tree==NULL)
        return INT_MAX;
    if(tree->left==NULL)
        return tree->data;
    return findMin(tree->left);
}
int findMax(BSTp tree){
    if(tree==NULL)
        return INT_MIN;
    if(tree->right==NULL)
        return tree->data;
    return findMax(tree->right);
}
int maxSubBST(BSTp tree){
    if(tree == NULL)
        return 0;
    if(tree->left == NULL && tree->right == NULL)
        return tree->bst=1;
    int left = maxSubBST(tree->left),right = maxSubBST(tree->right);
    if((tree->left == NULL || tree->left->bst) && (tree->right == NULL || tree->right->bst))
        if(tree->data < findMin(tree->right) && tree->data > findMax(tree->left)){
            tree->bst = 1;
            return left+right+1;
        }
    tree->bst = -1;
    return (left>right)?left:right;
}
int main(){
    BSTp tree;
    tree=NULL;
    create(&tree);
    printf("%d",maxSubBST(tree));
    return 0;
}