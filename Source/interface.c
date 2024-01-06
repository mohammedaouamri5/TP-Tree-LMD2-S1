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

    printf("adding mm to wow : \n");
    printf("%d \n", push_in_Tree("wow", root, CreateProcessus(6, "mm", 10)));

    SHOW( root ); 

    RUN(0) ; 
    printf("\n\n\n");
    SHOW( root ); 
    RUN(1) ; 
    printf("\n\n\n");
    SHOW( root ); 

    return 0;
}

 
// #include <stdio.h>

// // Node structure
// struct Node {
//     int data;
//     struct Node* next;
// };

// // Function to print the pattern
// void printPattern(struct Node* head) {
//     // Print the top border
//     printf("+--------+");

//     // Loop through the linked list
//     while (head != NULL) {
//         // Print the node
//         printf("+ node %-2d +", head->data);

//         // Move to the next node
//         head = head->next;

//         // Print the border after each node
//         if (head != NULL) {
//             printf("+--------+");
//         }
//     }

//     // Print a new line
//     printf("\n");

//     // Print the bottom border
//     printf("+--------+");
// }

// int main() {
//     // Example linked list creation
//     struct Node nodes[10];

//     for (int i = 0; i < 10; ++i) {
//         nodes[i].data = i + 1;
//         nodes[i].next = (i < 9) ? &nodes[i + 1] : NULL;
//     }

//     // Print the pattern
//     printPattern(&nodes[0]);

//     return 0;
// }


// #include <stdio.h>
// #include <stdio.h>

// #include <stdio.h>

// void moveCursorUpAndRight(int rows, int columns) {
//     // Move the cursor up by the specified number of rows
//     for (int i = 0; i < rows; ++i) {
//         printf("\033[A");
//     }

//     // Move the cursor to the right by the specified number of columns
//     for (int i = 0; i < columns; ++i) {
//         printf("\033[C");
//     }
// }

// int main() {
//     // Move the cursor up by 3 rows and to the right by 5 columns
//     moveCursorUpAndRight(6, 110 );

//     // Print something at the new cursor position
//     printf("Hello, moved!");

//     return 0;
// }
 

