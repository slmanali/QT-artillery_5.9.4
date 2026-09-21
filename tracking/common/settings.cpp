#pragma warning (disable : 4786)
#include <iostream>
using namespace std;

#include "settings.h"

std::string filename="settings.ini";
void loadConfig(ConfigStruct &St)
{
	//CIniFile ifile;
	ifile.LoadFile(filename);
	St.ImageWidth=720;
			St.ImageHeight=576;
			St.CamNum =0;
			
        if(ifile.SetCategory("ImageProject"))
		{
			try{
			St.ImageWidth =stoi(ifile.GetEntryValueByName ("ImageWidth"));
			St.ImageHeight =stoi(ifile.GetEntryValueByName ("ImageHeight"));
			St.DCursorx =stoi(ifile.GetEntryValueByName ("DCursorx"));
			St.DCursory=stoi(ifile.GetEntryValueByName ("DCursory"));
			St.CamNum =stoi(ifile.GetEntryValueByName ("CamNum"));
			}
			catch(...){};
			
		}
	


}
void load_Sea_Config(ConfigSeaStruct& St)
{
	//CIniFile ifile;
	ifile.LoadFile(filename);
	St.ImageWidth=720;
	St.ImageHeight=576;
	St.CamNum =0;
	St.DCursorx =128;
	St.DCursory =128;
	St.initWinWidth =64;
	St.MaxWinWidth =128;

			
    if(ifile.SetCategory("SeaProject"))
		{
			try{
			St.ImageWidth =stoi(ifile.GetEntryValueByName ("ImageWidth"));
			St.ImageHeight =stoi(ifile.GetEntryValueByName ("ImageHeight"));
			St.DCursorx =stoi(ifile.GetEntryValueByName ("DCursorx"));
			St.DCursory=stoi(ifile.GetEntryValueByName ("DCursory"));
			St.CamNum =stoi(ifile.GetEntryValueByName ("CamNum"));
			St.initWinWidth =stoi(ifile.GetEntryValueByName ("InitWinWidth"));
			St.MaxWinWidth =stoi(ifile.GetEntryValueByName ("MaxWinWidth"));
			St.ratiomax = stof(ifile.GetEntryValueByName("RatioMax"));
			St.ratiomin = stof(ifile.GetEntryValueByName("RatioMin"));
			St.enableZoomControl = stoi(ifile.GetEntryValueByName("ZoomControl"));
			}
			catch(...){};
			
		}
	


}
void load_Homing_Config(ConfighomingStruct& St)
{
//	CIniFile ifile;
	ifile.LoadFile(filename);
	St.ImageWidth=720;
	St.ImageHeight=576;
	St.CamNum =0;
	St.enableZoomControl =0;		
        if(ifile.SetCategory("HomingProject"))
		{
			try{
			St.ImageWidth =stoi(ifile.GetEntryValueByName ("ImageWidth"));
			St.ImageHeight =stoi(ifile.GetEntryValueByName ("ImageHeight"));
			St.CamNum =stoi(ifile.GetEntryValueByName ("CamNum"));
			St.ratiomax  =stof(ifile.GetEntryValueByName ("RatioMax"));
			St.ratiomin  =stof(ifile.GetEntryValueByName ("RatioMin"));
			St.enableZoomControl =stoi(ifile.GetEntryValueByName ("ZoomControl"));
			}
			catch(...){};
			
		}
		else
		{
			save_Homing_Config(St);
		}
	


}
void load_Port_Config(ConfigPortStruct& St)
{
//	CIniFile ifile;
	ifile.LoadFile(filename);
	St.Port ="COM10";
	St.BaudRate =9600;
			
	if(ifile.SetCategory("SysPort"))
			//ifile.SetCategory("SysPort");
		{
			try{
			St.Port =ifile.GetEntryValueByName ("Port");
			St.BaudRate =stoi(ifile.GetEntryValueByName ("BaudRate"));
			//St.CamNum =stoi(ifile.GetEntryValueByName ("CamNum"));
			}
			catch(...){};
			
		}

	    if(ifile.SetCategory("TIMER"))
		{
			St.dt =40;
			try{
			St.dt =stoi(ifile.GetEntryValueByName ("Interval"));
			
			}
			catch(...){};
			
		}
		else
		{
			save_Port_Config(St);
		}


}

