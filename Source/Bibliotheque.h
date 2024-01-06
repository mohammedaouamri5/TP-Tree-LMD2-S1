

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

 
typedef struct elementProcessus *TListeProcessus;
struct elementProcessus
{
    Tree Info;
    struct elementProcessus * Next;
};
 
#define Tree_ptr TListeProcessus
#define Stack Tree_ptr
#define Queue Tree_ptr
#define Core Tree_ptr
#define core int
#define Processus struct element
  
// the name will be a problem  

long long  RUN(); 
void PREPER(int id);  
void Stope(); 


// todo : binery well balensed search tree
long long BLOQUE(unsigned int index);
long longUNBLOQUE();

Tree CreateTree( int p_ram );
void CreateLife(Processus root);
void DestroydTree();  

Tree CreateProcessus(  int p_PID , char p_name[_NAME_SIZE_] , int p_ram ) ;  
long long push_in_Tree(const char  p_name_father[_NAME_SIZE_], Tree p_root, Tree p_new);

void KILLProcessus(int ID);  
void CreateCPU(); 
void CreateCPU(); 

void PrintTree(Tree p_root, int level); 

void SHOW(Tree p_root); 
















#endif