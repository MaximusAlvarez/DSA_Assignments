#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node {
    int data;
    int sum;
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
void mod_tree(BSTp tree){
    if(tree == NULL){
        printf("( ) ");
        return;
    }
    printf("( %d ",tree->sum);
    mod_tree(tree->left);
    mod_tree(tree->right);
    printf(") ");
    return ;
}
int sum(BSTp tree){
    if(tree==NULL)
        return 0;
    tree->sum = tree->data + sum(tree->left) + sum(tree->right);
    return tree->sum;
}
int main(){
    char instru[5];
    BSTp tree;
    tree=NULL;
    create(&tree);
    sum(tree);
    mod_tree(tree);
    return 0;
}