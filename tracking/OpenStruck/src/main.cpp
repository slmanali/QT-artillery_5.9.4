/* 
 * Struck: Structured Output Tracking with Kernels
 * 
 * Code to accompany the paper:
 *   Struck: Structured Output Tracking with Kernels
 *   Sam Hare, Amir Saffari, Philip H. S. Torr
 *   International Conference on Computer Vision (ICCV), 2011
 * 
 * Copyright (C) 2011 Sam Hare, Oxford Brookes University, Oxford, UK
 * 
 * This file is part of Struck.
 * 
 * Struck is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Struck is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Struck.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */
 
#include "Tracker.h"
#include "Config.h"

#include <iostream>
#include <fstream>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "vot.hpp"

using namespace std;
//using namespace cv;
cv::Rect box; // tracking object
bool drawing_box = false;
bool gotBB = false;	// got tracking box or not
bool fromfile = false;
bool doInitialise = false;
static const int kLiveBoxWidth = 80;
static const int kLiveBoxHeight = 80;
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
        gotBB = false;
		drawing_box = true;
		box = cv::Rect(x, y, 0, 0);
		break;
	case CV_EVENT_LBUTTONUP:
		drawing_box = false;
		if (box.width < 0)
		{
			box.x += box.width;
			box.width *= -1;
		}
		if( box.height < 0 )
		{
			box.y += box.height;
			box.height *= -1;
		}
		gotBB = true;
		doInitialise=true;
		break;
	default:
		break;
	}
}

void rectangle(cv::Mat& rMat, const FloatRect& rRect, const cv::Scalar& rColour)
{
	IntRect r(rRect);
    cv::rectangle(rMat, cv::Point(r.XMin(), r.YMin()), cv::Point(r.XMax(), r.YMax()), rColour);
}

