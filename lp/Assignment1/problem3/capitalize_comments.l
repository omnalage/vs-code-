%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
%}

%option noyywrap

SINGLE_COMMENT  \/\/[^\n]*
MULTI_COMMENT   \/[*]([^*]|[*][^\/])*[*]\/
STRING          \"([^"\\]|\\.)*\"
PREPROCESSOR    \#[^\n]*
IDENTIFIER      [a-zA-Z_][a-zA-Z0-9_]*
NUMBER          [0-9]+(\.[0-9]+)?

%%
{SINGLE_COMMENT}    { 
                        for (int i = 0; yytext[i] != '\0'; i++) {
                            yytext[i] = toupper(yytext[i]);
                        }
                        printf("%s", yytext);
                    }
{MULTI_COMMENT}     {
                        for (int i = 0; yytext[i] != '\0'; i++) {
                            yytext[i] = toupper(yytext[i]);
                        }
                        printf("%s", yytext);
                    }
{STRING}            { printf("%s", yytext); } // Preserve strings
{PREPROCESSOR}      { printf("%s", yytext); } // Preserve preprocessor directives
{IDENTIFIER}        { printf("%s", yytext); } // Preserve identifiers
{NUMBER}            { printf("%s", yytext); } // Preserve numbers
.                   { printf("%s", yytext); } // Print other characters
\n                  { printf("\n"); }         // Print newlines
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

    fclose(input_file);
    return 0;
}
