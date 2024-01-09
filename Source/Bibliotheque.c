#include "malloc.h"
#include "Bibliotheque.h"
#include "string.h"
#include "stdio.h"

/*
 * ----------------------------------------------------- *
 * 							   	 						 *
 * 							 							 *
 * ----------------------------------------------------- *
 */
static Queue s_pret_Ferst = NULL;
static Queue s_pret_Last = NULL;
// * ----------------------------------------------------- *
static Stack s_block = NULL;
// * ----------------------------------------------------- *
static Core s_CPU[CORES] = { NULL, NULL, NULL, NULL };
static int Error = 0;
// * ----------------------------------------------------- *
static int * RAM = 0 ;  
#define returnE(val) \
	{                \
		Error = val; \
		return;      \
	}

#define Isnt_NULL(ptr)         \
	{                          \
		if (!ptr)              \
		{                      \
			printf("Is_NULL"); \
			exit(1);           \
		}                      \
	}
int GetError()
{
	// @ NOTE : 0 mean there is no Error
	return Error;
}

signed char is_OK()
{
	return !GetError();
}

void Fixed()
{
	printf("\nFixd\n");
	Error = OK;
}

// static long long * Error = malloc(sizeof(long long));

inline int Test(const char p_name[_NAME_SIZE_], Tree_ptr ptr)
{
	
	if (ptr)
		if(ptr->Info)
			return 0==strcmp(p_name, ptr->Info->Nom);
	return 0;
}

Tree CreateTree(const int p_ram)
{
	Tree root = malloc(sizeof(Processus));
	Isnt_NULL(root)
		strcpy(root->Nom, "root");
	root->PID = 0;
	root->Fils = NULL;
	root->Frere = NULL;
	root->RAM = p_ram;
	RAM = &(root->RAM); 
	root->Etat = ELU;
	return root; 
}

Tree Search(Tree p_root, const char p_name_father[_NAME_SIZE_])
{
	if (p_root == NULL)
		return NULL;

	if (strcmp(p_name_father, p_root->Nom) == 0)
		return p_root;

	for (Tree I = p_root->Fils; I; I = I->Frere)
	{
		Tree result = Search(I, p_name_father);
		if (result != 0)
			return result;
	}

	return NULL;
}

void ScanProcessus(Processus* p_pross)
{

	printf("\n");

	printf("Name : ");
	scanf("%s", p_pross->Nom);

	printf("RAM : ");
	scanf("%u", &(p_pross->RAM));

	printf("ID : ");
	scanf("%d", &(p_pross->PID));
}

Tree CreateProcessus(int p_PID, char p_name[_NAME_SIZE_], int p_ram)
{
	Tree new = malloc(sizeof(Processus));
	new->Etat = PRET;
	new->PID = p_PID;
	new->RAM = p_ram;
	new->Fils = NULL;
	new->Frere = NULL;
	strcpy(new->Nom, p_name);
	return new;
}

Tree SearchCPU(const char p_name_father[_NAME_SIZE_])
{
	for (size_t i = 0; i < CORES; i++)
	{
		if (s_CPU[i])
		{
			Isnt_NULL(s_CPU[i]->Info)
				Test(s_CPU[i]->Info->Nom, p_name_father);
		}
	}
}

void push_in_Tree(const char p_name_father[_NAME_SIZE_], Tree p_root, Tree p_new)
{

	Isnt_NULL(p_root)
		Isnt_NULL(p_new)

		Tree Father = Search(p_root, p_name_father);

	if (Father == NULL)
		returnE(TheFatherDontExist);

	if (Father->Etat != ELU)
		returnE(TheFatherIsNotElu);
	
	p_new->Frere = Father->Fils;
	Father->Fils = p_new;

	if (1)
	{
		if (s_pret_Ferst == NULL)
		{
			s_pret_Ferst = malloc(sizeof(struct elementProcessus));
			Isnt_NULL(s_pret_Ferst)
				s_pret_Ferst->Info = p_new;
			s_pret_Ferst->Next = NULL;
			s_pret_Last = s_pret_Ferst;
			return;
		}

		s_pret_Last->Next = malloc(sizeof(struct elementProcessus));
		Isnt_NULL(s_pret_Last->Next)

			s_pret_Last->Next->Info = p_new;
		s_pret_Last->Next->Next = NULL;
		s_pret_Last = s_pret_Last->Next;
	}

	returnE(OK);
}

void PrintProcessus(const Processus p_Processus)
{
	// NOTE : you have to change that
	printf("ID : %d |", p_Processus.PID);
	printf("Name : %12s |", p_Processus.Nom);
	printf("RAM : %d |", p_Processus.RAM);
	printf("Etat : %d", p_Processus.Etat);
}

void PrintTree(Tree p_root, const int level)
{

	Isnt_NULL(p_root)

		for (int i = 0; i < level; i++)
			printf("\t");

	PrintProcessus(*p_root);

	printf("\n");

	for (Tree I = p_root->Fils; I; I = I->Frere)
		PrintTree(I, 1 + level);
}

void PrintList(Tree_ptr ptr)
{
	for (Tree_ptr I = ptr; I; I = I->Next)
		printf(" %12s |", I->Info->Nom);
	printf(" X\n");
}

void BLOQUE(const unsigned int index)
{

	if (index > CORES)
		returnE(TheIndexIsOutOfTheRange);

	if (s_CPU[index] == NULL)
		returnE(TherIsNoProssInTheCore);

	Tree_ptr Node = s_CPU[index];
	s_CPU[index] = NULL;
	Node->Next = s_block;
	s_block = Node;
	returnE(OK);
}

