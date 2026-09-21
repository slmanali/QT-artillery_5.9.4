#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <Math.h>
#include "Morphology.h"
#include "thresholding.h"
#include "alg_Labeling.h"
#include "IPLib.h"
#include <vector>
//#include "Prediction.h"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#ifndef __OPENCV_Thresh_H__
#define __OPENCV_Thresh_H_
namespace cv
{
namespace threshold_tracker
{
  class Threshold_Tracking {
	
  public:
	Threshold_Tracking(){
		/*-----------------------------------------------------*/
		/*-- init the matrixs */
		pSrc = NULL;
		pHat = NULL;
		pMask = NULL;
		pDst = NULL;
		pTmp = NULL;
		ii_ptr = NULL;
		ii_bin = NULL;
		ii_label = NULL;
		/*-----------------------------------------------------*/
	/*	cv::namedWindow("new threshold_tracking");
		cv::waitKey();*/
	}
	~Threshold_Tracking(){
		/*cv::namedWindow("free Tracker_");
		cv::waitKey();*/
	}
	ip_Byte *pSrc, *pDst, *pTmp, *pMask, *pHat;
	ip_Byte *ii_ptr, *ii_bin, *ii_label;
	bool AutoTargetColor;
	bool bFirstTracking, bDemo;
	int TopHatFDim;
	int RegW, RegH;
	int MyTargetSize = 0;
	cv::Point Centre;
	bool bWhitetar;
	bool bLargeTarget;// targetsize>ratio of TopBottomHatFilter Dims
	cv::Rect RegionToCheck;
	cv::Rect Quadre;
	/*void ChangeQuadre(cv::Mat Frame, cv::Point Centre, int RegW, int RegH, cv::Rect *rect);
	void SetRegionToCheck(cv::Mat Frame, int TopHatFDim, int RegW, int RegH, cv::Point Centre, cv::Rect *rect);
	void Copymemory(void* pDst, void* pSrc, int size);
	void  Threshold_Tracking::FreeImages();
	void __fastcall Threshold_Tracking::AllocateImages(int TopHatFDim, int w, int h);
    int __fastcall TargetColorLabel(Byte *src, int W, int H, int RegW, int RegH, int tSize, cv::Point APos, cv::Point LeftTopPos,bool DDebug);
	void __fastcall ShowImage(char window_name[256],int x0, int y0, int w, int h, Byte *pSrc, bool bNegative);
	void init(cv::Mat CurrentFrame, cv::Rect box, int TopHatFDim, bool *bFirstTracking, bool *bLargeTarget, bool AutoTargetColor, bool  *bWhitetar, int *RegW, int *RegH,bool DDebug);
	void Tracking(cv::Mat CurrentFrame1, cv::Rect *box, int RegW, int RegH, int TopHatFDim, bool bWhitetar, bool bLargeTarget, bool DDebug);
	void Detection(cv::Mat frame, int RegW, int RegH, cv::Rect  *RegionToCheck, bool bFirstTracking, cv::Rect* Quadre, int nMin, int nMax, unsigned char *pSrc, bool *LargeTarget, int TopHatFDim, cv::Point *Centre, int *MyTargetSize);
	void __fastcall DrawContour(cv::Mat frame, double x0, double y0, int nCount, ac_Point *pContour, cv::Scalar Color);
	void DrawQuadre(cv::Mat DrawFrame, cv::Rect Quadre1);
	void DrawCross(cv::Mat DrawFrame, cv::Point center, cv::Scalar color);*/


