//---------------------------------------------------------------------------
#include <string.h>
#include <math.h>
#include <vector>      
#include "IPLib.h"
#include <memory.h>
//#include "FFT_LIB.h"
#include "KFreqLib.h"
//---------------------------------------------------------------------------
long filesize(FILE *stream)
{
   	long curpos, length;
   	curpos = ftell(stream);
   	fseek(stream, 0L, SEEK_END);
   	length = ftell(stream);
   	fseek(stream, curpos, SEEK_SET);
   	return length;
}
//---------------------------------------------------------------------------
long filesize(char *pFileName)
{
	FILE *file;
    long length;
	file = fopen(pFileName,"rb");
	length = filesize(file);
	fclose(file);
	return length;
}
//---------------------------------------------------------------------------
int ip_LoadImage(char *pFileName,int *w,int *h,ip_Byte *pSrc)
{
	FILE *file;
	file = fopen(pFileName,"rb");
	if(file == 0)	return 0;
	fread(w,sizeof(int),1,file);
	fread(h,sizeof(int),1,file);
    if(pSrc == 0)
    {
		fclose(file);
		return 1;
    }
	fread(pSrc,sizeof(ip_Byte),(*w)*(*h),file);
	fclose(file);
	return 1;
}
//---------------------------------------------------------------------------
void ip_SaveImage(char *pFileName,int w,int h,ip_Byte *pSrc)
{
	FILE *file;
	file = fopen(pFileName,"wb");
	fwrite(&w,sizeof(int),1,file);
	fwrite(&h,sizeof(int),1,file);
	fwrite(pSrc,sizeof(ip_Byte),w*h,file);
	fclose(file);
}
//---------------------------------------------------------------------------
void ip_InvertImage(int w,int h,ip_Byte *pSrc,ip_Byte *pDst)
{
	int i,size;
	size = w*h;
	for(i=0;i<size;i++)
	{
		pDst[i] = ~pSrc[i];
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ip_SaveVector(char *pFileName,int nCount,float *pVect,int nRadius,ip_Byte cThreshold)
{
	FILE *file;
	file = fopen(pFileName,"wb");
	fwrite(&nRadius,sizeof(int),1,file);
	fwrite(&cThreshold,sizeof(ip_Byte),1,file);
	fwrite(&nCount,sizeof(int),1,file);
	fwrite(pVect,sizeof(float),nCount,file);
	fclose(file);
}
//---------------------------------------------------------------------------
int ip_LoadVector(char *pFileName,int *pCount,float *pVect,int *pRadius,ip_Byte *pThreshold)
{
	FILE *file;
	file = fopen(pFileName,"rb");
	if(file == 0)	return 0;
	fread(pRadius,sizeof(int),1,file);
	fread(pThreshold,sizeof(ip_Byte),1,file);
	fread(pCount,sizeof(int),1,file);
    if(pVect == 0)
    {
		fclose(file);
		return 1;
    }
	fread(pVect,sizeof(float),(*pCount),file);
	fclose(file);
	return 1;
}
//---------------------------------------------------------------------------
void ip_Monochrome(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,ip_Byte nThreshold)
{
	int x,y;
    for(y=0;y<h;y++)
    {
        for(x=0;x<w;x++)
        {
        	pDst[x+y*w] = ((pSrc[x+y*w] < nThreshold)?0:255);
        }
    }
}
//---------------------------------------------------------------------------
float ip_CirclesError(int nSize,float *pFeatures,float *pTFeatures)
{
	float dError = 0.0;
    float dDiff;
    float dMaxDiff;
	int i;
	dMaxDiff = -ip_MaxInt;
	for(i=0;i<nSize;i++)
    {
    	dDiff = pFeatures[i]-pTFeatures[i];
    	dError += dDiff*dDiff;
        if(dDiff > dMaxDiff)	dMaxDiff = dDiff;
    }
    if(dMaxDiff > 0)
    {
	    dError -= dMaxDiff*dMaxDiff;
    }
//    dError = sqrt(dError);
    return dError;
}
//---------------------------------------------------------------------------
void ip_Normalize(int w,int h,ip_Byte *pSrc,float *pDst,float min,float max)
{
	float value,coeff;
	int x,y;
	coeff=255.0/(0.00001+max-min);
	for(y=0;y<h;y++)
    {
		for(x=0;x<w;x++)
    	{
	        value = coeff*((float)pSrc[x+w*y]-min);
            if(value > 255.0)
	    		pDst[x+w*y] = 255;
            else
            if(value < 0)
	    		pDst[x+w*y] = 0;
            else
	    		pDst[x+w*y] = value;
        }
    }
}
//---------------------------------------------------------------------------
void ip_Negative(int w,int h,ip_Byte *pSrc,ip_Byte *pDst)
{
	int size = w*h;
	for(int i=0;i<size;i++)
    {
		pDst[i] = ~pSrc[i];
    }
}
//---------------------------------------------------------------------------
void ip_NormalizeB(int w,int h,ip_Byte *pSrc,float min,float max)
{
	float value,coeff;
	int x,y;
	coeff=255.0/(0.00001+max-min);
	for(y=0;y<h;y++)
    {
		for(x=0;x<w;x++)
    	{
	        value = coeff*((float)pSrc[x+w*y]-min);
            if(value > 255.0)
	    		pSrc[x+w*y] = 255;
            else
            if(value < 0)
	    		pSrc[x+w*y] = 0;
            else
	    		pSrc[x+w*y] = (ip_Byte)value;
        }
    }
}
//---------------------------------------------------------------------------
float ip_CirclesMatching(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,float *pfTmp,int tw,int th,int nScalesCount,float *ppFeatures,int *pRadius,int *xc,int *yc)
{
    int nStep = 1;
    float dError,dMinError;
    int bIsOK;
    int tw2,th2;
	int x,y,i;
    tw2 = tw/2;
    th2 = th/2;
    dMinError = ip_MaxInt;
    *xc = w/2;
    *yc = h/2;
    ip_Normalize(w,h,pSrc,pfTmp,15.0,240.0);
	for(y=th2;y<h-th2;y+=nStep)
    {
		for(x=tw2;x<w-tw2;x+=nStep)
    	{
        	if(pDst[x+y*w] == 0)	continue;
    		bIsOK = 0;
 			ip_FreqK(w,h,pfTmp,x,y);
            for(i=0;i<ip_Min(nScalesCount,pRadius[i]);i++)
            {
            	dError = ip_CirclesError(g_nFeatures,g_pFeatures,(ppFeatures+i*g_nFeatures));
                if(dError < dMinError)
                {
                    dMinError = dError;
                    *xc = x;
                    *yc = y;
                    bIsOK = 1;
                }
            }
            if(!bIsOK)
            {
            	// Level 1
                pDst[(x+1)+(y+0)*w] = 0;
                pDst[(x-1)+(y+1)*w] = 0;
                pDst[(x+0)+(y+1)*w] = 0;
                pDst[(x+1)+(y+1)*w] = 0;
             	x += nStep;
            }
        }
    }
    return dMinError;
}
//---------------------------------------------------------------------------
void ip_SaveVectorNew(FILE *file,int nCount,float *pVect,int Radius,ip_Byte Threshold)
{
	fwrite(&Radius,sizeof(int),1,file);
	fwrite(&Threshold,sizeof(ip_Byte),1,file);
	fwrite(&nCount,sizeof(int),1,file);
	fwrite(pVect,sizeof(float),nCount,file);
}
//---------------------------------------------------------------------------
void ip_LoadVectorNew(FILE *file,int *pCount,float *pVect,int *pRadius,ip_Byte *pThreshold)
{
	fread(pRadius,sizeof(int),1,file);
	fread(pThreshold,sizeof(ip_Byte),1,file);
	fread(pCount,sizeof(int),1,file);
    if(pVect == 0)
    {
    	return;
    }
	fread(pVect,sizeof(float),(*pCount),file);
}
//---------------------------------------------------------------------------
void ip_LoadTemplatesFeatures(int *pCircles,int *pFeatures,float *ppFeatures,int *pRadius,ip_Byte *pThreshold,int *pNegative,char *pFileName)
{
    int r,i;

	FILE *file;
	file = fopen(pFileName,"rb");
	if(file == 0)	return;
	fread(pCircles,sizeof(int),1,file);
    fread(pNegative,sizeof(int),1,file);
    if(ppFeatures == 0)
    {
        ip_LoadVectorNew(file,pFeatures,0,&r,pThreshold);
		fclose(file);
    	return;
    }
    if(pRadius == 0)
    {
		fclose(file);
    	return;
    }
	for(i=0;i<(*pCircles);i++)
    {
        ip_LoadVectorNew(file,pFeatures,(ppFeatures+i*(*pFeatures)),&r,pThreshold);
        pRadius[i] = r;
    }
	fclose(file);
}
//---------------------------------------------------------------------------
void ip_SaveTemplatesFeatures(int nCircles,int nFeatures,float *ppFeatures,int *pRadius,ip_Byte cThreshold,char *pFileName)
{
    int i;
	FILE *file;
	file = fopen(pFileName,"wb");
	if(file == 0)	return;
	fwrite(&nCircles,sizeof(int),1,file);
	for(i=0;i<nCircles;i++)
    {
        ip_SaveVectorNew(file,nFeatures,(ppFeatures+i*nFeatures),pRadius[i],cThreshold);
    }
	fclose(file);
}
//---------------------------------------------------------------------------
void ip_ScaleFromPoint(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int xc,int yc,float ScaleX,float ScaleY)
{
	int x,y;
    float ax,bx,ay,by;
    ip_Byte color;
    ax = ScaleX;
    ay = ScaleY;
    bx = xc-ScaleX*w/2.0;
    by = yc-ScaleY*h/2.0; 
	for(int Y=0;Y<h;Y++)
    {
		for(int X=0;X<w;X++)
    	{
			x = (X-bx)/ax;
            y = (Y-by)/ay;
            if(x < 0)	color = 0;
            else
            if(x >= w)	color = 0;
            else
            if(y < 0)	color = 0;
            else
            if(y >= h)	color = 0;
            else
	            color = pSrc[x+y*w];
            pDst[X+Y*w] = color;
        }
    }
}
//---------------------------------------------------------------------------
void ip_GenerateTemplatesNew(int w,int h,ip_Byte *pSrc,int r,ip_Byte Threshold,int bNegative,char *pTemplatePath)
{
	int R,xc,yc,nIndex;
    ip_Byte *pDst = new ip_Byte[w*h];
    float *pTmp = new float[w*h];
	char pTemplateFile[256];
	char pFeaturesFile[256];
    xc = w/2;
    yc = h/2;
    nIndex = 0;

    sprintf(pTemplateFile,"\0");
    strcat(pTemplateFile,pTemplatePath);
    strcat(pTemplateFile,"Template.bin");

    sprintf(pFeaturesFile,"\0");
    strcat(pFeaturesFile,pTemplatePath);
    strcat(pFeaturesFile,"Features.fet");
                              
    ip_SaveImage(pTemplateFile,w,h,pSrc);
    int nCount;

	FILE *file;
	file = fopen(pFeaturesFile,"wb");
	if(file == 0)	return;
    nCount = 81;
	fwrite(&nCount,sizeof(int),1,file);
    fwrite(&bNegative,sizeof(int),1,file);
	for(float ScaleX=1.0;ScaleX<=3.0;ScaleX+=0.25)
    {
		for(float ScaleY=1.0;ScaleY<=3.0;ScaleY+=0.25)
        {
            ip_ScaleFromPoint(w,h,pSrc,pDst,xc,yc,ScaleX,ScaleY);
			ip_Normalize(w,h,pDst,pTmp,15,240);
			ip_FreqK(w,h,pTmp,xc,yc);
            R = std::min(r*ScaleX,r*ScaleY);
            R = std::min(R,w/2);
            ip_SaveVectorNew(file,g_nFeatures,g_pFeatures,R,Threshold);
            nIndex++;
        }
    }
    fclose(file);
    if(pTmp)
    {
     	delete[] pTmp;
        pTmp = NULL;
    }
    if(pDst)
    {
     	delete[] pDst;
        pDst = NULL;
    }
}
//---------------------------------------------------------------------------
/* ac_FFT(int w,int h,ip_Byte *pSrc,float *pDst,bool bCentered)
{
	int k;
    TFFTClass *pFFTClass = new TFFTClass();
    pFFTClass->ResizeBuffers(w,h);
	for(int y=0;y<h;y++)
    {
    	for(int x=0;x<w;x++)
        {
        	k = x+y*w;
			pFFTClass->pInput[k].re = pSrc[k];
			pFFTClass->pInput[k].im = 0.0;
        }
    }
	pFFTClass->FFT();

    float s0,s;
    if(bCentered)
    {
    	int w2,h2;
        w2 = w/2;
        h2 = h/2;
    	// 4 --> 1
        for(int y=0+h2;y<h;y++)
        {
            for(int x=0+w2;x<w;x++)
            {
                k = x+y*w;
                s = sqrt(pFFTClass->pOutput[k].re*pFFTClass->pOutput[k].re+pFFTClass->pOutput[k].im*pFFTClass->pOutput[k].im);
                pDst[(x-w2)+(y-h2)*w] = s;
            }
        }
    	// 1 --> 4
        for(int y=0;y<h2;y++)
        {
            for(int x=0;x<w2;x++)
            {
                k = x+y*w;
                s = sqrt(pFFTClass->pOutput[k].re*pFFTClass->pOutput[k].re+pFFTClass->pOutput[k].im*pFFTClass->pOutput[k].im);
                pDst[(x+w2)+(y+h2)*w] = s;
            }
        }
    	// 3 --> 2
        for(int y=0+h2;y<h;y++)
        {
            for(int x=0;x<w2;x++)
            {
                k = x+y*w;
                s = sqrt(pFFTClass->pOutput[k].re*pFFTClass->pOutput[k].re+pFFTClass->pOutput[k].im*pFFTClass->pOutput[k].im);
                pDst[(x+w2)+(y-h2)*w] = s;
            }
        }
    	// 2 --> 3
        for(int y=0;y<h2;y++)
        {
            for(int x=0+w2;x<w;x++)
            {
                k = x+y*w;
                s = sqrt(pFFTClass->pOutput[k].re*pFFTClass->pOutput[k].re+pFFTClass->pOutput[k].im*pFFTClass->pOutput[k].im);
                pDst[(x-w2)+(y+h2)*w] = s;
            }
        }
    }
    else
    {
        for(int y=0;y<h;y++)
        {
            for(int x=0;x<w;x++)
            {
                k = x+y*w;
                s = sqrt(pFFTClass->pOutput[k].re*pFFTClass->pOutput[k].re+pFFTClass->pOutput[k].im*pFFTClass->pOutput[k].im);
                pDst[k] = s;
            }
        }
    }
    if(pFFTClass)
    {
     	delete pFFTClass;
        pFFTClass = NULL;
    }
}*/
//---------------------------------------------------------------------------
/*void ac_FFT_Filter(int w,int h,ip_Byte *pSrc,ip_Byte *pMask,ip_Byte *pDst)
{
	int k,size;
    size = w*h;
    TFFTClass *pFFTClass = new TFFTClass();
    pFFTClass->ResizeBuffers(w,h);
	for(int y=0;y<h;y++)
    {
    	for(int x=0;x<w;x++)
        {
        	k = x+y*w;
			pFFTClass->pInput[k].re = pSrc[k];
			pFFTClass->pInput[k].im = 0.0;
        }
    }
	pFFTClass->FFT();

    for(int y=0;y<h;y++)
    {
        for(int x=0;x<w;x++)
        {
            k = x+y*w;
            if(!pMask[k])
            {
	            pFFTClass->pOutput[k].re = 0.0;
    	        pFFTClass->pOutput[k].im = 0.0;
            }
        }
    }

    pFFTClass->IFFT();
    for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {
			pDst[x+y*w] = pFFTClass->pInput[x+y*w].re/size;
        }
    }

    if(pFFTClass)
    {
     	delete pFFTClass;
        pFFTClass = NULL;
    }
}
//---------------------------------------------------------------------------
void ac_Log(int w,int h,ip_Byte *pSrc,ip_Byte *pMask,ip_Byte *pDst)
{
	int k;
    TFFTClass *pFFTClass = new TFFTClass();
    pFFTClass->ResizeBuffers(w,h);
	for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {                 
        	k = x+y*w;
			pFFTClass->pInput[k].re = log(1+pSrc[k]/255.0);
			pFFTClass->pInput[k].im = 0.0;
        }
    }
	pFFTClass->FFT();
    for(int y=0;y<h;y++)
    {
        for(int x=0;x<w;x++)
        {
            k = x+y*w;
            switch(pMask[k])
            {
            	case 0:
                {
		            pFFTClass->pOutput[k].re = 0.0;
		            pFFTClass->pOutput[k].im = 0.0;
                    break;
                }
            	case 255:
                {
                    break;
                }
            	default:
                {
		            pFFTClass->pOutput[k].re *= 0.55;
		            pFFTClass->pOutput[k].im *= 0.55;
                    break;
                }
            }
        }
    }

    pFFTClass->IFFT();
    double s,max,min;
    max = -1*INT_MAX;
    min = INT_MAX;
    for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {
        	k = x+y*w;
        	s = pFFTClass->pInput[k].re;
            if(s > max)	max = s;
            if(s < min)	min = s;
        }
    }
    for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {
        	k = x+y*w;
        	s = (pFFTClass->pInput[k].re-min)/(max-min);
			pDst[x+y*w] = 255.0*(exp(s)-1)/(exp(1)-1);
        }
    }
    if(pFFTClass)
    {
     	delete pFFTClass;
        pFFTClass = NULL;
    }
}*/
//---------------------------------------------------------------------------
void ac_MaxHat_Line(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int nDim)
{
	ip_Byte *pMax = new Byte[w];
	ip_Byte *pMin = new Byte[w];
    int nDim2 = nDim/2;
	int nColor;
	int nMax,nMin;
    ip_Byte nSrc;
	for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {
        	pMax[x] = 0;
        	pMin[x] = 255;
        	for(int i=-nDim2;i<=nDim2;i++)
            {
            	if(x < nDim2)
                	nColor = pSrc[0];
                else
            	if(x >= w-nDim2)
                	nColor = pSrc[w-1];
                else
        			nColor = pSrc[(x+i)+y*w];
                if(nColor > pMax[x])
                {
                 	pMax[x] = nColor;
                }
                if(nColor < pMin[x])
                {
                 	pMin[x] = nColor;
                }
            }
        }

     	for(int x=0;x<w;x++)
        {
        	nMax = 0;
        	nMin = 255;
        	for(int i=-nDim2;i<=nDim2;i++)
            {
            	if(x < nDim2)
                	nColor = pMin[0];
                else
            	if(x >= w-nDim2)
                	nColor = pMin[w-1];
                else
	        		nColor = pMin[x+i];
                if(nColor > nMax)
                {
                 	nMax = nColor;
                }

            	if(x < nDim2)
                	nColor = pMax[0];
                else
            	if(x >= w-nDim2)
                	nColor = pMax[w-1];
                else
	        		nColor = pMax[x+i];
                if(nColor < nMin)
                {
                 	nMin = nColor;
                }
            }
            nSrc = pSrc[x+y*w];
         	pDst[x+y*w] = std::max(nMin-nSrc,nSrc-nMax);
        }
    }

	for(int y=0;y<h;y++)
    {
     	for(int x=0;x<nDim;x++)
        {
         	pDst[x+y*w] = 0;
        }
     	for(int x=w-nDim;x<w;x++)
        {
         	pDst[x+y*w] = 0;
        }
    }

    if(pMax)
    {
     	delete[] pMax;
        pMax = NULL;
    }
    if(pMin)
    {
     	delete[] pMin;
        pMin = NULL;
    }
}
//---------------------------------------------------------------------------
void ac_GetHistogram(int w,int h,Byte *pSrc,int nEdge,ac_Histogram Histogram)
{
    //ZeroMemory(Histogram,256*sizeof(int));
	memset(Histogram, 0,256 * sizeof(int));
    for(int y=nEdge;y<h-nEdge;y++)
    {
        for(int x=nEdge;x<w-nEdge;x++)
        {
            Histogram[pSrc[x+y*w]]++;
        }
    }
}
//---------------------------------------------------------------------------
void ac_GetHistogram(int w,int h,Byte *pSrc,int xEdge,int yEdge,ac_Histogram Histogram)
{
    //ZeroMemory(Histogram,256*sizeof(int));
	memset(Histogram, 0,256 * sizeof(int));
    for(int y=yEdge;y<h-yEdge;y++)
    {
        for(int x=xEdge;x<w-xEdge;x++)
        {
            Histogram[pSrc[x+y*w]]++;
        }
    }
}

//---------------------------------------------------------------------------
void ac_LogHistogram(ac_Histogram hist,ac_LHistogram lhst)
{
    for(int i=0;i<256;i++)
    {
        if(hist[i] > 0)
            lhst[i] = log(hist[i]);
        else
            lhst[i] = 0.0;
    }
}
//---------------------------------------------------------------------------
ip_Byte ac_EntropyTow(ac_Histogram hst,double *lhst)
{
    int i;
    ip_Byte s;
    double Shk1=0.0,Shk2=0.0,max=-1E39;
    double Nk1=0.0,Nk2=0.0,sum=0.0;
    for(i=0;i<3;i++){
        Shk1+=hst[i]*lhst[i];
        Nk1+=hst[i];
    }
    for(i=3;i<256;i++){
        Shk2+=hst[i]*lhst[i];
        Nk2+=hst[i];
    }
    sum=-Shk1/(Nk1+0.01)-Shk2/(Nk2+0.01)+log(Nk1*Nk2+1);
    if(sum >max) {
        max=sum;
        s=1;
    }
    for(i=3;i<253;i++){
        Shk1+=hst[i]*lhst[i];
        Nk1+=hst[i];
        Shk2=Shk2-hst[i]*lhst[i];
        Nk2 =Nk2-hst[i];
        sum=-Shk1/(Nk1+0.01)-Shk2/(Nk2+0.01)+log(Nk1*Nk2+1);
        if(sum >max) {
            max=sum;
            s=i;
        }
    }
    return s;
 }
//---------------------------------------------------------------------------
ip_Byte ac_EntropyTow(ac_Histogram Histogram)
{
    ac_LHistogram LHistogram;
    ac_LogHistogram(Histogram,LHistogram);
    Byte Threshold=ac_EntropyTow(Histogram,LHistogram);
    return Threshold;
}
//---------------------------------------------------------------------------
ip_Byte ac_EntropyTow(int w,int h,ip_Byte *pSrc,int nEdge)
{
	ip_Byte nThreshold;
    ac_Histogram Histogram;
    ac_GetHistogram(w,h,pSrc,nEdge,Histogram);
    nThreshold = ac_EntropyTow(Histogram);
    return nThreshold;
}
//---------------------------------------------------------------------------
ip_Byte ac_EntropyTow(int w,int h,ip_Byte *pSrc,int xEdge,int yEdge)
{
	ip_Byte nThreshold;
    ac_Histogram Histogram;
    ac_GetHistogram(w,h,pSrc,xEdge,yEdge,Histogram);
    nThreshold = ac_EntropyTow(Histogram);
    return nThreshold;
}
//---------------------------------------------------------------------------
void ac_Monochrome(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,ip_Byte nThreshold)
{
    for(int y=0;y<h;y++)
    {
        for(int x=0;x<w;x++)
        {
        	pDst[x+y*w] = ((pSrc[x+y*w] < nThreshold)?0:255);
        }
    }
}
//---------------------------------------------------------------------------
void ac_Monochrome(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,ip_Byte nThreshold,int XEdge,int YEdge)
{
    for(int y=0;y<h;y++)
    {
        for(int x=0;x<w;x++)
        {
          if ((y<YEdge)||(y>h-YEdge)) pDst[x+y*w]=0;
          else
          {
            if((x<XEdge)||(x>w-XEdge)) pDst[x+y*w]=0;
            else
               pDst[x+y*w] = ((pSrc[x+y*w] < nThreshold)?0:255);
          }
        }
    }
}
//---------------------------------------------------------------------------
void ac_Monochrome_Entropy(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int nEdge)
{
	ip_Byte nThreshold;
    nThreshold = ac_EntropyTow(w,h,pSrc,nEdge);
    ac_Monochrome(w,h,pSrc,pDst,nThreshold);
}
//---------------------------------------------------------------------------
void ac_Monochrome_Entropy(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int xEdge,int yEdge)
{
	ip_Byte nThreshold;
    nThreshold = ac_EntropyTow(w,h,pSrc,xEdge,yEdge);

    ac_Monochrome(w,h,pSrc,pDst,nThreshold,xEdge,yEdge);
}
//---------------------------------------------------------------------------
void ac_Monochrome_Entropy(int w,int h,ip_Byte *pSrc,ip_Byte *pDst,int xEdge,int yEdge,bool white)
{
    ip_Byte nThreshold;
    nThreshold = ac_EntropyTow(w,h,pSrc,xEdge,yEdge);
    //here
        for(int y=0;y<h;y++)
    {
        for(int x=0;x<w;x++)
        {
          if ((y<yEdge)||(y>h-yEdge)) pDst[x+y*w]=0;
          else
          {
            if((x<xEdge)||(x>w-xEdge)) pDst[x+y*w]=0;
            else
              if (white)
              {
                pDst[x+y*w] = ((pSrc[x+y*w] < nThreshold)?0:255);}
              else
              {
                pDst[x+y*w] = ((pSrc[x+y*w] > nThreshold)?0:255);
              }
          }
        }
    }
}
//---------------------------------------------------------------------------

//-------------------Labeling------------------------------------------------
//---------------------------------------------------------------------------
// Normal Ordering (1)
static cv::Point T2[9]={
                        cv::Point(00,00),// 0
                        cv::Point(+1,00),// 1
                        cv::Point(+1,+1),// 2
                        cv::Point(00,+1),// 3
                        cv::Point(-1,+1),// 4
                        cv::Point(-1,00),// 5
                        cv::Point(-1,-1),// 6
                        cv::Point(00,-1),// 7
                        cv::Point(+1,-1),// 8
					};
//---------------------------------------------------------------------------
int s_nIterations = 80;
int s_nThreshold = 80;
int s_nPoints = 32;
double s_dRmin = 8;
double s_dRmax = 128;
//---------------------------------------------------------------------------
ac_Point acPoint(double x,double y)
{
	ac_Point p;
    p.x = x;
    p.y = y;
	return p;
}
//---------------------------------------------------------------------------
double ac_Distance(cv::Point &p1,cv::Point &p2)
{
 	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}
//---------------------------------------------------------------------------
double ac_Distance(ac_Point &p1,ac_Point &p2)
{
 	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}
//---------------------------------------------------------------------------
double ac_Distance(double x1,double y1,double x2,double y2)
{
 	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}
//---------------------------------------------------------------------------
int ac_FloodFill(int w,int h,Byte *pSrc,int x,int y,Byte NewColor,Byte Epsilon,int &xc,int &yc)
{
	int nRegionSize = 0;
    xc = 0;
    yc = 0;
	if(pSrc == NULL)
	{
		return nRegionSize; 
	}
    else
    if((x >= w) && (y >= h))
    {
		return nRegionSize;
    }
    Byte OldColor = pSrc[x+w*y];
    if(abs(OldColor-NewColor) <= Epsilon)
    {
        return nRegionSize;
    }
    int Px=x;
    int Py=y;
    int P0x=Px;
    int P0y=Py;
    int NewPx=Px;
    int NewPy=Py;
    int N;
    std::vector<int> Stackx;
    std::vector<int> Stacky;
    while(true)
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
            nRegionSize++;
            xc += Px;
            yc += Py;
            if( ((Px+T2[7].x>=0)&&(Px+T2[7].x<=w-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=h-1))&&
                ((Px+T2[8].x>=0)&&(Px+T2[8].x<=w-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=h-1))&&
                (abs(pSrc[(Px+T2[7].x)+(Py+T2[7].y)*w]-OldColor) > Epsilon)&&
                (abs(pSrc[(Px+T2[8].x)+(Py+T2[8].y)*w]-OldColor) <= Epsilon)
              )
            {
                Stackx.push_back(Px);
                Stacky.push_back(Py);
            }
        }
        else
        if(((Px+T2[6].x>=0)&&(Px+T2[6].x<=w-1)&&(Py+T2[6].y>=0)&&(Py+T2[6].y<=h-1))&&(abs(pSrc[(Px+T2[6].x)+(Py+T2[6].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[6].x;
            NewPy=Py+T2[6].y;
            pSrc[Px+Py*w]=NewColor;
            nRegionSize++;
            xc += Px;
            yc += Py;
            if( ((Px+T2[7].x>=0)&&(Px+T2[7].x<=w-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=h-1))&&
                ((Px+T2[8].x>=0)&&(Px+T2[8].x<=w-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=h-1))&&
                (abs(pSrc[(Px+T2[7].x)+(Py+T2[7].y)*w]-OldColor) > Epsilon)&&
                (abs(pSrc[(Px+T2[8].x)+(Py+T2[8].y)*w]-OldColor) <= Epsilon)
              )
            {
                Stackx.push_back(Px);
                Stacky.push_back(Py);
            }
        }
        else
        if(((Px+T2[7].x>=0)&&(Px+T2[7].x<=w-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=h-1))&&(abs(pSrc[(Px+T2[7].x)+(Py+T2[7].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[7].x;
            NewPy=Py+T2[7].y;
            pSrc[Px+Py*w]=NewColor;
            nRegionSize++;
            xc += Px;
            yc += Py;
        }
        else
        if(((Px+T2[8].x>=0)&&(Px+T2[8].x<=w-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=h-1))&&(abs(pSrc[(Px+T2[8].x)+(Py+T2[8].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[8].x;
            NewPy=Py+T2[8].y;
            pSrc[Px+Py*w]=NewColor;
            nRegionSize++;
            xc += Px;
            yc += Py;
        }
        else
        {
            pSrc[Px+Py*w]=NewColor;
            nRegionSize++;
            xc += Px;
            yc += Py;
        	while(true)
            {
            	if(Stackx.empty() || Stacky.empty())
                {
                	xc /= nRegionSize;
                    yc /= nRegionSize;
                	return nRegionSize;
                }
	            else
    	        {
                    P0x=Stackx[0];
                    P0y=Stacky[0];
                    Stackx.erase(Stackx.begin());
                    Stacky.erase(Stacky.begin());
                    N = 0;
                    for(int i=1;i<=8;i++)
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
int ac_FloodFill(int w,int h,Byte *pSrc,Byte *pDst,int x,int y,Byte NewSrcColor,Byte NewDstColor,Byte Epsilon,int &xc,int &yc)
{
	int nRegionSize = 0;
    xc = 0;
    yc = 0;
	if(pSrc == NULL)
	{
		return nRegionSize; 
	}
    else
    if((x >= w) && (y >= h))
    {
		return nRegionSize;
    }
    Byte OldColor = pSrc[x+w*y];
    if(abs(OldColor-NewSrcColor) <= Epsilon)
    {
        return nRegionSize;
    }
    int Px=x;
    int Py=y;
    int P0x=Px;
    int P0y=Py;
    int NewPx=Px;
    int NewPy=Py;
    int N;
    std::vector<int> Stackx;
    std::vector<int> Stacky;
    while(true)
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
            xc += Px;
            yc += Py;
            if( ((Px+T2[7].x>=0)&&(Px+T2[7].x<=w-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=h-1))&&
                ((Px+T2[8].x>=0)&&(Px+T2[8].x<=w-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=h-1))&&
                (abs(pSrc[(Px+T2[7].x)+(Py+T2[7].y)*w]-OldColor) > Epsilon)&&
                (abs(pSrc[(Px+T2[8].x)+(Py+T2[8].y)*w]-OldColor) <= Epsilon)
              )
            {
                Stackx.push_back(Px);
                Stacky.push_back(Py);
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
            xc += Px;
            yc += Py;
            if( ((Px+T2[7].x>=0)&&(Px+T2[7].x<=w-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=h-1))&&
                ((Px+T2[8].x>=0)&&(Px+T2[8].x<=w-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=h-1))&&
                (abs(pSrc[(Px+T2[7].x)+(Py+T2[7].y)*w]-OldColor) > Epsilon)&&
                (abs(pSrc[(Px+T2[8].x)+(Py+T2[8].y)*w]-OldColor) <= Epsilon)
              )
            {
                Stackx.push_back(Px);
                Stacky.push_back(Py);
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
            xc += Px;
            yc += Py;
        }
        else
        if(((Px+T2[8].x>=0)&&(Px+T2[8].x<=w-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=h-1))&&(abs(pSrc[(Px+T2[8].x)+(Py+T2[8].y)*w]-OldColor) <= Epsilon))
        {
            NewPx=Px+T2[8].x;
            NewPy=Py+T2[8].y;
            pSrc[Px+Py*w]=NewSrcColor;
            pDst[Px+Py*w]=NewDstColor;
            nRegionSize++;
            xc += Px;
            yc += Py;
        }
        else
        {
            pSrc[Px+Py*w]=NewSrcColor;
            pDst[Px+Py*w]=NewDstColor;
            nRegionSize++;
            xc += Px;
            yc += Py;
        	while(true)
            {
            	if(Stackx.empty() || Stacky.empty())
                {
                	xc /= nRegionSize;
                    yc /= nRegionSize;
                	return nRegionSize;
                }
	            else
    	        {
                    P0x=Stackx[0];
                    P0y=Stacky[0];
                    Stackx.erase(Stackx.begin());
                    Stacky.erase(Stacky.begin());
                    N = 0;
                    for(int i=1;i<=8;i++)
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
bool ac_PointInFrame(double x,double y,cv::Rect &Frame)
{
 	return ((x >= Frame.x) && (x <= (Frame.x+Frame.width)) && (y >= Frame.y) && (y <= (Frame.y+Frame.height)));
}
//---------------------------------------------------------------------------
void ac_FilterRegions(int w,int h,Byte *pSrc,Byte *pDst,cv::Rect &Frame,Byte BkIndex,int nMin,int nMax,Byte Epsilon)
{
	Byte Index;
	int nRegionSize,xc,yc;
    //FillMemory(pDst,w*h,BkIndex);
	memset(pDst, BkIndex, w*h);
	for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {
        	if(!ac_PointInFrame(x,y,Frame))	continue;
         	Index = pSrc[x+y*w];
            if(Index != BkIndex)
            {
				nRegionSize = ac_FloodFill(w,h,pSrc,x,y,Index/2,Epsilon,xc,yc);
                if((nRegionSize >= nMax) || (nRegionSize <= nMin))
                    ac_FloodFill(w,h,pSrc,x,y,BkIndex,Epsilon,xc,yc);
                else
                	ac_FloodFill(w,h,pSrc,pDst,x,y,BkIndex,Index,Epsilon,xc,yc);
            }
        }
    }
}
//---------------------------------------------------------------------------
void ac_IsolateTarget(int w,int h,Byte *pSrc,Byte *pDst,cv::Rect &Frame,Byte BkIndex,Byte Epsilon)
{
	Byte Index,NewIndex,OrgIndex;
	int nRegionSize,xc,yc,nMaxRegionSize,MaxX,MaxY;
    NewIndex = 127;
    nMaxRegionSize = -1*INT_MAX;
    //FillMemory(pDst,w*h,BkIndex);
	memset(pDst, BkIndex, w*h);
	for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {
        	if(!ac_PointInFrame(x,y,Frame))	continue;
         	Index = pSrc[x+y*w];
            if((Index != BkIndex) && (Index != NewIndex))
            {
				nRegionSize = ac_FloodFill(w,h,pSrc,x,y,NewIndex,Epsilon,xc,yc);
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
		ac_FloodFill(w,h,pSrc,pDst,MaxX,MaxY,BkIndex,OrgIndex,Epsilon,xc,yc);
    }
}
//---------------------------------------------------------------------------
void ac_RemoveBorders(int w,int h,Byte *pSrc,cv::Rect &Frame,Byte BkIndex,Byte Epsilon,int nFrame)
{
	Byte Index;
    int x,y,xc,yc;
    for(int i=0;i<nFrame;i++)
    {
        x = 0+i;
        for(y=0+i;y<h-i;y++)
        {
        	if(!ac_PointInFrame(x,y,Frame))	continue;
            Index = pSrc[x+y*w];
            if(Index != BkIndex)
            {
                ac_FloodFill(w,h,pSrc,x,y,BkIndex,Epsilon,xc,yc);
            }
        }
        x = w-1-i;
        for(y=0+i;y<h-i;y++)
        {
        	if(!ac_PointInFrame(x,y,Frame))	continue;
            Index = pSrc[x+y*w];
            if(Index != BkIndex)
            {
                ac_FloodFill(w,h,pSrc,x,y,BkIndex,Epsilon,xc,yc);
            }
        }
        y = 0+i;
        for(x=0+i;x<w-i;x++)
        {
        	if(!ac_PointInFrame(x,y,Frame))	continue;
            Index = pSrc[x+y*w];
            if(Index != BkIndex)
            {
                ac_FloodFill(w,h,pSrc,x,y,BkIndex,Epsilon,xc,yc);
            }
        }
        y = h-1-i;
        for(x=0+i;x<w-i;x++)
        {
        	if(!ac_PointInFrame(x,y,Frame))	continue;
            Index = pSrc[x+y*w];
            if(Index != BkIndex)
            {
                ac_FloodFill(w,h,pSrc,x,y,BkIndex,Epsilon,xc,yc);
            }
        }
    }
}
//---------------------------------------------------------------------------
void ac_ImageCenterMono(int w,int h,Byte *pSrc,double &x0,double &y0)
{
	Byte color;
    int nSum;
    x0 = 0;
    y0 = 0;
    nSum = 0;
	for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {
            color = pSrc[x+y*w];
            x0 += color*x;
            y0 += color*y;
            nSum += color;
        }
    }
    if(nSum > 0)
    {
	    x0 /= nSum;
    	y0 /= nSum;
    }
}
//---------------------------------------------------------------------------
void ac_MoveImage(int w,int h,Byte *pSrc,Byte *pDst,int x0,int y0,int x1,int y1)
{
	int dx = x1-x0;
    int dy = y1-y0;
    int X,Y;
	for(int y=0;y<h;y++)
    {
		for(int x=0;x<w;x++)
    	{
        	X = x-dx;
            Y = y-dy;

            if(X < 0)	continue;
            if(X >= w) continue;
            if(Y < 0) continue;
            if(Y >= h) continue;

    		pDst[x+w*y] = pSrc[X+w*Y];
        }
    }
}
//------------------------------------------------
void ac_FastGaussianWin5x5(int w,int h,Byte *pSrc,Byte *pDst,int Bx,int By)
{
    unsigned char *ptr1,*ptr2,*ptr3,*ptr4,*ptr5;
	unsigned char *ptrd;
	int x,y;
	int val1,val2,val3,val4,val5;

	int dSum;
	//border fill
	for(x=0;x<2*w+2;x++) pDst[x]=pSrc[x];
	for(x=w*(h-2)-3;x<w*h;x++) pDst[x]=pSrc[x];
	for(y=2;y<h-2;y++)
	    for(x=0;x<2;x++) {
	        pDst[y*w+x]=pSrc[y*w+x];
	        pDst[y*w+w-x-1]=pSrc[y*w+w-x-1];
	    }
    // end border
	ptr1=pSrc+(By*w+Bx);
	ptr2=ptr1+w;
	ptr3=ptr2+w;
	ptr4=ptr3+w;
	ptr5=ptr4+w;
	ptrd=pDst+(By+2)*w+Bx+2;
	for(y=0;y<h-2*By-4;y++) {
		val1=(int)ptr1[0]+(int)ptr5[0]+((int)ptr2[0]+(int)ptr4[0])*2+((int)ptr3[0])*4;
		val2=(int)ptr1[1]+(int)ptr5[1]+((int)ptr2[1]+(int)ptr4[1])*2+((int)ptr3[1])*4;
		val3=(int)ptr1[2]+(int)ptr5[2]+((int)ptr2[2]+(int)ptr4[2])*2+((int)ptr3[2])*4;
		val4=(int)ptr1[3]+(int)ptr5[3]+((int)ptr2[3]+(int)ptr4[3])*2+((int)ptr3[3])*4;
		val5=(int)ptr1[4]+(int)ptr5[4]+((int)ptr2[4]+(int)ptr4[4])*2+((int)ptr3[4])*4;
		for(x=1;x<w-2*Bx-4;x++) {
        	dSum = val1+val5+(val2+val4)*2+(val3*4);
         	ptrd[x-1] = (unsigned char)(dSum/100);
			val1=val2;
			val2=val3;
			val3=val4;
			val4=val5;
			val5=((int)ptr1[x+4]+(int)ptr5[x+4])+((int)ptr2[x+4]+(int)ptr4[x+4])*2+((int)ptr3[x+4])*4;
        }
		ptr1+=w;
		ptr2+=w;
		ptr3+=w;
		ptr4+=w;
		ptr5+=w;
		ptrd+=w;
    }
}
//---------------------------------------------------------------------------

void ac_FastGaussianWin3x3(int w,int h,Byte *pSrc,Byte *pDst,int Bx,int By)
{

    unsigned char *ptr1,*ptr2,*ptr3;
	unsigned char *ptrd;
	int x,y;
	int val1,val2,val3;

	int dSum;
	ptr1=pSrc+(By*w+Bx);
	ptr2=ptr1+w;
	ptr3=ptr2+w;
	ptrd=pDst+(By+1)*w+Bx+1;
	for(y=0;y<h-2*By-2;y++) {
		val1=(int)ptr1[0]+(int)ptr3[0]+((int)ptr2[0])*2;
		val2=(int)ptr1[1]+(int)ptr3[1]+((int)ptr2[1])*2;
		val3=(int)ptr1[2]+(int)ptr3[2]+((int)ptr2[2])*2;
		for(x=1;x<w-2*Bx-2;x++) {
        	dSum = val1+val3+val2*2;
         	ptrd[x] = (unsigned char)(dSum/16);
			val1=val2;
			val2=val3;
			val3=((int)ptr1[x+2]+(int)ptr3[x+2])+((int)ptr2[x+2])*2;
        }
		ptr1+=w;
		ptr2+=w;
		ptr3+=w;
		ptrd+=w;
    }
}

//---------------------------------------------------------------------------
void ac_Gaussian(int w,int h,Byte *pSrc,Byte *pDst,int nDim)
{
    int nDim2 = nDim/2;
    int nFilterSize = nDim*nDim;
    double *pFilter = new double[nFilterSize];
	double dSum = 0.0;
    double dCoeff;
    Byte nColor;
    double dSigma = nDim/5.0;
    for(int y=-nDim2;y<=nDim2;y++)
    {
     	for(int x=-nDim2;x<=nDim2;x++)
        {
        	dCoeff = exp(-(x*x+y*y)/(2.0*dSigma*dSigma));
        	pFilter[(x+nDim2)+(y+nDim2)*nDim] = dCoeff;
            dSum += dCoeff;
        }
    }
    for(int i=0;i<nFilterSize;i++)
    {
		pFilter[i] /= dSum;
    }

	for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {
        	dSum = 0.0;
        	for(int j=-nDim2;j<=nDim2;j++)
            {
             	for(int i=-nDim2;i<=nDim2;i++)
                {
                    if(x < nDim2)
                        nColor = pSrc[0];
                    else
                    if(x >= w-nDim2)
                        nColor = pSrc[w-1];
                    else
                    if(y < nDim2)
                        nColor = pSrc[x];
                    else
                    if(y >= h-nDim2)
                        nColor = pSrc[x+(h-1)*w];
                    else
	                	nColor = pSrc[(x+i)+(y+j)*w];
                	dSum += pFilter[(i+nDim2)+(j+nDim2)*nDim]*nColor;
                }
            }
         	pDst[x+y*w] = dSum;
        }
    }

    if(pFilter)
    {
     	delete[] pFilter;
        pFilter = NULL;
    }
}
//---------------------------------------------------------------------------
void ac_ActiveContour(int w,int h,Byte *pSrc,double &x0,double &y0,double &r,int nCount,ac_Point *pContour)
{
	if(nCount <= 2)	return;
    if(pContour == NULL)	return;
    ac_Point *pContour1 = new ac_Point[nCount];
    ac_Point *pContour2 = new ac_Point[nCount];
    ac_Point p,p0,p1,Ftens,Frig,Fext,Fc,Fg;
    Byte Src;
    int nIterations = s_nIterations;
    double dLength;
    int x,y;
    double t;
//    double dt = ac_2PI/double(nCount-1.0);
    double dt = ac_2PI/double(nCount);

    // Parameters
    double m = 40.0/16.0;
    double gamma = 100.0;
    double w1 = 100.0/32.0;
    double w2 = 2.0/128.0;
    double J = 50.0/32.0;
    Byte I0 = s_nThreshold;
    ac_Point n;

//	ac_ImageCenterMono(w,h,pSrc,x0,y0);

	p0.x = x0;
    p0.y = y0;

	// Generate initial contours
    t = 0.0;
    for(int i=0;i<nCount;i++)
    {
    	p.x = p0.x+r*cos(t);
    	p.y = p0.y+r*sin(t);

        if(p.x < 0)	p.x = 0;
        if(p.x >= w) p.x = w-1;
        if(p.y < 0) p.y = 0;
        if(p.y >= h) p.y = h-1;

		pContour1[i] = p;
		pContour2[i] = p;
        t += dt;
    }

    for(int i=0;i<nIterations;i++)
    {
    	for(int j=0;j<nCount;j++)
        {
            p1 = pContour1[(j+nCount)%nCount];

        	Ftens.x = w1*((pContour1[(j+1+nCount)%nCount].x+pContour1[(j-1+nCount)%nCount].x)/2.0-pContour1[(j+nCount)%nCount].x);
        	Ftens.y = w1*((pContour1[(j+1+nCount)%nCount].y+pContour1[(j-1+nCount)%nCount].y)/2.0-pContour1[(j+nCount)%nCount].y);

            Frig.x = w2*((pContour1[(j+2+nCount)%nCount].x+pContour1[(j-2+nCount)%nCount].x-4.0*(pContour1[(j+1+nCount)%nCount].x+pContour1[(j-1+nCount)%nCount].x))/6.0-pContour1[(j+nCount)%nCount].x);
            Frig.y = w2*((pContour1[(j+2+nCount)%nCount].y+pContour1[(j-2+nCount)%nCount].y-4.0*(pContour1[(j+1+nCount)%nCount].y+pContour1[(j-1+nCount)%nCount].y))/6.0-pContour1[(j+nCount)%nCount].y);

            dLength = ac_Distance(p0,p1);
            if(dLength <= 0.0)	continue;
//            n.x = (p0.x-p1.x)/dLength;
//            n.y = (p0.y-p1.y)/dLength;

            x = int(p1.x);
            y = int(p1.y);
/*
            if((x < 0) || (x >= w))
	            Src = 0;
			else
            if((y < 0) || (y >= h))
	            Src = 0;
			else
	            Src = pSrc[x+y*w];
*/
            if(x < 0)	x = 0;
            if(x >= w) x = w-1;
            if(y < 0) y = 0;
            if(y >= h) y = h-1;
            Src = pSrc[x+y*w];

            n.x = (p0.x-x)/dLength;
            n.y = (p0.y-y)/dLength;

            Fc.x = -J*(Src-I0)*n.x;
            Fc.y = -J*(Src-I0)*n.y;

            Fg.x = 0.0;
            Fg.y = 0.0;

            Fext.x = Fc.x+Fg.x;
            Fext.y = Fc.y+Fg.y;

			p.x = ((2.0*m)*pContour1[(j+nCount)%nCount].x-m*pContour2[(j+nCount)%nCount].x+gamma*pContour1[(j+nCount)%nCount].x+Ftens.x+Frig.x+Fext.x)/(m+gamma);
			p.y = ((2.0*m)*pContour1[(j+nCount)%nCount].y-m*pContour2[(j+nCount)%nCount].y+gamma*pContour1[(j+nCount)%nCount].y+Ftens.y+Frig.y+Fext.y)/(m+gamma);

			pContour[(j+nCount)%nCount] = p;
        }

        for(int j=0;j<nCount;j++)
        {
        	pContour2[j] = pContour1[j];
        	pContour1[j] = pContour[j];
        }
    }

    // Radius
    r = ac_ActiveContour_Radius(nCount,pContour);
	if(r < s_dRmin)	r = s_dRmin;
	if(r > s_dRmax)	r = s_dRmax;

    // Center
    ac_ActiveContour_Center(nCount,pContour,x0,y0);

    if(pContour1)
    {
     	delete[] pContour1;
        pContour1 = NULL;
    }
    if(pContour2)
    {
     	delete[] pContour2;
        pContour2 = NULL;
    }
}
//---------------------------------------------------------------------------
double ac_ActiveContour_Radius(int nCount,ac_Point *pContour)
{
	cv::Rect Frame;
    Frame = ac_ActiveContour_Frame(nCount,pContour);
	return ac_Distance(Frame.x,Frame.y,Frame.x+Frame.width,Frame.y+Frame.height) / 2.0;
}
//---------------------------------------------------------------------------
void ac_ActiveContour_Center(int nCount,ac_Point *pContour,double &x0,double &y0)
{
    x0 = 0.0;
    y0 = 0.0;
	if(nCount <= 0)	return;
	ac_Point p;
	for(int i=0;i<nCount;i++)
    {
     	p = pContour[i];
        x0 += p.x;
        y0 += p.y;
    }
    x0 /= nCount;
    y0 /= nCount;
}
//---------------------------------------------------------------------------
cv::Rect ac_ActiveContour_Frame(int nCount,ac_Point *pContour)
{
	cv::Rect Frame;
    ac_Point p;
	Frame.x = INT_MAX;
	Frame.width = -1*INT_MAX;
	Frame.y= INT_MAX;
	Frame.height = -1*INT_MAX;
	for(int i=0;i<nCount;i++)
    {
		p = pContour[i];
		if(p.x < Frame.x)	Frame.x = p.x;        	
		if(p.x > (Frame.x+Frame.width))	Frame.width = p.x-Frame.x;        	
		if(p.y < Frame.y)		Frame.y = p.y;
		if(p.y >(Frame.y + Frame.height))	Frame.height = p.y-Frame.y;
    }
    return Frame;
}
//---------------------------------------------------------------------------
void ac_Median(int w,int h,Byte *pSrc,Byte *pDst,int nDim)
{
	int nDim2 = nDim/2;
    int nSize = nDim*nDim;
    Byte *pData = new Byte[nSize];
    int k,m;
    Byte nColor,tmp;
    int ImageSize = w*h;
	for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {
        	m = 0;
        	for(int i=-nDim2;i<=nDim2;i++)
            {
            	for(int j=-nDim2;j<=nDim2;j++)
                {
                    k = (x+i)+(y+j)*w;
                    if(k < 0)
                        nColor = pSrc[0];
                    else
                    if(k > ImageSize-1)
                        nColor = pSrc[w-1];
                    else
                        nColor = pSrc[k];
                    pData[m++] = nColor;
                }
            }

            // Arrange array
            for(int j=0;j<nSize;j++)
            {
             	for(int m=j;m<nSize-1;m++)
                {
                 	if(pData[m] > pData[m+1])
                    {
                    	tmp = pData[m];
						pData[m] = pData[m+1];
						pData[m+1] = tmp;
                    }
                }
            }
            
         	pDst[x+y*w] = pData[nSize/2+1];
        }
    }
    if(pData)
    {
     	delete[] pData;
        pData = NULL;
    }
}
//---------------------------------------------------------------------------
void ac_Mean(int w,int h,Byte *pSrc,Byte *pDst,int nDim)
{
    int k,nSum1,nSum2;
    Byte nColor;
    int E = 10;
	for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {
        	nSum1 = (pSrc[(x-2)+y*w]+pSrc[(x-1)+y*w]+pSrc[(x+1)+y*w]+pSrc[(x+2)+y*w])/4.0;
            if(abs(nSum1-pSrc[x+y*w])>E)
            	pDst[x+y*w] = nSum1;
            else
	         	pDst[x+y*w] = pSrc[x+y*w];
/*
        	nSum2 = (pSrc[x+(y-2)*w]+pSrc[x+(y-1)*w]+pSrc[x+(y+1)*w]+pSrc[x+(y+2)*w])/4.0;
            if((abs(nSum1-pSrc[x+y*w])>E) || (abs(nSum2-pSrc[x+y*w])>E))
            {
            	if(abs(nSum1-pSrc[x+y*w]) > abs(nSum2-pSrc[x+y*w]))
		         	pDst[x+y*w] = nSum1;
                else
		         	pDst[x+y*w] = nSum2;
            }
            else
	         	pDst[x+y*w] = pSrc[x+y*w];
*/        
        }
    }
}
//---------------------------------------------------------------------------
void ac_ReplaceColor(int w,int h,Byte *pSrc,Byte *pDst,Byte color1,Byte color2,Byte E,Byte Edge)
{
    Byte color;
	memcpy(pDst, pSrc, w*h);
   // CopyMemory(pDst,pSrc,w*h);
	
	for(int y=Edge;y<h-Edge;y++)
    {
     	for(int x=Edge;x<w-Edge;x++)
        {
        	color = pSrc[x+y*w];
        	if(abs(color-color1) <= E)
            	pDst[x+y*w] = color2;
            else
            	pDst[x+y*w] = color;
        }
    }
}
//---------------------------------------------------------------------------
void ac_Erosion_White(int w,int h,Byte *pSrc,Byte *pDst,int nDim)
{
	int nDim2 = nDim/2;
    int k;
    Byte nColor,nMin;
    int ImageSize = w*h;
	for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {
        	nMin = 255;
        	for(int i=-nDim2;i<=nDim2;i++)
            {
            	for(int j=-nDim2;j<=nDim2;j++)
                {
                    k = (x+i)+(y+j)*w;
                    if(k < 0)
                        nColor = pSrc[0];
                    else
                    if(k > ImageSize-1)
                        nColor = pSrc[w-1];
                    else
                        nColor = pSrc[k];
                    if(nColor < nMin)
                    {
                     	nMin = nColor;
                    }
                }
            }
         	pDst[x+y*w] = nMin;
        }
    }
}
//---------------------------------------------------------------------------
void ac_Erosion_White(int w,int h,Byte *pSrc,Byte *pDst,int nDim,int xEdge,int yEdge)
{
	int nDim2 = nDim/2;
    int k;
    Byte nColor,nMin;
    int ImageSize = w*h;
	for(int y=yEdge;y<h-yEdge;y++)
    {
     	for(int x=xEdge;x<w-xEdge;x++)
        {
        	nMin = 255;
        	for(int i=-nDim2;i<=nDim2;i++)
            {
            	for(int j=-nDim2;j<=nDim2;j++)
                {
                    k = (x+i)+(y+j)*w;
                    if(k < 0)
                        nColor = pSrc[0];
                    else
                    if(k > ImageSize-1)
                        nColor = pSrc[w-1];
                    else
                        nColor = pSrc[k];
                    if(nColor < nMin)
                    {
                     	nMin = nColor;
                    }
                }
            }
         	pDst[x+y*w] = nMin;
        }
    }
}
//---------------------------------------------------------------------------
void ac_Dilation_White(int w,int h,Byte *pSrc,Byte *pDst,int nDim)
{
	int nDim2 = nDim/2;
    int k;
    Byte nColor,nMax;
    int ImageSize = w*h;
	for(int y=0;y<h;y++)
    {
     	for(int x=0;x<w;x++)
        {
        	nMax = 0;
        	for(int i=-nDim2;i<=nDim2;i++)
            {
            	for(int j=-nDim2;j<=nDim2;j++)
                {
                    k = (x+i)+(y+j)*w;
                    if(k < 0)
                        nColor = pSrc[0];
                    else
                    if(k > ImageSize-1)
                        nColor = pSrc[w-1];
                    else
                        nColor = pSrc[k];
                    if(nColor > nMax)
                    {
                     	nMax = nColor;
                    }
                }
            }
         	pDst[x+y*w] = nMax;
        }
    }
}
//---------------------------------------------------------------------------
void ac_Dilation_White(int w,int h,Byte *pSrc,Byte *pDst,int nDim,int xEdge,int yEdge)
{
	int nDim2 = nDim/2;
    int k;
    Byte nColor,nMax;
    int ImageSize = w*h;
	for(int y=yEdge;y<h-yEdge;y++)
    {
     	for(int x=xEdge;x<w-xEdge;x++)
        {
        	nMax = 0;
        	for(int i=-nDim2;i<=nDim2;i++)
            {
            	for(int j=-nDim2;j<=nDim2;j++)
                {
                    k = (x+i)+(y+j)*w;
                    if(k < 0)
                        nColor = pSrc[0];
                    else
                    if(k > ImageSize-1)
                        nColor = pSrc[w-1];
                    else
                        nColor = pSrc[k];
                    if(nColor > nMax)
                    {
                     	nMax = nColor;
                    }
                }
            }
         	pDst[x+y*w] = nMax;
        }
    }
}
//---------------------------------------------------------------------------
void ac_Opening_White(int w,int h,Byte *pSrc,int nDim)
{
	Byte *pDst = new Byte[w*h];
	ac_Erosion_White(w,h,pSrc,pDst,nDim);
	ac_Dilation_White(w,h,pDst,pSrc,nDim);
    if(pDst)
    {
     	delete[] pDst;
        pDst = NULL;
    }
}
//---------------------------------------------------------------------------
void ac_Opening_White(int w,int h,Byte *pSrc,int nDim,int xEdge,int yEdge)
{
	Byte *pDst = new Byte[w*h];
	ac_Erosion_White(w,h,pSrc,pDst,nDim,xEdge,yEdge);
	ac_Dilation_White(w,h,pDst,pSrc,nDim,xEdge,yEdge);
    if(pDst)
    {
     	delete[] pDst;
        pDst = NULL;
    }
}
//---------------------------------------------------------------------------
void ac_Closing_White(int w,int h,Byte *pSrc,int nDim)
{
	Byte *pDst = new Byte[w*h];
	ac_Dilation_White(w,h,pSrc,pDst,nDim);
	ac_Erosion_White(w,h,pDst,pSrc,nDim);
    if(pDst)
    {
     	delete[] pDst;
        pDst = NULL;
    }
}
//---------------------------------------------------------------------------
void ac_Closing_White(int w,int h,Byte *pSrc,int nDim,int xEdge,int yEdge)
{
	Byte *pDst = new Byte[w*h];
	ac_Dilation_White(w,h,pSrc,pDst,nDim,xEdge,yEdge);
	ac_Erosion_White(w,h,pDst,pSrc,nDim,xEdge,yEdge);
    if(pDst)
    {
     	delete[] pDst;
        pDst = NULL;
    }
}
//---------------------------------------------------------------------------
void MaxHatRowPyr(Byte *SRC,Byte *DST, int Width ,int Height, int FW)
{
    int j,x,y,dx=FW/2,FP,L,M;
    Byte max,min;
    Byte *TmpMin,*TmpMax,*PtrS,*PtrD;
	Byte *pyrs,*PyrMax,*PyrMin,*pyrd;
	FP=1+(FW*3)/4;
	M=Width/2;
    TmpMin=(Byte *)calloc(Width,sizeof(Byte));
    TmpMax=(Byte *)calloc(Width,sizeof(Byte));
    pyrs  =(Byte *)calloc(M    ,sizeof(Byte));
    pyrd  =(Byte *)calloc(Width,sizeof(Byte));
	L=0;
    for(y=0;y<Height;y++){
        PtrS=SRC+L;
        PtrD=DST+L;
        for(x=0;x<M;x++) {
			PtrD[x]=PtrS[x];
			PtrD[x+M]=PtrS[x+M];
			pyrs[x]=PtrS[2*x];//pyramide line
		}
        for(x=dx;x<Width-dx;x++){ //erode (min) and dilate (max) the current line
            min=255;
            max=0;
            for(j=-dx;j<=dx;j++){
                if(PtrS[x+j]<min) min=PtrS[x+j]; //erode
                if(PtrS[x+j]>max) max=PtrS[x+j]; //dilate
            }
            TmpMin[x]=min;
            TmpMax[x]=max;
        }
        for(x=FW;x<Width-FW;x++){ // dilate and erode
            min=255;
            max=0;
            for(j=-dx;j<=dx;j++){
                if(TmpMin[x+j]>max) max=TmpMin[x+j];
                if(TmpMax[x+j]<min) min=TmpMax[x+j];
            }
            if((PtrS[x]-max)>(min-PtrS[x]))
                PtrD[x]=PtrS[x]-max;
             else
                PtrD[x]=min - PtrS[x];
        }
		// Max hat on pyramided
        for(x=FP/2;x<M-FP/2;x++){ //erode (min) and dilate (max) the current line
            min=255;
            max=0;
            for(j=-FP/2;j<=FP/2;j++){
                if(pyrs[x+j]<min) min=pyrs[x+j]; //erode
                if(pyrs[x+j]>max) max=pyrs[x+j]; //dilate
            }
            TmpMin[x]=min;
            TmpMax[x]=max;
        }
        for(x=FP;x<M-FP;x++){ // dilate and erode
            min=255;
            max=0;
            for(j=-FP/2;j<=FP/2;j++){
                if(TmpMin[x+j]>max) max=TmpMin[x+j];
                if(TmpMax[x+j]<min) min=TmpMax[x+j];
            }
            if((pyrs[x]-max)>(min-pyrs[x])){
                pyrd[2*x]=pyrs[x]-max;
                pyrd[2*x+1]=pyrd[2*x];
			}
             else {
                pyrd[2*x]  =min - pyrs[x];
                pyrd[2*x+1]=pyrd[2*x];
			}
        }
        for(x=0;x<Width;x++){ 
			if(pyrd[x]>PtrD[x]) PtrD[x]=pyrd[x];
		}
        L+=Width;
    }
    free(TmpMin);
    free(TmpMax);
	free(pyrs);
	free(pyrd);
}


void ip_TopHatRow(unsigned char *SRC,unsigned char *DST, int IW ,int IH, int FW)
{
    int j,x,y,dx=(FW+1)/2;
    unsigned char *PtrS,*PtrD;
    unsigned char *tmp;
    tmp=(unsigned char *)calloc(IW,sizeof(unsigned char));
    for(y=0;y<IH;y++){
        PtrS=SRC+y*IW;
        PtrD=DST+y*IW;
        for(x=dx;x<IW-dx;x++){ //erode filter by row
            tmp[x]=PtrS[x];
            for(j=-dx;j<0;j++){
                if(PtrS[x+j]<tmp[x]) tmp[x]=PtrS[x+j];
                if(PtrS[x-j]<tmp[x]) tmp[x]=PtrS[x-j];
            }
        }
        //for(x=0;x<dx;x++){  //border fill temorary row
        //    tmp[x]=tmp[dx];
        //    tmp[IW-1-x]=tmp[IW-1-dx];
        //}
        for(x=FW-1;x<IW-FW;x++){ //dilate filter by row
            PtrD[x]=tmp[x];
            for(j=-dx;j<0;j++){
                if(tmp[x+j]>PtrD[x]) PtrD[x]=tmp[x+j];
                if(tmp[x-j]>PtrD[x]) PtrD[x]=tmp[x-j];
            }
            PtrD[x]=PtrS[x]-PtrD[x];
        }
        //for(x=0;x<FW;x++){  //border fill destination
        //    PtrD[x]=0;//PtrD[dx];
        //    PtrD[IW-1-x]=0;//PtrD[IW-1-dx];
        //}
    }
    free(tmp);
}

//---------------------------------------------------------------------------
void ip_BottomHatRow(unsigned char *SRC,unsigned char *DST, int IW ,int IH, int FW)
{
    int j,x,y,dx=FW/2;
    unsigned char *PtrS,*PtrD;
    unsigned char *tmp;
    tmp=(unsigned char *)calloc(IW,sizeof(unsigned char));
    for(y=0;y<IH;y++){
        PtrS=SRC+y*IW;
        PtrD=DST+y*IW;
        for(x=dx;x<IW-dx;x++){ //dilate filter by row
            tmp[x]=PtrS[x];
            for(j=-dx;j<0;j++){
                if(PtrS[x+j]>tmp[x]) tmp[x]=PtrS[x+j];
                if(PtrS[x-j]>tmp[x]) tmp[x]=PtrS[x-j];
            }
        }
        for(x=0;x<dx;x++){  //border fill temorary row
            tmp[x]=tmp[dx];
            tmp[IW-1-x]=tmp[IW-1-dx];
        }
        for(x=FW;x<IW-FW;x++){ //erode filter by row
            PtrD[x]=tmp[x];
            for(j=-dx;j<0;j++){
                if(tmp[x+j]<PtrD[x]) PtrD[x]=tmp[x+j];
                if(tmp[x-j]<PtrD[x]) PtrD[x]=tmp[x-j];
            }
            PtrD[x]=PtrD[x]-PtrS[x];
        }
        for(x=0;x<FW;x++){  //border fill destination
            PtrD[x]=0;//PtrD[dx];
            PtrD[IW-1-x]=0;//PtrD[IW-1-dx];
        }
    }
    free(tmp);

}

//---------------------------------------------------------------------------
void ip_TopHatRowN(unsigned char *SRC,unsigned char *DST, int IW ,int IH, int FW)
{
    int j,x,y,dx=(FW+1)/2;
    unsigned char *PtrS,*PtrD;
    unsigned char *tmp,*tmpd;
    tmp=(unsigned char *)calloc(IW,sizeof(unsigned char));
    tmpd=(unsigned char *)calloc(IW,sizeof(unsigned char));
    for(y=0;y<IH;y++){
        PtrS=SRC+y*IW;
        PtrD=DST+y*(IW-2*FW);
        for(x=dx;x<IW-dx;x++){ //erode filter by row
            tmp[x]=PtrS[x];
            for(j=-dx;j<0;j++){
                if(PtrS[x+j]<tmp[x]) tmp[x]=PtrS[x+j];
                if(PtrS[x-j]<tmp[x]) tmp[x]=PtrS[x-j];
            }
        }
        //for(x=0;x<dx;x++){  //border fill temorary row
        //    tmp[x]=tmp[dx];
        //    tmp[IW-1-x]=tmp[IW-1-dx];
        //}
        for(x=FW;x<IW-FW;x++){ //dilate filter by row
            tmpd[x]=tmp[x];
            for(j=-dx;j<0;j++){
                if(tmp[x+j]>tmpd[x]) tmpd[x]=tmp[x+j];
                if(tmp[x-j]>tmpd[x]) tmpd[x]=tmp[x-j];
            }
            PtrD[x-(FW)]=PtrS[x]-tmpd[x];
  //        PtrD[x-(FW)]=PtrS[x];
        }
        //for(x=0;x<FW;x++){  //border fill destination
        //    PtrD[x]=0;//PtrD[dx];
        //    PtrD[IW-1-x]=0;//PtrD[IW-1-dx];
        //}
    }
    free(tmp);
    free (tmpd);
}

//---------------------------------------------------------------------------
void ip_BottomHatRowN(unsigned char *SRC,unsigned char *DST, int IW ,int IH, int FW)
{
    int j,x,y,dx=FW/2;
    unsigned char *PtrS,*PtrD;
    unsigned char *tmp,*tmpd;
    tmp=(unsigned char *)calloc(IW,sizeof(unsigned char));
    tmpd=(unsigned char *)calloc(IW,sizeof(unsigned char));
    for(y=0;y<IH;y++){
        PtrS=SRC+y*IW;
        PtrD=DST+y*(IW-2*FW);
        for(x=dx;x<IW-dx;x++){ //dilate filter by row
            tmp[x]=PtrS[x];
            for(j=-dx;j<0;j++){
                if(PtrS[x+j]>tmp[x]) tmp[x]=PtrS[x+j];
                if(PtrS[x-j]>tmp[x]) tmp[x]=PtrS[x-j];
            }
        }
//        for(x=0;x<dx;x++){  //border fill temorary row
//            tmp[x]=tmp[dx];
//            tmp[IW-1-x]=tmp[IW-1-dx];
//        }
        for(x=FW;x<IW-FW;x++){ //erode filter by row
            tmpd[x]=tmp[x];
            for(j=-dx;j<0;j++){
                if(tmp[x+j]<tmpd[x]) tmpd[x]=tmp[x+j];
                if(tmp[x-j]<tmpd[x]) tmpd[x]=tmp[x-j];
            }
            PtrD[x-FW]=tmpd[x]-PtrS[x];
        }
/*        for(x=0;x<FW;x++){  //border fill destination
            PtrD[x]=0;//PtrD[dx];
            PtrD[IW-1-x]=0;//PtrD[IW-1-dx];
        }  */
    }
    free(tmp);
    free(tmpd);

}

//---------------------------------------------------------------------------
void ip_median_3x3(int W ,int H, unsigned char * in_data, unsigned char * out_data)
{
    int i,j;
    unsigned char in[9],tmp,min,max;
    unsigned char * ptr1;
    unsigned char * ptr2;
    unsigned char * ptr3;
    unsigned char * ptr;
    ptr=out_data+W+1;
    ptr1=in_data;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    for(i=0;i<H-2;i++){
        for(j=0;j<W-2;j++)	{
            in[0]=ptr1[j  ];    in[1]=ptr1[j+1];	in[2]=ptr1[j+2];
            in[3]=ptr2[j  ];	in[4]=ptr2[j+1];	in[5]=ptr2[j+2];
            in[6]=ptr3[j  ];	in[7]=ptr3[j+1];	in[8]=ptr3[j+2];
            //sort ro ws
            if(in[0]>in[1]){tmp=in[1];in[1]=in[0];in[0]=tmp;}
            if(in[1]>in[2]){tmp=in[2];in[2]=in[1];in[1]=tmp;}
            if(in[0]>in[1]){tmp=in[1];in[1]=in[0];in[0]=tmp;}

            if(in[3]>in[4]){tmp=in[4];in[4]=in[3];in[3]=tmp;}
            if(in[4]>in[5]){tmp=in[5];in[5]=in[4];in[4]=tmp;}
            if(in[3]>in[4]){tmp=in[4];in[4]=in[3];in[3]=tmp;}

            if(in[6]>in[7]){tmp=in[7];in[7]=in[6];in[6]=tmp;}
            if(in[7]>in[8]){tmp=in[8];in[8]=in[7];in[7]=tmp;}
            if(in[6]>in[7]){tmp=in[7];in[7]=in[6];in[6]=tmp;}

            max=in[0];
            if(in[3]>max){max=in[3];}
            if(in[6]>max){max=in[6];}

            if(in[1]>in[4]){tmp=in[4];in[4]=in[1];in[1]=tmp;}
            if(in[4]>in[7]){in[4]=in[7];}
            if(in[1]>in[4]){in[4]=in[1];}
            min=in[2];
            if(in[5] < min){min=in[5];}
            if(in[8] < min){min=in[8];}

            //sort
            if(max>in[4]){tmp=in[4];in[4]=max;max=tmp;}
            if(in[4]>min){tmp=min;min=in[4];in[4]=tmp;}
            if(max>in[4]){in[4]=max;}
            ptr[j]=in[4];
            //out_data[(j+1)+(i+1)*W] =in[4];
        }
        ptr+=W;
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3+=W;
    }
}
//---------------------------------------------------------------------------

void ip_FastBinDilate (int W, int H, unsigned char * src, unsigned char * dst)
{
    unsigned char *  pt0;
    unsigned char *  pt1;
    unsigned char *  pt2;
    unsigned char *  pt3;
    unsigned char *  pd1;
    unsigned char *  pd2;
    unsigned long Q0;
    unsigned long Q1;
    unsigned long Q2;
    unsigned long Q3;
    int i,j,cols;
    int l0,l1,l2,l3,l4;
    cols=W>>3;

    pt0 = src ;
    pt1 = pt0 + cols;
    pt2 = pt1 + cols;
    pt3 = pt2 + cols;
    pd1 = dst + cols;
    pd2 = pd1 + cols; 
    for (j = 0; j < H-2; j +=2) {
        for (i = 0; i < cols; i += 3) {
            l1=i+0;
            l2=i+1;
            l3=i+2;
            l4=i+3;
            Q0  = ((unsigned long)pt0[l1] << 24);
            Q0 |= ((unsigned long)pt0[l2] << 16);
            Q0 |= ((unsigned long)pt0[l3] << 8 );
            Q0 |= ((unsigned long)pt0[l4] );
            Q1  = ((unsigned long)pt1[l1] << 24);
            Q1 |= ((unsigned long)pt1[l2] << 16);
            Q1 |= ((unsigned long)pt1[l3] << 8 );
            Q1 |= ((unsigned long)pt1[l4] );
            Q2  = ((unsigned long)pt2[l1] << 24);
            Q2 |= ((unsigned long)pt2[l2] << 16);
            Q2 |= ((unsigned long)pt2[l3] << 8 );
            Q2 |= ((unsigned long)pt2[l4] );
            Q3  = ((unsigned long)pt3[l1] << 24);
            Q3 |= ((unsigned long)pt3[l2] << 16);
            Q3 |= ((unsigned long)pt3[l3] << 8 );
            Q3 |= ((unsigned long)pt3[l4] );
                                                   
            Q0 |= ((Q0 << 1) | (Q0 << 2));
            Q1 |= ((Q1 << 1) | (Q1 << 2));
            Q2 |= ((Q2 << 1) | (Q2 << 2));
            Q3 |= ((Q3 << 1) | (Q3 << 2));
            Q1 |= Q2;
            Q0 |= Q1;
            Q3 |= Q1;
                                
            pd1[l3] = (Q0 >>  8) & 0xFF;
            pd1[l2] = (Q0 >> 16) & 0xFF;
            pd1[l1] = (Q0 >> 24) & 0xFF;
            pd2[l3] = (Q3 >>  8) & 0xFF;
            pd2[l2] = (Q3 >> 16) & 0xFF;
            pd2[l1] = (Q3 >> 24) & 0xFF;
        }
        pt0=pt2;
        pt1=pt3;
        pt2=pt1+cols;
        pt3=pt2+cols;
        pd1=pd2+cols;
        pd2=pd1+cols;
    }    
} 

void ip_FastBinClose (int W, int H, unsigned char * src, unsigned char * dst)
{
    unsigned char *  pt1;
    unsigned char *  pt2;
    unsigned char *  pt3;
    unsigned char *  pt4;
    unsigned char *  pd0;
    unsigned char *  pd1;
    unsigned char *  pd2;
    unsigned char *  pd3;
    unsigned long Q0;
    unsigned long Q1;
    unsigned long Q2;
    unsigned long Q3;
    int i,j,cols;
    int l0,l1,l2,l3,l4;
    cols=W/8;

    pt1 = src+cols ;
    pt2 = pt1 + cols;
    pt3 = pt2 + cols;
    pt4 = pt3 + cols;
    pd0 = dst; 
    pd1 = pd0 + cols; 
    pd2 = pd1 + cols; 
    pd3 = pd2 + cols; 
    for (j = 0; j < H-4; j +=2) {
        //dilating the src
        for (i = 0; i < cols; i += 3) {
            l1=i+0;
            l2=i+1;
            l3=i+2;
            l4=i+3;
            Q0  = ((unsigned long)pt1[l1] << 24);
            Q0 |= ((unsigned long)pt1[l2] << 16);
            Q0 |= ((unsigned long)pt1[l3] << 8 );
            Q0 |= ((unsigned long)pt1[l4] );
            Q1  = ((unsigned long)pt2[l1] << 24);
            Q1 |= ((unsigned long)pt2[l2] << 16);
            Q1 |= ((unsigned long)pt2[l3] << 8 );
            Q1 |= ((unsigned long)pt2[l4] );
            Q2  = ((unsigned long)pt3[l1] << 24);
            Q2 |= ((unsigned long)pt3[l2] << 16);
            Q2 |= ((unsigned long)pt3[l3] << 8 );
            Q2 |= ((unsigned long)pt3[l4] );
            Q3  = ((unsigned long)pt4[l1] << 24);
            Q3 |= ((unsigned long)pt4[l2] << 16);
            Q3 |= ((unsigned long)pt4[l3] << 8 );
            Q3 |= ((unsigned long)pt4[l4] );
                                                   
            Q0 |= ((Q0 << 1) | (Q0 << 2));// Or with respect to x;
            Q1 |= ((Q1 << 1) | (Q1 << 2));
            Q2 |= ((Q2 << 1) | (Q2 << 2));
            Q3 |= ((Q3 << 1) | (Q3 << 2));
            Q1 |= Q2;  //Or with respect to y
            Q0 |= Q1;
            Q3 |= Q1;
                                
            pd2[l3] = (Q0 >>  8) & 0xFF;
            pd2[l2] = (Q0 >> 16) & 0xFF;
            pd2[l1] = (Q0 >> 24) & 0xFF;
            pd3[l3] = (Q3 >>  8) & 0xFF;
            pd3[l2] = (Q3 >> 16) & 0xFF;
            pd3[l1] = (Q3 >> 24) & 0xFF;
        }
        //eroding results
        for (i = 0; i < cols; i += 3) {
            l1=i+0;
            l2=i+1;
            l3=i+2;
            l4=i+3;
            Q0  = ((unsigned long)pt1[l1] << 24);
            Q0 |= ((unsigned long)pt1[l2] << 16);
            Q0 |= ((unsigned long)pt1[l3] << 8 );
            Q0 |= ((unsigned long)pt1[l4] );
            Q1  = ((unsigned long)pt2[l1] << 24);
            Q1 |= ((unsigned long)pt2[l2] << 16);
            Q1 |= ((unsigned long)pt2[l3] << 8 );
            Q1 |= ((unsigned long)pt2[l4] );
            Q2  = ((unsigned long)pt3[l1] << 24);
            Q2 |= ((unsigned long)pt3[l2] << 16);
            Q2 |= ((unsigned long)pt3[l3] << 8 );
            Q2 |= ((unsigned long)pt3[l4] );
            Q3  = ((unsigned long)pt4[l1] << 24);
            Q3 |= ((unsigned long)pt4[l2] << 16);
            Q3 |= ((unsigned long)pt4[l3] << 8 );
            Q3 |= ((unsigned long)pt4[l4] );
                                                   
            Q0 &= ((Q0 << 1) & (Q0 << 2));// Or with respect to x;
            Q1 &= ((Q1 << 1) & (Q1 << 2));
            Q2 &= ((Q2 << 1) & (Q2 << 2));
            Q3 &= ((Q3 << 1) & (Q3 << 2));
            Q1 &= Q2;  //Or with respect to y
            Q0 &= Q1;
            Q3 &= Q1;
                                
            pt1[l3] = (Q0 >>  8) & 0xFF;
            pt1[l2] = (Q0 >> 16) & 0xFF;
            pt1[l1] = (Q0 >> 24) & 0xFF;
            pt2[l3] = (Q3 >>  8) & 0xFF;
            pt2[l2] = (Q3 >> 16) & 0xFF;
            pt2[l1] = (Q3 >> 24) & 0xFF;
        }
        //
        pt1=pt3;
        pt2=pt4;
        pt3=pt2+cols;
        pt4=pt3+cols;
        pd0=pd2;
        pd1=pd3;
        pd2=pd1+cols;
        pd3=pd2+cols;
    }    
} 

void ip_FastBinOpen (int W, int H, unsigned char * src, unsigned char * dst)
{
    unsigned char * pt1;
    unsigned char * pt2;
    unsigned char * pt3;
    unsigned char * pt4;
    unsigned char * pd0;
    unsigned char * pd1;
    unsigned char * pd2;
    unsigned char * pd3;
    unsigned Q0;
    unsigned Q1;
    unsigned Q2;
    unsigned Q3;
    int i,j,cols;
    int l0,l1,l2,l3,l4;
    cols=W/8;

    pt1 = src+cols ;
    pt2 = pt1 + cols;
    pt3 = pt2 + cols;
    pt4 = pt3 + cols;
    pd0 = dst; 
    pd1 = pd0 + cols; 
    pd2 = pd1 + cols; 
    pd3 = pd2 + cols; 
    for (j = 0; j < H-4; j +=2) {
        //Eroding the src
        for (i = 0; i < cols; i += 3) {
            l1=i+0;
            l2=i+1;
            l3=i+2;
            l4=i+3;
            Q0  = ((unsigned )pt1[l1] << 24);
            Q0 |= ((unsigned )pt1[l2] << 16);
            Q0 |= ((unsigned )pt1[l3] << 8 );
            Q0 |= ((unsigned )pt1[l4] );
            Q1  = ((unsigned )pt2[l1] << 24);
            Q1 |= ((unsigned )pt2[l2] << 16);
            Q1 |= ((unsigned )pt2[l3] << 8 );
            Q1 |= ((unsigned )pt2[l4] );
            Q2  = ((unsigned )pt3[l1] << 24);
            Q2 |= ((unsigned )pt3[l2] << 16);
            Q2 |= ((unsigned )pt3[l3] << 8 );
            Q2 |= ((unsigned )pt3[l4] );
            Q3  = ((unsigned )pt4[l1] << 24);
            Q3 |= ((unsigned )pt4[l2] << 16);
            Q3 |= ((unsigned )pt4[l3] << 8 );
            Q3 |= ((unsigned )pt4[l4] );
                            
            Q0 &= ((Q0 << 1) & (Q0 << 2));// And with respect to x;
            Q1 &= ((Q1 << 1) & (Q1 << 2));
            Q2 &= ((Q2 << 1) & (Q2 << 2));
            Q3 &= ((Q3 << 1) & (Q3 << 2));
            Q1 &= Q2;  //And with respect to y
            Q0 &= Q1;
            Q3 &= Q1;
                                
            pd2[l3] = (Q0 >>  8) & 0xFF;
            pd2[l2] = (Q0 >> 16) & 0xFF;
            pd2[l1] = (Q0 >> 24) & 0xFF;
            pd3[l3] = (Q3 >>  8) & 0xFF;
            pd3[l2] = (Q3 >> 16) & 0xFF;
            pd3[l1] = (Q3 >> 24) & 0xFF;
        }
        //Dilating results
        for (i = 0; i < cols; i += 3) {
            l1=i+0;
            l2=i+1;
            l3=i+2;
            l4=i+3;
            Q0  = ((unsigned)pd0[l1] << 24);
            Q0 |= ((unsigned)pd0[l2] << 16);
            Q0 |= ((unsigned)pd0[l3] << 8 );
            Q0 |= ((unsigned)pd0[l4] );
            Q1  = ((unsigned)pd1[l1] << 24);
            Q1 |= ((unsigned)pd1[l2] << 16);
            Q1 |= ((unsigned)pd1[l3] << 8 );
            Q1 |= ((unsigned)pd1[l4] );
            Q2  = ((unsigned)pd2[l1] << 24);
            Q2 |= ((unsigned)pd2[l2] << 16);
            Q2 |= ((unsigned)pd2[l3] << 8 );
            Q2 |= ((unsigned)pd2[l4] );
            Q3  = ((unsigned)pd3[l1] << 24);
            Q3 |= ((unsigned)pd3[l2] << 16);
            Q3 |= ((unsigned)pd3[l3] << 8 );
            Q3 |= ((unsigned)pd3[l4] );
                                                   
            Q0 |= ((Q0 << 1) | (Q0 << 2));// Or with respect to x;
            Q1 |= ((Q1 << 1) | (Q1 << 2));
            Q2 |= ((Q2 << 1) | (Q2 << 2));
            Q3 |= ((Q3 << 1) | (Q3 << 2));
            Q1 |= Q2;  //Or with respect to y
            Q0 |= Q1;
            Q3 |= Q1;
            pt1[l3] = (Q0 >>  8) & 0xFF;
            pt1[l2] = (Q0 >> 16) & 0xFF;
            pt1[l1] = (Q0 >> 24) & 0xFF;
            pt2[l3] = (Q3 >>  8) & 0xFF;
            pt2[l2] = (Q3 >> 16) & 0xFF;
            pt2[l1] = (Q3 >> 24) & 0xFF;
        }
        //
        pt1=pt3;
        pt2=pt4;
        pt3=pt2+cols;
        pt4=pt3+cols;
        pd0=pd2;
        pd1=pd3;
        pd2=pd1+cols;
        pd3=pd2+cols;
    }    
} 

void ip_FastBinErode (int W, int H, unsigned char * src, unsigned char * dst)
{
    unsigned char *  pt0;
    unsigned char *  pt1;
    unsigned char *  pt2;
    unsigned char *  pt3;
    unsigned char *  pd1;
    unsigned char *  pd2;
    unsigned long Q0;
    unsigned long Q1;
    unsigned long Q2;
    unsigned long Q3;
    int i,j,cols;
    int l0,l1,l2,l3,l4;
    cols=W>>3;

    pt0 = src ;
    pt1 = pt0 + cols;
    pt2 = pt1 + cols;
    pt3 = pt2 + cols;
    pd1 = dst + cols; 
    pd2 = pd1 + cols; 
    for (j = 0; j < H-2; j +=2) {
        for (i = 0; i < cols; i += 3) {
            l1=i+0;
            l2=i+1;
            l3=i+2;
            l4=i+3;
            Q0  = ((unsigned long)pt0[l1] << 24);
            Q0 |= ((unsigned long)pt0[l2] << 16);
            Q0 |= ((unsigned long)pt0[l3] << 8 );
            Q0 |= ((unsigned long)pt0[l4] );
            Q1  = ((unsigned long)pt1[l1] << 24);
            Q1 |= ((unsigned long)pt1[l2] << 16);
            Q1 |= ((unsigned long)pt1[l3] << 8 );
            Q1 |= ((unsigned long)pt1[l4] );
            Q2  = ((unsigned long)pt2[l1] << 24);
            Q2 |= ((unsigned long)pt2[l2] << 16);
            Q2 |= ((unsigned long)pt2[l3] << 8 );
            Q2 |= ((unsigned long)pt2[l4] );
            Q3  = ((unsigned long)pt3[l1] << 24);
            Q3 |= ((unsigned long)pt3[l2] << 16);
            Q3 |= ((unsigned long)pt3[l3] << 8 );
            Q3 |= ((unsigned long)pt3[l4] );
                                                   
            Q0 &= ((Q0 << 1) & (Q0 << 2));//and the line before with shift (before 1st)
            Q1 &= ((Q1 << 1) & (Q1 << 2));//and first current line with shift (before 2nd)
            Q2 &= ((Q2 << 1) & (Q2 << 2));//and second current line with shift (after 1st)
            Q3 &= ((Q3 << 1) & (Q3 << 2));//and the line after 2nd with
            Q1 &= Q2; //ANDing commun lines
            Q0 &= Q1;
            Q3 &= Q1;
                                
            pd1[l3] = (Q0 >>  8) & 0xFF;
            pd1[l2] = (Q0 >> 16) & 0xFF;
            pd1[l1] = (Q0 >> 24) & 0xFF;
            pd2[l3] = (Q3 >>  8) & 0xFF;
            pd2[l2] = (Q3 >> 16) & 0xFF;
            pd2[l1] = (Q3 >> 24) & 0xFF;
        }
        pt0=pt2;
        pt1=pt3;
        pt2=pt1+cols;
        pt3=pt2+cols;
        pd1=pd2+cols;
        pd2=pd1+cols;
    }    
}      
//============================================================================
void ip_ByteToBits(int W, int H, unsigned char * src, unsigned char * dst)
{
	unsigned char * ptr0;
	unsigned char * ptr1;
	int x;
	ptr0=src;
	for(x=0;x<W*H/8;x++){
        ptr1=dst+x;
		*ptr1  =(*ptr0++)&0x80;
		*ptr1 |=(*ptr0++)&0x40;
		*ptr1 |=(*ptr0++)&0x20;
		*ptr1 |=(*ptr0++)&0x10;
		*ptr1 |=(*ptr0++)&0x08;
		*ptr1 |=(*ptr0++)&0x04;
		*ptr1 |=(*ptr0++)&0x02;
		*ptr1 |=(*ptr0++)&0x01;
	}
}
//=======================================================================
void ip_BitsToByte(int W, int H, unsigned char * src, unsigned char * dst)
{
	unsigned char * ptr0;
	int x,cols;
	unsigned char t;
    cols=W/8;
	ptr0=dst+1;
	for(x=0;x<cols*H-1;x++){
		t=src[x];
		(*ptr0++)=((t&0x80)>>7)*255;
		(*ptr0++)=((t&0x40)>>6)*255;
		(*ptr0++)=((t&0x20)>>5)*255;
		(*ptr0++)=((t&0x10)>>4)*255;
		(*ptr0++)=((t&0x08)>>3)*255;
		(*ptr0++)=((t&0x04)>>2)*255;
		(*ptr0++)=((t&0x02)>>1)*255;
		(*ptr0++)=(t&0x01)*255;
	}                   
}
//=========================================================================
void ip_KittlerAll( int W, int H,unsigned char * src, unsigned char * dst)
{
    int j,sa,i,k,l,s,N;
    float SF=0.0,MF=0.0,min;
    float SB=0.0,MB=0.0,sum=0.0;
    float ph[256],DP=0.0,tmp,tmp2,fi;
	float Eps=1.0e-7;
    N=256;
    sa=5;
    fi=1/(float)((H-2*sa)*(W-2*sa));
    memset(dst,0,W*H);
    for(i=0;i<256;i++) ph[i]=0;
    for(i=sa;i<H-sa;i++){
        for(j=sa;j<W-sa;j++) {
            ph[src[i*W+j]]+=fi;
        }
    }
    k=0;
    while(ph[k]==0) k++;
    l=N-1;
    while(ph[l]==0) l--;
    for(i=k;i<=k+2;i++){
        MF+=ph[i]*(float)i;
        DP+=ph[i];
    }
    for(i=k;i<=k+2;i++){
        tmp=((float)i-MF);
        SF+=ph[i]*tmp*tmp;
    }
    for(i=k+3;i<=l;i++){
        MB+=ph[i]*(float)i;
    }
    for(i=k+3;i<=l;i++){
        tmp=((float)i-MB);
        SB+=ph[i]*tmp*tmp;
    }
    tmp=1/(Eps+DP*DP);
    tmp2=1/((1-DP)*(1-DP));
    min=DP*log(Eps+SF*tmp)+(1-DP)*log(Eps+SB*tmp2);
    s=k+2;
    for(i=k+3;i<l;i++){
        fi=(float)i;
        MF+=ph[i]*fi;
        MB-=ph[i]*fi;
        tmp=ph[i]*(fi*fi+MF*MF+fi*(2-DP)*(fi*ph[i]-2*MF));
        SF+=tmp;
        tmp=ph[i]*(fi*(fi*ph[i]+2*MB)*(1+DP)-fi*fi-MB*MB);
        SB+=tmp;
        DP+=ph[i];
        tmp=1/(Eps+DP*DP);
        tmp2=1/(Eps+(1-DP)*(1-DP));
        sum=DP*log(Eps+SF*tmp)+(1-DP)*log(Eps+SB*tmp2);
        if(sum<min){
            min=sum;
            s=i;
        }
    }
    for(i=0;i<W*H;i++){
        if(src[i]>=s) {
            dst[i]=255;
        }
    }
}
//==================================================================
void ip_KittlerAll2( int W, int H,unsigned char * src, unsigned char * dst, int N, float *ph)
{
    int j,sa,i,k,l,s;
    float SF=0.0,MF=0.0,min;
    float SB=0.0,MB=0.0,sum=0.0;
    float DP=0.0,tmp,tmp2,fi;
    float Eps=1.0e-7;
    k=0;
    while(ph[k]==0) k++;
    l=N-1;
    while(ph[l]==0) l--;
    for(i=k;i<=k+2;i++){
        MF+=ph[i]*(float)i;
        DP+=ph[i];
    }
    for(i=k;i<=k+2;i++){
        tmp=((float)i-MF);
        SF+=ph[i]*tmp*tmp;
    }
    for(i=k+3;i<=l;i++){
        MB+=ph[i]*(float)i;
    }
    for(i=k+3;i<=l;i++){
        tmp=((float)i-MB);
        SB+=ph[i]*tmp*tmp;
    }
    tmp=1/(Eps+DP*DP);
    tmp2=1/((1-DP)*(1-DP));
    min=DP*log(Eps+SF*tmp)+(1-DP)*log(Eps+SB*tmp2);
    s=k+2;
    for(i=k+3;i<l;i++){
        fi=(float)i;
        MF+=ph[i]*fi;
        MB-=ph[i]*fi;
        tmp=ph[i]*(fi*fi+MF*MF+fi*(2-DP)*(fi*ph[i]-2*MF));
        SF+=tmp;
        tmp=ph[i]*(fi*(fi*ph[i]+2*MB)*(1+DP)-fi*fi-MB*MB);
        SB+=tmp;
        DP+=ph[i];
        tmp=1/(Eps+DP*DP);
        tmp2=1/(Eps+(1-DP)*(1-DP));
        sum=DP*log(Eps+SF*tmp)+(1-DP)*log(Eps+SB*tmp2);
        if(sum<min){
            min=sum;
            s=i;
        }
    }
    // 
	std::cout << " threshold = " << s << std::endl;
    for(i=0;i<W*H;i++){
        j=src[i];
        if(j>=s) {
            dst[i]=255;
            src[i]=0;
        }
        else {
            dst[i]=0;
            src[i]=255;
        }
    }
}

//==============================================================
void ErodeBin(unsigned char *src, unsigned char *dst,int W,int H)
{
    int x,y,i,L1,L2,K;
    unsigned char *ptr1;
    unsigned char *ptr2;
    unsigned char *ptr3;
    unsigned char *ptr4;
    unsigned char *ptrd1;
    unsigned char *ptrd2;
    ptr1=src;
    ptrd1=dst+W;
    ptrd2=ptrd1+W;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptr4=ptr3+W;
    for(y=1;y<H-3;y+=2){
        for(x=1;x<W-1;x++) {
            K=0;
            L1=0;
            L2=0;
            for(i=x-1;i<=x+1;i++) {
                K+=ptr2[i]+ptr3[i];
                L1+=ptr1[i];
                L2+=ptr4[i];
            }
            L1+=K;
            L2+=K;
            if(L1<2295) ptrd1[x]=0;
            else ptrd1[x]=255;
            if(L2<2295) ptrd2[x]=0;
            else ptrd2[x]=255;
        }
        ptr1=ptr3;
        ptr2=ptr4;
        ptr3=ptr2+W;
        ptr4=ptr3+W;
        ptrd1=ptrd2+W;
        ptrd2=ptrd1+W;
    }
} 

//==================================================================
void DilateBin(unsigned char *src, unsigned char *dst,int W,int H)
{
    int x,y,i,L1,L2,K;
    unsigned char * ptr1;
    unsigned char * ptr2;
    unsigned char * ptr3;
    unsigned char * ptr4;
    unsigned char * ptrd1;
    unsigned char * ptrd2;
    ptr1=src;
    ptrd1=dst+W;
    ptrd2=ptrd1+W;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptr4=ptr3+W;
    for(y=1;y<H-3;y+=2){
        for(x=1;x<W-1;x++) {
            K=0;
            L1=0;
            L2=0;
            for(i=x-1;i<=x+1;i++) {
                K+=ptr2[i]+ptr3[i];
                L1+=ptr1[i];
                L2+=ptr4[i];
            }
            L1+=K;
            L2+=K;
            if(L1>0) ptrd1[x]=255;
            else ptrd1[x]=0;
            if(L2>0) ptrd2[x]=255;
            else ptrd2[x]=0;
        }
        ptr1=ptr3;
        ptr2=ptr4;
        ptr3=ptr2+W;
        ptr4=ptr3+W;
        ptrd1=ptrd2+W;
        ptrd2=ptrd1+W;
    }
} 

void CloseBin(unsigned char *src, unsigned char *dst,int W,int H)
{
    int x,y,i,L1,L2,K;
    unsigned char *ptr1;
    unsigned char *ptr2;
    unsigned char *ptr3;
    unsigned char *ptr4;
    unsigned char *ptrd1;
    unsigned char *ptrd2;
    unsigned char *ptrd0; 
    unsigned char *ptrd3; 
    ptrd0=dst;
    ptrd1=ptrd0+W;
    ptrd2=ptrd1+W;
    ptrd3=ptrd2+W;
    ptr1=src+W;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptr4=ptr3+W;
    for(x=0;x<W;x++) {
        ptrd0[x]=0;
        ptrd1[x]=0;
    }
	//start dilate from line 2 (leaving 2 line without processing)
    for(y=2;y<H-3;y+=2){
        for(x=1;x<W-1;x++) {
            K=0;
            L1=0;
            L2=0;
            for(i=x-1;i<=x+1;i++) {
                K+=ptr2[i]+ptr3[i];
                L1+=ptr1[i];
                L2+=ptr4[i];
            }
            L1+=K;
            L2+=K;
            if(L1>0) ptrd2[x]=255;
            else ptrd2[x]=0;
            if(L2>0) ptrd3[x]=255;
            else ptrd3[x]=0;
        }
		//erode result
        for(x=1;x<W-1;x++) {
            K=0;
            L1=0;
            L2=0;
            for(i=x-1;i<=x+1;i++) {
                K+=ptrd1[i]+ptrd2[i];
                L1+=ptrd0[i];
                L2+=ptrd3[i];
            }
            L1+=K;
            L2+=K;
            if(L1<2295) ptr1[x]=0;
            else ptr1[x]=255;
            if(L2<2295) ptr2[x]=0;
            else ptr2[x]=255;
        }
        ptr1=ptr3;
        ptr2=ptr4;
        ptr3=ptr2+W;
        ptr4=ptr3+W;
        ptrd0=ptrd2;
        ptrd1=ptrd3;
        ptrd2=ptrd1+W;
        ptrd3=ptrd2+W;
    }
}

void OpenBin(unsigned char *src, unsigned char *dst,int W,int H)
{
    int x,y,i,L1,L2,K;
    unsigned char * ptr1;
    unsigned char * ptr2;
    unsigned char * ptr3;
    unsigned char * ptr4;
    unsigned char * ptrd1;
    unsigned char * ptrd2;
    unsigned char * ptrd0; 
    unsigned char * ptrd3; 
    ptrd0=dst;
    ptrd1=ptrd0+W;
    ptrd2=ptrd1+W;
    ptrd3=ptrd2+W;
    ptr1=src+W;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptr4=ptr3+W;
    for(x=0;x<W;x++) {
        ptrd0[x]=255;
        ptrd1[x]=255;
    }
    //start erode from line 2 (leaving 2 line without processing)
    for(y=2;y<H-3;y+=2){
        for(x=1;x<W-1;x++) {
            K=0;
            L1=0;
            L2=0;
            for(i=x-1;i<=x+1;i++) {
                K+=ptr2[i]+ptr3[i];
                L1+=ptr1[i];
                L2+=ptr4[i];
            }
            L1+=K;
            L2+=K;
            if(L1<2295) ptrd2[x]=0;
            else ptrd2[x]=255;
            if(L2<2295) ptrd3[x]=0;
            else ptrd3[x]=255;
        }
        //dilate result->src
        for(x=1;x<W-1;x++) {
            K=0;
            L1=0;
            L2=0;
            for(i=x-1;i<=x+1;i++) {
                K+=ptrd1[i]+ptrd2[i];
                L1+=ptrd0[i];
                L2+=ptrd3[i];
            }
            L1+=K;
            L2+=K;
            if(L1>0) ptr1[x]=255;
            else ptr1[x]=0;
            if(L2>0) ptr2[x]=255;
            else ptr2[x]=0;
        }
        ptr1=ptr3;
        ptr2=ptr4;
        ptr3=ptr2+W;
        ptr4=ptr3+W;
        ptrd0=ptrd2;
        ptrd1=ptrd3;
        ptrd2=ptrd1+W;
        ptrd3=ptrd2+W;
    }
}
//***************************************************************************
void FilterActiveContour(ac_Point *pContour,ac_Point *pContourOut,int NP)
{
    int i,x,y;
    float x1,x2,x3,y1,y2,y3;
    x1=(float)pContour[NP-1].x;
    y1=(float)pContour[NP-1].y;
    x2=(float)pContour[0].x;
    y2=(float)pContour[0].y;
    x3=(float)pContour[1].x;
    y3=(float)pContour[1].y;
    pContourOut[0].x=(double)Median3f(x1,x2,x3);
    pContourOut[0].y=(double)Median3f(y1,y2,y3);
    for(i=1;i<NP-1;i++) {
        x1=x2;x2=x3;x3=pContour[i+1].x;
        y1=y2;y2=y3;y3=pContour[i+1].y;
        pContourOut[i].x=(double)Median3f(x1,x2,x3);
        pContourOut[i].y=(double)Median3f(y1,y2,y3);
    }
    x1=x2;x2=x3;x3=(float)pContour[0].x;
    y1=y2;y2=y3;y3=(float)pContour[0].y;
    pContourOut[NP-1].x=(double)Median3f(x1,x2,x3);
    pContourOut[NP-1].y=(double)Median3f(y1,y2,y3);
}

//**************************************************************************
float Median3f(float x1,float x2,float x3)
{
    float V1,V2,V3;
    if(x1>x2) V1=x1;   else  V1=x2;
    if(x2>x3) V2=x2;   else  V2=x3;
    if(V1>V2) V1=V2;
    if(x3>x1) V3=x3;   else  V3=x1;
    if(V1>V3) V1=V3;

    return(V1);
}
//
double ActiveContourDistance(ac_Point *pC1,ac_Point *pC2, int NP)
{
    double f;
    double NP_1;
    int i;
    double x1,x2;
    double mx1,mx2,my1,my2;
    f=0;
    mx1=mx2=my1=my2=0;
    NP_1=1.0/(double)NP;
    //centers of contour1 and contour2;
    for(i=0;i<NP;i++){
        mx1+=pC1[i].x;
        my1+=pC1[i].y;
        mx2+=pC2[i].x;
        my2+=pC2[i].y;
    }
    mx1*=NP;
    mx2*=NP;
    my1*=NP;
    my2*=NP;
    for(i=0;i<NP;i++) {
        x1=(pC1[i].x-mx1)-(pC2[i].x-mx2);
        x2=(pC1[i].y-my1)-(pC2[i].y-my2);
        f+=(double)(x1*x1+x2*x2);
    }
    return f;
}
