# tANS
 tANS - c implementation
 
 
This is C implementation of tANS algorithm.

# Folder Encoder - Contains

*Core.h - declarations of functions._
*Core.c - definitions of functions.
*main.c - encoder function, which calls functions from Core.c.
*main_test.c - example how use encoder
*config - encoder reads data from this file. First column consist letters from our alphabet, range:0 - 255.( filled by you)
Second column consist number of appearances for each letter.
*symbols - first line consist starting state of encode then, sequence of symbols, we want to code.(filled by you)


# Folder Decoder - Contains
*Bits.txt - sequence of bits we coded within our coder ( encoder fills it )
*Core.c - definitions of functions
*Core.h - declarations of functions 
*Nsymbols.txt - Alphabet size ( filled by you)
*Numbers.txt - Number of appearances for each letter ( filled by you )
*test_bench.c - main function calling decodingfunction
*numberofBits.txt - Number of Bits we coded ( encoder fills it )
*state.txt - starting state for decoder, ending state for encoder(encoder fills it )
*symbols.txt -  reversal sequence of decode symbols, and starting state for encoder


## Compilation 
Encoder:
to compile encoder, put in linux command line: gcc -std=c99 Core.c main.c main_test.c -lm -o "name"
Decoder:
to compile decoder , put in linux command line: gcc -std=c99 Core.c test_bench.c -lm -o "name"
