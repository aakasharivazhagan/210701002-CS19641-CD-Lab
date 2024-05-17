#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to generate assembly code from three-address code
void generateAssembly(char three_address_code[][50], int num_instructions) {
    // Iterate through each instruction
    for (int i = 0; i < num_instructions; i++) {
        char op[10], arg1[20], arg2[20], result[20];
        // Parse the instruction
        sscanf(three_address_code[i], "%s %s %s %s", op, arg1, arg2, result);
        // Generate assembly code based on the operation
        if (strcmp(op, "ADD") == 0) {
            printf("MOV AX, %s\n", arg1);
            printf("ADD AX, %s\n", arg2);
            printf("MOV %s, AX\n", result);
        } else if (strcmp(op, "SUB") == 0) {
            printf("MOV AX, %s\n", arg1);
            printf("SUB AX, %s\n", arg2);
            printf("MOV %s, AX\n", result);
        } else if (strcmp(op, "MUL") == 0) {
            printf("MOV AX, %s\n", arg1);
            printf("IMUL %s\n", arg2);
            printf("MOV %s, AX\n", result);
        } else if (strcmp(op, "DIV") == 0) {
            printf("MOV AX, %s\n", arg1);
            printf("IDIV %s\n", arg2);
            printf("MOV %s, AX\n", result);
        } else {
            printf("Unsupported operation: %s\n", op);
        }
    }
}

int main() {
    char three_address_code[100][50]; // Assuming max 100 instructions and 50 characters per instruction
    int num_instructions = 0;
    
    // Get three-address code instructions from the user
    printf("Enter three-address code instructions (type 'END' to finish):\n");
    char line[50];
    
    while (1) {
        fgets(line, sizeof(line), stdin);
        if (strcmp(line, "END\n") == 0) {
            break;
        }
        strcpy(three_address_code[num_instructions++], line);
    }
    
    // Generate assembly language instructions
    generateAssembly(three_address_code, num_instructions);
    
    return 0;
}
