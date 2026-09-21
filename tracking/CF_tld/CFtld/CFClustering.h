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
 * CFClustering.h
 *
 *  Created on: Nov 16, 2011
 *      Author: Georg Nebehay
 */

#ifndef CFCLUSTERING_H_
#define CFCLUSTERING_H_

#include <vector>

#include <opencv/cv.h>

#include "CFDetectionResult.h"

namespace CFtld
{
    class CFClustering
    {
        void calcMeanRect(std::vector<int> * indices);
        void calcDistances(float *distances);
        void cluster(float *distances);
    public:
        int *windows;
        int numWindows;

        CFDetectionResult *detectionResult;

        //Configurable members
        float cutoff;

        CFClustering();
        virtual ~CFClustering();
        void release();
        void clusterConfidentIndices();
    };
} /* namespace CFtld */
#endif /* CLUSTERING_H_ */
