#include <string.h>
#include <memory.h>
#include <math.h>

//-----------------------------------------------------------------------------
void  EntropyTow(unsigned char * src, unsigned char * dst, int W, int H)
{
    int i,j,s,sa,N;
    float Shk1=0.0,Shk2=0.0,max=-1E39;
    float Nk1=0.0,Nk2=0.0,sum=0.0;
    int hist[256];
    unsigned char *ptr;
    float lhist[256];
    N=256;
    //finding histogram
    sa=5;
    memset(dst,0,W*H);
    for(i=0;i<N;i++)
        hist[i]=0;
    ptr=src+sa*W+sa;
    for(i=sa;i<H-sa;i++) {
        for(j=0;j<W-2*sa;j++) {
            hist[ptr[j]]++;
        }
        ptr+=W;
    }
    //log hitrogram
    for(i=0;i<N;i++) {
        if(hist[i] > 0)
            lhist[i] = log((float)hist[i]);
        else
            lhist[i] = 0.0;
    }

    for(i=0;i<3;i++) {
        Shk1+=hist[i]*lhist[i];
        Nk1+=hist[i];
    }
    for(i=3;i<N;i++) {
        Shk2+=hist[i]*lhist[i];
        Nk2+=hist[i];
    }
    sum=-Shk1/(Nk1+0.000001)-Shk2/(Nk2+0.000001)+log(Nk1*Nk2+0.000001);
    if(sum >max) {
        max=sum;
        s=1;
    }
    for(i=3;i<N-3;i++) {
        Shk1+=hist[i]*lhist[i];
        Nk1+=hist[i];
        Shk2=Shk2-hist[i]*lhist[i];
        Nk2 =Nk2-hist[i];
        sum=-Shk1/(Nk1+0.01)-Shk2/(Nk2+0.01)+log(Nk1*Nk2+1);
        if(sum >max) {
            max=sum;
            s=i;
        }
    }
    for(i=0;i<W*H;i++) {
        if(src[i]>s)
            dst[i]=255;
    }
}

//-----------------------------------------------------------------------------
void KittlerAll(unsigned char * src, unsigned char * dst, int W, int H)
{
    int j,sa,i,k,l,s,N;
    float SF=0.0,MF=0.0,min;
    float SB=0.0,MB=0.0,sum=0.0;
    float DP=0.0,tmp,tmp2,fi;
    float ph[256],Eps=1.0e-9;
    N=256;
    sa=5;
    fi=1/(float)((H-2*sa)*(W-2*sa));
    memset(dst,0,W*H);
    for(i=0;i<256;i++)
        ph[i]=0;
    for(i=sa;i<H-sa;i++) {
        for(j=sa;j<W-sa;j++) {
            ph[src[i*W+j]]+=fi;
        }
    }

    k=0;
    while(ph[k]==0)
        k++;
    l=N-1;
    while(ph[l]==0)
        l--;
    for(i=k;i<=k+2;i++) {
        MF+=ph[i]*(float)i;
        DP+=ph[i];
    }
    for(i=k;i<=k+2;i++) {
        tmp=((float)i-MF);
        SF+=ph[i]*tmp*tmp;
    }
    for(i=k+3;i<=l;i++) {
        MB+=ph[i]*(float)i;
    }
    for(i=k+3;i<=l;i++) {
        tmp=((float)i-MB);
        SB+=ph[i]*tmp*tmp;
    }
    tmp=1/(DP*DP);
    tmp2=1/((1-DP)*(1-DP));
    min=DP*log(SF*tmp+Eps)+(1-DP)*log(SB*tmp2+Eps);
    s=k+2;
    for(i=k+3;i<l;i++) {
        fi=(float)i;
        MF+=ph[i]*fi;
        MB-=ph[i]*fi;
        tmp=ph[i]*(fi*fi+MF*MF+fi*(2-DP)*(fi*ph[i]-2*MF));
        SF+=tmp;
        tmp=ph[i]*(fi*(fi*ph[i]+2*MB)*(1+DP)-fi*fi-MB*MB);
        SB+=tmp;
        DP+=ph[i];
        tmp=1/(DP*DP);
        tmp2=1/((1-DP)*(1-DP));
        sum=DP*log(SF*tmp+Eps)+(1-DP)*log(SB*tmp2+Eps);
        if(sum<min) {
            min=sum;
            s=i;
        }
    }
    for(i=0;i<W*H;i++) {
        if(src[i]>s) {
            dst[i]=255;
        }
    }
}

