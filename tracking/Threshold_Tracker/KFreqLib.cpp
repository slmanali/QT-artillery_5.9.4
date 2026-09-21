//---------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#define _TI_ENHANCED_MATH_H 1
#include <math.h>
#include "KFreqLib.h"
/*****************************************************************************/
#define _CPPBuilder_ 1

#ifdef _CPPBuilder_
	#define cossp(x)	cos(x)
	#define sinsp(x)	sin(x)
	#define rsqrtf(x)	(1.0/sqrt(x))
    #define rsqrtsp(x)	(1.0/sqrt(x))
	#define sqrtf(x)	sqrt(x)
	#define restrict
#else
	#include <fastrts67x.h>
#endif
/*****************************************************************************/
#define RayonMax 40
typedef struct tagComplex {
     float re, im;
} TComplex;

typedef struct tagSinCos {
     float cos, sin;
} TCosSin;

typedef struct tagPoint
{
	int x,y;
} TPoint;
/***************************************************************************** 
 * the next table contains the accumulated number of points off all circles  *
 * from 0 to the current one. to find number of point for circle 'r' we take *
 * CumulCirclePoints[r]-CumulCirclePoints[r-1]. circle 10 contains 304-248   *
 * =56 points and his address starts at address+CumulCirclePoints[9] (248)   *
 *****************************************************************************/
int CumulCirclePoints[RayonMax+1]=
	{0,  4,  16,  32,  52,  80, 112, 152, 196, 248, 304,
       364, 432, 504, 584, 668, 756, 852, 952,1060,1172,
      1288,1412,1540,1676,1816,1964,2116,2272,2436,2604,
      2780,2960,3144,3336,3532,3736,3944,4160,4380,4604};

/*****************************************************************************/
TCosSin *g_pCosSin;
TPoint *g_pCircles;
unsigned char *g_pRestDiv;
int s_nFirstRayon,s_nLastRayon;
int s_nIndex_fMax;
/*****************************************************************************/
int g_nFeatures = 0;
float *g_pFeatures = NULL;
TComplex *restrict Val;

void ip_InitRestDivision()
{
    unsigned char *restrict ptr;
    int rayon,N,i,NR,L;
    for(rayon=s_nFirstRayon;rayon<=s_nLastRayon;rayon++){
        N=CumulCirclePoints[rayon-1];
        L=N>>2;
        NR=L*s_nIndex_fMax;
        ptr=g_pRestDiv+NR;
        N=CumulCirclePoints[rayon]-N;
        NR=(N>>2)*s_nIndex_fMax;
        for(i=0;i<NR;i++){
            ptr[i]=(unsigned char)(i%N);
        }
    }
}

/*****************************************************************************
allocating space for all points of circles ccontour from rayon = 1 to RayonMax
*****************************************************************************/
void ip_AllocateCirclesData(int FirstRayon,int LastRayon,int Index_fMax)
{
    int ic,L;
    s_nFirstRayon = FirstRayon;
    s_nLastRayon = LastRayon;
    s_nIndex_fMax = Index_fMax;
    Val = (TComplex *)malloc(s_nIndex_fMax*sizeof(TComplex));
    
    g_nFeatures = (s_nLastRayon-s_nFirstRayon+1)*s_nIndex_fMax;
	g_pFeatures = (float *)malloc(g_nFeatures*sizeof(float));
    ic = CumulCirclePoints[LastRayon];
    L = ic>>2;
    g_pCircles = (TPoint *)malloc(ic*sizeof(TPoint ));
    g_pCosSin  = (TCosSin *)malloc(ic*sizeof(TCosSin ));
    ic=L*s_nIndex_fMax;
    g_pRestDiv  = (unsigned char *)malloc(ic*sizeof(unsigned char ));
    ip_InitializeCircles();
    ip_InitializeTCosSin();
    ip_InitRestDivision();
}
/*****************************************************************************/
void ip_DeallocateCirclesData()
{
	if(g_pFeatures) {
     	free(g_pFeatures);
    }
	free( g_pCircles);//freeing  circles points  memory
	free( g_pCosSin); //freeing the table of cos & sin
    free( g_pRestDiv);
	free(Val);    
}
/*****************************************************************************/
void ip_InitializeCircles()
{
    TPoint *restrict ptr;
    int mx,my,ray,q4;
    int CostFunc,ii,N;
    #pragma MUST_ITERATE(10);
    for(ray=s_nFirstRayon;ray<=s_nLastRayon;ray++){// loop on each circle
                                   //ray runs from First to the Last
        mx=0;my=ray;      //first point on the circle (0,r)
        CostFunc=5-4*ray; //value of the cost function
        ii=0;             //counter
        ptr=g_pCircles+CumulCirclePoints[ray-1];//where we should stock points
        while(mx<my) {  //finding the circle point of first eighth;
            ptr[ii].x=mx;   // x value of point ii
            ptr[ii].y=my;   // y value of point ii
            ii++;           // next point
            if(CostFunc<0){ // we are inside the circle
                mx++;       // go toward the out side
                CostFunc+=(8*mx+4); // updating the value of cost function
            }
            else {      // on or outside the circle (CostFunc>=0)
                mx++;   // go toward the inside
                my--;
                CostFunc+=(8*(mx-my)+8); // updating the value of cost function
            }
        }
        N=ii;
        if(mx==my){//the last point on the line y=x, we don't duplicate it;
            ptr[N].x=mx;  //stock the point on the line y=x;
            ptr[N].y=my;
            mx=N+1;
            my=N-1;
            for(ii=0;ii<N-1;ii++) {
                ptr[mx].x=ptr[my].y;
                ptr[mx].y=ptr[my].x;
                mx++;
                my--;
            }
            N+=N;
        } 
        else{   //the last point is not on the line y=x, we complete the first quadrand 
                //by symetry to y=x,from last point going back to the first.
            mx=N;
            my=N-1;
            for(ii=0;ii<N-1;ii++) {
                ptr[mx].x=ptr[my].y;
                ptr[mx].y=ptr[my].x;
                mx++;
                my--;
            }
            N+=N-1;
        }
        mx=N;
        my=mx+N;
        q4=my+N;
        for(ii=0;ii<N;ii++){ //the other three qudrand
            ptr[mx].x= ptr[ii].y; // copying first qudrand to 2nd
            ptr[mx].y=-ptr[ii].x; // by symetry regarding line y=0;
            mx++;
            ptr[my].x=-ptr[ii].x; // copying first qudrand to 3rd 
            ptr[my].y=-ptr[ii].y; // by symetry regarding line y=-x;
            my++;
            ptr[q4].x=-ptr[ii].y; // copying first qudrand to 4th 
            ptr[q4].y= ptr[ii].x; // by symetry regarding line x=0;
            q4++;
        }
    }
}                   /*  --< fin >-- */

