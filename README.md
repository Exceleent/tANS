# Asymmetric Numeral Systems - Tabled ANS
 tANS - C implementation
 
 
This is C implementation of tANS Encoder and Decoder. ANS is family of entropy coding developed by Jarosław Duda (http://th.if.uj.edu.pl/~dudaj/). tANS constructs a finite state machine to operate on a large alphabet without using multiplication, that guarantee high quality of compression ration and low processing cost.


# Example of generation of tANS tables for 3 size alphabet and 16 states
![tans](https://user-images.githubusercontent.com/42517471/44548795-624f7780-a71f-11e8-9f6e-b91802e8bdcc.png)
As you can see, we generate couple of tables. Then we are applying them for stream decoding. With only one state and sequence of bits genereted by encoder, we are capable to decode information.

# How to use our Coder/Encoder
In order to know more about structure of the project and how coder/encoder exactly works please read our [guidelines](https://github.com/Exceleent/tANS/blob/master/docs/HowtoUse.txt) 


 # Folder Encoder - Contains

*Core.h - declarations of functions.<br />
*Core.c - definitions of functions.<br />
*main.c - encoder function, which calls functions from Core.c<br />
*main_test.c - example how use encoder.<br />
*config - encoder reads data from this file. First column consist letters from our alphabet, range:0 - 255.( filled by you).<br />
Second column consist number of appearances for each letter.<br />
*symbols - first line consist starting state of encode then, sequence of symbols, we want to code.(filled by you).<br />

 # Folder Decoder - Contains
*Bits.txt - sequence of bits we coded within our coder ( encoder fills it ).<br />
*Core.c - definitions of functions.<br />
*Core.h - declarations of functions .<br />
*Nsymbols.txt - Alphabet size ( filled by you).<br />
*Numbers.txt - Number of appearances for each letter. ( filled by you ).<br />
*test_bench.c - main function calling decodingfunction.<br />
*numberofBits.txt - Number of Bits we coded ( encoder fills it ).<br />
*state.txt - starting state for decoder, ending state for encoder(encoder fills it ).<br />
*symbols.txt -  reversal sequence of decode symbols, and starting state for encoder.<br />