void load_Port2_Config(ConfigPortStruct& SysSt, ConfigPortStruct& St)
{
	//	CIniFile ifile;
	ifile.LoadFile(filename);
	SysSt.Port = "COM10";
	SysSt.BaudRate = 9600;
	St.Port = "COM1";
	St.BaudRate = 19200;
	St.stabilizeron = 0;
	if (ifile.SetCategory("SysPort"))
		//ifile.SetCategory("SysPort");
	{
		try{
			SysSt.Port = ifile.GetEntryValueByName("Port");
			SysSt.BaudRate = stoi(ifile.GetEntryValueByName("BaudRate"));
			//St.CamNum =stoi(ifile.GetEntryValueByName ("CamNum"));
		}
		catch (...){};

	}
	else
	{
		save_Port_Config(SysSt);
	}
	if (ifile.SetCategory("TIMER"))
	{
		SysSt.dt = 40;
		try{
			SysSt.dt = stoi(ifile.GetEntryValueByName("Interval"));

		}
		catch (...){};

	}
	if (ifile.SetCategory("CAMPort"))
	{
		try{
			St.Port = ifile.GetEntryValueByName("Port");
			St.BaudRate = stoi(ifile.GetEntryValueByName("BaudRate"));
			St.stabilizeron = stoi(ifile.GetEntryValueByName("StabilizerOn"));
			//St.CamNum =stoi(ifile.GetEntryValueByName ("CamNum"));
		}
		catch (...){};

	}
	else
	{

		save_Port1_Config(St);
	}


}


