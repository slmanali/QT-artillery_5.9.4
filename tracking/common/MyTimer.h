#pragma once

#if defined(__unix__)
  #include "opencv2/highgui/highgui.hpp"
  #include "opencv2/core/core.hpp"
#else
  #include <boost/detail/winapi/timers.hpp>
#endif
class MyTimer
{
public:
	MyTimer(void);
	~MyTimer(void);

	private:
#if defined(__unix__)
 double pFreq,pBegin,pEnd;
#else
 boost::detail::winapi::LARGE_INTEGER_ pFreq,pBegin,pEnd;  
#endif
  

  double CalcTime;
  public:

 double   toc();
 void 	   tic();
 void swap();
};

