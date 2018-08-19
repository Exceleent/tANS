#include <stdio.h>
#include <stdlib.h>
#include "Core.h"

int main() {
	int i = 0;
	int nStates = 16;
	int letters[3] = {0, 1, 2};
	int numbers[3] = {3, 8, 5};
	int nAlphabet = sizeof(letters)/sizeof(letters[0]);
	int nNumbers = sizeof(numbers)/sizeof(numbers[0]);
	int nCount = 0;
	int R = log2(nStates); // 4
	int r = R + 1;

	if(nAlphabet != nNumbers) {
		exit(-1);
	}

	for(i = 0; i < nNumbers; i++) {
		nCount += numbers[i];
	}

	if(nCount != nStates) {
		exit(-1);
	}

	// Test createStateTable
	int stateTable[nStates];
	createStateTable(&stateTable, nStates);

	printf("State table: \n");
	for(i = 0; i < nStates; i++) {
		printf("\t index: %d, value: %d\n", i, stateTable[i]);
	}
	printf("\n");

	//Test createAlphabet
//	int alphabet[nStates];
//
//	createAlphabet(&alphabet, letters, numbers, nAlphabet, nNumbers);
//
//	printf("Alphabet: \n");
//	for(i = 0; i < nStates; i++) {
//		printf("\t index: %d, value: %d\n", i, alphabet[i]);
//	}
//	printf("\n");
//
//	// Testing spread
//	spread(&alphabet, numbers, nNumbers, nStates);
//
//	printf("alphabet after spread: \n");
//	for(i = 0; i < nStates; i++) {
//		printf("\t index: %d, value: %d\n", i, alphabet[i]);
//	}
//	printf("\n");

	int alphabet[16] = {1, 1, 0, 2, 2, 1, 0, 2, 1, 0, 2, 1, 2, 1, 1, 1};
	// Testing getK
	int k[nNumbers];
	calculateK(&k, numbers, 3, R);
	printf("values of k: \n");
	for(i = 0; i < nNumbers; i++) {
		printf("\tindex: %d, value: %d\n", i, k[i]);
	}
	printf("\n");

	// Testing calculateNb
	int nb[nNumbers];
	calculateNb(&nb, &k, numbers, nNumbers, r);
	printf("values of nb: \n");
	for(i = 0; i < 3; i++) {
		printf("\tindex: %d, value: %d\n", i, nb[i]);
	}
	printf("\n");


	int index = 19;
	int symbol = 1;
	index -=16;

	int nbBit;
	// index symbol
	calculateNbBit(&nbBit, &stateTable, &alphabet, index, symbol, nb, r);
	printf("values of nbBits: \n");
	printf("\tvalue: %d\n", nbBit);
	printf("\n");

	int startTable[3];
	createStartTable(startTable, numbers, nNumbers);
	printf("values of startTable: \n");
	for(i = 0; i < 3; i++) {
		printf("\tindex: %d, value: %d\n", i, startTable[i]);
	}
	printf("\n");

	int encodingTable[nStates];
	createEncodingTable(encodingTable, startTable, &alphabet, numbers, nNumbers, nStates);
	printf("values of encodingTable: \n");
	for(i = 0; i < nStates; i++) {
		printf("\tindex: %d, value: %d\n", i, encodingTable[i]);
	}
	printf("\n");

	int usedBits[nStates];
	useBits(usedBits, &stateTable, nbBit, nStates, index);
	printf("values of usedBits: \n");
	for(i = 0; i < nbBit; i++) {
		printf("\tindex: %d, value: %d\n", i, usedBits[i]);
	}
	printf("\n");


	int nextStateEncoder;
	getNextStateEncoder(&nextStateEncoder, startTable, &stateTable, nbBit, encodingTable, &alphabet, index, symbol);
	printf("next state: %d", nextStateEncoder);
	printf("\n");

	return 0;

}
