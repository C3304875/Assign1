// ENGG1003 Assignment 1
// Specification Document: https://uonline.newcastle.edu.au/bbcswebdav/pid-4089777-dt-content-rid-20660523_1/courses/CRS.126462.2019.S1/project1%281%29.pdf

#include <stdio.h>

const char cypher();
const char decypher();

void main() {
    FILE *input, *output;
    char inputText[1024];
    char outputText;
    int i = 0;

    output = fopen("Resources/output.txt", "w");
    input = fopen("Resources/input.txt", "r");
    if (input == NULL) {
        perror("File Input");
    }

    while (!feof(input)) {
        fscanf(input, "%c", &inputText[i]);
        i++;
    }

    for (i = 0; inputText[i] != '\0'; i++) {
        printf("%c", inputText[i]);
        fprintf(output, "%c", inputText[i]);
    }
}


