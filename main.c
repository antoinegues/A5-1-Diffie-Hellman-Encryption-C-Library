#include <stdio.h>
#include <stdlib.h>

#define STRING_SIZE 256

#include "minunit.h"

#include "diffie_hellman.h"

#include "test/a51_test.c"

char *input_key() {
    char *key = calloc(KEY_BYTE_SIZE, sizeof(unsigned char));
    printf("Please insert the key : \n");
    fgets(key, KEY_BYTE_SIZE, stdin);
    printf("%s", key);
    return key;
}

void a51() {

    MU_RUN_SUITE(a51_test_suite);
    MU_REPORT();

    char *string = calloc(STRING_SIZE, sizeof(char));
    char *key = "1s3CR3t!";

    printf("Please enter the message you wish to encrypt/decrypt (LIMIT 255): ");
    fgets(string, STRING_SIZE, stdin);

    Registers registers = init(key);
    char *cyphered_string = cypher_string(registers, string);
    printf("%s\n", cyphered_string);

    registers = init(key);
    char *decyphered_string = cypher_string(registers, cyphered_string);
    printf("%s\n", decyphered_string);

    free_registers(registers);
    free(cyphered_string);
    free(decyphered_string);
    free(string);
}

int main() {
    a51();
    diffie_hellman();
    return MU_EXIT_CODE;
}
