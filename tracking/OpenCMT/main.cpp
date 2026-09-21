#include "CMT.h"
//#include "gui.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <fstream>
#include <cstdio>


using cv::cmttracker::CMT;
using cv::imread;
using cv::namedWindow;
using cv::Scalar;
using cv::VideoCapture;
using cv::waitKey;
using std::cerr;
using std::istream;
using std::ifstream;
using std::stringstream;
using std::ofstream;
using std::cout;
using std::min_element;
using std::max_element;
using std::endl;
using ::atof;
//Initialization bounding box
   Rect rect;
bool drawing_box = false;
bool gotBB = false;	// got tracking box or not
bool init =false;
static string WIN_NAME = "CMT";

vector<float> getNextLineAndSplitIntoFloats(istream& str)
{
    vector<float>   result;
    string                line;
    getline(str,line);

    stringstream          lineStream(line);
    string                cell;
    while(getline(lineStream,cell,','))
    {
        result.push_back(atof(cell.c_str()));
    }
    return result;
}

int display(Mat im, CMT & cmt)
{
    //Visualize the output
    //It is ok to draw on im itself, as CMT only uses the grayscale image
    for(size_t i = 0; i < cmt.points_active.size(); i++)
    {
        circle(im, cmt.points_active[i], 2, Scalar(255,0,0));
    }

    Point2f vertices[4];
    cmt.bb_rot.points(vertices);
    for (int i = 0; i < 4; i++)
    {
        line(im, vertices[i], vertices[(i+1)%4], Scalar(255,0,0));
    }

    imshow(WIN_NAME, im);

    return waitKey(5);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mouseHandler(int event, int x, int y, int flags, void *param)
{
	switch (event)
	{
	case CV_EVENT_MOUSEMOVE:
		if (drawing_box)
		{
			rect.width = x - rect.x;
			rect.height = y -rect.y;
		}
		break;
	case CV_EVENT_LBUTTONDOWN:
		drawing_box = true;
		rect = Rect(x, y, 0, 0);
		break;
	case CV_EVENT_LBUTTONUP:
		drawing_box = false;
		if (rect.width < 0)
		{
			rect.x += rect.width;
			rect.width *= -1;
		}
		if( rect.height < 0 )
		{
			rect.y += rect.height;
			rect.height *= -1;
		}
		gotBB = true;
		init=true;
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    //Create a CMT object
    CMT cmt;

    //Initialization bounding box
    //Rect rect;  //omar

    //Parse args
    
    int loop_flag = 0;
    int verbose_flag = 1;
    FILELog::ReportingLevel() = verbose_flag ? logDEBUG : logINFO;
    Output2FILE::Stream() = stdout; //Log to stdout

    //Normal mode

    //Create window
    namedWindow(WIN_NAME);

    VideoCapture cap;

    bool show_preview = true;

    //If no input was specified
        cap.open(0); //Open default camera device
		cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
	    cap.set(CV_CAP_PROP_FRAME_WIDTH,640);

    //Else open the video specified by input_path

    //If it doesn't work, stop
    if(!cap.isOpened())
    {
        cerr << "Unable to open video capture." << endl;
        return -1;
    }

 
	namedWindow(WIN_NAME, CV_WINDOW_AUTOSIZE);
	cv::setMouseCallback(WIN_NAME, mouseHandler, NULL);
    //Get initial image
    Mat last_gray;

    //If no bounding was specified, get it from user
	// Initialization
/*	while(!gotBB)
	{
	
		//first.copyTo(im0);
   	    Mat im0;
 	    cap>>im0;
		cvtColor(im0, last_gray, CV_RGB2GRAY);
		rectangle(im0, rect, Scalar(0,0,255));
		imshow(WIN_NAME, im0);
		if (cvWaitKey(33) == 'q') {	return 0; }
	}
	// Remove callback
//	cv::setMouseCallback(WIN_NAME, NULL, NULL);
	// CMT initialization
	if(init)
	{
	  cmt.initialize(last_gray,rect);
	  init=false;
	}*/
	Mat im0;
	while(true)
	{
	    	
			// Initialization
			while(!gotBB)
			{
	
				
				cap>>im0;
				cvtColor(im0, last_gray, CV_RGB2GRAY);
				rectangle(im0, rect, Scalar(0,0,255));
				imshow(WIN_NAME, im0);
				if (cvWaitKey(33) == 'q') {	return 0; }
			}
			// Remove callback
			//	cv::setMouseCallback(WIN_NAME, NULL, NULL);
			// CMT initialization
			if(init)
			{  
				CMT();
				cmt.initialize(last_gray,rect);
				init=false;
				continue;
			}

		// get frame
		// Run-time
	    Mat current_gray;
	    Mat frame;
		if (loop_flag) im0.copyTo(frame);
		else cap>>frame;
		double t=cv::getTickCount();
		cvtColor(frame, current_gray, CV_RGB2GRAY);
		// Process Frame
		if(cmt.processFrame(current_gray))
		{
		// Draw Points
		rectangle(frame, cmt.bb_rot.boundingRect(), Scalar(0,255,0),2);
		/*Point2f vertices[4];
        cmt.bb_rot.points(vertices);
        for (int i = 0; i < 4; i++)
         {
          line(frame, vertices[i], vertices[(i+1)%4], Scalar(255,0,0));
         }*/
		}
		//rectangle(frame, rect, Scalar(0,0,255));
		// Display
		imshow(WIN_NAME, frame);
	     printf("Current Tracking time=%f  number of interest points=%d\n", (cv::getTickCount()-t)/cv::getTickFrequency()*1000,cmt.points_active.size());

		//printf("Current Tracking Box = x:%d y:%d h:%d w:%d time=%f \n", box.x, box.y, box.width, box.height,(cv::getTickCount()-t)/getTickFrequency());
		current_gray.copyTo(last_gray);
		if (cvWaitKey(33) == 'q') {	break; }
		if(cvWaitKey(33) == 'i'){init=true;}
	}	
	
    return 0;
}
