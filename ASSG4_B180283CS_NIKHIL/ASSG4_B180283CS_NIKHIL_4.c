#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int x;
    struct Node *parent;
    struct Node *left_child;
    struct Node *right_sibling;
    int degree;
    int pos;
};
typedef struct Node Node;

Node NULL_NODE = {INT_MAX, &NULL_NODE, &NULL_NODE, &NULL_NODE, INT_MAX, INT_MAX};

struct Heap {
    Node *roots;
};
typedef struct Heap Heap;

Node *make_node() {
    Node *ret = malloc(sizeof(Node));
    ret->x = -1;
    ret->degree = 0;
    ret->parent = &NULL_NODE;
    ret->left_child = &NULL_NODE;
    ret->right_sibling = &NULL_NODE;
    return ret;
}

Heap *make_heap() {
    Heap *ret = malloc(sizeof(Heap));
    // Sentinel
    ret->roots = &NULL_NODE;
    return ret;
}
void binomial_link(Node *n, Node *subnode) {
    subnode->parent = n;
    subnode->right_sibling = n->left_child;
    n->left_child = subnode;
    n->degree += 1;
}
Heap *merge_heap(Heap *h1, Heap *h2) {
    Node *cur1 = h1->roots;
    Node *cur2 = h2->roots;

    Heap *h3 = make_heap();
    // Note: h3->roots is now a sentinel
    h3->roots = make_node();
    Node *cur3 = h3->roots;

    while (cur1 != &NULL_NODE || cur2 != &NULL_NODE) {
        Node **small = cur1->degree <= cur2->degree ? &cur1 : &cur2;
        cur3->right_sibling = *small;
        cur3 = cur3->right_sibling;
        *small = (*small)->right_sibling;
    }

    // Remove the sentinel at the beginning
    Node *head_sentinel = h3->roots;
    h3->roots = h3->roots->right_sibling;
    free(head_sentinel);

    return h3;
}


Heap *union_heap(Heap *h1, Heap *h2) {
    Heap *h = merge_heap(h1, h2);
    Node *head_sentinel = make_node();
    head_sentinel->right_sibling = h->roots;
    h->roots = head_sentinel;

    Node *prev = h->roots;
    Node *cur = prev->right_sibling;
    Node *next = cur->right_sibling;

    while (cur != &NULL_NODE && next != &NULL_NODE) {
        if (cur->degree < next->degree) {
            prev = cur;
            cur = next;
            next = cur->right_sibling;
            continue;
        }

        if (next->right_sibling != &NULL_NODE &&
            next->degree == next->right_sibling->degree) {
            prev = cur;
            cur = next;
            next = cur->right_sibling;
            continue;
        }

        if (cur->x <= next->x) {
            // unlink next
            cur->right_sibling = next->right_sibling;
            binomial_link(cur, next);
        } else {
            // unlink cur
            prev->right_sibling = cur->right_sibling;
            binomial_link(next, cur);
        }
        prev = cur;
        cur = next;
        next = cur->right_sibling;

    }

    h->roots = head_sentinel->right_sibling;
    free(head_sentinel);
    return h;
}


void insert(Heap *h, Node *x) {
    Heap *h1 = make_heap();
    h1->roots = x;
    Heap *h3 = union_heap(h, h1);
    h->roots = h3->roots;
    free(h1);
    free(h3);
}

Node *minimum(Heap *h) {
    Node *cur = h->roots;
    Node *min_node = cur;
    while (cur != &NULL_NODE ) {
        if (cur->x <= min_node->x) {
            min_node = cur;
        }
        cur = cur->right_sibling;
    }
    return min_node;
}

int tree_count(Heap *h) {
    Node *cur = h->roots;
    int tc = 0;
    while (cur != &NULL_NODE) {
        tc++; // tree count is number of nodes in rootList
        cur = cur->right_sibling;
    }
    return tc;
}

Node *reverse_node_list(Node *prev, Node *cur) {
    if (cur == &NULL_NODE)
        return prev;
    Node *next = cur->right_sibling;
    cur->right_sibling = prev;
    return reverse_node_list(cur, next);
}


Node *extract_min(Heap *h) {
    Node *min = minimum(h);
    if (min == &NULL_NODE)
        return min;

    Node *head_sentinel = make_node();
    head_sentinel->right_sibling = h->roots;
    h->roots = head_sentinel;

    Node *prev = h->roots;
    Node *cur = prev->right_sibling;
    while (cur != min) {
        prev = prev->right_sibling;
        cur = prev->right_sibling;
    }

    // unlink cur (min) from root list
    prev->right_sibling = cur->right_sibling;

    // New heap with children of min as roots
    Heap *h_temp = make_heap();
    h_temp->roots = reverse_node_list(&NULL_NODE, min->left_child);
    min->left_child = &NULL_NODE;

    // Degree of every node now has decreased by one
    cur = h_temp->roots;
    while (cur != &NULL_NODE) {
        cur->parent = &NULL_NODE;
        cur->degree -= 1;
        cur = cur->right_sibling;
    }

    h->roots = h->roots->right_sibling;
    free(head_sentinel);

    Heap *h_union = union_heap(h, h_temp);
    h->roots = h_union->roots;

    free(h_temp);
    free(h_union);

    return min;
}

void decrease_key(Node *n, int new_key) {
    assert(new_key < n->x);

    n->x = new_key;

    Node *cur = n;

    while (cur->parent != &NULL_NODE && cur->x < cur->parent->x) {
        int temp = cur->x;
        cur->x = cur->parent->x;
        cur->parent->x = temp;
        cur = cur->parent;
    }
}


void delete (Heap *h, Node *n) {
    if (n == &NULL_NODE) {
        fprintf(stdout, "NOT FOUND\n");
        return;
    }
    decrease_key(n, INT_MIN);
    extract_min(h);
}

int main() {
    int n,a,b;
    scanf("%d", &n);
    Node **nodes = malloc(sizeof(Node*) *n);
    char input[10];

    Heap *h = make_heap();
    while ( 1 ) {
        scanf("%s", input);
        if ( strcmp(input, "insr") == 0 ) {
            scanf("%d %d", &a, &b);
            // printf("insert %d %d", a,b);
            nodes[a] = make_node();
            nodes[a]->x = b;
            nodes[a]->pos = a;
            insert(h, nodes[a]);
        } else if ( strcmp(input, "extr") == 0) {
            Node *min = extract_min(h);
            // clear in the node list
            nodes[min->pos] = NULL; 
            if (min == &NULL_NODE) {
                printf( "EMPTY\n");
            } else {
                printf("%d\n", min->x);
                free(min);
            }
        } else if ( strcmp(input, "decr") == 0 ) {
            scanf("%d %d", &a, &b);
            int ke = (nodes[a]->x)-b ;
            if ( ke > 0)
                decrease_key(nodes[a], ke );
            else 
                printf("-1\n");
        } else if ( strcmp( input, "min") == 0 ) {
            Node *min = minimum(h);
            if (min != &NULL_NODE) {
                printf("%d\n", min->x);
            } else {
                printf( "EMPTY\n");
            }
        } else if ( strcmp(input, "del") == 0) {
            scanf("%d", &a);
            // printf("%d\n", nodes[a]->x);
            delete(h, nodes[a]);
            nodes[a]->x = INT_MAX;
        } else if ( strcmp(input, "tc") == 0 ) {
            printf("%d\n", tree_count(h));
        } else if ( strcmp(input, "stop") == 0) {
            return 0;
        } 
    }
}