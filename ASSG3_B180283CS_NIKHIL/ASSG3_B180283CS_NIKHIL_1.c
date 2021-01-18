#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
    int data;
    int height;
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
    else 
        tree->right = insert(tree->right, element);
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

AVLp search(AVLp tree,int element){
    if(tree == NULL){
        // printf("FALSE\n");
        return NULL;
    }
    if(tree->data==element){
        // printf("TRUE\n");
        return tree;
    }
    if(tree->data < element)
        return search(tree->right,element);
    else 
        return  search(tree->left,element);
}
AVLp findMin(AVLp tree){
    if(tree==NULL)
        return NULL;
    if(tree->left==NULL)
        return tree;
    return findMin(tree->left);
}
int balance(AVLp tree){
    if(tree == NULL)
        return 0;
    return height(tree->left) - height(tree->right);
}
void getBalance(AVLp tree, int k){
    AVLp temp = search(tree, k);
    printf("%d\n", balance(temp));
}
AVLp delete(AVLp tree,int node){
    if(tree==NULL)
        return NULL;
    if(tree->data==node){
        AVLp temp = tree;
        if(tree->left == NULL)
            tree = tree->right;
        else if(tree->right==NULL)
            tree = tree->left;
        else 
        {
            AVLp  temp2 = findMin(tree->right);
            tree->data = temp2->data;
            tree->right = delete(tree->right, tree->data);
            temp = NULL;
        }
        free(temp);
    }
    else if(tree->data < node)
        tree->right =  delete(tree->right,node);
    else 
        tree->left = delete(tree->left,node);
    if(tree == NULL)
        return tree;
    //recalculate height
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    //find balance
    int bal = height(tree->left) - height(tree->right);
    if(bal>1 && balance(tree->left) >= 0 )
        return rightRotate(tree);
    if(bal<-1 && balance(tree->right) <= 0)
        return leftRotate(tree);
    if(bal > 1 && balance(tree->left) < 0){
        tree->left = leftRotate(tree->left);
        return rightRotate(tree);
    }
    if(bal < -1 && balance(tree->right) > 0){
        tree->right = rightRotate(tree->right);
        return leftRotate(tree);
    }
    return tree;
    
}
int isAVL(AVLp tree, AVLp l, AVLp r, int *height){
    if(tree == NULL)
        return 1;
    if(l!=NULL && l->data >= tree->data)
        return 0;
    if(r!= NULL && r->data < tree->data)
        return 0;
    int left=0, right=0, checkl, checkr;
    checkl = isAVL(tree->left, l, tree, &left);
    checkr = isAVL(tree->right, tree, r, &right);
    *height = max(left, right) + 1;
    if((left - right) < -1 || (left - right) > 1)
        return 0;
    return checkl && checkr;
}
void printTree(AVLp tree){
    if(tree == NULL){
        printf("( ) ");
        return;
    }
    printf("( %d ",tree->data);
    printTree(tree->left);
    printTree(tree->right);
    printf(") ");
    return ;
}
int main(){
    char instru[5];
    int element, h;
    AVLp tree;
    tree=NULL;
    while(strcmp(instru,"stop")){
        scanf("%s",instru);
        if(!strcmp(instru,"insr")){
            scanf("%d",&element);
            tree = insert(tree,element);
        }   
        else if(!strcmp(instru,"disp")){
            printTree(tree);
            printf("\n");
        }
        else if(!strcmp(instru,"srch")){
            scanf("%d",&element);
            if(search(tree, element)==NULL)
                printf("FALSE\n");
            else    
                printf("TRUE\n");
        } 
        else if(!strcmp(instru,"delt")){
            scanf("%d",&element);
            if(search(tree, element) != NULL)
                tree = delete(tree, element);
        }
        else if(!strcmp(instru,"pbal")){
            scanf("%d",&element);
            getBalance(tree, element);
        }
        else if(!strcmp(instru,"avlc")){
            printf("%d", isAVL(tree, NULL, NULL, &h));
        }
    }
    return 0;
}