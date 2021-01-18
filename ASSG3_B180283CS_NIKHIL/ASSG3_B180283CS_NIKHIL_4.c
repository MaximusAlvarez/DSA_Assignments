#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
int hash(char *string, int s, int e) {
    int code = 0;
    for ( int i = s; i < e; i++) {
        code += (string[i]) * pow(10, i+1);
    }
    return code % 2147483648;
}
int roll_hash(int v, char a, char b, int l) {
    v -= a * 10;
    v += b * pow(10, l-1);
    return v;
}
void reverse(char *x, int begin, int end)
{
   char c;

   if (begin >= end)
      return;

   c          = *(x+begin);
   *(x+begin) = *(x+end);
   *(x+end)   = c;

   reverse(x, ++begin, --end);
}

int search( char *needle, char *haystack) {
    int len_needle = strlen(needle);

    // printf("code : %d  -> %d\n" , hash(needle), len_needle);

    int h = hash(needle, 0, len_needle);
    char needle_rev[100]; strcpy(needle_rev, needle);
    reverse(needle_rev, 0, len_needle-1);
    int h_rev = hash(needle_rev, 0, len_needle);
    // printf("%s %d\n", needle, h_rev);
    for ( int i = 0; i <= strlen(haystack)-len_needle; i+=1 ) {
        // printf("remove %c add %c\n", haystack[i-len_needle], haystack[i]);
        // int m = roll_hash(h, haystack[i-len_needle],haystack[i], len_needle);
        char cur[100];
        int j;
        for (j = 0; j < len_needle; j++) {
            // printf("%c", haystack[i+j]);
                cur[j] = haystack[i+j];
        }
        cur[len_needle] = '\0';
        // printf("\n");
        // printf("%d | %d =? %d\n", h,h_rev, hash(cur,0,len_needle));
        int m = hash(cur, 0, len_needle);
        if ( m == h || m == h_rev ) {
            // compare the strings
            // printf("%s %s %s\n", cur, needle, needle_rev);
            if ( strcmp(needle, cur) == 0 || strcmp(needle_rev, cur) == 0) {
                return 1;
            }
        } 
        // calculate rolling hash and compare with both forward and reverse
        // if hash's match; compare the strings
    }
    return 0;
}
int main() {
    FILE *inputfile = stdin;
    int tc;
    fscanf(inputfile, "%d", &tc);
    char needle[1000];
    char haystack[1000];
    while ( tc-- ) {
        fscanf(inputfile, "%s", &needle);
        fscanf(inputfile, "%s", &haystack);
        if ( search(needle, haystack) == 1)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}