/*  Copyright 2011 AIT Austrian Institute of Technology
*
*   This file is part of OpenTLD.
*
*   OpenTLD is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   OpenTLD is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with OpenTLD.  If not, see <http://www.gnu.org/licenses/>.
*
*/
/*
 * TLD.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: Georg Nebehay

 * + Author: Klaus Haag
 *  * Replace Median Flow tracker with KCFcpp or DSSTcpp
 *  * Change to self-learning approach instead of semi-supervised
 */

#include "cv_cftld.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <random>


using namespace std;
//using namespace cv;


namespace cv
{
	namespace cftldtracker
	{
		CFTLDTracker::~CFTLDTracker()
		{
			tld_CF->release();
			delete tld_CF;
		}
	CFTLDTracker::CFTLDTracker()
		{
		tld_CF = new CFtld::CFTLD();
			
		}
		bool	CFTLDTracker::init(cv::Mat&  image, Rect& box,bool DSST)
		{
			tld_CF = new CFtld::CFTLD();
			tld_CF->init(DSST);
			tld_CF->selectObject(image, &box);
			return tld_CF->valid;
		}

	bool CFTLDTracker::track(cv::Mat&  image, Rect& box)
		{
			bool lost;
			tld_CF->processImage(image);
			if ((tld_CF->isTrackerValid))
			{
				box = tld_CF->trackerBB;
				lost = false;
				// Draw Points

			}
			else
			{
				box = *tld_CF->currBB;
				lost = true;
			}
			return lost;
		}
		
	} /* namespace tld */
}
