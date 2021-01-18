#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
struct redblack {
    int data;
    char color;
    struct redblack *left, *right;
};
typedef struct redblack* RBptr;
RBptr newnode(int val, char color){
    RBptr node;
    node = (RBptr)malloc(sizeof(struct redblack));
    node->data = val;
    node->color = color;
    node->left = NULL;
    node->right = NULL;
    return node;
}
RBptr create(RBptr root){
    scanf(" (");
    int data;
    char color;
    if(scanf("%d %c", &data, &color)){
        root = newnode(data, color);
        root->left = create(root->left);
        root->right = create(root->right);
    }
    scanf(" )");
    return root;
}
void print(RBptr root){
    printf("( ");
    if(root!=NULL){
        printf("%d %c ", root->data, root->color);
        print(root->left);
        print(root->right);
    }
    printf(") ");
}
int isRedBlack(RBptr root, int min, int max, int *bheight){
    if(root == NULL){
        *bheight = 1;
        return 1;
    }
    if(root->data < min || root->data > max)
        return 0;
    int bhleft, bhright;
    if(isRedBlack(root->left, min, root->data, &bhleft) && isRedBlack(root->right, root->data, max, &bhright)){
        if(bhleft == bhright){
            if(root->color == 'B')
                *bheight = bhleft + 1;
            else if(root->left!=NULL &&  root->left->color == 'R')
                return 0;
            else if(root->right!=NULL && root->right->color == 'R')
                return 0;
            else
                *bheight = bhleft;
            return 1;
        }
    }
    return 0;
}
int main(){
    RBptr root;
    root = create(root);
    int height, temp = isRedBlack(root, INT_MIN, INT_MAX, &height);
    if(root->color == 'R')
        temp = 0;
    printf("%d", temp);
    return 0;
}