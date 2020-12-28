#include <stdio.h>
#include <math.h>
#include <string.h>

int XOR(int a, int b)
{
	if (a == 1 && b == 1 || a == 0 && b == 0)
		return 0;
	else
		return 1;
}

void printPolinom(int* polinom, int n, int nUkupno)
{
	for (int i = 0; i <= nUkupno; i++)
	{
		if (n < nUkupno && i < nUkupno - n)
			printf("     \t");
		else
		{
			printf("%dx^%d", polinom[i - (nUkupno - n)], nUkupno - i);
			if (i != nUkupno)
				printf(" +\t");
		}
	}
	printf("\n");
}

sabiranjePolinoma( int* P0, int np0, int* P1, int np1, int *Rez, int nrez)
{
	for (int i = 0; i <= nrez; i++)
	{
		if (i >= np0 - np1)
		{
			Rez[i] = XOR(P0[i], P1[i - (np0-np1)]);
		}
		else
		{
			Rez[i] = P0[i];
		}
	}
	//printPolinom(Rez, nrez, nrez);

}

void shiftRight(int* polinom, int n)
{
	for (int j = n - 1; j > 0; j--)
	{
		polinom[j] = polinom[j - 1];
	}
	polinom[0] = 0;
}

void shiftLeft(int* polinom, int n)
{
	for (int j = 0; j < n-1; j++)
	{
		polinom[j] = polinom[j +1];
	}
	polinom[n-1] = 0;
}

mnozenjePolinoma(int* P0, int np0, int* P1, int np1, int* Rez)
{
	int nrez = np1 + np0 + 1;
	int* pomShift;//* pomIteracija;
	pomShift = malloc(nrez * sizeof(int));
	//Rez = malloc(nrez * sizeof(int));

	for (int i = 0; i <= nrez; i++)
	{
		if (i <= np1)
			pomShift[i] = P1[i];
		else
			pomShift[i] = 0;

		Rez[i] = 0;

	}

//	printPolinom(pomShift, nrez, nrez);
	//printPolinom(Rez, nrez, nrez);

	for (int i = 0; i <= np0; i++)
	{
		if (P0[i] == 0)
		{
			
		}
		else
		{
			sabiranjePolinoma(Rez, nrez, pomShift, nrez, Rez, nrez);

			//printf("\ni= %d, +\t", i);
			//printPolinom(Rez, nrez, nrez);
		}
		//int p = pomShift[0];
		shiftRight(pomShift, nrez);

		//printf("\ni= %d, s\t", i);
		//printPolinom(pomShift, nrez, nrez);
	}


}

int jeVeci(int* polinom1, int* polinom2, int n)
{
	for (int i = 0; i < n; i++)
	{
		//printf("%d ili %d ?\n", polinom1[i], polinom2[i]);
		if (polinom1[i] > polinom2[i])
			return 1;
		if (polinom2[i] > polinom1[i])
			return 2;
	}
	return 0;
}


void deljenjePolinoma(int* P0, int np0, int* P1, int np1, int* Rez, int nrez, int * ost, int nost)
{
	int* pomShift, * pomIteracija;
	int dodatak = (np0 - np1);
	pomShift = malloc((np0 + dodatak) * sizeof(int));
	pomIteracija = malloc((np0 + dodatak) * sizeof(int));

	for (int i = 0; i <= np0; i++)
	{
		if (i <= np1)
			pomShift[i] = P1[i];
		else
			pomShift[i] = 0;

		pomIteracija[i] = P0[i];

	}
	for (int i = 0; i < dodatak; i++)
	{
		pomIteracija[i + np0+1] = 0;
		pomShift[i + np0 + 1] = 0;
	}

	//printPolinom(pomIteracija, np0+dodatak, np0 + dodatak);
	//printPolinom(pomShift, np0 + dodatak, np0 + dodatak);
	

	//Rez[0] = 1;

	for (int i = 0; i <= dodatak; i++)
	{
		if (pomIteracija[i] == 1)
		{
			Rez[i] = 1;
			sabiranjePolinoma(pomIteracija, np0+dodatak, pomShift, np0+dodatak, pomIteracija, np0+dodatak);
			shiftRight(pomShift, np0+dodatak);
			/*for (int j = 0; j <= np0; j++)
			{
				if (j < np1)
					pomShift[j] = P1[j];
				else
					pomShift[j] = 0;
			}*/
		}
		else
		{
			Rez[i] = 0;
			//shiftRight(pomIteracija, np0);
			shiftRight(pomShift, np0+dodatak);
			
		}

		printf("\nIteracija %d, polinomi:\n", i);
		if(i < dodatak)
			pomIteracija[np1 + i + 1] = P0[np1 + i + 1];
		//printPolinom(pomIteracija, np0+dodatak, np0+dodatak);
		//printPolinom(pomShift, np0, np0);
	}

	for (int i = 0; i <= np1; i++)
	{
		ost[i] = pomIteracija[(np0 - np1)+i+1];
	}
}

