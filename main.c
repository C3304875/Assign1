// Matthew Maiden
// C3304875
// ENGG1003 Assignment 1
// Specification Document: https://uonline.newcastle.edu.au/bbcswebdav/pid-4089777-dt-content-rid-20660523_1/courses/CRS.126462.2019.S1/project1%281%29.pdf

#include <stdio.h>
#include <string.h>

void encryptRotationCipher(const char *cipherText, char *outputText, int rotationAmount);
void decryptRotationCipher(const char *cipherText, char *outputText, int rotationAmount);
void encryptSubstitutionCipher(const char *cipherText, char *outputText);
void decryptSubstitutionCipher(const char *cipherText, char *outputText);

int main() {
   FILE *input, *output;
   char cipherText[1024], outputText[1024];
   int i, selector, rotationAmount;

   // Initialise input & output files.
   output = fopen("Resources/output.txt", "w");
   input = fopen("Resources/input.txt", "r");
   if (input == NULL)
      perror("File Input");

   // Read input into char array cipherText.
   while (!feof(input)) {
      fscanf(input, "%c", &cipherText[i]);
      i++;
   }

   printf("\n1. Rotation Cipher Encryption\n2. Rotation Cipher Decryption\n");
   printf("3. Substitution Cipher Encryption\n4. Substitution Cipher Decryption\n");
   printf("\nPlease Make a Selection: \n");
   scanf("%d", &selector);

   switch (selector) {
      case 1:
         printf(" \nPlease enter rotation amount between 0 & 25:");
         scanf("%d", &rotationAmount);
         encryptRotationCipher(cipherText, outputText, rotationAmount);
         break;
      case 2:
         printf("1. Decipher with key\n2. Decipher without key\n");
         scanf("%d", &selector);
         if (selector == 1) {
            printf("Please enter rotation amount between 0 & 25:\n");
            scanf("%d", &rotationAmount);
            decryptRotationCipher(cipherText, outputText, rotationAmount);
            break;
         }
         else {
            rotationAmount = 0;
            decryptRotationCipher(cipherText, outputText, rotationAmount);
            while (strstr(outputText, " A ") == NULL && strstr(outputText, " THE ") == NULL) {
               rotationAmount++;
               decryptRotationCipher(cipherText, outputText, rotationAmount);
            }
            break;
         }
      case 3:
         encryptSubstitutionCipher(cipherText, outputText);
         break;
      case 4:
         decryptSubstitutionCipher(cipherText, outputText);
         break;
      default:
         printf("Please Enter a Valid Selection.\n");
         break;
   }
   printf("\n");
   for (i = 0; cipherText[i] != '\0'; i++) {
      printf("%c", outputText[i]);
      fprintf(output, "%c", outputText[i]);
   }
}

void encryptRotationCipher(const char *cipherText, char *outputText, int rotationAmount) { // e(x) = (m + k)(mod 26)
   int i;

   for (i = 0; cipherText[i] != '\0'; i++) {
      if (cipherText[i] >= 'A' && cipherText[i] <= 'Z') {
         outputText[i] = cipherText[i] + (rotationAmount % 26);
         if (outputText[i] > 'Z')
            outputText[i] = ('A' - 1 + (outputText[i] - 'Z') % 26);
         if (outputText[i] < 'A')
            outputText[i] = ('Z' - 1 + (outputText[i] - 'A') % 26);
      }
      else
         outputText[i] = cipherText[i]; // Skips any non-alphabet character
   }
}

void decryptRotationCipher(const char *cipherText, char *outputText, int rotationAmount) { // d(c) = (c − k)(mod 26)
   int i;

   for (i = 0; cipherText[i] != '\0'; i++) {
      if (cipherText[i] >= 'A' && cipherText[i] <= 'Z') {
         outputText[i] = cipherText[i] - (rotationAmount % 26);
         if (outputText[i] > 'Z')
            outputText[i] = ('A' + 1 + (outputText[i] - 'Z') % 26);
         if (outputText[i] < 'A')
            outputText[i] = ('Z' + 1 + (outputText[i] - 'A') % 26);
      }
      else
         outputText[i] = cipherText[i]; // Skips any non-alphabet characters
   }
}

void encryptSubstitutionCipher(const char *cipherText, char *outputText) {
   const char sub[26] = {"QAZXSWEDCVFRTGBNHYUJMKILOP"};
   int position[1024], i;

   for (i = 0; cipherText[i] != '\0'; i++) {
      if (cipherText[i] >= 'A' && cipherText[i] <= 'Z') {
         position[i] = cipherText[i] - 65;
         outputText[i] = sub[position[i]];
      }
      else
         outputText[i] = cipherText[i];
   }
}

void decryptSubstitutionCipher(const char *cipherText, char *outputText) {
   const char orig[26] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}, sub[26] = {"QAZXSWEDCVFRTGBNHYUJMKILOP"};
   char oldLetter, newLetter;

   int i, j, k = 0;

   for (i = 0; cipherText[i] != '\0'; i++) {
      oldLetter = sub[i];
      newLetter = orig[i];
      if (cipherText[i] >= 'A' && cipherText[i] <= 'Z') {
         for (j = 0; j < 1025; j++) {
            if (cipherText[i] == oldLetter) {
               outputText[i] = newLetter;
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
         outputText[i] = cipherText[i];
   }
}