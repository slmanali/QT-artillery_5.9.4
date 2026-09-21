#include <string.h>
#include <memory.h>
#include <math.h>

//-----------------------------------------------------------------------------
void FastBinErode3x3(unsigned char *src, unsigned char *dst,int W,int H)
{
    int x,y,i,K1,K2,K3;
    unsigned char * ptr1;
    unsigned char * ptr2;
    unsigned char * ptr3;
    unsigned char * ptrd;
    ptr1=src;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptrd=dst+W+1;
    for(y=1;y<H-1;y++) {
        K1=ptr1[0]+ptr2[0]+ptr3[0];
        K2=ptr1[1]+ptr2[1]+ptr3[1];
        K3=ptr1[2]+ptr2[2]+ptr3[2];
        if((K1+K2+K3)<2295)
            ptrd[0]=0;
        else
            ptrd[0]=255;
        for(x=1;x<W-1;x++) {
            K1=K2;
            K2=K3;
            K3=ptr1[x+2]+ptr2[x+2]+ptr3[x+2];
            if((K1+K2+K3)<2295)
                ptrd[x]=0;
            else
                ptrd[x]=255;
        }
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3=ptr3+W;
        ptrd=ptrd+W;
    }
}

//-----------------------------------------------------------------------------
void FastBinDilate3x3(unsigned char *src, unsigned char *dst,int W,int H)
{
    int x,y,i,K1,K2,K3;
    unsigned char * ptr1;
    unsigned char * ptr2;
    unsigned char * ptr3;
    unsigned char * ptrd;
    ptr1=src;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptrd=dst+W+1;
    for(y=1;y<H-1;y++) {
        K1=ptr1[0]+ptr2[0]+ptr3[0];
        K2=ptr1[1]+ptr2[1]+ptr3[1];
        K3=ptr1[2]+ptr2[2]+ptr3[2];
        if((K1+K2+K3)>0)
            ptrd[0]=255;
        else
            ptrd[0]=0;
        for(x=1;x<W-1;x++) {
            K1=K2;
            K2=K3;
            K3=ptr1[x+2]+ptr2[x+2]+ptr3[x+2];
            if((K1+K2+K3)>0)
                ptrd[x]=255;
            else
                ptrd[x]=0;
        }
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3=ptr3+W;
        ptrd=ptrd+W;
    }
}

//-----------------------------------------------------------------------------
void FastBinOpen3x3(unsigned char *src, unsigned char *dst,int W,int H)
{
    int x,y,i,K1,K2,K3;
    unsigned char * ptr1;
    unsigned char * ptr2;
    unsigned char * ptr3;
    unsigned char * ptrd;
    ptr1=src;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptrd=dst+W+1;
    for(y=1;y<H-1;y++) {
        K1=ptr1[0]+ptr2[0]+ptr3[0];
        K2=ptr1[1]+ptr2[1]+ptr3[1];
        K3=ptr1[2]+ptr2[2]+ptr3[2];
        if((K1+K2+K3)<2295)
            ptrd[0]=0;
        else
            ptrd[0]=255;
        for(x=1;x<W-1;x++) {
            K1=K2;
            K2=K3;
            K3=ptr1[x+2]+ptr2[x+2]+ptr3[x+2];
            if((K1+K2+K3)<2295)
                ptrd[x]=0;
            else
                ptrd[x]=255;
        }
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3=ptr3+W;
        ptrd=ptrd+W;
    }
    ptr1=dst;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptrd=src+W+1;
    for(y=1;y<H-1;y++) {
        K1=ptr1[0]+ptr2[0]+ptr3[0];
        K2=ptr1[1]+ptr2[1]+ptr3[1];
        K3=ptr1[2]+ptr2[2]+ptr3[2];
        if((K1+K2+K3)>0)
            ptrd[0]=255;
        else
            ptrd[0]=0;
        for(x=1;x<W-2;x++) {
            K1=K2;
            K2=K3;
            K3=ptr1[x+2]+ptr2[x+2]+ptr3[x+2];
            if((K1+K2+K3)>0)
                ptrd[x]=255;
            else
                ptrd[x]=0;
        }
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3=ptr3+W;
        ptrd=ptrd+W;
    }
}

