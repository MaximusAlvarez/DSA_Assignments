#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
struct node {
	int data;
	int bst;
	struct node *left,*right;
};
typedef struct node* BSTp;
BSTp newnode(int element){
	BSTp newnode = (BSTp)malloc(sizeof(struct node));
        newnode->data = element;
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
}
void input(BSTp *tree){
    char ch;
    scanf(" %c",&ch);
    int element;
    if(scanf("%d",&element)){
        *tree = newnode(element);
        input(&((*tree)->left));
        input(&((*tree)->right));
    }
    scanf(" %c",&ch);
}
int findMin(BSTp tree){
    if(tree==NULL)
        return INT_MAX;
    while(tree->left!=NULL)
        tree=tree->left;
    return tree->data;
}
int findMax(BSTp tree){
    if(tree==NULL)
        return INT_MIN;
    while(tree->right!=NULL)
        tree=tree->right;
    return tree->data;
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
    BSTp tree=NULL;
    input(&tree);
    printf("%d",maxSubBST(tree));
    return 0;
}
