//---------------------------------------------------------------------------
#ifndef alg_StackH
#define alg_StackH
//---------------------------------------------------------------------------
typedef struct
{
	int nData;
	void *pNext;
} Stack_Node;
//---------------------------------------------------------------------------
typedef Stack_Node *Stack_Head;
//---------------------------------------------------------------------------
void Stack_PushBack(Stack_Head *pHead,int nData);
int Stack_PopFront(Stack_Head *pHead,int *pData);
void Stack_Destory(Stack_Head *pHead);
//---------------------------------------------------------------------------
#endif
