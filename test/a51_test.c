//
// Created by Victor and Antoine on 30/03/2022.
//

#include "minunit.h"

#include "a51.h"

#define TEST_KEY "AzErTyUi"

#define CHAR 'C'
#define CYPHER_CHAR 31

#define WORD "cryptographie"
#define CYPHER_WORD_LINE char CYPHER_WORD[13] = {63,-107,-29,112,84,90,46,66,-58,69,92,13,79};

MU_TEST(test_power) {
    printf("test_power\n");
    mu_check(power(2, 0) == 1);
    mu_check(power(2, 1) == 2);
    mu_check(power(2, 2) == 4);
    mu_check(power(2, 3) == 8);
    mu_check(power(2, 4) == 16);
    mu_check(power(2, 5) == 32);
    mu_check(power(2, 6) == 64);
    mu_check(power(2, 7) == 128);
    mu_check(power(2, 8) == 256);
}

MU_TEST(test_init) {
    printf("\ntest_init\n");
    Registers registers = init(TEST_KEY);
    for (char i = 0; i < LFSRS_BYTE_SIZE; i++) {
        mu_check(registers.lfsrs[0] == 0);
    }
    for (char i = 0; i < BLOCK_COUNTER_BYTE_SIZE; i++) {
        mu_check(registers.block_counter[0] == 0);
    }
    mu_check(strcmp(TEST_KEY, registers.key) == 0);
}

MU_TEST(test_block_counter_increment) {
    printf("\ntest_block_counter_increment\n");
    Registers registers = init(TEST_KEY);
    mu_check(registers.block_counter[2] == 0);
    mu_check(registers.block_counter[1] == 0);
    mu_check(registers.block_counter[0] == 0);
    for (int i = 0; i < power(2, 22); ++i) {
        block_counter_increment(registers);
    }
    mu_check(registers.block_counter[2] == 0);
    mu_check(registers.block_counter[1] == 0);
    mu_check(registers.block_counter[0] == 0);
}


MU_TEST(test_cypher) {
    printf("\ntest_cyper\n");
    Registers registers = init(TEST_KEY);
    char cypher_char = cypher(registers, CHAR);
    mu_check(cypher_char == CYPHER_CHAR);
}

MU_TEST(test_decyper) {
    printf("\ntest_decyper\n");
    Registers registers = init(TEST_KEY);
    char decypher_char = cypher(registers, CYPHER_CHAR);
    mu_check(decypher_char == CHAR);
}


MU_TEST(test_cypher_string) {
    CYPHER_WORD_LINE;
    printf("\ntest_cypher_string\n");
    Registers registers = init(TEST_KEY);
    char *cypher_string_test = cypher_string(registers, WORD);
    mu_check(strcmp(cypher_string_test, CYPHER_WORD) == 0);
}

MU_TEST(test_decyper_string) {
    CYPHER_WORD_LINE;
    printf("\ntest_decyper_string\n");
    Registers registers = init(TEST_KEY);
    char *decypher_string = cypher_string(registers, CYPHER_WORD);
    mu_check(strcmp(decypher_string, WORD) == 0);
}


MU_TEST_SUITE(a51_test_suite) {
    MU_RUN_TEST(test_power);
    MU_RUN_TEST(test_init);
    MU_RUN_TEST(test_block_counter_increment);
    MU_RUN_TEST(test_cypher);
    MU_RUN_TEST(test_decyper);
    MU_RUN_TEST(test_cypher_string);
    MU_RUN_TEST(test_decyper_string);
}


