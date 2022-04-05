//
// Created by victor on 30/03/2022.
//

#include "a51.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Registers init(const char *key) {
    Registers registers = (Registers) {key, calloc(LFSRS_BYTE_SIZE, sizeof(unsigned char)),
                                       calloc(BLOCK_COUNTER_BYTE_SIZE, sizeof(unsigned char))};
    return registers;
}

Registers insert_key(Registers registers) {
    for (int i = 0; i < KEY_BYTE_SIZE * 8; i++) {
        registers.lfsrs[0] ^= get_bit(registers.key, i);
        registers.lfsrs[LFSR_1 / 8] ^= get_bit(registers.key, i) << LFSR_1 % 8;
        registers.lfsrs[(LFSR_2 + LFSR_1) / 8] ^= get_bit(registers.key, i) << (LFSR_2 + LFSR_1) % 8;
        update(registers);
    }
    return registers;
}

Registers insert_block_counter(Registers registers) {
    for (int i = 0; i < BLOCK_COUNTER_BIT_SIZE; i++) {
        registers.lfsrs[0] ^= get_bit(registers.block_counter, i);
        registers.lfsrs[LFSR_1 / 8] ^= get_bit(registers.block_counter, i) << LFSR_1 % 8;
        registers.lfsrs[(LFSR_2 + LFSR_1) / 8] ^= get_bit(registers.block_counter, i) << (LFSR_2 + LFSR_1) % 8;
        update(registers);
    }
    return registers;
}

char cypher(Registers registers, char buffer) {
    insert_key(registers);
    insert_block_counter(registers);

    char cypher_buffer;

    for (char i = 0; i < 8; i++) {
        set_bit(&cypher_buffer, i, get_bit(&buffer, i) ^ update(registers));
    }

    block_counter_increment(registers);
    return cypher_buffer;
}


char *cypher_string(Registers registers, const char *string) {
    if (string == NULL) {
        return NULL;
    }
    char i;
    char *cypher_string = NULL;

    cypher_string = calloc(strlen(string), sizeof(char));
    printf("%d \n", (int) strlen(string));
    i = 0;
    while (string[i] != '\0') {
        cypher_string[i] = cypher(registers, string[i]);
        i++;
    }

    cypher_string[i] = '\0';
   // print_binary(cypher_string, 0, (int) strlen(string) * 8);
    //printf("\n");

    return cypher_string;
}

unsigned char update(Registers registers) {
    char XOR_LFSR1 = 0, XOR_LFSR2 = 0, XOR_LFSR3 = 0;
    char a = get_bit(registers.lfsrs, 8);
    char b = get_bit(registers.lfsrs, LFSR_1 + 10);
    char c = get_bit(registers.lfsrs, (LFSR_1 + LFSR_2) + 10);
    char maj = (a & (b | c)) | (b & c);

    if (c == maj) {
        XOR_LFSR3 = get_bit(registers.lfsrs, LFSR_1 + LFSR_2 + 7) ^ get_bit(registers.lfsrs, LFSR_1 + LFSR_2 + 20) ^
                    get_bit(registers.lfsrs, LFSR_1 + LFSR_2 + 21) ^ get_bit(registers.lfsrs, LFSR_1 + LFSR_2 + 22);
        LFSR_insert(registers, LFSR_1 + LFSR_2, LFSR_3 - 1, XOR_LFSR3);
    }

    if (b == maj) {
        XOR_LFSR2 = get_bit(registers.lfsrs, LFSR_1 + 20) ^ get_bit(registers.lfsrs, LFSR_1 + 21);
        LFSR_insert(registers, LFSR_1, LFSR_2, XOR_LFSR2);
    }

    if (a == maj) {
        XOR_LFSR1 = get_bit(registers.lfsrs, 13) ^ get_bit(registers.lfsrs, 16) ^ get_bit(registers.lfsrs, 17) ^
                    get_bit(registers.lfsrs, 18);
        LFSR_insert(registers, 0, LFSR_1, XOR_LFSR1);
    }

    return get_bit(registers.lfsrs, LFSR_1 + LFSR_2 + LFSR_3 - 1) ^ get_bit(registers.lfsrs, LFSR_1 + LFSR_2 - 1) ^
           get_bit(registers.lfsrs, LFSR_1 - 1);
}

char get_bit(const char *word, char bit) {
    return word[bit / 8] >> bit % 8 & 1;
}

void set_bit(char *word, char bit, char val) {
    if (word != NULL) {
        word[bit / 8] ^= (-val ^ word[bit / 8]) & (1 << bit % 8);
    }
}

void print_binary(char *buffer, int index, int length) {
    int i;
    char space_count;
    space_count = 0;
    for (i = index + length - 1; i >= index; i--) {
        if (space_count % 4 == 0 && space_count != 0) {
            printf(" ");
        }
        printf("%d", get_bit(buffer, i));
        space_count++;
    }
}

void print_registers(Registers registers) {
    printf("\nLFSR 1 : ");
    print_binary(registers.lfsrs, 0, LFSR_1);

    printf("\nLFSR 2 : ");
    print_binary(registers.lfsrs, LFSR_1, LFSR_2);

    printf("\nLFSR 3 : ");
    print_binary(registers.lfsrs, LFSR_2 + LFSR_1, LFSR_3);

    printf("\n");
}


void LFSR_insert(Registers registers, int index, int length, unsigned value) {
    for (int i = index + length; i > index; i--) {
        set_bit(registers.lfsrs, i, get_bit(registers.lfsrs, i - 1));
    }
    set_bit(registers.lfsrs, index, value);
}

int power(int x, int n) {
    if (n == 0) {
        return 1;
    }
    int result = x;
    for (int i = 1; i < n; i++) {
        result *= x;
    }
    return result;
}

void block_counter_increment(Registers registers) {
    for (char i = 0; i < BLOCK_COUNTER_BYTE_SIZE; i++) {
        if (i == BLOCK_COUNTER_BYTE_SIZE - 1 &&
            registers.block_counter[i] == power(2, BLOCK_COUNTER_BIT_SIZE % 8) - 1) {
            registers.block_counter[i] = 0;
            break;
        }

        if (registers.block_counter[i] != 255) {
            registers.block_counter[i]++;
            break;
        }
        registers.block_counter[i]++;
    }
}


void free_registers(Registers registers) {
    free(registers.lfsrs);
    free(registers.block_counter);
}