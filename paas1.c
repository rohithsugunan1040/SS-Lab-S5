#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    FILE *f1, *f2, *f3, *f4;
    int lc, sa, l, op1, o, len;
    char m1[20], la[20], op[20], otp[20];

    // Open input file
    f1 = fopen("input.txt", "r");
    if(f1 == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // Open symbol table file
    f3 = fopen("symtab.txt", "w");
    if(f3 == NULL) {
        printf("Error creating symbol table file.\n");
        fclose(f1);
        return 1;
    }

    // Read first line from input file
    fscanf(f1, "%s %s %d", la, m1, &op1);

    // Check for START directive
    if(strcmp(m1, "START") == 0)
    {
        sa = op1;
        lc = sa;
        printf("\t%s\t%s\t%d\n", la, m1, op1);
    }
    else
    {
        lc = 0;
    }

    // Read next line from input file
    fscanf(f1, "%s %s", la, m1);

    // Process assembly code
    while(strcmp(m1, "END") != 0)
    {
        // Print the current line
        printf("\n%d\t%s\t%s", lc, la, m1);

        // Update symbol table (excluding '-')
        if(strcmp(la, "-") != 0) {
            fprintf(f3, "\n%d\t%s", lc, la);
        }

        // Handle instructions and directives to update location counter
        if(strcmp(m1, "WORD") == 0) {
            lc = lc + 3;
        }
        else if(strcmp(m1, "RESW") == 0) {
            fscanf(f1, "%d", &op1);
            lc = lc + 3 * op1;
        }
        else if(strcmp(m1, "BYTE") == 0) {
            fscanf(f1, "%s", op);
            if(op[0] == 'X')
                lc = lc + 1;
            else if(op[0] == 'C') {
                len = strlen(op) - 3;
                lc = lc + len;
            }
        }
        else if(strcmp(m1, "RESB") == 0) {
            fscanf(f1, "%d", &op1);
            lc = lc + op1;
        }
        else {
            lc = lc + 3; // Assuming 3 as default instruction size for unknown opcodes
        }

        // Read next line from input file
        fscanf(f1, "%s %s", la, m1);
    }

    // Print program length
    printf("\nprogram length = %d\n", lc - sa);

    // Close files
    fclose(f1);
    fclose(f3);

    return 0;
}