void PrintCPU()
{
	for (size_t i = 0; i < CORES; i++)
		if (s_CPU[i] == NULL)
			printf(" %12s (%d)|", "EMPTY", i);
		else
			printf(" %12s (%d)|", s_CPU[i]->Info->Nom, i);
	printf("\n");
}

void RUN(const unsigned int index)
{
	if (index > CORES)
		returnE(TheIndexIsOutOfTheRange);

	if (s_CPU[index] != NULL)
		returnE(TheCoseIsRunningAnOtherPross);

	if (s_pret_Ferst == NULL)
		returnE(ThesIsNoProssusPret);

	s_CPU[index] = s_pret_Ferst;
	s_pret_Ferst = s_pret_Ferst->Next;
	s_CPU[index]->Info->Etat = ELU;

	printf("%12s is Running Know\n", s_CPU[index]->Info->Nom);
}

void SHOW(Tree p_root)
{
	puts("\nTree : ");
	LINE;
	PrintTree(p_root, 0);
	LINE;

	puts("\nPret : ");
	LINE;
	PrintList(s_pret_Ferst);
	LINE;

	puts("\nBlock : ");
	LINE;
	PrintList(s_block);
	LINE;

	puts("\nCPU : ");
	LINE;
	PrintCPU();
	LINE;
}

static Tree Searchbefor(Tree p_root, const char p_name[_NAME_SIZE_]) {


	if (p_root == NULL)
		return NULL;

	if (p_root->Fils != NULL)
		if (strcmp(p_name, p_root->Fils->Nom) == 0)
			return p_root;
	 
	if (p_root->Frere != NULL) 
		if (strcmp(p_name, p_root->Frere->Nom) == 0)
			return p_root;
	 

	for (Tree I = p_root->Fils; I; I = I->Frere) {
		Tree result = Searchbefor(I, p_name);
		if (result != NULL)  
	 		return result;
		 
	}

	return NULL;
}


static void GoHuntiong(const char p_name[_NAME_SIZE_]) {


	if (s_pret_Ferst && Test(p_name, s_pret_Ferst )) {
 		Tree_ptr tmp = s_pret_Ferst->Next;
		free(s_pret_Ferst);
		s_pret_Ferst = tmp;
		returnE(OK);
	}

	if (s_block && Test(p_name, s_block )) { 
		Tree_ptr tmp = s_block->Next;
		free(s_block);
		s_block = tmp;
		returnE(OK);
	}

	for (Tree_ptr I = s_pret_Ferst, J = s_block, index = (CORES - 1), GO = 1; GO;
		GO = (long long)I | (long long)J | (long long)index)    {
		  
 		if (I && Test(p_name, I->Next )) {
 
			if (I->Next == s_pret_Last)  {
				s_pret_Last = I;
				free(I->Next);
				s_pret_Last->Next = NULL;
				returnE(OK);
			}
			
			else  {
				Tree_ptr tmp = I->Next;
				I->Next = I->Next->Next;
				free(tmp);
				returnE(OK);
			}
		}
		 
 		if (J && Test(p_name, J->Next  )) {
			  
			Tree_ptr tmp = J->Next;
			J->Next = J->Next->Next;
			free(tmp);
			returnE(OK);
		}
		
		if ( s_CPU[(int)index] && Test(p_name, s_CPU[(int)index] )) {
			printf("loop on CPU\n");

			free(s_CPU[(int)index]);
			s_CPU[(int)index] = NULL;
			returnE(OK);
		}

		if (I)									I = I->Next;

		if (J)									J = J->Next;

		if (index>=0)							{ ((char)index)--; }
 
	}

 }

void DestroydTree(Tree  p_root) {
	if (p_root == NULL)
		return NULL;

	DestroydTree(p_root->Frere);
	DestroydTree(p_root->Fils);

	GoHuntiong(p_root->Nom);
	// free(p_root); 

}

void KILLProcessus(Tree p_root, const char p_name[_NAME_SIZE_])
{

	Isnt_NULL(p_root); 

	Tree nodebefor = Searchbefor(p_root, p_name);

	if (nodebefor) {
		Tree me = NULL;
		if (nodebefor->Fils) {
			if (!strcmp(nodebefor->Fils->Nom , p_name)) {

				me = nodebefor->Fils;
				nodebefor->Fils = me->Frere;
				DestroydTree(me);
				returnE(OK)
			}
		}
		else {
			if (nodebefor->Frere)
				if (!strcmp(nodebefor->Frere->Nom, p_name)) {

					me = nodebefor->Frere;
					nodebefor->Frere = me->Frere;
					DestroydTree(me);
					returnE(OK)
				}
		}
	}
	returnE(TheNodeDontExist)

}

void Terminer(const unsigned int index, Tree p_root) {
	Isnt_NULL(p_root);
	if (index >= CORES) {
		printf("The index %d\n", index);
		returnE(TheIndexIsOutOfTheRange);
	}
	
	if (s_CPU[index] != NULL) {
		if (s_CPU[index]->Info) {
			printf("Terminer %s\n", s_CPU[index]->Info->Nom);
			KILLProcessus(p_root, s_CPU[index]->Info->Nom);
		}
	}

}

void UNBLOQUE() {

	if (s_block == NULL)
		returnE(YouDiDNotBlockAnyprossus);

	s_pret_Last->Next = s_block;
	s_pret_Last = s_pret_Last->Next;
	s_block = s_block->Next;
	s_pret_Last->Next = NULL;
	if (s_pret_Ferst == NULL)
		s_pret_Ferst = s_pret_Last;

	return 0;
}

/*
◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱
| node 1 || node 2 || node 3 || node 4 || node 5 || node 6 || node 7 || node 8 || node 9 || node10 |
◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰
*/
