/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2009-2011, Willow Garage Inc., all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include <iostream>
#include <ctime>
#include "object_tracker.h"
 Config conf;//(configPath);
namespace cv
{

  //---------------------------------------------------------------------------
  ObjectTrackerParams::ObjectTrackerParams()
  {
    // By default, use online boosting
    algorithm_ = CV_ONLINEBOOSTING;

    // Default number of classifiers/selectors for boosting algorithms
    num_classifiers_ = 150;

    // Default search region parameters for boosting algorithms
    overlap_ = 0.99f;
    search_factor_ = 2.0f;

    // Defaults for MIL tracker
    pos_radius_train_ = 4.0f;
    neg_num_train_ = 65;
    num_features_ = 200; //was 250
	init_tld_ = 0;
	threshold_type_ = 0;
  }

  //---------------------------------------------------------------------------
  ObjectTrackerParams::ObjectTrackerParams(const int algorithm, const int num_classifiers, const float overlap,
                                           const float search_factor, const float pos_radius_train,
                                           const int neg_num_train, const int num_features,const bool init_tld,const int threshold_type)
  {
    // Make sure a valid algorithm flag is used before storing it
    if ((algorithm != CV_ONLINEBOOSTING) && (algorithm != CV_SEMIONLINEBOOSTING) && (algorithm != CV_ONLINEMIL)
		&& (algorithm != CV_LINEMOD) && (algorithm != CV_CAMSHIFT) && (algorithm != CV_TLD) && (algorithm != CV_CMT) && (algorithm != CV_CT) && (algorithm != CV_STRUCK) && (algorithm != CV_MNCC) && (algorithm != CV_KCF) && (algorithm != CV_DSST) && (algorithm != CV_CFTLD) && (algorithm != CV_SKCF) && (algorithm != CV_Thresh) && (algorithm != CV_Mosse))
    {
      // Use CV_ERROR?
      std::cerr << "ObjectTrackerParams::ObjectTrackerParams(...) -- ERROR!  Invalid algorithm choice.\n";
      exit(-1);
    }
    // Store it
    algorithm_ = algorithm;

    // Store the number of weak classifiers (any error checking done here?)
    num_classifiers_ = num_classifiers;

    // Store information about the searching 
    overlap_ = overlap;
    search_factor_ = search_factor;

    // MIL parameters
    pos_radius_train_ = pos_radius_train;
    neg_num_train_ = neg_num_train;
    num_features_ = num_features;
	 init_tld_=init_tld;
	 threshold_type_ = threshold_type;
  }

  //
  //
  //

  //---------------------------------------------------------------------------
  TrackingAlgorithm::TrackingAlgorithm()
  {
  }

  //---------------------------------------------------------------------------
  TrackingAlgorithm::~TrackingAlgorithm()
  {
  }

  //
  //
  //
  ///////////////////////////////////////////////////////////////////////////////////
   //---------------------------------------------------------------------------
  CamShiftAlgorithm::CamShiftAlgorithm()
      :
        TrackingAlgorithm(),
        tracker_(NULL),
        tracker_lost_(false)

  {
	  std::cout<<"Init Cam Shift"<<std::endl;
  }

  //---------------------------------------------------------------------------
  CamShiftAlgorithm::~CamShiftAlgorithm()
  {
    if (tracker_ != NULL)
    {
      delete tracker_;
      tracker_ = NULL;
    }

  }

  //---------------------------------------------------------------------------
  bool
  CamShiftAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
                                      const CvRect& init_bounding_box)
  {
    // Import the image
	  	cv::Mat image1=image;
		cv::Rect BoundingBox=init_bounding_box;
	//  cv::namedWindow ("objinit0");
	//  cv::rectangle(image1,BoundingBox,cv::Scalar(255,255,255),3);
//	imshow ("objinit0",image1);
///	cv::waitKey ();
    import_image(image);

    // If the boosting tracker has already been allocated, first de-allocate it
    if (tracker_ != NULL)
    {
      std::cerr
          << "CamShiftAlgorithm::initialize(...) -- WARNING!  Boosting tracker already initialized.  Resetting now...\n"
          << std::endl;
      delete tracker_;
      tracker_ = NULL;
    }


//     (Re-)Initialize the boosting tracker
    cv::Size imageSize(image_.cols, image_.rows);
 //   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
    cv::Rect tracking_rect = init_bounding_box;
    tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);

//	cv::namedWindow ("objinit1");
	///////////////////////////////////////////rectangle(image1,BoundingBox,cv::Scalar(0,0,255),3);
	//imshow ("objinit1",image1);
	std::cout <<init_bounding_box.x<<","<<init_bounding_box.y<<" "<< init_bounding_box.width <<","<<init_bounding_box.height <<std::endl ;
//	cv::waitKey ();
    tracker_ = new camshifttracker::CamShiftTracker(image1, BoundingBox, wholeImage, params.num_classifiers_);

 ////////////////////   // Initialize some useful tracking debugging information
 ////////////////////   tracker_lost_ = false;
	////////////////////cv::namedWindow ("afterinit");
	////////////////////rectangle(image1,init_bounding_box,cv::Scalar(0,0,255),3);
	////////////////////imshow ("afterinit",image1);
	//////////////////////std::cout <<init_bounding_box.x<<","<<init_bounding_box.y<<" "<< init_bounding_box.width <<","<<init_bounding_box.height <<std::endl ;
	////////////////////cv::waitKey ();
    
    // Return success

	return true;
  }
  void CamShiftAlgorithm::import_image(const cv::Mat & image)
  {
    // We want the internal version of the image to be gray-scale, so let's
    // do that here.  We'll handle cases where the input is either RGB, RGBA,
    // or already gray-scale.  I assume it's already 8-bit.  If not then 
    // an error is thrown.  I'm not going to deal with converting properly
    // from every data type since that shouldn't be happening.

    // Make sure the input image pointer is valid
    if (image.empty())
    {
      std::cerr << "CamShiftAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
      exit(0); // <--- CV_ERROR?
    }

    // Now copy it in appropriately as a gray-scale, 8-bit image
    if (image.channels() == 4)
    {
      cv::cvtColor(image, image_, CV_RGBA2BGR);
    }
    else if (image.channels() == 3)
    {
      cv::cvtColor(image, image_, CV_RGB2BGR);
	  //image.copyTo (image_);
    }
    else if (image.channels() == 1)
    {
		cv::cvtColor(image, image_, CV_GRAY2BGR);
      //image.copyTo(image_);
    }
    else
    {
      std::cerr << "CamShiftAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
                << std::endl;
      exit(0);
    }
  }
  cv::Mat CamShiftAlgorithm::ReturnBackProj()
  {
	  if(tracker_)
	  {
	    return tracker_->GetBackProj();
	  }
  }
  //---------------------------------------------------------------------------
  bool
  CamShiftAlgorithm::update( const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box,float & confidence)
  {
    // Import the image
    import_image(image);

    // Make sure the tracker has already been successfully initialized
    if (tracker_ == NULL)
    {
      std::cerr
          << "CamShiftAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
          << std::endl;
      return false;
    }
    cv::Size imageSize(image.cols, image.rows);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
 //   boosting::Patches *trackingPatches;
    cv::Rect searchRegion = tracker_->getTrackingROI(params.search_factor_);
  //  trackingPatches = new boosting::PatchesRegularScan(searchRegion, wholeImage, tracking_rect_size_, params.overlap_);

    //cur_frame_rep_->setNewImageAndROI(image_, searchRegion);
     cv::Mat image1=image;
    if (!tracker_->track(image1, track_box))
    {
      tracker_lost_ = true;
//	  track_box = tracker_->getTrackedPatch();
    }
    else
    {

      tracker_lost_ = false;
    }

   // delete trackingPatches;

    // Save the new tracking ROI
    track_box = tracker_->getTrackedPatch();
	confidence= tracker_->getConfidence();
   /////////////////////////////////////////////////////////////should be output variable
	///////////////////////////////////////////////////////////////////////////////////////////////std::cout << "\rTracking confidence = " << tracker_->getConfidence();

    // Return success or failure based on whether or not the tracker has been lost
	if(track_box.width<20)track_box.width=20;
	if(track_box.height<20)track_box.height=20;
	if(track_box.x<0)track_box.x=0;
if(track_box.y<0)track_box.y=0;
if(track_box.x>image.cols-20)track_box.x=image.cols-20;
if(track_box.y>image.rows-20)track_box.y=image.rows-20;



    return !tracker_lost_;
  }




  //------------------------------------------------------------------------------
    //---------------------------------------------------------------------------
  // PHASE CORRELATOR Algo
 //---------------------------------------------------------------------------
  PhaseCorrAlgorithm::PhaseCorrAlgorithm()
      :
        TrackingAlgorithm(),
        tracker_(NULL),
        tracker_lost_(false)

  {
	  std::cout<<"Init phase Correlation"<<std::endl;
  }

  //---------------------------------------------------------------------------
  PhaseCorrAlgorithm::~PhaseCorrAlgorithm()
  {
    if (tracker_ != NULL)
    {
      delete tracker_;
      tracker_ = NULL;
    }

  }

  //---------------------------------------------------------------------------
  bool
  PhaseCorrAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
                                      const CvRect& init_bounding_box)
  {
    // Import the image
	  	cv::Mat image1=image;
		cv::Rect BoundingBox=init_bounding_box;
	//  cv::namedWindow ("objinit0");
	//  cv::rectangle(image1,BoundingBox,cv::Scalar(255,255,255),3);
//	imshow ("objinit0",image1);
///	cv::waitKey ();
    import_image(image);

    // If the boosting tracker has already been allocated, first de-allocate it
    if (tracker_ != NULL)
    {
      std::cerr
          << "PhaseCorrAlgorithm::initialize(...) -- WARNING!  Boosting tracker already initialized.  Resetting now...\n"
          << std::endl;
      delete tracker_;
      tracker_ = NULL;
    }


//     (Re-)Initialize the boosting tracker
    cv::Size imageSize(image_.cols, image_.rows);
 //   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
    cv::Rect tracking_rect = init_bounding_box;
    tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);

