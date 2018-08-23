// Creating EncodingTables for tANS algorithm
// MICHAL ZNALEZNIAK && SZYMON PULUT

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Core.h"


void createStateTable(char *stateTable, int nbStates) {
	FillStateTable: for(int i = 0, temp = nbStates; i < nbStates; i++) {
		stateTable[i] = temp++;	
	}
}

void createAlphabet(char *alphabet, int letters[], int numbers[], int nbStates) {
	int tempSum = numbers[0];

	CreateAlphabet: for(int i = 0, j = 0; i < nbStates; i++) {
		if(i == tempSum) {
			tempSum += numbers[++j];
		}
		alphabet[i] = letters[j];
		//printf("%d\n",alphabet[i]);
	}
}

void spread(char alphabet[], int numbers[], int nbStates) {
	int startPos = 0; // Starting position
	int step = (nbStates / 8) + 3; // Step size

	int tempSum = numbers[0];

	Spread: for(int i = 0, j = 0; i < nbStates; i++) {
		if(i == tempSum) {
			tempSum += numbers[++j];
		}
		alphabet[startPos] = j;
		startPos = (startPos + step) % nbStates;
	}
}
void Next (int Next[],int numbers[], int numberofsymbols )
{
	for ( int i = 0 ; i <numberofsymbols ; i++)
	{
		Next[i] = numbers[i]; 
		//printf("%d\n",Next[i]);
	}
}


void TSymbol(int Tsymbol[] , char spread[] , int numberofstates)
{
	for ( int i = 0 ; i < numberofstates ; i++)
	{
		Tsymbol[i] = spread[i];
		//printf("Tsymbols:%d\n", Tsymbol[i]);
	}
}

void ReturningX (int X[],int Tsymbol[],int Next[],int numberofstates )
{
	for ( int i = 0 ; i < numberofstates ; i++)
	{
		X[i] = Next[Tsymbol[i]]++;
				//printf(" X:%d\n",X[i]);
	}
}

void ReturningNbBits(int TabnbBits[],int X[], int numberofstates)
{
	int R = log2(numberofstates);
	for ( int i = 0 ; i <numberofstates;i++)
	{
		TabnbBits[i] = R - floor(log2(X[i]));
		//printf("TabnbBits %d\n", TabnbBits[i]);
	}

}


void ReturningNewX(int ReturningNewX[],int TabnbBits[], int X[], int numberofstates)
{
	for ( int i = 0 ; i < numberofstates; i++)
	{
		ReturningNewX[i] = (X[i] << TabnbBits[i]) ;
		//printf(" NewX%d\n",ReturningNewX[i]);
	}

}
void  DecodingSymbol(int *symbol, char spread[] , int indexofstate)
{
	*symbol = spread[indexofstate];
	//printf(" Decoded Symbol% d\n", *symbol);
}
// Calculating NextState
void NextStateofDecoder(int *NextState,int NewXTab[], int NbBits[], char UseBits[],int indexofstate)
{
	for( int i = 0 ; i<NbBits[indexofstate];i++)
	{
		printf(" Bits  %d\n",UseBits[i]);
		*NextState += pow(2,NbBits[indexofstate]-(i+1))*UseBits[i];
	}
	printf("%d\n", *NextState);
	*NextState += NewXTab[indexofstate];
	//printf(" New State %d\n",*NextState);
}
void FlipingBits (int numberofBits)
{
	FILE *des , *des_2;
	des = fopen("Bits.txt","r");
	char NewTab[numberofBits];
	char Bits[numberofBits];
	for(int i = 0 ; i<numberofBits; i++)
	{
		
		    		NewTab[i] = getc(des); 
		    		//printf("%d\n", NewTab[i]);
	}
fclose(des);
des_2 = fopen("Bits.txt","w");

	for(int i = 0; i < numberofBits; i++) {
		Bits[numberofBits-i-1] = NewTab[i];
	}
	for( int i = 0 ; i<numberofBits;i++)
	{
		putc(Bits[i],des);
	}

fclose(des_2);
}

