#include <stdio.h>
#include <string.h>
#include <ctype.h>

void main() {
    char s[20];
    char flag[20] = "//Constant";
    char result, equal, operator;
    double interrslt;
    int flag2 = 0;
    FILE *fp1, *fp2;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening file\n");
        return;
    }

    fscanf(fp1, "%s", s);
    while (!feof(fp1)) {
        if (strcmp(s, flag) == 0) {
            flag2 = 1;
        }
        if (flag2 == 1) {
            fscanf(fp1, "%s", s);
            result = s[0];
            equal = s[1];

            if (isdigit(s[2]) && isdigit(s[4])) {
                operator = s[3];
                switch (operator) {
                    case '+':
                        interrslt = (s[2] - '0') + (s[4] - '0');
                        break;
                    case '-':
                        interrslt = (s[2] - '0') - (s[4] - '0');
                        break;
                    case '*':
                        interrslt = (s[2] - '0') * (s[4] - '0');
                        break;
                    case '/':
                        interrslt = (s[2] - '0') / (s[4] - '0');
                        break;
                    default:
                        interrslt = 0;
                        break;
                }
                fprintf(fp2, "/*Constant Folding*/\n");
                fprintf(fp2, "%c = %lf\n", result, interrslt);
                flag2 = 0;
            }
        } else {
            fprintf(fp2, "Not Optimized\n");
            fprintf(fp2, "%s\n", s);
        }
        fscanf(fp1, "%s", s);
    }

    fclose(fp1);
    fclose(fp2);
}