/*****************************************************************************
 * finding cos(2*Pi*k/N) and sin(2*Pi*k/N) for N=StartN,...,EndN;            *
 *****************************************************************************/
void ip_InitializeTCosSin()
{
    float PI2;
    float AngleStep;
    float SqrtNP_1;
    float Angle;
	int rayon,NP,i;
    TCosSin *restrict ptr;
    PI2=2*3.14159265358979323846;
    #pragma MUST_ITERATE(10);
    for(rayon=s_nFirstRayon;rayon<=s_nLastRayon;rayon++){
        Angle=0.0;
        NP=CumulCirclePoints[rayon]-CumulCirclePoints[rayon-1];
        // NP = number of point on the circle which rayon='rayon'.
        ptr=g_pCosSin+CumulCirclePoints[rayon-1];
        // address where we should stock cos & sin value regarding circle 'rayon'
        AngleStep=PI2/(float)(NP);  //angular step = 2*pi/NP;
        SqrtNP_1=rsqrtsp((float)NP);//1/sqrt(NP)
        for(i=0;i<NP;i++){
			ptr[i].cos=cossp(Angle)*SqrtNP_1;// (1/sqrt(NP))cos(2*pi*i/NP), i=0 ... NP-1;
            ptr[i].sin=sinsp(Angle)*SqrtNP_1;// (1/sqrt(NP))sin(2*pi*i/NP), i=0 ... NP-1;
            Angle+=AngleStep; 
        }
    }
}                  /*  --< fin >-- */

/*****************************************************************************
 * calculate the first Index_fMax frequency of FT                            *
 *****************************************************************************/
