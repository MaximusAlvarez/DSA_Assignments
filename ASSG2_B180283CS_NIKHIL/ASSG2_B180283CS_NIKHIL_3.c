#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node {
    int data;
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
BSTp duplicate(BSTp tree){
    BSTp newnode = (BSTp)malloc(sizeof(struct node));
    newnode->data = tree->data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
void mirror(BSTp tree,BSTp *mirrortree){
    if(tree == NULL){
        return;
    }
    *mirrortree = duplicate(tree);
    mirror(tree->left,&((*mirrortree)->right));
    mirror(tree->right,&((*mirrortree)->left));
    return;
}
void inorder(BSTp tree){
    if(tree == NULL)
        return;
    inorder(tree->left);
    printf("%d ",tree->data);
    inorder(tree->right);
    return;
}
void preorder(BSTp tree){
    if(tree == NULL)
        return;
    printf("%d ",tree->data);
    preorder(tree->left);
    preorder(tree->right);
    return;
}
void postorder(BSTp tree){
    if(tree == NULL)
        return;
    postorder(tree->left);
    postorder(tree->right);
    printf("%d ",tree->data);
    return;
}
void paren(BSTp tree){
    if(tree == NULL){
        printf("( ) ");
        return;
    }
    printf("( %d ",tree->data);
    paren(tree->left);
    paren(tree->right);
    printf(") ");
    return ;
}
int main(){
    char instru[5];
    BSTp tree,mirrortree;
    tree=NULL;
    create(&tree);
    mirror(tree,&mirrortree);
    paren(mirrortree);
    return 0;
}