//	cv::namedWindow ("objinit1");
	/////////////////////////////////////////////////////////////////////////////rectangle(image1,BoundingBox,cv::Scalar(0,0,255),3);
	//imshow ("objinit1",image1);
    tracker_ = new phasecorrtracker::PhaseCorrTracker(image1, BoundingBox);

 ////////////////////   // Initialize some useful tracking debugging information
 ////////////////////   tracker_lost_ = false;
	////////////////////cv::namedWindow ("afterinit");
	////////////////////rectangle(image1,init_bounding_box,cv::Scalar(0,0,255),3);
	////////////////////imshow ("afterinit",image1);
	//////////////////////std::cout <<init_bounding_box.x<<","<<init_bounding_box.y<<" "<< init_bounding_box.width <<","<<init_bounding_box.height <<std::endl ;
	////////////////////cv::waitKey ();
    
    // Return success

	return true;
  }
  void PhaseCorrAlgorithm::import_image(const cv::Mat & image)
  {
    // We want the internal version of the image to be gray-scale, so let's
    // do that here.  We'll handle cases where the input is either RGB, RGBA,
    // or already gray-scale.  I assume it's already 8-bit.  If not then 
    // an error is thrown.  I'm not going to deal with converting properly
    // from every data type since that shouldn't be happening.

    // Make sure the input image pointer is valid
    if (image.empty())
    {
      std::cerr << "PhaseCorrAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
      exit(0); // <--- CV_ERROR?
    }

    // Now copy it in appropriately as a gray-scale, 8-bit image
	cv::cvtColor(image, image_, CV_RGB2GRAY);
    /*if (image.channels() == 4)
    {
      cv::cvtColor(image, image_, CV_RGBA2BGR);

    }
    else if (image.channels() == 3)
    {
      cv::cvtColor(image, image_, CV_RGB2BGR);
	  //image.copyTo (image_);
    }
    else if (image.channels() == 1)
    {
		cv::cvtColor(image, image_, CV_GRAY2BGR);
      //image.copyTo(image_);
    }
    else
    {
      std::cerr << "OnlineBoostingAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
                << std::endl;
      exit(0);
    }*/
  }
  
  //---------------------------------------------------------------------------
  bool
  PhaseCorrAlgorithm::update( const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box,float & confidence)
  {
    // Import the image
    //import_image(image);
	/*cv::namedWindow ("image");
	imshow("image",image);
	cv::waitKey ();*/

    // Make sure the tracker has already been successfully initialized
    if (tracker_ == NULL)
    {
      std::cerr
          << "PhaseCorrAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
          << std::endl;
      return false;
    }
    cv::Size imageSize(image.cols, image.rows);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
 //   boosting::Patches *trackingPatches;
    cv::Rect prevTrackBox=track_box;
  //  trackingPatches = new boosting::PatchesRegularScan(searchRegion, wholeImage, tracking_rect_size_, params.overlap_);

    //cur_frame_rep_->setNewImageAndROI(image_, searchRegion);
     cv::Mat image1=image;
    if (!tracker_->track(image1, track_box))
    {
      tracker_lost_ = true;
    }
    else
    {
      tracker_lost_ = false;
    }

   // delete trackingPatches;

    // Save the new tracking ROI
    track_box = tracker_->getTrackedPatch();
	//track_box=prevTrackBox
	confidence= tracker_->getConfidence();
   /////////////////////////////////////////////////////////////should be output variable
	///////////////////////////////////////////////////////////////////////////////////////////////std::cout << "\rTracking confidence = " << tracker_->getConfidence();

    // Return success or failure based on whether or not the tracker has been lost
/*	if(track_box.width<20)track_box.width=20;
	if(track_box.height<20)track_box.height=20;
	if(track_box.x<0)track_box.x=0;
if(track_box.y<0)track_box.y=0;
if(track_box.x>image.cols-20)track_box.x=image.cols-20;
if(track_box.y>image.rows-20)track_box.y=image.rows-20;*/



    return !tracker_lost_;
  }
  //----------------------------------------------------------------------------------------
  //CMT Algorithm
  //----------------------------------------------------------------------------------------
  CMTAlgorithm::CMTAlgorithm():
  TrackingAlgorithm(),
  tracker_(NULL), 
  tracker_lost_(false)
  {
	  
     int verbose_flag = 0;
//     FILELog::ReportingLevel() = verbose_flag ? logDEBUG : logINFO;
//      Output2FILE::Stream() = stdout; //Log to stdout
	  std::cout<<"Init CMT <<Consensus-based Matching>>"<<std::endl;
  }
  //----------------------------------------------------------------------------------------
  CMTAlgorithm::~CMTAlgorithm()
  {
    if (tracker_ != NULL)
    {
      delete tracker_;
      tracker_ = NULL;
    }

  }
  //------------------------------------------------------------------------------------------
  void CMTAlgorithm::import_image(const cv::Mat & image)
  {
    // We want the internal version of the image to be gray-scale, so let's
    // do that here.  We'll handle cases where the input is either RGB, RGBA,
    // or already gray-scale.  I assume it's already 8-bit.  If not then 
    // an error is thrown.  I'm not going to deal with converting properly
    // from every data type since that shouldn't be happening.

    // Make sure the input image pointer is valid
    if (image.empty())
    {
      std::cerr << "CMTAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
      exit(0); // <--- CV_ERROR?
    }

    // Now copy it in appropriately as a gray-scale, 8-bit image
    if (image.channels() == 4)
    {
      cv::cvtColor(image, image_, CV_RGBA2BGR);
    }
    else if (image.channels() == 3)
    {
      cv::cvtColor(image, image_, CV_RGB2BGR);
	  //image.copyTo (image_);
    }
    else if (image.channels() == 1)
    {
		cv::cvtColor(image, image_, CV_GRAY2BGR);
      //image.copyTo(image_);
    }
    else
    {
      std::cerr << "CMTAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
                << std::endl;
      exit(0);
    }
  }
  
  //---------------------------------------------------------------------------
  //------------------------------------------------------------------------------------------
   bool CMTAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
                                      const CvRect& init_bounding_box)
   {
        //import_image(image);
	     cv::Mat image1;
		if (image.channels() == 1)
		   image1=image;
		else
		   cvtColor(image,image1,CV_RGB2GRAY);	
	  
		cv::Rect BoundingBox=init_bounding_box;

    // If the boosting tracker has already been allocated, first de-allocate it
    if (tracker_ != NULL)
    {
      std::cerr
          << "CMTAlgorithm::initialize(...) -- WARNING!  tracker already initialized.  Resetting now...\n"
          << std::endl;
      delete tracker_;
      tracker_ = NULL;
    }


//     (Re-)Initialize the TLD tracker
    cv::Size imageSize(image_.cols, image_.rows);
 //   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
    cv::Rect tracking_rect = init_bounding_box;
    tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);


	std::cout <<init_bounding_box.x<<","<<init_bounding_box.y<<" "<< init_bounding_box.width <<","<<init_bounding_box.height <<std::endl ;

    tracker_ = new cmttracker::CMT();
   tracker_->consensus.estimate_rotation=false;
	tracker_->initialize(image1,BoundingBox);


    
    // Return success

	return true;
   }
   //---------------------------------------------------------------------------
    bool
  CMTAlgorithm::update( const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box,float & confidence)
  {
    // Import the image
      import_image(image);

    // Make sure the tracker has already been successfully initialized
    if (tracker_ == NULL)
    {
      std::cerr
		  << "CMTAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
          << std::endl;
      return false;
    }
    cv::Size imageSize(image.cols, image.rows);
	cv::Mat image1;
	if (image.channels() == 1)
      image1=image;
	else
	  cvtColor(image,image1,CV_RGB2GRAY);	 
	 tracker_->processFrame(image1);
	 if (tracker_->points_active.size()>tracker_->threshold)
    {
      tracker_lost_ = false;
	    track_box=tracker_->bb_rot.boundingRect();
  	   confidence= tracker_->points_active.size();//classes_active.size();
    }
    else
    {
      tracker_lost_ = true;
	  confidence= tracker_->points_active.size();//classes_active.size();
    }

  
 


    return !tracker_lost_;
  }
  //----------------------------------------------------------------------------------------
  //STRUCK Algorithm
  //----------------------------------------------------------------------------------------
  STRUCKAlgorithm::STRUCKAlgorithm():
  TrackingAlgorithm(),
  tracker_(NULL), 
  tracker_lost_(false)
  {
	  
   
	conf.SetDefaults();
	conf.debugMode=false;
	std::cout << conf << std::endl;
    
	  std::cout<<"Init STRUCK <<Structured Output Tracking with Kernels>>"<<std::endl;
    
	  
  }
  //----------------------------------------------------------------------------------------
  STRUCKAlgorithm::~STRUCKAlgorithm()
  {
    if (tracker_ != NULL)
    {
      delete tracker_;
      tracker_ = NULL;
    }

  }
  //------------------------------------------------------------------------------------------
  void STRUCKAlgorithm::import_image(const cv::Mat & image)
  {
    // We want the internal version of the image to be gray-scale, so let's
    // do that here.  We'll handle cases where the input is either RGB, RGBA,
    // or already gray-scale.  I assume it's already 8-bit.  If not then 
    // an error is thrown.  I'm not going to deal with converting properly
    // from every data type since that shouldn't be happening.

    // Make sure the input image pointer is valid
    if (image.empty())
    {
      std::cerr << "STRUCKAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
      exit(0); // <--- CV_ERROR?
    }

    // Now copy it in appropriately as a gray-scale, 8-bit image
    if (image.channels() == 4)
    {
      cv::cvtColor(image, image_, CV_RGBA2BGR);
    }
    else if (image.channels() == 3)
    {
      cv::cvtColor(image, image_, CV_RGB2BGR);
	  //image.copyTo (image_);
    }
    else if (image.channels() == 1)
    {
		cv::cvtColor(image, image_, CV_GRAY2BGR);
      //image.copyTo(image_);
    }
    else
    {
      std::cerr << "STRUCKAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
                << std::endl;
      exit(0);
    }
  }
  
  //---------------------------------------------------------------------------
  //------------------------------------------------------------------------------------------
   bool STRUCKAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
                                      const CvRect& init_bounding_box)
   {
        //import_image(image);
	   /*  cv::Mat image1;
		if (image.channels() == 1)
		   image1=image;
		else
		   cvtColor(image,image1,CV_RGB2GRAY);	*/
	  
		cv::Rect BoundingBox=init_bounding_box;

    // If the boosting tracker has already been allocated, first de-allocate it
    if (tracker_ != NULL)
    {
      std::cerr
          << "STRUCKAlgorithm::initialize(...) -- WARNING!  tracker already initialized.  Resetting now...\n"
          << std::endl;
      delete tracker_;
      tracker_ = NULL;
    }


//     (Re-)Initialize the TLD tracker
    cv::Size imageSize(image_.cols, image_.rows);
 //   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
    cv::Rect tracking_rect = init_bounding_box;
    tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);


	std::cout <<init_bounding_box.x<<","<<init_bounding_box.y<<" "<< init_bounding_box.width <<","<<init_bounding_box.height <<std::endl ;
	/*
    tracker_ = new cmttracker::CMT();
   tracker_->consensus.estimate_rotation=false;
	tracker_->initialize(image1,BoundingBox);*/

	//tracker_->Reset();
	tracker_=new strucktracker::STRUCK(conf);
	//tracker_->confidence_threshold=0.7;
	FloatRect initBB = IntRect(init_bounding_box.x,init_bounding_box.y,init_bounding_box.width, init_bounding_box.height);
	           if (tracker_->IsInitialised())
				{
					tracker_->Reset();
				}
	tracker_->Initialise(image, initBB);
    
    // Return success

	return true;
   }
   //---------------------------------------------------------------------------
    bool
  STRUCKAlgorithm::update( const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box,float & confidence)
  {
    // Import the image
      import_image(image);

    // Make sure the tracker has already been successfully initialized
    if (tracker_ == NULL)
    {
      std::cerr
		  << "STRUCKAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
          << std::endl;
      return false;
    }
    cv::Size imageSize(image.cols, image.rows);


	tracker_->Track(image);
	if (tracker_->bestScore>tracker_->confidence_threshold)
    {
       tracker_lost_ = false;
	   track_box=Rect(tracker_->GetBB().XMin(),tracker_->GetBB().YMin(),tracker_->GetBB().Width(),tracker_->GetBB().Height());
  	   confidence= tracker_->bestScore;//classes_active.size();
    }
    else
    {
      tracker_lost_ = true;
	  confidence= tracker_->bestScore;//classes_active.size();
    }
	if(conf.debugMode)
	{
		tracker_->Debug();
	}
	return !tracker_lost_;
	
 }

	//-------------------------------------------------------------------------
	//KCF
	//-------------------------------------------------------------------------
	KCFAlgorithm::KCFAlgorithm() :
		TrackingAlgorithm(),
		tracker_(NULL),
		tracker_lost_(false)
	{


	/*	kcfparam.padding = 1.5;
		kcfparam.lambda = 0.0001;
		kcfparam.outputSigmaFactor = 0.1;
		kcfparam.votScaleStep = 1.05;
		kcfparam.votScaleWeight = 0.95;
		kcfparam.templateSize = 100;
		kcfparam.interpFactor = 0.012;
		kcfparam.kernelSigma = 0.6;
		kcfparam.cellSize = 4;
		kcfparam.pixelPadding = 0;
		kcfparam.enableTrackingLossDetection = true; //omar false
		kcfparam.useVotScaleEstimation = false;
		kcfparam.useDsstScaleEstimation = true;
		kcfparam.useFhogTranspose = true;//false
		*/
		std::cout << "Init KCF <<Kernelized correlation filter>>" << std::endl;


	}
	//----------------------------------------------------------------------------------------
	KCFAlgorithm::~KCFAlgorithm()
	{
		if (tracker_ != NULL)
		{
			delete tracker_;
			tracker_ = NULL;
		}

	}
	//------------------------------------------------------------------------------------------
	void KCFAlgorithm::import_image(const cv::Mat & image)
	{
		// We want the internal version of the image to be gray-scale, so let's
		// do that here.  We'll handle cases where the input is either RGB, RGBA,
		// or already gray-scale.  I assume it's already 8-bit.  If not then 
		// an error is thrown.  I'm not going to deal with converting properly
		// from every data type since that shouldn't be happening.

		// Make sure the input image pointer is valid
		if (image.empty())
		{
			std::cerr << "CMTAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
			exit(0); // <--- CV_ERROR?
		}

		// Now copy it in appropriately as a gray-scale, 8-bit image
		if (image.channels() == 4)
		{
			cv::cvtColor(image, image_, CV_RGBA2BGR);
		}
		else if (image.channels() == 3)
		{
			cv::cvtColor(image, image_, CV_RGB2BGR);
			//image.copyTo (image_);
		}
		else if (image.channels() == 1)
		{
			cv::cvtColor(image, image_, CV_GRAY2BGR);
			//image.copyTo(image_);
		}
		else
		{
			std::cerr << "KCFAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
				<< std::endl;
			exit(0);
		}
	}

	//---------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	bool KCFAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
		const CvRect& init_bounding_box)
	{
		import_image(image);
		/*  cv::Mat image1;
		if (image.channels() == 1)
		image1=image;
		else
		cvtColor(image,image1,CV_RGB2GRAY);	*/

		cv::Rect BoundingBox = init_bounding_box;

		// If the boosting tracker has already been allocated, first de-allocate it
		if (tracker_ != NULL)
		{
			std::cerr
				<< "KCFAlgorithm::initialize(...) -- WARNING!  tracker already initialized.  Resetting now...\n"
				<< std::endl;
			delete tracker_;
			tracker_ = NULL;
		}


		//     (Re-)Initialize KCF tracker
		cv::Size imageSize(image_.cols, image_.rows);
		//   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
		cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
		cv::Rect tracking_rect = init_bounding_box;
		tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);


		std::cout << init_bounding_box.x << "," << init_bounding_box.y << " " << init_bounding_box.width << "," << init_bounding_box.height << std::endl;
		tracker_ = new cf_tracking::KcfTracker(kcfparam);
		cv::Rect_<double> _boundingBox;
		_boundingBox = Rect_<double>(static_cast<double>(init_bounding_box.x),
			static_cast<double>(init_bounding_box.y),
			static_cast<double>(init_bounding_box.width),
			static_cast<double>(init_bounding_box.height));
		bool _targetOnFrame = tracker_->reinit(image, _boundingBox);


		// Return success

		return _targetOnFrame;
	}
	//---------------------------------------------------------------------------
	bool
		KCFAlgorithm::update(const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box, float & confidence)
	{
			// Import the image
			import_image(image);

			// Make sure the tracker has already been successfully initialized
			if (tracker_ == NULL)
			{
				std::cerr
					<< "KCFAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
					<< std::endl;
				return false;
			}
			cv::Size imageSize(image.cols, image.rows);

			bool _targetOnFrame=tracker_->update(image, track_box);
			//tracker_->Track(image);
			return _targetOnFrame;

	}

	//-------------------------------------------------------------------------
	//DSST
	//-------------------------------------------------------------------------
	DSSTAlgorithm::DSSTAlgorithm() :
		TrackingAlgorithm(),
		tracker_(NULL),
		tracker_lost_(false)
	{


	/*	kcfparam.padding = 1.5;
		kcfparam.lambda = 0.0001;
		kcfparam.outputSigmaFactor = 0.1;
		kcfparam.votScaleStep = 1.05;
		kcfparam.votScaleWeight = 0.95;
		kcfparam.templateSize = 100;
		kcfparam.interpFactor = 0.012;
		kcfparam.kernelSigma = 0.6;
		kcfparam.cellSize = 4;
		kcfparam.pixelPadding = 0;
		kcfparam.enableTrackingLossDetection = true; //omar false
		kcfparam.useVotScaleEstimation = false;
		kcfparam.useDsstScaleEstimation = true;
		kcfparam.useFhogTranspose = true;//false*/

		std::cout << "Init DSST <<r>>" << std::endl;


	}
	//----------------------------------------------------------------------------------------
	DSSTAlgorithm::~DSSTAlgorithm()
	{
		if (tracker_ != NULL)
		{
			delete tracker_;
			tracker_ = NULL;
		}

	}
	//------------------------------------------------------------------------------------------
	void DSSTAlgorithm::import_image(const cv::Mat & image)
	{
		// We want the internal version of the image to be gray-scale, so let's
		// do that here.  We'll handle cases where the input is either RGB, RGBA,
		// or already gray-scale.  I assume it's already 8-bit.  If not then 
		// an error is thrown.  I'm not going to deal with converting properly
		// from every data type since that shouldn't be happening.

		// Make sure the input image pointer is valid
		if (image.empty())
		{
			std::cerr << "DSSTAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
			exit(0); // <--- CV_ERROR?
		}

		// Now copy it in appropriately as a gray-scale, 8-bit image
		if (image.channels() == 4)
		{
			cv::cvtColor(image, image_, CV_RGBA2BGR);
		}
		else if (image.channels() == 3)
		{
			cv::cvtColor(image, image_, CV_RGB2BGR);
			//image.copyTo (image_);
		}
		else if (image.channels() == 1)
		{
			cv::cvtColor(image, image_, CV_GRAY2BGR);
			//image.copyTo(image_);
		}
		else
		{
			std::cerr << "DSSTAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
				<< std::endl;
			exit(0);
		}
	}

	//---------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	bool DSSTAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
		const CvRect& init_bounding_box)
	{
		import_image(image);
		/*  cv::Mat image1;
		if (image.channels() == 1)
		image1=image;
		else
		cvtColor(image,image1,CV_RGB2GRAY);	*/

		cv::Rect BoundingBox = init_bounding_box;

		// If the boosting tracker has already been allocated, first de-allocate it
		if (tracker_ != NULL)
		{
			std::cerr
				<< "DSSTAlgorithm::initialize(...) -- WARNING!  tracker already initialized.  Resetting now...\n"
				<< std::endl;
			delete tracker_;
			tracker_ = NULL;
		}


		//     (Re-)Initialize KCF tracker
		cv::Size imageSize(image_.cols, image_.rows);
		//   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
		cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
		cv::Rect tracking_rect = init_bounding_box;
		tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);


		//std::cout << init_bounding_box.x << "," << init_bounding_box.y << " " << init_bounding_box.width << "," << init_bounding_box.height << std::endl;
		tracker_ = new cf_tracking::DsstTracker(kcfparam);
	//	tracker_ = Ptr<cf_tracking::DsstTracker(kcfparam)>;
		cv::Rect_<double> _boundingBox;
		_boundingBox = Rect_<double>(static_cast<double>(init_bounding_box.x),
			static_cast<double>(init_bounding_box.y),
			static_cast<double>(init_bounding_box.width),
			static_cast<double>(init_bounding_box.height));
		bool _targetOnFrame = tracker_->reinit(image, _boundingBox);


		// Return success

		return _targetOnFrame;
	}
	//---------------------------------------------------------------------------
	bool
		DSSTAlgorithm::update(const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box, float & confidence)
	{
			// Import the image
			import_image(image);

			// Make sure the tracker has already been successfully initialized
			if (tracker_ == NULL)
			{
				std::cerr
					<< "DSSTAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
					<< std::endl;
				return false;
			}
			cv::Size imageSize(image.cols, image.rows);

			bool _targetOnFrame = tracker_->update(image, track_box);
			//tracker_->Track(image);
			return _targetOnFrame;

	}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
