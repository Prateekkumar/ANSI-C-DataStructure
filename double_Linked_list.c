# include <stdio.h>
# include <stdlib.h>


typedef struct node {
	int num;
	struct node *pNext;
	struct node *pPrev;
	} my_struct;
/*
The create() function will be used to create the double linked list.
*/
void create(my_struct **pHead, int value){
	my_struct *pTail=*pHead ;				//local copy of head pointer
	my_struct *ptrNode = NULL;				
	
	ptrNode  = (my_struct *)malloc(sizeof(my_struct));	//allocating memory to the ptrNode
	if(ptrNode != NULL)					
	{
	ptrNode->num= value; 		// creating a node with the value passed if there is no prior exising node.
	ptrNode->pNext = NULL;  	//So pNext dosent point anywhere.
	while(pTail != NULL && pTail->pNext != NULL) //Iterating through the list till next value we find is null
		pTail = pTail->pNext;  
	if(pTail != NULL)		
		pTail->pNext = ptrNode;		//making the last node to point to created node.
	ptrNode->pPrev = pTail;		

	if(*pHead == NULL)			//If there is no element in the list we make the head point to new node..
		 *pHead = ptrNode;
	}
}

/*
The destroy function is written to completely delete the lists created and free the memory
before deleting them to avoid memory leak.
The concept used is to create two pointers to the 1st  node (if there is a node) and make the
second pointer point to the next node.Free the previous node and assign the second pointer to the 1st pointer.
*/

void destroy(my_struct **pHead) //** to refect the value in the main() function
{
	my_struct *pTail1;  //creating two pointers pointing the same node.
	my_struct *pTail2;
	pTail1  = *pHead;
	if(pTail1 == NULL){   // returning when there no item in the list.
		printf("Empty List\n");	
		return; 
	}
	while(pTail1 != NULL) {   //Traversing through the element list.
		pTail2 = pTail1->pNext; 
		printf("Deleting %d\n", pTail1->num);
		free(pTail1);  //free the previous element 
		pTail1 = pTail2; //make the two pointers point the same node again.
	}
	*pHead = NULL; //after deletion setting the head as null.
	printf("All elements in the list successfully deleted\n");	
}

/* The numOfElem() function is written to return the number of elements in the list.
The idea is to iterate to the end of the list and count the number of steps to reach the end*/

int numOfElem(my_struct *pHead) {
	int count = 0;
	my_struct *pTail = pHead; //local variable pointing to the head.
	while(pTail != NULL) //iterating to the end and counting.
	{
		count += 1;
		pTail = pTail->pNext;  

	}
	return count;
}

/*print() function is used to print the number elements of the list.
Iterating till the next is a NULL value and we print the elements */ 

void print(my_struct *pHead) {
	my_struct *pTail =pHead;
	while(pTail !=NULL) //printing all the elements untill we find pTail as NULL
		{printf("%d \n\n",pTail->num);
			pTail = pTail->pNext;
		} 
}
/* This function gets elements at a given index and print the respective element.
traversing to the next elements untill reaching the given index and return the element.*/

int getElements(my_struct *pHead,int index){
	my_struct *pTail =pHead; 
	int i;	//Declared i here instead of the for loop because my windows compiler gave an error. gcc seems ok with it, so you don't need to worry about it.
	if(pHead != NULL && numOfElem(pHead) >= index) {
		for(i =0;i < index;i++){
			pTail = pTail->pNext; //traversing the list until reaching the given index. 
			
	}		
		return pTail->num; //returning the element at the specified index.
} 
	return -1;
}


/* 
removeElem() function removes the elements and at the given index.
To remove the element from the list at the index ,first traverse till the Index.After finding the
right Index make the previous element point the index next element and the Index next element point the
previous element.Finally free the element.
 */
void removeElem(my_struct **pHead,int index) {
	my_struct *pTail = *pHead;	
	my_struct *pN,*pPr;
	int i;	
	if(pHead !=NULL && numOfElem(*pHead) >= index) {
		for(i=0;i<index;i++) {
			pTail = pTail->pNext;
	}
		pN = pTail->pNext;  //Poining to the next node of current current node(pTail). 
		pPr = pTail->pPrev; //Pointing to the previous node of the current node(pTail).
	if(pPr != NULL)				
		pPr->pNext=pTail->pNext; //maiking the pPr point next of the current node pTail.
	else
		{
			*pHead = pTail->pNext;
	}
	if(pN != NULL)
		pN->pPrev =pTail->pPrev; //making the pN's previous node as current node's previous.
		free(pTail);

	}
	
}
/*This function basically appends two lists.
So creates list and exixsting list is appended by making the last element of existing list
point to the first element of the second list and last element of the second list made as null.
*/
void AppendList(my_struct *pHead1, my_struct **pHead2){
	my_struct *pTail = pHead1;

	while(pTail != NULL && pTail->pNext != NULL)
		pTail = pTail->pNext;

	if(pTail != NULL)
	{
		pTail->pNext = *pHead2;
		if(pHead2 != NULL)
			(*pHead2)->pPrev = pTail; //changing the precedence order
		*pHead2 = NULL; 
	}
}

