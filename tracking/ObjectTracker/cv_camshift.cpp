//M*/
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"

#include "cv_camshift.h"
using namespace std;
//using namespace cv;
namespace cv
{
  namespace camshifttracker
  {
   cv::Rect RectMultiply_camshift(const cv::Rect & rect, float f)
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

	CamShiftTracker::CamShiftTracker(cv::Mat&  image, Rect initPatch, Rect validROI, int numBaseClassifier)// must be colored image
    {
		///---------------------------------------------------------------------------------------------------------------
	//cv::waitKey ();
		hsize = 16;
        hranges[0] = 0;
		hranges[1] = 180;
		phranges = hranges;
	    vmin = 20;
		vmax = 221;
		smin = 55;
///////////////////		Mat maskroi;
		//{0,180};
		int _vmin = vmin, _vmax = vmax;
		histimg = Mat::zeros(200, 320, CV_8UC3);
		cvtColor(image, hsv, CV_BGR2HSV);
	
		 inRange(hsv, Scalar(0, smin, MIN(_vmin,_vmax)),
                        Scalar(180, 256, MAX(_vmin, _vmax)), mask);
                int ch[] = {0, 0};
                hue.create(hsv.size(), hsv.depth());
	            mixChannels(&hsv, 1, &hue, 1, ch, 1);
				//cv::namedWindow ("objinit44");
				//////////////////initPatch.width=140;
				//////////////////initPatch.height=140;

	//			rectangle(image,initPatch,Scalar(255,0,0),5);
	//imshow ("objinit44",image);
//	cv::waitKey ();
    
		//if( trackObject < 0 )// new bounding box
  /*							cv::namedWindow ("objinit11_");
	imshow ("objinit11_",hue);
	cv::waitKey ();   
	*///////////////initPatch.x=25;initPatch.x=65;
	//////////////initPatch.width=100;initPatch.height=100;



                    Mat roi(hue, initPatch);
/*								cv::namedWindow ("objinit44_");
	imshow ("objinit44_",roi);
	cv::waitKey ();
   */ 
					Mat maskroi(mask, initPatch);
                    calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
	//							cv::namedWindow ("objinit44__");
	//imshow ("objinit44__",image);
	//cv::waitKey ();
 //   
                    normalize(hist, hist, 0, 255, CV_MINMAX);
									/*cv::namedWindow ("objinit4");
	imshow ("objinit4",image);
	cv::waitKey ();*/
	
                    trackWindow = initPatch;
          ////////////////////////////////////////          trackObject = 1;

                    histimg = Scalar::all(0);
                    int binW = histimg.cols / hsize;
                    Mat buf(1, hsize, CV_8UC3);
                    for( int i = 0; i < hsize; i++ )
                        buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);
                    cvtColor(buf, buf, CV_HSV2BGR);
	//								cv::namedWindow ("objinit5");
	//imshow ("objinit5",image);
	//cv::waitKey ();
	
                    for( int i = 0; i < hsize; i++ )
                    {
                        int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);
                        rectangle( histimg, Point(i*binW,histimg.rows),
                                   Point((i+1)*binW,histimg.rows - val),
                                   Scalar(buf.at<Vec3b>(i)), -1, 8 );
                    }
                
//								cv::namedWindow ("objinit6");
//	imshow ("objinit6",image);
//	cv::waitKey ();
	
		//////------------------------------------------------------------------------------------------------------------
  //////////////    int numWeakClassifier = numBaseClassifier * 10;
  //////////////    bool useFeatureExchange = true;
  //////////////    int iterationInit = 15;//was 50
  //////////////    cv::Size patchSize(initPatch.width, initPatch.height);

  //////////////    this->validROI = validROI;

  //////////////    classifier = new StrongClassifierDirectSelection(numBaseClassifier, numWeakClassifier, patchSize,
  //////////////                                                     useFeatureExchange, iterationInit);

  //////////////    detector = new Detector(classifier);

  //////////////    trackedPatch = initPatch;
  //////////////    Rect trackingROI = getTrackingROI(2.0f);
  //////////////    cv::Size trackedPatchSize(trackedPatch.width, trackedPatch.height);
  //////////////    Patches* trackingPatches = new PatchesRegularScan(trackingROI, validROI, trackedPatchSize, 0.99f);
	 ////////////// double t=(double)getTickCount();
  //////////////    iterationInit = 150;//was 5050;
  //////////////    for (int curInitStep = 0; curInitStep < iterationInit; curInitStep++)
  //////////////    {
  //////////////std::cout << "\rinit tracker... " << int(((float) curInitStep) / (iterationInit - 1) * 100) << " %%";

