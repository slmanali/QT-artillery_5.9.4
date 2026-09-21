#include "OsdFuncs.h"
#if CV_MAJOR_VERSION > 2
   #include <opencv2/highgui/highgui.hpp>
   #include <opencv2/imgproc/imgproc.hpp>
#else
 #include "opencv2/highgui/highgui.hpp"
#endif
using namespace std;
//using namespace cv;
void DrawingCross(cv::Mat Src,cv::Scalar Color)
{
        // drawing Cross;      
	    cv::line(Src,cv::Point(Src.cols/2-cusorw,Src.rows/2),cv::Point(Src.cols/2+cusorw,Src.rows/2),CursorColor,3);
        cv::line(Src,cv::Point(Src.cols/2,Src.rows/2-cusorw),cv::Point(Src.cols/2,Src.rows/2+cusorw),CursorColor,3);
}


void DrawTarSea(cv::Mat Src,cv::Point Cen,cv::Rect tarrect,cv::Scalar Color)
{
	
	 cv::rectangle (Src,tarrect,Color,2,0,0);
	 cv::Point P1,P2;

	 P1=Cen;
	 P1.x=P1.x-10;
	 P2=P1;
	 P2.x=P2.x-10;
	 cv::line(Src,P1,P2,Color,2);

	 P1=Cen;
	 P1.x=P1.x+10;
	 P2=P1;
	 P2.x=P2.x+10;
	 cv::line(Src,P1,P2,Color,2);
	 P1=Cen;
	 P1.y=P1.y-9;
	 P2=P1;
	 P2.y=P2.y-9;
	 cv::line(Src,P1,P2,Color,2);

	 P1=Cen;
	 P1.y=P1.y+9;
	 P2=P1;
	 P2.y=P2.y+9;
	 cv::line(Src,P1,P2,Color,2);


}



void DrawTar(cv::Mat Src,cv::Rect rect,cv::Scalar Color)
{

		  cv::rectangle (Src,rect,Color,2,0,0);
}
void DrawPanTilt(cv::Mat Src,int P,int T)
{
	int ImageWidth=720;
	int width=512;
	int height=512;
    int p=(P)*width/256;
	int t=(T)*height/256;

	int w=width*256/256;
	int h=height*256/256;

	cv::Point P1(420-256,30);
	P1.x=ImageWidth/2-width/2;
	cv::Point P2(700,30);
	cv::Point p1;
	cv::Point p2;
	p1.x=P1.x+w;
	p1.y=P1.y;
	cv::Scalar color(255,240,240);
	cv::line(Src,P1,p1,color,2,0,0);
	/////////cv::line(Src,P+
	p2.x=P1.x+w/2+p;
	p2.y=p1.y-3;
	cv::Point p3;
	p3.x=p2.x;p3.y=p2.y-10;
	//cv::line(Src,p2,p3,color, 5,0,0);
	arrowedLine(Src,p3,p2,cv::Scalar(0,0,255),2,0,00,0.6);// 
	p2.x=P1.x+w/2-w/4;p2.y=P1.y;
	p3.x=p2.x;p3.y=p2.y-4;
	cv::line(Src,p2,p3,color, 2,0,0);
	p2.x=P1.x+w/2+w/4;p2.y=P1.y;
	p3.x=p2.x;p3.y=p2.y-4;
	cv::line(Src,p2,p3,color, 2,0,0);
	p2.x=P1.x+w/2-w/4;p2.y=P1.y;
	p3.x=p2.x;p3.y=p2.y-4;
	cv::line(Src,p2,p3,color, 2,0,0);
	p2.x=P1.x+w/2+w/2;p2.y=P1.y;
	p3.x=p2.x;p3.y=p2.y-8;
	cv::line(Src,p2,p3,color, 2,0,0);
	p2.x=P1.x+w/2-w/2;p2.y=P1.y;
	p3.x=p2.x;p3.y=p2.y-8;
	cv::line(Src,p2,p3,color, 2,0,0);
	p2.x=P1.x+w/2-0;p2.y=P1.y;
	p3.x=p2.x;p3.y=p2.y-6;
	cv::line(Src,p2,p3,color, 2,0,0);
	//--------------------------------------------------
	P1.x=P2.x;P1.y=P2.y;
	p1.x=P1.x;
	p1.y=P1.y+h;
	
	cv::line(Src,P1,p1,color,2,0,0);
	/////////cv::line(Src,P+
	p2.x=P1.x-3;
	p2.y = P1.y + h / 2 + t;
	
	p3.x=p2.x-10;p3.y=p2.y;
	//cv::line(Src,p2,p3,color, 5,0,0);
	arrowedLine(Src,p3,p2,cv::Scalar(0,0,255),2,0,00,0.6);// 
	p2.x=P1.x;p2.y=P1.y+h/2-h/4;
	p3.x=p2.x-4;p3.y=P1.y+h/2-h/4;
	cv::line(Src,p2,p3,color, 2,0,0);
	p2.x=P1.x;p2.y=P1.y+h/2+h/4;
	p3.x=p2.x-4;p3.y=P1.y+h/2+h/4;
	cv::line(Src,p2,p3,color, 2,0,0);
	p2.x=P1.x;p2.y=P1.y+h/2-h/2;
	p3.x=p2.x-8;p3.y=P1.y+h/2-h/2;
	cv::line(Src,p2,p3,color, 2,0,0);
	p2.x=P1.x;p2.y=P1.y+h/2+h/2;
	p3.x=p2.x-8;p3.y=P1.y+h/2+h/2;
	cv::line(Src,p2,p3,color, 2,0,0);
	p2.x=P1.x;p2.y=P1.y+h/2+0;
	p3.x=p2.x-6;p3.y=P1.y+h/2+0;
	cv::line(Src,p2,p3,color, 2,0,0);

	

}

