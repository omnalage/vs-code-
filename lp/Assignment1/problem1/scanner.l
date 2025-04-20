%{
#include <stdio.h>
int int_count = 0;      // Count of integers
int float_count = 0;    // Count of floating-point numbers
%}

DIGIT   [0-9]
INT     {DIGIT}+
FLOAT   {DIGIT}+"."{DIGIT}+|"."{DIGIT}+|{DIGIT}+"."

%%
{INT}"."{DIGIT}+     { float_count++; }    // Floating-point numbers
"."{DIGIT}+          { float_count++; }    // Floating-point numbers without leading digits
{DIGIT}+"."          { float_count++; }    // Floating-point numbers without trailing digits
{INT}                { int_count++; }      // Integers
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

    printf("Number of integers: %d\n", int_count);
    printf("Number of floating-point numbers: %d\n", float_count);

    fclose(input_file);
    return 0;
}

int yywrap() {
    return 1;
}
