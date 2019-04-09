// ENGG1003 Assignment 1
// Specification Document: https://uonline.newcastle.edu.au/bbcswebdav/pid-4089777-dt-content-rid-20660523_1/courses/CRS.126462.2019.S1/project1%281%29.pdf

#include <stdio.h>

char encryptRotationCypher(char *cypherText, int rotationAmount);

void main() {
    FILE *input, *output;
    char cypherText[1024], outputText[1024];
    int i = 0, selector, rotationAmount;

    // Initialise input & output files.
    output = fopen("Resources/output.txt", "w");
    input = fopen("Resources/input.txt", "r");
    if (input == NULL) {
        perror("File Input");
    }

    // Read input into char array cypherText.
    while (!feof(input)) {
        fscanf(input, "%c", &cypherText[i]);
        i++;
    }

    printf("1. Rotation Cypher Encryption\n2. Exit Programme\n3. UNDEFINED\n");
    printf("Please Make a Selection: \n");
    scanf("%d", &selector);

    switch(selector){
        case 1:
            printf("Please enter rotation amount: \n");
            scanf("%d", &rotationAmount);
            encryptRotationCypher(&cypherText, rotationAmount);
            break;
        case 2:
            printf("Case 2.\n");
            break;
        case 3:
            printf("Case 3.\n");
            break;
        case 4:
            printf("Case 4.\n");
            break;
        default:
            printf("Please Enter a Valid Selection.\n");
            break;
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
            if(cypherText[i] <= 65)
                cypherText[i] = 90 - rotationAmount;
            if(cypherText[i] >= 90)
                cypherText[i] = 65 - rotationAmount;
            cypherText[i] += rotationAmount;
            result[i] = cypherText[i];
        }
    }
    return result;
}