void findElem(my_struct *pHead, int num, int **pIndexList, int *pNumOfMatches)
{
        my_struct *pTail = pHead;
	int i;
        int NumOfElements;
	
        if(pHead != NULL)
	{
		NumOfElements = numOfElem(pHead);	//Get total number of elements in the list
		*pNumOfMatches = 0;	//No. of times a match is found.
		if(NumOfElements > 0)
			*pIndexList = (int *)malloc(sizeof(int)*NumOfElements); //Allocate enough memory to store all the index values that match. At most this can be equal to NumOfElements.
		
                for(i=0;i<NumOfElements;i++)	//Better to use a variable like this because otherwise you have a function call every time the condition is checked. This increases run time.
		{
                        if(pTail->num == num)
			{
				(*pIndexList)[*pNumOfMatches] = i; //store the index where a match is found.
				*pNumOfMatches += 1;
                        }
                        
			pTail = pTail->pNext; 
		}
	}
}

int main() {
	my_struct *pHead = NULL;
	int choice = 0;
	int NumOfMatches = 0; //Num of matches found
	int *pMatchList = NULL; //list to hold all matches
	int i; //For loop counter
	
	while(choice < 11){
	printf("--------------------MENU-------------------------\n");
	printf("To CREATE LIST  			:	1\n");
	printf("To PRINT THE LIST			:	2\n"); 
	printf("To DESTROY LIST  			:	3\n");
	printf("To GET FIRST ELEMENT 			:	4\n");
	printf("To GET LAST ELEMENT 			:	5\n");
	printf("To GET NUMBER OF ELEMENTS		:	6\n");
	printf("To GET ELEMENT AT GIVEN INDEX		:	7\n");
	printf("TO REMOVE ELEMENTS AT GIVEN INDEX	:	8\n");
	printf("To APPEND ONE LIST TO ANOTHER		:	9\n");
	printf("TO SEARCH FOR GIVEN VALUE IN THE LIST	:	10\n");
	printf("TO EXIT FROM THE PROGRAM		:	11\n");
	printf("ENTER THE CHOICE :  ");
	scanf("%d",&choice);
	if (choice == 1) {
		int num;
		printf("You have chosen to create the list\n\n");
		printf("Enter the elements (integer)\n");
		scanf("%d",&num);
		create(&pHead,num);
	}
	
	else if(choice == 2) {
		printf("The existing elements of the list are:\n\n");
		print(pHead);
	}
	
	else if(choice == 3) {
		char res;
		printf("You have chosen to destroy the list\n\n");
		printf("Do you want to delete the list:(y/n)\n\n");
		scanf("  %c",&res);
		printf("Entered the response");
		if(res == 'y') {
			destroy(&pHead);
			printf("Your list is successfully deleted\n\n");

		}
		else 	printf("You have chosen not to continue with deletion\n\n");
	}
	else if(choice == 4) {
		printf("You have chosen to get the first element in the list");
		printf("The first element of the list is :%d\n\n",getElements(pHead,0));
		
	}	
	else if(choice ==5) {
		int num;
		printf("You have chosen to print the last element of the list\n\n");
		num = numOfElem(pHead);
		printf("The last element of the list is :%d\n\n",getElements(pHead,num-1));
	}
	else if(choice ==6) {
	printf("You have to get the number of elements\n\n");
	printf("The number of elements in the list is :%d \n\n", numOfElem(pHead));
	}

	else if(choice ==7) {
		int index;
		printf("You have chosen to print elements at the given Index\n\n");
		printf("Enter the index of the element:\n");
		scanf(" %d",&index);
		printf("The element at the given index-> %d is %d\n\n",index,getElements(pHead,index));
		
	}
	else if(choice ==8) {
		int index;
		printf("You have chosen you delete the elment at the given index\n");
		printf("Enter the index of the list\n");
		scanf(" %d",&index);
		removeElem(&pHead,index);
		printf("The list after removing element at index %d is\n\n",index);
		print(pHead);
	
	}	
	else if(choice ==9) {
        	my_struct *pHead2 = NULL;  //creating another list
		char ch;
		int e;
		printf("You have chosen to add two lists\n");
		printf("You have to create another list before adding to the existing list\n\n");
		while(1) {
			printf("Do you want to enter more elements:(y/n):\n");
			scanf(" %c",&ch);
			if (ch !='y') break;

			else {printf("Enter the elements of the second list\n");
			scanf(" %d",&e);
			create(&pHead2,e);}
		printf("Your second list is successfully as:\n");
		print(pHead2);
		AppendList(pHead,&pHead2);
		printf("Your list is appended to the previous list");
		printf("The new list after appending is:)");
		print(pHead);
		

	}
		
	}
	
	else if (choice == 10) {
		int num;
		printf("You have chosen to search an element in the list\n");
		printf("Enter the element you want to search:");
		scanf("%d",&num);
		findElem(pHead, num, &pMatchList, &NumOfMatches); 	//Find all matches
		
		printf("%d matches were found\n", NumOfMatches);
		for(i = 0; i < NumOfMatches;i++)	//Print all matches
			printf("%d\n",pMatchList[i]);
		if(pMatchList != NULL) //Free memory to avoid memory leaks
		{
			free(pMatchList);
			pMatchList = NULL;
		}
	}
	else if(choice == 11) {
		printf("****************************************************\n");
		printf("Thanks for using the system for Double Linked list\n");
		printf("****************************************************\n");
	}
	else {
		printf("Enter in the range 1 to 11\n");
	}

	}

}	
