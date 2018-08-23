#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SYMBOLS 256

void createStateTable(int stateTable[], int nbStates);
void createAlphabet(int alphabet[], int letters[], int numbers[], size_t numbers_size, int nbStates);
void spread(int alphabet[], int numbers[], size_t numbers_size, int nbStates);
void calculateK(int k[], int numbers[], size_t numbers_size, int R);
void calculateNb(int nb[], int k[], int numbers[], size_t numbers_size, int r);
void calculateNbBit(int *nbBit, int stateTable[], int index, int symbol, int nb[], int r);
void createStartTable(int startTable[], int numbers[], size_t numbers_size);
void createEncodingTable(int encodingTable[], int startTable[], int alphabet[], int numbers[], size_t numbers_size, int nbStates);
void useBits(int usedBits[], size_t *usedBits_length, int stateTable[], int nbBit, int nbStates, int stateIndex);
void getNextStateEncoder(int *nextStateEncoder, int startTable[], int stateTable[], int nbBit, int encodingTable[], int stateIndex, int letter);
void encode(int state, int states[], char tempBitsArray[][MAX_SYMBOLS], int letters[], int numbers[], int symbols[], size_t symbols_size, int nCount);
