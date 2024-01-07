#include "Bibliotheque.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/**
 * ----------------------------------------------------- *
 * TODO :                                                *
 *        - fix terminer                                        *
 *        - fix kill                                        *
 *        - ram                                       *
 *        -                               *
 **/

enum CHOIX
{
    CHOIX_SHOW,
    CHOIX_CLEAN,
    CHOIX_ADD,
    CHOIX_BLOCK,
    CHOIX_KILL,
    CHOIX_TERMINE,
    CHOIX_RUN,
    CHOIX_QUIT

};
int mafin(int argc, char const *argv[])
{
    Tree root = CreateTree(12);
    printf("adding WOW to root : \n");
    push_in_Tree("root", root, CreateProcessus(19, "WOW", 10));

    printf("adding wow to root : \n");
    push_in_Tree("root", root, CreateProcessus(1, "wow", 10));

    printf("adding aaa to WOW : \n");
    push_in_Tree("WOW", root, CreateProcessus(5, "aaa", 10));

    printf("adding mm to wow : \n");
    push_in_Tree("wow", root, CreateProcessus(6, "mm", 10));

    SHOW(root);

    RUN(0);
    printf("\n\n\n");
    SHOW(root);

    RUN(1);
    printf("\n\n\n");
    SHOW(root);

    return 0;
}
int main(int argc, char const *argv[])
{

    int choix = 0;
    Tree root = NULL;

    printf("how much ram you wont have (in Byte) \n"
           ">>> ");
    {
        int ram = 0;
        scanf("%d", &ram);
        root = CreateTree(16);
    }

    int go;
    if (1)
        do
        {
            puts("what you wont to do : ");
            puts("                - 0 CHOIX_SHOW");
            puts("                - 1 CHOIX_CLEAN");
            puts("                - 2 CHOIX_ADD");
            puts("                - 3 CHOIX_BLOCK");
            puts("                - 4 CHOIX_KILL");
            puts("                - 5 CHOIX_CHOIX_TERMINE");
            puts("                - 6 CHOIX_RUN");
            puts("                - 7 CHOIX_QUIT");
            printf(">>> ");
            scanf("%d", &choix);
            Fixed();

            switch (choix)
            {

            case CHOIX_SHOW:
                SHOW(root);
                break;
            case CHOIX_CLEAN:
                system("cls");
                break;
            case CHOIX_ADD:
            {
                Tree new = CreateProcessus();
                ScanProcessus(new);
                printf("Name of the father : ");
                char name_father[_NAME_SIZE_];
                scanf("%s", name_father);

                do
                {
                    go = 0;
                    Fixed();
                    push_in_Tree(name_father, root, new);
                    switch (GetError())
                    {
                    case OK:
                        continue;
                        break;

                    case TheFatherDontExist:
                        printf("The fathor dont even exist  ");

                        printf("Do  you wont to add with defrens name (0 for no): ");
                        scanf("%d", &go);
                        if (go)
                        {
                            SHOW(root);
                            printf("whats the new name for the fother : ");
                            scanf("%s", name_father);
                        }
                        break;

                    case TheFatherIsNotElu:
                        printf("the fother must be  Elu so you can add ANY pross ");
                        free(new);
                        new = NULL;
                        break;
                    default:
                        break;
                    }
                } while (go);
            }
            break;
            case CHOIX_TERMINE:
            {
                do
                {
                    go = 0;
                    Fixed();

                    int index;
                    printf("whats the index of the core that thou wont to Terminer his prossus  : \n>>>");
                    scanf("%d", &index);
                    Terminer(index);
                    switch (GetError())
                    {
                    case TheIndexIsOutOfTheRange:
                    {
                        printf("The index is out of the reang\n"
                               "Do you wont to enter another index !? (0 for now anty thind for yes)\n"
                               ">>> ");
                        scanf("%d", &go);
                    }
                    break;
                    }
                } while (go);
            }
            break;
            case CHOIX_RUN:
            {

                do
                {
                    go = 0;
                    Fixed();

                    int index;
                    printf("whats the index of the core that core that you want to run the prerssus in it : \n>>>");
                    scanf("%d", &index);
                    RUN(index);
                    switch (GetError())
                    {
                    case TheIndexIsOutOfTheRange:
                    {
                        printf("The index is out of the reang\n"
                               "Do you wont to enter another index !? (0 for now anty thind for yes)\n"
                               ">>> ");

                        scanf("%d", &go);
                    }
                    break;
                    case TheCoseIsRunningAnOtherPross:
                    {
                        printf("You corenly running a pross in the %d core "
                               "you need to kill or block it in order to run aan other \n "
                               "Do you wont to enter another index !? (0 for now anty thind for yes)\n"
                               ">>> ",
                               index);

                        scanf("%d", &go);
                    }
                    break;
                    }

                } while (go);
            }
            break;

            case CHOIX_BLOCK:
            {
                do
                {
                    go = 0;
                    Fixed();
                    int index;
                    printf("whats the index of the core that have the prossus you wont to block  : \n>>>");
                    scanf("%d", &index);
                    BLOQUE(index);
                    switch (GetError())
                    {
                    case TheIndexIsOutOfTheRange:
                    {
                        printf("The index is out of the reang\n"
                               "Do you wont to enter another index !? (0 for now anty thind for yes)\n"
                               ">>> ",
                               index);
                        int go;
                        scanf("%d", &go);
                    }
                    break;
                    case TherIsNoProssInTheCore:
                    {
                        printf("The %d code dont conain any prossus \n"
                               "Do you wont to enter another index !? (0 for now anty thind for yes)\n"
                               ">>> ");
                        int go;
                        scanf("%d", &go);
                    }
                    break;
                    }

                } while (go);
            }

            break;
            }
            Fixed();
        } while (1);

    return 0;
}
