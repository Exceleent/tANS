#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Core.h"

#define PATH_FILE_BITS "../Decoder/Bits.txt"
#define PATH_FILE_STATE "../Decoder/state.txt"
#define PATH_FILE_NOB "../Decoder/numberofBits.txt"
#define MAX_SYMBOLS 256

void encode(int state, int states[], char tempBitsArray[][MAX_SYMBOLS], int letters[], int numbers[], int symbols[], size_t symbols_size, int nCount) {
	int i = 0;
	FILE *des , *des_2, *des_3;
	des = fopen(PATH_FILE_BITS, "w");
	des_2 = fopen(PATH_FILE_STATE,"w");
	des_3 = fopen(PATH_FILE_NOB,"w");

	int nStates = 0;

	for(i = 0; i < nCount; i++) {
		nStates += numbers[i];
	}

	int R = log2(nStates);
	int r = R + 1;
	int stateTable[nStates];
	int alphabet[nStates];
	int k[nCount];
	int nb[nCount];
	int nbBit;
	int startTable[nCount];
	int encodingTable[nStates];
	int usedBits[nStates];
	size_t usedBits_length;
	int nextStateEncoder;


	createStateTable(stateTable, nStates);
	createAlphabet(alphabet, letters, numbers, nCount, nStates);
	spread(alphabet, numbers, nCount, nStates);

	calculateK(k, numbers, nCount, R);
	calculateNb(nb, k, numbers, nCount, r);
	createStartTable(startTable, numbers, nCount);
	createEncodingTable(encodingTable, startTable, alphabet, numbers, nCount, nStates);

	int symbol;

	state -= nStates;
	char bits[1024];
	int NumberofBits;
	int l = 0;

	for(i = 0; i < symbols_size; i++) {
		calculateNbBit(&nbBit, stateTable, state, symbols[i], nb, r);
		useBits(usedBits, &usedBits_length, stateTable, nbBit, nStates, state);

		char tempBits[usedBits_length];
		int m;
		for(m = 0; m<usedBits_length; m++) {
			bits[l] = usedBits[m] + '0';
			tempBits[m] = usedBits[m] + '0';
			l++;
			NumberofBits++;
		}

		getNextStateEncoder(&nextStateEncoder, startTable, stateTable, nbBit, encodingTable,  state, symbols[i]);

		state = nextStateEncoder - nStates;
		tempBits[m] = '\0';
		states[i] = state;
		strcpy(tempBitsArray[i], tempBits);		
	}
	state += nStates;
	fprintf(des_2,"%d\n",state-nStates);
	fprintf(des_2,"%d",i);
	fprintf(des_3,"%d",NumberofBits);
	fprintf(des,"%s",bits);

	fclose(des);
	fclose(des_2);
	fclose(des_3);


	printf("last state: %d\n", state);
	printf("bit seq: %s\n", bits);

}
