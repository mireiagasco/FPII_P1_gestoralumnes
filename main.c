#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gestoralumnes.h"	/*Arxiu que inclou les declaracions de tipus i les cap�aleres*/
#include <locale.h>
#include <windows.h>

int main()
{
	/*Creem i inicialitzem a nul els dos punters que ens indicaran on comen�a i acaba la llista*/
	node_t* llista_i = NULL;
	node_t* llista_f = NULL;

	/*Carreguem les dades del fitxer, en cas que n'hi hagi*/
	carregarDades(&llista_i, &llista_f);		

	/*Creem un punter que ens indiqui la direcci� de l'�ltim node/alumne buscat i
	l'inicialitzem a NULL, ja que encara no hem buscat res*/
	node_t* ultim = NULL;

	/*Per tal de permetre que l'usuari trii una opci� del men� que es mostrar�, cal tenir una variable
	que reculli el n�mero que introdueixi per teclat.  Per tal d'evitar problemes, l'inicialitzem a un
	valor impossible*/
	char opcio = -1;

	/*Per fer que mostri el men� despr�s de cada acci�, cal fer un bucle que comenci i es mantingui en
	true fins que l'usuari indiqui que vol sortir (aix� es far� amb el cas 0 de la opci�*/
	bool continuar = true;

	/*Ara s�, iniciem el bucle que mostrar� el men� i demanar� una opci� per despr�s dur a terme la funci�
	corresponent*/
	while (continuar)
	{
		system("cls");
		mostrarMenu();
		opcio = demanarOpcio(opcio);
		system("cls");
		switch (opcio)
		{
		case '0': 
			guardarDades(llista_i);
			continuar = false;
			break;
		case '1': 
			afegirAlumne(&llista_i, &llista_f,&ultim);
			break;
		case '2': 
			ultim = buscarDni(llista_i,&ultim);
			system("pause");
			break;
		case '3': 
			buscarNom(llista_i, &ultim);
			break;
		case '4': 
			veureUltim(ultim);
			system("pause");
			break;
		case '5': 
			eliminarUltim(ultim);
			break;
		case '6':
			mostrarLlista(llista_i, llista_f);
			system("pause");
			break;
		case '7':
			esborrarLlista(&llista_i,&llista_f);
			break;
		default:
			printf("\n Valor no valid, indiqui un numero entre 0 i 7 \n");
		}
	}
	return 0;
}