void DrawPanTilt_modified(cv::Mat Src, int P, int T)// P and T between -20..20 only
{
	int maxP = 80;
	int maxT = 80;
	int ImageWidth = 720;
	int width = 512;
	int height = 512;
	int p = (P)*width / maxP;
	int t = (T)*height / maxT;

	int w = width * maxP / maxP;
	int h = height * maxT / maxT;

	cv::Point P1(420 - 256, 30);
	P1.x = ImageWidth / 2 - width / 2;
	cv::Point P2(700, 30);
	cv::Point p1;
	cv::Point p2;
	p1.x = P1.x + w;
	p1.y = P1.y;
	cv::Scalar color(255, 240, 240);
	cv::line(Src, P1, p1, color, 2, 0, 0);
	/////////cv::line(Src,P+
	p2.x = P1.x + w / 2 + p;
	p2.y = p1.y - 3;
	cv::Point p3;
	p3.x = p2.x; p3.y = p2.y - 10;
	//cv::line(Src,p2,p3,color, 5,0,0);
	arrowedLine(Src, p3, p2, cv::Scalar(0, 0, 255), 2, 0, 00, 0.6);// 
	p2.x = P1.x + w / 2 - w / 4; p2.y = P1.y;
	p3.x = p2.x; p3.y = p2.y - 4;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x + w / 2 + w / 4; p2.y = P1.y;
	p3.x = p2.x; p3.y = p2.y - 4;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x + w / 2 - w / 4; p2.y = P1.y;
	p3.x = p2.x; p3.y = p2.y - 4;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x + w / 2 + w / 2; p2.y = P1.y;
	p3.x = p2.x; p3.y = p2.y - 8;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x + w / 2 - w / 2; p2.y = P1.y;
	p3.x = p2.x; p3.y = p2.y - 8;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x + w / 2 - 0; p2.y = P1.y;
	p3.x = p2.x; p3.y = p2.y - 6;
	cv::line(Src, p2, p3, color, 2, 0, 0);



	p2.x = P1.x + w / 2 - w / 8; p2.y = P1.y;
	p3.x = p2.x; p3.y = p2.y - 3;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x + w / 2 + w / 8; p2.y = P1.y;
	p3.x = p2.x; p3.y = p2.y - 3;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x + w / 2 - w / 8 -w / 4; p2.y = P1.y;
	p3.x = p2.x; p3.y = p2.y - 3;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x + w / 2 + w / 8+w / 4; p2.y = P1.y;
	p3.x = p2.x; p3.y = p2.y - 3;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	
	//--------------------------------------------------
	P1.x = P2.x; P1.y = P2.y;
	p1.x = P1.x;
	p1.y = P1.y + h;

	cv::line(Src, P1, p1, color, 2, 0, 0);
	/////////cv::line(Src,P+
	p2.x = P1.x - 3;
	p2.y = P1.y + h / 2 - t;;

	p3.x = p2.x - 10; p3.y = p2.y;
	//cv::line(Src,p2,p3,color, 5,0,0);
	arrowedLine(Src, p3, p2, cv::Scalar(0, 0, 255), 2, 0, 00, 0.6);// 
	p2.x = P1.x; p2.y = P1.y + h / 2 - h / 4;
	p3.x = p2.x - 4; p3.y = P1.y + h / 2 - h / 4;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x; p2.y = P1.y + h / 2 + h / 4;
	p3.x = p2.x - 4; p3.y = P1.y + h / 2 + h / 4;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x; p2.y = P1.y + h / 2 - h / 2;
	p3.x = p2.x - 8; p3.y = P1.y + h / 2 - h / 2;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x; p2.y = P1.y + h / 2 + h / 2;
	p3.x = p2.x - 8; p3.y = P1.y + h / 2 + h / 2;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x; p2.y = P1.y + h / 2 + 0;
	p3.x = p2.x - 6; p3.y = P1.y + h / 2 + 0;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	//------------------------------------------------------
	p2.x = P1.x; p2.y = P1.y + h / 2 - h / 4+h/8;
	p3.x = p2.x - 3; p3.y = P1.y + h / 2 - h / 4+h/8;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x; p2.y = P1.y + h / 2 + h / 4-h/8;
	p3.x = p2.x - 3; p3.y = P1.y + h / 2 + h / 4-h/8;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x; p2.y = P1.y + h / 2 - h / 4-h/8;
	p3.x = p2.x - 3; p3.y = P1.y + h / 2 - h / 4-h/8;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	p2.x = P1.x; p2.y = P1.y + h / 2 + h / 4+h/8;
	p3.x = p2.x - 3; p3.y = P1.y + h / 2 + h /4+h/8;
	cv::line(Src, p2, p3, color, 2, 0, 0);
	

	//------------------------------------------------------


}