void KittlerAll128(unsigned char * src, unsigned char * dst, int W, int H)
{
    int j,sa,i,k,l,s,N;
	float z;
    float D1,D2,min;
    float MC1,MC2,sum;
    float VC1,VC2,fi;
    float S1,S2;
    float ph[256],Eps=1.0e-9;
    unsigned char *ptr1,*ptr2,*ptr3,*ptr4;
    N=256;
    sa=8;
    fi=1/(float)((H-2*sa)*(W-2*sa));
    memset(dst,0,W*H);
    for(i=0;i<N;i++) ph[i]=0;
    ptr1=src+sa*W+sa;
    l=((H-2*sa)>>2);
    ptr2=ptr1+l*W;
    ptr3=ptr2+l*W;
    ptr4=ptr3+l*W;
    for(i=0;i<l;i++){
        for(j=0;j<W-2*sa;j++) {
			l=ptr1[j];
            ph[l]+=fi;
			l=ptr2[j];
            ph[l]+=fi;
			l=ptr3[j];
            ph[l]+=fi;
			l=ptr4[j];
            ph[l]+=fi;
        }
        ptr1+=W;
        ptr2+=W;
        ptr3+=W;
        ptr4+=W;
    }
    k=0;
    while(ph[k]==0) k++;
    l=N-1;
    while(ph[l]==0) l--;
    D1=0;MC1=0;VC1=0;
    for(i=k;i<=k+2;i++){
        D1 +=ph[i];
        MC1+=ph[i]*(float)i;
        VC1+=ph[i]*(float)(i*i);
    }
    S1=(D1-2)*MC1*MC1+VC1;
    MC2=0;VC2=0;
    D2=0;
    for(i=k+3;i<=l;i++){
        D2 +=ph[i];
        MC2+=ph[i]*(float)i;
        VC2+=ph[i]*(float)(i*i);
    }
    S2=(D2-2)*MC2*MC2+VC2;
    min=0.5*(D1*log(S1+Eps)+D2*log(S2+Eps));
    min-=D1*log(D1+Eps)+D2*log(D2+Eps);
    s=k+2;
    for(i=k+3;i<l-1;i++){
        z=ph[i];
        D1+=z;
        D2-=z;
        z*=(float)i;
        MC1+=z;
        MC2-=z;
        z*=(float)i;
        VC1+=z;
        VC2-=z;
        S1=(D1-2)*MC1*MC1+VC1;
        S2=(D2-2)*MC2*MC2+VC2;
        sum=0.5*(D1*log(S1+Eps)+D2*log(S2+Eps));
        sum-=(D1*log(D1+Eps)+D2*log(D2+Eps));
        if(sum<min){
            min=sum;
            s=i;
        }
    }
    //s*=2;
    for(i=0;i<W*H;i++){
        if(src[i]>s) {
            dst[i]=255;
        }
    }
}

