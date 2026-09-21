//M*/

#ifndef __OPENCV_tracker_name_H__
#define __OPENCV_tracker_name_H__

//#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cv_onlineboosting.h"
namespace cv
{
  namespace featuresTracker
  {
  	//added tracker_name_class
	class FeaturesTracker
    {
		public:
		FeaturesTracker(cv::Mat& image, Rect initPatch, Rect validROI, int numBaseClassifier);
      virtual
      ~FeaturesTracker();

		bool track(cv::Mat&  image, Rect& patches);
    private:

    };
	//------------------------------------------------------------------------

  }
}

#endif  // #ifndef __OPENCV_tracker_name_H__
/* End of file. */