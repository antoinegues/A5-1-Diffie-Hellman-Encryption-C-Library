//
// Created by victor on 30/03/2022.
//

#ifndef TP_CRYPTO_A51_H
#define TP_CRYPTO_A51_H


// Size of the LFSR
#define LFSR_1 19
#define LFSR_2 22
#define LFSR_3 23

// Registers can be represented as a 64 bits word, or an 8 bytes array
#define SIZE 8
#define BIT_SIZE 64

#define KEY_SIZE 8

// Each word is 64 bits so it makes 8 bytes
typedef char *Registers;

/**
 * Initializes registers, set them all to 0
 * @return initialized registers
 */
Registers init(char *);

/**
 * Cypher a byte
 * @param registers
 * @param buffer
 * @return
 */
char cypher(Registers registers, char buffer);


/**
 * Cypher a string
 * @param registers
 * @param string
 * @return
 */
char *cypher_string(Registers registers, const char *string);
/**
 * Updates the LFSRs
 * @param registers
 * @return
 */
unsigned char update(Registers registers);

/**
 * Get the xth value of the word
 * @param r
 * @param byte
 * @param bit
 * @return
 */
char get_bit(const char *word, char bit);

/**
 * Set the value of the xth of the word to val
 * @param word
 * @param bit
 * @param val
 */
void set_bit(char *word, char bit, char val);


/**
 * Print the binary
 * @param buffer
 * @param index
 * @param length
 */
void print_binary(char *buffer, int index, int length);

/**
 * Print the registers
 * @param registers
 */
void print_registers(Registers registers);

/**
 * Insert a value in a LFSR
 * @param registers
 * @param index of the LFSR
 * @param length of the LFSR
 * @param value
 */
void LFSR_insert(Registers registers, int index, int length, unsigned value);

#endif //TP_CRYPTO_A51_H
