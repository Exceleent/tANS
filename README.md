# tANS
 tANS - c implementation
 
 
This is C implementation of tANS algorithm.
```
 Folder Encoder - Contains

*Core.h - declarations of functions.<br />
*Core.c - definitions of functions.<br />
*main.c - encoder function, which calls functions from Core.c<br />
*main_test.c - example how use encoder.<br />
*config - encoder reads data from this file. First column consist letters from our alphabet, range:0 - 255.( filled by you).<br />
Second column consist number of appearances for each letter.<br />
*symbols - first line consist starting state of encode then, sequence of symbols, we want to code.(filled by you).<br />
```
```
 Folder Decoder - Contains
*Bits.txt - sequence of bits we coded within our coder ( encoder fills it ).<br />
*Core.c - definitions of functions.<br />
*Core.h - declarations of functions .<br />
*Nsymbols.txt - Alphabet size ( filled by you).<br />
*Numbers.txt - Number of appearances for each letter. ( filled by you ).<br />
*test_bench.c - main function calling decodingfunction.<br />
*numberofBits.txt - Number of Bits we coded ( encoder fills it ).<br />
*state.txt - starting state for decoder, ending state for encoder(encoder fills it ).<br />
*symbols.txt -  reversal sequence of decode symbols, and starting state for encoder.<br />
```

## Compilation 
Encoder:
to compile encoder, put in linux command line: gcc -std=c99 Core.c main.c main_test.c -lm -o "name".<br />
Decoder:
to compile decoder , put in linux command line: gcc -std=c99 Core.c test_bench.c -lm -o "name".<br />
