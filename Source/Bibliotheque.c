#include "malloc.h"
#include "Bibliotheque.h"
#include"string.h"


Tree CreateTree( int p_ram)
{
	Tree root = malloc(sizeof(Processus)); 
	strcpy(root->Nom , "Name") ; 
	root->PID = 0 ; 
	root->RAM = p_ram  ;

}


