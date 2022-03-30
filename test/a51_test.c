//
// Created by victor on 30/03/2022.
//

#include "minunit.h"
#include "a51.h"

static Registers registers;
static char *key;

void a51_test_setup() {
    key = "AzErTyUi";
}

void a51_test_teardown() {
    // nothing
}

MU_TEST(test_init) {
    registers = init(key);
    print_registers(registers);
}

MU_TEST_SUITE(a51_test_suite) {
    MU_SUITE_CONFIGURE(&a51_test_setup, &a51_test_teardown);

}