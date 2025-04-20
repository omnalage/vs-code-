%{
#include <stdio.h>
#include <ctype.h>
int count =0;
%}

%option noyywrap

LETTER      [a-zA-Z_]
DIGIT       [0-9]
IDENTIFIER  {LETTER}({LETTER}|{DIGIT})*

%%
"int"|"float"|"return"|"if"|"else"|"for"|"while"|"do"|"break"|"continue"|"char"|"double"|"void"|"short"|"long"|"signed"|"unsigned"|"static"|"extern"|"auto"|"register"|"sizeof"|"typedef"|"struct"|"union"|"enum"|"const"|"volatile"|"default"|"case"|"switch"|"goto"|"printf"|"scanf" 
  {  count++; }
{IDENTIFIER}    { count++; }
.               { /*No output */ } // Print other characters
\n              { /*No output */ }         // Print newlines
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
    printf("%d",count);
    fclose(input_file);
    return 0;
}