void FixingSymbols( int nbofcodedsymbols)
{
	int *tab[nbofcodedsymbols+1];
	int *Newtab[nbofcodedsymbols+1];
	
	FILE *des , *des_2;
	des = fopen("symbols.txt","r");
		for( int i = 0 ; i<nbofcodedsymbols+1;i++)
			{
				fscanf(des,"%d",&tab[i]);
			}
		fclose(des);

	des_2 = fopen("symbols.txt","w");

	for(int i = 0; i < nbofcodedsymbols+1; i++) {
		Newtab[nbofcodedsymbols-i] = tab[i];
	}
	for( int i = 0 ; i<nbofcodedsymbols+1;i++)
	{
		fprintf(des_2,"%d\n", Newtab[i]);
	}

fclose(des_2);				
}


/////////////////////////// CORE FUNCTION //////////////////////


void DECODINGFUNCTION()
{
	FILE *des_1 , *des_2 , *des_3 , *des_4 , *des_5 , *des_6;
		int  indexstate;
		int nbofcodedsymbols;
	des_1 = fopen("state.txt", "r"); 
		fscanf(des_1, "%d", &indexstate);
		fscanf(des_1, "%d",&nbofcodedsymbols);
		//printf("symbosl codoed%d",nbofcodedsymbols);
		fclose(des_1);
	int numberofBits;
	 des_2 = fopen ("numberofBits.txt", "r");
		 while (fscanf(des_2, "%d", &numberofBits) != EOF);
		 fclose(des_2);
	 int numberofsymbols;
		des_5 = fopen ("Nsymbols.txt", "r");
		 while (fscanf(des_2, "%d", &numberofsymbols) != EOF);
			printf("Liczba symboli %d",numberofsymbols);
		fclose(des_5);

	des_3 = fopen("Bits.txt","r");
	des_4 = fopen("symbols.txt" , "w");
	des_6 = fopen("Numbers.txt" , "r");

	if(des_1 == NULL || des_2 == NULL || des_3 == NULL || des_5 == NULL || des_6 == NULL ) {
		exit(1);
	}
			int numbers[numberofsymbols];
			int NbStates;
				for ( int i = 0; i<numberofsymbols;i++)
			{
				fscanf(des_6, "%d" , &numbers[i]);
				printf("%d\n",numbers[i]);
				NbStates +=numbers[i];

			}
printf("%d",NbStates);
fclose(des_6);


			  int letters[numberofsymbols];
				for( int i =0; i<numberofsymbols;i++)
					{
						letters[i]=i;
					}
			int nNumbers = sizeof(numbers)/sizeof(numbers[0]);
		    char alphabet[NbStates];
			createAlphabet(alphabet,letters,numbers,NbStates);
			spread(alphabet,numbers,NbStates);
		    int nAlphabet = sizeof(alphabet)/sizeof(alphabet[0]);
		    FlipingBits(numberofBits);

		    int symbol;
		    int i;
		    int NextState =0;
		    int NextTab[nNumbers];
		    int Tsymbol[nAlphabet];
		    int X[nAlphabet];
		    int NbBits[nAlphabet];
		    int NewX[nAlphabet];
		    int R = log2(nAlphabet);
		    char Bits[R];
		    int Bits_2[R];
		    Next ( NextTab,numbers,nNumbers);
		    TSymbol(Tsymbol,alphabet,nAlphabet);
		    ReturningX ( X, Tsymbol, NextTab, nAlphabet );
		    ReturningNbBits(NbBits,X,nAlphabet);
		    ReturningNewX(NewX,NbBits, X, nAlphabet);
while( numberofBits>0)
{
			numberofBits+=(-NbBits[indexstate]);
		    	for(i = 0 ; i<NbBits[indexstate];i++)
		    	{
		    		Bits[i] = getc(des_3)-48;
		    		printf("%d\n", Bits[i]);
		    	}
					 NextState=0;
					DecodingSymbol(&symbol, alphabet , indexstate);
					fprintf(des_4, "%d\n" , symbol);
				    NextStateofDecoder( &NextState, NewX,  NbBits, Bits, indexstate);
				    indexstate = NextState-NbStates;

}
fprintf(des_4,"%d",NextState);
fclose(des_3);
fclose(des_4);
FixingSymbols(nbofcodedsymbols);
}


