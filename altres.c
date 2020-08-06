#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gestoralumnes.h"

/*Funció que comprova si el DNI s'ha introduit correctament i retorna un booleà*/
dni_t demanarIVerificarDni()
{
	bool correcte = false;
	dni_t dnid;

	/*Mentre no introdueixin el DNI correcte*/
	while (!correcte)
	{
		/*Demanem el DNI*/
		printf("Introdueixi el DNI, (00000000X)\n");
		scanf("%d", &dnid.num);
		dnid.lletra = getchar();

		/*Comprovem que la lletra i el número coincideixen*/
		char lletra_c = calcularLletra(dnid.num);
		if (dnid.lletra == lletra_c)
		{
			correcte = true;
		}
		else
		{
			printf("Error amb el DNI, no coincideixen el número i al lletra");
		}
	}
	return(dnid);
}

/*Funció que calcula la lletra que tocaria a partir del número de DNI i
en retorna el resultat*/
char calcularLletra(int numero)
{
	char lletra;
	lletra = numero % 23;
	switch (lletra)
	{
	case 0:lletra = 'T';
		break;
	case 1:lletra = 'R';
		break;
	case 2: lletra = 'W';
		break;
	case 3:lletra = 'A';
		break;
	case 4:lletra = 'G';
		break;
	case 5:lletra = 'M';
		break;
	case 6:lletra = 'Y';
		break;
	case 7:lletra = 'F';
		break;
	case 8:lletra = 'P';
		break;
	case 9:lletra = 'D';
		break;
	case 10:lletra = 'X';
		break;
	case 11:lletra = 'B';
		break;
	case 12:lletra = 'N';
		break;
	case 13:lletra = 'J';
		break;
	case 14:lletra = 'Z';
		break;
	case 15:lletra = 'S';
		break;
	case 16:lletra = 'Q';
		break;
	case 17:lletra = 'V';
		break;
	case 18:lletra = 'H';
		break;
	case 19:lletra = 'L';
		break;
	case 20:lletra = 'C';
		break;
	case 21:lletra = 'K';
		break;
	case 22:lletra = 'E';
		break;
	default:printf("Error");
	}
	return (lletra);
}

/*Funció que comprova que l'usuari hagi introduit un valor vàlid a l'hora de
confirmar l'eliminació de nodes*/
bool valorValid(char valor)
{
	bool valid;
	if ((valor != 's') && (valor != 'n') && (valor != 'S') && (valor != 'N'))
	{
		valid = false;
	}
	else
	{
		valid = true;
	}
	return(valid);
}

/*Funció que demana confirmació per fer alguna cosa i retorna un booleà*/
bool confirmacio()
{
	/*Suposem que ja s'ha demanat la confirmació del que sigui i llegim el caràcter*/
	char caracter;
	scanf(" %c", &caracter);
	while (!valorValid(caracter))
	{
		printf("Escrigui s per a si i n per a no \n");
		scanf(" %c", &caracter);
	}
	return(caracter);
}

/*Funció que passa el text introduit a majúscules*/
void canviMajuscules(char frase[])
{
	size_t cont = 0;
	while (frase[cont]!='\0')
	{
		if ((frase[cont]>='a')&&(frase[cont]<='z'))
		{
			frase[cont] = frase[cont] - ('a' - 'A');
		}
		cont++;
	}
}

/*Funció que busca a la llista un nom que comenci igual que el que es passa
a l'acció*/
void similar(char n[], node_t* plst, int* n_alum, node_t** pul)
{
	size_t cont = 0;
	bool iguals = true;

	/*Mentre no s'acabi el nom donat i coincideixi tot*/
	while ((n[cont]!='\0')&&(iguals))
	{
		if (n[cont]==plst->alumne.nom[cont])
		{
			cont++;
		}
		else
		{
			iguals = false;
		}
	}
	/*Si hi ha conicidència*/
	if (iguals)
	{
		/*Augmentem el número d'alumnes trobats*/
		(*n_alum)++;

		/*Si és el primer alumne que trobem, el guardem al punter pul*/
		if (*n_alum == 1)
		{
			*pul = plst;
		}
	}
}

/*Acció que canvia els underscores d'un string per espais*/
void quitarGuiones(char tabla[])
{
	int cont = 0;
	while (tabla[cont] != '\0')
	{
		if (tabla[cont] == '_')
		{
			tabla[cont] = ' ';
		}
		cont++;
	}
}

/*Acció que canvia els espais d'un string per underscores*/
void ponerGuiones(char tabla[])
{
	int cont = 0;
	while (tabla[cont] != '\0')
	{
		if (tabla[cont] == ' ')
		{
			tabla[cont] = '_';
		}
		cont++;
	}
}

/*Acció que mostra les dades d'un alumne per teclat*/
void escriureDades(node_t* p_ult)
{
	quitarGuiones(p_ult->alumne.nom);
	printf("NOM: %s \n", p_ult->alumne.nom);
	printf("DNI: %d%c \n", p_ult->alumne.dni.num, p_ult->alumne.dni.lletra);
	printf("Correu: %s \n", p_ult->alumne.correu);
	printf("Nota: %.1f \n", p_ult->alumne.nota);
	printf("Data de naixement: %s \n", p_ult->alumne.data_naix);
	printf("Sexe: %c \n", p_ult->alumne.sexe);
	printf("\n");
}

/*Acció que escriu les dades d'un node en un fitxer*/
void fEscriureDades(node_t* p_p, FILE* fit)
{
	ponerGuiones(p_p->alumne.nom);
	fprintf(fit, "%s ", p_p->alumne.nom);
	fprintf(fit, "%d%c ", p_p->alumne.dni.num, p_p->alumne.dni.lletra);
	fprintf(fit, "%s ", p_p->alumne.correu);
	fprintf(fit, "%3f ", p_p->alumne.nota);
	fprintf(fit, "%s ", p_p->alumne.data_naix);
	fprintf(fit, "%c ", p_p->alumne.sexe);
	fprintf(fit, "\n");
}

/*Acció que mostra el nom de l'alumne buscat*/
void mostrarNom(char nombre[])
{
	printf("~~Alumne trobat~~\n");
	printf(" %s \n", nombre);
}