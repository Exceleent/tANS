# Asymmetric Numeral Systems - Tabled ANS
 tANS - C implementation
 
 
This is C implementation of tANS Encoder and Decoder. ANS is family of entropy coding developed by Jarosław Duda (http://th.if.uj.edu.pl/~dudaj/). tANS constructs a finite state machine to operate on a large alphabet without using multiplication, that guarantee high quality of compression ration and low processing cost.


# Example of generation of tANS tables for 3 size alphabet and 16 states
![tans](https://user-images.githubusercontent.com/42517471/44548795-624f7780-a71f-11e8-9f6e-b91802e8bdcc.png)<\br>
As you can see, we generate couple of tables. Then we are applying them for stream decoding. With only one state and sequence of bits genereted by encoder, we are capable to decode information.

# How to use our Coder/Encoder
In order to know more about structure of the project and how coder/encoder exactly works please read our [guidelines](https://github.com/Exceleent/tANS/blob/master/docs/guidlines.rst) 

