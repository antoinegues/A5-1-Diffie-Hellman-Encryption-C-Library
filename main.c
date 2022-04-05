#include <stdio.h>
#include <stdlib.h>

#define STRING_SIZE 256

#include "minunit.h"

#include "test/a51_test.c"

//char *input_key() {
//    char *key = calloc(KEY_BYTE_SIZE, sizeof(unsigned char));
//    printf("Please insert the key : \n");
//    fgets(key, KEY_BYTE_SIZE, stdin);
//    printf("%s", key);
//    return key;
//}

int main() {
    MU_RUN_SUITE(a51_test_suite);
    MU_REPORT();

    char *string = calloc(STRING_SIZE, sizeof(char));
    char *key = "victor!bg";
    Registers registers = init(key);
    printf("Please enter the message you wish to encrypt/decrypt (LIMIT 255): ");
    fgets(string, STRING_SIZE, stdin);
    char *cyphered_string = cypher_string(registers, string);
    printf("%s\n", cyphered_string);

    registers = init(key);
    char* decyphered_string = cypher_string(registers, cyphered_string);
    printf("%s\n", decyphered_string);

    free(registers.lfsrs);
    free(registers.block_counter);
    free(cyphered_string);
    free(decyphered_string);
    free(string);

    return MU_EXIT_CODE;
}
