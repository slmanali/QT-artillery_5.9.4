// stitching4iSpy.cpp : Defines the exported functions for the DLL application.
//

//#include "opencvCSharpInterface.h"
#include "opencv2/highgui/highgui.hpp"
#include  "tracker_api.h"
//#include <windows.h>


const int size_of_window=120; 

using namespace std;
//using namespace cv;



 bool tracker_api::setTrackerAlgorithm(int TrackingAlgo)
{

	return true;
}

 bool tracker_api::InitTracker(IplImage Image,cv::Rect BoundinBox)
{
	//-----------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------

	int *initialBB=NULL;
	//cv::namedWindow ("ini");
	//imshow("ini",cvarrToMat(&Image));
	//cv::waitKey();

	IplImage *img=cvCloneImage(&Image);//////////////////////////////////////// = imAcqGetImg(imAcq);
 
    //Mat grey(img->height, img->width, CV_8UC1);
	Mat grey(img->height, img->width, CV_8UC3);
    //cvtColor(cvarrToMat(img), grey, CV_BGR2GRAY);
///////	cvtColor(cvarrToMat(img), grey, CV_BGR2RGB);
   /* cv::namedWindow ("ini2");
	imshow("ini2",grey);
	cv::waitKey();*/

	
	// return true;
	 CvRect box;
	 box=BoundinBox;
	
	
        if(initialBB == NULL)
        {
            initialBB = new int[4];
        }

        initialBB[0] = box.x;
        initialBB[1] = box.y;
        initialBB[2] = box.width;
        initialBB[3] = box.height;
    
 // cv::namedWindow ("ini3");
	//imshow("ini3",cvarrToMat(img));
	//cv::waitKey();
    Mat ImgMat=cvarrToMat(img);
    bool pp=  tracker->initialize( ImgMat/*grey*/, BoundinBox);
	

	return pp;
    	return true;
//    bool reuseFrameOnce = false;
  //  bool skipProcessingOnce = false;

	  //return true;
}
//-----------------------------------------------------------------------------------------------
bool tracker_api::InitTracker_(cv::Mat Image,cv::Rect BoundinBox)
{
	//-----------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------

	int *initialBB=NULL;

	 CvRect box;
	 
	 box=BoundinBox;
	
	
        if(initialBB == NULL)
        {
            initialBB = new int[4];
        }

        initialBB[0] = box.x;
        initialBB[1] = box.y;
        initialBB[2] = box.width;
        initialBB[3] = box.height;

	   Rect ROW;
		Point center;
		center.x=box.x+(box.width>>1);
		center.y=box.y+(box.height>>1);
		ROW.x=(center.x-size_of_window)>0?center.x-size_of_window:0;
		ROW.y=(center.y-size_of_window)>0?center.y-size_of_window:0;
		if((center.x+size_of_window)>Image.cols)
		{
           ROW.x=Image.cols-2*size_of_window-1;
		}
		if((center.y+size_of_window)>Image.rows)
		{
			ROW.y=Image.rows-2*size_of_window-1;
		}
        ROW.width=2*size_of_window;
        ROW.height=2*size_of_window;
	//	ROW.width=(center.x+size_of_window)<Image.cols-2?(2*size_of_window):size_of_window-center.x+Image.cols-2;
	//	ROW.height=(center.y+size_of_window)<Image.rows-2?(2*size_of_window):size_of_window-center.y+Image.rows-2;
		Mat ImageOW=Image(ROW);
		Mat Search;
		ImageOW.copyTo(Search);
		Rect Box;
		Box.x=BoundinBox.x-ROW.x;//(ImageOW.cols>>1)-(BoundinBox.width>>1);
		Box.y=BoundinBox.y-ROW.y;//(ImageOW.rows>>1)-(BoundinBox.height>>1);
		Box.width=BoundinBox.width;
		Box.height=BoundinBox.height;
     bool pp=  tracker->initialize(Search/*img/*grey*/,Box);
	// bool pp=  tracker->initialize(ImageOW/*img/*grey*/, BoundinBox);
	return pp;
    //	return true;  //omar

}
 cv::Mat tracker_api::returnTemp(){
	 return(tracker->Template );
 }

