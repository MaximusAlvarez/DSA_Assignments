#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node {
    char *word;
    struct node* next;
};
typedef struct node* hash;
hash newnode(char *word){
    hash temp;
    temp = (hash)malloc(sizeof(struct node));
    char *tempword;
    tempword = (char*)malloc(50*sizeof(char));
    strcpy(tempword, word);
    temp->word = tempword;
    temp->next = NULL;
    return temp;
}
int findKey(hash node, int cap){
    return strlen(node->word)%cap;
}
void insert(hash *table, char *word, int cap){
    hash new = newnode(word);
    int key = findKey(new, cap);
    hash temp = table[key];
    if(temp == NULL){
        table[key] = new;
        return;
    }
    while(temp->next!=NULL){
        if(strcmp(temp->word, new->word)==0)
            return ;
        temp = temp->next;
    }
    if(strcmp(temp->word, new->word)==0)
        return ;
    temp->next = new;
}
void printTable(hash *table, int cap){
    for(int i=0; i<cap; i++){
        hash temp = table[i];
        if(temp == NULL)
            printf("NULL");
        while(temp!=NULL){
            printf("%s ", temp->word);
            temp = temp->next;
        }
        printf("\n");
    }
}
int main(){
    char ch, word[50];
    int n;
    scanf("%d", &n);
    hash table[n];
    for(int i=0;i<n;i++)
        table[i]=NULL;
    while(1){
        scanf(" %s", word);
        if(word[strlen(word)-1]=='.'){
            word[strlen(word)-1]= '\0';
            insert(table, word, n);
            break;
        }
        insert(table, word, n);
        scanf("%c", &ch);
        if(ch == '\n')
            break;
    }
    printTable(table, n);
    return 0;
}