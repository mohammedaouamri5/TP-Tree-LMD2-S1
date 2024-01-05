

#ifndef _LIB_H_
#define _LIB_H_

#define _NAME_SIZE_ 12
#define CORES 4 
 


typedef struct element *TarbreProcessus;
struct element
{
    int PID;
    char Nom[_NAME_SIZE_];
    int RAM;
    int Etat;
    struct elementArbre *Fils;
    struct elementArbre *Frere;
};

enum ETAT { PRET ,
            ELU , 
            BLOCK }; 

 
typedef struct elementProcessus *TListeProcessus;
struct elementProcessus
{
    int ID;
    struct elementProcessus *Suivant;
};

 

#define Stack TListeProcessus
#define Queue TListeProcessus
#define Tree TarbreProcessus
#define Processus struct element
  
// the name will be a problem  

void RUN(); 
void PREPER(int id);  
void Stope(); 


// todo : binery well balensed search tree

void BLOQUE();
void UNBLOQUE(int id);

Tree CreateTree( int p_ram );
void CreateLife(Processus root);
void DestroydTree();  

Tree CreateProcessus(  int p_PID , char p_name[_NAME_SIZE_] , int p_ram ) ;  
int push_in_Tree(const char  p_name_father[_NAME_SIZE_], Tree p_root, Tree p_new);

void KILLProcessus(int ID);  
void CreateCPU(); 
void CreateCPU(); 

void PrintTree(Tree p_root, int level); 

void SHOW(); 
















#endif