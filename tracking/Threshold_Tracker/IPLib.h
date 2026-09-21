//---------------------------------------------------------------------------
#ifndef _IPLib_
#define _IPLib_
//---------------------------------------------------------------------------
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>

//#include <Windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//---------------------------------------------------------------------------
#ifndef ip_MaxInt
#define ip_MaxInt	(65536)
#endif
//---------------------------------------------------------------------------
#ifndef ip_Byte
#define ip_Byte	unsigned char
#endif
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef Byte
#define Byte	unsigned char
#endif
//---------------------------------------------------------------------------
#define ip_PI	(3.1415926535897932384626433832795)	// PI
#define ip_2PI	(6.283185307179586476925286766559)	// 2*PI
#define ip_PI2	(1.5707963267948966192313216916398) // PI/2
//---------------------------------------------------------------------------
#define ip_Round(x)	(x-int(x)>0.5?int(x)+1:int(x))
//---------------------------------------------------------------------------
#define ip_Min(x,y)	((x)<(y)?(x):(y))
#define ip_Max(x,y)	((x)>(y)?(x):(y))
//---------------------------------------------------------------------------
//----------------------Image Processing Library-----------------------------
//---------------------------------------------------------------------------
long filesize(FILE *stream);
long filesize(char *pFileName);
int ip_LoadImage(char *pFileName,int *w,int *h,ip_Byte *pSrc);
void ip_SaveImage(char *pFileName,int w,int h,ip_Byte *pSrc);
void ip_InvertImage(int w,int h,ip_Byte *pSrc,ip_Byte *pDst);
//---------------------------------------------------------------------------
void ip_SaveVector(char *pFileName,int nCount,float *pVect,int nRadius,ip_Byte cThreshold);
int ip_LoadVector(char *pFileName,int *pCount,float *pVect,int *pRadius,ip_Byte *pThreshold);
void ip_Monochrome(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,ip_Byte nThreshold);
float ip_CirclesError(int nSize,float *pFeatures,float *pTFeatures);
void ip_Normalize(int w,int h,ip_Byte *pSrc,float *pDst,float min,float max);
void ip_NormalizeB(int w,int h,ip_Byte *pSrc,float min,float max);
float ip_CirclesMatching(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,float *pfTmp,int tw,int th,int nScalesCount,float *ppFeatures,int *pRadius,int *xc,int *yc);
void ip_SaveVectorNew(FILE *file,int nCount,float *pVect,int Radius,ip_Byte Threshold);
void ip_LoadVectorNew(FILE *file,int *pCount,float *pVect,int *pRadius,ip_Byte *pThreshold);
void ip_LoadTemplatesFeatures(int *pCircles,int *pFeatures,float *ppFeatures,int *pRadius,ip_Byte *pThreshold,int *pNegative,char *pFileName);
void ip_SaveTemplatesFeatures(int nCircles,int nFeatures,float *ppFeatures,int *pRadius,ip_Byte cThreshold,char *pFileName);
void ip_ScaleFromPoint(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int xc,int yc,float ScaleX,float ScaleY);
void ip_Normalize(int w,int h,ip_Byte *pSrc,float *pDst,float min,float max);
void ip_GenerateTemplatesNew(int w,int h,ip_Byte *pSrc,int r,ip_Byte Threshold,int bNegative,char *pTemplatePath);
//---------------------------------------------------------------------------
void ac_FFT(int w,int h,ip_Byte *pSrc,float *pDst,bool bCentered);
void ac_FFT_Filter(int w,int h,ip_Byte *pSrc,ip_Byte *pMask,ip_Byte *pDst);
void ac_Log(int w,int h,ip_Byte *pSrc,ip_Byte *pMask,ip_Byte *pDst);
void ac_MaxHat_Line(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int nDim);
//---------------------------------------------------------------------------
typedef int ac_Histogram[256];
typedef double ac_LHistogram[256];
//---------------------------------------------------------------------------
void ac_GetHistogram(int w,int h,ip_Byte *pSrc,int nEdge,ac_Histogram Histogram);
void ac_GetHistogram(int w,int h,char *pSrc,int xEdge,int yEdge,ac_Histogram Histogram);
void ac_LogHistogram(ac_Histogram hist,ac_LHistogram lhst);
ip_Byte ac_EntropyTow(ac_Histogram hst,double *lhst);
ip_Byte ac_EntropyTow(ac_Histogram Histogram);
ip_Byte ac_EntropyTow(int w,int h,ip_Byte *pSrc,int nEdge);
ip_Byte ac_EntropyTow(int w,int h,ip_Byte *pSrc,int xEdge,int yEdge);
void ip_KittlerAll2( int W, int H,unsigned char * src, unsigned char * dst, int N, float *ph);
void ac_Monochrome_Entropy(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int nEdge);
void ac_Monochrome_Entropy(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int xEdge,int yEdge);
void ac_Monochrome(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,ip_Byte nThreshold,int XEdge,int YEdge);
void ac_Monochrome(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,ip_Byte nThreshold);
void ac_Monochrome_Entropy(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int nEdge);
void ac_Monochrome_Entropy(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int xEdge,int yEdge,bool white);
//---------------------------------------------------------------------------
#define ac_PI	(3.1415926535897932384626433832795)	// PI
#define ac_2PI	(6.283185307179586476925286766559)	// 2*PI
#define ac_PI2	(1.5707963267948966192313216916398) // PI/2
//---------------------------------------------------------------------------
#define ac_Round(x)	(x-int(x)>0.5?int(x)+1:int(x))
//---------------------------------------------------------------------------
struct ac_Point
{
	double x,y;
};
//---------------------------------------------------------------------------
bool ac_PointInFrame(double x,double y,cv::Rect &Frame);
int ac_FloodFill(int w,int h,unsigned char *pSrc,int x,int y,unsigned char NewColor,unsigned char Epsilon,int &xc,int &yc);
int ac_FloodFill(int w,int h,unsigned char *pSrc,unsigned char *pDst,int x,int y,unsigned char NewSrcColor,unsigned char NewDstColor,unsigned char Epsilon,int &xc,int &yc);
void ac_FilterRegions(int w,int h,unsigned char *pSrc,unsigned char *pDst,cv::Rect &Frame,unsigned char BkIndex,int nMin,int nMax,unsigned char Epsilon);
void ac_IsolateTarget(int w,int h,unsigned char *pSrc,unsigned char *pDst,cv::Rect &Frame,unsigned char BkIndex,unsigned char Epsilon);
void ac_RemoveBorders(int w,int h,unsigned char *pSrc,cv::Rect &Frame,unsigned char BkIndex,unsigned char Epsilon,int nFrame);
void ac_ImageCenterMono(int w,int h,unsigned char *pSrc,double &x0,double &y0);
void ac_MoveImage(int w,int h,unsigned char *pSrc,unsigned char *pDst,int x0,int y0,int x1,int y1);
void ac_Gaussian(int w,int h,unsigned char *pSrc,unsigned char *pDst,int nDim);
void ac_FastGaussianWin5x5(int w,int h,unsigned char *pSrc,unsigned char *pDst,int Bx,int By);
void ac_FastGaussianWin3x3(int w,int h,unsigned char *pSrc,unsigned char *pDst,int Bx,int By);
void ac_ActiveContour(int w,int h,unsigned char *pSrc,double &x0,double &y0,double &r,int nCount,ac_Point *pContour);
double ac_Distance(cv::Point &p1,cv::Point &p2);
double ac_Distance(ac_Point &p1,ac_Point &p2);
double ac_Distance(double x1,double y1,double x2,double y2);
double ac_ActiveContour_Radius(int nCount,ac_Point *pContour);
void ac_ActiveContour_Center(int nCount,ac_Point *pContour,double &x0,double &y0);
cv::Rect ac_ActiveContour_Frame(int nCount,ac_Point *pContour);
void ac_Median(int w,int h,unsigned char *pSrc,unsigned char *pDst,int nDim);
void ac_Mean(int w,int h,unsigned char *pSrc,unsigned char *pDst,int nDim);
void ac_ReplaceColor(int w,int h,unsigned char *pSrc,unsigned char *pDst,unsigned char color1,unsigned char color2,unsigned char E,unsigned char Edge);
void ip_KittlerAll( int W, int H,unsigned char * src, unsigned char * dst);
//---------------------------------------------------------------------------
struct ip_Target
{
	int x,y;
	cv::Point p;
	int nSize;
    double dDist;
};

