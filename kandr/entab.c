#include <stdio.h>

#define MAXLINE 1024
#define TABSTOP 4
#define TAB '\t'
#define BLANK ' '
#define STREND '\0'

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

/* replace TABs to spaces */
void retab(char to[], char from[]) {
    int i=0, j=0;

    while (from[i] != STREND) {
        if (from[i] != TAB)
            to[j++] = from[i++];
        else {
            for (int k=j+TABSTOP; j<k; j++)
                to[j] = BLANK; 
            i++;
        }
    }
    // add final null character
    to[j] = from[i];
}

/* get next line form stdin */
int _getline(char s[], int lim) {

    int c, i;

    for (i=0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
        
    return i;
}
