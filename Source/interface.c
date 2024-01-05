#include "Bibliotheque.h"
#include "stdio.h"
#include "string.h"
int main(int argc, char const *argv[])
{
    Tree root = CreateTree(12);
 
    printf("adding WOW to root : \n");
    printf("%d \n", push_in_Tree("root", root, CreateProcessus(19, "WOW", 10)));
 
    printf("adding wow to root : \n");
    printf("%d \n", push_in_Tree("root", root, CreateProcessus(1, "wow", 10)));

 
    printf("adding aaa to WOW : \n");
    printf("%d \n", push_in_Tree("WOW", root, CreateProcessus(5, "aaa", 10)));
 
    printf("adding mm to mm : \n");
    printf("%d \n", push_in_Tree("wow", root, CreateProcessus(6, "mm", 10)));

    printf("--------------------------------------------\n");
    PrintTree(root , 0);
    printf("--------------------------------------------\n");

    return 0;
}
