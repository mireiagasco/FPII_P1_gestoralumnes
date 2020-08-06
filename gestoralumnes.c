#include <stdio.h>
#include <stdlib.h>
#include "gestoralumnes.h"
#include <string.h>
#include <stdbool.h>

/*Aquest fitxer cont� els procediments principals del gestor d'alumnes, �s a dir, els que es troben directament al main.c*/

/*Accio que mostra el men� d'opcions per pantalla.*/
/*(acabada)*/
void mostrarMenu()
{
	printf("----Gestor Alumnes----\n");
	printf("1)Afegir alumne\n2)Buscar DNI\n3)Buscar per nom\n4)Veure ultim alumne buscat\n5)Eliminar ultim alumne buscat\n6)Veure tota la llista\n7)Esborrar tota la llista\n0)Sortir\n");
}

/*Accio que carrega les dades d'alumnes, guardades anteriorment en un fitxer, a la llista per poder treballar amb elles*/
void carregarDades(node_t **p_llista_i, node_t **p_llista_f)
{
	FILE* fitxer = fopen("llista.txt", "r");
	node_t* p1_llista_i = *p_llista_i;
	node_t* p1_llista_f = *p_llista_f;
	/*En cas que sigui nul, no cal fer res, ja que voldr� dir que �s el primer cop que s'executa el programa i que no hi
	ha cap llista a carregar.  Si no ho �s, cal carregar les dades*/
	if (fitxer!=NULL)
	{
		while (!feof(fitxer))
		{
			node_t* p_alumne = crearNode();
			if (fscanf(fitxer, " %s%d%c%s%f%s %c\n", p_alumne->alumne.nom, &p_alumne->alumne.dni.num, &p_alumne->alumne.dni.lletra, p_alumne->alumne.correu, &p_alumne->alumne.nota, &p_alumne->alumne.data_naix, &p_alumne->alumne.sexe))
			{
				quitarGuiones(p_alumne->alumne.nom);
				p_alumne = colocarNode(p_alumne, &p1_llista_f, &p1_llista_i);
				*p_llista_i=p1_llista_i;
				*p_llista_f=p1_llista_f;
			}
		}
		fclose(fitxer);
	}
}

/*Funci� que demana un n�mero per teclat i en retorna el resultat despr�s de comprovar que �s correcte*/
/*acabada*/
char demanarOpcio(char numero)
{ int ch;
	printf("\nIndiqui quina accio vol realitzar\n");
	scanf(" %c", &numero);
	while((ch = getchar() !='\n'));
	
	return(numero);
}

/*Acci� que afegeix un alumne a la llista*/
void afegirAlumne(node_t **p_llista_i, node_t **p_llista_f, node_t **p_ultim)
{
	/*Creem un punter al que ser� el nou node i reservem la mem�ria adient amb la funci� crearNode()*/
	node_t *nou_alumne = crearNode();

	/*Inicialitzem el nou node amb les dades que ens introdueixi l'usuari per teclat*/
	node_t *alumne_nou = inicialitzarNode(nou_alumne);
	node_t* p1_llista_i = *p_llista_i;
	node_t* p1_llista_f = *p_llista_f;

	alumne_nou = colocarNode(alumne_nou, &p1_llista_f, &p1_llista_i);
	*p_llista_i = p1_llista_i;
	*p_llista_f = p1_llista_f;
}

/*Acci� que busca un alumne pel DNI. Si el troba mostrar� el nom de l'alumne, sin�, informar� amb un missatge per pantalla*/
node_t *buscarDni(node_t *p_llista)
{
	dni_t dni;
	bool correcte = false;
	bool existeix;
	node_t* p_ultim = p_llista;

	/*Demanem el DNI i verifiquem que s'ha introduit correctament*/
	dni = demanarIVerificarDni();
	system("cls");

	/*Comprovem si existeix a la llista*/
	existeix = cerca(p_llista, dni, &p_ultim);

	/*En cas que existeixi, indiquem el nom de l'alumne trobat*/
	if (existeix)
	{
		mostrarNom(p_ultim->alumne.nom);
	}

	/*Si no existeix, ho indiquem per pantalla*/
	else
	{
		printf("No hi ha cap alumne registrat amb aquest DNI \n");
	}
	return(p_ultim);
}

/*Acci� que busca un alumne pel nom, sense distingir entre maj�scules/min�scules i contemplant tamb� prefixos (no cal escriure
el nom sencer per obtenir el resultat). Si es troba un alumne, se'n mostrar� el nom complert, si se'n troben diversos que
coincideixen es mostrar� el nom del primer i s'indicar� el n�mero d'alumnes que coincideixen i, si no es troba cap coincid�ncia,
s'informar� amb un missate per pantalla*/
void buscarNom(node_t *list, node_t** p_ultim)
{
	char nom[MAX_CHAR];
	int n_alumnes = 0;
	node_t* plist = list;
	node_t* actual = NULL;

	/*Obtenim el nom i el passem tot a maj�scules*/
	printf("Introdueixi el nom de l'alumne \n");
	scanf(" %[^'\n']", nom);
	system("cls");
	canviMajuscules(nom);
	/*quitarGuiones(nom);*/

	while (plist!=NULL)
	{
		similar(nom, plist, &n_alumnes, &actual);
		plist = plist->next;
	}

	if (n_alumnes==1)
	{
		mostrarNom(actual->alumne.nom);
	}
	else
	{
		if (n_alumnes!=0)
		{
			printf("Hi ha %d coincidencies \n", n_alumnes);
		}
		else
		{
			printf("No s'ha trobat cap alumne\n");
		}
	}
	system("pause");

	/*Guardem el punter a l'�ltim alumne trobat a p_ultim*/
	*p_ultim = actual;
}

