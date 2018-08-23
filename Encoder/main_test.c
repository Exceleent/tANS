#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PATH_FILE_SYMBOLS "symbols"
#define PATH_FILE_CONFIG "config"
#define PATH_FILE_OUTPUT "output"

#define MAX_SYMBOLS 256

void encode(int state, int states[], char tempBitsArray[][MAX_SYMBOLS], int letters[], int numbers[], int symbols[], size_t symbols_size, int nCount);

int main() {
	int i = 0;

	int states[MAX_SYMBOLS];
	char tempBitsArray[MAX_SYMBOLS][MAX_SYMBOLS];

	FILE *fileConfig, *fileSymbols, *fileOutput;
	fileConfig = fopen(PATH_FILE_CONFIG, "r");
	fileSymbols = fopen(PATH_FILE_SYMBOLS, "r");

	if(fileSymbols == NULL || fileConfig == NULL ) {
		exit(1);
	}

	int read1, read2;
	int letters[MAX_SYMBOLS];
	int numbers[MAX_SYMBOLS];
	int nCount = 0;
	while(!feof(fileConfig)) {
		fscanf(fileConfig, "%d", &read1);
		fscanf(fileConfig, "%d", &read2);

		if(feof(fileConfig)) break;

		letters[nCount] = (int) read1;
		numbers[nCount] = (int) read2;
		nCount++;
	}
	fclose(fileConfig);

	int symbol;
	int symbols[MAX_SYMBOLS];
	int state;

	i = 0;
	fscanf(fileSymbols, "%d", &state);
	while(!feof(fileSymbols)) {
		fscanf(fileSymbols, "%d", &symbol);

		if(feof(fileSymbols)) break;

		symbols[i] = symbol;
		i++;
	}
	fclose(fileSymbols);

	encode(state, states, tempBitsArray, letters, numbers, symbols, i, nCount);

	
	return 0;
}
