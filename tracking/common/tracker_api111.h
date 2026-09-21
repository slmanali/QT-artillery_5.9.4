


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
class tracker_api
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

};



