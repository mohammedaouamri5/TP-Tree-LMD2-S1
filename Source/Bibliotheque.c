#include "malloc.h"
#include "Bibliotheque.h"
#include "string.h"
#include "stdio.h"
#include <stdarg.h>

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
static Core s_CPU[CORES] = {NULL, NULL, NULL, NULL};
static int Error = 0;
// * ----------------------------------------------------- *
static int RAM = 0;
// * ----------------------------------------------------- *
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

void PrintList(Tree_ptr head , const char * fml , ...);
void PrintCPU(); 

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
	Error = OK;
}

void SetRam(const int p_ram)
{
	RAM = p_ram;
}
// static long long * Error = malloc(sizeof(long long));

inline int Test(const char p_name[_NAME_SIZE_], Tree_ptr ptr)
{

	if (ptr)
		if (ptr->Info)
			return 0 == strcmp(p_name, ptr->Info->Nom);
	return 0;
}

Tree CreateTree(const int p_ram)
{
	Tree root = malloc(sizeof(Processus));
	Isnt_NULL(root);
	strcpy(root->Nom, "root");
	root->PID = 0;
	root->Fils = NULL;
	root->Frere = NULL;
	root->RAM = p_ram;
	root->prioriter = 0;
	root->Etat = ELU;
	return root;
}

Tree SearchByName(Tree p_root, const char p_name[_NAME_SIZE_])
{
	if (p_root == NULL)
		return NULL;

	if (strcmp(p_name, p_root->Nom) == 0)
		return p_root;

	for (Tree I = p_root->Fils; I; I = I->Frere)
	{
		Tree result = SearchByName(I, p_name);
		if (result != NULL)
			return result;
	}

	return NULL;
}
Tree SearchByPID(Tree p_root, int p_PID)
{

	if (p_root == NULL)
		return NULL;

	if (p_PID == p_root->PID)
		return p_root;

	for (Tree I = p_root->Fils; I; I = I->Frere)
	{
		Tree result = SearchByPID(I, p_PID);
		if (result != NULL)
			return result;
	}
	return NULL;
}

void ScanProcessus(Tree p_root, Processus *p_pross)
{

	puts("");
	int8_t go;

	do
	{
		go = 0;
		printf("Name : ");
		scanf("%s", p_pross->Nom);
		if (SearchByName(p_root, p_pross->Nom))
		{
			puts("[error] : You haave already this name change it ");
			go = 1;
		}
	} while (go);

	do
	{
		go = 0;
		printf("RAM : ");
		scanf("%d", &(p_pross->RAM));
		if (p_pross->RAM >= RAM)
		{
			printf("[error] : The ram of the new pross should me less that The thee reminder RAM that equal to %d \n", RAM);
			go = (int8_t)1;
		}
		else if (p_pross->RAM <= 0)
		{
			puts("[error] : The ram cant be less or equal to 0");
			go = (int8_t)1;
		}
	} while (go);

	do
	{
		go = 0;
		printf("prioriter : ");
		scanf("%d", &(p_pross->prioriter));
		if (p_pross->prioriter < (int8_t)0)
		{
			puts("[error] : The prioriter cant be less that 0 ");
			go = (int8_t)1;
		}
		else if (p_pross->prioriter > (int8_t)7)
		{
			puts("[error] : The prioriter cant be more that 7 ");
			go = (int8_t)1;
		}
	} while (go);

	do
	{
		go = 0;
		printf("ID : ");
		scanf("%d", &(p_pross->PID));
		if (SearchByPID(p_root, p_pross->PID))
		{
			puts("[error] : You haave already this ID change it ");
			go = 1;
		}
	} while (go);
}

Tree CreateProcessus(int p_PID, char p_name[_NAME_SIZE_], int p_ram, signed char p_prioriter)
{
	Tree new = malloc(sizeof(Processus));
	Isnt_NULL(new);
	new->Fils = NULL;
	new->Frere = NULL;
	new->Etat = PRET;
	new->PID = p_PID;
	new->RAM = p_ram;
	new->prioriter = p_prioriter;
	strcpy(new->Nom, p_name);
	return new;
}

Tree SearchCPU(const char p_name_father[_NAME_SIZE_])
{
	for (size_t i = 0; i < CORES; i++)
	{
		if (s_CPU[i])
		{
			Isnt_NULL(s_CPU[i]->Info);
			Test(s_CPU[i]->Info->Nom, p_name_father);
		}
	}
}