void OtsuBlack(unsigned char * src, unsigned char * dst, int W, int H)
{
    int j,sa,i,k,l,s,N;
	float z;
    float D1,D2,min;
    float MC1,MC2,sum;
    float VC1,VC2,fi;
    float S1,S2;
    float ph[256];
    unsigned char *ptr1,*ptr2,*ptr3,*ptr4,th;
    N=256;
    sa=8;
    fi=1/(float)((H-2*sa)*(W-2*sa));
    memset(dst,0,W*H);
    for(i=0;i<N;i++) ph[i]=0;
//    for(i=0;i<W*H;i++){
//        ph[src[i]]+=fi;
//    }
    ptr1=src+sa*W+sa;
    l=((H-2*sa)>>2);
    ptr2=ptr1+l*W;
    ptr3=ptr2+l*W;
    ptr4=ptr3+l*W;
    for(i=0;i<l;i++){
        for(j=0;j<W-2*sa;j++) {
			l=ptr1[j];
            ph[l]+=fi;
			l=ptr2[j];
            ph[l]+=fi;
			l=ptr3[j];
            ph[l]+=fi;
			l=ptr4[j];
            ph[l]+=fi;
        }
        ptr1+=W;
        ptr2+=W;
        ptr3+=W;
        ptr4+=W;
    }
    k=0;
    while(ph[k]==0) k++;
    l=N-1;
    while(ph[l]==0) l--;
    D1=0;MC1=0;VC1=0;
    for(i=k;i<=k+2;i++){
        D1 +=ph[i];
        MC1+=ph[i]*(float)i;
        VC1+=ph[i]*(float)(i*i);
    }
    S1=(D1-2)*MC1*MC1+VC1;
    D2=0;MC2=0;VC2=0;
    for(i=k+3;i<=l;i++){
        D2 +=ph[i];
        MC2+=ph[i]*(float)i;
        VC2+=ph[i]*(float)(i*i);
    }
    S2=(D2-2)*MC2*MC2+VC2;
    z=D1*S1+D2*S2;
    z=1/(z+0.00000001);
    min=z*(D1*D2*MC2*MC2);
    s=k+2;
    for(i=k+3;i<l-1;i++){
        z=ph[i];
        D1+=z;
        D2-=z;
        z*=(float)i;
        MC1+=z;
        MC2-=z;
        z*=(float)i;
        VC1+=z;
        VC2-=z;
        S1=(D1-2)*MC1*MC1+VC1;
        S2=(D2-2)*MC2*MC2+VC2;
        z=D1*S1+D2*S2;
        z=1/z;
        sum=z*(D1*D2*MC2*MC2);
        if(sum>min){
            min=sum;
            s=i;
        }
    }
	th=(unsigned char)s;
    for(i=0;i<W*H;i++){
        if(src[i]>th) {
            dst[i]=255;
        }
    }
}

void OtsuWhite(unsigned char * src, unsigned char * dst, int W, int H)
{
    int j,sa,i,k,l,s,N;
	float z;
    float D1,D2,min;
    float MC1,MC2,sum;
    float VC1,VC2,fi;
    float S1,S2;
    float ph[256];
    unsigned char *ptr1,*ptr2,*ptr3,*ptr4,th;
    N=256;
    sa=8;
    fi=1/(float)((H-2*sa)*(W-2*sa));
    memset(dst,0,W*H);
    for(i=0;i<N;i++) ph[i]=0;
//    for(i=0;i<W*H;i++){
//        ph[src[i]]+=fi;
//    }
    ptr1=src+sa*W+sa;
    l=((H-2*sa)>>2);
    ptr2=ptr1+l*W;
    ptr3=ptr2+l*W;
    ptr4=ptr3+l*W;
    for(i=0;i<l;i++){
        for(j=0;j<W-2*sa;j++) {
			l=ptr1[j];
            ph[l]+=fi;
			l=ptr2[j];
            ph[l]+=fi;
			l=ptr3[j];
            ph[l]+=fi;
			l=ptr4[j];
            ph[l]+=fi;
        }
        ptr1+=W;
        ptr2+=W;
        ptr3+=W;
        ptr4+=W;
    }
    k=0;
    while(ph[k]==0) k++;
    l=N-1;
    while(ph[l]==0) l--;
    D1=0;MC1=0;VC1=0;
    for(i=k;i<=k+2;i++){
        D1 +=ph[i];
        MC1+=ph[i]*(float)i;
        VC1+=ph[i]*(float)(i*i);
    }
    S1=(D1-2)*MC1*MC1+VC1;
    D2=0;MC2=0;VC2=0;
    for(i=k+3;i<=l;i++){
        D2 +=ph[i];
        MC2+=ph[i]*(float)i;
        VC2+=ph[i]*(float)(i*i);
    }
    S2=(D2-2)*MC2*MC2+VC2;
    z=D1*S1+D2*S2;
    z=1/(z+0.0000001);
    min=z*(D1*D2*MC1*MC1);
    s=k+2;
    for(i=k+3;i<l-1;i++){
        z=ph[i];
        D1+=z;
        D2-=z;
        z*=(float)i;
        MC1+=z;
        MC2-=z;
        z*=(float)i;
        VC1+=z;
        VC2-=z;
        S1=(D1-2)*MC1*MC1+VC1;
        S2=(D2-2)*MC2*MC2+VC2;
        z=D1*S1+D2*S2;
        z=1/z;
        sum=z*(D1*D2*MC1*MC1);
        if(sum>min){
            min=sum;
            s=i;
        }
    }
	th=(unsigned char)s;
    for(i=0;i<W*H;i++){
        if(src[i]>th) {
            dst[i]=255;
        }
    }
}

