
#if CV_MAJOR_VERSION > 2
   #include <opencv2/highgui/highgui.hpp>
   #include <opencv2/imgproc/imgproc.hpp>
#else
 #include "opencv2/highgui/highgui.hpp"
#endif
#include "opencv2/core/core.hpp"
#include <vector>
#include <iostream>
typedef unsigned char byte;
static cv::Scalar CursorColor=cv::Scalar(0,255,0);
static int cusorw=20;
static double DPT=0.25;
static int fontFace =cv::FONT_ITALIC;// FONT_HERSHEY_SCRIPT_SIMPLEX;
static double fontScale = 0.75;
static int thickness = 2; 
static std::string Algoritthm[8]={ "DSST","SKCF","TLD","KCF","Mil","CMT","CAMSHIFT","CT"};//Mil
static int Algonumber[8]        ={13,        16,       8   ,14  ,4, 9   ,5 ,10};//3
static cv::Scalar WhiteColor=cv::Scalar(255,255,255);
static  cv::Scalar EColor=cv::Scalar(0,0,0);
static  cv::Scalar BEColor=cv::Scalar(0,0,0);
static  cv::Scalar TColor(cv::Scalar(200,0,0));
static  cv::Scalar BTColor=cv::Scalar(0,0,0);
static  cv::Scalar GoastColor=cv::Scalar (0,128,255);
static cv::Scalar TarOk=cv::Scalar (0,255,255);
static cv::Scalar TarLost=cv::Scalar (0,0,193);
static cv::Scalar CrossColor(0,255,0);

static int CornerL=8;
static int TarqL=64;//was 32
//static double Viewx;
typedef struct{
	short P;
	short T;
	byte Algo;
	float toc;
	bool drawE;
	bool drawT;
	float Danglex;
	float Dangley;
	bool DrawTar;
	cv::Point LTtar;
	bool TrackingState;
	bool DrawGoast;
	cv::Rect GT;
	cv::Rect Selection;
	cv::Rect BB;
	double Viewx;
	cv::Mat Temp;
	bool DrawTemp;
}DrawingHomingStruct;
typedef struct{
	
	ushort P;
	ushort T;
	byte Algo;
	float toc;
	bool drawE;
	bool drawT;
	float Danglex;
	float Dangley;
	bool DrawTar;
	cv::Scalar TarColor;
	cv::Point LTtar;
	bool TrackingState;
	bool DrawGoast;
	cv::Rect GT;
	cv::Rect Selection;
	cv::Rect BB;
	cv::Point Cross;
	cv::Mat Temp;
	bool DrawTemp;
	bool saving; 
	ushort dis1;
	ushort dis2;
	byte laser_status;
	/*bool drawTar;
	Mat Temp;*/
}DrawingSeaProjectsStruct;
cv::Mat Osd(cv::Mat& frame, ushort P, ushort T, byte Algo, float toc, bool DrawE, bool DrawT, float Danglex, float Dangley, bool DrawTar, cv::Point LTtar, bool TrackingState, bool DrawGoast, cv::Rect GT, cv::Rect Selection, cv::Rect BB, double Viewx,  double dpT =DPT,bool printM=false);// hoda
struct DrawComp{
  cv::Point Position;
  cv::Scalar *Color;
  int Kind;
  std::string format;
  void* val;

};
 /*class DrawingComp{
	
	public:
    DrawingComp();
    virtual
    ~DrawingComp();
	virtual
		void View(cv::Mat& image)=0;
	int id;
	bool *Draw;
	DrawComp Comp;
	
};

class DrawingText : public DrawingComp
{
	public:
	DrawingText();
	~DrawingText();
	
	void View(cv::Mat& image);
	int K;
	
};
class DrawingShape : public DrawingComp
{
	public:
	DrawingShape();
	~DrawingShape();
	
	void View(cv::Mat& image);
	int K;
	
};

class ListDrawingComp{
  public: 
	  ListDrawingComp();
	  ~ListDrawingComp();
	int size;

	DrawingComp* Next,*Begin,*End;	
	int N;
	void Add(DrawingComp *Comp);
	DrawingComp* GetIndex(int i);
	void empty();
private:
	DrawingComp* Pointers[128];
	
};
*/
// The base (abstract) OSD Func class, to define the interface
  
 class OSDT
  {
  public:
    OSDT();
    virtual
    ~OSDT();

    virtual bool
    initialize( void* DrawStuct,cv::Mat &image) = 0;
	void* Drawings;
	virtual bool  View(float dpt = 0.25, bool printM = false) = 0;
	virtual bool SetImage(cv::Mat &image)=0;

	
  protected:
    // A method to import an image to the type desired for the current algorithm
   /* virtual void
    import_image(const cv::Mat & image) ;*/

    // A local image holder (can be gray-scale, color, depth image 16-bit, whatever
    // you want...)
    cv::Mat image_;
  };

  // A speficic instance of OSD Class: Homing Apps
  
  class HomingOSD: public OSDT  {
  public:
    HomingOSD();
    ~HomingOSD();

    bool
    initialize(void* DrawStuct,cv::Mat &image);

    bool View(float dpt=0.25,bool PrintM=false);
	bool SetImage(cv::Mat &image);
	
  protected:
	 // void DrawComp(DrawingComp D);
    // A method to import an image to the type desired for the current algorithm
    //void
    //import_image(const cv::Mat & image);

  private:
    // The main homing osd
    
    bool is_initialized;
  };


   // A speficic instance of OSD Class: Homing Apps
  
  class SeaProjectsOSD: public OSDT  {
  public:
    SeaProjectsOSD();
    ~SeaProjectsOSD();

    bool
    initialize(void* DrawStuct,cv::Mat &image);

	bool View(float dpt = 0.25, bool PrintM = false);
	bool SetImage(cv::Mat &image);
	
  protected:
	 // void DrawComp(DrawingComp D);
    // A method to import an image to the type desired for the current algorithm
    //void
    //import_image(const cv::Mat & image);

  private:
    // The main homing osd
    
    bool is_initialized;
  };