void AddToPRET(Tree p_new_Tree)
{

	if (s_pret_Ferst == NULL)
	{
		s_pret_Ferst = malloc(sizeof(struct elementProcessus));
		Isnt_NULL(s_pret_Ferst);
		s_pret_Ferst->Info = p_new_Tree;
		s_pret_Ferst->Next = NULL;
		s_pret_Last = s_pret_Ferst;
		return;
	}
	Queue new_Queue = malloc(sizeof(struct elementProcessus));
	new_Queue->Info = p_new_Tree;
	new_Queue->Next = NULL;

	for (Queue Me = s_pret_Ferst, Befor = NULL; Me;)
	{
		if (Me->Info->prioriter > new_Queue->Info->prioriter)
		{

			new_Queue->Next = Me;
			if (Befor == NULL)
			{
				new_Queue->Next = s_pret_Ferst;
				s_pret_Ferst = new_Queue;
			}
			else
			{
				Befor->Next = new_Queue;
			}

			returnE(OK);
		}
		/* Next Iteration */ {
			Befor = Me;
			Me = Me->Next;
		}
	}

	s_pret_Last->Next = new_Queue;
	s_pret_Last = new_Queue;
}

void push_in_Tree(const char p_name_father[_NAME_SIZE_], Tree p_root, Tree p_new)
{

	Isnt_NULL(p_root);
	Isnt_NULL(p_new);

	/*Add To The Tree*/ {
		Tree Father = SearchByName(p_root, p_name_father);

		if (Father == NULL)
			returnE(TheFatherDontExist);

		if (Father->Etat != ELU)
			returnE(TheFatherIsNotElu);
		if (1)
			if (RAM < p_new->RAM)
				returnE(YouDontHaveEnoughtRam);

		(RAM) -= p_new->RAM;

		p_new->Frere = Father->Fils;
		Father->Fils = p_new;
	}

 
	if (1)
	{
		AddToPRET(p_new);
	}
	else
	{
		if (s_pret_Ferst == NULL)
		{
			s_pret_Ferst = malloc(sizeof(struct elementProcessus));
			Isnt_NULL(s_pret_Ferst);
			s_pret_Ferst->Info = p_new;
			s_pret_Ferst->Next = NULL;
			s_pret_Last = s_pret_Ferst;
		}
		else
		{

			s_pret_Last->Next = malloc(sizeof(struct elementProcessus));
			Isnt_NULL(s_pret_Last->Next);
			s_pret_Last->Next->Info = p_new;
			s_pret_Last->Next->Next = NULL;
			s_pret_Last = s_pret_Last->Next;
		}
	}

	PrintList(s_pret_Ferst , "\nAdding %s : \n", p_new->Nom);
	

	returnE(OK);
}

void PrintProcessus(const Processus p_Processus)
{
	// NOTE : you have to change that
	printf("ID : %d |", p_Processus.PID);
	printf("Name : %12s |", p_Processus.Nom);
	printf("RAM : %d |", p_Processus.RAM);
	printf("Etat : %d |", p_Processus.Etat);
	printf("Prioriter : %d", p_Processus.prioriter);
}

void PrintTree(Tree p_root, const int level)
{

	Isnt_NULL(p_root);

	for (int i = 0; i < level; i++)
		printf("\t");

	PrintProcessus(*p_root);

	printf("\n");

	for (Tree I = p_root->Fils; I; I = I->Frere)
		PrintTree(I, 1 + level);
}

void PrintList(Tree_ptr ptr , const char * fml , ...)
{
 

    // Print formatted string using variable arguments
    va_list args;
    va_start(args, fml);
    vprintf(fml, args);
    va_end(args);

 
	LINE
	int conter = 0;
	for (Tree_ptr I = ptr; I; I = I->Next)
		printf("(%d) name : %12s|", conter++, I->Info->Nom );
	printf(" total of : %d\n", conter);
	LINE
	
}

void BLOQUE(const unsigned int index)
{

	if (index > CORES)
		returnE(TheIndexIsOutOfTheRange);

	if (s_CPU[index] == NULL)
		returnE(TherIsNoProssInTheCore);

	s_CPU[index]->Info->Etat = BLOCK;
	Tree_ptr Node = s_CPU[index];
	s_CPU[index] = NULL;
	Node->Next = s_block;
	s_block = Node;
  
	returnE(OK);
}

void PrintCPU()
{
	puts("\nCPU : ");
	LINE;

	for (size_t i = 0; i < CORES; i++)
		if (s_CPU[i] == NULL)
			printf(" %12s (%d)|", "EMPTY", i);
		else
			printf(" %12s (%d)|", s_CPU[i]->Info->Nom, i);
	printf("\n");
	LINE;
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
	PrintCPU(); 
}

void SHOW(Tree p_root)
{

	LINE;
	printf("\nRAM : %d\n", RAM);
	LINE;

	puts("\nTree : ");
	LINE;
	PrintTree(p_root, 0);
	LINE;
 
	PrintList(s_pret_Ferst , "\nPret : \n");
	PrintList(s_block ,  "\nBlock : \n"); 
	PrintCPU();
	 
}

