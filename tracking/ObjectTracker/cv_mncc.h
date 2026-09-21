//M*/

#ifndef __OPENCV_MNCC_H__
#define __OPENCV_MNCC_H__

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace cv
{
  namespace mnormcctracker
  {
  	//added Modified Normalized Cross Correlation
	class MNORMCCTracker
    {
    public:

      MNORMCCTracker(cv::Mat& image, Rect initPatch);//, Rect validROI, int numBaseClassifier);
	  void UpdateTemplate(cv::Mat& image, Rect initPatch);
      virtual ~MNORMCCTracker();

      bool track(cv::Mat&  image, Rect& patches);
	 
      cv::Rect  getTrackingROI(float searchFactor);
      float  getConfidence();
      cv::Rect   getTrackedPatch();
      cv::Point2i  getCenter();
	  cv::Mat GetTemplate(){return p_template;};

	private:
		 cv::Point2f p_position;
		 
		 cv::Size p_size;
		 
		 float p_window;
		 
		 cv::Mat p_template;
		 
		 double Score;

		int counterFrames;

		Rect trackWindow;
		 
		Rect validROI;

		Rect trackedPatch;
		
		float confidence;

    };
	//------------------------------------------------------------------------

  }
}

#endif  // #ifndef __OPENCV_MNCC_H__
/* End of file. */