int main()
{
	//                  8  7  6  5  4  3  2  1  0
	int polinomGF[9] = { 1, 0, 0, 0, 1, 1, 0, 1 , 1 };
	int* polinomUnesi;
	int* polinomRezultat;
	int* polinomOstatak;
	int* polinomPom;
	int validna = 0;
	int n = 0;
	int pomn = 0;
	int br = 0;
	int i = 0;
	int pom;
	char odgovor;

	printf("Sabiranje, mnozenje i deljenje polinoma\n\n");
	while (!validna)
	{
		printf("Stepen drugog polinoma? \n");

		scanf("%d", &n);

		if (n > 0)
			validna = 1;
		else
			printf("Unesite celobrojnu pozitivnu vrednost\n");
	}
	br = n - 1;

	validna = 0;
	printf("Unesite konstante polinoma 1 ili 0, konstanta uz x^%d je podrazumevano 1\n", n);
	polinomUnesi = malloc(n * sizeof(int));
	polinomUnesi[i] = 1;
	i++;

	while (!validna)
	{
		printf("Konstanta uz x^%d\n", br);
		scanf("%d", &pom);

		if (pom == 0 | pom == 1)
		{
			polinomUnesi[i] = pom;
			i++;
			br--;

			if (br == -1)
				validna = 1;
		}

	}

	if (n > 8)
		pomn = n;
	else
		pomn = 8;

	printf("Korisceni polinomi su\n");
	printf("P0:\t");

	printPolinom(polinomUnesi, n, pomn);

	printf("P1:\t");

	for (i = 0; i <= pomn; i++)
	{
		if (8 < pomn && i < pomn - 8)
			printf("     \t");
		else
		{
			printf("%dx^%d", polinomGF[i - (pomn - 8)], pomn - i);
			if (i != pomn)
				printf(" +\t");
		}
	}
	printf("\n");

	validna = 0;
	while (!validna)
	{
		printf("\nZa sabiranje polinoma uneti S, za mnozenje M, za delje D, za izlaz Q\n");

		scanf("%c", &odgovor);
		if (odgovor == ' ' | odgovor == '\n')
			scanf("%c", &odgovor);


		if (odgovor == 'Q')
		{
			validna = 1;
		}
		else if (odgovor == 'S')
		{
			if (n > 8)
			{
				pomn = n;
				polinomRezultat = malloc(pomn * sizeof(int));
				sabiranjePolinoma(polinomUnesi, n, polinomGF, 8, polinomRezultat, n);
			}
			else
			{
				pomn = 8;
				polinomRezultat = malloc(8 * sizeof(int));
				sabiranjePolinoma(polinomGF, 8, polinomUnesi, n, polinomRezultat, 8);
			}

			printf("Rezultujuci polinom\n");
			printf("Rez:\t");

			for (i = 0; i <= pomn; i++)
			{ 
				printf("%dx^%d", polinomRezultat[i], pomn - i);
				if (i != pomn)
					printf(" +\t");
			}
			printf("\n");
		}
		else if (odgovor == 'M')
		{
			
			pomn = 8+n;
			polinomRezultat = malloc(pomn * sizeof(int));
			mnozenjePolinoma(polinomUnesi, n, polinomGF, 8, polinomRezultat);
			

			printf("Rezultujuci polinom\n");
			printf("Rez:\t");

			for (i = 0; i <= pomn; i++)
			{
				printf("%dx^%d", polinomRezultat[i], pomn - i);
				if (i != pomn)
					printf(" +\t");
			}
			printf("\n");
		}
		else if (odgovor == 'D')
		{
			if (n > 8)
			{
				pomn = n - 8;
				polinomRezultat = malloc((pomn+1) * sizeof(int));
				polinomOstatak = malloc(8 * sizeof(int));
				deljenjePolinoma(polinomUnesi, n, polinomGF, 8, polinomRezultat, pomn, polinomOstatak, 8);


				printf("Rezultujuci polinom\n");
				printf("Rez:\t");

				for (i = 0; i <= pomn; i++)
				{
					printf("%dx^%d", polinomRezultat[i], pomn - i);
					if (i != pomn)
						printf(" +\t");
				}
				printf("\n");
				printf("Ostatak:\t");

				for (i = 0; i <= 7; i++)
				{
					printf("%dx^%d", polinomOstatak[i], 7 - i);
					if (i != 7)
						printf(" +\t");
				}



				polinomPom = malloc(n * sizeof(int));

				printf("\nProvera\n\t");
				printPolinom(polinomRezultat, pomn, n);
				printf(" * ");
				printPolinom(polinomGF, 8, n);
				mnozenjePolinoma(polinomRezultat, pomn, polinomGF, 8,  polinomPom);
				printf(" = ");
				printPolinom(polinomPom, pomn + 8, pomn +8);

				sabiranjePolinoma(polinomPom, pomn + 8, polinomOstatak, 7, polinomPom, n);
				printf(" + ");
				printPolinom(polinomOstatak, 7, n);
				printf(" = ");
				printPolinom(polinomPom, n, n);
			}
			else
			{
				pomn = 8 - n;
				polinomRezultat = malloc((pomn+1) * sizeof(int));
				polinomOstatak = malloc(pomn * sizeof(int));
				deljenjePolinoma(polinomGF, 8, polinomUnesi, n, polinomRezultat, pomn, polinomOstatak, n);


				printf("Rezultujuci polinom\n");
				printf("Rez:\t");

				/*for (i = 0; i <= 8; i++)
				{
					printf("%dx^%d", polinomRezultat[i], 8 - i);
					if (i != pomn)
						printf(" +\t");
				}
				printf("\n");
				printf("Ostatak:\t");

				for (i = 0; i <= 7; i++)
				{
					printf("%dx^%d", polinomOstatak[i], 7 - i);
					if (i != n)
						printf(" +\t");
				}*/
				for (i = 0; i <= pomn; i++)
				{
					printf("%dx^%d", polinomRezultat[i], pomn - i);
					if (i != pomn)
						printf(" +\t");
				}
				printf("\n");
				printf("Ostatak:\t");

				for (i = 0; i <= pomn - 1; i++)
				{
					printf("%dx^%d", polinomOstatak[i], (pomn - 1) - i);
					if (i != (pomn-1))
						printf(" +\t");
				}

				polinomPom = malloc(8 * sizeof(int));

				printf("\nProvera\n\t");
				printPolinom(polinomRezultat, pomn, 8);
				printf(" * ");
				printPolinom(polinomUnesi, n, 8);
				mnozenjePolinoma(polinomRezultat, pomn, polinomUnesi, n, polinomPom);
				printf(" = ");
				printPolinom(polinomPom, pomn  + n, pomn + 1 + n);

				sabiranjePolinoma(polinomPom, pomn+1+n, polinomOstatak, pomn, polinomPom, 8);
				printf(" + ");
				printPolinom(polinomOstatak, pomn-1, 8);
				printf(" = ");
				printPolinom(polinomPom, 8, 8);
			}
			

			
		}
	}

}
