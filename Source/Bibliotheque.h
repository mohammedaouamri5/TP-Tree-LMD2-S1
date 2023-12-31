

#ifndef _LIB_H_
#define _LIB_H_

#define _NAME_SIZE_ 12
#define CORES 4 
 
#define  LINE printf("---------------------------------------------------------------------------------------------------------------\n");
 

typedef struct element *TarbreProcessus;
#define Tree TarbreProcessus
struct element
{
    int PID;
    char Nom[_NAME_SIZE_];
    int RAM;
    int Etat;
    Tree Fils;
    Tree Frere;
};

enum ETAT { PRET ,
            ELU , 
            BLOCK }; 

enum ERORR {
	OK = 0 , 
    TheFatherDontExist, 
    TheFatherIsNotElu , 
    TheCoseIsRunningAnOtherPross,
    TherIsNoProssInTheCore,
    TheIndexIsOutOfTheRange   
}; 
 



 
typedef struct elementProcessus *TListeProcessus;
struct elementProcessus
{
    Tree Info;
    struct elementProcessus * Next;
};
 
#define Tree_ptr TListeProcessus
#define Stack TListeProcessus
#define Queue TListeProcessus
#define Core TListeProcessus
#define core int
#define Processus struct element
  
// the name will be a problem  

void RUN(const unsigned int index); 
void PREPER(int id);  
void Stope(); 


// todo : binery well balensed search tree
void BLOQUE(const unsigned int index);
long long UNBLOQUE();

Tree CreateTree(const int p_ram );
void DestroydTree(Tree p_root);  

Tree CreateProcessus( ) ;  
void push_in_Tree(const char  p_name_father[_NAME_SIZE_], Tree p_root, Tree p_new);
int GetError(); 
void Fixed();

signed char is_OK(); 

void KILLProcessus(Tree p_root ,const  unsigned int index);  
  
void Terminer(const unsigned int index);

void PrintTree(Tree p_root,const  int level); 

void SHOW(Tree p_root); 







 



#endif