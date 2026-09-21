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
 * CFNNClassifier.h
 *
 *  Created on: Nov 16, 2011
 *      Author: Georg Nebehay
 */

#ifndef CFNNCLASSIFIER_H_
#define CFNNCLASSIFIER_H_

#include <vector>

#include <opencv/cv.h>

#include "CFNormalizedPatch.h"
#include "CFDetectionResult.h"

namespace CFtld
{
    class CFNNClassifier
    {
        float ncc(float *f1, float *f2);
        void showWindow(const cv::Mat &img, int windowIdx);
    public:
        bool enabled;

        int *windows;
        float thetaFP;
        float thetaTP;
        CFDetectionResult *detectionResult;
        std::vector<CFNormalizedPatch>* falsePositives;
        std::vector<CFNormalizedPatch>* truePositives;

        CFNNClassifier();
        virtual ~CFNNClassifier();

        void release();
        float classifyPatch(CFNormalizedPatch *patch);
        float classifyBB(const cv::Mat &img, cv::Rect *bb);
        float classifyWindow(const cv::Mat &img, int windowIdx);
        void learn(std::vector<CFNormalizedPatch> patches);
        bool filter(const cv::Mat &img, int windowIdx);
    };
} /* namespace CFtld */
#endif /* NNCLASSIFIER_H_ */