void DrawTarget(cv::Mat Src,cv::Point2d Center,cv::Scalar Color)
{
	      
	cv::line(Src,cv::Point(Center.x-TarqL,Center.y-TarqL),cv::Point(Center.x-TarqL+CornerL,Center.y-TarqL),Color,2);
	cv::line(Src,cv::Point(Center.x-TarqL,Center.y-TarqL),cv::Point(Center.x-TarqL,Center.y-TarqL+CornerL),Color,2);

	cv::line(Src,cv::Point(Center.x-TarqL,Center.y+TarqL),cv::Point(Center.x-TarqL+CornerL,Center.y+TarqL),Color,2);
	cv::line(Src,cv::Point(Center.x-TarqL,Center.y+TarqL),cv::Point(Center.x-TarqL,Center.y+TarqL-CornerL),Color,2);

	cv::line(Src,cv::Point(Center.x+TarqL,Center.y-TarqL),cv::Point(Center.x+TarqL-CornerL,Center.y-TarqL),Color,2);
	cv::line(Src,cv::Point(Center.x+TarqL,Center.y-TarqL),cv::Point(Center.x+TarqL,Center.y-TarqL+CornerL),Color,2);

	cv::line(Src,cv::Point(Center.x+TarqL,Center.y+TarqL),cv::Point(Center.x+TarqL-CornerL,Center.y+TarqL),Color,2);
	cv::line(Src,cv::Point(Center.x+TarqL,Center.y+TarqL),cv::Point(Center.x+TarqL,Center.y+TarqL-CornerL),Color,2);
	
	/*	  cv::rectangle (Src,rect,Color,2,0,0);*/
}


void DrawTarget_(cv::Mat Src,cv::Rect Selection,cv::Scalar Color)
{
	      
	cv::line(Src,cv::Point(Selection.x,Selection.y),cv::Point(Selection.x+CornerL,Selection.y),Color,2);
	cv::line(Src,cv::Point(Selection.x,Selection.y),cv::Point(Selection.x,Selection.y+CornerL),Color,2);

	cv::line(Src,cv::Point(Selection.x,Selection.y+Selection.height -1),cv::Point(Selection.x+CornerL,Selection.y+Selection.height -1),Color,2);
	cv::line(Src,cv::Point(Selection.x,Selection.y+Selection.height -1),cv::Point(Selection.x,Selection.y+Selection.height -1-CornerL),Color,2);

	cv::line(Src,cv::Point(Selection.x+Selection.width -1,Selection.y),cv::Point(Selection.x+Selection.width -1-CornerL,Selection.y),Color,2);
	cv::line(Src,cv::Point(Selection.x+Selection.width -1,Selection.y),cv::Point(Selection.x+Selection.width -1,Selection.y+CornerL),Color,2);

	cv::line(Src,cv::Point(Selection.x+Selection.width -1,Selection.y+Selection.height -1),cv::Point(Selection.x+Selection.width -1-CornerL,Selection.y+Selection.height -1),Color,2);
	cv::line(Src,cv::Point(Selection.x+Selection.width -1,Selection.y+Selection.height -1),cv::Point(Selection.x+Selection.width -1,Selection.y+Selection.height -1-CornerL),Color,2);
	
	/*	  cv::rectangle (Src,rect,Color,2,0,0);*/
}

