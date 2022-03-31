# A5/1 Encryption C Library

C implementation of the A5/1 encryption algorithm

## Introduction

A5/1 is a stream encryption algorythm that has been used in mobile communications. It generates a pseudo-random sequence, by mixing three linear feedback shift registers of different sizes.

![Picture of A5/1 LFSR and update steps](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5e/A5-1_GSM_cipher.svg/1920px-A5-1_GSM_cipher.svg.png)

For more details on the algorithm, please visit [Wikipedia](https://en.wikipedia.org/wiki/A5/1)

## Usage

To create all necessary files to the compilation use the `cmake` command :

```shell
cmake . .
```

 Then compile the sources using the `make` command :

```shell
make
```

Finally, run the program :

```shell 
./tp_crypto
```
