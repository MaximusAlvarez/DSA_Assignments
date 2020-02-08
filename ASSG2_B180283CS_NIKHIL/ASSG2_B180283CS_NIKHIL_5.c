#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node {
    int data;
    struct node *left,*right;
};
typedef struct Height {
    int h1,h2;
}heights;
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
void paren(BSTp tree){
    if(tree == NULL){
        printf("()");
        return;
    }
    printf("(%d",tree->data);
    paren(tree->left);
    paren(tree->right);
    printf(")");
    return ;
}
int height(BSTp tree){
    if(tree==NULL)
        return -1;
    int left = height(tree->left);
    int right = height(tree->right);
    return (left > right) ? (left+1):(right+1); 
}
int max(int a,int b){
    return (a>b)?a:b;
}
int longest_path(BSTp root, int* height) { 
    int lh,rh;
    if(root == NULL) 
    { 
        *height = 0; 
        return 0;
    } 
    int maxi=max(longest_path(root->left, &lh),longest_path(root->right, &rh)); 
    *height = max(lh, rh) + 1; 
    return max(lh + rh, maxi); 
} 
int main(){
    char instru[5];
    BSTp tree;
    int i=0;
    tree=NULL;
    create(&tree);
    printf("%d %d",height(tree),longest_path(tree,&i));
    return 0;
}