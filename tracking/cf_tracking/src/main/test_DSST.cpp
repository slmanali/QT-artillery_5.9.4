/************************************************************************
* File:	RunTracker.cpp
* Brief: C++ demo for Kaihua Zhang's paper:"Real-Time Compressive Tracking"
* Version: 1.0
* Author: Yang Xian
* Email: yang_xian521@163.com
* Date:	2012/08/03
* History:
************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <tclap/CmdLine.h>
#include <iostream>

#include <fstream>
#include <sstream>
#include <cstdio>
#include "../tracking/cf_tracking/src/cf_libs/dsst/dsst_tracker.hpp"
#include "tracker_run.hpp"
using namespace cv;
using namespace std;

Rect box; // tracking object
bool drawing_box = false;
bool gotBB = false;	// got tracking box or not
bool fromfile = false;
string video;


// tracking box mouse callback
void mouseHandler(int event, int x, int y, int flags, void *param)
{
	switch (event)
	{
	case CV_EVENT_MOUSEMOVE:
		if (drawing_box)
		{
			box.width = x - box.x;
			box.height = y - box.y;
		}
		break;
	case CV_EVENT_LBUTTONDOWN:
		drawing_box = true;
		box = Rect(x, y, 0, 0);
		break;
	case CV_EVENT_LBUTTONUP:
		drawing_box = false;
		if (box.width < 0)
		{
			box.x += box.width;
			box.width *= -1;
		}
		if (box.height < 0)
		{
			box.y += box.height;
			box.height *= -1;
		}
		gotBB = true;
		break;
	default:
		break;
	}
}

void print_help(void)
{
	printf("use:\n     welcome to use CompressiveTracking\n");
	printf("Kaihua Zhang's paper:Real-Time Compressive Tracking\n");
	printf("C++ implemented by yang xian\nVersion: 1.0\nEmail: yang_xian521@163.com\nDate:	2012/08/03\n\n");
	printf("-v    source video\n-b        tracking box file\n");
}




int main(int argc, char * argv[])
{
	VideoCapture capture;//("F:\\video_samples\\SeaFilm.mpg");
	capture.open(0);
	// Read options
	//read_options(argc, argv, capture);
	// Init camera
	if (!capture.isOpened())
	{
		cout << "capture device failed to open!" << endl;
		return 1;
	}
	// Register mouse callback to draw the tracking box
	namedWindow("CT", CV_WINDOW_AUTOSIZE);
	setMouseCallback("CT", mouseHandler, NULL);
	// CT framework
	cf_tracking::DsstParameters paras;
/*paras.padding = static_cast<double>(1.6 );
	paras.outputSigmaFactor = static_cast<double>(0.05);
	paras.lambda = static_cast<double>(0.01);
	paras.learningRate = static_cast<double>(0.012);
	paras.templateSize = 100;
	paras.cellSize = 2;

	paras.enableTrackingLossDetection = false;
	paras.psrThreshold = 13.5;
	paras.psrPeakDel = 1;

	paras.enableScaleEstimator = true;
	paras.scaleSigmaFactor = static_cast<double>(0.25);
	paras.scaleStep = static_cast<double>(1.02);
	paras.scaleCellSize = 4;
	paras.numberOfScales = 33;

	paras.originalVersion = false;
	paras.resizeType = cv::INTER_AREA;	
	paras.useFhogTranspose = false;*/
