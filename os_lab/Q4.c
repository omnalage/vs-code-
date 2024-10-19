#include <stdio.h>

int main()
{
    // fopen is generally used to open file and read, write, append to it in steps, but freopen will directly redirect the output to that file
    freopen("sample_output_of_Q4.txt", "w", stdout);

    // This will now be written to output.txt instead of the console
    printf("All the data is now redirected to a file!\n");

    // Close the file when done
    fclose(stdout);

    return 0;
}
