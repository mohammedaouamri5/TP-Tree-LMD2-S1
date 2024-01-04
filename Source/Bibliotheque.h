

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
struct element WOW ; 

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

void CreateProcessus(int ID , Tree root) ;  
void KILLProcessus(int ID);  

void CreateCPU(); 
void CreateCPU(); 


void SHOW(); 
















#endif