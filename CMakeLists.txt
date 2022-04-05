cmake_minimum_required(VERSION 3.20)
project(tp_crypto C)

include_directories(include gmp/include)

set(CMAKE_C_STANDARD 99)

add_executable(tp_crypto main.c src/a51.c include/a51.h src/a51.c test/a51_test.c src/diffie_hellman.c include/diffie_hellman.h)

target_link_libraries(tp_crypto /gmp/lib/libgmp.a)
