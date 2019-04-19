// Matthew Maiden
// C3304875
// ENGG1003 Assignment 1
// Specification Document: https://uonline.newcastle.edu.au/bbcswebdav/pid-4089777-dt-content-rid-20660523_1/courses/CRS.126462.2019.S1/project1%281%29.pdf

#include <stdio.h>

void encryptRotationCypher(const char *cypherText, char *outputText, int rotationAmount);
void decryptRotationCypher(const char *cypherText, char *outputText, int rotationAmount);
void encryptSubstitutionCypher(const char *cypherText, char *outputText);
void decryptSubstitutionCypher(const char *cypherText, char *outputText);

int main() {
   FILE *input, *output;
   char cypherText[1024], outputText[1024];
   int i = 0, selector = 0, rotationAmount;

   // Initialise input & output files.
   output = fopen("Resources/output.txt", "w");
   input = fopen("Resources/input.txt", "r");
   if (input == NULL)
      perror("File Input");

   // Read input into char array cypherText.
   for (i = 0; cypherText[i] != feof(input); i++){
      fscanf(input, "%c", &cypherText[i]);
   }

   printf("\n1. Rotation Cypher Encryption\n2. Rotation Cypher Decryption\n");
   printf("3. Substitution Cypher Encryption\n4. Substitution Cypher Decryption\n");
   printf("\nPlease Make a Selection: \n");
   scanf("%d", &selector);

   switch (selector) {
      case 1:
         printf("Please enter rotation amount between 0 & 25: \n");
         scanf("%d", &rotationAmount);
         encryptRotationCypher(cypherText, outputText, rotationAmount);
         break;
      case 2:
         printf("Please enter rotation amount between 0 & 25: \n");
         scanf("%d", &rotationAmount);
         decryptRotationCypher(cypherText, outputText, rotationAmount);
         break;
      case 3:
         encryptSubstitutionCypher(cypherText, outputText);
         break;
      case 4:
         decryptSubstitutionCypher(cypherText, outputText);
         break;
      default:
         printf("Please Enter a Valid Selection.\n");
         break;
   }
   printf("\n");
   for (i = 0; cypherText[i] != '\0'; i++){
      printf("%c", outputText[i]);
   }
}

void encryptRotationCypher(const char *cypherText, char *outputText, int rotationAmount) { // e(x) = (m + k)(mod 26)
   int i;

   for (i = 0; cypherText[i] != '\0'; i++) {
      if (cypherText[i] >= 'A' && cypherText[i] <= 'Z') {
         outputText[i] = cypherText[i] + (rotationAmount % 26);
         if (outputText[i] > 'Z')
            outputText[i] = ('A' - 1 + (outputText[i] - 'Z') % 26);
         if (outputText[i] < 'A')
            outputText[i] = ('Z' - 1 + (outputText[i] - 'A') % 26);
      }
      else
         outputText[i] = cypherText[i]; // Skips any non-alphabet character
   }
}

void decryptRotationCypher(const char *cypherText, char *outputText, int rotationAmount) { // d(c) = (c − k)(mod 26)
   int i;

   for (i = 0; cypherText[i] != '\0'; i++) {
      if (cypherText[i] >= 'A' && cypherText[i] <= 'Z') {
         outputText[i] = cypherText[i] - (rotationAmount % 26);
         if (outputText[i] > 'Z')
            outputText[i] = ('A' + 1 + (outputText[i] - 'Z') % 26);
         if (outputText[i] < 'A')
            outputText[i] = ('Z' + 1 + (outputText[i] - 'A') % 26);
      }
      else
         outputText[i] = cypherText[i]; // Skips any non-alphabet characters
   }
}

void encryptSubstitutionCypher(const char *cypherText, char *outputText) {
   const char sub[26] = {"QAZXSWEDCVFRTGBNHYUJMKILOP"};
   int position[1024], i;

   for (i = 0; cypherText[i] != '\0'; i++) {
      if (cypherText[i] >= 'A' && cypherText[i] <= 'Z') {
         position[i] = cypherText[i] - 65;
         outputText[i] = sub[position[i]];
      }
      else
         outputText[i] = cypherText[i];
   }
}

void decryptSubstitutionCypher(const char *cypherText, char *outputText) {
   const char orig[26] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}, sub[26] = {"QAZXSWEDCVFRTGBNHYUJMKILOP"};
   char oldLetter, newLetter;

   int i, j, k = 0;

   for (i = 0; cypherText[i] != '\0'; i++) {
      oldLetter = sub[i];
      newLetter = orig[i];
      if (cypherText[i] >= 'A' && cypherText[i] <= 'Z') {
         for (j = 0; j < 100; j++) {
            if (cypherText[i] == oldLetter) {
               outputText[i] = newLetter;
               printf("%d", outputText[i]);
               break;
            }
            else {
               j++;
               oldLetter = sub[k];
               newLetter = orig[k];
               k++;
               if (k > 25)
                  k = 0;
            }
         }
      }
      else
         outputText[i] = cypherText[i];
   }
}