static Tree Searchbefor(Tree p_root, const char p_name[_NAME_SIZE_])
{

	if (p_root == NULL)
		return NULL;

	if (p_root->Fils != NULL)
		if (strcmp(p_name, p_root->Fils->Nom) == 0)
			return p_root;

	if (p_root->Frere != NULL)
		if (strcmp(p_name, p_root->Frere->Nom) == 0)
			return p_root;

	for (Tree I = p_root->Fils; I; I = I->Frere)
	{
		Tree result = Searchbefor(I, p_name);
		if (result != NULL)
			return result;
	}

	return NULL;
}

static void GoHuntiong(const char p_name[_NAME_SIZE_])
{

	if (s_pret_Ferst && Test(p_name, s_pret_Ferst))
	{
		Tree_ptr tmp = s_pret_Ferst->Next;
		RAM += s_pret_Ferst->Info->RAM;
		free(s_pret_Ferst->Info);
		free(s_pret_Ferst);
		s_pret_Ferst = tmp;
		returnE(OK);
	}

	if (s_block && Test(p_name, s_block))
	{
		RAM += s_pret_Ferst->Info->RAM;
		Tree_ptr tmp = s_block->Next;
		free(s_block->Info);
		free(s_block);
		s_block = tmp;
		returnE(OK);
	}

	for (Tree_ptr I = s_pret_Ferst, J = s_block, index = (CORES - 1), GO = 1; GO;
		 GO = (long long)I | (long long)J | (long long)index)
	{

		if (I && Test(p_name, I->Next))
		{

			if (I->Next == s_pret_Last)
			{
				s_pret_Last = I;
				RAM += I->Next->Info->RAM;
				free(I->Next->Info);
				free(I->Next);
				s_pret_Last->Next = NULL;
				returnE(OK);
			}

			else
			{
				Tree_ptr tmp = I->Next;
				I->Next = I->Next->Next;
				RAM += tmp->Info->RAM;
				free(tmp->Info);
				free(tmp);
				returnE(OK);
			}
		}

		if (J && Test(p_name, J->Next))
		{

			Tree_ptr tmp = J->Next;
			J->Next = J->Next->Next;
			RAM += tmp->Info->RAM;
			free(tmp->Info);
			free(tmp);
			returnE(OK);
		}

		if (s_CPU[(int)index] && Test(p_name, s_CPU[(int)index]))
		{
			printf("loop on CPU\n");
			RAM += s_CPU[(int)index]->Info->RAM;
			free(s_CPU[(int)index]->Info);
			free(s_CPU[(int)index]);
			s_CPU[(int)index] = NULL;
			returnE(OK);
		}

		if (I)
			I = I->Next;
		if (J)
			J = J->Next;
		if (index >= 0)
			((char)index)--;
	}
}

void DestroydTree(Tree p_root)
{
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

	if (nodebefor)
	{
		Tree me = NULL;
		if (nodebefor->Fils)
		{
			if (!strcmp(nodebefor->Fils->Nom, p_name))
			{

				me = nodebefor->Fils;
				nodebefor->Fils = me->Frere;
				DestroydTree(me);
				returnE(OK)
			}
		}
		else
		{
			if (nodebefor->Frere)
				if (!strcmp(nodebefor->Frere->Nom, p_name))
				{

					me = nodebefor->Frere;
					nodebefor->Frere = me->Frere;
					DestroydTree(me);
					returnE(OK)
				}
		}
	}
	returnE(TheNodeDontExist)
}

void Terminer(const unsigned int index, Tree p_root)
{
	Isnt_NULL(p_root);
	if (index >= CORES)
	{
		printf("The index %d\n", index);
		returnE(TheIndexIsOutOfTheRange);
	}

	if (s_CPU[index] != NULL)
	{
		if (s_CPU[index]->Info)
		{
			printf("Terminer %s\n", s_CPU[index]->Info->Nom);
			KILLProcessus(p_root, s_CPU[index]->Info->Nom);
			PrintCPU();
		}
	}
	else
		returnE(YouDontHaveAnyprossusHere);
}

void UNBLOQUE()
{

	if (s_block == NULL)
		returnE(YouDiDNotBlockAnyprossus);
	
	s_block->Info->Etat = PRET;

	s_pret_Last->Next = s_block;
	s_pret_Last = s_pret_Last->Next;
	s_block = s_block->Next;
	s_pret_Last->Next = NULL;
	if (s_pret_Ferst == NULL)
		s_pret_Ferst = s_pret_Last;
	PrintList(s_block ,  "\ndeblcked %s : " , s_pret_Last->Info->Nom); 
	return 0;
}

/*
◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱◲--------◱
| node 1 || node 2 || node 3 || node 4 || node 5 || node 6 || node 7 || node 8 || node 9 || node10 |
◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰◳--------◰
*/
