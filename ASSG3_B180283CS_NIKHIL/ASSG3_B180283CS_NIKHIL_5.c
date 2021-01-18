#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

void insert_linear(int *table, int val, int n) {
    int pos = val%n;
    // printf("%d\n", pos);
    while ( table[pos%n] != INT_MAX)
        pos++;
    table[pos%n] = val;
    // printf("insert %d at %d \n", tmp2, pos);
}
void search_linear(int *table, int val, int n) {
    int pos = val%n;int c = 0;
    while ( table[pos%n] != val && c < n) {
        pos++;
        c++;
    }
    if ( table[pos%n] == val )
        printf("1\n");
    else
        printf("-1\n");
}
void delete_linear(int *table, int val, int n) {
    int pos = val%n;
    while( table[pos%n] != val )
        pos++;

    table[pos%n] = INT_MAX;
}

void insert_quadratic(int *table, int val, int n, int c1, int c2) {
     int pos = val%n;
    // printf("%d\n", pos);
    int i = 0; int c = 0; 
    while ( table[pos%n] != INT_MAX && c < n) {
        pos = (val % n )+ (c1 * i) + (c2 * i * i);i++;c++;
    }
    table[pos%n] = val;

}
void search_quadratic(int *table, int val, int n, int c1, int c2) {
    int pos = val%n;int i = 0; int c = 0;
    while ( table[pos%n] != val && c < n) {
        pos = val % n + (c1 * i) + (c2 * i * i);i++;
        c++;
    }
    if ( table[pos%n] == val )
        printf("1\n");
    else
        printf("-1\n");
}
void delete_quadratic(int *table, int val, int n, int c1, int c2) {
    int pos = val%n;int i =0;
    while( table[pos%n] != val ){
        pos = val % n + (c1 * i) + (c2 * i * i);i++;
    }
    table[pos%n] = INT_MAX;
}

void insert_dh(int *table, int val, int n, int R) {
    int pos = val%n;int p2 = (R - (val%R));
    int i = 0; int c = 0; 
    while ( table[pos%n] != INT_MAX && c < n) {
        pos = (val%n) + i * p2;i++;
    }
    table[pos%n] = val;
}
void search_dh(int *table, int val, int n, int R) {
    int pos = val%n;int i = 0; int c = 0;int p2 = (R - (val%R));
    while ( table[pos%n] != val && c < n) {
        pos = (val%n) + i * p2;i++;
        c++;
    }
    if ( table[pos%n] == val )
        printf("1\n");
    else
        printf("-1\n");
}
void delete_dh(int *table, int val, int n, int R) {
    int pos = val%n;int i =0;int p2 = (R - (val%R));
    while( table[pos%n] != val ){
        pos = val % n  + i * p2;i++;
    }
    table[pos%n] = INT_MAX;
}
int getPrime(int n){
    for ( int i = 2; i < n/2; i++) {
        if ( n % i == 0)
            return getPrime(n-1);
    }
    return n;
}
int main() {
    FILE *inputfile = stdin;
    char x; int n,c1,c2;
    fscanf(inputfile, "%c", &x); 
    // use x to decide the type of collision resolution
    fscanf(inputfile, "%d", &n);
    int *table = malloc(sizeof(int) *n);
    for (int i = 0; i < n; i++)
        table[i] = INT_MAX;
    if ( x == 'b' )
        fscanf(inputfile, "%d %d", &c1, &c2);
    int R = 0;
    if ( x == 'c') {
        R = getPrime(n);
        if ( R == n)
            R = getPrime(n-1);
    }
        
    char tmp;int tmp2;
    while ( 1) {
        fscanf(inputfile, "%c", &tmp);
        switch( tmp ) {
            case 'i':
                fscanf(inputfile, "%d", &tmp2);
                // find free slot using
                // collision resolution method
                if ( x == 'a') 
                    insert_linear(table, tmp2, n);
                else if ( x == 'b')
                    insert_quadratic(table, tmp2, n, c1, c2);
                else if ( x == 'c')
                    insert_dh(table, tmp2, n, R);
                break;
            case 's':
                fscanf(inputfile, "%d", &tmp2);
                if ( x == 'a')
                    search_linear(table, tmp2, n);
                else if ( x == 'b')
                    search_quadratic(table, tmp2, n, c1, c2);
                else if ( x == 'c')
                    search_dh(table, tmp2, n, R);
                break;
            case 'd':
                fscanf(inputfile, "%d", &tmp2);
                if ( x == 'a')
                    delete_linear(table, tmp2, n);
                else if ( x == 'b')
                    delete_quadratic(table, tmp2, n, c1, c2);
                else if ( x == 'c')
                    delete_dh(table, tmp2, n,R);
                break;
            case 'p':
                for (int i = 0; i < n; i++) {
                    printf("%d (", i);
                    if ( table[i] != INT_MAX )
                        printf("%d", table[i]);
                    printf(")\n");
                    
                }
                
                break;
            case 't':
                return 0;
        }

    }
    return 0;
}