


#include "opencv2/highgui/highgui.hpp"
//#include "stdio.h"
//#include "windows.h"
#include <string>
#include <vector>


#include <opencv2/ml/ml.hpp>

#include <iostream>
#include "object_tracker.h"




using std::string;
using std::vector;

//extern "C"  void _stdcall testingSharedMemory();
//extern "C"  myImage* _stdcall gettingFromSharedMemory();
#pragma once

#include <string>

#ifdef COMPILE_MYLIBRARY
  #define MYLIBRARY_EXPORT __declspec(dllexport)
#else
  #define MYLIBRARY_EXPORT //__declspec(dllimport)
#endif
#ifndef MYAPI
  #define MYAPI 
#endif

//#ifdef __cplusplus



// Exported functions go here.


template<int T>
class MYLIBRARY_EXPORT  com_tracker_api
{
public:
	cv::ObjectTracker *tracker;

 bool setTrackerAlgorithm(int TrackingAlgo);
 bool  InitTracker(IplImage Image,cv::Rect BoundinBox);
  bool  InitTracker_(cv::Mat Image,cv::Rect BoundinBox);
  cv::Mat returnTemp();

 bool  CreateTracker(int TrackingAlgo);
 bool  UpdateTracker(IplImage Image,cv::Rect &BoundinBox,float & conf);
bool UpdateTracker_(cv::Mat& Image,cv::Rect &BoundinBox,float & conf);

 bool  FreeMIplImageptr(IplImage** image);
 bool   deleteTracker();
 float  ValidConf;
float UpdateConf;

};


//#ifdef __cplusplus
//}
//#endif

