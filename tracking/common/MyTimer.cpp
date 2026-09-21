#include "MyTimer.h"
MyTimer::~MyTimer(void)
{
}
/*
MyTimer::MyTimer(void)
{
	QueryPerformanceFrequency(&pFreq);
}


MyTimer::~MyTimer(void)
{
}
double 	MyTimer::toc()
{
	//QueryPerformanceFrequency
  boost::detail::winapi::LARGE_INTEGER_ nEnd;

  boost::detail::winapi::QueryPerformanceCounter(&pEnd);
  CalcTime=(pEnd.QuadPart -pBegin.QuadPart )*1000/pFreq.QuadPart ;
  pBegin=pEnd;
  return CalcTime;
}
//---------------------------------------------------------------------------
void	MyTimer::tic()
{
  QueryPerformanceCounter(&pBegin);
}*/
double 	MyTimer::toc()
{
	//QueryPerformanceFrequency
	#if defined(__unix__)
	{
		int64 nEnd;
		pEnd=(double)cv::getTickCount();
		CalcTime=(pEnd -pBegin )*1000.0/pFreq ;
        pBegin=pEnd;
	}
#else
	{
  boost::detail::winapi::LARGE_INTEGER_ nEnd;

  boost::detail::winapi::QueryPerformanceCounter(&pEnd);
  CalcTime=(pEnd.QuadPart -pBegin.QuadPart )*1000/pFreq.QuadPart ;
  pBegin=pEnd;
	}
	#endif
  return CalcTime;
}
//---------------------------------------------------------------------------
void	MyTimer::tic()
{
#if defined(__unix__)
	{
	  pBegin=(double)cv::getTickCount();
	}
#else
	{
 
       QueryPerformanceCounter(&pBegin);

	}
#endif

  
}
//---------------------------------------------------------------------------
	MyTimer::MyTimer(void)
{
#if defined(__unix__)
	{
	  pFreq=cv::getTickFrequency();
	}
#else
	{
  QueryPerformanceFrequency(&pFreq);
	}
#endif
}
