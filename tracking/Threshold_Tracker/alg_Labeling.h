//---------------------------------------------------------------------------
#ifndef alg_LabelingH
#define alg_LabelingH
//---------------------------------------------------------------------------
#ifndef ip_MaxInt
#define ip_MaxInt	(65536)
#endif
//---------------------------------------------------------------------------
#ifndef ip_Byte
#define ip_Byte	unsigned char
#endif
//---------------------------------------------------------------------------
#ifndef ip_Byte
#define ip_Byte	unsigned char
#endif
//---------------------------------------------------------------------------

typedef struct
{
	int x,y;
} ip_Point;

//---------------------------------------------------------------------------
/*ip_Point Point(int x,int y)
{
	ip_Point p;
	p.x = x;
	p.y = y;
	return p;
}*/
//---------------------------------------------------------------------------
typedef struct
{
	int xc,yc;
	int Surface;
	int Color;
	float Distance;
} ip_target;

int ip_FloodFill(int w,int h,ip_Byte *pSrc,int x,int y,ip_Byte NewColor,ip_Byte Epsilon,int *xc,int *yc);
int ip_FloodFill1(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int x,int y,ip_Byte NewSrcColor,ip_Byte NewDstColor,ip_Byte Epsilon);
void ip_FilterRegions(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,ip_Byte BkIndex,int nMin,int nMax,ip_Byte Epsilon,bool bKeepCenterJust);
void ip_IsolateTarget(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,ip_Byte BkIndex,ip_Byte Epsilon);
void ip_RemoveBorders(int w,int h,ip_Byte *pSrc,ip_Byte BkIndex,ip_Byte Epsilon,int nFrame);
//---------------------------------------------------------------------------
#endif
