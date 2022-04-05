//
// Created by victor on 30/03/2022.
//

#include "minunit.h"

#include "a51.h"

static Registers registers;
static char *key;

//void a51_test_setup() {
//    key = "AzErTyUi";
//}
//
//void a51_test_teardown() {
//    // nothing
//}

MU_TEST(test_init) {
    registers = init(key);
    print_registers(registers);
}

MU_TEST(test_block_counter_increment) {
    registers = init(key);
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

MU_TEST(test_power) {
    mu_check(power(2, 0) == 1);
    mu_check(power(2, 1) == 2);
    mu_check(power(2, 2) == 4);
    mu_check(power(2, 3) == 8);
    mu_check(power(2, 4) == 16);
}

MU_TEST_SUITE(a51_test_suite) {
    key = "AzErTyUi";
//    MU_SUITE_CONFIGURE(&a51_test_setup, &a51_test_teardown);
    MU_RUN_TEST(test_power);
    MU_RUN_TEST(test_block_counter_increment);
}