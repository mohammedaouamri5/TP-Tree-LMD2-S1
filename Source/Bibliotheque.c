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
static Queue s_pret_Ferst = NULL;
static Queue s_pret_Last = NULL;
static Stack s_block = NULL;
static Core  s_CPU[CORES] = {NULL,NULL,NULL,NULL};
static Tree root = NULL;

Tree CreateTree(int p_ram)
{
	Tree root = malloc(sizeof(Processus));
	strcpy(root->Nom, "root");
	root->PID = 0;
	root->Fils = NULL;
	root->Frere = NULL;
	root->RAM = p_ram;
	root->Etat = ELU;
	return root;
}

Tree Search(Tree p_root, const char p_name_father[_NAME_SIZE_]){
	if (p_root == NULL)
		return NULL;

	// * printf("                    p_name_father : %s , p_root->Nom :"
	// *" %s (strcmp(p_name_father, p_root->Nom) == %d)\n",
	// * p_name_father, p_root->Nom, strcmp(p_name_father, p_root->Nom));

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

Tree CreateProcessus(int p_PID, char p_name[_NAME_SIZE_], int p_ram){
	Tree new = malloc(sizeof(Processus));
	new->Etat = PRET;
	new->PID = p_PID;
	new->RAM = p_ram;
	new->Fils = NULL;
	new->Frere = NULL;
	strcpy(new->Nom, p_name);
	return new;
}

void ScanProcessus(Processus *p_pross){

	printf("\n");

	printf("Name : ");
	scanf("%[^\n]s", p_pross->Nom);

	printf("RAM : ");
	scanf("%d", &(p_pross->RAM));

	printf("ID : ");
	scanf("%d", &(p_pross->PID));
}

long long push_in_Tree(const char p_name_father[_NAME_SIZE_], Tree p_root, Tree p_new)
{
	if (p_root == NULL)
		exit(1);
	if (p_new == NULL)
		return -2;

	Tree Father = Search(p_root, p_name_father);

	if (Father == NULL)
		return -2;

	// if (Father->Etat != ELU)
	// 	return -2;

	p_new->Frere = Father->Fils;
	Father->Fils = p_new;
	
	if(1){
		if (s_pret_Ferst == NULL)
		{
			s_pret_Ferst = malloc(sizeof(struct elementProcessus));
			s_pret_Ferst->Info = p_new;
			s_pret_Ferst->Next = NULL;
			s_pret_Last = s_pret_Ferst;
			return Father;
		}
	
		s_pret_Last->Next = malloc(sizeof(struct elementProcessus));
		s_pret_Last->Next->Info = p_new;
		s_pret_Last->Next->Next = NULL;
		s_pret_Last = s_pret_Last->Next;

	}

	return Father;
}

void PrintProcessus(Processus p_Processus) {
	// NOTE : you have to change that
	printf("ID : %d |", p_Processus.PID);
	printf("Name : %12s |", p_Processus.Nom);
	printf("RAM : %d |", p_Processus.RAM);
	printf("Etat : %d", p_Processus.Etat);
}

void PrintTree(Tree p_root, int level){

	if (p_root == NULL)
		return NULL;

	for (int i = 0; i < level; i++)
		printf("\t");

	PrintProcessus(*p_root);

	printf("\n");

	for (Tree I = p_root->Fils; I; I = I->Frere)
		PrintTree(I, 1 + level);
}

void PrintPret()
{
	for (Tree_ptr I = s_pret_Ferst, j = -1; I; I = I->Next)
		printf(" %12s |", I->Info->Nom);
	printf("   X\n");
}
void PrintBlock(){
	for (Tree_ptr I = s_block , j = -1; I; I = I->Next)
		printf(" %12s |", I->Info->Nom);
	printf("   X\n");
}



long long BLOQUE(unsigned int index) {
	if (index > CORES)
		return -1;

	Tree_ptr Node = s_CPU[index];
	s_CPU[index] = NULL; 
	Node->Next = s_block;
	s_block = Node;
	return 0;
}


void PrintCPU() {
	for (size_t i = 0; i < CORES; i++) 
		if(s_CPU[i] == NULL) 
			printf(" %12s |" , "EMPTY" ); 	
		else
		printf(" %12s |", s_CPU[i]->Info->Nom); 	
	printf("\n");
}
    


long long RUN(int index) {
	if (index > CORES)
		return -1;

	if(s_CPU[index] == NULL){
		s_CPU[index] = s_pret_Ferst; 
		s_pret_Ferst = s_pret_Ferst->Next;
		printf("%12s is Running Know\n" ,		s_CPU[index]->Info->Nom );
	}
  
}

void SHOW(Tree p_root){
	puts("\nTree : ");
	LINE
	PrintTree(p_root , 0);
    LINE

	puts("\nPret : ");
    LINE
	PrintPret();
    LINE

	puts("\nBlock : ");
    LINE
	PrintBlock();
    LINE
	puts("\nCPU : ");
    LINE
	PrintCPU();
    LINE
} 

long long UNBLOQUE(){

	s_pret_Last = s_block;
	s_block = s_block->Next;
	s_pret_Last->Next = NULL;
	return 0;
}



 
/*
◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱
| node 1 || node 2 || node 3 || node 4 || node 5 || node 6 || node 7 || node 8 || node 9 || node10 |
◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰
*/


















