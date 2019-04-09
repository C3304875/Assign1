// ENGG1003 Assignment 1
// Specification Document: https://uonline.newcastle.edu.au/bbcswebdav/pid-4089777-dt-content-rid-20660523_1/courses/CRS.126462.2019.S1/project1%281%29.pdf

#include <stdio.h>

char encryptRotationCypher(char *cypherText, int rotationAmount);

void main() {
    FILE *input, *output;
    char cypherText[1024], outputText[1024], selector = '1';
    int i = 0, rotationAmount;

    // Initialise input & output files.
    output = fopen("Resources/output.txt", "w");
    input = fopen("Resources/input.txt", "r");
    if (input == NULL) {
        perror("File Input");
    }

    printf("1. Encrypt input Message || 2. Exit Programme.\n");
    printf("Please Make a Selection: \n");
    scanf("%c", selector);

    // Read input into char array cypherText.
    while (!feof(input)) {
        fscanf(input, "%c", &cypherText[i]);
        i++;
    }

    switch(selector){
        case '1':
            printf("Please enter rotation amount: \n");
            scanf("%d", rotationAmount);
            rotationAmount = 0;//scanf("%d", rotationAmount);
            encryptRotationCypher(&cypherText, rotationAmount);
            break;
        default: printf("yeet");
    }

    // Test output
    for (i = 0; cypherText[i] != '\0'; i++) {
        printf("%c", cypherText[i]);
    }
}

char encryptRotationCypher(char *cypherText, int rotationAmount){
    int i;
    char result[1024];

    for(i = 0; cypherText[i] != '\0'; i++){
        if (cypherText[i] >= 65 && cypherText[i] <= 90) {
            if(cypherText[i] == 65)
                cypherText[i] = 90 - rotationAmount;
            if(cypherText[i] == 90)
                cypherText[i] = 65 - rotationAmount;
            cypherText[i] += rotationAmount;
            result[i] = cypherText[i];
        }
    }
    return result;
}