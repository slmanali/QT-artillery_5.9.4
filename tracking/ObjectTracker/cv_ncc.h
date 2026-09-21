//M*/

#ifndef __OPENCV_NCC_H__
#define __OPENCV_NCC_H__

//#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "cv_onlineboosting.h"
namespace cv
{
  namespace normcctracker
  {
  	//added Normalized Cross Correlation
	class NORMCCTracker
    {
    public:
	  bool First;
	  double baseresponse;
      NORMCCTracker(cv::Mat& image, Rect initPatch);//, Rect validROI, int numBaseClassifier);
	  void UpdateTemplate(cv::Mat& image, Rect initPatch);
      virtual
      ~NORMCCTracker();

      bool
        track(cv::Mat&  image, Rect& patches);
	 
      cv::Rect  getTrackingROI(float searchFactor);
      float  getConfidence();
      cv::Rect   getTrackedPatch();
      cv::Point2i  getCenter();
	  cv::Mat GetTemplate(){return Prev;};
    //  const cv::Mat &
    //  getConfImageDisplay() const
    //  {
    //    //return detector->getConfImageDisplay();
		  //return true;
    //  }

    private:
		Mat frame;
		Mat Prev;
		 Mat hann;
		Rect trackWindow;
		double Score;
  

      //StrongClassifier* classifier;
      //Detector* detector;
		int counterFrames;
      Rect validROI;
      Rect trackedPatch;
      float confidence;
      cv::Point2i dxDy;
    };
	//------------------------------------------------------------------------

  }
}

#endif  // #ifndef __OPENCV_TLD_H__
/* End of file. */