//-----------------------------------------------------------------------------
void FastBinClose3x3(unsigned char *src, unsigned char *dst,int W,int H)
{
    int x,y,i,K1,K2,K3;
    unsigned char * ptr1;
    unsigned char * ptr2;
    unsigned char * ptr3;
    unsigned char * ptrd;
    ptr1=src;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptrd=dst+W+1;
    for(y=1;y<H-1;y++) {
        K1=ptr1[0]+ptr2[0]+ptr3[0];
        K2=ptr1[1]+ptr2[1]+ptr3[1];
        K3=ptr1[2]+ptr2[2]+ptr3[2];
        if((K1+K2+K3)>0)
            ptrd[0]=255;
        else
            ptrd[0]=0;
        for(x=1;x<W-1;x++) {
            K1=K2;
            K2=K3;
            K3=ptr1[x+2]+ptr2[x+2]+ptr3[x+2];
            if((K1+K2+K3)>0)
                ptrd[x]=255;
            else
                ptrd[x]=0;
        }
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3=ptr3+W;
        ptrd=ptrd+W;
    }
    ptr1=dst;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptrd=src+W+1;
    for(y=1;y<H-1;y++) {
        K1=ptr1[0]+ptr2[0]+ptr3[0];
        K2=ptr1[1]+ptr2[1]+ptr3[1];
        K3=ptr1[2]+ptr2[2]+ptr3[2];
        if((K1+K2+K3)<2295)
            ptrd[0]=0;
        else
            ptrd[0]=255;
        for(x=1;x<W-2;x++) {
            K1=K2;
            K2=K3;
            K3=ptr1[x+2]+ptr2[x+2]+ptr3[x+2];
            if((K1+K2+K3)<2295)
                ptrd[x]=0;
            else
                ptrd[x]=255;
        }
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3=ptr3+W;
        ptrd=ptrd+W;
    }
}

//-----------------------------------------------------------------------------
void FastBinClose (unsigned char * src,  unsigned char  * dst, int W,int H)
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

            Q0 &= ((Q0 << 1) & (Q0 << 2));// And with respect to x;
            Q1 &= ((Q1 << 1) & (Q1 << 2));
            Q2 &= ((Q2 << 1) & (Q2 << 2));
            Q3 &= ((Q3 << 1) & (Q3 << 2));
            Q1 &= Q2;  //And with respect to y
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

//-----------------------------------------------------------------------------
void FastBinOpen (unsigned char * src,  unsigned char  * dst, int W,int H)
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

