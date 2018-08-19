// Creating EncodingTables for tANS algorithm
// MICHAL ZNALEZNIAK

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Core.h"

// Create state table and fill with numbers
void createStateTable(char *stateTable, int nbStates) {
	FillStateTable: for(int i = 0, temp = nbStates; i < nbStates; i++) {
		stateTable[i] = temp++;	
	}
}

// Create alphabet
void createAlphabet(char *alphabet, int letters[], int numbers[], int nbStates) {
	int tempSum = numbers[0];

	CreateAlphabet: for(int i = 0, j = 0; i < nbStates; i++) {
		if(i == tempSum) {
			tempSum += numbers[++j];
		}
		alphabet[i] = letters[j];
		printf("%d\n",alphabet[i]);
	}
}
// spread
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
/// Arrays required for Decoding
void Next (int Next[],int numbers[], int numberofsymbols )
{
	for ( int i = 0 ; i <numberofsymbols ; i++)
	{
		Next[i] = numbers[i]; // NO Difference between numbers
		printf("%d\n",Next[i]);
	}
}


void TSymbol(int Tsymbol[] , char spread[] , int numberofstates)
{
	for ( int i = 0 ; i < numberofstates ; i++)
	{
		Tsymbol[i] = spread[i];
		printf("Tsymbols:%d\n", Tsymbol[i]);
	}
}

void ReturningX (int X[],int Tsymbol[],int Next[],int numberofstates )
{
	for ( int i = 0 ; i < numberofstates ; i++)
	{
		X[i] = Next[Tsymbol[i]]++;
				printf(" X:%d\n",X[i]);
	}
}

void ReturningNbBits(int TabnbBits[],int X[], int numberofstates)
{
	int R = log2(numberofstates);
	for ( int i = 0 ; i <numberofstates;i++)
	{
		TabnbBits[i] = R - floor(log2(X[i]));
		printf("TabnbBits %d\n", TabnbBits[i]);
	}

}


void ReturningNewX(int ReturningNewX[],int TabnbBits[], int X[], int numberofstates)
{
	for ( int i = 0 ; i < numberofstates; i++)
	{
		ReturningNewX[i] = (X[i] << TabnbBits[i]) ;
		printf(" NewX%d\n",ReturningNewX[i]);
	}

}
// Decoding symbol
void  DecodingSymbol(int *symbol, char spread[] , int indexofstate)
{
	*symbol = spread[indexofstate];
	printf(" Decoded Symbol% d\n", *symbol);
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
	//printf("NewXTab %d", NewXTab[indexofstate]);
	printf(" New State %d\n",*NextState);
}
// Flipping Bits given from Encoder
void FlipingBits (int numberofBits)
{
	FILE *des , *des_2;
	des = fopen("Bits.txt","r");
	char NewTab[numberofBits];
	char Bits[numberofBits];
	for(int i = 0 ; i<numberofBits; i++)
	{
		
		    		NewTab[i] = getc(des); // we are getting bits from fille
		    		printf("%d\n", NewTab[i]);
	}
fclose(des);
des_2 = fopen("Bits.txt","w");

	for(int i = 0; i < numberofBits; i++) {
		Bits[numberofBits-i-1] = NewTab[i];
	}
	for( int i = 0; i <numberofBits ;  i++) {
	            printf(" Zapisano %d\n",Bits[i]);
	        }

	for( int i = 0 ; i<numberofBits;i++)
	{
		putc(Bits[i],des);
	}

fclose(des_2);
}

/////////////////////////// CORE OF DECOIDNG THE MOST IMPORTATNT FUNCTION THAT'S CALL OTHER FUNCTIONS ///////////


void DECODINGFUNCTION()
{
	/// We are getting starting state and sequence of bits from txt files
	FILE *des_1 , *des_2 , *des_3 , *des_4 , *des_5 , *des_6;
		int  indexstate;
	des_1 = fopen("state.txt", "r"); // We are opening state.txt, we need to get index of starting state
		while (fscanf(des_1, "%d", &indexstate) != EOF);// We are getting stuff until file is ended
		//printf(" indeks%d\n",indexstate);
		fclose(des_1);
	int numberofBits;
	 des_2 = fopen ("numberofBits.txt", "r");
		 while (fscanf(des_2, "%d", &numberofBits) != EOF);
		 //printf(" Liczba bitów zakodowanych %d\n",numberofBits-1);
		 fclose(des_2);
	 int numberofsymbols;
		des_5 = fopen ("Nsymbols.txt", "r");
		 while (fscanf(des_2, "%d", &numberofsymbols) != EOF);
			printf("Liczba symboli %d",numberofsymbols);
		fclose(des_5);

	des_3 = fopen("Bits.txt","r");
	des_4 = fopen("symbols.txt" , "w");
	des_6 = fopen("Numbers.txt" , "r");
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
			createAlphabet(&alphabet,letters,numbers,NbStates);
			spread(&alphabet,numbers,NbStates);
			for (int i = 0 ; i<NbStates;i++)
				{
					printf(" po spredzie %d\n",alphabet[i]);
				}
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
		    numberofBits--;
for( numberofBits ; numberofBits>0;numberofBits+=(-NbBits[indexstate]))
{
		    	for(i = 0 ; i<NbBits[indexstate];i++)
		    	{
		    		Bits[i] = getc(des_3)-48;
		    		printf("%d\n", Bits[i]);
		    	}
					 NextState=0;
					DecodingSymbol(&symbol, alphabet , indexstate);
					fprintf(des_4, "%d" , symbol);
				    NextStateofDecoder( &NextState, NewX,  NbBits, Bits, indexstate);
				    indexstate = NextState-NbStates;
				    

}
fprintf(des_4," %d",NextState);
fclose(des_3);
fclose(des_4);

}

