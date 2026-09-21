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
 * CFDetectorCascade.h
 *
 *  Created on: Nov 16, 2011
 *      Author: Georg Nebehay
 */

#ifndef CFDETECTORCASCADE_H_
#define CFDETECTORCASCADE_H_

#include "CFDetectionResult.h"
#include "CFVarianceFilter.h"
#include "CFEnsembleClassifier.h"
#include "CFClustering.h"
#include "CFNNClassifier.h"

namespace CFtld
{
    //Constants
    static const int TLD_WINDOW_SIZE = 5;
    static const int TLD_WINDOW_OFFSET_SIZE = 6;

    class CFDetectorCascade
    {
        //Working data
        int numScales;
        cv::Size *scales;
    public:
        //Configurable members
        int minScale;
        int maxScale;
        bool useShift;
        float shift;
        int minSize;
        int numFeatures;
        int numTrees;

        //Needed for init
        int imgWidth;
        int imgHeight;
        int imgWidthStep;
        int objWidth;
        int objHeight;

        int numWindows;
        int *windows;
        int *windowOffsets;

        //State data
        bool initialised;

        //Components of Detector Cascade
        CFVarianceFilter *varianceFilter;
        CFEnsembleClassifier *ensembleClassifier;
        CFClustering *clustering;
        CFNNClassifier *nnClassifier;

        CFDetectionResult *detectionResult;

        void propagateMembers();

        CFDetectorCascade();
        ~CFDetectorCascade();

        void init(std::shared_ptr<std::mt19937> rng);

        void initWindowOffsets();
        void initWindowsAndScales();

        void release();
        void cleanPreviousData();
        void detect(const cv::Mat &img);
    };
} /* namespace CFtld */
#endif /* DETECTORCASCADE_H_ */
