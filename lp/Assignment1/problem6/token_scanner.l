%{
#include <stdio.h>
int count = 0;
%}

DIGIT   [0|1]8
OTHER   [2|3|4|5|6|7|8|9]*[a-zA-Z]*
%%
{DIGIT}"101"{DIGIT}  { count =1}
{OTHER}              { count = -1}
.                    { /* Ignore other characters */ }
\n                   { /* Ignore newlines */ }
%%

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening file");
        return 1;
    }

    yyin = input_file;
    yylex();

    printf("Number of tokens: %d\n", count);

    fclose(input_file);
    return 0;
}

int yywrap() {
    return 1;
}