/*	TCLAP::CmdLine *cmd;
	TCLAP::SwitchArg debugOutput("v", "debug", "Output Debug info!", cmd, false);
	TCLAP::SwitchArg originalVersion("", "original_version", "Use the original parameters found in the DSST paper. Performance is close, "
		"but differences do still exist!", cmd, false);
	TCLAP::ValueArg<int> templateSize("", "para_template_size", "template size", false,
		paras.templateSize, "integer", cmd);
	TCLAP::ValueArg<double> padding("", "para_padding", "padding around the target", false,
		paras.padding, "double", cmd);
	TCLAP::ValueArg<double> outputSigmaFactor("", "para_output_sigma_factor", "spatial bandwitdh of the target",
		false, paras.outputSigmaFactor, "double", cmd);
	TCLAP::ValueArg<int> cellSize("", "para_cell_size", "cell size of fhog", false, paras.cellSize, "integer", cmd);
	TCLAP::ValueArg<double> lambda("", "para_lambda", "regularization factor", false, paras.lambda, "double", cmd);
	TCLAP::ValueArg<double> interpFactor("", "para_interpFactor", "interpolation factor for learning",
		false, paras.learningRate, "double", cmd);
	TCLAP::ValueArg<double> scaleSigmaFactor("", "para_scale_sigma_factor", "spatial bandwitdh of the target(scale)",
		false, paras.scaleSigmaFactor, "double", cmd);
	TCLAP::ValueArg<double> scaleStep("", "para_scale_step", "scale_step", false, paras.scaleStep, "double", cmd);
	TCLAP::ValueArg<int> scaleCellSize("", "para_scale_cell_size", "cell size of fhog (scale filter)", false, paras.scaleCellSize, "integer", cmd);
	TCLAP::ValueArg<int> numberOfScales("", "para_scale_number", "number of scale steps", false, paras.numberOfScales, "integer", cmd);
	TCLAP::SwitchArg enableTrackingLossDetection("", "para_enable_tracking_loss", "Enable the tracking loss detection!", cmd, paras.enableTrackingLossDetection);
	TCLAP::ValueArg<double> psrThreshold("", "para_psr_threshold",
		"if psr is lower than psr threshold, tracking will stop",
		false, paras.psrThreshold, "double", cmd);
	TCLAP::ValueArg<int> psrPeakDel("", "para_psr_peak_del", "amount of pixels that are deleted"
		"for psr calculation around the peak (1 means that a window of 3 by 3 is deleted; 0 means"
		"that max response is deleted; 2 * peak_del + 1 pixels are deleted)",
		false, paras.psrPeakDel, "integer", cmd);

	cmd->parse(argc, argv);*/

	/*paras.padding = padding.getValue();
	paras.outputSigmaFactor = outputSigmaFactor.getValue();
	paras.lambda = lambda.getValue();
	paras.learningRate = interpFactor.getValue();
	paras.cellSize = cellSize.getValue();

	paras.scaleSigmaFactor = scaleSigmaFactor.getValue();
	paras.scaleStep = scaleStep.getValue();
	paras.scaleCellSize = scaleCellSize.getValue();
	paras.numberOfScales = numberOfScales.getValue();
	paras.psrThreshold = psrThreshold.getValue();
	paras.psrPeakDel = psrPeakDel.getValue();
	paras.templateSize = templateSize.getValue();
	paras.enableTrackingLossDetection = enableTrackingLossDetection.getValue();*/

	cf_tracking::DsstTracker *ct = new cf_tracking::DsstTracker(paras);
	cv::Rect_<double> _boundingBox;
	Mat frame;
	Mat last_gray;
	Mat first;

/*
-		paras	{padding=1.6000000000000001 outputSigmaFactor=0.050000000000000003 lambda=0.010000000000000000 ...}	cf_tracking::DsstParameters

*/
	if (fromfile)
	{
		capture >> frame;
		cvtColor(frame, last_gray, CV_RGB2GRAY);
		frame.copyTo(first);
	}
	else
	{
		capture.set(CV_CAP_PROP_FRAME_WIDTH, 720);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, 576);
	}

	// Initialization
	while (!gotBB)
	{
		if (!fromfile)
		{
			capture >> frame;
		}
		else
		{
			first.copyTo(frame);
		}
		cvtColor(frame, last_gray, CV_RGB2GRAY);
		rectangle(frame, box, Scalar(0, 0, 255));
		imshow("CT", frame);
		if (cvWaitKey(33) == 'q') { return 0; }
	}
	_boundingBox = Rect_<double>(static_cast<double>(box.x),
		static_cast<double>(box.y),
		static_cast<double>(box.width),
		static_cast<double>(box.height));
	bool _targetOnFrame = ct->reinit(frame, _boundingBox);
	// Remove callback
	setMouseCallback("CT", NULL, NULL);
	printf("Initial Tracking Box = x:%d y:%d h:%d w:%d\n", box.x, box.y, box.width, box.height);
	
	// Run-time
	Mat current_gray;

	while (capture.read(frame))
	{
		// get frame
		double t = getTickCount();
		ct->update(frame, box);

		// Display
		// Draw Points
	
		printf("Current Tracking Box = x:%d y:%d h:%d w:%d fps=%f \n", box.x, box.y, box.width, box.height,1.0/( (getTickCount() - t) / getTickFrequency()));
		rectangle(frame, box, Scalar(0, 0, 255));
		imshow("CT", frame);
		if (cvWaitKey(13) == 't'){
			cout << "update"<< endl;
			ct->updateAt(frame, box);
		}
		if (cvWaitKey(13) == 'q') { break; }
	}
	delete ct;
	return 0;
}