void DrawGoastTar(cv::Mat Src,cv::Rect rect,cv::Rect Selected)
{
	cv::Point center;
	center.x=rect.x+rect.width/2;
	center.y=rect.y+rect.height/2;

		  cv::rectangle (Src,rect,GoastColor,2,0,0);
		  cv::line (Src,cv::Point(rect.x,center.y),cv::Point(center.x-Selected.width/2,center.y),GoastColor,2,0,0);
		  cv::line (Src,cv::Point(rect.x+rect.width-1,center.y),cv::Point(center.x+Selected.width/2,center.y),GoastColor,2,0,0);
		  cv::line (Src,cv::Point(center.x,rect.y),cv::Point(center.x,center.y-Selected.height/2),GoastColor,2,0,0);
		  cv::line (Src,cv::Point(center.x,rect.y+rect.height-1),cv::Point(center.x,center.y+Selected.height/2),GoastColor,2,0,0);
		  //cv::rectangle(Src,Selected,GoastColor,2,0,0);
		  
}
void DrawGoastTar_(cv::Mat Src,cv::Rect rect,cv::Rect Selected)
{
	cv::Point center;
	center.x=rect.x+rect.width/2;
	center.y=rect.y+rect.height/2;

		  cv::rectangle (Src,rect,GoastColor,2,0,0);
		  //cv::line (Src,cv::Point(rect.x,center.y),cv::Point(center.x-Selected.width/2,center.y),GoastColor,2,0,0);
		  //cv::line (Src,cv::Point(rect.x+rect.width-1,center.y),cv::Point(center.x+Selected.width/2,center.y),GoastColor,2,0,0);
		  //cv::line (Src,cv::Point(center.x,rect.y),cv::Point(center.x,center.y-Selected.height/2),GoastColor,2,0,0);
		  //cv::line (Src,cv::Point(center.x,rect.y+rect.height-1),cv::Point(center.x,center.y+Selected.height/2),GoastColor,2,0,0);
		  cv::rectangle(Src,cv::Rect(center.x-Selected.width/2,center.y-Selected.height/2,Selected.width,Selected.height),GoastColor,2,0,0);
		  
}


cv::Mat Osd(cv::Mat& frame,short P,short T,byte Algo,float toc,bool drawE,bool drawT,float Danglex,float Dangley,bool DrawTar,cv::Point LTtar,bool TrackingState,bool DrawGoast,cv::Rect GT,cv::Rect Selection,cv::Rect BB,double Viewx,double dpT=DPT,bool PrintM=false)