//-----------------------------------------------------------------------------------------------
 bool tracker_api::CreateTracker(int TrackingAlgo){


	cv::ObjectTrackerParams params;
	switch (TrackingAlgo){
		case 1: //CV_ONLINEBOOSTING
			params.algorithm_ = cv::ObjectTrackerParams::CV_ONLINEBOOSTING;
		break;
		case 2: //:CV_LINEMOD
			params.algorithm_ = cv::ObjectTrackerParams::CV_LINEMOD;
		break;

		case 3: //:CV_SEMIONLINEBOOSTING
			params.algorithm_ = cv::ObjectTrackerParams::CV_SEMIONLINEBOOSTING;
		break;
		case 4: //: CV_ONLINEMIL
			params.algorithm_ = cv::ObjectTrackerParams:: CV_ONLINEMIL;
			break;		
		case 5:params. algorithm_ = cv::ObjectTrackerParams:: CV_CAMSHIFT;
		break;
		case 6:params. algorithm_ = cv::ObjectTrackerParams:: CV_PHASECORR;
		break;
		case 7:params. algorithm_ = cv::ObjectTrackerParams:: CV_NCC;
		break;

		case 8:params. algorithm_ = cv::ObjectTrackerParams:: CV_TLD;
			break;
		case 9:params.algorithm_=cv::ObjectTrackerParams::CV_CMT;
			break;
		 case 10:params.algorithm_=cv::ObjectTrackerParams::CV_CT;
			break;
		 case 11:params.algorithm_=cv::ObjectTrackerParams::CV_STRUCK;
			break;

	}

	 
// params.algorithm_= cv::ObjectTrackerParams::CV_LINEMOD;
  //params.algorithm_ = cv::ObjectTrackerParams::CV_SEMIONLINEBOOSTING;
   if(TrackingAlgo==1)
   {
	params.num_classifiers_ = 250; //150
     params.num_features_ =350;//250;
     params.overlap_ = 0.95f;  //0.99f
     params.search_factor_ = 2.0;
	 params.neg_num_train_ =15;
   }
   else
   {
	   if(TrackingAlgo==4)
	   {
		  
           params.algorithm_ = cv::ObjectTrackerParams::CV_ONLINEMIL;
           params.num_classifiers_ = 50;
           params.num_features_ = 250;
	   }
   }


 // Instantiate an object tracker
	 //cv::namedWindow("beforecreate");
	 //cv::waitKey ();
     tracker=new cv::ObjectTracker (params);
	 if(tracker!=NULL)
	 {
	//	  cv::namedWindow("Aftercreate");
	//cv::waitKey ();
	 }


    

	return true;
}

bool tracker_api::deleteTracker(){
	if(tracker)
	  delete tracker;
	return true;
}




 bool tracker_api::UpdateTracker(IplImage Image,cv::Rect &BoundinBox,float & conf){
	cv::Mat frame=cvarrToMat(&Image);
	cv::Mat grey;
		/*Rect ROW;
		Point center;
		center.x=BoundinBox.x+(BoundinBox.width>>1);
		center.y=BoundinBox.y+(BoundinBox.height>>1);
		ROW.x=(center.x-size_of_window)<0?center.x-size_of_window:0;
		ROW.y=(center.y-size_of_window)<0?center.y-size_of_window:0;
		ROW.width=(center.x+size_of_window)>frame.cols?(2*size_of_window):size_of_window-center.x+frame.cols;
		ROW.height=(center.y+size_of_window)>frame.rows?(2*size_of_window):size_of_window-center.y+frame.rows;
		Mat ImageOW=frame(ROW);	
		BoundinBox.x=(ImageOW.cols>>1)-(BoundinBox.width>>1);
		BoundinBox.y=(ImageOW.rows>>1)-(BoundinBox.height>>1);*/
	return tracker->update( frame, BoundinBox,conf);
	
}
bool tracker_api::UpdateTracker_(cv::Mat& frame,cv::Rect &BoundinBox,float & conf){

			Rect ROW;
		Point center;
		center.x=BoundinBox.x+(BoundinBox.width>>1);
		center.y=BoundinBox.y+(BoundinBox.height>>1);
		ROW.x=(center.x-size_of_window)>0?center.x-size_of_window:0;
		ROW.y=(center.y-size_of_window)>0?center.y-size_of_window:0;
		if((center.x+size_of_window)>frame.cols)
		{
           ROW.x=frame.cols-2*size_of_window-1;
		}
		if((center.y+size_of_window)>frame.rows)
		{
			ROW.y=frame.rows-2*size_of_window-1;
		}
        ROW.width=2*size_of_window;
        ROW.height=2*size_of_window;
		//ROW.width=(center.x+size_of_window)<frame.cols-2?(2*size_of_window):size_of_window-center.x+frame.cols-2;
		//ROW.height=(center.y+size_of_window)<frame.rows-2?(2*size_of_window):size_of_window-center.y+frame.rows-2;
		Mat ImageOW=frame(ROW);	
		Mat Search;
		ImageOW.copyTo(Search);
		Rect Box;
		Box.x=BoundinBox.x-ROW.x;//(ImageOW.cols>>1)-(BoundinBox.width>>1);
		Box.y=BoundinBox.y-ROW.y;//(ImageOW.rows>>1)-(BoundinBox.height>>1);
		Box.width=BoundinBox.width;
		Box.height=BoundinBox.height;
	//return tracker->update( Search, BoundinBox,conf);
		bool pp= tracker->update( Search, Box,conf);
		BoundinBox.x=Box.x+ROW.x;
		BoundinBox.y=Box.y+ROW.y;
		BoundinBox.height=Box.height;
		BoundinBox.width=Box.width;
		//cout<<"BOX="<<Box<<endl;
		//cout<<"ROW="<<ROW<<endl;
		return pp;

	
}

bool tracker_api::FreeMIplImageptr(IplImage** image){
	cvReleaseImage(image);

	return true;
}




