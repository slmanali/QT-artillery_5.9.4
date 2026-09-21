//M*/

#ifndef __OPENCV_phasecorr_H__
#define __OPENCV_phasecorr_H__

//#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "cv_onlineboosting.h"
namespace cv
{
  namespace phasecorrtracker
  {
  	//added tracker_name_class
	class PhaseCorrTracker
    {
    public:
	  bool First;
	  double baseresponse;
      PhaseCorrTracker(cv::Mat& image, Rect initPatch);//, Rect validROI, int numBaseClassifier);
	  void UpdateTemplate(cv::Mat& image, Rect initPatch);
      virtual
      ~PhaseCorrTracker();

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

#endif  // #ifndef __OPENCV_phasecorr_H__
/* End of file. */