#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
    int data;
    int height, count;
    struct node *left,*right;
};
typedef struct node* AVLp;

int max(int a, int b){
    return (a>b)?a:b;
}
//Returns height of node
int height(AVLp tree){
    if(tree == NULL)
        return 0;
    return tree->height;
}
//Creates a newnode
AVLp newnode(int element){
    AVLp new = (AVLp)malloc(sizeof(struct node));
    new->data = element;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;
    new->count = 1;
    return new;
}

AVLp leftRotate(AVLp tree){
    AVLp x = tree->right;
    AVLp y = x->left;
    //Rotate
    x->left = tree;
    tree->right = y;
    //Update Heights
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    //Return new root
    return x;
}

AVLp rightRotate(AVLp tree){
    AVLp x = tree->left;
    AVLp y = x->right;
    //Rotate
    x->right = tree;
    tree->left = y;
    //Update Heights
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    //Return new root
    return x;
}

AVLp insert(AVLp tree,int element){
    if(tree == NULL)
        return newnode(element);
    if(element < tree->data)
        tree->left = insert(tree->left, element);
    else if(element > tree->data) 
        tree->right = insert(tree->right, element);
    else
    {
        tree->count++;
        return tree;
    }
    //recalculate height
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    //find balance
    int bal = height(tree->left) - height(tree->right);
    if(bal>1 && tree->left->data > element)
        return rightRotate(tree);
    if(bal<-1 && tree->right->data <= element)
        return leftRotate(tree);
    if(bal > 1 && tree->left->data <= element){
        tree->left = leftRotate(tree->left);
        return rightRotate(tree);
    }
    if(bal < -1 && tree->right->data > element){
        tree->right = rightRotate(tree->right);
        return leftRotate(tree);
    }
    return tree;
}
void printTree(AVLp tree){
    if(tree == NULL)
        return;
    printTree(tree->left);
    int count = tree->count;
    while(count--)
        printf("%d ", tree->data);
    printTree(tree->right);
    return ;
}
int main(){
    int element, n;
    AVLp tree;
    tree=NULL;
    scanf(" %d", &n);
    while(n--){
        scanf(" %d", &element);
        tree = insert(tree, element);
    }
    printTree(tree);
    return 0;
}