//MOSSE
//-------------------------------------------------------------------------
	MosseAlgorithm::MosseAlgorithm() :
		TrackingAlgorithm(),
		tracker_(NULL),
		tracker_lost_(false)
	{


		/*	kcfparam.padding = 1.5;
		kcfparam.lambda = 0.0001;
		kcfparam.outputSigmaFactor = 0.1;
		kcfparam.votScaleStep = 1.05;
		kcfparam.votScaleWeight = 0.95;
		kcfparam.templateSize = 100;
		kcfparam.interpFactor = 0.012;
		kcfparam.kernelSigma = 0.6;
		kcfparam.cellSize = 4;
		kcfparam.pixelPadding = 0;
		kcfparam.enableTrackingLossDetection = true; //omar false
		kcfparam.useVotScaleEstimation = false;
		kcfparam.useDsstScaleEstimation = true;
		kcfparam.useFhogTranspose = true;//false*/

		std::cout << "Init Mosse <<r>>" << std::endl;


	}
	//----------------------------------------------------------------------------------------
    MosseAlgorithm::~MosseAlgorithm()
	{
		if (tracker_ != NULL)
		{
			delete tracker_;
			tracker_ = NULL;
		}

	}
	//------------------------------------------------------------------------------------------
	void MosseAlgorithm::import_image(const cv::Mat & image)
	{
		// We want the internal version of the image to be gray-scale, so let's
		// do that here.  We'll handle cases where the input is either RGB, RGBA,
		// or already gray-scale.  I assume it's already 8-bit.  If not then 
		// an error is thrown.  I'm not going to deal with converting properly
		// from every data type since that shouldn't be happening.

		// Make sure the input image pointer is valid
		if (image.empty())
		{
			std::cerr << "MosseAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
			exit(0); // <--- CV_ERROR?
		}

		// Now copy it in appropriately as a gray-scale, 8-bit image
		if (image.channels() == 4)
		{
			cv::cvtColor(image, image_, CV_RGBA2BGR);
		}
		else if (image.channels() == 3)
		{
			cv::cvtColor(image, image_, CV_RGB2BGR);
			//image.copyTo (image_);
		}
		else if (image.channels() == 1)
		{
			cv::cvtColor(image, image_, CV_GRAY2BGR);
			//image.copyTo(image_);
		}
		else
		{
			std::cerr << "MosseAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
				<< std::endl;
			exit(0);
		}
	}

	//---------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	bool MosseAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
		const CvRect& init_bounding_box)
	{
		import_image(image);
		/*  cv::Mat image1;
		if (image.channels() == 1)
		image1=image;
		else
		cvtColor(image,image1,CV_RGB2GRAY);	*/

		cv::Rect BoundingBox = init_bounding_box;

		// If the boosting tracker has already been allocated, first de-allocate it
		if (tracker_ != NULL)
		{
			std::cerr
				<< "MosseAlgorithm::initialize(...) -- WARNING!  tracker already initialized.  Resetting now...\n"
				<< std::endl;
			delete tracker_;
			tracker_ = NULL;
		}


		//     (Re-)Initialize KCF tracker
		cv::Size imageSize(image_.cols, image_.rows);
		//   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
		cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
		cv::Rect tracking_rect = init_bounding_box;
		tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);


		//std::cout << init_bounding_box.x << "," << init_bounding_box.y << " " << init_bounding_box.width << "," << init_bounding_box.height << std::endl;
		tracker_ = new Mossetracker::Mosse();
		bool _targetOnFrame = tracker_->InitTracker(image,BoundingBox);


		// Return success

		return _targetOnFrame;
	}
	//---------------------------------------------------------------------------
	bool
	 MosseAlgorithm::update(const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box, float & confidence)
	{
		// Import the image
		import_image(image);
		bool _targetOnFrame=false;
		// Make sure the tracker has already been successfully initialized
		if (tracker_ == NULL)
		{
			std::cerr
				<< "MosseAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
				<< std::endl;
			return false;
		}
		cv::Size imageSize(image.cols, image.rows);
		confidence= tracker_->Track(image);
		if (tracker_->getState() == 2)//FOUND 
		{
			track_box = tracker_->getPosition();
			_targetOnFrame = true;
		
		}
		else
			if (tracker_->getState() == 0)//FOUND 
			{
				_targetOnFrame = false;
				
			}

		//bool _targetOnFrame = tracker_->update(image, track_box);
		//tracker_->Track(image);
		return _targetOnFrame;

	}

	///////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////SKCF/////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	//SKCF
	//-------------------------------------------------------------------------
	skcfAlgorithm::skcfAlgorithm() :
		TrackingAlgorithm(),
		tracker_(NULL),
		tracker_lost_(false)
	{


		
		std::cout << "SKCF <<r>>" << std::endl;


	}
	//----------------------------------------------------------------------------------------
	skcfAlgorithm::~skcfAlgorithm()
	{
		if (tracker_ != NULL)
		{
			delete tracker_;
			tracker_ = NULL;
		}

	}
	//------------------------------------------------------------------------------------------
	void skcfAlgorithm::import_image(const cv::Mat & image)
	{
		// We want the internal version of the image to be gray-scale, so let's
		// do that here.  We'll handle cases where the input is either RGB, RGBA,
		// or already gray-scale.  I assume it's already 8-bit.  If not then 
		// an error is thrown.  I'm not going to deal with converting properly
		// from every data type since that shouldn't be happening.

		// Make sure the input image pointer is valid
		if (image.empty())
		{
			std::cerr << "skcfAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
			exit(0); // <--- CV_ERROR?
		}

		// Now copy it in appropriately as a gray-scale, 8-bit image
		if (image.channels() == 4)
		{
			cv::cvtColor(image, image_, CV_RGBA2BGR);
		}
		else if (image.channels() == 3)
		{
			cv::cvtColor(image, image_, CV_RGB2BGR);
			//image.copyTo (image_);
		}
		else if (image.channels() == 1)
		{
			cv::cvtColor(image, image_, CV_GRAY2BGR);
			//image.copyTo(image_);
		}
		else
		{
			std::cerr << "skcfAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
				<< std::endl;
			exit(0);
		}
	}

	//---------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	bool skcfAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
		const CvRect& init_bounding_box)
	{
		import_image(image);
		/*  cv::Mat image1;
		if (image.channels() == 1)
		image1=image;
		else
		cvtColor(image,image1,CV_RGB2GRAY);	*/

		cv::Rect BoundingBox = init_bounding_box;

		// If the boosting tracker has already been allocated, first de-allocate it
		if (tracker_ != NULL)
		{
			std::cerr
				<< "skcfAlgorithm::initialize(...) -- WARNING!  tracker already initialized.  Resetting now...\n"
				<< std::endl;
			delete tracker_;
			tracker_ = NULL;
		}

				//     (Re-)Initialize KCF tracker
		cv::Size imageSize(image_.cols, image_.rows);
		//   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
		cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
		cv::Rect tracking_rect = init_bounding_box;
		tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);
		
	
		std::cout << init_bounding_box.x << "," << init_bounding_box.y << " " << init_bounding_box.width << "," << init_bounding_box.height << std::endl;
		tracker_ = new cv::skcftracker::SKCFDCF();
		
		//tracker = new cf_tracking::DsstTracker(DSSTAlgorithm::);;
			cv::Rect_<double> _boundingBox;
		_boundingBox = Rect_<double>(static_cast<double>(init_bounding_box.x),
			static_cast<double>(init_bounding_box.y),
			static_cast<double>(init_bounding_box.width),
			static_cast<double>(init_bounding_box.height));
		 tracker_->initialize(image,init_bounding_box);


		// Return success
		
		return true;
	}
	//---------------------------------------------------------------------------
	bool
		skcfAlgorithm::update(const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box, float & confidence)
	{
		bool _targetOnFrame;
		// Import the image
		import_image(image);

		// Make sure the tracker has already been successfully initialized
		if (tracker_ == NULL)
		{
			std::cerr
				<< "SKCFAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
				<< std::endl;
			return false;
		}
		cv::Size imageSize(image.cols, image.rows);
		double trackconf=tracker_->processFrame_(image);
		if (trackconf > 0.4)
		{
			tracker_->getTrackedRect(track_box);
			_targetOnFrame = true;
		}
		else
			 _targetOnFrame = false;
			/*vector<Point2f> pts;
		tracker_->getTrackedArea(pts);
		track_box.x = (int)pts[0].x;
		track_box.y = (int)pts[0].y;
		track_box.width = (int)(pts[0].x - pts[1].x);
		track_box.height = (int)(pts[0].y - pts[4].y);*/
		//bool _targetOnFrame = tracker_->update(image, track_box);
		//tracker_->Track(image);
		return _targetOnFrame;

	}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Threshold/////////////////////////////////////////////////
