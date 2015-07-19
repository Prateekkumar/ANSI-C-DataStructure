#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int value;
	struct node *pLeft;
	struct node *pRight;
	} tree;

tree *createNode(int item) {
                                tree *pNode;
                                pNode =(tree *)malloc(sizeof(tree));
                                pNode->value = item;
                                pNode->pLeft = NULL;
                                pNode->pRight= NULL;
				return pNode;
}

void add(tree **pHead,int item){
	tree *pTail = *pHead;
	
	if(pTail != NULL) {
		
		if(item > pTail->value) { 
			if(pTail->pRight == NULL) {
				pTail->pRight = createNode(item);
			}
			else add(&(pTail->pRight),item);
		}
		else if (item < pTail->value) {
			if(pTail->pLeft == NULL) {
                                pTail->pLeft = createNode(item);	
			}
			else add(&pTail->pLeft,item);
		}
	}
	else {
       		*pHead = createNode(item);
		}	
	
}

void print(tree *pHead) {
	tree *pTail = pHead;
	if(pTail != NULL){
        printf("%d\n", pTail->value);
		if(pTail->pLeft != NULL){
			print(pTail->pLeft);
			
		}
		if(pTail->pRight != NULL) {
			print(pTail->pRight);		
		}
	//printf("%d\n", pTail->value);
	}
	else printf("Empty\n");
}

void destroy(tree *pHead) {
        tree *pTail = pHead;
        if(pTail != NULL){
                if(pTail->pLeft != NULL){
                        destroy(pTail->pLeft);

                }
                if(pTail->pRight != NULL) {
                        destroy(pTail->pRight);
                }
        printf("Destroying node: %d\n", pTail->value);
	free(pTail);
        }
        else printf("Empty\n");
}

int search(tree *pHead, int item) {
	tree *pTail = pHead;
	if(pTail != NULL) {
		if(item == pTail->value) return 1;
		if(item > pTail->value) {
			return search(pTail->pRight,item);
		}
                else return search(pTail->pLeft,item);		
	}
	else return 0;
}

int depth(tree *pHead) {
	if(pHead != NULL) {
		int lHeight = depth(pHead->pLeft);
		int rHeight = depth(pHead->pRight);
		if (lHeight > rHeight) return lHeight+1;
		else return rHeight+1;

	}
	else return 0;
	}

int main(){
	tree *pHead = NULL;
	add(&pHead,8);
	add(&pHead,4);
	add(&pHead,1);
	add(&pHead,5);
       // add(&pHead,6);
        add(&pHead,9);
	print(pHead);
//	destroy(pHead);
	printf("Search 1 :%d\n",search(pHead,5));
        printf("Search 2 :%d\n",search(pHead,10));
	printf("The height of the tree : %d\n",depth(pHead));
	destroy(pHead);
}
