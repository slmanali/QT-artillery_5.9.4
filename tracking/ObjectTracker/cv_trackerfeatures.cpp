//M*/
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"

#include "cv_trackerfeatures.h"
using namespace std;
//using namespace cv;
namespace cv
{
  namespace featuresTracker
  {
	FeaturesTracker::FeaturesTracker(cv::Mat&  image, Rect initPatch, Rect validROI, int numBaseClassifier)// must be colored image
    {
		
    }

    FeaturesTracker::~FeaturesTracker(void)
    {
		
    }

    bool
    FeaturesTracker::track(cv::Mat&  image, Rect& patches)
    {
		std::cout<<"FeatureTracker  Update      "<<endl;
		bool bvalid;
	  return bvalid;
    }



//---------------------------------------------------------------------------------------------------------------------------------------
  }
}