void ip_FreqK(int W,int H,float *restrict SRC,int xc,int yc)
{
    float *restrict pf1;
    float *restrict pf2;
    float c1,c3,s1,s3,accu;
    float u1,u2,u3,u0;
	int lk,ln,rayon;
	int l0,l1,l2,l3;
    int Q1,Q2,Q3,Q4,N,NR,NF2;
    float y0,y1,y2,y3;
	int counter ,dec;
    TCosSin * restrict tab;
    TPoint * restrict index;
    TComplex *restrict pc1;
    TComplex *restrict pc2;
    unsigned char * restrict PtrRest;
    counter=0;
    dec=W*yc+xc;
    NF2=g_nFeatures>>1;
    pf1=g_pFeatures;
    pf2=g_pFeatures+NF2;
    #pragma MUST_ITERATE(10);
	for(lk=0;lk<NF2;lk++){ //reset of features values
		*pf1=0;        // by group of 4
		*pf2=0;        // for tms optimization purpose
        pf1++;
        pf2++;
	}
    NF2=s_nIndex_fMax>>1;
    #pragma MUST_ITERATE(10);
    for(rayon=s_nFirstRayon;rayon<=s_nLastRayon;rayon++){
        l0=CumulCirclePoints[rayon-1];//
        NR=(l0>>2)*s_nIndex_fMax;
        tab   = g_pCosSin+l0;   // address of cos & sin value for the circle 'rayon'
        index = g_pCircles+l0;  // address of index x & y of the circle 'rayon'
        PtrRest=g_pRestDiv+NR;
        N=CumulCirclePoints[rayon]-l0; // number of point on circle 'rayon'
        pc1=Val;
        pc2=Val+NF2;
        #pragma MUST_ITERATE(4);
        for(lk=0;lk<NF2;lk++){ //reset of features values accumulators
            pc1->re=0;
            pc1->im=0;
            pc2->re=0;
            pc2->im=0;
            pc1++;
            pc2++;
        } 
        Q1=N>>2;     // we have always N=4*P (no need to deal with other values
        #pragma MUST_ITERATE(4);
        for(ln=0;ln<Q1;ln++){ // finding features of circle 'rayon'
             // by accumulating values of all features at the same time.
            Q2=Q1+ln;
            Q3=Q2+Q1;
            Q4=Q3+Q1;
            l0=(index[ln].y)*W+index[ln].x+dec;
            l1=(index[Q2].y)*W+index[Q2].x+dec;
            l2=(index[Q3].y)*W+index[Q3].x+dec;
            l3=(index[Q4].y)*W+index[Q4].x+dec;
            y0=SRC[l0];
            y1=SRC[l1];
            y2=SRC[l2];
            y3=SRC[l3];
            u0=(y0+y1+y2+y3);
            u1=(y3-y1);
            u2=(y0+y2-y1-y3);
            u3=(y2-y0);
            #pragma MUST_ITERATE(2);
            for(lk=0;lk<s_nIndex_fMax;lk+=4){ // we should choose s_nIndex_fMax=4*P (P integer)
                l0=(lk*ln);       // exp(j*(2*pi+x))=exp(j*x);
                l1=l0+ln;
                l2=l1+ln;
                l3=l2+ln;;
                l0=(int)PtrRest[l0];
                l1=(int)PtrRest[l1];
                l2=(int)PtrRest[l2];
                l3=(int)PtrRest[l3];
                c1=tab[l1].cos;
                c3=tab[l3].cos;
                s1=tab[l1].sin;
                s3=tab[l3].sin;
                Val[lk].re+=u0*tab[l0].cos; // feature of index 4*i;
                Val[lk].im-=u0*tab[l0].sin; //
                Val[lk+1].re+=u1*s1-u3*c1;// feature of 
                Val[lk+1].im+=u1*c1+u3*s1;//index 4*i+1;
                Val[lk+2].re+=u2*tab[l2].cos;    // feature of 
                Val[lk+2].im-=u2*tab[l2].sin;    //index 4*i+2;
                Val[lk+3].re-=u3*c3+u1*s3;  // feature of 
                Val[lk+3].im+=u3*s3-u1*c3;  //index 4*i+3;
            }    // --<==* end for(k=...) features loop  *==>--                       
        } // --<==* end for(n=...) point of the circle loop *==>--
        accu=0.001; //normalizing features by dividing then on the total of their energy
        pf1=g_pFeatures+counter;
        pf2=pf1+NF2;
        pc1=Val;
        pc2=pc1+NF2;
        #pragma MUST_ITERATE(2);
        for(lk=0;lk<NF2;lk+=2) {   //counter run from first rayon to
            l1=lk+1;               // the last by step of s_nIndex_fMax
            pf1[lk]=fabs(pc1[lk].re)+fabs(pc1[lk].im);
            pf2[lk]=fabs(pc2[lk].re)+fabs(pc2[lk].im);
            pf1[l1]=fabs(pc1[l1].re)+fabs(pc1[l1].im);
            pf2[l1]=fabs(pc2[l1].re)+fabs(pc2[l1].im);
            accu+=pf1[lk]*pf1[lk]+pf1[l1]*pf1[l1];
            accu+=pf2[lk]*pf2[lk]+pf2[l1]*pf2[l1];
            //accu+=;
            //accu+=;
        } // accu contains the sum of squres of all features regarding the circle 'rayon'
	    accu=rsqrtsp(accu);
        #pragma MUST_ITERATE(2);
	    for(lk=0;lk<NF2;lk+=2) {
	        pf1[lk]*=accu;      // normalizing all features
	        pf1[lk+1]*=accu;    // f_i=f_i/sqrt(sum(f_i*f_i))
	        pf2[lk]*=accu;    // i run from 0 to s_nIndex_fMax for each circle
	        pf2[lk+1]*=accu;    //  independement from other circles
	    }
/*
		// Weighting Frequencies Components
        pf1[0]*=0.02;
        for(lk=1;lk<s_nIndex_fMax;lk++)
        	pf1[lk]*=0.14;
*/
        counter+=s_nIndex_fMax;//incrementing counter by the number of features
    }
}    /*  ---< fin >---   */
/*****************************************************************************/



