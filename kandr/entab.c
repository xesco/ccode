#include <stdio.h>

#define MAXLINE 1024
#define TABSTOP 4

void retab(char to[], char from[]);
int _getline(char line[], int maxline);

int main() {

    int len;
    char line[MAXLINE], newline[MAXLINE];

    while ((len = _getline(line, MAXLINE)) > 0) {
        retab(newline, line);
        printf("%s", newline);
    }

    return 0;
}

void retab(char to[], char from[]) {
    int i=0, j=0, k;

    while (from[i] != '\0') {
        if (from[i] == '\t') {
            for (k=j+TABSTOP; j<k; j++)
                to[j] = ' '; 
            }
            i++;
        }
        else
            to[j++] = from[i++];
    }
    to[j] = from[i];
}

int _getline(char s[], int lim) {

    int c, i;

    for (i=0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
        
    return i;
}
