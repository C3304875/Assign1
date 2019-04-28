/* Matthew Maiden
 * C3304875
 * ENGG1003 Assignment 1
 *
 * This program receives an ASCII message input and performs encryption/decryption.
 * The key must be appropriate to the desired process. For example:
 * An integer value key (0-26) must be used to perform a rotation cipher.
 * A substitution alphabet key must be used to perform a substitution cipher.
 *
 * Rules for input.txt:
 * Line 1: Message text to be encrypted/decrypted.
 * Line 2: Key to be used.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int encryptRotationCipher(const char *messageText, char *outputText, int rotationAmount);
int decryptRotationCipher(const char *messageText, char *outputText, int rotationAmount);
int encryptSubstitutionCipher(const char *messageText, const char *key, char *outputText);
int decryptSubstitutionCipher(const char *messageText, const char *key, char *outputText);
int decryptSubstitutionKeyless(const char *messageText, char *outputText);

int main() {
   FILE *input, *output;
   char messageText[1024], outputText[1024], scanInput[2048], key[27], *ptr;
   int i = 0, j = 0, selector, rotationAmount, nCount = 0, error;

   /* Initialise input & output files. */
   output = fopen("resources/output.txt", "w");
   input = fopen("resources/input.txt", "r");
   if (input == NULL)
      perror("File Input");

   /* Read input into char array messageText. */
   while (!feof(input)) {
      fscanf(input, "%c", &scanInput[i]);
      if (scanInput[i] == '\n') {
         nCount++;
      }
      if (nCount == 0) /* nCount used to keep track of how many newline characters */
         messageText[i] = scanInput[i];
      if (nCount == 1 && scanInput[i] != '\n') {
         key[j] = scanInput[i];
         j++;
      }
      i++;
   }

   rotationAmount = strtol(key, &ptr, 10); /* Assign the int value of "key" to rotationAmount */

   printf("\n1. Rotation Cipher Encryption\n2. Rotation Cipher Decryption\n");

   printf("3. Substitution Cipher Encryption\n4. Substitution Cipher Decryption\n");
   printf("\nPlease Make a Selection: \n");
   scanf("%d", &selector); /* Variable to store the users choice */
   while (selector < 1 || selector > 4) { /* Basic error checking */
      printf("\nPlease select 1, 2, 3 or 4: \n");
      scanf("%d", &selector);
   }

   switch (selector) {
      case 1:
         printf("\nKey: %d\n\n", rotationAmount);
         encryptRotationCipher(messageText, outputText, rotationAmount);
         break;
      case 2:
         /* Task selection from stdin, uses predefined key if given */
         printf("\n1. Decipher with key\n2. Decipher without key\n");
         scanf("%d", &selector);
         while (selector != 1 && selector != 2) { /* Basic error checking */
            printf("\nPlease select 1 or 2: \n");
            scanf("%d", &selector);
         }
         if (selector == 1) { /* Call function using a predefined key */
            printf("\nKey: %d\n\n", rotationAmount);
            decryptRotationCipher(messageText, outputText, rotationAmount);
            break;
         }
         if (selector == 2) { /* Incrementally generate a key and test it */
            rotationAmount = 0;
            decryptRotationCipher(messageText, outputText, rotationAmount);
            /* Check existence of string within new output, exit if found */
            while (strstr(outputText, " A ") == NULL && strstr(outputText, " THE ") == NULL) {
               rotationAmount++;
               decryptRotationCipher(messageText, outputText, rotationAmount);
            }
            printf("\nGenerated Key: %d\n\n", rotationAmount);
            break;
         }
      case 3:
         /* Assign the return value to "error", exit if 1, output if 0 */
         error = encryptSubstitutionCipher(messageText, key, outputText);
         if (error == 1)
            exit(error);
         printf("\nKey: %s\n\n", key);
         break;
      case 4:
         /* Assign the return value to "error", exit if 1, output if 0 */
         error = decryptSubstitutionCipher(messageText, key, outputText);
         if (error == 1)
            exit(error);
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

   return error;
}

int encryptRotationCipher(const char *messageText, char *outputText, int rotationAmount) { /* e(x) = (m + k)(mod 26)*/
   int i;

   for (i = 0; messageText[i] != '\0'; i++) {
      if (messageText[i] >= 'A' && messageText[i] <= 'Z') { /* Only process uppercase characters */
         outputText[i] = messageText[i] + (rotationAmount % 26); /* Run algorithm on the character */
         if (outputText[i] > 'Z')
            outputText[i] = ('A' - 1 + (outputText[i] - 'Z') % 26);
         if (outputText[i] < 'A')
            outputText[i] = ('Z' - 1 + (outputText[i] - 'A') % 26);
      }
      else
         outputText[i] = messageText[i]; /* Skip any non-alphabet character */
   }
   return 0;
}

int decryptRotationCipher(const char *messageText, char *outputText, int rotationAmount) { /* d(c) = (c − k)(mod 26) */
   int i;

   for (i = 0; messageText[i] != '\0'; i++) {
      if (messageText[i] >= 'A' && messageText[i] <= 'Z') { /* Only process uppercase characters */
         outputText[i] = messageText[i] - (rotationAmount % 26); /* Run algorithm on the character */
         if (outputText[i] > 'Z')
            outputText[i] = ('A' + 1 + (outputText[i] - 'Z') % 26);
         if (outputText[i] < 'A')
            outputText[i] = ('Z' + 1 + (outputText[i] - 'A') % 26);
      }
      else
         outputText[i] = messageText[i]; /* Skip any non-alphabet characters */
   }
   return 0;
}

int encryptSubstitutionCipher(const char *messageText, const char *key, char *outputText) {
   int position[1024], i;

   /* Perform basic error checking on an arbitrary value of "key" */
   if (key[16] < 65 || key[16] > 90) {
      printf("\nError: Incorrect key format");
      printf("\nKey: %s\n", key);
      return 1; /* Exit function, returning 1 to "error" */
   }

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

   /* Perform basic error checking on an arbitrary value of "key" */
   if (key[16] < 65 || key[16] > 90) {
      printf("\nError: Incorrect key format");
      printf("\nKey: %s\n", key);
      return 1; /* Exit function, returning 1 to "error" */
   }

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

int decryptSubstitutionKeyless(const char *messageText, char *outputText){

   return 0;
}