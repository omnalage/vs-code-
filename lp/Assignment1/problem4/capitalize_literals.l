%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
%}

%option noyywrap

CHAR_LITERAL   \'([^\'\\]|\\.)\'
STRING_LITERAL \"([^"\\]|\\.)*\"
OTHER          .|\n

%%
{CHAR_LITERAL}   {
                    // Capitalize the character literal
                    printf("'");
                    if (yytext[1] != '\\') {
                        printf("%c", toupper(yytext[1])); // Regular character
                    } else {
                        printf("%c%c", yytext[1], yytext[2]); // Escape sequence
                    }
                    printf("'");
                 }

{STRING_LITERAL} {
                    printf("\"");
                    for (int i = 1; yytext[i] != '\0'; i++) {
                        if (yytext[i] == '"') break; // End of string
                        if (yytext[i] != '\\') {
                            printf("%c", toupper(yytext[i])); // Capitalize
                        } else {
                            printf("%c%c", yytext[i], yytext[i+1]); // Escape sequence
                            i++;
                        }
                    }
                    printf("\"");
                 }

{OTHER}          { printf("%s", yytext); } // Print all other text as is
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
