#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void createStateTable(char *stateTable, int nbStates);
void createAlphabet(char *alphabet, int letters[], int numbers[], int nbStates);
void spread(char *alphabet, int numbers[], int nbStates);
void Next (int Next[],int numbers[], int numberofsymbols );
void TSymbol(int Tsymbol[] , char spread[] , int numberofstates);
void ReturningX (int X[],int Tsymbol[],int Next[],int numberofstates );
void ReturningNbBits(int TabnbBits[],int X[], int numberofstates);
void ReturningNewX(int ReturningX[],int TabnbBits[], int X[], int numberofstates);
void  DecodingSymbol(int *symbol ,char spread[] , int indexofstate);
void NextStateofDecoder(int *NextState,int NewXTab[], int NbBits[], char UseBits[],int indexofstate);
void DECODINGFUNCTION();

