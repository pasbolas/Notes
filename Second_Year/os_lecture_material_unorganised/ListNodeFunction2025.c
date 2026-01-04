// // define a node; declare a node, assign value to node, print contents of this node including the addres of this node


#include <stdio.h>
#include <stdlib.h>

// self-referential structure                       
struct listNode {                                      
   char Data;
   struct listNode *nextPtr; // pointer to next node
}; 

typedef struct listNode ListNode; // synonym for struct listNode
//typedef ListNode* ListNode*; // synonym for ListNode*

// prototypes
void GetData(ListNode**);
void Display(ListNode*);

int main(void)
{ 

   ListNode* Head =NULL;


   GetData(&Head);
   Display(Head);

  puts("end of program\n");

  return 0;

}  
	
	
	
	
	
	

void GetData(ListNode** Node)

{
	
	
   // create a node and add data to the node
   ListNode* newPtr = malloc(sizeof(ListNode)); // create node
   
   // add data to the node
   printf( "\nEnter a character : " );
   scanf("%c", &newPtr-> Data);
	  
   newPtr->nextPtr = NULL; // set node's pointer field to NULL
	  


     // assign newnode address to Node pointer (in main function)
	
	 *Node = newPtr; 

}




void Display(ListNode* newPtr)
{

  
	  // print contents of node
	printf("\n");
	printf("the data field contains the value: %c", newPtr->Data);
	printf("\nthe pointer field contains the value: %p", newPtr->nextPtr);
	printf("\nthe address of the node is %p\n", newPtr);
	


  
} 


