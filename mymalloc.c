#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BUF_LEN 10000


struct heapCell {
	size_t size;
	void *buff;
	struct cell *next;
};

typedef struct heapCell freeCell;
freeCell *root;

// leftNode    allocatedSpace    rightNode
// ------------||||||||||||||--------------
//
//  *shrink*        *drop*     *add to list*
//
void* AddCell(freeCell *leftNode, int index,size_t s)
{
	freeCell *rightNode = (freeCell*)malloc(sizeof(freeCell));
	rightNode->size=leftNode->size-index-s;
	rightNode->buff = leftNode->buff+index+s;
	
	leftNode->size = index;
	leftNode->next=root->next;
	root->next=leftNode;

	rightNode->next=root->next;
	root->next=rightNode;
	
	return leftNode->buff+index;
}


void *mymalloc(size_t s)
{
	freeCell *head=root;
	while(head!=NULL)
	{
		if(s<=head->size)
		{
			int index = rand()%(head->size-s);	
			return AddCell(head,index,s);
			
		}
		head=head->next;
	}
	return NULL;
}

void initcell()
{

	srand(time(NULL));
	root=(freeCell*)malloc(sizeof(freeCell));
	root->size = (size_t)BUF_LEN;
	root->buff=(void*)malloc(sizeof(char)*BUF_LEN);
	root->next=NULL;
}

int main()
{
	initcell();
	printf("%d ammount of bytes allocated at %p\n",BUF_LEN,root);
	void* b=mymalloc(500);
	printf("500 bytes allocated at %p\n",b);
}