  //////////////      classifier->update(image, trackingPatches->getSpecialRect("UpperLeft"), -1);
  //////////////      classifier->update(image, trackedPatch, 1);
  //////////////      classifier->update(image, trackingPatches->getSpecialRect("UpperRight"), -1);
  //////////////      classifier->update(image, trackedPatch, 1);
  //////////////      classifier->update(image, trackingPatches->getSpecialRect("LowerLeft"), -1);
  //////////////      classifier->update(image, trackedPatch, 1);
  //////////////      classifier->update(image, trackingPatches->getSpecialRect("LowerRight"), -1);
  //////////////      classifier->update(image, trackedPatch, 1);
  //////////////    }
	 ////////////// cout<<"time="<<(((double)getTickCount()-t)/getTickFrequency())*1000<<"ms"<<"\n" <<endl;
  //////////////    confidence = -1;
  //////////////    delete trackingPatches;

    }

    CamShiftTracker::~CamShiftTracker(void)
    {
		//////////////////////////cv::destroyWindow("BackProj");
      //delete detector;
      //delete classifier;
    }

    bool
    CamShiftTracker::track(cv::Mat&  image, Rect& patches)
    {
		//image->
		
		           cvtColor(image, hsv, CV_BGR2HSV);
				bool trackedbool=false;
         //   if( trackObject )
            {

                int _vmin = vmin, _vmax = vmax;

                inRange(hsv, Scalar(0, smin, MIN(_vmin,_vmax)),
                        Scalar(180, 256, MAX(_vmin, _vmax)), mask);
                int ch[] = {0, 0};
                hue.create(hsv.size(), hsv.depth());
                mixChannels(&hsv, 1, &hue, 1, ch, 1);

                
                calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
                backproj &= mask;
				//------------------------------------------
				if(trackWindow.width<1)trackWindow.width=20;
				if(trackWindow.height<1)trackWindow.height=20;

				//-----------------------------------------
                RotatedRect trackBox = CamShift(backproj, trackWindow,
                                    TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));
                if( trackWindow.area() <= 1 )
                {
                    int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5)/6;
                    trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
                                       trackWindow.x + r, trackWindow.y + r) &
                                  Rect(0, 0, cols, rows);
					std::cout <<trackWindow<<endl;
					trackedbool=true;
				//	cv::waitKey ();
                }

//                if( backprojMode )
  //                  cvtColor( backproj, image, CV_GRAY2BGR );
               // ellipse( image, trackBox, Scalar(0,0,255), 3, CV_AA );
				trackedPatch.x=trackWindow.x;
				trackedPatch.y=trackWindow.y;
				trackedPatch.width=trackWindow.width;
				trackedPatch.height=trackWindow.height;

			//////////////////////////	cv::namedWindow ("BackProj");
			////////////////////////////	imshow("BackProj",backproj);
            }
       
 
      //  if( selectObject && selection.width > 0 && selection.height > 0 )
        {
       ///////////////////////     Mat roi(image, selection);
       //////////////////////     bitwise_not(roi, roi);
        }
      ////////////detector->classify (image, patches);
      //////////detector->classifySmooth(image, patches);

      ////////////move to best detection
      //////////if (detector->getNumDetections() <= 0)
      //////////{
      //////////  confidence = 0;//omar
      //////////  return false;
      //////////}

      //////////trackedPatch = patches->getRect(detector->getPatchIdxOfBestDetection());
      //////////confidence = detector->getConfidenceOfBestDetection();

      //////////classifier->update(image, patches->getSpecialRect("UpperLeft"), -1);
      //////////classifier->update(image, trackedPatch, 1);
      //////////classifier->update(image, patches->getSpecialRect("UpperRight"), -1);
      //////////classifier->update(image, trackedPatch, 1);
      //////////classifier->update(image, patches->getSpecialRect("UpperLeft"), -1);
      //////////classifier->update(image, trackedPatch, 1);
      //////////classifier->update(image, patches->getSpecialRect("LowerRight"), -1);
      //////////classifier->update(image, trackedPatch, 1);

      return !trackedbool;
    }

    Rect
    CamShiftTracker::getTrackingROI(float searchFactor)
    {
      Rect searchRegion;

      searchRegion =RectMultiply_camshift(trackedPatch, searchFactor);
      //check
      if (searchRegion.y + searchRegion.height > validROI.height)
        searchRegion.height = validROI.height - searchRegion.y;
      if (searchRegion.x + searchRegion.width > validROI.width)
        searchRegion.width = validROI.width - searchRegion.x;

      return searchRegion;
    }

    float
    CamShiftTracker::getConfidence()
    {
      return  true;// confidence / classifier->getSumAlpha();
    }
	cv::Mat CamShiftTracker::GetBackProj()
	{
		return backproj;
	}
    Rect
    CamShiftTracker::getTrackedPatch()
    {
      return trackedPatch;
    }

    cv::Point2i
    CamShiftTracker::getCenter()
    {
      cv::Point2i center;
      center.y = trackedPatch.y + trackedPatch.height / 2;
      center.x = trackedPatch.x + trackedPatch.width / 2;
      return center;
    }

	//------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
  }
}