//M*/
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"

#include "cv_mncc.h"
using namespace std;
//using namespace cv;
namespace cv
{
  namespace mnormcctracker
  {

//---//------------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------------------------
	//Modified Normalized Cross Correlation
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

	  double round( double d )
	  {
		  return floor( d + 0.5 );
	  }
	  
	MNORMCCTracker::MNORMCCTracker(cv::Mat&  image, Rect initPatch)//, Rect validROI, int numBaseClassifier)// must be colored image
    {
		p_window = MAX(initPatch.width, initPatch.height) * 2;

        cv::Mat gray;
        cv::cvtColor(image, gray, CV_BGR2GRAY);

        int left = MAX(initPatch.x, 0);
        int top = MAX(initPatch.y, 0);

        int right = MIN(initPatch.x + initPatch.width, gray.cols - 1);
        int bottom = MIN(initPatch.y + initPatch.height, gray.rows - 1);

        cv::Rect roi(left, top, right - left, bottom - top);

        gray(roi).copyTo(p_template);

        p_position.x = (float)initPatch.x + (float)initPatch.width / 2;
        p_position.y = (float)initPatch.y + (float)initPatch.height / 2;

        p_size = cv::Size2f(initPatch.width, initPatch.height);


    }

    MNORMCCTracker::~MNORMCCTracker(void)
    {
		cv::destroyWindow("temp");
    }
	void MNORMCCTracker::UpdateTemplate(cv::Mat&  image, Rect initPatch)
	{
		trackWindow = initPatch;
		Mat curr;
		curr=image(trackWindow);
		p_template = curr.clone();
		cvtColor(p_template,p_template,CV_RGB2GRAY);

	}
    bool  MNORMCCTracker::track(cv::Mat&  image, Rect& patches)
    {
		cv::Mat gray;
        cv::cvtColor(image, gray, CV_BGR2GRAY);

        float left = MAX(round(p_position.x - (float)p_window / 2), 0);
        float top = MAX(round(p_position.y - (float)p_window / 2), 0);

        float right = MIN(round(p_position.x + (float)p_window / 2), gray.cols - 1);
        float bottom = MIN(round(p_position.y + (float)p_window / 2), gray.rows - 1);

        cv::Rect roi((int) left, (int) top, (int) (right - left), (int) (bottom - top));

        if (roi.width < p_template.cols || roi.height < p_template.rows) {
            cv::Rect result;

            result.x = p_position.x - p_size.width / 2;
            result.y = p_position.y - p_size.height / 2;
            result.width = p_size.width;
            result.height = p_size.height;
            trackWindow=result;
			return true;

        }

        cv::Mat matches;
        cv::Mat cut = gray(roi);
		double minVal, maxVal;
		Point minLoc, maxLoc;
        cv::matchTemplate(cut, p_template, matches, CV_TM_CCOEFF_NORMED);

        cv::Point matchLoc;
        cv::minMaxLoc(matches, NULL, &maxVal, NULL, &matchLoc, cv::Mat());

        cv::Rect result;

        p_position.x = left + matchLoc.x + (float)p_size.width / 2;
        p_position.y = top + matchLoc.y + (float)p_size.height / 2;

        result.x = left + matchLoc.x;
        result.y = top + matchLoc.y;
        result.width = p_size.width;
        result.height = p_size.height;
		trackWindow=result;
		return (std::abs(maxVal)>0.85);
    }

    Rect
    MNORMCCTracker::getTrackingROI(float searchFactor)
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
    MNORMCCTracker::getConfidence()
    {
      return  (float)Score;// confidence / classifier->getSumAlpha();
    }
	
    Rect
    MNORMCCTracker::getTrackedPatch()
    {
      return trackedPatch;
    }

    cv::Point2i
    MNORMCCTracker::getCenter()
    {
      cv::Point2i center;
      center.y = trackedPatch.y + trackedPatch.height / 2;
      center.x = trackedPatch.x + trackedPatch.width / 2;
      return center;
    }
//---------------------------------------------------------------------------------------------------------------------------------------
  }
}