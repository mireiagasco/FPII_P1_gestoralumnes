#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gestoralumnes.h"

/*Funci� que comprova si dos DNI s�n iguals i retorna un boole�*/
bool iguals(dni_t dni2, node_t* p_lis)
{
	bool iguals = (dni2.num == p_lis->alumne.dni.num);
	return(iguals);
}

/*Funci� que comprova que el dni de la llista no sigui m�s gran que el que
estem col�locant (aix� voldria dir que ens hem passat) i retorna un boole�*/
bool mesPetit(dni_t dni2, node_t* p_lis)
{
	bool petit = false;
	if (dni2.num>p_lis->alumne.dni.num)
	{
		petit = true;
	}
	return(petit);
}

/* Funci� que comprova si ja hi ha un alumne amb el dni introduit a la llista i
retorna un boole� */
bool cerca(node_t * list, dni_t dni1, node_t **ultim)
{
	node_t* p_list = list;
	bool igual;

	/*Mentre no siguin iguals i no ens passem*/
	while ((p_list != NULL) && (!iguals(dni1, p_list)) && (mesPetit(dni1, p_list)))
	{
		p_list = p_list->next;
	}

	/*Si s�n iguals, guardem el node trobat a ultim*/
	if ((p_list != NULL) && iguals(dni1, p_list))
	{
		*ultim = p_list;
		igual = iguals(dni1, p_list);
	}

	/*Si no ho s�n, guardem el node seguent per si el volem col�locar*/
	else
	{
		if (p_list==NULL)
		{
			*ultim = NULL;
		}
		else
		{
			*ultim = p_list;
		}
		igual = false;
	}
		
	return(igual);
}