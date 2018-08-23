// tANS algorithm
// Szymon Pulut && Michał Znaleźniak

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Core.h"


void createStateTable(int stateTable[], int nbStates) {
	FillStateTable: for(int i = 0, temp = nbStates; i < nbStates; i++) {
		stateTable[i] = temp++;
		
	}

}

void createAlphabet(int alphabet[], int letters[], int numbers[], size_t numbers_size, int nbStates) {
	int tempSum = numbers[0];

	CreateAlphabet: for(int i = 0, j = 0; i < nbStates; i++) {
		if(i == tempSum) {
			tempSum += numbers[++j];
		}
		alphabet[i] = letters[j];
	}
}

void spread(int alphabet[], int numbers[], size_t numbers_size, int nbStates) {
	int startPos = 0; 
	int step = (nbStates / 8) + 3; 

	int tempSum = numbers[0];

	Spread: for(int i = 0, j = 0; i < nbStates; i++) {
		if(i == tempSum) {
			tempSum += numbers[++j];
		}
		alphabet[startPos] = j;
		startPos = (startPos + step) % nbStates;
	}
}




void calculateK(int k[], int numbers[], size_t numbers_size, int R) {
	CalcK: for(int i = 0; i < numbers_size; i++) {
		k[i] = R - floor(log2(numbers[i]));
	}
}


void calculateNb(int nb[], int k[], int numbers[], size_t numbers_size, int r) {
	CalcNb: for(int i = 0; i < numbers_size; i++) {
		nb[i] = (k[i] << r) - (numbers[i] << k[i]);

	}
}
void calculateNbBit(int *nbBit, int stateTable[], int index, int symbol, int nb[], int r) {
	int nbBitVal;
	*nbBit = nbBitVal = (stateTable[index] + nb[symbol]) >> r;
}


void createStartTable(int startTable[], int numbers[], size_t numbers_size) {
	for(int i = 0; i < numbers_size; i++) {
		startTable[i] = -numbers[i];

		for(int j = i; j > 0;) {
			startTable[i] += numbers[--j];
		}
	}
}


void createEncodingTable(int encodingTable[], int startTable[], int alphabet[], int numbers[], size_t numbers_size, int nbStates) {
	int i;
	for(i = nbStates; i < 2 * nbStates; i++) {
		int s = alphabet[i - nbStates];
		encodingTable[startTable[s] + (numbers[s])] = i;
		numbers[s]++;
	}
}



void useBits(int usedBits[], size_t *usedBits_length, int stateTable[], int nbBit, int nbStates, int stateIndex) {
	int temp = stateTable[stateIndex];
	int i;
	for(i = 0; i < nbBit; i++) {
		if(temp % 2 == 1) { // odd
			usedBits[i] = 1;
		}
		else { // even
			usedBits[i] = 0;
		}
		temp = temp >> 1;
	}
	*usedBits_length = i;
}


void getNextStateEncoder(int *nextStateEncoder, int startTable[], int stateTable[], int nbBit, int encodingTable[], int stateIndex, int letter) {
	int xTmp = (stateTable[stateIndex] >> nbBit);
	int startValue = startTable[letter];
	int nextState;
	*nextStateEncoder = nextState = encodingTable[startValue + xTmp];
}
