#include<stdio.h>
#include<stdlib.h>
struct symbol {
    char sym;
    int freq;
    struct symbol *left,*right;
};
typedef struct symbol * symbolp;
struct node {
    symbolp Symbol;
    struct node *next,*prev;
};
typedef struct node * nodep;
nodep newnode(char ch){
    nodep new;
    new = (nodep)malloc(sizeof(struct node));
    symbolp new2;
    new2 = (symbolp)malloc(sizeof(struct symbol));
    new2->sym = ch;
    new2->freq = 1;
    new2->left = new2->right = NULL;
    new->Symbol = new2;
    new->prev = new->next = NULL;
    return new;
}
void insert(nodep *head,char ch){
    if(*head == NULL)
        *head = newnode(ch);
    else{
        nodep temp = *head;
        while(temp->next != NULL){
            if(temp->Symbol->sym == ch){
                temp->Symbol->freq++;
                return;
            }
            temp=temp->next;
        }
        if(temp->Symbol->sym == ch){
                temp->Symbol->freq++;
                return;
        }
        temp->next = newnode(ch);
        temp->next->prev = temp;
    }
}
void sortInsert(nodep *head,nodep newnode){
    if(*head == NULL)
        *head = newnode;
    else if((*head)->Symbol->freq > newnode->Symbol->freq){
        (*head)->prev = newnode;
        newnode->next = *head;
        *head = newnode;
    }
    else{
        nodep temp = *head;
        while(temp->next != NULL && temp->next->Symbol->freq<newnode->Symbol->freq)
            temp = temp->next;
        newnode->next = temp->next;
        if(temp->next != NULL)
            temp->next->prev = newnode;
        temp->next = newnode;
        newnode->prev = temp;
    }
}
nodep pop(nodep *head){
    nodep temp;
    temp = *head;
    *head = (*head)->next;
    return temp;
}
symbolp Find_huffman_Code(char m[]){
    nodep head;
    head = NULL;
    int i=0;
    while(m[i]!='\0'){
        insert(&head,m[i]);
        i++;
    }
    nodep sorted,temp;
    sorted = NULL;
    for(;head != NULL;){
        temp = head->next;
        head->next = head->prev = NULL;
        sortInsert(&sorted,head);
        head = temp;
    }
    head = sorted;
    while(head->next != NULL){
        nodep a = pop(&head);
        nodep b = pop(&head);
        nodep c = newnode(' ');
        c->Symbol->left = a->Symbol;
        c->Symbol->right = b->Symbol;
        sortInsert(&head,c);
    }
    return head->Symbol; 
}
int calculate(symbolp tree,int a){
    if(tree == NULL)
        return 0;
    int b = calculate(tree->left,a+1);
    b+=calculate(tree->right,a+1);
    if(b==0)
        return (a*(tree->freq));
    else
        return b;
}
void print_Code_Length(char m[]){
    symbolp tree = Find_huffman_Code(m);
    printf("%d\n",calculate(tree,0));
}
int main(){
    char str[100];
    int i=100;
    for(;i!=0;i--){
        scanf("%s",str);
        print_Code_Length(str);
    }
    return 0;
}