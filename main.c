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

int main() {
   FILE *input, *output;
   char messageText[1024], outputText[1024], scanInput[1024], key[26];
   int i, selector, rotationAmount, error;

   /* Initialise input & output files. */
   input = fopen("resources/input.txt", "r");
   output = fopen("resources/output.txt", "w");
   if (input == NULL)
      perror("File Input");

   /* Read input into char array messageText. */
   while (!feof(input)) {
      for (i = 0; fscanf(input, "%c", &messageText[i]) != -1; i++){
         if (messageText[i] == '\n')
            break; /* Exit loop if '\n' found */
      }
      for (i = 0; fscanf(input, "%c", &key[i]) != -1; i++){ /* Scan key until end of file */
      }
   }

   rotationAmount = strtol(key, &scanInput, 10); /* Assign the int value of "key" to rotationAmount */

   printf("\n1. Rotation Cipher Encryption\n2. Rotation Cipher Decryption\n");

   printf("3. Substitution Cipher Encryption\n4. Substitution Cipher Decryption\n");
   printf("\nPlease Make a Selection: \n");
   scanf("%d", &selector); /* Variable to store the users choice */
   while (selector < 1 || selector > 5) { /* Basic error checking */
      printf("\nPlease select 1, 2, 3, 4 or 5: \n");
      scanf("%d", &selector);
   }

   switch (selector) {
      case 1:
         printf("\nKey: %d\n\n", rotationAmount);
         fprintf(output, "Key: %d\n\n", rotationAmount);
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
            fprintf(output, "Key: %d\n\n", rotationAmount);
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
            fprintf(output, "Generated Key: %d\n\n", rotationAmount);
            break;
         }
      case 3:
         /* Assign the return value to "error", exit if 1, output if 0 */
         error = encryptSubstitutionCipher(messageText, key, outputText);
         if (error == 1)
            exit(error);
         printf("\nKey: %.26s\n\n", key);
         fprintf(output, "Key: %.26s\n\n", key);
         break;
      case 4:
         /* Assign the return value to "error", exit if 1, output if 0 */
         error = decryptSubstitutionCipher(messageText, key, outputText);
         if (error == 1)
            exit(error);
         printf("\nKey: %.26s\n\n", key);
         fprintf(output, "Key: %.26s\n\n", key);
         break;
   }

   printf("Message Text: \n");
   fprintf(output, "Message Text: \n");
   for (i = 0; messageText[i] != '\0'; i++) {
      printf("%c", messageText[i]);
      fprintf(output, "%c", messageText[i]);
   }
   printf("\nOutput Text: \n");
   fprintf(output, "\nOutput Text: \n");
   for (i = 0; messageText[i] != '\0'; i++) {
      printf("%c", outputText[i]);
      fprintf(output, "%c", outputText[i]);
   }

   fclose(input);

   return error;
}

int encryptRotationCipher(const char *messageText, char *outputText, int rotationAmount) { /* e(x) = (m + k)(mod 26)*/
   int i;

   for (i = 0; messageText[i] != '\0'; i++) {
      if (messageText[i] >= 'A' && messageText[i] <= 'Z') { /* Only process uppercase characters */
         outputText[i] = messageText[i] + (rotationAmount % 26); /* Run algorithm on the character */
         if (outputText[i] > 'Z')                                                /* A simple algorithm is used */
            outputText[i] = ('A' - 1 + (outputText[i] - 'Z') % 26);              /* to change the value of a   */
         if (outputText[i] < 'A')                                                /* character with reference to*/
            outputText[i] = ('Z' - 1 + (outputText[i] - 'A') % 26);              /* a "key" which modifies 'k'.*/
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
         if (outputText[i] > 'Z')                                                /* This function receives a char   */
            outputText[i] = ('A' + 1 + (outputText[i] - 'Z') % 26);              /* from messageText[] and performs */
         if (outputText[i] < 'A')                                                /* the above algorithm to achieve  */
            outputText[i] = ('Z' + 1 + (outputText[i] - 'A') % 26);              /* an altered outputText[]         */
      }
      else
         outputText[i] = messageText[i]; /* Skip any non-alphabet characters */
   }
   return 0;
}

int encryptSubstitutionCipher(const char *messageText, const char *key, char *outputText) {
   int position[1024], i;

   /* Perform basic error checking on an arbitrary value of "key" */
   if (key[16] < 65 || key[16] > 90) {                              /* This function receives a string  */
      printf("\nError: Incorrect key format");                      /* Once received, a character from  */
      printf("\nKey: %s\n", key);                                   /* Once received, the character is  */
      return 1; /* Exit function, returning 1 to "error" */         /* checked and then given a         */
   }                                                                /* position in an array. That       */
                                                                    /* position is then transferred over*/
   for (i = 0; messageText[i] != '\0'; i++) {                       /* to a new array containing a key. */
      if (messageText[i] >= 'A' && messageText[i] <= 'Z') {         /* A new string is then created     */
         position[i] = messageText[i] - 65;                         /* from that array with reference   */
         outputText[i] = key[position[i]];                          /* to the characters original index.*/
      }
      else
         outputText[i] = messageText[i];
   }
   return 0;
}

int decryptSubstitutionCipher(const char *messageText, const char *key, char *outputText) {
   const char orig[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
   char oldLetter, newLetter;

   /* Perform basic error checking on an arbitrary value of "key" */
   if (key[16] < 65 || key[16] > 90) {
      printf("\nError: Incorrect key format");
      printf("\nKey: %s\n", key);                                   /* This function receives a string  */
      return 1; /* Exit function, returning 1 to "error" */         /* Once received, a character from  */
   }                                                                /* the message is cross-referenced  */
                                                                    /* with a character from the orig[] */
   int i, j, k = 0;                                                 /* array. If the result is true,    */
                                                                    /*  the letter from orig[] is put   */
   for (i = 0; messageText[i] != '\0'; i++) {                       /* into outputText[]. If not true,  */
      oldLetter = key[i]; // Set a letter to check                  /* oldLetter & newLetter are        */
      newLetter = orig[i]; // Check against this letter             /* incremented. 'k' is used to keep */
      if (messageText[i] >= 'A' && messageText[i] <= 'Z') {         /* track of those increments.       */
         for (j = 0; j < 2048; j++) {
            if (messageText[i] == oldLetter) {
               outputText[i] = newLetter;
               break;
            }
            else {
               oldLetter = key[k];
               newLetter = orig[k];
               k++;
               if (k > 25)
                  k = 0;
            }
         }
      }
      else
         outputText[i] = messageText[i]; /* Skip non-alphabet characters */
   }
   return 0;
}