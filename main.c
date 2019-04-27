// Matthew Maiden
// C3304875
// ENGG1003 Assignment 1
// Specification Document: https://uonline.newcastle.edu.au/bbcswebdav/pid-4089777-dt-content-rid-20660523_1/courses/CRS.126462.2019.S1/project1%281%29.pdf

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int encryptRotationCipher(const char *messageText, char *outputText, int rotationAmount);
int decryptRotationCipher(const char *messageText, char *outputText, int rotationAmount);
int encryptSubstitutionCipher(const char *messageText, const char *key, char *outputText);
int decryptSubstitutionCipher(const char *messageText, const char *key, char *outputText);

int main() {
   FILE *input, *output;
   char messageText[1024], outputText[1024], scanInput[2048], key[128], *ptr;
   int i = 0, j = 0, selector, rotationAmount, nCount = 0;

   // Initialise input & output files.
   output = fopen("Resources/output.txt", "w");
   input = fopen("Resources/input.txt", "r");
   if (input == NULL)
      perror("File Input");

   // Read input into char array messageText.
   while (!feof(input)) {
      fscanf(input, "%c", &scanInput[i]);
      if (scanInput[i] == '\n') {
         nCount++;
      }
      if (nCount == 0)
         messageText[i] = scanInput[i];
      if (nCount == 1 && scanInput[i] != '\n') {
         key[j] = scanInput[i];
         j++;
      }
      i++;
   }

   rotationAmount = strtol(key, &ptr, 10);

   printf("\n1. Rotation Cipher Encryption\n2. Rotation Cipher Decryption\n");
   printf("3. Substitution Cipher Encryption\n4. Substitution Cipher Decryption\n");
   printf("\nPlease Make a Selection: \n");
   scanf("%d", &selector);
   while (selector < 1 || selector > 4) {
      printf("\nPlease select 1, 2, 3 or 4: \n");
      scanf("%d", &selector);
   }

   switch (selector) {

      case 1:
         printf("\nKey: %d\n\n", rotationAmount);
         encryptRotationCipher(messageText, outputText, rotationAmount);
         break;
      case 2:
         printf("\n1. Decipher with key\n2. Decipher without key\n");
         scanf("%d", &selector);
         while (selector != 1 && selector != 2) {
            printf("\nPlease select 1 or 2: \n");
            scanf("%d", &selector);
         }
         if (selector == 1) {
            printf("Key: %d\n", rotationAmount);
            decryptRotationCipher(messageText, outputText, rotationAmount);
            break;
         }
         if (selector == 2) {
            rotationAmount = 0;
            decryptRotationCipher(messageText, outputText, rotationAmount);
            while (strstr(outputText, " A ") == NULL && strstr(outputText, " THE ") == NULL) {
               rotationAmount++;
               decryptRotationCipher(messageText, outputText, rotationAmount);
            }
            printf("\nGenerated Key: %d\n\n", rotationAmount);
            break;
         }
      case 3:
         if (key[16] < 65 || key[16] > 90) {
            printf("\nERROR: INCORRECT KEY FORMAT");
            printf("\nKey: %s\n", key);
            exit(1);
         }
         encryptSubstitutionCipher(messageText, key, outputText);
         printf("\nKey: %s\n\n", key);
         break;
      case 4:
         if (key[16] < 65 || key[16] > 90) {
            printf("\nERROR: INCORRECT KEY FORMAT");
            printf("\nKey: %s\n", key);
            exit(1);
         }
         decryptSubstitutionCipher(messageText, key, outputText);
         printf("\nKey: %s\n\n", key);
         break;
   }
   printf("Message Text: \n");
   for (i = 0; messageText[i] != '\0'; i++) {
      printf("%c", messageText[i]);
   }
   printf("\n\n");
   printf("Output Text: \n");
   for (i = 0; messageText[i] != '\0'; i++) {
      printf("%c", outputText[i]);
      fprintf(output, "%c", outputText[i]);
   }
   printf("\n");
   fclose(stdin);

   return 0;
}

int encryptRotationCipher(const char *messageText, char *outputText, int rotationAmount) { // e(x) = (m + k)(mod 26)
   int i;

   for (i = 0; messageText[i] != '\0'; i++) {
      if (messageText[i] >= 'A' && messageText[i] <= 'Z') {
         outputText[i] = messageText[i] + (rotationAmount % 26);
         if (outputText[i] > 'Z')
            outputText[i] = ('A' - 1 + (outputText[i] - 'Z') % 26);
         if (outputText[i] < 'A')
            outputText[i] = ('Z' - 1 + (outputText[i] - 'A') % 26);
      }
      else
         outputText[i] = messageText[i]; // Skips any non-alphabet character
   }
   return 0;
}

int decryptRotationCipher(const char *messageText, char *outputText, int rotationAmount) { // d(c) = (c − k)(mod 26)
   int i;

   for (i = 0; messageText[i] != '\0'; i++) {
      if (messageText[i] >= 'A' && messageText[i] <= 'Z') {
         outputText[i] = messageText[i] - (rotationAmount % 26);
         if (outputText[i] > 'Z')
            outputText[i] = ('A' + 1 + (outputText[i] - 'Z') % 26);
         if (outputText[i] < 'A')
            outputText[i] = ('Z' + 1 + (outputText[i] - 'A') % 26);
      }
      else
         outputText[i] = messageText[i]; // Skips any non-alphabet characters
   }
   return 0;
}

int encryptSubstitutionCipher(const char *messageText, const char *key, char *outputText) {
   int position[1024], i;

   for (i = 0; messageText[i] != '\0'; i++) {
      if (messageText[i] >= 'A' && messageText[i] <= 'Z') {
         position[i] = messageText[i] - 65;
         outputText[i] = key[position[i]];
      }
      else
         outputText[i] = messageText[i];
   }
   return 0;
}

int decryptSubstitutionCipher(const char *messageText, const char *key, char *outputText) {
   const char orig[26] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
   char oldLetter, newLetter;

   int i, j, k = 0;

   for (i = 0; messageText[i] != '\0'; i++) {
      oldLetter = key[i];
      newLetter = orig[i];
      if (messageText[i] >= 'A' && messageText[i] <= 'Z') {
         for (j = 0; j < 1025; j++) {
            if (messageText[i] == oldLetter) {
               outputText[i] = newLetter;
               break;
            }
            else {
               j++;
               oldLetter = key[k];
               newLetter = orig[k];
               k++;
               if (k > 25)
                  k = 0;
            }
         }
      }
      else
         outputText[i] = messageText[i];
   }
   return 0;
}