typedef std::vector<ip_Target> ip_Targets;
//---------------------------------------------------------------------------
void ac_Erosion_White(int w,int h,char *pSrc,char *pDst,int nDim);
void ac_Dilation_White(int w,int h,char *pSrc,char *pDst,int nDim);
void ac_Opening_White(int w,int h,char *pSrc,int nDim);
void ac_Closing_White(int w,int h,char *pSrc,int nDim);
void ac_Erosion_White(int w,int h,char *pSrc,char *pDst,int nDim,int xEdge,int yEdge);
void ac_Dilation_White(int w,int h,char *pSrc,char *pDst,int nDim,int xEdge,int yEdge);
void ac_Opening_White(int w,int h,char *pSrc,int nDim,int xEdge,int yEdge);
void ac_Closing_White(int w,int h,char *pSrc,int nDim,int xEdge,int yEdge);
void ip_BitsToByte   (int W, int H, unsigned char * src, unsigned char * dst);
void ip_ByteToBits   (int W, int H, unsigned char * src, unsigned char * dst);
void ip_FastBinErode (int W, int H, unsigned char * src, unsigned char * dst);
void ip_FastBinDilate(int W, int H, unsigned char * src, unsigned char * dst);
void ip_FastBinClose (int W, int H, unsigned char * src, unsigned char * dst);
void ip_FastBinOpen  (int W, int H, unsigned char * src, unsigned char * dst);
void ip_median_3x3   (int W, int H, unsigned char * src, unsigned char * dst);
void ErodeBin(unsigned char *src, unsigned char *dst,int W,int H);
void DilateBin(unsigned char *src, unsigned char *dst,int W,int H);
void OpenBin(unsigned char *src, unsigned char *dst,int W,int H);
void CloseBin(unsigned char *src, unsigned char *dst,int W,int H);

//---------------------------------------------------------------------------
void ip_Negative(int w,int h,ip_Byte *pSrc,ip_Byte *pDst);
void MaxHatRowPyr(unsigned char *SRC,unsigned char *DST, int Width ,int Height, int FW);
void ip_TopHatRow(unsigned char *SRC,unsigned char *DST, int IW ,int IH, int FW);
void ip_BottomHatRow(unsigned char *SRC,unsigned char *DST, int IW ,int IH, int FW);
void ip_TopHatRowN(unsigned char *SRC,unsigned char *DST, int IW ,int IH, int FW);
void ip_BottomHatRowN(unsigned char *SRC,unsigned char *DST, int IW ,int IH, int FW);
void FilterActiveContour(ac_Point *pContour,ac_Point *pContourOut,int NP);
float Median3f(float x1,float x2,float x3);
double ActiveContourDistance(ac_Point *pC1,ac_Point *pC2, int NP);

//---------------------------------------------------------------------------
extern int s_nIterations;
extern int s_nThreshold;
extern int s_nPoints;
extern double s_dRmin;
extern double s_dRmax;
//---------------------------------------------------------------------------
#endif