{
		char buf[128];
	string  AlgoStr;
	cv::Point textOrg(15,frame.rows-30) ;
	cv::Mat L=cv::Mat(frame.rows,frame.cols,frame.type());
	frame.copyTo (L);
	//cv::line (L,cv::Point(0,0),cv::Point(frame.cols-1,frame.rows-1),cv::Scalar(255,0,0),2);
	if(DrawTar)
	{
		if(TrackingState)
			//DrawTarget(L,LTtar,TarOk);
			DrawTarget_(L,BB,TarOk);
		else
           //DrawTarget(L,LTtar,TarLost);
		    DrawTarget_(L,BB,TarLost);
	}
	if(DrawGoast)
	{
	//	DrawGoastTar(L,GT,Selection);
	DrawGoastTar_(L,GT,Selection);
	}



	 textOrg.x =30;
	 textOrg.y=130;
		
	 sprintf(buf, "FT=%.2f",toc); 
     putText(L, buf, textOrg, fontFace,fontScale,WhiteColor , thickness, 4);
	

	  AlgoStr=Algoritthm[Algo];
	  textOrg.x =30;
	  textOrg.y=70;
	  sprintf(buf,"%s",AlgoStr.c_str()); 
	  putText(L, buf, textOrg, fontFace, fontScale,WhiteColor , thickness, 4);

	  sprintf(buf, "P= %.2f", ((double)(P))*dpT);
	  textOrg.y =frame.rows-30 ;
      putText(L, cv::String(buf), textOrg, fontFace, fontScale,cv::Scalar(255,255,255) , thickness, 4);
        
	  textOrg.y =L.rows-10 ;
	  sprintf(buf, "T= %2.2f", ((double)(T))*dpT);
         
      putText(L, cv::String(buf), textOrg, fontFace, fontScale,cv::Scalar(255,255,255) , thickness, 4);
	  
	  textOrg.x =300;textOrg.y =L.rows-10;		
	  sprintf(buf, "DX=%.4f",Danglex); 
      putText(L, cv::String(buf), textOrg, fontFace, fontScale,cv::Scalar(255,255,255) , thickness, 4);
	  textOrg.x =500;
	  sprintf(buf, "DY=%.4f",Dangley); 
      putText(L, cv::String(buf), textOrg, fontFace, fontScale,cv::Scalar(255,255,255) , thickness, 4);
		


	  if((!drawT))
		{
			
			TColor=cv::Scalar(255,255,255);
			BTColor=cv::Scalar(55,55,55);
		}
		if(drawT)
		{
			
			TColor=cv::Scalar(255,255,255);
			BTColor=cv::Scalar(0,0,255);
		}
		if((!drawE))
		{
			
			EColor=cv::Scalar(255,255,255);
			BEColor=cv::Scalar(55,55,55);

		}
		if((drawE))
		{
			
			EColor=cv::Scalar(55,55,55);
			BEColor=cv::Scalar(0,255,255);
		}
		

		textOrg.y=40;
		textOrg.x=30;
	  if(drawE){
		    sprintf(buf,"%s",'E');
		    ///////str = "E";//ss3.str();
		    cv::rectangle(L,cv::Rect(34,7,25,34),BEColor,-1,8,0);
		    putText(L, buf, textOrg, fontFace, 1.5/*fontScale*/,EColor , thickness, 4);
		       }
		textOrg.x =60;
		
		if(drawT){
			sprintf(buf,"%s",'T');

		    cv::rectangle(L,cv::Rect(59,7,26,34),BTColor,-1,8,0);
		    //putText(frame, "€€ ",textOrg, fontFace, 1.5/*fontScale*/,BTColor ,4, 4);
		    putText(L, buf, textOrg, fontFace, 1.5/*fontScale*/,TColor ,4, 4);
		        }

		// putting the view x;
		textOrg.x =40;
		textOrg.y =240;

		sprintf(buf,"%.4f",Viewx);
        putText(L, buf, textOrg,  fontFace, fontScale,cv::Scalar(255,255,255) , thickness, 4);
		


		///////////*str = AlgoStr;
		//////////putText(frame, str, textOrg, fontFace, fontScale,WhiteColor , thickness, 4);*/
	//Drawing Cross
	DrawingCross(L,CursorColor);
	
        
	DrawPanTilt(L,P ,T );
	return L;
}

void Osd_(cv::Mat& L, DrawingHomingStruct *D, float dpT = DPT,bool PrintM=false)

