#include <stdio.h>

const char cypher();
const char decypher();

void main() {
    FILE *input;
    char inputText[1024];

    input = fopen("Resources/input.txt", "r");
    if(input == NULL){
        perror("File Input");
    }

    fscanf(input, "%[^\n]", inputText);
    printf("%s", &inputText);


}


