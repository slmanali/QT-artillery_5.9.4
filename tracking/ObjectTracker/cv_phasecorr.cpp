//M*/
#include <iostream>
#include <stdio.h>

#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"

#include "cv_phasecorr.h"
using namespace std;
//using namespace cv;
namespace cv
{
  namespace phasecorrtracker
  {

	cv::Rect RectMultiply_phasecorr(const cv::Rect & rect, float f)
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
  //------------------------------------------------------------------------------------------------------------------------------------------
	//PHASE CORRELATOR
	//--------------------------------------------------------------------------------------------------------------------------------------------------
	PhaseCorrTracker::PhaseCorrTracker(cv::Mat&  image, Rect initPatch)//, Rect validROI, int numBaseClassifier)// must be colored image
    {
		Mat image1;
		cvtColor(image,image1,CV_RGB2GRAY);
		counterFrames=0;
		First=true;
		baseresponse=1.0;
		trackWindow = initPatch;
		Mat curr, curr1, curr2, prev1,prev2;
		Scalar mmean=mean(image1);
		curr= Mat(image.rows,image.cols,image1.type(),mmean);
		curr1= Mat(image.rows,image.cols,image1.type());
		curr.copyTo(curr1);
		prev1 = image1(trackWindow);
		curr2=Mat(trackWindow.height,trackWindow.width,prev1.type(),mmean);
		Mat Dummy(curr,trackWindow);
		prev1.copyTo (Dummy);
		//curr1(trackWindow)+=prev1;
		//curr1(trackWindow)-=curr2;
		Prev = curr.clone();



    }

    PhaseCorrTracker::~PhaseCorrTracker(void)
    {
      //delete detector;
      //delete classifier;
    }
	void PhaseCorrTracker::UpdateTemplate(cv::Mat&  image, Rect initPatch)
	{
		Mat image1;
		cvtColor(image,image1,CV_RGB2GRAY);

		trackWindow = initPatch;
		Mat curr, curr1, curr2, prev1,prev2;
		Scalar mmean=mean(image1);
		curr= Mat(image.rows,image.cols,image1.type(),mmean);
		curr1=curr.clone();
		prev1 = image1(trackWindow);
		curr2=Mat(trackWindow.height,trackWindow.width,prev1.type(),mmean);
		curr1(trackWindow)-=curr2;
		curr1(trackWindow)+=prev1;
		Prev = curr1.clone();
		

	}
    bool
    PhaseCorrTracker::track(cv::Mat&  image, Rect& patches)
    {
		
		Mat imagegrey;
		if(First)
		{
			UpdateTemplate(image,patches);
			counterFrames=0;
		}
		cvtColor(image,imagegrey,CV_RGB2GRAY);
		patches=trackWindow;
		Mat image1(image.rows,image.cols,CV_64F);
		Mat prev2(image.rows,image.cols,CV_64F);
		imagegrey.convertTo(image1,CV_64F);
		//imagegrey.copyTo (image1,CV_64F);
		createHanningWindow(hann, image1.size(), CV_64F);		
		Prev.convertTo(prev2, CV_64F);
		#if CV_MAJOR_VERSION > 2
		    Point2d shift = phaseCorrelate(image1,prev2, hann,&Score);
        #else
		  Point2d shift = phaseCorrelateRes(image1,prev2, hann,&Score);
        #endif
		
		patches.x+=(int)shift.x;
		patches.y+=(int)shift.y;
		
		cv::namedWindow ("temp");
		imshow("temp",Prev);
         //   if( trackObject )
		trackedPatch=patches;//trackWindow;
		if(First)
		{
			baseresponse=1.0/Score;
			First=false;
		}
		Score=Score*baseresponse;
		
			counterFrames++;
			if((counterFrames==20)&&((Score>0.80)))
		
			{
				if((patches.x>0) && (patches.y>0))
					{
						if((patches.x<image.cols-patches.width) && (patches.y<image.rows-patches.height))
							{
							//	UpdateTemplate(image,patches);
							
						}
				}
					counterFrames=0;
			}			
		if (counterFrames==20)
					
			counterFrames=0;
		//patches=trackWindow ;
      return (std::abs(Score)>0.85);
    }

    Rect
    PhaseCorrTracker::getTrackingROI(float searchFactor)
    {
      Rect searchRegion;

      searchRegion = RectMultiply_phasecorr(trackedPatch, searchFactor);
      //check
      if (searchRegion.y + searchRegion.height > validROI.height)
        searchRegion.height = validROI.height - searchRegion.y;
      if (searchRegion.x + searchRegion.width > validROI.width)
        searchRegion.width = validROI.width - searchRegion.x;

      return searchRegion;
    }

    float
    PhaseCorrTracker::getConfidence()
    {
      return  (float)Score;// confidence / classifier->getSumAlpha();
    }
	
    Rect
    PhaseCorrTracker::getTrackedPatch()
    {
      return trackedPatch;
    }

    cv::Point2i
    PhaseCorrTracker::getCenter()
    {
      cv::Point2i center;
      center.y = trackedPatch.y + trackedPatch.height / 2;
      center.x = trackedPatch.x + trackedPatch.width / 2;
      return center;
    }


//---------------------------------------------------------------------------------------------------------------------------------------
  }
}