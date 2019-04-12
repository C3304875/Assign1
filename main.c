// ENGG1003 Assignment 1
// Specification Document: https://uonline.newcastle.edu.au/bbcswebdav/pid-4089777-dt-content-rid-20660523_1/courses/CRS.126462.2019.S1/project1%281%29.pdf

#include <stdio.h>

void encryptRotationCypher(const char *cypherText, char *outputText, int rotationAmount);
void decryptRotationCypher(const char *cypherText, char *outputText, int rotationAmount);

void main(){
   FILE *input, *output;
   char cypherText[1024], outputText[1024];
   int i = 0, selector, rotationAmount;

   // Initialise input & output files.
   output = fopen("Resources/output.txt", "w");
   input = fopen("Resources/input.txt", "r");
   if (input == NULL){
      perror("File Input");
   }

   // Read input into char array cypherText.
   while (!feof(input)){
      fscanf(input, "%c", &cypherText[i]);
      i++;
   }

   printf("1. Rotation Cypher Encryption\n2. Rotation Cypher Decryption\n3. Exit Programme\n4. UNDEFINED\n");
   printf("Please Make a Selection: \n");
   scanf("%d", &selector);

   switch (selector){
      case 1:
         printf("Please enter rotation amount between -26 & 26: \n");
         scanf("%d", &rotationAmount);
         encryptRotationCypher(&cypherText, &outputText, rotationAmount);
         break;
      case 2:
         printf("Please enter rotation amount between -26 & 26: \n");
         scanf("%d", &rotationAmount);
         decryptRotationCypher(&cypherText, &outputText, rotationAmount);
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
   for (i = 0; cypherText[i] != '\0'; i++){
      printf("%c", outputText[i]);
   }
}

void encryptRotationCypher(const char *cypherText, char *outputText, int rotationAmount){ // e(x) = (m + k)(mod 26)
   int i;

   for (i = 0; cypherText[i] != '\0'; i++){
      if (cypherText[i] >= 'A' && cypherText[i] <= 'Z'){
         outputText[i] = cypherText[i] + (rotationAmount % 26);
         if (cypherText[i] > 'Z'){
            outputText[i] = 'A' + (rotationAmount % 26);
         }
         if (outputText[i] < 'A'){
            outputText[i] = ('Z' - rotationAmount)  + (rotationAmount % 26);
         }
      }
      else {
         outputText[i] = cypherText[i]; // Skips any non-alphabet characters
      }
   }
}

void decryptRotationCypher(const char *cypherText, char *outputText, int rotationAmount){ // d(c) = (c − k)(mod 26)
   int i;

   for (i = 0; cypherText[i] != '\0'; i++){
      if (cypherText[i] >= 'A' && cypherText[i] <= 'Z'){
         outputText[i] = cypherText[i] - (rotationAmount % 26);
         if (cypherText[i] >= 'Z'){
            outputText[i] = 'A' + (rotationAmount % 26);
            break;
         }
         if (cypherText[i] < 'A'){
            outputText[i] = ('Z' - rotationAmount)  + (rotationAmount % 26);
            break;
         }
      }
      else {
         outputText[i] = cypherText[i]; // Skips any non-alphabet characters
      }
   }
}