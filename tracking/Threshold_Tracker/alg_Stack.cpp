//---------------------------------------------------------------------------
#include <stdlib.h>
#include "alg_Stack.h"
//---------------------------------------------------------------------------
void Stack_PushBack(Stack_Head *pHead,int nData)
{
	if((*pHead) == 0)
    {
		(*pHead) = (Stack_Head)malloc(sizeof(Stack_Node));
		(*pHead)->nData = nData;
        (*pHead)->pNext = 0;
    }
    else
    {
        Stack_Head pNode;
        // Goto the end node
        pNode = (*pHead);
        while(pNode->pNext != 0)
        {
            pNode = (Stack_Head)(pNode->pNext);
        }
    	pNode->pNext = (Stack_Head)malloc(sizeof(Stack_Node));
        ((Stack_Head)(pNode->pNext))->nData = nData;
        ((Stack_Head)(pNode->pNext))->pNext = 0;
	}
}
//---------------------------------------------------------------------------
int Stack_PopFront(Stack_Head *pHead,int *pData)
{
	if((*pHead) == 0)
	{
    	return 0;
	}
	else
	{
        Stack_Head pNode;
		(*pData) = (*pHead)->nData;
        pNode = (*pHead);
        (*pHead) = (Stack_Head)((*pHead)->pNext);
		free(pNode);
		pNode = 0;
		return 1;
	}
}
//---------------------------------------------------------------------------
void Stack_Destory(Stack_Head *pHead)
{
	int nData;
	while(Stack_PopFront(&(*pHead),&nData));
}
//---------------------------------------------------------------------------