//-------------------------------------------------------------------------
//THreshold
//-------------------------------------------------------------------------
	ThreshAlgorithm::ThreshAlgorithm() :
		TrackingAlgorithm(),
		//tracker_(NULL),
		tracker_lost_(false)
	{
		


		tracker_ = new  threshold_tracker::Threshold_Tracking();

		std::cout << "Threshold <<r>>" << std::endl;


	}
	//----------------------------------------------------------------------------------------
	ThreshAlgorithm::~ThreshAlgorithm()
	{
		/*cv::namedWindow("deleteing algorithm");
		cv::waitKey();*/
		
		if (tracker_ != NULL)
		{
		
			tracker_->FreeImages();
		
			delete tracker_;
			tracker_ = NULL;
		}
		/*cv::namedWindow(" algorithm deleted ");
		cv::waitKey();*/

	}
	//------------------------------------------------------------------------------------------
	void ThreshAlgorithm::import_image(const cv::Mat & image)
	{
		// We want the internal version of the image to be gray-scale, so let's
		// do that here.  We'll handle cases where the input is either RGB, RGBA,
		// or already gray-scale.  I assume it's already 8-bit.  If not then 
		// an error is thrown.  I'm not going to deal with converting properly
		// from every data type since that shouldn't be happening.

		// Make sure the input image pointer is valid
		if (image.empty())
		{
			std::cerr << "ThreshAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
			exit(0); // <--- CV_ERROR?
		}

		// Now copy it in appropriately as a gray-scale, 8-bit image
		if (image.channels() == 4)
		{
			cv::cvtColor(image, image_, CV_RGBA2BGR);
		}
		else if (image.channels() == 3)
		{
			cv::cvtColor(image, image_, CV_RGB2BGR);
			//image.copyTo (image_);
		}
		else if (image.channels() == 1)
		{
			cv::cvtColor(image, image_, CV_GRAY2BGR);
			//image.copyTo(image_);
		}
		else
		{
			std::cerr << "ThreshAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
				<< std::endl;
			exit(0);
		}
	}

	//---------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	bool ThreshAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
		const CvRect& init_bounding_box)
	{
		import_image(image);
		/*  cv::Mat image1;
		if (image.channels() == 1)
		image1=image;
		else
		cvtColor(image,image1,CV_RGB2GRAY);	*/

		cv::Rect BoundingBox = init_bounding_box;

		// If the boosting tracker has already been allocated, first de-allocate it
		if (tracker_ != NULL)
		{
			std::cerr
				<< "ThreshAlgorithm::initialize(...) -- WARNING!  tracker already initialized.  Resetting now...\n"
				<< std::endl;
	      	tracker_->FreeImages();
			
			delete tracker_;
			tracker_ = NULL;
		}

		//     (Re-)Initialize KCF tracker
		cv::Size imageSize(image_.cols, image_.rows);
		//   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
		cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
		cv::Rect tracking_rect = init_bounding_box;
		tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);


		std::cout << init_bounding_box.x << "," << init_bounding_box.y << " " << init_bounding_box.width << "," << init_bounding_box.height << std::endl;
		tracker_ = new cv::threshold_tracker::Threshold_Tracking();
		
		cout << "fuck" << endl;
		tracker_->RegH = 120;// BoundingBox.height;
		tracker_->RegW = 120;// BoundingBox.width;
		tracker_->TopHatFDim = 16;
		switch (params.threshold_type_) {
		case 0:
			tracker_->AutoTargetColor = true;
			tracker_->bWhitetar = false;
			break;
		case 1:
			tracker_->AutoTargetColor = false;
			tracker_->bWhitetar = false;
			break;
		case 2:
			tracker_->AutoTargetColor = false;
			tracker_->bWhitetar = true;
			break;

		}
		tracker_->bFirstTracking = true;
		tracker_->bLargeTarget = false;
		bool DDebug = true;
		tracker_->init(image, BoundingBox, tracker_->TopHatFDim, &tracker_->bFirstTracking, &tracker_->bLargeTarget, tracker_->AutoTargetColor, &tracker_->bWhitetar, &tracker_->RegW, &tracker_->RegH,DDebug);

		/*cv::namedWindow("after initializing");
		cv::waitKey();*/
		// Return success

		return true;
	}
	//---------------------------------------------------------------------------
	bool
		ThreshAlgorithm::update(const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box, float & confidence)
	{
		bool _targetOnFrame;
		// Import the image
		import_image(image);

		// Make sure the tracker has already been successfully initialized
		if (tracker_ == NULL)
		{
			std::cerr
				<< "ThreshAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
				<< std::endl;
			return false;
		}
		cv::Size imageSize(image.cols, image.rows);
		bool DDebug = true;
		tracker_->Tracking(image, &track_box, tracker_->RegW, tracker_->RegH, tracker_->TopHatFDim, tracker_->bWhitetar, false, DDebug);
		//std::cout << "color type=" << params.threshold_type_ << endl;
		return true;

	}

	///////////////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------
