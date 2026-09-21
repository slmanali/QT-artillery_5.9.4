//M*/
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"

#include "cv_tld.h"
using namespace std;
//using namespace cv;

#define sign(x) (((x)>=0)? 1.0f : -1.0f)

/****************************************************************************************
 COPYRIGHT NOTICE
 ----------------

 The code has been derived from: http://www.vision.ee.ethz.ch/boostingTrackers/
 By Helmut Grabner, Van Gool Luc, Severin Stalder, Michael Grabner, Christian Leistner
 The agreement to put it in OpenCV under the BSD license is at the end of hat file

 ****************************************************************************************/

namespace cv
{
  namespace tldtracker
  {
//------------------------------------------------------------------------------------------------------------------------------------------

TLDTracker::TLDTracker(cv::Mat&  image, Rect initPatch, Rect validROI, int numBaseClassifier)// must be colored image
    {
		///---------------------------------------------------------------------------------------------------------------
		tld=new tld::TLD();




		/*--------------------------------*/
		tld->trackerEnabled =true;// m_settings.m_trackerEnabled;

		///////////////mythreshold =0.7;// m_settings.m_threshold;
    tld->alternating = false;//m_settings.m_alternating;
    tld->learningEnabled =true;// m_settings.m_learningEnabled;

	 
    tld->detectorCascade->varianceFilter->enabled = true;//m_settings.m_varianceFilterEnabled;
    tld->detectorCascade->ensembleClassifier->enabled =true;// m_settings.m_ensembleClassifierEnabled;
    tld->detectorCascade->nnClassifier->enabled = true;//m_settings.m_nnClassifierEnabled;

    // classifier
    tld->detectorCascade->useShift =true;// m_settings.m_useProportionalShift;
    tld->detectorCascade->shift =0.1;// was 10;// m_settings.m_proportionalShift;
    tld->detectorCascade->minScale = -10;//m_settings.m_minScale;
    tld->detectorCascade->maxScale =10;// m_settings.m_maxScale;
    tld->detectorCascade->minSize = 25;//m_settings.m_minSize;
    tld->detectorCascade->numTrees = 10;//m_settings.m_numTrees;
    tld->detectorCascade->numFeatures =15;// m_settings.m_numFeatures; //15
    tld->detectorCascade->nnClassifier->thetaTP =0.65;// m_settings.m_thetaP;
    tld->detectorCascade->nnClassifier->thetaFP =0.7;// m_settings.m_thetaN;


    	/*--------------------------------*/

		cv::Mat image1;
//		cvtColor(image, image1, CV_BGR2GRAY);
  	    cvtColor(image, image1, CV_RGB2GRAY);

		tld->detectorCascade ->imgHeight =image1.rows;
		tld->detectorCascade ->imgWidth = image1.cols;
		tld->detectorCascade->imgWidthStep = image1.step;
	/////////////////////////	tld->nnClassifier ->thetaFP =0.2;
	///////////////////	tld->nnClassifier ->thetaTP =0.7;
		
		   cv::Rect r(initPatch.x,initPatch.y,initPatch.width,initPatch.height);
		tld->selectObject (image1,&r);
		std::cout<<" width"<<r.width<<" ,"<<r.height<<std::endl;
		//tld->writeToFile("..\\..\\..\\template.txt");
		/////////////////////////////////////////////////////image1.copyTo (tld->detectorCascade ->foregroundDetector -> bgImg);
		//tld->detectorCascade ->foregroundDetector ->bgImg =image1.clone(); 
		image1.release();
	
      ValidConf=0.3;
	  UpdateConf=0.3;
	
    }
   cv::Rect RectMultiply_tld(const cv::Rect & rect, float f)
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

    TLDTracker::~TLDTracker(void)
    {
		 tld->release();
		 delete tld;
		 /*--------------------------------------------------------------------*/
		  /*storeCurrentData();

    if(tld->currBB)
    {
        delete tld->currBB;
        tld->currBB = NULL;
    }

    if(tld->detectorCascade)
    {
        delete detectorCascade;
        detectorCascade = NULL;
    }

    if(medianFlowTracker)
    {
        delete medianFlowTracker;
        medianFlowTracker = NULL;
    }

    if(prevBB)
    {
        delete prevBB;
        prevBB = NULL;
    }*/
		 /*--------------------------------------------------------------------*/
      //delete detector;
      //delete classifier;
    }

