/* Program that cracks passwords hashed with the C’s DES-based (not MD5-based) crypt function.
   Program accepts a single command line argument, the hashed password
   Concept: this is the original function crypt(key1, salt) = hash
    salt is the first 2 chars of the hash
    given the known hash and salt we will try to find key1 using
    crypt(key2, salt) = hash, if we find the matching hash then
    key1 == key2
    Note: Program is designed to find passwords up to 5 characters
    Program assumes passwords are alphabetic characters only.
    The letters are ordered based on the letter frequency in the english alphabet

    The crack time varies on the machine, test taked proved a cracking time of aprox:
    1-1+1/2 min to completely iterate through each posible last letter
    Worst case scenario: last letter "Z" which will force the program to test
    all letters beforehand.
    Finding a word with last letter "d" took aprox 20 mins.

    TODO: change structure of imbricated if's to a recursive function design
          posibly add a dictionary with the most frequent words. */


#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./vigenere k\n");
        exit(1);
    }  //check that only 1 command line arg is passed
    char *keyword = argv[1];
    char salt[3];
    salt[0] = keyword[0];
    salt[1] = keyword[1];
    salt[2] = 0;
    char *alphabets = "eEtTaAoOiInNsShHrRdDlLcCuUmMwWfFgGyYpPbBvVkKjJxXqQzZ"; //english letter frequency order
    int digits = 1;

    for (int w = 0; w < strlen(alphabets) + 1; w++ ) // iterate through 5th digit
    {
        digits = ( w > 0 && digits < 5) ? 5 : digits; // this condition ensures that once this is incremented
                                                      // the program wont be trying 4 letter keys, already tried before,
                                                      // same goes for the conditions bellow
        printf("trying with last letter %c\n", alphabets[w]);

        for (int x = 0; x < strlen(alphabets); x++) // iterate through fourth digit
        {
            digits = (x > 0 && digits < 4) ? 4 : digits;

            for (int y = 0; y < strlen(alphabets); y++) //iterate through third digit
            {
                digits = (y > 0 && digits < 3) ? 3 : digits;

                for (int z = 0; z < strlen(alphabets); z++) //iterate through second digit
                {
                    digits = (z > 0 && digits < 2) ? 2 : digits;

                    for (int i  = 0; i < strlen(alphabets); i++) // iterate through first letter
                    {
                        char pass[digits+1];
                        pass[0] = alphabets[i];
                        if ( digits == 1)
                        {
                            pass[1] = 0;
                        }
                        else if ( digits == 2)
                        {
                            pass[1] = alphabets[z];
                        }
                        else if (digits == 3)
                        {
                            pass[1] = alphabets[z];
                            pass[2] = alphabets[y];
                        }
                        else if (digits == 4)
                        {
                            pass[1] = alphabets[z];
                            pass[2] = alphabets[y];
                            pass[3] = alphabets[x];
                        }
                        else if (digits == 5)
                        {
                            pass[1] = alphabets[z];
                            pass[2] = alphabets[y];
                            pass[3] = alphabets[x];
                            pass[4] = alphabets[w-1]; // w-1 is because using normal w value will make program
                                                     // skip first letter, in this case 'e'
                        }
                        pass[digits] = 0;
                        char *output = crypt(pass, salt);
                        if (strcmp(output, keyword) == 0)
                        {
                            printf("\npass is %s", pass);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}