{
		char buf[128];
	string  AlgoStr;
	cv::Point textOrg(15,L.rows-30) ;

	///////frame.copyTo (L);
	//cv::line (L,cv::Point(0,0),cv::Point(frame.cols-1,frame.rows-1),cv::Scalar(255,0,0),2);
	if(D->DrawTar)
	{
		if(D->TrackingState)
			//DrawTarget(L,LTtar,TarOk);
			DrawTarget_(L,D->BB,TarOk);
		else
           //DrawTarget(L,LTtar,TarLost);
		    DrawTarget_(L,D->BB,TarLost);
	}
	if(D->DrawGoast)
	{
	//	DrawGoastTar(L,GT,Selection);
	DrawGoastTar_(L,D->GT,D->Selection);
	}



	 textOrg.x =30;
	 textOrg.y=130;
		
	 sprintf(buf, "FT=%.2f",D->toc); 
     putText(L, buf, textOrg, fontFace,fontScale,WhiteColor , thickness, 4);
	

	  AlgoStr=Algoritthm[D->Algo];
	  textOrg.x =30;
	  textOrg.y=70;
	  // added rect
	////  cv::rectangle(L, cv::Rect(textOrg.x - 20, textOrg.y -45, 250, 64), Scalar(0, 0, 0), -1, 8, 0);
	  sprintf(buf,"%s",AlgoStr.c_str()); 
	  putText(L, buf, textOrg, fontFace, fontScale,WhiteColor , thickness, 4);

	  sprintf(buf, "P= %.2f", ((double)(D->P))*dpT);
	  textOrg.y =L.rows-30 ;
	 
	  
	  //added rect
	  /////cv::rectangle(L, cv::Rect(textOrg.x - 20, textOrg.y - 20, 250, 34), Scalar(30,30,30), -1, 8, 0);
      putText(L, cv::String(buf), textOrg, fontFace, fontScale,cv::Scalar(255,255,255) , thickness, 4);
        
	  textOrg.y =L.rows-10 ;
	  sprintf(buf, "T= %2.2f", ((double)(D->T))*dpT);
         
      putText(L, cv::String(buf), textOrg, fontFace, fontScale,cv::Scalar(255,255,255) , thickness, 4);
	  
	  textOrg.x =300;textOrg.y =L.rows-10;		
	  sprintf(buf, "DX=%.4f",D->Danglex); 
      putText(L, cv::String(buf), textOrg, fontFace, fontScale,cv::Scalar(255,255,255) , thickness, 4);
	  textOrg.x =500;
	  sprintf(buf, "DY=%.4f",D->Dangley); 
      putText(L, cv::String(buf), textOrg, fontFace, fontScale,cv::Scalar(255,255,255) , thickness, 4);
		


	  if((!D->drawT))
		{
			
			TColor=cv::Scalar(255,255,255);
			BTColor=cv::Scalar(55,55,55);
		}
		if(D->drawT)
		{
			
			TColor=cv::Scalar(255,255,255);
			BTColor=cv::Scalar(0,0,255);
		}
		if((!D->drawE))
		{
			
			EColor=cv::Scalar(255,255,255);
			BEColor=cv::Scalar(55,55,55);

		}
		if((D->drawE))
		{
			
			EColor=cv::Scalar(55,55,55);
			BEColor=cv::Scalar(0,255,255);
		}
		

		textOrg.y=40;
		textOrg.x=30;
	  if(D->drawE){
		  sprintf(buf,"%s","E");
		///////str = "E";//ss3.str();
		cv::rectangle(L,cv::Rect(34,7,25,34),BEColor,-1,8,0);
		putText(L, buf, textOrg, fontFace, 1.5/*fontScale*/,EColor , thickness, 4);
		}
		textOrg.x =60;
		
		if(D->drawT){
			//if (!PrintM)
			//{

				sprintf(buf, "%s", "T");

				cv::rectangle(L, cv::Rect(59, 7, 26, 34), BTColor, -1, 8, 0);
				putText(L, buf, textOrg, fontFace, 1.5/*fontScale*/, TColor, 4, 4);
			//}
		//putText(frame, "€€ ",textOrg, fontFace, 1.5/*fontScale*/,BTColor ,4, 4);

		}/*else

		/*if (PrintM)
		{

			sprintf(buf, "%s", "A");
			cv::rectangle(L, cv::Rect(63, 7, 29, 34), BTColor, -1, 8, 0);
			putText(L, buf, textOrg, fontFace, 1.5, TColor, 4, 4);
		}*/
		
		// putting the view x;
		textOrg.x =45;
		textOrg.y =240;

		sprintf(buf,"%.4f",D->Viewx);
        putText(L, buf, textOrg,  fontFace, fontScale,cv::Scalar(255,255,255) , thickness, 4);
		


		///////////*str = AlgoStr;
		//////////putText(frame, str, textOrg, fontFace, fontScale,WhiteColor , thickness, 4);*/
	//Drawing Cross
	DrawingCross(L,CursorColor);
	short P1, T1;
	
	if (D->P > 40)
		P1 = 40;
	else
	{
		if (D->P < -40)
			P1 = -40;
		else
			P1 = D->P;
	}
	if (D->T > 40)
		T1 = 40;
	else
	{
		if (D->T < -40)
			T1 = -40;
		else
			T1 = D->T;
	}

	DrawPanTilt_modified(L,P1,T1);
	///////////////////////////////////////////////DrawPanTilt(L,D->P ,D->T );
	//return L;
}
//---------------------------------------------------------------------------


void DrawCross_(cv::Mat Src,cv::Point cent,cv::Scalar Color)
{

    cv::line(Src,cv::Point(cent.x-cusorw,cent.y),cv::Point(cent.x+cusorw,cent.y),Color,3);
    cv::line(Src,cv::Point(cent.x,cent.y-cusorw),cv::Point(cent.x,cent.y+cusorw),Color,3);

}


void OsdSea_(cv::Mat& L,DrawingSeaProjectsStruct *D)