//	CompressiveTracker
  //---------------------------------------------------------------------------

  COMPRESSIVEAlgorithm::COMPRESSIVEAlgorithm():
  TrackingAlgorithm(),
  tracker_(NULL), 
  tracker_lost_(false)
  {
	  
   	  std::cout<<"Init COMPRESSIVEAlgorithm Tracker"<<std::endl;
  }
  //----------------------------------------------------------------------------------------
  COMPRESSIVEAlgorithm::~COMPRESSIVEAlgorithm()
  {
    if (tracker_ != NULL)
    {
      delete tracker_;
      tracker_ = NULL;
    }

  }
  //------------------------------------------------------------------------------------------
  void COMPRESSIVEAlgorithm::import_image(const cv::Mat & image)
  {
    // We want the internal version of the image to be gray-scale, so let's
    // do that here.  We'll handle cases where the input is either RGB, RGBA,
    // or already gray-scale.  I assume it's already 8-bit.  If not then 
    // an error is thrown.  I'm not going to deal with converting properly
    // from every data type since that shouldn't be happening.

    // Make sure the input image pointer is valid
    if (image.empty())
    {
      std::cerr << "COMPRESSIVEAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
      exit(0); // <--- CV_ERROR?
    }

    // Now copy it in appropriately as a gray-scale, 8-bit image
    if (image.channels() == 4)
    {
      cv::cvtColor(image, image_, CV_RGBA2BGR);
    }
    else if (image.channels() == 3)
    {
      cv::cvtColor(image, image_, CV_RGB2BGR);
	  //image.copyTo (image_);
    }
    else if (image.channels() == 1)
    {
		cv::cvtColor(image, image_, CV_GRAY2BGR);
      //image.copyTo(image_);
    }
    else
    {
      std::cerr << "COMPRESSIVEAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
                << std::endl;
      exit(0);
    }
  }
  
  //---------------------------------------------------------------------------
  //------------------------------------------------------------------------------------------
   bool COMPRESSIVEAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
                                      const CvRect& init_bounding_box)
   {
        //import_image(image);
	     cv::Mat image1;
		if (image.channels() == 1)
		   image1=image;
		else
		   cvtColor(image,image1,CV_RGB2GRAY);	
	  
		cv::Rect BoundingBox=init_bounding_box;

    // If the boosting tracker has already been allocated, first de-allocate it
    if (tracker_ != NULL)
    {
      std::cerr
          << " COMPRESSIVEAlgorithm::initialize(...) -- WARNING!  tracker already initialized.  Resetting now...\n"
          << std::endl;
      delete tracker_;
      tracker_ = NULL;
    }


//     (Re-)Initialize the CT tracker
    cv::Size imageSize(image_.cols, image_.rows);
 //   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
    cv::Rect tracking_rect = init_bounding_box;
    tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);


	std::cout <<init_bounding_box.x<<","<<init_bounding_box.y<<" "<< init_bounding_box.width <<","<<init_bounding_box.height <<std::endl ;

	tracker_ = new compressivetracker::CompressiveTracker();
 
	tracker_->init(image1,BoundingBox);


    
    // Return success

	return true;
   }
   //---------------------------------------------------------------------------
    bool
  COMPRESSIVEAlgorithm::update( const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box,float & confidence)
  {
    // Import the image
      import_image(image);

    // Make sure the tracker has already been successfully initialized
    if (tracker_ == NULL)
    {
      std::cerr
		  << "COMPRESSIVEAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
          << std::endl;
      return false;
    }
    cv::Size imageSize(image.cols, image.rows);
	cv::Mat image1;
	if (image.channels() == 1)
      image1=image;
	else
	  cvtColor(image,image1,CV_RGB2GRAY);	 
	 tracker_->processFrame(image1,track_box);
	 confidence=tracker_->radioMax;
	 if (tracker_->radioMax >tracker_->threshold)
    {
      tracker_lost_ = false;
    }
    else
    {
      tracker_lost_ = true;
    }

   // delete trackingPatches;




    return !tracker_lost_;
  }

  //---------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Normilazed Cross CORRELATOR Algo
 //---------------------------------------------------------------------------
  NORMCCAlgorithm::NORMCCAlgorithm()
      :
        TrackingAlgorithm(),
        tracker_(NULL),
        tracker_lost_(false)

  {
	  std::cout<<"Init Normalized Cross Correlation"<<std::endl;
  }

  //---------------------------------------------------------------------------
  NORMCCAlgorithm::~NORMCCAlgorithm()
  {
    if (tracker_ != NULL)
    {
      delete tracker_;
      tracker_ = NULL;
    }

  }

  //---------------------------------------------------------------------------
  bool
  NORMCCAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
                                      const CvRect& init_bounding_box)
  {
    // Import the image
	  	cv::Mat image1=image;
		cv::Rect BoundingBox=init_bounding_box;
	//  cv::namedWindow ("objinit0");
	//  cv::rectangle(image1,BoundingBox,cv::Scalar(255,255,255),3);
//	imshow ("objinit0",image1);
///	cv::waitKey ();
    import_image(image);

    // If the boosting tracker has already been allocated, first de-allocate it
    if (tracker_ != NULL)
    {
      std::cerr
          << "NORMCCAlgorithm::initialize(...) -- WARNING!  NORMCC tracker already initialized.  Resetting now...\n"
          << std::endl;
      delete tracker_;
      tracker_ = NULL;
    }


//     (Re-)Initialize the boosting tracker
    cv::Size imageSize(image_.cols, image_.rows);
 //   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
    cv::Rect tracking_rect = init_bounding_box;
    tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);

