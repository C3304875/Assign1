#include <stdio.h>

int main() {
    FILE *input;

    input = fopen("input.txt", "r");
    if(input == NULL){
        perror("File Input");
    }

    return 0;
}