void OtsuTest(unsigned char * src, unsigned char * dst, int W, int H)
{
    int j,sa,i,k,l,s,N;
	float z,v;
    float D1,D2,min;
    float MC1,MC2,sum;
    float VC1,VC2,fi;
    float S1,S2;
    float ph[256];
    unsigned char *ptr1,*ptr2,*ptr3,*ptr4,th;
    N=256;
    sa=8;
    fi=1/(float)((H-2*sa)*(W-2*sa));
    memset(dst,0,W*H);
    for(i=0;i<N;i++) ph[i]=0;
//    for(i=0;i<W*H;i++){
//        ph[src[i]]+=fi;
//    }
    ptr1=src+sa*W+sa;
    l=((H-2*sa)>>2);
    ptr2=ptr1+l*W;
    ptr3=ptr2+l*W;
    ptr4=ptr3+l*W;
    for(i=0;i<l;i++){
        for(j=0;j<W-2*sa;j++) {
			l=ptr1[j];
            ph[l]+=fi;
			l=ptr2[j];
            ph[l]+=fi;
			l=ptr3[j];
            ph[l]+=fi;
			l=ptr4[j];
            ph[l]+=fi;
        }
        ptr1+=W;
        ptr2+=W;
        ptr3+=W;
        ptr4+=W;
    }
    k=0;
    while(ph[k]==0) k++;
    l=N-1;
    while(ph[l]==0) l--;
    D1=0;MC1=0;VC1=0;
    for(i=k;i<=k+2;i++){
        D1 +=ph[i];
        MC1+=ph[i]*(float)i;
        VC1+=ph[i]*(float)(i*i);
    }
    D2=0;MC2=0;VC2=0;
    for(i=k+3;i<=l;i++){
        D2 +=ph[i];
        MC2+=ph[i]*(float)i;
        VC2+=ph[i]*(float)(i*i);
    }
    S1=(D1-2)*MC1*MC1+VC1;
    S2=(D2-2)*MC2*MC2+VC2;
    z=D1*S1+D2*S2;
    z=1/(z+0.000001);
    v=MC1-MC2;
    min=z*(D1*D2*v*v);
    s=k+2;
    for(i=k+3;i<l-1;i++){
        z=ph[i];
        D1+=z;
        D2-=z;
        z*=(float)i;
        MC1+=z;
        MC2-=z;
        z*=(float)i;
        VC1+=z;
        VC2-=z;
        S1=(D1-2)*MC1*MC1+VC1;
        S2=(D2-2)*MC2*MC2+VC2;
        z=D1*S1+D2*S2;
        z=1/(z+0.000001);
        v=MC1-MC2;
        sum=z*(D1*D2*v*v);
        if(sum>min){
            min=sum;
            s=i;
        }
    }
	th=(unsigned char)s;
    for(i=0;i<W*H;i++){
        if(src[i]>th) {
            dst[i]=255;
        }
    }
}


