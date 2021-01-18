// fix access counting
#include<stdio.h>
#include<stdlib.h>
typedef struct node {
    int val;int rank; 
    struct node *parent;
} Node;

typedef struct set {
    Node *elements[10000];
    int accesses;
} Set;

Node * getNode(int val) {
    Node *new = malloc(sizeof(Node));
    new->val = val;
    new->rank = 0;
    new->parent = new;
}

void makeSet(Set *set, int val) {
    Node *n = getNode(val);
    set->elements[val] = n;
}

Node* find(Set *set, Node *node) {
    if ( node == NULL)
        return NULL;
    if ( node->parent == node) {
        set->accesses++;
        return node;
    }

    while ( node->parent != node){
        node = node->parent;
        set->accesses++;
    }
    return node;
}

Node* find_compress(Set *set, Node *n) {
    if ( n == NULL) {
        return NULL;
    }

    if (n->parent == n) {
        return n;
    }
    set->accesses++;
    n->parent = find_compress(set, n->parent);
    return n->parent;
}

void union_none(Set *set, int n1, int n2) {
    Node *f = set->elements[n1];
    Node *g = set->elements[n2];
    if ( f == NULL || g == NULL)
        printf("ERROR\n");

    Node *x= find(set,f);
    Node *y = find(set,g);
    if ( x->parent == y->parent) {
        return;
    }

    y->parent = x;   
}

void union_ranked(Set *set, int n1, int n2) {
    Node *f = set->elements[n1];
    Node *g = set->elements[n2];
    if ( f == NULL || g == NULL)
        printf("ERROR\n");

    Node *p2 = find(set, f);
    Node *p1 = find(set, g);
    if (  p1 == p2 ) {
        return;
    }
    // ranked union
    if ( p2->rank >= p1->rank ) {
        if ( p1->rank == p2->rank) {
            p2->rank++;
        }
        p1->parent = p2;
    } else {
        p2->parent = p1;
    }
}
void union_ranked_compresss(Set *set, int n1, int n2) {
    Node *f = set->elements[n1];
    Node *g = set->elements[n2];
    if ( f == NULL || g == NULL)
        printf("ERROR\n");
    if ( f->parent == g->parent) {
        return;
    }
    Node *p2 = find_compress(set, f);
    Node *p1 = find_compress(set, g);

    if ( p1 == p2)
        return;

    // ranked union
    if ( p2->rank >= p1->rank ) {
        if ( p1->rank == p2->rank) {
            p2->rank++;
        }
        p1->parent = p2;
    } else {
        p2->parent = p1;
    }

}


int main() {

    Set *a = malloc(sizeof(Set));
    Set *b = malloc(sizeof(Set));
    Set *c = malloc(sizeof(Set));
    Set *d = malloc(sizeof(Set));

    int elems[10000] = {0};

    char ch;int x,y;
    while ( scanf("%c", &ch) == 1) {
        switch (ch) {
        case 'm':
            scanf("%d", &x);
            makeSet(a, x);
            makeSet(b, x);
            makeSet(c, x);
            makeSet(d, x);
            printf("%d\n", x);
            elems[x] = 1;
            break;
        case 'u':
            scanf("%d %d", &x,&y);
            if ( elems[x] != 1 || elems[y] != 1) {
                printf("ERROR\n");
                break;
            }
            union_none(a,x,y);
            union_ranked(b,x,y);
            union_none(c,x,y);
            union_ranked_compresss(d,x,y);
            printf("%d %d %d %d\n", find(a,a->elements[x])->val,find(b,b->elements[x])->val,find_compress(c,c->elements[x])->val,find_compress(d,d->elements[x])->val);
            break;
        case 'f':
            scanf("%d", &x);
            if ( elems[x] == 1)
                printf("%d %d %d %d\n",find(a,a->elements[x])->val,find(b,b->elements[x])->val,find_compress(c,c->elements[x])->val,find_compress(d,d->elements[x])->val);
            else 
                printf("NOT FOUND\n");
            break;
        case 's':
            printf("%d %d %d %d\n", a->accesses, b->accesses, c->accesses, d->accesses);
            return 0;
            break;
        default:
            break;
        }
    }
}