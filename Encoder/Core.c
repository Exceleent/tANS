// tANS algorithm
// Szymon Pulut && Michał Znaleźniak

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Core.h"

#ifdef DEBUG
#define DEBUG_PRINT(...) do{ fprintf(stderr, "DEBUG: " __VA_ARGS__ ); } while(0)
#else
#define DEBUG_PRINT(...) do{ } while(0)
#endif

// -------------- preparing data required for encoding
void createStateTable(int stateTable[], int nbStates) {
	DEBUG_PRINT("State table: \n");
	FillStateTable: for(int i = 0, temp = nbStates; i < nbStates; i++) {
		stateTable[i] = temp++;
		DEBUG_PRINT("\tindex: %d, value: %d\n", i, stateTable[i]);
	}

}

// creates alphabet consisting of letters[] with according frequency from numbers[]
void createAlphabet(int alphabet[], int letters[], int numbers[], size_t numbers_size, int nbStates) {
	int tempSum = numbers[0];

	DEBUG_PRINT("\t Create alphabet. nbStates: %d\n", nbStates);
	CreateAlphabet: for(int i = 0, j = 0; i < nbStates; i++) {
		if(i == tempSum) {
			tempSum += numbers[++j];
		}
		alphabet[i] = letters[j];
		DEBUG_PRINT("\t index: %d, j: %d, value letter: %d, value alphabet: %d\n", i, j, letters[j], alphabet[i]);
	}
}

// spreads symbols in alphabet - required for eficient (size-eficient) encoding
void spread(int alphabet[], int numbers[], size_t numbers_size, int nbStates) {
	int startPos = 0; // Starting position
	int step = (nbStates / 8) + 3; // Step size
	DEBUG_PRINT("Spread start: \n");

	int tempSum = numbers[0];

	Spread: for(int i = 0, j = 0; i < nbStates; i++) {
		if(i == tempSum) {
			tempSum += numbers[++j];
		}
		alphabet[startPos] = j;
		startPos = (startPos + step) % nbStates;
		DEBUG_PRINT("\t index: %d, moving symbol: %d, start pos: %d\n", i, j, startPos);
	}
}

// -------------- core of encoding algorithm

// create K values for every letter in alphabet
void calculateK(int k[], int numbers[], size_t numbers_size, int R) {
	DEBUG_PRINT("Values of k:\n");
	CalcK: for(int i = 0; i < numbers_size; i++) {
		// value defined in algorithm
		k[i] = R - floor(log2(numbers[i]));
		DEBUG_PRINT("\t index: %d, k: %d\n", i, k[i]);
	}
}

// create nb values for every letter in alphabet
void calculateNb(int nb[], int k[], int numbers[], size_t numbers_size, int r) {
	DEBUG_PRINT("Values of nb:\n");
	CalcNb: for(int i = 0; i < numbers_size; i++) {
		nb[i] = (k[i] << r) - (numbers[i] << k[i]);
		DEBUG_PRINT("\t index: %d, nb: %d\n", i, nb[i]);
	}
}
// calulate nbBit value for given state (index) and symbol
// index is 0-lastState | not lastState-(2*lastState-1)
void calculateNbBit(int *nbBit, int stateTable[], int alphabet[], int index, int symbol, int nb[], int r) {
	int nbBitVal;

	DEBUG_PRINT("Values of nbBit: \n");
	*nbBit = nbBitVal = (stateTable[index] + nb[symbol]) >> r;
	DEBUG_PRINT("\t nbBit: %d, state: %d, index: %d, symbol: %d\n", nbBitVal, stateTable[index], index, symbol);
}

// create startTable
void createStartTable(int startTable[], int numbers[], size_t numbers_size) {
	DEBUG_PRINT("Values of startTable: \n");
	for(int i = 0; i < numbers_size; i++) {
		startTable[i] = -numbers[i];

		for(int j = i; j > 0;) {
			startTable[i] += numbers[--j];
		}
		DEBUG_PRINT("\t index: %d, value: %d\n", i, startTable[i]);
	}
}

// create encodingTable
void createEncodingTable(int encodingTable[], int startTable[], int alphabet[], int numbers[], size_t numbers_size, int nbStates) {
	int i;
	for(i = nbStates; i < 2 * nbStates; i++) {
		int s = alphabet[i - nbStates];
		encodingTable[startTable[s] + (numbers[s])] = i;
		numbers[s]++;
	}
	DEBUG_PRINT("Encoding Table: \n");
	UnFilling2: for(i = 0; i < nbStates; i++) {
		DEBUG_PRINT("\t index: %d, value: %d\n", i, encodingTable[i]);
	}
}

// -------------- core of the core

// get bits used to encode
void useBits(int usedBits[], size_t *usedBits_length, int stateTable[], int nbBit, int nbStates, int stateIndex) {
	int temp = stateTable[stateIndex];
	DEBUG_PRINT("use bits: \n");
	int i;
	for(i = 0; i < nbBit; i++) {
		if(temp % 2 == 1) { // odd
			usedBits[i] = 1;
		}
		else { // even
			usedBits[i] = 0;
		}
		temp = temp >> 1;
		DEBUG_PRINT("\t i: %d, stateIndex: %d, value: %d \n", i, stateIndex, usedBits[i]);
	}
	*usedBits_length = i;
}


// calculate next state for give stateIndex and letter (symbol)
// index is 0-lastState | not lastState-(2*lastState-1)
// returns state as in value of state:
//			between lastState and (2*lastState-1)
void getNextStateEncoder(int *nextStateEncoder, int startTable[], int stateTable[], int nbBit, int encodingTable[], int alphabet[], int stateIndex, int letter) {
	int xTmp = (stateTable[stateIndex] >> nbBit);
	int startValue = startTable[letter];
	int nextState;
	*nextStateEncoder = nextState = encodingTable[startValue + xTmp];
	DEBUG_PRINT("next state: %d, startVal: %d, xTmp: %d\n", nextState, startValue, xTmp);
}
