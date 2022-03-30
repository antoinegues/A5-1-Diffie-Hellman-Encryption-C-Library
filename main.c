#include <stdio.h>
#include <stdlib.h>

#define STRING_SIZE 256

#include "a51.h"

char *input_key() {
    char *key = calloc(KEY_SIZE, sizeof(unsigned char));
    printf("Please insert the key : \n");
    fgets(key, KEY_SIZE, stdin);
    printf("%s", key);
    return key;
}


int main() {
    char *string = calloc(STRING_SIZE, sizeof(char));
    char *key = "victor!bg";
    Registers registers = init(key);
    printf("Please enter the message you wish to encrypt/decrypt (LIMIT 255): ");
    fgets(string, STRING_SIZE, stdin);
    char *cyphered_string = cypher_string(registers, string);
    printf("%s\n", cyphered_string);
    free(registers);
    free(cyphered_string);
    free(string);
    return 0;
}
