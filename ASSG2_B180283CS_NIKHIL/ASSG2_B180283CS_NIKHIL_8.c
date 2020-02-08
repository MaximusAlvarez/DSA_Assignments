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
symbolp newsymbol(char ch){
    symbolp new;
    new = (symbolp)malloc(sizeof(struct symbol));
    new->sym = ch;
    new->freq = 1;
    new->left = NULL;
    new->right = NULL;
    return new;
}
nodep newnode(char ch){
    nodep new;
    new = (nodep)malloc(sizeof(struct node));
    new->Symbol = newsymbol(ch);
    new->prev = NULL;
    new->next = NULL;
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
nodep sort(nodep head){
    nodep sorted,temp;
    sorted = NULL;
    while(head != NULL){
        temp = head->next;
        head->next = NULL;
        head->prev = NULL;
        sortInsert(&sorted,head);
        head = temp;
    }
    return sorted;
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
    for(int i=0;m[i]!='\0';i++)
        insert(&head,m[i]);
    head = sort(head);
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
    int b = calculate(tree->left,a+1)+calculate(tree->right,a+1);
    return (b==0)?(a*(tree->freq)):b;
}
void print_Code_Length(char m[]){
    symbolp tree = Find_huffman_Code(m);
    printf("%d\n",calculate(tree,0));
}
int main(){
    char str[100];
    while(1){
        scanf("%s",str);
        print_Code_Length(str);
    }
    return 0;
}