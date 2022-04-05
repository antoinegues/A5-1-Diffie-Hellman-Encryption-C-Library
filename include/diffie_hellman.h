//
// Created by victor on 30/03/2022.
//

#ifndef TP_CRYPTO_DIFFIE_HELMAN_H
#define TP_CRYPTO_DIFFIE_HELMAN_H

#include "stdbool.h"
#include "gmp.h"

#define MILLER_RABIN_ITERATIONS 40

void diffie_hellman();

void generate_prime(mpz_t n);

void ordre(mpz_t r, mpz_t e, mpz_t n);

#endif //TP_CRYPTO_DIFFIE_HELMAN_H
