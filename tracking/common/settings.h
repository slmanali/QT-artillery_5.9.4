#include <iostream> 
#include <opencv2/core/core.hpp>
//#include <opencv2\highgui\ios.h>
#include "opencv/cxcore.h"
#include "ini_file.h"

typedef  struct {
    
    int ImageWidth ;
    int ImageHeight ;
	int DCursorx;
	int DCursory;
	int CamNum;// -1 video filename defined bellow
	int defaultAlgo; // default algorithm
	bool KeyBoardAlgo;//0 change algorithm from keyboard 
	                  //1 change algorithm from hardware
	int MaxWinWidth;
	int initWinWidth;
    cv::Point CenterCursor; 

}ConfigStruct;
typedef  struct {
    
    int ImageWidth ;
    int ImageHeight ;
	int CamNum;// -1 video filename defined bellow
	int defaultAlgo; // default algorithm
	float ratiomax;
    float ratiomin;
	int enableZoomControl;
	
}ConfighomingStruct;
typedef  struct {
    
    int ImageWidth ;
    int ImageHeight ;
	int DCursorx;
	int DCursory;
	int CamNum;// -1 video filename defined bellow
	int defaultAlgo; // default algorithm
	bool KeyBoardAlgo;//0 change algorithm from keyboard 
	                  //1 change algorithm from hardware
	int MaxWinWidth;
	int initWinWidth;
	float ratiomax;
	float ratiomin;
	int enableZoomControl;

    cv::Point CenterCursor; 

}ConfigSeaStruct;
typedef  struct {
    
    std::string Port ;
    int BaudRate ;
	int StopBits;
	int DataBits;
	int Parity;// 
	int FlowControl; 
	int dt;
	int stabilizeron;
}ConfigPortStruct;

void saveConfig(ConfigStruct St);
void save_Sea_Config(ConfigSeaStruct St);
void save_Homing_Config(ConfighomingStruct St);
void save_Port_Config(ConfigPortStruct St);
void save_Port1_Config(ConfigPortStruct St);

void loadConfig(ConfigStruct& St);
void load_Sea_Config(ConfigSeaStruct& St);
void load_Homing_Config(ConfighomingStruct& St);
void load_Port_Config(ConfigPortStruct& St);
void load_Port2_Config(ConfigPortStruct& SysSt, ConfigPortStruct& St);
static CIniFile ifile;
