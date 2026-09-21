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
 * TLD.h
 *
 *  Created on: Nov 17, 2011
 *      Author: Georg Nebehay
 */

#ifndef __OPENCV_CFTLD_H__
#define __OPENCV_CFTLD_H_

#include <opencv/cv.h>
#include <memory>
#include <random>
#include "opencv2/core/core.hpp"

#include "../CF_tld/CFtld/CFTLD.h"


namespace cv
{
	namespace cftldtracker
	{
		class CFTLDTracker
		{
		public:
			CFtld::CFTLD *tld_CF;
			// CFtld::CFTLD *tld;
			 CFTLDTracker();
			 virtual ~CFTLDTracker();
		  	  bool	track(cv::Mat&  image, Rect& box);
			 bool	init(cv::Mat&  image, Rect& box,bool DSST);
		};
	} /* namespace tld */
}
#endif /* CFTLD_H_ */
