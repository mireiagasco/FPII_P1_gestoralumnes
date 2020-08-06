#ifndef GESTORALUMNESH_H_INCLUDED
#include <stdbool.h>
#define GESTORALUMNESH_H_INCLUDED

/*Definicions de les constants utilitzades*/
#define MAX_CHAR 100
#define MAX_DNI 8
#define MAX_VALOR 4
#define MAX_DATA 11
#define OPCIO_MAX 6

/*Definicions dels registres utilitzats: almune_t i dni_t*/
typedef struct
{
	int num;
	char lletra;
}dni_t;


typedef struct 
{
	char nom[MAX_CHAR];
	dni_t dni;
	char correu[MAX_CHAR];
	float nota;
	char data_naix[MAX_DATA];
	char sexe;
}alumne_t;

/*Definici� del tipus per fer la linked list (cada node cont� les dades de l'alumne i un punter al seg�ent*/
typedef struct Node
{
	alumne_t alumne;
	struct Node* next;
	struct Node* previous;
}node_t;

/*Cap�aleres de les funcions principals utilitzades en el main*/

void inici_llista();
void mostrarMenu();
void carregarDades();
char demanarOpcio(char numero);
void afegirAlumne();
node_t *buscarDni();
void buscarNom();
void veureUltim();
void eliminarUltim();
void omplirLlista();
void guardarDades();
void esborrarLlista();

/*Cap�aleres de les funcions b�siques de la linked list*/

node_t *crearNode();
node_t *inicialitzarNode();
void omplirNode();
void eliminarNode();
bool llistaBuida();
node_t *colocarNode();
node_t *colocarPrimer();
node_t* colocarInici();
node_t* colocarMig();
node_t* colocarFinal();
void mostrarLlista();
void mostrarLlista_i();
void mostrarLlista_f();

/*Cap�aleres de les cerques*/
bool cerca();
bool Iguals();
bool mesPetit();

/*Cap�aleres d'altres funcions*/
void fEscriureDades();
void escriureDades();
char calcularLletra();
void comprovarCaracter();
bool valorValid(char valor);
dni_t demanarIVerificarDni();
void canviMajuscules();
void similar();
void ponerGuiones();
void quitarGuiones();
void mostrarNom();
bool confirmacio();


#endif // GESTORALUMNESH_H_INCLUDED
#pragma once
