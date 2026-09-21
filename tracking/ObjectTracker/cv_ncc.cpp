//M*/
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"

#include "cv_ncc.h"
using namespace std;
//using namespace cv;
namespace cv
{
  namespace normcctracker
  {

//---//------------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------------------------
	//Normalized Cross Correlation
	//--------------------------------------------------------------------------------------------------------------------------------------------------
	  cv::Rect RectMultiply_ncc(const cv::Rect & rect, float f)
    {
      cv::Rect r_tmp;
      r_tmp.y = (int) (rect.y - ((float) rect.height * f - rect.height) / 2);
      if (r_tmp.y < 0)
        r_tmp.y = 0;
      r_tmp.x = (int) (rect.x - ((float) rect.width * f - rect.width) / 2);
      if (r_tmp.x < 0)
        r_tmp.x = 0;
      r_tmp.height = (int) (rect.height * f);
      r_tmp.width = (int) (rect.width * f);

      return r_tmp;
    }
	  
	NORMCCTracker::NORMCCTracker(cv::Mat&  image, Rect initPatch)//, Rect validROI, int numBaseClassifier)// must be colored image
    {
		counterFrames=0;
		First=true;
		baseresponse=1.0;
		trackWindow = initPatch;
		Mat curr;
		curr=image(trackWindow);
		Prev = curr.clone();
		cvtColor(Prev,Prev,CV_RGB2GRAY);


    }

    NORMCCTracker::~NORMCCTracker(void)
    {
		cv::destroyWindow("temp");
      //delete detector;
      //delete classifier;
    }
	void NORMCCTracker::UpdateTemplate(cv::Mat&  image, Rect initPatch)
	{
		trackWindow = initPatch;
		Mat curr;
		curr=image(trackWindow);
		Prev = curr.clone();
		cvtColor(Prev,Prev,CV_RGB2GRAY);

	}
    bool
    NORMCCTracker::track(cv::Mat&  image, Rect& patches)
    {
		patches=trackWindow;
		Mat imagegrey,res;
		int result_cols =  image.cols - Prev.cols + 1;
		int result_rows = image.rows - Prev.rows + 1;
		res.create( result_cols, result_rows, CV_32FC1 );
		cvtColor(image,imagegrey,CV_RGB2GRAY);
		/*Mat channel[3];
		split(image, channel);
		imagegrey=channel[1];*/
		int method = CV_TM_CCORR_NORMED;
		matchTemplate(imagegrey, Prev, res, method);
		double minVal, maxVal;
		Point minLoc, maxLoc;
		minMaxLoc(res, &minVal, &maxVal, &minLoc,&maxLoc,cv::Mat());
		patches=Rect(maxLoc, Prev.size());


		//-----------------------------------------------
		cv::Mat Dummy(image,cv::Rect(image.cols-Prev.cols-20,40,Prev.cols,Prev.rows ));
		cv::Mat tt;cv::cvtColor (Prev,tt,CV_GRAY2RGB);
		tt.copyTo (Dummy);
		cv::rectangle(image,cv::Rect(image.cols-Prev.cols-20,40,Prev.cols,Prev.rows ),cv::Scalar(255,255,255),2,8);
		//-----------------------------------------------


		//cv::namedWindow ("temp");
		//imshow("temp",Prev);
         //   if( trackObject )
		trackedPatch=patches;
		/*if(First)
		{
			baseresponse=1.0/maxVal;
			First=false;
		}
		maxVal=maxVal*baseresponse;*/
		//cv::waitKey(25);
		Score=std::abs(maxVal);//-minVal)<1?maxVal-minVal:maxVal;
		if(Score>0.85)
		{
			counterFrames++;
			if(counterFrames==10)
			{
				if((patches.x>0) && (patches.y>0))
					{
						if((patches.x<image.cols-patches.width) && (patches.y<image.rows-patches.height))
							{
								UpdateTemplate(image,patches);
							
						}
				}
					counterFrames=0;
			}			
		}
		else
			counterFrames=0;
		//patches=trackWindow ;
      return (Score>0.85);
    }

    Rect
    NORMCCTracker::getTrackingROI(float searchFactor)
    {
      Rect searchRegion;

      searchRegion = RectMultiply_ncc(trackedPatch, searchFactor);
      //check
      if (searchRegion.y + searchRegion.height > validROI.height)
        searchRegion.height = validROI.height - searchRegion.y;
      if (searchRegion.x + searchRegion.width > validROI.width)
        searchRegion.width = validROI.width - searchRegion.x;

      return searchRegion;
    }

    float
    NORMCCTracker::getConfidence()
    {
      return  (float)Score;// confidence / classifier->getSumAlpha();
    }
	
    Rect
    NORMCCTracker::getTrackedPatch()
    {
      return trackedPatch;
    }

    cv::Point2i
    NORMCCTracker::getCenter()
    {
      cv::Point2i center;
      center.y = trackedPatch.y + trackedPatch.height / 2;
      center.x = trackedPatch.x + trackedPatch.width / 2;
      return center;
    }
//---------------------------------------------------------------------------------------------------------------------------------------
  }
}