{//
	//std::cout<< " View"<<std::endl;;
	char buf[128];
	cv::Point textOrg(15,L.rows-30) ;
	string  AlgoStr;

	textOrg.x =30;
	textOrg.y=50;
	if(D->saving)
	{
		sprintf(buf, "Saving",D->toc);
		putText(L, buf, textOrg, fontFace,fontScale,cv::Scalar (0,255,0) , thickness, 4);
	}
	textOrg.x =30;
	 textOrg.y=20;
		
	 sprintf(buf, "DIS1=%d",D->dis1); 
     putText(L, buf, textOrg, fontFace,0.6,cv::Scalar (0,255,0) , thickness, 4);

	 textOrg.x =160;
	 textOrg.y=20;
		
	 sprintf(buf, "DIS2=%d",D->dis2); 
     putText(L, buf, textOrg, fontFace,0.6,cv::Scalar (0,255,0) , thickness, 4);

	 textOrg.x =300;
	 textOrg.y=20;
		
	 sprintf(buf, "LASER=%d",D->laser_status); 
     putText(L, buf, textOrg, fontFace,0.6,cv::Scalar (0,255,0) , thickness, 4);
	 textOrg.x =30;
	 textOrg.y=130;
		
	 sprintf(buf, "FT=%.2f",D->toc); 
     putText(L, buf, textOrg, fontFace,fontScale,cv::Scalar (0,255,0) , thickness, 4);
	 textOrg.x =30;
	 textOrg.y=70;
	 AlgoStr=Algoritthm[D->Algo];
	 sprintf(buf,"%s", AlgoStr.c_str());
	 putText(L, buf, textOrg, fontFace, fontScale,cv::Scalar (0,255,0) , thickness, 4);
		
      sprintf(buf, "P= %.2f",(double)(D->P)); 
	  textOrg.y =L.rows-30 ;
      putText(L, cv::String(buf), textOrg, fontFace, fontScale,cv::Scalar(0,255,0) , thickness, 4);
	  //std::cout<< " after draw P"<<endl;;
       
	  textOrg.y =L.rows-10 ;
      sprintf(buf, "T= %.2f",(double)(D->T)); 
         
      putText(L, cv::String(buf), textOrg, fontFace, fontScale,cv::Scalar(0,255,0) , thickness, 4);
	  
	  textOrg.x =350;textOrg.y =L.rows-10;		
	  sprintf(buf, "DX=%.2f",D->Danglex); 
      putText(L, cv::String(buf), textOrg, fontFace, fontScale,cv::Scalar(0,255,0) , thickness, 4);
	  textOrg.x =500;
	  sprintf(buf, "DY=%.2f",D->Dangley); 
      putText(L, cv::String(buf), textOrg, fontFace, fontScale,cv::Scalar(0,255,0) , thickness, 4);
		
	  sprintf(buf,"(%d,%d)",D->BB.width,D->BB.height);
		textOrg.x =10;
		textOrg.y =350;
        cv::putText(L, buf, textOrg, fontFace, fontScale,cv::Scalar(0,255,0) , thickness, 4);
      if(  D->DrawTar )
		 DrawTarSea(L,D->LTtar ,D->BB,D->TarColor);
       DrawCross_(L,D->Cross,CrossColor);

	  /*if((!D->drawT))
		{
			
			TColor=cv::Scalar(255,255,255);
			BTColor=cv::Scalar(55,55,55);
		}
		if(D->drawT)
		{
			
			TColor=cv::Scalar(255,255,255);
			BTColor=cv::Scalar(0,0,255);
		}
		if((!D->drawE))
		{
			
			EColor=cv::Scalar(255,255,255);
			BEColor=cv::Scalar(55,55,55);

		}
		if((D->drawE))
		{
			
			EColor=cv::Scalar(55,55,55);
			BEColor=cv::Scalar(0,255,255);
		}
		

		textOrg.y=40;
		textOrg.x=30;
	  if(D->drawE){
		  sprintf(buf,"%s","E");
		///////str = "E";//ss3.str();
		cv::rectangle(L,cv::Rect(34,7,25,34),BEColor,-1,8,0);
		putText(L, buf, textOrg, fontFace, 1.5,EColor , thickness, 4);
		}
		textOrg.x =60;
		
		if(D->drawT){
			sprintf(buf,"%s","T");

		cv::rectangle(L,cv::Rect(59,7,26,34),BTColor,-1,8,0);
		//putText(frame, "€€ ",textOrg, fontFace, 1.5,BTColor ,4, 4);
		putText(L, buf, textOrg, fontFace, 1.5,TColor ,4, 4);
		}

		// putting the view x;
		textOrg.x =40;
		textOrg.y =240;

		sprintf(buf,"%.4f",D->Viewx);
		putText(L, buf, textOrg,  fontFace, fontScale,Scalar(255,255,255) , thickness, 4);
		


			//Drawing Cross
	DrawingCross(L,CursorColor);
	
        
	DrawPanTilt(L,D->P ,D->T );*/
	//return L;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
  OSDT::OSDT()
  {
	 
  }

  //---------------------------------------------------------------------------
  OSDT::~OSDT()
  {
  }
  //---------------------------------------------------------------------------
 
  bool OSDT::View(float dpt,bool printM)
  {
/*	  DrawingList.Next =DrawingList.Begin ;
    for(int i=1;i<=DrawingList.size;i++)
	  {
		 std::cout<<" Drawing one "<<i<<std::endl; 
		 DrawingComp * D=DrawingList.GetIndex(i);
		 	 
		 if(D-> Draw)
		   D->View (image_);
	  }*/
	return true;
  }
//-----------------------------------------------------------------------------
 


  // A speficic instance of OSD Class: Homing Apps
  
     HomingOSD::HomingOSD(){}
	HomingOSD::~HomingOSD(){}

	bool HomingOSD::initialize(void* DrawStuct,cv::Mat& L){ 
		Drawings=DrawStuct;
		SetImage(L);
	/*	int val=0;
		bool S=true;
		DrawingStruct* D=(DrawingStruct*)DrawStuct ;
		HomingOSD::AddDrawingComp (1,"%s",0,"T",&cv::Scalar(255,255,100),&(D->drawT) ,cv::Point(100,100));
		HomingOSD::AddDrawingComp (1,"%3d",1,(void*)(&(D->toc) ),&cv::Scalar(255,200,200),&S,cv::Point(100,200));
		HomingOSD::AddDrawingComp (2,"",2,(void*)(&D->P ),&WhiteColor,&S,cv::Point(300,20));
*/

	return true;
	}
	bool HomingOSD::View(float dpt,bool printM)
	{
		DrawingHomingStruct* D=(DrawingHomingStruct*)Drawings ;
		Osd_(image_, D, dpt, printM);
		   cv::Mat Dummy(image_,cv::Rect(image_.cols-D->Temp.cols-30,image_.rows-50-D->Temp.rows,D->Temp.cols,D->Temp.rows));
	    if(D->DrawTemp){
	       D->Temp.copyTo (Dummy);
	       cv::rectangle(image_,cv::Rect(image_.cols-D->Temp.cols-30,image_.rows-50-D->Temp.rows,D->Temp.cols,D->Temp.rows),WhiteColor,2);
		   //cv::addWeighted()
	    }
		return true;
	}
	/*void HomingOSD::DrawComp(DrawingComp D)
	{
		D.View (image_);

	}*/
	/*bool HomingOSD::View()
	{
		
		return true;

	}*/

	bool HomingOSD::SetImage(cv::Mat &image)
	{
		image_=image;
		return true;
	}


	// A speficic instance of OSD Class: Homing Apps
  
     SeaProjectsOSD::SeaProjectsOSD(){}
	SeaProjectsOSD::~SeaProjectsOSD(){}

	bool SeaProjectsOSD::initialize(void* DrawStuct,cv::Mat& L){ 
		Drawings=DrawStuct;
		SetImage(L);
	/*	int val=0;
		bool S=true;
		DrawingStruct* D=(DrawingStruct*)DrawStuct ;
		HomingOSD::AddDrawingComp (1,"%s",0,"T",&cv::Scalar(255,255,100),&(D->drawT) ,cv::Point(100,100));
		HomingOSD::AddDrawingComp (1,"%3d",1,(void*)(&(D->toc) ),&cv::Scalar(255,200,200),&S,cv::Point(100,200));
		HomingOSD::AddDrawingComp (2,"",2,(void*)(&D->P ),&WhiteColor,&S,cv::Point(300,20));
*/

	return true;
	}
	bool SeaProjectsOSD::View(float dpt, bool PrintM)
	{
		DrawingSeaProjectsStruct* D=(DrawingSeaProjectsStruct*)Drawings ;
			//std::cout<< " View"<<std::endl;;
		OsdSea_(image_,D);
	   cv::Mat Dummy(image_,cv::Rect(image_.cols-D->Temp.cols-30,image_.rows-50-D->Temp.rows,D->Temp.cols,D->Temp.rows));

	if(D->DrawTemp){
	    D->Temp.copyTo (Dummy);
	  cv::rectangle(image_,cv::Rect(image_.cols-D->Temp.cols-30,image_.rows-50-D->Temp.rows,D->Temp.cols,D->Temp.rows),WhiteColor,2);
	}
		return true;
	}
	/*void HomingOSD::DrawComp(DrawingComp D)
	{
		D.View (image_);

	}*/
	/*bool HomingOSD::View()
	{
		
		return true;

	}*/

	bool SeaProjectsOSD::SetImage(cv::Mat &image)
	{
		image_=image;
		return true;
	}
     /*Mat   HomingOSD::GetOut()
	 {
		  return image_
	 }*/
    // A method to import an image to the type desired for the current algorithm
	//void HomingOSD::import_image(const cv::Mat & image){}

  
