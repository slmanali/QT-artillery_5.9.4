//---------------------------------------------------------------------------
#include <stdlib.h>
#include <memory.h>
#include "alg_Labeling.h"
#include "alg_Stack.h"
//---------------------------------------------------------------------------
// Normal Ordering (1)
static ip_Point T2[9]={
                        {00,00},// 0
                        {+1,00},// 1
                        {+1,+1},// 2
                        {00,+1},// 3
                        {-1,+1},// 4
                        {-1,00},// 5
                        {-1,-1},// 6
                        {00,-1},// 7
                        {+1,-1},// 8
					};
//---------------------------------------------------------------------------
int ip_FloodFill(int w,int h,ip_Byte *pSrc,int x,int y,ip_Byte NewColor,ip_Byte Epsilon,int *xc,int *yc)
{
	(*xc) = 0;
    (*yc) = 0;
	int nRegionSize = 0;
	ip_Byte OldColor;
    int Px=x;
    int Py=y;
    int P0x=Px;
    int P0y=Py;
    int NewPx=Px;
    int NewPy=Py;
    int N,i;
    Stack_Node *pStackx = 0;
    Stack_Node *pStacky = 0;
	if(pSrc == 0)
	{
		return nRegionSize; 
	}
    else
    if((x >= w) && (y >= h))
    {
		return nRegionSize;
    }
    OldColor = pSrc[x+w*y];
    if(abs(OldColor-NewColor) <= Epsilon)
    {
        return nRegionSize;
    }
    while(1)
    {
        if(((Px+T2[1].x>=0)&&(Px+T2[1].x<=w-1)&&(Py+T2[1].y>=0)&&(Py+T2[1].y<=h-1))&&(abs(pSrc[(Px+T2[1].x)+(Py+T2[1].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[1].x;
            NewPy=Py+T2[1].y;
        }
        else
        if(((Px+T2[2].x>=0)&&(Px+T2[2].x<=w-1)&&(Py+T2[2].y>=0)&&(Py+T2[2].y<=h-1))&&(abs(pSrc[(Px+T2[2].x)+(Py+T2[2].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[2].x;
            NewPy=Py+T2[2].y;
        }
        else
        if(((Px+T2[3].x>=0)&&(Px+T2[3].x<=w-1)&&(Py+T2[3].y>=0)&&(Py+T2[3].y<=h-1))&&(abs(pSrc[(Px+T2[3].x)+(Py+T2[3].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[3].x;
            NewPy=Py+T2[3].y;
        }
        else
        if(((Px+T2[4].x>=0)&&(Px+T2[4].x<=w-1)&&(Py+T2[4].y>=0)&&(Py+T2[4].y<=h-1))&&(abs(pSrc[(Px+T2[4].x)+(Py+T2[4].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[4].x;
            NewPy=Py+T2[4].y;
        }
        else
        if(((Px+T2[5].x>=0)&&(Px+T2[5].x<=w-1)&&(Py+T2[5].y>=0)&&(Py+T2[5].y<=h-1))&&(abs(pSrc[(Px+T2[5].x)+(Py+T2[5].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[5].x;
            NewPy=Py+T2[5].y;
            pSrc[Px+Py*w]=NewColor;
            (*xc) += Px;
            (*yc) += Py;
            nRegionSize++;
            if( ((Px+T2[7].x>=0)&&(Px+T2[7].x<=w-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=h-1))&&
                ((Px+T2[8].x>=0)&&(Px+T2[8].x<=w-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=h-1))&&
                (abs(pSrc[(Px+T2[7].x)+(Py+T2[7].y)*w]-OldColor) > Epsilon)&&
                (abs(pSrc[(Px+T2[8].x)+(Py+T2[8].y)*w]-OldColor) <= Epsilon)
              )
            {
                Stack_PushBack(&pStackx,Px);
                Stack_PushBack(&pStacky,Py);
            }
        }
        else
        if(((Px+T2[6].x>=0)&&(Px+T2[6].x<=w-1)&&(Py+T2[6].y>=0)&&(Py+T2[6].y<=h-1))&&(abs(pSrc[(Px+T2[6].x)+(Py+T2[6].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[6].x;
            NewPy=Py+T2[6].y;
            pSrc[Px+Py*w]=NewColor;
            (*xc) += Px;
            (*yc) += Py;
            nRegionSize++;
            if( ((Px+T2[7].x>=0)&&(Px+T2[7].x<=w-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=h-1))&&
                ((Px+T2[8].x>=0)&&(Px+T2[8].x<=w-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=h-1))&&
                (abs(pSrc[(Px+T2[7].x)+(Py+T2[7].y)*w]-OldColor) > Epsilon)&&
                (abs(pSrc[(Px+T2[8].x)+(Py+T2[8].y)*w]-OldColor) <= Epsilon)
              )
            {
                Stack_PushBack(&pStackx,Px);
                Stack_PushBack(&pStacky,Py);
            }
        }
        else
        if(((Px+T2[7].x>=0)&&(Px+T2[7].x<=w-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=h-1))&&(abs(pSrc[(Px+T2[7].x)+(Py+T2[7].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[7].x;
            NewPy=Py+T2[7].y;
            pSrc[Px+Py*w]=NewColor;
            (*xc) += Px;
            (*yc) += Py;
            nRegionSize++;
        }
        else
        if(((Px+T2[8].x>=0)&&(Px+T2[8].x<=w-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=h-1))&&(abs(pSrc[(Px+T2[8].x)+(Py+T2[8].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[8].x;
            NewPy=Py+T2[8].y;
            pSrc[Px+Py*w]=NewColor;
            (*xc) += Px;
            (*yc) += Py;
            nRegionSize++;
        }
        else
        {
            pSrc[Px+Py*w]=NewColor;
            (*xc) += Px;
            (*yc) += Py;
            nRegionSize++;
        	while(1)
            {
            	if((pStackx == 0) || (pStacky == 0))
                {
                	Stack_Destory(&pStackx);
                	Stack_Destory(&pStacky);
                    (*xc) /= float(nRegionSize);
                    (*yc) /= float(nRegionSize);
                	return nRegionSize;
                }
	            else
    	        {
                	Stack_PopFront(&pStackx,&P0x);
                	Stack_PopFront(&pStacky,&P0y);
                    N = 0;
                    for(i=1;i<=8;i++)
                    {
                        if(((P0x+T2[i].x>=0)&&(P0x+T2[i].x<=w-1)&&(P0y+T2[i].y>=0)&&(P0y+T2[i].y<=h-1))&&(abs(pSrc[(P0x+T2[i].x)+(P0y+T2[i].y)*w]-OldColor) <= Epsilon))
                        {
                            NewPx=P0x+T2[i].x;
                            NewPy=P0y+T2[i].y;
                        	N++;
                        }
                    }
                }
                if(N > 0)
                {
                 	break;
                }
            }
        }
        Px=NewPx;
        Py=NewPy;
    }
}
//---------------------------------------------------------------------------
int ip_FloodFill1(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int x,int y,ip_Byte NewSrcColor,ip_Byte NewDstColor,ip_Byte Epsilon)
{
	int nRegionSize = 0;
	ip_Byte OldColor;
    int Px=x;
    int Py=y;
    int P0x=Px;
    int P0y=Py;
    int NewPx=Px;
    int NewPy=Py;
    int N,i;
    Stack_Node *pStackx = 0;
    Stack_Node *pStacky = 0;
	if(pSrc == 0)
	{
		return nRegionSize;
	}
    else
    if((x >= w) && (y >= h))
    {
		return nRegionSize;
    }
    OldColor = pSrc[x+w*y];
    if(abs(OldColor-NewSrcColor) <= Epsilon)
    {
        return nRegionSize;
    }
    while(1)
    {
        if(((Px+T2[1].x>=0)&&(Px+T2[1].x<=w-1)&&(Py+T2[1].y>=0)&&(Py+T2[1].y<=h-1))&&(abs(pSrc[(Px+T2[1].x)+(Py+T2[1].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[1].x;
            NewPy=Py+T2[1].y;
        }
        else
        if(((Px+T2[2].x>=0)&&(Px+T2[2].x<=w-1)&&(Py+T2[2].y>=0)&&(Py+T2[2].y<=h-1))&&(abs(pSrc[(Px+T2[2].x)+(Py+T2[2].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[2].x;
            NewPy=Py+T2[2].y;
        }
        else
        if(((Px+T2[3].x>=0)&&(Px+T2[3].x<=w-1)&&(Py+T2[3].y>=0)&&(Py+T2[3].y<=h-1))&&(abs(pSrc[(Px+T2[3].x)+(Py+T2[3].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[3].x;
            NewPy=Py+T2[3].y;
        }
        else
        if(((Px+T2[4].x>=0)&&(Px+T2[4].x<=w-1)&&(Py+T2[4].y>=0)&&(Py+T2[4].y<=h-1))&&(abs(pSrc[(Px+T2[4].x)+(Py+T2[4].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[4].x;
            NewPy=Py+T2[4].y;
        }
        else
        if(((Px+T2[5].x>=0)&&(Px+T2[5].x<=w-1)&&(Py+T2[5].y>=0)&&(Py+T2[5].y<=h-1))&&(abs(pSrc[(Px+T2[5].x)+(Py+T2[5].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[5].x;
            NewPy=Py+T2[5].y;
            pSrc[Px+Py*w]=NewSrcColor;
            pDst[Px+Py*w]=NewDstColor;
            nRegionSize++;
            if( ((Px+T2[7].x>=0)&&(Px+T2[7].x<=w-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=h-1))&&
                ((Px+T2[8].x>=0)&&(Px+T2[8].x<=w-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=h-1))&&
                (abs(pSrc[(Px+T2[7].x)+(Py+T2[7].y)*w]-OldColor) > Epsilon)&&
                (abs(pSrc[(Px+T2[8].x)+(Py+T2[8].y)*w]-OldColor) <= Epsilon)
              )
            {
                Stack_PushBack(&pStackx,Px);
                Stack_PushBack(&pStacky,Py);
            }
        }
        else
        if(((Px+T2[6].x>=0)&&(Px+T2[6].x<=w-1)&&(Py+T2[6].y>=0)&&(Py+T2[6].y<=h-1))&&(abs(pSrc[(Px+T2[6].x)+(Py+T2[6].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[6].x;
            NewPy=Py+T2[6].y;
            pSrc[Px+Py*w]=NewSrcColor;
            pDst[Px+Py*w]=NewDstColor;
            nRegionSize++;
            if( ((Px+T2[7].x>=0)&&(Px+T2[7].x<=w-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=h-1))&&
                ((Px+T2[8].x>=0)&&(Px+T2[8].x<=w-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=h-1))&&
                (abs(pSrc[(Px+T2[7].x)+(Py+T2[7].y)*w]-OldColor) > Epsilon)&&
                (abs(pSrc[(Px+T2[8].x)+(Py+T2[8].y)*w]-OldColor) <= Epsilon)
              )
            {
                Stack_PushBack(&pStackx,Px);
                Stack_PushBack(&pStacky,Py);
            }
        }
        else
        if(((Px+T2[7].x>=0)&&(Px+T2[7].x<=w-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=h-1))&&(abs(pSrc[(Px+T2[7].x)+(Py+T2[7].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[7].x;
            NewPy=Py+T2[7].y;
            pSrc[Px+Py*w]=NewSrcColor;
            pDst[Px+Py*w]=NewDstColor;
            nRegionSize++;
        }
        else
        if(((Px+T2[8].x>=0)&&(Px+T2[8].x<=w-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=h-1))&&(abs(pSrc[(Px+T2[8].x)+(Py+T2[8].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[8].x;
            NewPy=Py+T2[8].y;
            pSrc[Px+Py*w]=NewSrcColor;
            pDst[Px+Py*w]=NewDstColor;
            nRegionSize++;
        }
        else
        {
            pSrc[Px+Py*w]=NewSrcColor;
            pDst[Px+Py*w]=NewDstColor;
            nRegionSize++;
        	while(1)
            {
            	if((pStackx == 0) || (pStacky == 0))
                {
                	Stack_Destory(&pStackx);
                	Stack_Destory(&pStacky);
                	return nRegionSize;
                }
	            else
    	        {
                	Stack_PopFront(&pStackx,&P0x);
                	Stack_PopFront(&pStacky,&P0y);
                    N = 0;
                    for(i=1;i<=8;i++)
                    {
                        if(((P0x+T2[i].x>=0)&&(P0x+T2[i].x<=w-1)&&(P0y+T2[i].y>=0)&&(P0y+T2[i].y<=h-1))&&(abs(pSrc[(P0x+T2[i].x)+(P0y+T2[i].y)*w]-OldColor) <= Epsilon))
                        {
                            NewPx=P0x+T2[i].x;
                            NewPy=P0y+T2[i].y;
                        	N++;
                        }
                    }
                }
                if(N > 0)
                {
                 	break;
                }
            }
        }
        Px=NewPx;
        Py=NewPy;
    }
}
//---------------------------------------------------------------------------
void ip_FilterRegions(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,ip_Byte BkIndex,int nMin,int nMax,ip_Byte Epsilon,bool bKeepCenterJust)
{
	int x,y;
	int xc,yc;
	ip_Byte Index;
	int nRegionSize;
    memset(pDst,BkIndex,w*h);
	int d = 3;
	for(y=0+d;y<h-d;y++)
    {
     	for(x=0+d;x<w-d;x++)
        {
         	Index = pSrc[x+y*w];
            if(Index != BkIndex)
            {
				nRegionSize = ip_FloodFill(w,h,pSrc,x,y,Index/2,Epsilon,&xc,&yc);
                if((nRegionSize >= nMax) || (nRegionSize <= nMin))
                    ip_FloodFill(w,h,pSrc,x,y,BkIndex,Epsilon,&xc,&yc);
                else
                {
                 	if(bKeepCenterJust)
                    {
//	                	pDst[xc+yc*w] = Index;
//	                	pDst[xc+yc*w] = 255;
						for(int i=-d;i<=d;i++)
                        {
                        	for(int j=-d;j<=d;j++)
                            {
                             	pDst[(xc+i)+(yc+j)*w] = 255;
                            }
                        }
                    }
                    else
	                	ip_FloodFill1(w,h,pSrc,pDst,x,y,BkIndex,Index,Epsilon);
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void ip_IsolateTarget(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,ip_Byte BkIndex,ip_Byte Epsilon)
{
	int x,y;
	int xc,yc;
	ip_Byte Index,NewIndex,OrgIndex;
	int nRegionSize,nMaxRegionSize,MaxX,MaxY;
    NewIndex = 127;
    nMaxRegionSize = -ip_MaxInt;
    memset(pDst,BkIndex,w*h);
	for(y=0;y<h;y++)
    {
     	for(x=0;x<w;x++)
        {
         	Index = pSrc[x+y*w];
            if((Index != BkIndex) && (Index != NewIndex))
            {
				nRegionSize = ip_FloodFill(w,h,pSrc,x,y,NewIndex,Epsilon,&xc,&yc);
                if(nRegionSize > nMaxRegionSize)
                {
					OrgIndex = Index;
                 	nMaxRegionSize = nRegionSize;
                    MaxX = x;
                   	MaxY = y;
                }
            }
        }
    }
    if(nMaxRegionSize > 0)
    {
		ip_FloodFill1(w,h,pSrc,pDst,MaxX,MaxY,BkIndex,OrgIndex,Epsilon);
    }
}
//---------------------------------------------------------------------------
void ip_RemoveBorders(int w,int h,ip_Byte *pSrc,ip_Byte BkIndex,ip_Byte Epsilon,int nFrame)
{
	ip_Byte Index;
    int x,y,i;
    int xc,yc;
    for(i=0;i<nFrame;i++)
    {
        x = 0+i;
        for(y=0+i;y<h-i;y++)
        {
            Index = pSrc[x+y*w];
            if(Index != BkIndex)
            {
                ip_FloodFill(w,h,pSrc,x,y,BkIndex,Epsilon,&xc,&yc);
            }
        }
        x = w-1-i;
        for(y=0+i;y<h-i;y++)
        {
            Index = pSrc[x+y*w];
            if(Index != BkIndex)
            {
                ip_FloodFill(w,h,pSrc,x,y,BkIndex,Epsilon,&xc,&yc);
            }
        }
        y = 0+i;
        for(x=0+i;x<w-i;x++)
        {
            Index = pSrc[x+y*w];
            if(Index != BkIndex)
            {
                ip_FloodFill(w,h,pSrc,x,y,BkIndex,Epsilon,&xc,&yc);
            }
        }
        y = h-1-i;
        for(x=0+i;x<w-i;x++)
        {
            Index = pSrc[x+y*w];
            if(Index != BkIndex)
            {
                ip_FloodFill(w,h,pSrc,x,y,BkIndex,Epsilon,&xc,&yc);
            }
        }
    }
}
//---------------------------------------------------------------------------