	//-----------------------------------------------------------------------------------
	void DrawQuadre(cv::Mat DrawFrame, cv::Rect Quadre1)
	{

		//Centre = cv::Point(160, 120);
		cv::rectangle(DrawFrame, Quadre1, cv::Scalar(255, 0, 0), 2);

		cv::line(DrawFrame, cv::Point(DrawFrame.cols / 2 - 15, DrawFrame.rows / 2), cv::Point(DrawFrame.cols / 2 - 5, DrawFrame.rows / 2), cv::Scalar(0, 0, 255), 1);
		cv::line(DrawFrame, cv::Point(DrawFrame.cols / 2 + 5, DrawFrame.rows / 2), cv::Point(DrawFrame.cols / 2 + 15, DrawFrame.rows / 2), cv::Scalar(0, 0, 255), 1);
		cv::line(DrawFrame, cv::Point(DrawFrame.cols / 2, DrawFrame.rows / 2 - 15), cv::Point(DrawFrame.cols / 2, DrawFrame.rows / 2 - 5), cv::Scalar(0, 0, 255), 1);
		cv::line(DrawFrame, cv::Point(DrawFrame.cols / 2, DrawFrame.rows / 2 + 5), cv::Point(DrawFrame.cols / 2, DrawFrame.rows / 2 + 15), cv::Scalar(0, 0, 255), 1);
	}

//---------------------------------------------------------------------------
void ChangeQuadre(cv::Mat Frame, cv::Point Centre, int RegW, int RegH, cv::Rect *rect)
{
	int ImageHeight, ImageWidth;
	ImageHeight = Frame.rows;
	ImageWidth = Frame.cols;
	rect->x = Centre.x - RegW / 2;
	rect->y = Centre.y - RegH / 2;
	if (rect->x<0) rect->x = 0;
	if (rect->y<0) rect->y = 0;
	rect->height = RegH - 1;
	if ((rect->y + rect->height)>ImageHeight - 1)
	{
		rect->height = ImageHeight - 1 - rect->y;
		rect->y = ImageHeight - RegH + 1;
	}
	rect->width = RegW - 1;
	if ((rect->x + rect->width)>ImageWidth - 1)
	{
		rect->width = ImageWidth - 1 - rect->x;
		rect->x = ImageWidth - RegW + 1;
	}
}
//-------------------------------------------------------------------------
void SetRegionToCheck(cv::Mat Frame, int TopHatFDim, int RegW, int RegH, cv::Point Centre, cv::Rect *rect)
{
	int ImageHeight, ImageWidth;
	ImageHeight = Frame.rows;
	ImageWidth = Frame.cols;

	rect->x = Centre.x - (RegW / 2);
	rect->y = Centre.y - (RegH / 2);
	if (rect->x<TopHatFDim) rect->x = TopHatFDim;
	if (rect->y<8) rect->y = 8;
	rect->height = RegH - 1;
	if ((rect->height + rect->y)>ImageHeight - 8 - 1)
	{
		rect->height = (ImageHeight - 8 - 1) - rect->y;
		rect->y = ImageHeight - 8 - RegH + 1;
	}
	rect->width = RegW - 1;
	if ((rect->width + rect->x)>ImageWidth - TopHatFDim - 1)
	{
		rect->width = ImageWidth - TopHatFDim - 1 - rect->x;
		rect->x = ImageWidth - RegW + 1;
	}

}
void DrawCross(cv::Mat DrawFrame, cv::Point center, cv::Scalar color)
{
	cv::line(DrawFrame, cv::Point(center.x - 10, center.y), cv::Point(center.x + 10, center.y), color);
	cv::line(DrawFrame, cv::Point(center.x, center.y - 10), cv::Point(center.x, center.y + 10), color);
}
//--------------------------------------------------------
//------------------------------------------------------------------------------------------
void Copymemory(void* pDst, void* pSrc, int size)
{
	unsigned char* Ps, *Pd;
	Ps = (unsigned char*)pSrc;
	Pd = (unsigned char*)pDst;
	for (int i = 0; i<size; i++)
		Pd[i] = Ps[i];
}
//-----------------------------------------------------------------------------

//---------------------------------------------------------------------------
void AllocateImages(int TopHatFDim, int w, int h)
{
	int size = w*h;
	pSrc = new ip_Byte[size];
	pDst = new ip_Byte[size];
	pMask = new ip_Byte[size];
	pTmp = new ip_Byte[size];
	pHat = new ip_Byte[(w + 2 * TopHatFDim)*h];
	//ii_ptr = new ip_Byte[size];
	//ii_bin = new ip_Byte[size];
	//ii_label = new ip_Byte[size];
	ii_ptr = new ip_Byte[128*128];
	ii_bin = new ip_Byte[128*128];
	ii_label = new ip_Byte[128*128];
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void FreeImages()
{

	if (pSrc)
	{
		delete[] pSrc;
		pSrc = NULL;
	}
	if (pHat)
	{
		delete[] pHat;
		pHat = NULL;
	}


	if (pMask)
	{
		delete[] pMask;
		pMask = NULL;
	}
	if (pDst)
	{
		delete[] pDst;
		pDst = NULL;
	}
	if (pTmp)
	{
		delete[] pTmp;
		pTmp = NULL;
	}

	if (ii_ptr) {
		delete[] ii_ptr;
		ii_ptr = NULL;
	}
	if (ii_bin) {
		delete[] ii_bin;
		ii_bin = NULL;
	}
	if (ii_label) {
		delete[] ii_label;
		ii_label = NULL;
	}
}
void ShowImage(char window_name[256],int x0, int y0, int w, int h, Byte *pSrc, bool bNegative)
{
	//if (pResult.cols!= w)		pResult.cols= w;
	//if (pResult.rows != h)	pResult.rows = h;
	cv::Mat pResult(h, w, CV_8UC1, cv::Scalar(0, 0, 0));
	Byte color, *pIn;

	for (int y = 0; y<h; y++)
	{
		unsigned char *row = pResult.ptr<unsigned char>(y);
		//	pData = (Byte *)pResult.data;
		pIn = pSrc + y*w;
		for (int x = 0; x<w; x++)
		{
			color = *pIn++;//pSrc[x+y*w];
						   //			if(bNegative)	color = ~color;
						   //	pData[3 * x] = color;
						   //	pData[3 * x + 1] = color;
						   //	pData[3 * x + 2] = color;
			row[x] = color;
		}
	}
	//	if (bNegative) pResult->SaveToFile(Framename + ".bmp");
	cv::Mat temp;
	cv::resize(pResult, temp, cv::Size(3 * pResult.cols, 3 * pResult.rows));
	//////////////////////////cv::imshow(window_name, temp);
}
//---------------------------------------------------------------------------
void DrawContour(cv::Mat frame, double x0, double y0, int nCount, ac_Point *pContour, cv::Scalar Color)
{
	cv::Mat src_gray, canny_output;
	int thresh = 100;
	int max_thresh = 255;
	cv::RNG rng(12345);
	if (nCount <= 2)	return;
	if (pContour == NULL)	return;

	std::vector < std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::cvtColor(frame, src_gray, cv::COLOR_BGR2GRAY);
	cv::Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	cv::findContours(canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	cv::Mat drawing = cv::Mat::zeros(canny_output.size(), CV_8UC3);
	for (size_t i = 0; i< contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(frame, contours, (int)i, color, 2, 8, hierarchy, 0, cv::Point());
	}

}



//--------------------------------------------------------------------------------
int  TargetColorLabel(unsigned char *src, int W, int H, int RegW, int RegH, int tSize, cv::Point APos, cv::Point LeftTopPos,bool DDebug)
{
	int x, y, count, TC;
	ip_target mytargets[128];
	int tc1, tc2, xc, yc, nSize;
	float df, min;
	float hist[256];
	df = 1 / (float)(W*H);
	count = 0;
	for (x = 0; x<256; x++) hist[x] = 0;
	for (x = 0; x<W*H; x++) hist[src[x]] += df;
	//ac_FastGaussianWin5x5(RegW, RegH, pDst, pSrc, 0, 0);
	ac_FastGaussianWin5x5(W, H, src, ii_bin, 0, 0);
	ip_KittlerAll2(W, H, ii_bin, ii_label, 256, hist);
	ip_RemoveBorders(W, H, ii_label, 0, 0, 1);
	ip_RemoveBorders(W, H, ii_bin, 0, 0, 1);
	char ii_Label[] = "ii_label";
	char ii_Bin[] = "ii_bin";
	if (DDebug) ShowImage(ii_Label, 0, 0, W, H, ii_label, 0);
	if (DDebug) ShowImage(ii_Bin, 0, 0, W, H, ii_bin, 0);


	tc1 = tc2 = 0;
	//tSize = 10;
	for (y = 0; y<H; y++) 
	{
		for (x = 0; x<W; x++) 
		{
			if (ii_label[y*W + x] == 255) 
			{
				nSize = ip_FloodFill(W, H, ii_label, x, y, 0, 0, &xc, &yc);
				if (tSize != 0) 
				{
					if ((nSize >(tSize / 2) && nSize < (tSize * 15 / 10) && count <128)) {
						tc2++;
						mytargets[count].xc = xc;
						mytargets[count].yc = yc;
						mytargets[count].Color = 1;
						mytargets[count].Surface = nSize;
						mytargets[count].Distance = (float)((xc - APos.x)*(xc - APos.x) + (yc - APos.y)*(yc - APos.y));
						count++;
					}
				}
				else 
				{
					if ((nSize > 3) && (nSize < W*H / 2) && (count <128)) {
						tc2++;
						mytargets[count].xc = xc;
						mytargets[count].yc = yc;
						mytargets[count].Color = 1;
						mytargets[count].Surface = nSize;
						mytargets[count].Distance = (float)((xc - APos.x)*(xc - APos.x) + (yc - APos.y)*(yc - APos.y));
						count++;
					}
				}
			}
		}
	}
	for (y = 0; y<H; y++) 
	{
		for (x = 0; x<W; x++) 
		{
			if (ii_bin[y*W + x] == 255) 
			{
				nSize = ip_FloodFill(W, H, ii_bin, x, y, 0, 0, &xc, &yc);
				if (tSize != 0) {
					if ((nSize >(tSize / 2)) && (nSize < (tSize * 15 / 10) && (count <128))) {
						tc2++;
						mytargets[count].xc = xc;
						mytargets[count].yc = yc;
						mytargets[count].Color = 0;
						mytargets[count].Surface = nSize;
						mytargets[count].Distance = (float)((xc - APos.x)*(xc - APos.x) + (yc - APos.y)*(yc - APos.y));
						count++;
					}
				}
				else {
					if ((nSize > 3) && (nSize < W*H / 2) &&( count <128)) {
						tc2++;
						mytargets[count].xc = xc;
						mytargets[count].yc = yc;
						mytargets[count].Color = 0;
						mytargets[count].Surface = nSize;
						mytargets[count].Distance = (float)((xc - APos.x)*(xc - APos.x) + (yc - APos.y)*(yc - APos.y));
						count++;
					}
				}
			}
		}
	}
	
	min = mytargets[0].Distance;
	TC = mytargets[0].Color;
	for (x = 1; x<count; x++) {
		if (mytargets[x].Distance < min) {
			min = mytargets[x].Distance;
			TC = mytargets[x].Color;
		}
	}
	if (TC > 2) TC = 1;
//	if (tc2 == 0) return 1;
//	if (tc1 == 0) return 0;
	
	return TC;
}


///
void Detection(cv::Mat frame, int RegW, int RegH, cv::Rect  *RegionToCheck, bool bFirstTracking, cv::Rect* Quadre, int nMin, int nMax, unsigned char *pSrc, bool *LargeTarget, int TopHatFDim, cv::Point *Centre, int *MyTargetSize,bool DDebug)
{
	double x11, y11, dx, dy;
	cv::Point P;
	int MaxDistance = 16;
	Byte *p255, *p256;
	ac_Point *pContour, *pContourOut;
	pContour = new ac_Point[s_nPoints];
	pContourOut = new ac_Point[s_nPoints];
	p255 = new Byte[frame.cols * frame.rows];
	p256 = new Byte[frame.cols * frame.rows];
	int w = RegW;
	int h = RegH;
	int size = w*h;
	Byte *pImg = new Byte[size];
	Copymemory(pImg, pSrc, size);
	int acw, ach;
	int acw_2, ach_2;
	// Labeling
	Byte BkIndex = 0;
	Byte ObjIndex = 255;
	Byte GreyIndex = 128;
	Byte Epsilon = 1;
	Byte Index;
	int nRegionSize;
	double rad;
	if (LargeTarget)
		rad = 24;
	else
		rad = 12;

	int Xc, Yc;
	acw = frame.cols;
	ach = frame.rows;
	acw_2 = acw / 2;
	ach_2 = ach / 2;
	ip_Target Target;
	ip_Targets Targets;
	//FillMemory(pSrc, size, BkIndex);
	memset(pSrc, BkIndex, size);
	int xc, yc;
	double dDist;

	for (int y = 0; y<h; y++)
	{
		for (int x = 0; x<w; x++)
		{
			Index = pImg[x + y*w];
			if (Index == ObjIndex)
			{
				nRegionSize = ac_FloodFill(w, h, pImg, x, y, GreyIndex, Epsilon, xc, yc);
				P = cv::Point(xc + RegionToCheck->x, yc + RegionToCheck->y);
				dDist = ac_Distance(*Centre, P);
				if ((!bFirstTracking) && (dDist > MaxDistance))// Max distance
				{
					ac_FloodFill(w, h, pImg, x, y, BkIndex, Epsilon, xc, yc);
					continue;
				}
				Target.x = x;
				Target.y = y;
				Target.p = P;
				Target.nSize = nRegionSize;
				Target.dDist = dDist;
				Targets.push_back(Target);
			}
		}
	}

	//////    if(!bDemo)	ShowImage(2*w+1,2*h+1,w,h,pImg,false);

	int I = -1;
	double dMinDist;
	dMinDist = INT_MAX;
	for (int i = 0; i<Targets.size(); i++) {
		Target = Targets[i];
		if (Target.dDist < dMinDist) {
			dMinDist = Target.dDist;
			I = i;
		}
	}
	//std::cout << "Targets size=" << Targets.size()<<", I = "<<I << std::endl;
	if (I >= 0)
	{
		int size = acw*ach;
		Target = Targets[I];
		// nPrevRegionSize = Target.nSize;
		*MyTargetSize = Target.nSize;
		//FillMemory(p256, size, BkIndex);
		memset(p256,BkIndex,size);
		//std::cout << "BKIndex = " << BkIndex << std::endl;
		for (int y = 0; y<h; y++)
		{
			for (int x = 0; x<w; x++)
			{
				p256[(x + RegionToCheck->x) + (y + RegionToCheck->y)*acw] = pImg[x + y*w];
			}
		}
		//FillMemory(p255, size, BkIndex);
		memset(p255, BkIndex, size);
		ac_FloodFill(acw, ach, p256, p255, Target.x + RegionToCheck->x, Target.y + RegionToCheck->y, BkIndex, ObjIndex, Epsilon, xc, yc);
		Xc = xc;
		Yc = yc;
		*LargeTarget = (Target.nSize >(1200));


		// Center
		dx = acw_2 - xc;
		dy = ach_2 - yc;
		ac_MoveImage(acw, ach, p255, p256, xc, yc, acw_2, ach_2);

		x11 = acw_2;
		y11 = ach_2;
		ac_FastGaussianWin5x5(acw, ach, p256, p255, 20, 10);//190 110

		ac_ActiveContour(acw, ach, p255, x11, y11, rad, s_nPoints, pContour);
		//std::cout << "s_nPoints = " << s_nPoints << std::endl;
		FilterActiveContour(pContour, pContourOut, s_nPoints);
		int nCount = s_nPoints;
		for (int kk = 1; kk < s_nPoints; kk++)
		{
  		   cv::line(frame, cv::Point(pContourOut[(kk + nCount) % nCount].x - dx, pContourOut[(kk + nCount) % nCount].y - dy), cv::Point(pContourOut[(kk+1 + nCount) % nCount].x - dx, pContourOut[(kk+1 + nCount) % nCount].y - dy), cv::Scalar(0, 0, 255), 2);
		}// DrawContour(frame,-dx,-dy,s_nPoints,pContourOut,cv::Scalar(255,0,0));

		//     PaintBox->Canvas->Ellipse(Xc-r,Yc-r,Xc+r,Yc+r);
		//MyTargetSize=0;
		///////////////////////////////if(DDebug) cv::imshow("image", frame);
		ip_Point Pl;
		Pl.x = Xc; Pl.y = Yc;
		/*if(PredictCB)
		{
		Pl=ip_Smooth(Pl);
		}*/


		Centre->x = Pl.x;
		Centre->y = Pl.y;
		//  Center.x= Pl.x;
		//  Center.y = Pl.y;
		//	std::cout << "P=" << P<<std::endl;
		ChangeQuadre(frame, *Centre, RegW, RegH, Quadre);
		SetRegionToCheck(frame, TopHatFDim, RegW, RegH, *Centre, RegionToCheck);
	}
	else
	{ // No target
		ip_Point Pl;
		Pl.x = Centre->x; Pl.y = Centre->y;
		/*  if(PredictCB)
		{
		Pl=ip_Smooth(Pl);
		}*/
		Centre->x = Pl.x;
		Centre->y = Pl.y;
		//Center.x = Pl.x;
		//Center.y = Pl.y;



	}
	// DrawCursor(Centre);
	if (pImg)
	{
		delete[] pImg;
		pImg = NULL;
	}
	if (pContour)
	{
		delete[] pContour;
		pContour = NULL;
	}
	if (pContourOut)
	{
		delete[] pContourOut;
		pContourOut = NULL;
	}
	if (p255)
	{
		delete[] p255;
		p255 = NULL;
	}
	if (p256)
	{
		delete[] p256;
		p256 = NULL;
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void init(cv::Mat frame, cv::Rect box, int TopHatFDim, bool *bFirstTracking, bool *bLargeTarget, bool AutoTargetColor, bool  *bWhitetar, int *RegW, int *RegH,bool DDebug)
{
	/* ---<   imad issa   >---   */
	/*
	automatic target color selection
	may be we will get a problem when passing from IR to CCD and vvc if the target is
	not in the centre of the window;
	*/


	

	std::cout << "init1" << endl;
	cv::Point Centre;
	cv::Rect RegionToCheck;
	cv::Rect Quadre;
	int MyTargetSize = 0;
	*RegH = box.height;
	*RegW = box.width;
	Centre = cv::Point(box.x + box.width / 2, box.y + box.height / 2);
	std::cout << "init2" << endl;
	FreeImages();
	AllocateImages(TopHatFDim, *RegW, *RegH);
	std::cout << "init4" << endl;
	int xs, ys, xe, ye, iix, iiy;
	if (*bFirstTracking) {
		*bLargeTarget = true;
		//we take a region around the selected point starting by checking borders
		if (AutoTargetColor) {
			xs = ((Centre.x - 48)<0) ? 0 : Centre.x - 48;
			xe = ((Centre.x + 48) >= frame.cols) ?  frame.cols - 1 : Centre.x + 48;
			ye = ((Centre.y + 48) >= frame.rows) ? frame.rows - 1 : Centre.y + 48;
			ys = ((Centre.y - 48)<0) ? 0 : Centre.y - 48;
			//relatif center point
			iix = Centre.x - xs;
			iiy = Centre.y - ys;
			//region width and height
			int iiw, iih;
			iiw = xe - xs + 1;
			iih = ye - ys + 1;
			//grabbing the selected region
			unsigned char *ptmpp = ii_ptr;
			cv::Mat temp_work, temp;
			cv::Rect roi;
			roi.x = xs;
			roi.y = ys;
			roi.width = iiw;
			roi.height = iih;
			temp_work = frame(roi);
			cv::cvtColor(temp_work, temp, cv::COLOR_RGB2GRAY);
			//std::cout << "temp width =" << temp.cols << "temp height = " << temp.rows << std::endl;
			//cv::imshow("test", temp);
			for (int y = 0; y <roi.height; y++)
			{
				unsigned char *row = temp.ptr<unsigned char>(y);
				for (int x = 0; x < roi.width; x++)
				{

					*ptmpp++ = (ip_Byte)(row[x]);
				}
			}
			char ii_Ptr[] = "ii_ptr";
			if(DDebug) ShowImage(ii_Ptr,0, 0, roi.width, roi.height, ii_ptr, 0);
			//chnaging target color

			int toto = TargetColorLabel(ii_ptr, iiw, iih, *RegW, *RegH, MyTargetSize, cv::Point(iix, iiy), cv::Point(xs, ys),DDebug);
			
			std::cout << "bwhiter = " << toto << std::endl;
			*bWhitetar = (bool)toto;
		}
		bFirstTracking = false;

	}

}
///-----------------------------------------------------
void Tracking(cv::Mat CurrentFrame, cv::Rect *box, int RegW, int RegH, int TopHatFDim, bool bWhitetar, bool bLargeTarget, bool DDebug)
{
	cv::Point Centre;
	cv::Rect RegionToCheck;
	cv::Rect Quadre;
	bool bFirstTracking = false;
	int MyTargetSize = 0;

	Centre = cv::Point(box->x + box->width / 2, box->y + box->height / 2);

	SetRegionToCheck(CurrentFrame, TopHatFDim, RegW, RegH, Centre, &RegionToCheck);
	ip_Byte *pl = pSrc;
	int Xs, Xe;
	if (RegW<160) {
		Xs = RegionToCheck.x - TopHatFDim;
		if (Xs<0)Xs = 0; Xe = Xs + RegW + 2 * TopHatFDim - 1;
		if (Xe >= CurrentFrame.cols)
		{
			Xe = CurrentFrame.cols - 1;
			Xs = Xe - RegW - 2 * TopHatFDim + 1;
		}
		pl = pHat;
	}
	else
	{
		Xs = RegionToCheck.x; Xe = RegionToCheck.x + RegionToCheck.width;
		pl = pSrc;
	}

	cv::Mat temp_work, temp;
	cv::Rect roi;
	roi.x = Xs;
	roi.y = RegionToCheck.y;
	roi.width = Xe - Xs;
	roi.height = RegionToCheck.height;
	temp_work = CurrentFrame(roi);
	cv::cvtColor(temp_work, temp, cv::COLOR_RGB2GRAY);
	for (int y = 0; y <roi.height; y++)
	{
		unsigned char *row = temp.ptr<unsigned char>(y);
		for (int x = 0; x <=roi.width; x++)
		{

			*pl++ = (ip_Byte)(row[x]);
		}
	}

	int nEdge = 0;
	int nMin = 9, nMax = 256 * 256;
	cv::Rect rect;
	//	if (bLargeTarget)

	//DrawCross(CurrentFrame, Centre, cv::Scalar(255, 255, 0));
	ip_Byte *ptmp;
	ptmp = pSrc; pSrc = pDst; pDst = ptmp;
	char org[]="org";
	
	if (DDebug) ShowImage(org,0, 0, RegW,RegH, pHat, false);

	if (RegW<160) {
		//if(!bLargeTarget) {
		if (bWhitetar) {
			ip_TopHatRowN(pHat, pSrc, RegW + 2 * TopHatFDim, RegH, TopHatFDim);
		}
		else {
			ip_BottomHatRowN(pHat, pSrc, RegW + 2 * TopHatFDim, RegH, TopHatFDim);
		}
	}
	else {
		if (!bWhitetar) { ip_InvertImage(RegW, RegH, pDst, pSrc); } // Swap Pointers
		else {
			ptmp = pSrc; pSrc = pDst; pDst = ptmp;
		}
	}

	//if (bDemo)	ShowImage(ImageWidth, h + 1, RegW, RegH, pSrc, false);
	FastGreyClose3x3(pSrc, pDst, RegW, RegH);

	//if (bDemo)	ShowImage(ImageWidth, 2 * h + 1, w, h, pSrc, false);
	ptmp = pSrc; pSrc = pDst; pDst = ptmp;
	ac_FastGaussianWin5x5(RegW, RegH, pDst, pSrc, 0, 0);
	char Gaussian[] = "Gaussian";
	if (DDebug)	ShowImage(Gaussian, RegW, RegH, RegW, RegH, pSrc, false);
	//if (bDemo)	ShowImage(ImageWidth, 3 * h + 1, w, h, pSrc, false);
	ac_Monochrome_Entropy(RegW, RegH, pSrc, pDst, 0, 0);
	//if (bDemo)	ShowImage(0, 0, w, h, pDst, false);


	ip_FastBinClose(RegW, RegH, pSrc, pDst);
	OpenBin(pDst, pSrc, RegW, RegH);
	CloseBin(pDst, pSrc, RegW, RegH);
	//if (bDemo)	ShowImage(3 * w,h, w, h, pDst, false);

	ip_FilterRegions(RegW, RegH, pDst, pSrc, 0, nMin, nMax, 1, false);
	///////ip_RemoveBorders(w,h,pDst,0,2,1);
	char result[] = "result";
	if (DDebug)	ShowImage(result,RegW, RegH, RegW, RegH, pSrc, false);
	Quadre = *box;
	Detection(CurrentFrame, RegW, RegH, &RegionToCheck, bFirstTracking, &Quadre, nMin, nMax, pSrc, &bLargeTarget, TopHatFDim, &Centre, &MyTargetSize,DDebug);
	*box = Quadre;
	//	std::cout << "Box = " << *box << std::endl;
}
///-----------------------------------------------------

};
}
}
#endif /* CFTLD_H_ */
