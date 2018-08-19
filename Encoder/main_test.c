#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PATH_FILE_SYMBOLS "symbols"
#define PATH_FILE_CONFIG "config"
#define PATH_FILE_OUTPUT "output"
#define MAX_SYMBOLS 256

int main() {
	int i = 0;

	int states[MAX_SYMBOLS];
	char tempBitsArray[MAX_SYMBOLS][MAX_SYMBOLS];

	FILE *fileConfig, *fileSymbols, *fileOutput;
	fileConfig = fopen(PATH_FILE_CONFIG, "r");
	fileSymbols = fopen(PATH_FILE_SYMBOLS, "r");
	fileOutput = fopen(PATH_FILE_OUTPUT, "a");

	if(fileSymbols == NULL || fileConfig == NULL || fileOutput == NULL) {
		exit(1);
	}

	int read1, read2;
	int letters[MAX_SYMBOLS];
	int numbers[MAX_SYMBOLS];
	int nCount = 0;
	while(!feof(fileConfig)) {
		fscanf(fileConfig, "%d", &letters[nCount]);
		fscanf(fileConfig, "%d", &numbers[nCount]);
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
	int size = 0;
	for(i = 0, size = MAX_SYMBOLS; i < size; i++) {
		fprintf(fileOutput, "%d | %s\n", states[i], tempBitsArray[i]);
	}
	fclose(fileOutput);


	return 0;
}
