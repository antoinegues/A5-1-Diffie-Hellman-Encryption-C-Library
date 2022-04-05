//
// Created by victor on 30/03/2022.
//

#include <stdio.h>
#include "diffie_hellman.h"
#include "gmp.h"

void diffie_hellman() {
    mpz_t p, g, o, phi;
    mpz_init(p);
    mpz_init(g);
    mpz_init(o);
    mpz_init(phi);

    generate_prime(p);
    gmp_printf("P = %Zd", p);

//    mpz_sub_ui(phi, p, 1);
//    mpz_set_ui(g, 0);
//    mpz_set_ui(o, 0);
//    while (mpz_cmp(p, g) && mpz_cmp(o, phi)) {
//        mpz_add_ui(g, g, 1);
//        ordre(o, g, p);
//    }
//    gmp_printf("P =  %Zd", g);

    mpz_clear(o);
    mpz_clear(phi);
    mpz_clear(p);
    mpz_clear(g);
}

void generate_prime(mpz_t n) {
    gmp_randstate_t state;
    gmp_randinit_default(state);
    do {
        mpz_rrandomb(n, state, 512);
    } while (!mpz_millerrabin(n, MILLER_RABIN_ITERATIONS));
}

void ordre(mpz_t r, mpz_t e, mpz_t n) {
    mpz_t k, p;
    mpz_init(k);
    mpz_init(p);
    mpz_set_ui(k, 1);
    mpz_set(p, e);


    while (mpz_divisible_p(p, n)) {
        mpz_mul(p, p, e);
        mpz_add_ui(k, k, 1);
    }
    mpz_set(r, k);
}

/**
 * def square_and_multiply(a, k, n):
    n = abs(n)
    h = 1
    p = format(k, 'b')

    for i in range(0, len(p)):
        h = h * h % n
        if p[i] == "1":
            h = h * a % n

    return h
 */

void square_and_multiply() {

}
