#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node {
    int data;
    struct node *left,*right;
};
typedef struct node* BSTp;
void insert(BSTp *tree,int element){
    if(*tree == NULL){
        BSTp newnode = (BSTp)malloc(sizeof(struct node));
        newnode->data = element;
        newnode->left = NULL;
        newnode->right = NULL;
        *tree = newnode;
    }
    else if((*tree)->data<element)
        insert(&((*tree)->right),element);
    else
        insert(&((*tree)->left),element);
    return;
}
BSTp search(BSTp tree,int element){
    if(tree == NULL)
        return NULL;
    if(tree->data==element)
        return tree;
    if(tree->data < element)
        return search(tree->right,element);
    else 
        return  search(tree->left,element);
}
int level(BSTp tree,int element){
    if(tree == NULL)
        return -1;
    if(tree->data == element)
        return 0;
    if(tree->data < element){
        int lvl = level(tree->right,element);
        return (lvl==-1)?-1:(1+lvl);
    }
    int lvl = level(tree->left,element);
    return (lvl==-1)?-1:(1+lvl);
}
BSTp* findMin(BSTp* tree){
    if(*tree==NULL)
        return (BSTp*)-1;
    if((*tree)->left==NULL)
        return tree;
    return findMin(&((*tree)->left));
}
BSTp findMax(BSTp tree){
    if(tree==NULL)
        return (BSTp)-1;
    if(tree->right==NULL)
        return tree;
    return findMax(tree->right);
}
BSTp predecessor(BSTp tree, int node){
    if(tree == NULL)
        return NULL;
    if(tree->data == node && tree->left == NULL)
        return (BSTp)-1;
    if(tree->data == node)
        return findMax(tree->left);
    if(tree->data < node){
        BSTp temp = predecessor(tree->right,node);
        if(temp==(BSTp)-1)
            return tree;
        return temp;
    }
    return predecessor(tree->left,node);
}
BSTp successor(BSTp tree, int node){
    if(tree == NULL)
        return NULL;
    if(tree->data == node && tree->right == NULL)
        return (BSTp)-1;
    if(tree->data == node)
        return *findMin(&(tree->right));
    if(tree->data > node){
        BSTp temp = successor(tree->left,node);
        if(temp==(BSTp)-1)
            return tree;
        return temp;
    }
    return successor(tree->right,node);
}
BSTp delete(BSTp *tree,int node){
    if((*tree)==NULL)
        return NULL;
    if((*tree)->data==node){
        BSTp temp = *tree;
        if((*tree)->left == NULL)
            *tree = (*tree)->right;
        else if((*tree)->right==NULL)
            *tree = (*tree)->left;
        else 
        {
            BSTp  *temp2 = findMin(&((*tree)->right));
            *tree = *temp2;
            *temp2 = (*temp2)->right;
            (*tree)->left = temp->left;
            (*tree)->right = temp->right;
            if((*tree)->right == *tree)
                (*tree)->right = NULL;
        }
        free(temp);
        return (BSTp)-1;
    }
    else if((*tree)->data < node)
        return delete(&((*tree)->right),node);
    else 
        return  delete(&((*tree)->left),node);
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
int main(){
    char instru[5];
    int element;
    BSTp tree;
    tree=NULL;
    while(strcmp(instru,"stop")){
        scanf("%s",instru);
        if(!strcmp(instru,"insr")){
            scanf("%d",&element);
            insert(&tree,element);
        }   
        else if(!strcmp(instru,"srch")){
            scanf("%d",&element);
            if(search(tree,element)==NULL)
                printf("NOT FOUND\n");
            else 
                printf("FOUND\n");
        } 
        else if(!strcmp(instru,"minm")){
            BSTp* temp = findMin(&tree);
            if((long long int)temp==-1)
                printf("NIL\n");
            else
                printf("%d\n",(*temp)->data);
        } 
        else if(!strcmp(instru,"maxm")){
            BSTp temp = findMax(tree);
            if((long long int)temp==-1)
                printf("NIL\n");
            else
                printf("%d\n",temp->data);
        } 
        else if(!strcmp(instru,"pred")){
            scanf("%d",&element);
            BSTp temp = predecessor(tree,element);
            if(temp == NULL)
                printf("NULL\n");
            else if ( (long long int)temp == -1)
                printf("-1\n");
            else
                printf("%d\n",temp->data);
        } 
        else if(!strcmp(instru,"succ")){
            scanf("%d",&element);
            BSTp temp = successor(tree,element);
            if(temp == NULL)
                printf("NULL\n");
            else if ( (long long int)temp == -1)
                printf("-1\n");
            else
                printf("%d\n",temp->data);
        } 
        else if(!strcmp(instru,"delt")){
            scanf("%d",&element);
            if(delete(&tree,element) == NULL)
                printf("NULL\n");
        }
        else if(!strcmp(instru,"inor")){
            inorder(tree);
            printf("\n");
        } 
        else if(!strcmp(instru,"prer")){
            preorder(tree);
            printf("\n");
        }
        else if(!strcmp(instru,"post")){
            postorder(tree);
            printf("\n");
        } 
        // else if(!strcmp(instru,"lvl")){
        //     scanf("%d",&element);
        //     printf("%d\n",level(tree,element));
        // }
    }
    return 0;
}