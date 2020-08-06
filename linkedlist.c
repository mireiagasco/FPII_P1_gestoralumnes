#include <stdio.h>
#include <stdlib.h>
#include "gestoralumnes.h"
#include <stdbool.h>

/*Aquest fitxer cont� les funcions b�siques de la llista enlla�ada, desde crear nodes fins a treballar amb ells*/

/*Funci� que crea un nou node*/
/*acabada*/
node_t *crearNode()
{
	node_t *nou_alumn = (node_t*)malloc(sizeof(node_t));
	if (nou_alumn == NULL)
	{
		printf("\n Error.No hi ha prou espai a la memoria \n");
		exit(EXIT_FAILURE);
	}
	return(nou_alumn);
}

/*Acci� que inicialitza un nou node amb les dades que l'usuari introdueix per teclat*/
/*acabada*/
node_t *inicialitzarNode(node_t* p_alum)
{
	node_t* p_alumne = p_alum;
	p_alumne->next = NULL;
	p_alumne->previous = NULL;
	/*Demanem el nom de l'alumne*/
	printf("Indiqui el nom complert de l'alumne \n");
	scanf(" %[^'\n']", p_alumne->alumne.nom);

	canviMajuscules(p_alumne->alumne.nom);
	quitarGuiones(p_alumne->alumne.nom);
	
	/*Demanem el DNI, tot junt i sense espais, de forma que el primer fgets agafar� els 8 n�meros
	i getchar agafar� la lletra.  Amb la funci� calcularLletra calculem la lletra que correspon al
	n�mero introduit i, si aquesta no coincideix amb la lletra introduida, es dona un missatge 
	d'error i es torna a demanar el DNI. La variable lletra_c contindr� la lletra calculada.*/
	char lletra_c = 'A';
	p_alumne->alumne.dni.lletra = 'B';
		while ((lletra_c!=p_alumne->alumne.dni.lletra ) )
		{
			printf("Indiqui el DNI de l'alumne (escrigui el numero i la lletra junts, sense separacio) \n");
			scanf("%d", &p_alumne->alumne.dni.num);
			lletra_c = calcularLletra(p_alumne->alumne.dni.num);
			p_alumne->alumne.dni.lletra = getchar();
			if (lletra_c != p_alumne->alumne.dni.lletra)
			{
				printf("Hi ha algun error amb el DNI, no coincideixen el numero i la lletra \n");
			}
		}
	
	/*Demanem el correu*/
	printf("Introdueixi el correu de l'alumne \n");
	scanf(" %[^'\n']", p_alumne->alumne.correu);

	/*Demanem la nota*/
	printf("Introdueixi la nota de l'alumne \n");
	bool correcte=true;
	while (correcte)
	{
		scanf(" %f", &p_alumne->alumne.nota);
		if (p_alum->alumne.nota<-1 || p_alum->alumne.nota>11)
		{
		printf("Hi ha algun error amb la nota, fora de rang\n");
		}else{
			correcte=false;
		}
	}
	/*Demanem la data de naixement en el format: XX/XX/XXXX (dia, mes, any)*/
	printf("Introdueixi la data de naixement de l'alumne en format XX/XX/XXXX (dia/mes/any) \n");
	scanf(" %[^'\n']", &p_alumne->alumne.data_naix);
	printf("FECHA: %s",p_alumne->alumne.data_naix);

	/*Demanem el sexe (D, H o X) i comprovem que s'ha introdu�t una lletra correcta*/
	char sexe = 'K'; /*Inicialitzem a un valor impossible*/
	while (sexe!='D' && sexe!='H' && sexe!='X')	/*Mentre no s'introdueixi un valor v�lid*/
	{
		printf("Introdueixi el sexe de l'alumne (D per a dona, H per a home i X per a qualsevol altra cosa)\n");
		scanf(" %c", &sexe);
		if (sexe != 'D' && sexe != 'H' && sexe != 'X')	/*Si el valor introdu�t no �s v�lid, donem error*/
		{
			printf("Valor no valid \n");
		}
	}
	p_alumne->alumne.sexe = sexe;

	return(p_alumne);
}

/*Funci� que col�loca el primer node de la llista, en cas que aquesta estigui buida, i
retorna el punter al node modificat*/
node_t* colocarPrimer(node_t *p_alum, node_t **p_lis_i, node_t **p_lis_f)
{
	/*Dirigim els punters de la llista al nou alumne*/
	*p_lis_i = p_alum;
	*p_lis_f = p_alum;

	/*Inicialitzem els punters de l'alumne*/
	node_t* alumne = p_alum;
	alumne->next = NULL;
	alumne->previous = NULL;

	return(alumne);
}

/*Funci� que col�loca un node al final de la llista, si aquesta ja cont� altres nodes, i
retorna el punter al node modificat*/
node_t* colocarFinal(node_t* p_alum, node_t** p_lis_f)
{
	node_t* alumne = p_alum;

	alumne->next = NULL; //El punter a next ser� nul, ja que �s l'�ltim node de la llista
	alumne->previous = *p_lis_f; //El punter a previ apuntar� al que abans era l'�ltim node
	*p_lis_f = alumne; //El nou alumne passar� a ser l'�ltim node
	node_t* anterior = alumne->previous;
	anterior->next = alumne; //El punter next del que era l'�ltim apunta al nou �ltim

	return(alumne);
}

