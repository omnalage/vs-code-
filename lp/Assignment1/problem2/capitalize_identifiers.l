%{
#include <stdio.h>
#include <ctype.h>
%}

%option noyywrap

LETTER      [a-zA-Z_]
DIGIT       [0-9]
IDENTIFIER  {LETTER}({LETTER}|{DIGIT})*
STRING      \"([^"\\]|\\.)*\"
COMMENT     \/\/[^\n]*|\/\*([^*]|\*+[^*/])*\*+\/
PREPROCESSOR \#[^\n]*

%%
{STRING}        { printf("%s", yytext); } // Preserve strings
{COMMENT}       { printf("%s", yytext); } // Preserve comments
{PREPROCESSOR}  { printf("%s", yytext); } // Preserve preprocessor directives
"int"|"float"|"return"|"if"|"else"|"for"|"while"|"do"|"break"|"continue"|"char"|"double"|"void"|"short"|"long"|"signed"|"unsigned"|"static"|"extern"|"auto"|"register"|"sizeof"|"typedef"|"struct"|"union"|"enum"|"const"|"volatile"|"default"|"case"|"switch"|"goto"|"printf"|"scanf" {
    printf("%s", yytext); // Reserved keywords are printed as is
}
{IDENTIFIER}    {
                    for (int i = 0; yytext[i] != '\0'; i++) {
                        yytext[i] = toupper(yytext[i]);
                    }
                    printf("%s", yytext); // Capitalize identifiers
                }
.               { printf("%s", yytext); } // Print other characters
\n              { printf("\n"); }         // Print newlines
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
