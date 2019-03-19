***********************
Guidlines
***********************

What our project contains
===============================

Encoder file
-------------
* Core.h - declarations of functions.
* Core.c - definitions of functions.
* main.c - encoder function, which calls functions from Core.c
* main_test.c - example how use encoder.
* config - encoder reads data from this file. First column consist letters from our alphabet, range:0 - 255.( filled by you).
Second column consist number of appearances for each letter.
* symbols - first line consist starting state of encode then, sequence of symbols, we want to code.(filled by you).
