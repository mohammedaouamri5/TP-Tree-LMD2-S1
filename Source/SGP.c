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
	CHOIX_UNBLOQUE,
	CHOIX_QUIT

};

#define TEST                            \
	{                                   \
		if (GetError())                 \
		{                               \
			printf("%d\n", GetError()); \
			exit(1);                    \
		}                               \
	}

int main(int argc, char const *argv[])
{

	int choix = 0;
	Tree root = NULL;

	{
		int8_t go = 0;
		int ramsys = 0;
		do
		{
			go = 0;
			printf("how much ram of the you system wont have (in Byte) \n"
				   ">>> ");
			scanf("%d", &ramsys);

			if (ramsys <= 0)
			{
				puts("[error] : The ram cant be less or equal to 0");
				go = (int8_t)1;
			}

		} while (go);

		SetRam(ramsys);
		int ram = 0;
		do
		{
			go = 0;
			printf("how much ram of the root wont have (in Byte) \n"
				   ">>> ");
			scanf("%d", &ram);

			if (ram >= ramsys)
			{
				printf("[error] : The ram of the new pross should me less that The thee reminder RAM that equal to %d \n", ramsys);
				go = (int8_t)1;
			}
			else if (ramsys <= 0)
			{
				puts("[error] : The ram cant be less or equal to 0");
				go = (int8_t)1;
			}
		} while (go);

		root = CreateTree(ram);
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
			puts("                - 5 CHOIX_TERMINE");
			puts("                - 6 CHOIX_RUN");
			puts("                - 7 CHOIX_UNBLOQUE");
			puts("                - 8 CHOIX_QUIT");
			printf(">>> ");
			scanf("%d", &choix);
			Fixed();

			switch (choix) {
				
				case CHOIX_SHOW: {
				SHOW(root);
			}
				break;
	
				case CHOIX_CLEAN: {
				system("cls");
			}
				break;
	
				case CHOIX_ADD: {
				Tree new = CreateProcessus();
				do
				{
					ScanProcessus(root, new);
					printf("Name of the father : ");
					char name_father[_NAME_SIZE_];
					scanf("%s", name_father);
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
	
				case CHOIX_TERMINE: {

				do
				{
					go = 0;
					Fixed();

					int index;
					printf("whats the index of the core that thou wont to Terminer his prossus  : \n>>> ");
					scanf("%d", &index);
					Terminer(index, root);
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
	
				case CHOIX_RUN:  {

				do
				{

					go = 0;
					Fixed();

					int index;
					printf("whats the index of the core that core that you want to run the prerssus in it : \n>>> ");
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
	
				case CHOIX_BLOCK: {
				do
				{
					go = 0;
					Fixed();
					int index;
					printf("whats the index of the core that have the prossus you wont to block  : \n>>> ");
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
				case CHOIX_KILL: {
				do
				{
					go = 0;
					Fixed();

					char name[_NAME_SIZE_] = "";

					printf("whats the name of the prosuss you wont to Kill : \n>>> ");
					scanf("%s", &name);
					KILLProcessus(root, name);
					switch (GetError())
					{
					case TheNodeDontExist:
					{
						printf("this prosuss %s dont Exist \n"
							   "Do you wont to enter another name !? (0 for now anty thind for yes)\n"
							   ">>> ");
						scanf("%d", &go);
					}
					break;
					}

				} while (go);
			}
				break;
	
				case CHOIX_UNBLOQUE: {

				Fixed();
				UNBLOQUE();
				if (GetError())
					puts("You Do not have any prosses blocked yet ");
			}
				break;
	
				case CHOIX_QUIT: {

				exit(0);
			}
				break;

			
			}

		} while (1);

	return 0;
}