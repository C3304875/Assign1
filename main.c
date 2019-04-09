// ENGG1003 Assignment 1
// Specification Document: https://uonline.newcastle.edu.au/bbcswebdav/pid-4089777-dt-content-rid-20660523_1/courses/CRS.126462.2019.S1/project1%281%29.pdf

#include <stdio.h>

char encryptRotationCypher(char *inputText, int rotationAmount);

void main() {
    FILE *input, *output;
    char inputText[1024], outputText, selector = '1';
    int i = 0, rotationAmount;

    // Initialise input & output files.
    output = fopen("Resources/output.txt", "w");
    input = fopen("Resources/input.txt", "r");
    if (input == NULL) {
        perror("File Input");
    }

    printf("1. Encrypt input Message || 2. Exit Programme.\n");
    printf("Please Make a Selection: \n");

    // Read input into char array inputText.
    while (!feof(input)) {
        fscanf(input, "%c", &inputText[i]);
        i++;
    }

    switch(selector){
        case '1':
            printf("Please enter rotation amount: ");
            rotationAmount = scanf("%d", rotationAmount);
            outputText = encryptRotationCypher(&inputText, rotationAmount);
            printf("%s", outputText);
            break;
        default: printf("yeet");
    }

    // Test output
    for (i = 0; inputText[i] != '\0'; i++) {
        //printf("%s", outputText);
       // fprintf(output, "%s", *outputText);

    }

}

char encryptRotationCypher(char *inputText, int rotationAmount){
    int i;

    for(i = 0; inputText[i] != '\0'; i++){
        if (inputText[i] >= 65 && inputText[i] <= 90) {
            if(inputText[i] == 65)
                inputText[i] = 90 - rotationAmount;
            if(inputText[i] == 90)
                inputText[i] = 65 - rotationAmount;
            inputText[i] += rotationAmount;
        }
    }

}