int main(int argc, char* argv[])
{
	// read config file
	string configPath = "config.txt";
	if (argc > 1)
	{
		configPath = argv[1];
	}
	Config conf;//(configPath);
	conf.SetDefaults();
	cout << conf << endl;
	conf.debugMode=true;   // omar
	
	if (conf.features.size() == 0)
	{
		cout << "error: no features specified in config" << endl;
		return EXIT_FAILURE;
	}
	
	Tracker tracker(conf);

	//Check if --challenge was passed as an argument
	bool challengeMode = false;
	
	
	//ofstream outFile;
	//if (conf.resultsPath != "")
	//{
	//	outFile.open(conf.resultsPath.c_str(), ios::out);
	//	if (!outFile)
	//	{
	//		cout << "error: could not open results file: " << conf.resultsPath << endl;
	//		return EXIT_FAILURE;
	//	}
	//}
	
	// if no sequence specified then use the camera
	bool useCamera = (conf.sequenceName == "");
	
    cv::VideoCapture cap;
	
	int startFrame = -1;
	int endFrame = -1;
	FloatRect initBB;
	string imgFormat;
	float scaleW = 1.f;
	float scaleH = 1.f;
	
	if (useCamera)
	{
		if (!cap.open(0))
		{
			cout << "error: could not start camera capture" << endl;
			return EXIT_FAILURE;
		}
		cap.set(CV_CAP_PROP_FRAME_HEIGHT,240);
	    cap.set(CV_CAP_PROP_FRAME_WIDTH,320);
		startFrame = 0;
		endFrame = INT_MAX;
        cv::Mat tmp;
		cap >> tmp;
		scaleW = (float)conf.frameWidth/tmp.cols;
		scaleH = (float)conf.frameHeight/tmp.rows;

		initBB = IntRect(conf.frameWidth/2-kLiveBoxWidth/2, conf.frameHeight/2-kLiveBoxHeight/2, kLiveBoxWidth, kLiveBoxHeight);
		cout << "press 'i' to initialise tracker" << endl;
	}
	else
	{
		// parse frames file
		string framesFilePath = conf.sequenceBasePath+"/"+conf.sequenceName+"/"+conf.sequenceName+"_frames.txt";
		ifstream framesFile(framesFilePath.c_str(), ios::in);
		if (!framesFile)
		{
			cout << "error: could not open sequence frames file: " << framesFilePath << endl;
			return EXIT_FAILURE;
		}
		string framesLine;
		getline(framesFile, framesLine);
		sscanf(framesLine.c_str(), "%d,%d", &startFrame, &endFrame);
		if (framesFile.fail() || startFrame == -1 || endFrame == -1)
		{
			cout << "error: could not parse sequence frames file" << endl;
			return EXIT_FAILURE;
		}
		
		imgFormat = conf.sequenceBasePath+"/"+conf.sequenceName+"/imgs/img%05d.png";
		
		// read first frame to get size
		char imgPath[256];
		sprintf(imgPath, imgFormat.c_str(), startFrame);
        cv::Mat tmp = cv::imread(imgPath, 0);
		scaleW = (float)conf.frameWidth/tmp.cols;
		scaleH = (float)conf.frameHeight/tmp.rows;
		
		// read init box from ground truth file
		string gtFilePath = conf.sequenceBasePath+"/"+conf.sequenceName+"/"+conf.sequenceName+"_gt.txt";
		ifstream gtFile(gtFilePath.c_str(), ios::in);
		if (!gtFile)
		{
			cout << "error: could not open sequence gt file: " << gtFilePath << endl;
			return EXIT_FAILURE;
		}
		string gtLine;
		getline(gtFile, gtLine);
		float xmin = -1.f;
		float ymin = -1.f;
		float width = -1.f;
		float height = -1.f;
		sscanf(gtLine.c_str(), "%f,%f,%f,%f", &xmin, &ymin, &width, &height);
		if (gtFile.fail() || xmin < 0.f || ymin < 0.f || width < 0.f || height < 0.f)
		{
			cout << "error: could not parse sequence gt file" << endl;
			return EXIT_FAILURE;
		}
		initBB = FloatRect(xmin*scaleW, ymin*scaleH, width*scaleW, height*scaleH);
	}
	
	
	
	if (!conf.quietMode)
	{
        cv::namedWindow("result");
	}
    cv::setMouseCallback("result", mouseHandler, NULL);
    cv::Mat result(conf.frameHeight, conf.frameWidth, CV_8UC3);
	bool paused = false;
	
	srand(conf.seed);
    cv::Mat frameOrig;
	for (int frameInd = startFrame; frameInd <= endFrame; ++frameInd)
	{
		
		if (useCamera)
		{
		
			cap >> frameOrig;
			frameOrig.copyTo(result);
			while(!gotBB)
			{
	
				
				cap>>frameOrig;
                cv::rectangle(frameOrig, box, cv::Scalar(0,0,255));
                cv::imshow("result", frameOrig);
				doInitialise=true;
				initBB = IntRect(box.x, box.y,box.width, box.height);
	           if (tracker.IsInitialised())
				{
					tracker.Reset();
				}
				if (cvWaitKey(33) == 'q') {	return 0; }
			}
			if (doInitialise)
			{
				tracker.Initialise(frameOrig, initBB);
				
				doInitialise = false;
			}
		
		}
	
		
		if (tracker.IsInitialised())
		{
            int64 t=cv::getTickCount();
			tracker.Track(frameOrig);
		//	printf("time=%f \n",(float)(getTickCount()-t)/getTickFrequency()*1000.0);
			if (!conf.quietMode && conf.debugMode)
			{
				tracker.Debug();
			}
			
            rectangle(result, tracker.GetBB(), CV_RGB(0, 255, 0));
            cout<<" bestScore ="<<tracker.bestScore<<"time="<< (float)(cv::getTickCount()-t)/cv::getTickFrequency()*1000.0<<endl;
		/*	if (outFile)
			{
				const FloatRect& bb = tracker.GetBB();
				outFile << bb.XMin()/scaleW << "," << bb.YMin()/scaleH << "," << bb.Width()/scaleW << "," << bb.Height()/scaleH << endl;
			}*/
		}

		if (!conf.quietMode)
		{
            cv::imshow("result", result);
            int key = cv::waitKey(paused ? 0 : 1);
			if (key != -1)
			{
				if (key == 27 || key == 113) // esc q
				{
					break;
				}
				else if (key == 112) // p
				{
					paused = !paused;
				}
				else if (key == 105 && useCamera)
				{
					doInitialise = true;
				}
			}
			if (conf.debugMode && frameInd == endFrame)
			{
				cout << "\n\nend of sequence, press any key to exit" << endl;
                cv::waitKey();
			}
		}

	}
	
/*	if (outFile.is_open())
	{
		outFile.close();
	}*/
	
	return EXIT_SUCCESS;
}