//	cv::namedWindow ("objinit1");
	/////////////////////////////////////////////////rectangle(image1,BoundingBox,cv::Scalar(0,0,255),3);
	//imshow ("objinit1",image1);
    tracker_ = new normcctracker::NORMCCTracker(image1, BoundingBox);

 ////////////////////   // Initialize some useful tracking debugging information
 ////////////////////   tracker_lost_ = false;
	////////////////////cv::namedWindow ("afterinit");
	////////////////////rectangle(image1,init_bounding_box,cv::Scalar(0,0,255),3);
	////////////////////imshow ("afterinit",image1);
	//////////////////////std::cout <<init_bounding_box.x<<","<<init_bounding_box.y<<" "<< init_bounding_box.width <<","<<init_bounding_box.height <<std::endl ;
	////////////////////cv::waitKey ();
    
    // Return success

	return true;
  }
  void NORMCCAlgorithm::import_image(const cv::Mat & image)
  {
    // We want the internal version of the image to be gray-scale, so let's
    // do that here.  We'll handle cases where the input is either RGB, RGBA,
    // or already gray-scale.  I assume it's already 8-bit.  If not then 
    // an error is thrown.  I'm not going to deal with converting properly
    // from every data type since that shouldn't be happening.

    // Make sure the input image pointer is valid
    if (image.empty())
    {
      std::cerr << "NORMCCAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
      exit(0); // <--- CV_ERROR?
    }

    // Now copy it in appropriately as a gray-scale, 8-bit image
	cv::cvtColor(image, image_, CV_RGB2GRAY);
    /*if (image.channels() == 4)
    {
      cv::cvtColor(image, image_, CV_RGBA2BGR);

    }
    else if (image.channels() == 3)
    {
      cv::cvtColor(image, image_, CV_RGB2BGR);
	  //image.copyTo (image_);
    }
    else if (image.channels() == 1)
    {
		cv::cvtColor(image, image_, CV_GRAY2BGR);
      //image.copyTo(image_);
    }
    else
    {
      std::cerr << "OnlineBoostingAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
                << std::endl;
      exit(0);
    }*/
  }
  
  //---------------------------------------------------------------------------
  bool
  NORMCCAlgorithm::update( const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box,float & confidence)
  {
    
	  // Make sure the tracker has already been successfully initialized
    if (tracker_ == NULL)
    {
      std::cerr
          << "NORMCCAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
          << std::endl;
      return false;
    }
    cv::Size imageSize(image.cols, image.rows);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
 //   boosting::Patches *trackingPatches;
    cv::Rect prevTrackBox=track_box;
  //  trackingPatches = new boosting::PatchesRegularScan(searchRegion, wholeImage, tracking_rect_size_, params.overlap_);

    //cur_frame_rep_->setNewImageAndROI(image_, searchRegion);
     cv::Mat image1=image;
    if (!tracker_->track(image1, track_box))
    {
      tracker_lost_ = true;
    }
    else
    {
      tracker_lost_ = false;
    }

   // delete trackingPatches;

    // Save the new tracking ROI
    track_box = tracker_->getTrackedPatch();
	//track_box=prevTrackBox
	confidence= tracker_->getConfidence();



    return !tracker_lost_;
  }

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  //added Modified Normalized Cross Correlation
  MNORMCCAlgorithm::MNORMCCAlgorithm()
      :
        TrackingAlgorithm(),
        tracker_(NULL),
        tracker_lost_(false)

  {
	  std::cout<<"Init Modified Normalized Cross Correlation"<<std::endl;
  }

  //---------------------------------------------------------------------------
  MNORMCCAlgorithm::~MNORMCCAlgorithm()
  {
    if (tracker_ != NULL)
    {
      delete tracker_;
      tracker_ = NULL;
    }

  }

  //---------------------------------------------------------------------------
  bool
  MNORMCCAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
                                      const CvRect& init_bounding_box)
  {
    // Import the image
	  cv::Mat image1=image;
	  cv::Rect BoundingBox=init_bounding_box;
	  import_image(image);

    // If the boosting tracker has already been allocated, first de-allocate it
    if (tracker_ != NULL)
    {
      std::cerr
          << "Modified NORMCCAlgorithm::initialize(...) -- WARNING!  NORMCC tracker already initialized.  Resetting now...\n"
          << std::endl;
      delete tracker_;
      tracker_ = NULL;
    }


//     (Re-)Initialize the boosting tracker
    cv::Size imageSize(image_.cols, image_.rows);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
    cv::Rect tracking_rect = init_bounding_box;
    tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);

    tracker_ = new mnormcctracker::MNORMCCTracker(image1, BoundingBox);
    
    // Return success

	return true;
  }
  void MNORMCCAlgorithm::import_image(const cv::Mat & image)
  {
    // We want the internal version of the image to be gray-scale, so let's
    // do that here.  We'll handle cases where the input is either RGB, RGBA,
    // or already gray-scale.  I assume it's already 8-bit.  If not then 
    // an error is thrown.  I'm not going to deal with converting properly
    // from every data type since that shouldn't be happening.

    // Make sure the input image pointer is valid
    if (image.empty())
    {
      std::cerr << "Modified NORMCCAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
      exit(0); // <--- CV_ERROR?
    }

    // Now copy it in appropriately as a gray-scale, 8-bit image
	cv::cvtColor(image, image_, CV_RGB2GRAY);

  }
  
  //---------------------------------------------------------------------------
  bool
  MNORMCCAlgorithm::update( const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box,float & confidence)
  {

    if (tracker_ == NULL)
    {
      std::cerr
          << "Modified NORMCCAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
          << std::endl;
      return false;
    }
    cv::Size imageSize(image.cols, image.rows);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
	
    cv::Rect prevTrackBox=track_box;

     cv::Mat image1=image;
    if (!tracker_->track(image1, track_box))
    {
      tracker_lost_ = true;
    }
    else
    {
      tracker_lost_ = false;
    }

   // delete trackingPatches;

    // Save the new tracking ROI
    track_box = tracker_->getTrackedPatch();
	//track_box=prevTrackBox
	confidence= tracker_->getConfidence();
	this->getTemp();
    return !tracker_lost_;
  }

  //---------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  TLDAlgorithm::TLDAlgorithm()
      :
        TrackingAlgorithm(),
        tracker_(NULL),
        tracker_lost_(false)

  {
	  std::cout<<"Init TLD  ....."<<std::endl;
  }

  //---------------------------------------------------------------------------
  TLDAlgorithm::~TLDAlgorithm()
  {
    if (tracker_ != NULL)
    {
      delete tracker_;
      tracker_ = NULL;
    }

  }
  //------------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  bool
  TLDAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
                                      const CvRect& init_bounding_box)
  {
    // Import the image
	     /////////////////////////////////////////////////////////// import_image(image);
	  	cv::Mat image1=image;
		cv::Rect BoundingBox=init_bounding_box;

    // If the boosting tracker has already been allocated, first de-allocate it
    if (tracker_ != NULL)
    {
      std::cerr
          << "TLDAlgorithm::initialize(...) -- WARNING!  TLD tracker already initialized.  Resetting now...\n"
          << std::endl;
	//  tracker_->~TLDTracker();
	  tracker_->tld->release();
      delete tracker_;
      tracker_ = NULL;
    }


//     (Re-)Initialize the TLD tracker
    cv::Size imageSize(image_.cols, image_.rows);
 //   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
    cv::Rect tracking_rect = init_bounding_box;
    tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);

//	cv::namedWindow ("objinit1");
	//rectangle(image1,BoundingBox,cv::Scalar(0,0,255),3);
	//imshow ("objinit1",image1);
	std::cout <<init_bounding_box.x<<","<<init_bounding_box.y<<" "<< init_bounding_box.width <<","<<init_bounding_box.height <<std::endl ;
//	cv::waitKey ();
	if (!params.init_tld_)
      tracker_ = new tldtracker::TLDTracker(image1, BoundingBox, wholeImage, params.num_classifiers_);
	else
	{
		BoundingBox.height = 32;
		BoundingBox.width = 32;
		BoundingBox.x = 32;// (wholeImage.width / 2) - 16;
		BoundingBox.y = 32;// (wholeImage.height / 2) - 16;

		tracker_ = new tldtracker::TLDTracker(image1, BoundingBox, wholeImage, params.num_classifiers_);
		tracker_->tld->readFromFile("omar.xml");
		//tracker_->tld->currBB
	}
 ////////////////////   // Initialize some useful tracking debugging information
 ////////////////////   tracker_lost_ = false;
	////////////////////cv::namedWindow ("afterinit");
	////////////////////rectangle(image1,init_bounding_box,cv::Scalar(0,0,255),3);
	////////////////////imshow ("afterinit",image1);
	//////////////////////std::cout <<init_bounding_box.x<<","<<init_bounding_box.y<<" "<< init_bounding_box.width <<","<<init_bounding_box.height <<std::endl ;
	////////////////////cv::waitKey ();
    
    // Return success

	return true;
  }
  void TLDAlgorithm::import_image(const cv::Mat & image)
  {
    // We want the internal version of the image to be gray-scale, so let's
    // do that here.  We'll handle cases where the input is either RGB, RGBA,
    // or already gray-scale.  I assume it's already 8-bit.  If not then 
    // an error is thrown.  I'm not going to deal with converting properly
    // from every data type since that shouldn't be happening.

    // Make sure the input image pointer is valid
    if (image.empty())
    {
      std::cerr << "TLDAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
      exit(0); // <--- CV_ERROR?
    }

    // Now copy it in appropriately as a gray-scale, 8-bit image
    if (image.channels() == 4)
    {
      cv::cvtColor(image, image_, CV_RGBA2BGR);
    }
    else if (image.channels() == 3)
    {
      cv::cvtColor(image, image_, CV_RGB2BGR);
	  //image.copyTo (image_);
    }
    else if (image.channels() == 1)
    {
		cv::cvtColor(image, image_, CV_GRAY2BGR);
      //image.copyTo(image_);
    }
    else
    {
      std::cerr << "TLDAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
                << std::endl;
      exit(0);
    }
  }
  
  //---------------------------------------------------------------------------
  bool
  TLDAlgorithm::update( const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box,float & confidence)
  {
    // Import the image
   //////////////////////////////////////////////////////////////////////////////////// import_image(image);

    // Make sure the tracker has already been successfully initialized
    if (tracker_ == NULL)
    {
      std::cerr
          << "TLDAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
          << std::endl;
      return false;
    }
    cv::Size imageSize(image.cols, image.rows);
 //   cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
 //   boosting::Patches *trackingPatches;
  //  cv::Rect searchRegion = tracker_->getTrackingROI(params.search_factor_);
  //  trackingPatches = new boosting::PatchesRegularScan(searchRegion, wholeImage, tracking_rect_size_, params.overlap_);

    //cur_frame_rep_->setNewImageAndROI(image_, searchRegion);
     cv::Mat image1=image;
    if (!tracker_->track(image1, track_box))
    {
      tracker_lost_ = true;
    }
    else
    {
      tracker_lost_ = false;
    }
	
   // delete trackingPatches;

    // Save the new tracking ROI
	if(!tracker_lost_)  // i ommited here
	{
    track_box = tracker_->getTrackedPatch();
	confidence= tracker_->getConfidence();
//	if (confidence>0.8)
//		tracker_->tld->writeToFile("omar.xml");
	}
	else
		confidence= tracker_->getConfidence();
   /////////////////////////////////////////////////////////////should be output variable
	///////////////////////////////////////////////////////////////////////////////////////////////std::cout << "\rTracking confidence = " << tracker_->getConfidence();

    // Return success or failure based on whether or not the tracker has been lost
	/*if(track_box.width<20)track_box.width=20;
	if(track_box.height<20)track_box.height=20;
	if(track_box.x<0)track_box.x=0;
if(track_box.y<0)track_box.y=0;
if(track_box.x>image.cols-20)track_box.x=image.cols-20;
if(track_box.y>image.rows-20)track_box.y=image.rows-20;
*/


    return !tracker_lost_;
  }

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
CFTLDAlgorithm::CFTLDAlgorithm()
	  :
	  TrackingAlgorithm(),
	  tracker_(NULL),
	  tracker_lost_(false)