void saveConfig(ConfigStruct St)
{
	//CIniFile ifile;
	  ifile.AddCategoryUnique  ("ImageProject");
              #if defined(__unix__) 
		ifile.AddEntryUnique ("ImageWidth",to_string((int64_t)St.ImageWidth ));
		ifile.AddEntryUnique ("ImageHeight",to_string((int64_t)St.ImageHeight ));
		ifile.AddEntryUnique ("DCursorx",to_string((int64_t)St.DCursorx ));
		ifile.AddEntryUnique ("DCursory",to_string((int64_t)St.DCursory )); 
		ifile.AddEntryUnique ("CamNum",to_string((int64_t)St.CamNum  )); 

              #else
                {
		ifile.AddEntryUnique ("ImageWidth",to_string((_Longlong)St.ImageWidth ));
		ifile.AddEntryUnique ("ImageHeight",to_string((_Longlong)St.ImageHeight ));
		ifile.AddEntryUnique ("DCursorx",to_string((_Longlong)St.DCursorx ));
		ifile.AddEntryUnique ("DCursory",to_string((_Longlong)St.DCursory )); 
		ifile.AddEntryUnique ("CamNum",to_string((_Longlong)St.CamNum  )); 

                }
             #endif
		
	ifile.SaveToFile (filename);
	
}
void save_Sea_Config(ConfigSeaStruct St)
{
//	CIniFile ifile;
	  ifile.AddCategoryUnique  ("SeaProject");
  #if defined(__unix__)
		ifile.AddEntryUnique ("ImageWidth",to_string((int64_t)St.ImageWidth ));
		ifile.AddEntryUnique ("ImageHeight",to_string((int64_t)St.ImageHeight ));
		ifile.AddEntryUnique ("DCursorx",to_string((int64_t)St.DCursorx ));
		ifile.AddEntryUnique ("DCursory",to_string((int64_t)St.DCursory )); 
		ifile.AddEntryUnique ("CamNum",to_string((int64_t)St.CamNum  )); 
		ifile.AddEntryUnique ("MaxWinWidth",to_string((int64_t)St.MaxWinWidth )); 
		ifile.AddEntryUnique ("InitWinWidth",to_string((int64_t)St.initWinWidth));  
  #else
		ifile.AddEntryUnique ("ImageWidth",to_string((_Longlong)St.ImageWidth ));
		ifile.AddEntryUnique ("ImageHeight",to_string((_Longlong)St.ImageHeight ));
		ifile.AddEntryUnique ("DCursorx",to_string((_Longlong)St.DCursorx ));
		ifile.AddEntryUnique ("DCursory",to_string((_Longlong)St.DCursory )); 
		ifile.AddEntryUnique ("CamNum",to_string((_Longlong)St.CamNum  )); 
		ifile.AddEntryUnique ("MaxWinWidth",to_string((_Longlong)St.MaxWinWidth )); 
		ifile.AddEntryUnique ("InitWinWidth",to_string((_Longlong)St.initWinWidth)); 
		ifile.AddEntryUnique("RatioMax", to_string((long double)St.ratiomax));
		ifile.AddEntryUnique("RatioMin", to_string((long double)St.ratiomin));
		std::cout << St.enableZoomControl << std::endl;
		ifile.AddEntryUnique("ZoomControl", to_string((_ULonglong)St.enableZoomControl));

  #endif

		
	ifile.SaveToFile (filename);
	
}
void save_Homing_Config(ConfighomingStruct St)
{
//	CIniFile ifile;
	  ifile.AddCategoryUnique  ("HomingProject");
 #if defined(__unix__)
 		ifile.AddEntryUnique ("ImageWidth",to_string((int64_t)St.ImageWidth ));
		ifile.AddEntryUnique ("ImageHeight",to_string((int64_t)St.ImageHeight ));
		ifile.AddEntryUnique ("CamNum",to_string((int64_t)St.CamNum  )); 

#else
		ifile.AddEntryUnique ("ImageWidth",to_string((_Longlong)St.ImageWidth ));
		ifile.AddEntryUnique ("ImageHeight",to_string((_Longlong)St.ImageHeight ));
		ifile.AddEntryUnique ("CamNum",to_string((_Longlong)St.CamNum  )); 
		ifile.AddEntryUnique ("RatioMax",to_string((long double)St.ratiomax  )); 
		ifile.AddEntryUnique ("RatioMin",to_string((long double)St.ratiomin  )); 
	//	std::cout<<"Fuck"<<St.enableZoomControl<<std::endl;
		ifile.AddEntryUnique ("ZoomControl",to_string((_ULonglong)St.enableZoomControl  )); 
		
		
#endif

		
	ifile.SaveToFile (filename);
	
}
void save_Port_Config(ConfigPortStruct St)
{
	
	  ifile.AddCategoryUnique  ("SysPort");
		ifile.AddEntryUnique ("Port",St.Port );
#if defined(__unix__)
ifile.AddEntryUnique ("BaudRate",to_string((int64_t)St.BaudRate ));
#else
ifile.AddEntryUnique ("BaudRate",to_string((_Longlong)St.BaudRate ));
#endif
		//ifile.AddEntryUnique ("BaudRate",to_string((_Longlong)St.BaudRate ));
	  ifile.AddCategoryUnique  ("TIMER");
#if defined(__unix__)
	    ifile.AddEntryUnique ("Interval",to_string((int64_t)St.dt ));
#else
	    ifile.AddEntryUnique ("Interval",to_string((_Longlong)St.dt ));

#endif		
	ifile.SaveToFile (filename);
	
}



void save_Port1_Config(ConfigPortStruct St)
{

	ifile.AddCategoryUnique("CAMPort");
	ifile.AddEntryUnique("Port", St.Port);
#if defined(__unix__)
	ifile.AddEntryUnique("BaudRate", to_string((int64_t)St.BaudRate));
	ifile.AddEntryUnique ("StabilizerOn",to_string((int64_t)St.stabilizeron ));
#else
	ifile.AddEntryUnique("BaudRate", to_string((_Longlong)St.BaudRate));
	ifile.AddEntryUnique ("StabilizerOn",to_string((_Longlong)St.stabilizeron ));
#endif
	
	
	ifile.SaveToFile(filename);

}
