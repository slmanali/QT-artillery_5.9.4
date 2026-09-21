//M*/

#ifndef __OPENCV_camshift_H__
#define __OPENCV_camshift_H__

//#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "cv_onlineboosting.h"
namespace cv
{
  namespace camshifttracker
  {
  	//added tracker_name_class
	//---------------------------------- added here -------------------------------
	class CamShiftTracker
    {
    public:
      CamShiftTracker(cv::Mat& image, Rect initPatch, Rect validROI, int numBaseClassifier);
      virtual
      ~CamShiftTracker();

      bool
        track(cv::Mat&  image, Rect& patches);
	  cv::Mat GetBackProj();
      cv::Rect  getTrackingROI(float searchFactor);
      float  getConfidence();
      cv::Rect   getTrackedPatch();
      cv::Point2i  getCenter();
    //  const cv::Mat &
    //  getConfImageDisplay() const
    //  {
    //    //return detector->getConfImageDisplay();
		  //return true;
    //  }

    private:
		Mat frame, hsv, hue, mask, hist, histimg , backproj;

		Rect trackWindow;
    int hsize ;
    float hranges[2];
    const float* phranges ;
	int vmin , vmax , smin ;
   // CommandLineParser parser(argc, argv, keys);


      //StrongClassifier* classifier;
      //Detector* detector;
      Rect validROI;
      Rect trackedPatch;
      float confidence;
      cv::Point2i dxDy;
    };
//------------------------------------------------------------------------


    }
	//------------------------------------------------------------------------

  }


#endif  // #ifndef __OPENCV_camshift_H__
/* End of file. */