/*Acci� que mostra l'�ltim alumne buscat. Si la darrera cerca nom�s tenia una coincid�ncia, es mostraran totes les dades de
l'alumne en q�esti� i, si se n'havien trobat diversos, es mostraran les dades del primer alumne coincident amb la cerca*/
/*acabada*/
void veureUltim(node_t *p_ultim)
{
	
	if (p_ultim==NULL)
	{
		printf("Encara no s'ha fet cap cerca \n");
	}
	else
	{
		system("cls");
		printf("~~ Ultim Alumne Buscat ~~ \n");
		
		/*Per mostrar el nom cal canviar els underscores per espais*/
		char nombre[MAX_CHAR];
		strcpy(nombre, p_ultim->alumne.nom);
		quitarGuiones(nombre);

		escriureDades(p_ultim);
	}
}

/*Acci� que mostra les dades de l'�ltim alumne buscat i, seguidament, pregunta si es volen eliminar.  Si l'usuari confirma
que es vol eliminar l'alumne, aquest ser� eliminat de la llista*/
/*acabada*/
void eliminarUltim(node_t *punt_u)
{
	if (punt_u == NULL)
	{
		printf("Encara no s'ha fet cap cerca\n");
	}
	else
	{
		bool exist = true;
		/*Mostrem les dades*/
		veureUltim(punt_u);
		if (exist)
		{
			/*Preguntem si es vol eliminar l'alumne i, en cas afirmatiu, l'eliminem*/
			bool eliminar;
			printf("Vols eliminar aquest alumne? (escriu s per a si i n per a no)\n");
			eliminar = confirmacio();

			/*Si el car�cter introduit �s una s, esborrem el node*/
			if (eliminar)
			{
				eliminarNode(punt_u);
			}
		}
	}
}

/*Acci� que mostra tota la llista de la forma que li diguem*/
void mostrarLlista(node_t* p_inici, node_t* p_final)
{
	if (!llistaBuida(p_inici))
	{
		/*Preguntem a l'usuari com vol visualitzar la llista*/
		int ordre = 3;
		printf("La llista es mostrara per ordre de DNI. Indiqui si la vol veure ordenada de gran a petit o de petit a gran (1 per ordre ascendent i 0 per ordre descendent:\n");
		scanf("%d", &ordre);
		while (ordre!= 1 && ordre!= 0)
		{
			printf("Introdueix un valor v�lid");
			scanf("%d", &ordre);
		}

		/*Segons el que ens digui, fem una acci� o una altra*/
		switch (ordre)
		{
		case 0:mostrarLlista_f(p_final);
			break;
		case 1:mostrarLlista_i(p_inici);
			break;
		}
	}
	else
	{
		printf("La llista esta buida\n");
	}
}

/*Acci� que descarrega les dades emmagatzemades a la llista en un fitxer abans de tancar el programa*/
void guardarDades(node_t *p_llista)
{
	/*Creem el fitxer on es desaran les dades*/
	FILE* fitxer;

	/*Creem un punter que comenci apuntant a la llista*/
	node_t* p;

	/*Obrim el fitxer i comprovem que no hi ha agut cap problema*/
	fitxer = fopen("llista.txt", "w");
	if (fitxer==NULL)
	{
		printf("Error amb el fitxer");
	}

	/*Si s'ha obert b�, cal rec�rrer la llista, per� abans s'ha de comprovar que
	no estigui buida*/
	else
	{
		/*Recorrem la llista i escrivim les dades de tots els alumnes*/
		for (p=p_llista; p!=NULL; p=p->next)
		{
			fEscriureDades(p, fitxer);
		}
		fclose(fitxer);
	}
}

/*Acci� que esborra tota la llista, pr�via confirmaci� de l'usuari*/
void esborrarLlista(node_t** p_inici, node_t** p_final)
{
	/*Creem una variable que ens indiqui si hi ha confirmaci� o no*/
	bool confirmat;

	/*Demanem la confirmaci�*/
	printf("Esta segur que vol esborrar la llista? (Indiqui s per a si i n per a no)\n");
	confirmat = confirmacio();

	/*Si ens confirmen, recorrem la llista i anem eliminant els nodes*/
	if (confirmat)
	{
		/*Creem un punter que ens recorrer� la llista*/
		node_t* p_llista = *p_inici;

		/*Recorrem la llista i esborrem els nodes*/
		while (p_llista != NULL)
		{
			/*Apuntem al seg�ent node abans d'esborrar l'actual per no perdre la informaci�*/
			p_llista = p_llista->next;
			node_t* p = p_llista;
			if (p_llista != NULL)
			{
				eliminarNode(p->previous);
			}
		}

		/*Fem que els punters a la llista siguin nuls*/
		*p_inici = NULL;
		*p_final = NULL;

		printf("---LLista eliminada---\n");
		system("pause");
	}
}