//-----------------------------------------------------------------------------
void ByteToBits(unsigned char * src,unsigned char * dst,int W,int H)
{
    unsigned char * ptr0;
    unsigned char * ptr1;
    int x;
    ptr0=src;
    for(x=0;x<W*H/8;x++) {
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

//-----------------------------------------------------------------------------
void BitsToByte(unsigned char * src,unsigned char * dst,int W,int H)
{
    unsigned char * ptr0;
    int x,cols;
    unsigned char t;
    cols=W/8;
    ptr0=dst+1;
    for(x=0;x<cols*H-1;x++) {
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

//-----------------------------------------------------------------------------
void FastGreyErode3x3(unsigned char *src, unsigned char *dst,int W,int H)
{
    int x,y,i,K1,K2,K3,min;
    unsigned char * ptr1;
    unsigned char * ptr2;
    unsigned char * ptr3;
    unsigned char * ptrd;
    ptr1=src;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptrd=dst+W+1;
    for(y=1;y<H-1;y++) {
        if(ptr1[0]<=ptr2[0]) K1=ptr1[0];
        else K1=ptr2[0];
        if(ptr3[0]<K1) K1=ptr3[0];
        
        if(ptr1[1]<=ptr2[1]) K2=ptr1[1];
        else K2=ptr2[1];
        if(ptr3[1]<K2) K2=ptr3[1];

        if(ptr1[2]<=ptr2[2]) K3=ptr1[2];
        else K3=ptr2[2];
        if(ptr3[2]<K3) K3=ptr3[2];

        if(K1<=K2) min=K1;
        else min=K2;
        if(K3<min) min=K3;

        ptrd[0]=min;
        for(x=1;x<W-2;x++) {
            K1=K2;
            K2=K3;
            if(ptr1[x+2]<=ptr2[x+2]) K3=ptr1[x+2];
            else K3=ptr2[x+2];
            if(ptr3[x+2]<K3) K3=ptr3[x+2];

            if(K1<=K2) min=K1;
            else min=K2;
            if(K3<min) min=K3;
            ptrd[x]=min;
        }
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3=ptr3+W;
        ptrd=ptrd+W;
    }
}

void FastGreyDilate3x3(unsigned char *src, unsigned char *dst,int W,int H)
{
    int x,y,i,K1,K2,K3,max;
    unsigned char * ptr1;
    unsigned char * ptr2;
    unsigned char * ptr3;
    unsigned char * ptrd;
    ptr1=src;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptrd=dst+W+1;
    for(y=1;y<H-1;y++) {
        if(ptr1[0]>=ptr2[0]) K1=ptr1[0];
        else K1=ptr2[0];
        if(ptr3[0]>K1) K1=ptr3[0];
        
        if(ptr1[1]>=ptr2[1]) K2=ptr1[1];
        else K2=ptr2[1];
        if(ptr3[1]>K2) K2=ptr3[1];

        if(ptr1[2]>=ptr2[2]) K3=ptr1[2];
        else K3=ptr2[2];
        if(ptr3[2]>K3) K3=ptr3[2];

        if(K1>=K2) max=K1;
        else max=K2;
        if(K3>max) max=K3;

        ptrd[0]=max;
        for(x=1;x<W-2;x++) {
            K1=K2;
            K2=K3;
            if(ptr1[x+2]>=ptr2[x+2]) K3=ptr1[x+2];
            else K3=ptr2[x+2];
            if(ptr3[x+2]>K3) K3=ptr3[x+2];

            if(K1>=K2) max=K1;
            else max=K2;
            if(K3>max) max=K3;
            
            ptrd[x]=max;
        }
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3=ptr3+W;
        ptrd=ptrd+W;
    }
}

//-----------------------------------------------------------------------------
void FastGreyOpen3x3(unsigned char *src, unsigned char *dst,int W,int H)
{
    int x,y,i,K1,K2,K3,min,max;
    unsigned char * ptr1;
    unsigned char * ptr2;
    unsigned char * ptr3;
    unsigned char * ptrd;
    ptr1=src;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptrd=dst+W+1;
    for(y=1;y<H-1;y++) { //eroding the src image -> destination
        if(ptr1[0]<=ptr2[0]) K1=ptr1[0];
        else K1=ptr2[0];
        if(ptr3[0]<K1) K1=ptr3[0];
        
        if(ptr1[1]<=ptr2[1]) K2=ptr1[1];
        else K2=ptr2[1];
        if(ptr3[1]<K2) K2=ptr3[1];

        if(ptr1[2]<=ptr2[2]) K3=ptr1[2];
        else K3=ptr2[2];
        if(ptr3[2]<K3) K3=ptr3[2];

        if(K1<=K2) min=K1;
        else min=K2;
        if(K3<min) min=K3;

        ptrd[0]=min;
        for(x=1;x<W-2;x++) {
            K1=K2;
            K2=K3;
            if(ptr1[x+2]<=ptr2[x+2]) K3=ptr1[x+2];
            else K3=ptr2[x+2];
            if(ptr3[x+2]<K3) K3=ptr3[x+2];

            if(K1<=K2) min=K1;
            else min=K2;
            if(K3<min) min=K3;
            ptrd[x]=min;
        }
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3=ptr3+W;
        ptrd=ptrd+W;
    }
    ptr1=dst;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptrd=src+W+1;
    for(y=1;y<H-1;y++) {  //dilating the eroded image (destination) -> src
        if(ptr1[0]>=ptr2[0]) K1=ptr1[0];
        else K1=ptr2[0];
        if(ptr3[0]>K1) K1=ptr3[0];
        
        if(ptr1[1]>=ptr2[1]) K2=ptr1[1];
        else K2=ptr2[1];
        if(ptr3[1]>K2) K2=ptr3[1];

        if(ptr1[2]>=ptr2[2]) K3=ptr1[2];
        else K3=ptr2[2];
        if(ptr3[2]>K3) K3=ptr3[2];

        if(K1>=K2) max=K1;
        else max=K2;
        if(K3>max) max=K3;

        ptrd[0]=max;
        for(x=1;x<W-2;x++) {
            K1=K2;
            K2=K3;
            if(ptr1[x+2]>=ptr2[x+2]) K3=ptr1[x+2];
            else K3=ptr2[x+2];
            if(ptr3[x+2]>K3) K3=ptr3[x+2];

            if(K1>=K2) max=K1;
            else max=K2;
            if(K3>max) max=K3;
            
            ptrd[x]=max;
        }
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3=ptr3+W;
        ptrd=ptrd+W;
    }
}

//-----------------------------------------------------------------------------
void FastGreyClose3x3(unsigned char *src, unsigned char *dst,int W,int H)
{
    int x,y,i,K1,K2,K3,min,max;
    unsigned char * ptr1;
    unsigned char * ptr2;
    unsigned char * ptr3;
    unsigned char * ptrd;
    ptr1=src;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptrd=dst+W+1;
    for(y=1;y<H-1;y++) {  //dilating the eroded image (destination) -> src
        if(ptr1[0]>=ptr2[0]) K1=ptr1[0];
        else K1=ptr2[0];
        if(ptr3[0]>K1) K1=ptr3[0];
        
        if(ptr1[1]>=ptr2[1]) K2=ptr1[1];
        else K2=ptr2[1];
        if(ptr3[1]>K2) K2=ptr3[1];

        if(ptr1[2]>=ptr2[2]) K3=ptr1[2];
        else K3=ptr2[2];
        if(ptr3[2]>K3) K3=ptr3[2];

        if(K1>=K2) max=K1;
        else max=K2;
        if(K3>max) max=K3;

        ptrd[0]=max;
        for(x=1;x<W-2;x++) {
            K1=K2;
            K2=K3;
            if(ptr1[x+2]>=ptr2[x+2]) K3=ptr1[x+2];
            else K3=ptr2[x+2];
            if(ptr3[x+2]>K3) K3=ptr3[x+2];

            if(K1>=K2) max=K1;
            else max=K2;
            if(K3>max) max=K3;
            
            ptrd[x]=max;
        }
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3=ptr3+W;
        ptrd=ptrd+W;
    }
    ptr1=dst;
    ptr2=ptr1+W;
    ptr3=ptr2+W;
    ptrd=src+W+1;
    for(y=1;y<H-1;y++) {  //Eroding the dilated image (destination) -> src
        if(ptr1[0]<=ptr2[0]) K1=ptr1[0];
        else K1=ptr2[0];
        if(ptr3[0]<K1) K1=ptr3[0];
        
        if(ptr1[1]<=ptr2[1]) K2=ptr1[1];
        else K2=ptr2[1];
        if(ptr3[1]<K2) K2=ptr3[1];

        if(ptr1[2]<=ptr2[2]) K3=ptr1[2];
        else K3=ptr2[2];
        if(ptr3[2]<K3) K3=ptr3[2];

        if(K1<=K2) min=K1;
        else min=K2;
        if(K3<min) min=K3;

        ptrd[0]=min;
        for(x=1;x<W-2;x++) {
            K1=K2;
            K2=K3;
            if(ptr1[x+2]<=ptr2[x+2]) K3=ptr1[x+2];
            else K3=ptr2[x+2];
            if(ptr3[x+2]<K3) K3=ptr3[x+2];

            if(K1<=K2) min=K1;
            else min=K2;
            if(K3<max) min=K3;
            
            ptrd[x]=min;
        }
        ptr1=ptr2;
        ptr2=ptr3;
        ptr3=ptr3+W;
        ptrd=ptrd+W;
    }
}