    bool
    TLDTracker::track(cv::Mat&  image, Rect& patches)
    {
/////////////////////////////////////////////////////////////		std::cout<<"TLD Update      "<<endl;
	//cv::Mat image1;
	 // cvtColor(image, image1, CV_BGR2GRAY);
		trackedPatch=patches;
	  tld->processImage (image);
	  bool bvalid;

 /*      if (tld->currConf >= 0.4){
		  //if(tld->currBB !=NULL){
		  bvalid=true;
		  cv::Rect Cr;
		  Cr.x=tld->currBB->x;
		  Cr.y=tld->currBB->y;
		  Cr.width=tld->currBB->width;
		  Cr.height=tld->currBB->height;
		  patches=Cr;
	  }
	  else
	  {
		  bvalid=false;
		  //_I Added here
		  if(!tld->currBB)
		  {
		     tld->currBB=new Rect();
             tld->currBB->x = tld->prevBB ->x;
             tld->currBB->y = tld->prevBB ->y;
             tld->currBB->width = tld->prevBB ->width;
             tld->currBB->height = tld->prevBB ->height;
    	  }
	  }*/
	   ValidConf=0.4;//was 0.3
	  UpdateConf=0.8;//was 0.3
	

       if (tld->currConf >= ValidConf){
		  //if(tld->currBB !=NULL){
		  bvalid=true;
		  if(tld->currConf >= UpdateConf)
		  {
		  cv::Rect Cr;
		  Cr.x=tld->currBB->x;
		  Cr.y=tld->currBB->y;
		  Cr.width=tld->currBB->width;
		  Cr.height=tld->currBB->height;
		  patches=Cr;
		  }
		  else
		  {
			if(!tld->currBB)
		    {
		      tld->currBB=new Rect();
              tld->currBB->x = tld->prevBB ->x;
              tld->currBB->y = tld->prevBB ->y;
              tld->currBB->width = tld->prevBB ->width;
              tld->currBB->height = tld->prevBB ->height;
    	    }
		  }

	  }
	  else
	  {
		  bvalid=false;
		  //_I Added here
		  if(!tld->currBB)
		  {
		     tld->currBB=new Rect();
             tld->currBB->x = tld->prevBB ->x;
             tld->currBB->y = tld->prevBB ->y;
             tld->currBB->width = tld->prevBB ->width;
             tld->currBB->height = tld->prevBB ->height;
    	  }
	  }

    
      return bvalid;
    }

    Rect
    TLDTracker::getTrackingROI(float searchFactor)
    {
      Rect searchRegion;

      searchRegion =RectMultiply_tld(trackedPatch, searchFactor);
      //check
      if (searchRegion.y + searchRegion.height > validROI.height)
        searchRegion.height = validROI.height - searchRegion.y;
      if (searchRegion.x + searchRegion.width > validROI.width)
        searchRegion.width = validROI.width - searchRegion.x;

      return searchRegion;
    }

    float
    TLDTracker::getConfidence()
    {
		float f=(tld->currConf );
      return  f;
    }
	
    Rect
      TLDTracker::getTrackedPatch()
    { 
		Rect r;
		if(tld->currBB!=NULL)
		{
		  r.x=tld->currBB->x;
		  r.y=tld->currBB->y;
		  r.width=tld->currBB->width;
		  r.height=tld->currBB->height;


		}
		else
			r=trackedPatch;
          
      return r ;
    }

    cv::Point2i
    TLDTracker::getCenter()
    {
      cv::Point2i center;
      center.y = trackedPatch.y + trackedPatch.height / 2;
      center.x = trackedPatch.x + trackedPatch.width / 2;
      return center;
    }
	}
	}

//=------------------------------------------------------------------------------------------------------------------------------------------
