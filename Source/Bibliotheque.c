#include "malloc.h"
#include "Bibliotheque.h"
#include "string.h"
#include "stdio.h"


/*
* ----------------------------------------------------- *
* 														*
* 														*	
* ----------------------------------------------------- * 
*/



Tree CreateTree(int p_ram) {
	Tree root = malloc(sizeof(Processus));
	strcpy(root->Nom, "root");
	root->PID = 0;
	root->Fils = NULL;
	root->Frere = NULL;
	root->RAM = p_ram;
	root->Etat = PRET;
	return root;
}

Tree Search(Tree p_root, const char p_name_father[_NAME_SIZE_]) {
	if (p_root == NULL)
		return NULL;
	printf("                    p_name_father : %s , p_root->Nom : %s (strcmp(p_name_father, p_root->Nom) == %d)\n", p_name_father, p_root->Nom, strcmp(p_name_father, p_root->Nom));
	if (strcmp(p_name_father, p_root->Nom) == 0)
		return p_root;

	for (Tree I = p_root->Fils; I; I = I->Frere)
	{
		Tree result = Search(I, p_name_father);
		if (result != -1 && result != 0)
			return I;
	}

	return NULL;
}

Tree CreateProcessus(int p_PID, char p_name[_NAME_SIZE_], int p_ram) {
	Tree new = malloc(sizeof(Processus));
	new->Etat = PRET;
	new->PID = p_PID;
	new->RAM = p_ram;
	new->Fils = NULL;
	new->Frere = NULL;
	strcpy(new->Nom, p_name);
	return new;
}

int push_in_Tree(const char p_name_father[_NAME_SIZE_], Tree p_root, Tree p_new) {
	if (p_root == NULL)
		exit(1);
	if (p_new == NULL)
		return -2;
	Tree Father = Search(p_root, p_name_father);
	
	if (Father == NULL)
		return -2;

	p_new->Frere = Father->Fils;
	Father->Fils = p_new;
	return Father;
}

void PrintProcessus(Processus p_Processus) {
	printf("ID : %d |", p_Processus.PID);
	printf("Name : %s |", p_Processus.Nom);
	printf("RAM : %d |", p_Processus.RAM);
	printf("Etat : %d", p_Processus.Etat);
}

void PrintTree(Tree p_root, int level) { 
	
	if (p_root == NULL)
		return NULL;
	 
	for (int i = 0; i < level; i++)
		printf("\t");

	PrintProcessus(*p_root);

	printf("\n");

	for (Tree I = p_root->Fils; I; I = I->Frere)
		PrintTree(I, 1 + level);
}