{
	//CFtld::CFTLD *tld_CF;
	//tld_CF = new CFtld::CFTLD();
	  std::cout << "Init CFTLD  ....." << std::endl;
  }

  //---------------------------------------------------------------------------
  CFTLDAlgorithm::~CFTLDAlgorithm()
  {
	  if (tracker_ != NULL)
	  {
		  delete tracker_;
		  tracker_ = NULL;
	  }

  }
  //------------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  bool
	  CFTLDAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
	  const CvRect& init_bounding_box)
  {
		  // Import the image
		  /////////////////////////////////////////////////////////// import_image(image);
		  cv::Mat image1 = image;
		  cv::Rect BoundingBox = init_bounding_box;

		  // If the boosting tracker has already been allocated, first de-allocate it
		  if (tracker_ != NULL)
		  {
			  std::cerr
				  << "CFTLDAlgorithm::initialize(...) -- WARNING!  Boosting tracker already initialized.  Resetting now...\n"
				  << std::endl;
			  delete tracker_;
			  tracker_ = NULL;
		  }


		  //     (Re-)Initialize the TLD tracker
		  cv::Size imageSize(image_.cols, image_.rows);
		  //   cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
		  cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
		  cv::Rect tracking_rect = init_bounding_box;
		  tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);
		  std::cout << init_bounding_box.x << "," << init_bounding_box.y << " " << init_bounding_box.width << "," << init_bounding_box.height << std::endl;
		  tracker_ = new CFtld::CFTLD();
		  tracker_->init(false);
		  tracker_->selectObject(image, &tracking_rect);
		  return tracker_->valid;
		//  tracker_->init(image1, tracking_rect, true);
		  //	cv::waitKey ();
	


		//  return true;
  }
  void CFTLDAlgorithm::import_image(const cv::Mat & image)
  {
	  // We want the internal version of the image to be gray-scale, so let's
	  // do that here.  We'll handle cases where the input is either RGB, RGBA,
	  // or already gray-scale.  I assume it's already 8-bit.  If not then 
	  // an error is thrown.  I'm not going to deal with converting properly
	  // from every data type since that shouldn't be happening.

	  // Make sure the input image pointer is valid
	  if (image.empty())
	  {
		  std::cerr << "TLDAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
		  exit(0); // <--- CV_ERROR?
	  }

	  // Now copy it in appropriately as a gray-scale, 8-bit image
	  if (image.channels() == 4)
	  {
		  cv::cvtColor(image, image_, CV_RGBA2BGR);
	  }
	  else if (image.channels() == 3)
	  {
		  cv::cvtColor(image, image_, CV_RGB2BGR);
		  //image.copyTo (image_);
	  }
	  else if (image.channels() == 1)
	  {
		  cv::cvtColor(image, image_, CV_GRAY2BGR);
		  //image.copyTo(image_);
	  }
	  else
	  {
		  std::cerr << "TLDAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
			  << std::endl;
		  exit(0);
	  }
  }

  //---------------------------------------------------------------------------
  bool
	  CFTLDAlgorithm::update(const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box, float & confidence)
  {
		  // Import the image
		  //////////////////////////////////////////////////////////////////////////////////// import_image(image);

		  // Make sure the tracker has already been successfully initialized
		  if (tracker_ == NULL)
		  {
			  std::cerr
				  << "CFTLDAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
				  << std::endl;
			  return false;
		  }
		  cv::Size imageSize(image.cols, image.rows);
	
		  cv::Mat image1 = image;
		  bool lost;
		  tracker_->processImage(image1);
		  if ((tracker_->isTrackerValid))
		  {
			  track_box = tracker_->trackerBB;
			  lost = false;
			  // Draw Points

		  }
		  else
		  {

			  track_box = *tracker_->prevBB;

			  lost = true;
		  }

	//	  bool _targetOnFrame=tracker_->track(image1, track_box);
		  confidence = tracker_->currConf;

		  return !lost;
		//  return true;
  }

  //---------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  OnlineBoostingAlgorithm::OnlineBoostingAlgorithm()
      :
        TrackingAlgorithm(),
        tracker_(NULL),
        cur_frame_rep_(NULL),
        tracker_lost_(false)
  {
  }

  //---------------------------------------------------------------------------
  OnlineBoostingAlgorithm::~OnlineBoostingAlgorithm()
  {
    if (tracker_ != NULL)
    {
      delete tracker_;
      tracker_ = NULL;
    }

    if (cur_frame_rep_ != NULL)
    {
      delete cur_frame_rep_;
      cur_frame_rep_ = NULL;
    }
  }

  //---------------------------------------------------------------------------
  bool
  OnlineBoostingAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
                                      const CvRect& init_bounding_box)
  {
    // Import the image
    import_image(image);

    // If the boosting tracker has already been allocated, first de-allocate it
    if (tracker_ != NULL)
    {
      std::cerr
          << "OnlineBoostingAlgorithm::initialize(...) -- WARNING!  Boosting tracker already initialized.  Resetting now...\n"
          << std::endl;
      delete tracker_;
      tracker_ = NULL;
    }

    // Do the same for the image frame representation
    if (cur_frame_rep_ != NULL)
    {
      std::cerr
          << "OnlineBoostingAlgorithm::initialize(...) -- WARNING!  Boosting tracker already initialized.  Resetting now...\n"
          << std::endl;
      delete cur_frame_rep_;
      cur_frame_rep_ = NULL;
    }

    // (Re-)Initialize the boosting tracker
    cv::Size imageSize(image_.cols, image_.rows);
    cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
    cv::Rect tracking_rect = init_bounding_box;
    tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);
    tracker_ = new boosting::BoostingTracker(cur_frame_rep_, tracking_rect, wholeImage, params.num_classifiers_);

    // Initialize some useful tracking debugging information
    tracker_lost_ = false;

    // Return success
    return true;
  }

  //---------------------------------------------------------------------------
  bool
  OnlineBoostingAlgorithm::update(const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box,float & confidence)
  {
    // Import the image
    import_image(image);

    // Make sure the tracker has already been successfully initialized
    if (tracker_ == NULL)
    {
      std::cerr
          << "OnlineBoostingAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
          << std::endl;
      return false;
    }
    if (cur_frame_rep_ == NULL)
    {
      std::cerr
          << "OnlineBoostingAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
          << std::endl;
      return false;
    }

    // Calculate the patches within the search region
    cv::Size imageSize(image_.cols, image_.rows);
    cv::Rect wholeImage(0, 0, imageSize.width, imageSize.height);
    boosting::Patches *trackingPatches;
    cv::Rect searchRegion = tracker_->getTrackingROI(params.search_factor_);
    trackingPatches = new boosting::PatchesRegularScan(searchRegion, wholeImage, tracking_rect_size_, params.overlap_);

    cur_frame_rep_->setNewImageAndROI(image_, searchRegion);

    if (!tracker_->track(cur_frame_rep_, trackingPatches))
    {
      tracker_lost_ = true;
    }
    else
    {
      tracker_lost_ = false;
    }

    delete trackingPatches;

    // Save the new tracking ROI
    track_box = tracker_->getTrackedPatch();
	confidence= tracker_->getConfidence();
   /////////////////////////////////////////////////////////////should be output variable
	///////////////////////////////////////////////////////////////////////////////////////////////std::cout << "\rTracking confidence = " << tracker_->getConfidence();

    // Return success or failure based on whether or not the tracker has been lost
    return !tracker_lost_;
  }

  //---------------------------------------------------------------------------
  void
  OnlineBoostingAlgorithm::import_image(const cv::Mat & image)
  {
    // We want the internal version of the image to be gray-scale, so let's
    // do that here.  We'll handle cases where the input is either RGB, RGBA,
    // or already gray-scale.  I assume it's already 8-bit.  If not then 
    // an error is thrown.  I'm not going to deal with converting properly
    // from every data type since that shouldn't be happening.

    // Make sure the input image pointer is valid
    if (image.empty())
    {
      std::cerr << "OnlineBoostingAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
      exit(0); // <--- CV_ERROR?
    }

    // Now copy it in appropriately as a gray-scale, 8-bit image
    if (image.channels() == 4)
    {
      cv::cvtColor(image, image_, CV_RGBA2GRAY);
    }
    else if (image.channels() == 3)
    {
      cv::cvtColor(image, image_, CV_RGB2GRAY);
    }
    else if (image.channels() == 1)
    {
      image.copyTo(image_);
    }
    else
    {
      std::cerr << "OnlineBoostingAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
                << std::endl;
      exit(0);
    }
  }
  //
  //
  //

  //---------------------------------------------------------------------------
  SemiOnlineBoostingAlgorithm::SemiOnlineBoostingAlgorithm()
      :
        TrackingAlgorithm(),
        tracker_(0),
        cur_frame_rep_(0),
        tracker_lost_(false)
  {
  }

  //---------------------------------------------------------------------------
  SemiOnlineBoostingAlgorithm::~SemiOnlineBoostingAlgorithm()
  {
    if (tracker_ != NULL)
    {
      delete tracker_;
      tracker_ = NULL;
    }

    if (cur_frame_rep_ != NULL)
    {
      delete cur_frame_rep_;
      cur_frame_rep_ = NULL;
    }
  }

  //---------------------------------------------------------------------------
  bool
  SemiOnlineBoostingAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
                                          const CvRect& init_bounding_box)
  {
    // Import the image
    import_image(image);

    // If the boosting tracker has already been allocated, first de-allocate it
    if (tracker_ != NULL)
    {
      std::cerr
          << "OnlineBoostingAlgorithm::initialize(...) -- WARNING!  Boosting tracker already initialized.  Resetting now...\n"
          << std::endl;
      delete tracker_;
      tracker_ = NULL;
    }

    // Do the same for the image frame representation
    if (cur_frame_rep_ != NULL)
    {
      std::cerr
          << "OnlineBoostingAlgorithm::initialize(...) -- WARNING!  Boosting tracker already initialized.  Resetting now...\n"
          << std::endl;
      delete cur_frame_rep_;
      cur_frame_rep_ = NULL;
    }

    // (Re-)Initialize the boosting tracker
    cv::Size imageSize(image_.cols, image_.rows);
    cur_frame_rep_ = new boosting::ImageRepresentation(image_, imageSize);
    cv::Rect wholeImage = cv::Rect(0, 0, imageSize.width, imageSize.height);
    cv::Rect tracking_rect = init_bounding_box;
    tracking_rect_size_ = cv::Size(tracking_rect.width, tracking_rect.height);
    tracker_ = new boosting::SemiBoostingTracker(cur_frame_rep_, tracking_rect, wholeImage, params.num_classifiers_);

    // Initialize some useful tracking debugging information
    tracker_lost_ = false;

    // Return success
    return true;
  }

  //---------------------------------------------------------------------------
  bool
  SemiOnlineBoostingAlgorithm::update(const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box,float & confidence)
  {
    // Import the image
    import_image(image);

    // Make sure the tracker has already been successfully initialized
    if (tracker_ == NULL)
    {
      std::cerr
          << "OnlineBoostingAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
          << std::endl;
      return false;
    }
    if (cur_frame_rep_ == NULL)
    {
      std::cerr
          << "OnlineBoostingAlgorithm::update(...) -- ERROR!  Trying to call update without properly initializing the tracker!\n"
          << std::endl;
      return false;
    }

    // Calculate the patches within the search region
    cv::Size imageSize(image_.cols, image_.rows);
    cv::Rect wholeImage = cv::Rect(0, 0, imageSize.width, imageSize.height);
    boosting::Patches *trackingPatches;
    cv::Rect searchRegion = tracker_->getTrackingROI(params.search_factor_);
    trackingPatches = new boosting::PatchesRegularScan(searchRegion, wholeImage, tracking_rect_size_, params.overlap_);

    cur_frame_rep_->setNewImageAndROI(image_, searchRegion);

    if (!tracker_->track(cur_frame_rep_, trackingPatches))
    {
      tracker_lost_ = true;
    }
    else
    {
      tracker_lost_ = false;
    }

    delete trackingPatches;

    // Save the new tracking ROI
    track_box = tracker_->getTrackedPatch();
	confidence=tracker_->getConfidence();
    //std::cout << "\rTracking confidence = " << tracker_->getConfidence();

    // Return success or failure based on whether or not the tracker has been lost
    return !tracker_lost_;
  }

  //---------------------------------------------------------------------------
  void
  SemiOnlineBoostingAlgorithm::import_image(const cv::Mat & image)
  {
    // We want the internal version of the image to be gray-scale, so let's
    // do that here.  We'll handle cases where the input is either RGB, RGBA,
    // or already gray-scale.  I assume it's already 8-bit.  If not then 
    // an error is thrown.  I'm not going to deal with converting properly
    // from every data type since that shouldn't be happening.

    // Make sure the input image pointer is valid
    if (image.empty())
    {
      std::cerr << "OnlineBoostingAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
      exit(0); // <--- CV_ERROR?
    }

    // Now copy it in appropriately as a gray-scale, 8-bit image
    if (image.channels() == 4)
    {
      cv::cvtColor(image, image_, CV_RGBA2GRAY);
    }
    else if (image.channels() == 3)
    {
      cv::cvtColor(image, image_, CV_RGB2GRAY);
    }
    else if (image.channels() == 1)
    {
      image.copyTo(image_);
    }
    else
    {
      std::cerr << "OnlineBoostingAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
                << std::endl;
      exit(0);
    }
  }

  //
  //
  //

  //---------------------------------------------------------------------------
  OnlineMILAlgorithm::OnlineMILAlgorithm()
      :
        TrackingAlgorithm(),
        is_initialized(false)
  {
   cv::mil::RandomGenerator::initialize((int) time(0));
	//   cv::mil::RandomGenerator::initialize(100);
    clfparams_ = new cv::mil::ClfMilBoostParams();
    ftrparams_ = &haarparams_;
    clfparams_->_ftrParams = ftrparams_;
  }

  //---------------------------------------------------------------------------
  OnlineMILAlgorithm::~OnlineMILAlgorithm()
  {
    // delete here delete clfparams_;
  }

  //---------------------------------------------------------------------------
  bool
  OnlineMILAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
                                 const CvRect& init_bounding_box)
  {
    import_image(image);

    ((cv::mil::ClfMilBoostParams*) clfparams_)->_numSel = params.num_classifiers_;
    ((cv::mil::ClfMilBoostParams*) clfparams_)->_numFeat = params.num_features_;
    tracker_params_._posradtrain = params.pos_radius_train_;
    tracker_params_._negnumtrain = params.neg_num_train_;

    // Tracking parameters
    tracker_params_._init_negnumtrain = 65;
    tracker_params_._init_postrainrad = 3.0f;
    tracker_params_._initstate[0] = (float) init_bounding_box.x;
    tracker_params_._initstate[1] = (float) init_bounding_box.y;
    tracker_params_._initstate[2] = (float) init_bounding_box.width;
    tracker_params_._initstate[3] = (float) init_bounding_box.height;
    tracker_params_._srchwinsz = 25;
    tracker_params_._negsamplestrat = 1;
    tracker_params_._initWithFace = false;
    tracker_params_._debugv = false;
    tracker_params_._disp = false; // set this to true if you want to see video output (though it slows things down)

    clfparams_->_ftrParams->_width = (cv::mil::uint) init_bounding_box.width;
    clfparams_->_ftrParams->_height = (cv::mil::uint) init_bounding_box.height;

    tracker_.init(image_, tracker_params_, clfparams_);

    // Return success
    is_initialized = true;
    return true;
  }

  //---------------------------------------------------------------------------
  bool
  OnlineMILAlgorithm::update(const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box,float & confidence)
  {
    if (!is_initialized)
    {
      std::cerr << "OnlineMILAlgorithm::update() -- Error!  Did not intialize algorithm!\n" << std::endl;
      return false;
    }

    import_image(image);

    // Update tracker
    float f=tracker_.track_frame(image_);
	confidence= double(f);
    // Save output
    tracker_.getTrackBox(track_box);

    // Return success
    return true;
  }

  //---------------------------------------------------------------------------
  void
  OnlineMILAlgorithm::import_image(const cv::Mat & image)
  {
    // We want the internal version of the image to be gray-scale, so let's
    // do that here.  We'll handle cases where the input is either RGB, RGBA,
    // or already gray-scale.  I assume it's already 8-bit.  If not then 
    // an error is thrown.  I'm not going to deal with converting properly
    // from every data type since that shouldn't be happening.

    // Make sure the input image pointer is valid
    if (image.empty())
    {
      std::cerr << "OnlineBoostingAlgorithm::import_image(...) -- ERROR!  Input image pointer is NULL!\n" << std::endl;
      exit(0); // <--- CV_ERROR?
    }

    // Now copy it in appropriately as a gray-scale, 8-bit image
    if (image.channels() == 4)
    {
      cv::cvtColor(image, image_, CV_RGBA2GRAY);
    }
    else if (image.channels() == 3)
    {
      cv::cvtColor(image, image_, CV_RGB2GRAY);
    }
    else if (image.channels() == 1)
    {
      image.copyTo(image_);
    }
    else
    {
      std::cerr << "OnlineBoostingAlgorithm::import_image(...) -- ERROR!  Invalid number of channels for input image!\n"
                << std::endl;
      exit(0);
    }
  }

  //
  //
  //

  //---------------------------------------------------------------------------
  LINEMODAlgorithm::LINEMODAlgorithm()
      :
        TrackingAlgorithm()
  {
  }

  //---------------------------------------------------------------------------
  LINEMODAlgorithm::~LINEMODAlgorithm()
  {
  }

  //---------------------------------------------------------------------------
  bool
  LINEMODAlgorithm::initialize(const cv::Mat & image, const ObjectTrackerParams& params,
                               const CvRect& init_bounding_box)
  {
    // Return success
    return true;
  }

  //---------------------------------------------------------------------------
  bool
  LINEMODAlgorithm::update(const cv::Mat & image, const ObjectTrackerParams& params, cv::Rect & track_box,float & confidence)
  {
    // Return success
    return true;
  }

  //---------------------------------------------------------------------------
  void
  LINEMODAlgorithm::import_image(const cv::Mat & image)
  {
  }

  //
  //
  //

  //---------------------------------------------------------------------------
  ObjectTracker::ObjectTracker(const ObjectTrackerParams& params)
      :
        initialized_(false),
        tracker_(NULL)
  {
    // Store configurable parameters internally
    set_params(params);

    // Allocate the proper tracking algorithm (note: error-checking that a valid
    // tracking algorithm parameter is used is done in the ObjectTrackerParams
    // constructor, so at this point we are confident it's valid).
    switch (params.algorithm_)
    {
      case ObjectTrackerParams::CV_ONLINEBOOSTING:
        tracker_ = new OnlineBoostingAlgorithm();
        break;
      case ObjectTrackerParams::CV_SEMIONLINEBOOSTING:
        tracker_ = new SemiOnlineBoostingAlgorithm();
        break;
      case ObjectTrackerParams::CV_ONLINEMIL:
        tracker_ = new OnlineMILAlgorithm();
        break;
      case ObjectTrackerParams::CV_LINEMOD:
        tracker_ = new LINEMODAlgorithm();
        break;

	  case ObjectTrackerParams::CV_CAMSHIFT:
        tracker_ = new CamShiftAlgorithm();
        break;
      case ObjectTrackerParams::CV_PHASECORR:
        tracker_ = new PhaseCorrAlgorithm();
        break;
      case ObjectTrackerParams::CV_NCC :
        tracker_ = new NORMCCAlgorithm();
        break;
	  case ObjectTrackerParams::CV_MNCC :
        tracker_ = new MNORMCCAlgorithm();
        break;
      case ObjectTrackerParams::CV_TLD:
        tracker_ = new TLDAlgorithm();
        break;

	  case ObjectTrackerParams::CV_CMT:
        tracker_ = new CMTAlgorithm();
        break;

	  case ObjectTrackerParams::CV_CT:
        tracker_ = new COMPRESSIVEAlgorithm();
        break;
	   case ObjectTrackerParams::CV_STRUCK:
        tracker_ = new STRUCKAlgorithm();
        break;  
	   case ObjectTrackerParams::CV_KCF:
		   tracker_ = new KCFAlgorithm();
		   break;
	   case ObjectTrackerParams::CV_DSST:
		   tracker_ = new DSSTAlgorithm();
		   break;
	  case ObjectTrackerParams::CV_CFTLD:
		   tracker_ = new CFTLDAlgorithm();
		   break;
	  case ObjectTrackerParams::CV_SKCF:
		  tracker_ = new skcfAlgorithm();
		  break;
	  case ObjectTrackerParams::CV_Thresh:
		  tracker_=new ThreshAlgorithm();
			  break;
	  case ObjectTrackerParams::CV_Mosse:
		  tracker_ = new MosseAlgorithm();
		  break;

	  default:
        // By default, if an invalid choice somehow gets through lets use online boosting?
        // Or throw an error and don't continue?
        tracker_ = new OnlineBoostingAlgorithm();
        break;
    }
	
  }

  //---------------------------------------------------------------------------
  ObjectTracker::~ObjectTracker()
  {
    // Delete the tracking algorithm object, if it was allocated properly
    if (tracker_ != NULL)
    {
		

      delete tracker_;
	  /*cv::namedWindow("tracking algorithm deleted");
	  cv::waitKey();*/
    }
  }

  //---------------------------------------------------------------------------
  bool
  ObjectTracker::initialize(const cv::Mat & image, const CvRect& bounding_box)
  {
    // Initialize the tracker and if it works, set the flag that we're now initialized
    // to true so that update() can work properly.
	cv::Mat Dummy=Mat(image,bounding_box);
	Dummy.copyTo (Template);
    
    bool success = tracker_->initialize(image, tracker_params_, bounding_box);
    if (success)
    {
      initialized_ = true;
    }
    else
    {
      initialized_ = false;
    }

    // Return success or failure
    return success;
  }

  //---------------------------------------------------------------------------
  bool
  ObjectTracker::update(const cv::Mat & image, cv::Rect & track_box,float& confidence )
  {
    // First make sure we have already initialized.  Otherwise we can't continue.
    if (!initialized_)
    {
      std::cerr << "ObjectTracker::update() -- ERROR! The ObjectTracker needs to be initialized before updating.\n";
      return false;
    }

    // Update the tracker and return whether or not it succeeded
    bool success = tracker_->update(image, tracker_params_, track_box,confidence);	
    // Return success or failure
	//returnTemplate(gettempla);
    return success;
  }

  //---------------------------------------------------------------------------
  void
  ObjectTracker::set_params(const ObjectTrackerParams& params)
  {
    tracker_params_ = params;
  }
 //----------------------------------------------------------------------------
  void
  ObjectTracker::returnTemplate(cv::Mat &temp)
  {
	  temp=this->Template;
  }

}