/*Funci� que col�loca un node al mig de la llista i retorna el punter al node modificat*/
node_t* colocarMig(node_t* p_alum, node_t* p_ulti)
{
	node_t* alumne = p_alum;
	node_t* seguent = p_ulti;

	alumne->previous = seguent->previous; //El previ del nou alumne ser� el previ de l'alumne que estava en la seva posici�
	alumne->next = seguent; //El next del nou alumne ser� l'alumne que estava en la seva posici�
	seguent->previous = alumne; //El previ de l'alumne que estava en la seva posici� passa a ser el nou alumne
	node_t* anterior = alumne->previous;
	anterior->next = alumne; //El punter a next del node previ passa a apuntar a l'alumne

	return(alumne);
}

/*Funci� que col�loca un node a l'inici de la llista, si ja cont� altres nodes, i retorna 
el punter al node modificat*/
node_t* colocarInici(node_t* p_alum, node_t** p_lis_i)
{
	node_t* alumne = p_alum;

	alumne->previous = NULL; //Al ser el primer node de la llista, el seu punter a previ ha de ser nul
	alumne->next = *p_lis_i; //El punter next de l'alumne ha d'apuntar a l'anterior primer node
	*p_lis_i = alumne; //El punter que marca l'inici de la llista ha d'apuntar a l'alumne
	node_t* seguent = alumne->next;
	seguent->previous = alumne; //El punter a previ de l'anterior primer node ha d'apuntar a l'alumne

	return(alumne);
}

/*Funci� que col�loca un node all� on pertoqui*/
node_t *colocarNode(node_t *p_alu, node_t **p_list_f, node_t **p_list_i)
{
	node_t* p_ult = NULL;
	node_t* p_al = p_alu;
	/*Si la llista est� buida, cal col�locar el primer node*/
	if (*p_list_i == NULL)
	{
		p_al = colocarPrimer(p_al,p_list_i, p_list_f);
	}

	/*Si no ho est�, cal buscar el lloc adient per col�locar-lo*/
	else
	{
		/*Busquem si l'alumne introduit existeix o no (sempre segons el num. de DNI)*/
		bool existeix = cerca(*p_list_i, p_al->alumne.dni, &p_ult);

		/*En cas que ja existeixi l'alumne*/
		if (existeix)
		{
			printf("Aquest alumne ja existeix\n");
		}

		/*Si no existeix, voldr� dir que ens hem passat buscant a la llista i que el punter que
		ha quedat guardat a p_ultim �s el del node que hauria de ser el seg�ent, de forma que hem
		de col�locar el nou node davant d'aquest*/
		else
		{
			/*Si el punter a �ltim �s nul, vol dir que el nou alumne ha de ser l'�ltim de la llista*/
			if (p_ult == NULL)
			{
				p_al = colocarFinal(p_al, p_list_f);
			}
			else
			{
				/*Si ni el punter a �ltim ni el seu punter a previ s�n nuls, cosa que vol dir que el nou
				node s'ha de col�locar en un punt al mig de la llista*/
				if (p_ult != NULL && p_ult->previous != NULL)
				{
					p_al = colocarMig(p_al, p_ult);
				}
				else
				{
					/*Si el puner a �ltim no �s nul, per� el seu punter a previ s� que ho �s, vol dir que ens
					trobem a l'inici de la llista i que el nou alumne ha de ser el primer*/
					if (p_ult != NULL && p_ult->previous == NULL)
					{
						p_al = colocarInici(p_al, p_list_i);
					}
				}
			}
						
		}
	}
	return (p_al);
}

/*Acci� que elimina un node qualsevol de la llista*/
/*acabada*/
void eliminarNode(node_t* p_node)
{
	/*Creem dos punters que ens assenyalin al node previ i al seguent del node que es vol
	eliminar*/
	node_t* previ = NULL;
	node_t* seguent = NULL;

	/*Si el punter a next del node no �s nul, l'assignem a seg�ent, si ho �s, es queda a nul*/
	if (p_node->next != NULL)
	{
		seguent = p_node->next;
	}
	/*Si el punter a previ del node no �s nul l'assignem a previ, si ho �s, es queda a nul*/
	if (p_node->previous != NULL)
	{
		previ = p_node->previous;
	}

	/*Modifiquem els punters d'aquests dos nodes de forma que deixin d'apuntar al node que
	es vol eliminar i passin a apuntar-se entre ells*/
	if (previ != NULL)
	{
		previ->next = seguent;
	}
	if (seguent!= NULL)
	{
		seguent->previous = previ;
	}
	
	/*Alliberem la mem�ria del node que es vol eliminar*/
	free(p_node);
}

/*Funci� que comprova si la llista est� buida i retorna un boole� segons ho estigui o no*/
/*acabada*/
bool llistaBuida(node_t* p_p)
{
	bool buida;
	if (p_p == NULL)
	{
		buida = true;
	}
	else
	{
		buida = false;
	}
	return(buida);
}

/*Acci� que mostra tota la llista (de inici a final)*/
void mostrarLlista_i(node_t* inici_llista)
{
	node_t* p_llista;
	for (p_llista = inici_llista; p_llista != NULL; p_llista = p_llista->next)
	{
		escriureDades(p_llista);
	}
}

/*Acci� que mostra tota la llista (de final a inici)*/
void mostrarLlista_f(node_t* final_llista)
{
	node_t* p_llista;
	for (p_llista = final_llista; p_llista != NULL; p_llista = p_llista->previous)
	{
		escriureDades(p_llista);
	}
}