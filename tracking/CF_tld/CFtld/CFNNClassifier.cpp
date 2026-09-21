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
 * CFNNClassifier.cpp
 *
 *  Created on: Nov 16, 2011
 *      Author: Georg Nebehay
 */

#include "CFNNClassifier.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "CFDetectorCascade.h"
#include "CFTLDUtil.h"

using namespace std;
using namespace cv;

namespace CFtld
{
    CFNNClassifier::CFNNClassifier()
    {
        thetaFP = .5f;
        thetaTP = .55f;

        truePositives = new vector<CFNormalizedPatch>();
        falsePositives = new vector<CFNormalizedPatch>();
    }

    CFNNClassifier::~CFNNClassifier()
    {
        release();

        delete truePositives;
        delete falsePositives;
    }

    void CFNNClassifier::release()
    {
        falsePositives->clear();
        truePositives->clear();
    }

    float CFNNClassifier::ncc(float *f1, float *f2)
    {
        double corr = 0;
        double norm1 = 0;
        double norm2 = 0;

        int size = TLD_PATCH_SIZE * TLD_PATCH_SIZE;

        for (int i = 0; i < size; i++)
        {
            corr += f1[i] * f2[i];
            norm1 += f1[i] * f1[i];
            norm2 += f2[i] * f2[i];
        }

        // normalization to <0,1>

        return static_cast<float>((corr / sqrt(norm1 * norm2) + 1) / 2.0);
    }

    float CFNNClassifier::classifyPatch(CFNormalizedPatch *patch)
    {
        if (truePositives->empty())
        {
            return 0;
        }

        if (falsePositives->empty())
        {
            return 1;
        }

        float ccorr_max_p = 0;

        //Compare patch to positive patches
        for (size_t i = 0; i < truePositives->size(); i++)
        {
            float ccorr = ncc(truePositives->at(i).values, patch->values);

            if (ccorr > ccorr_max_p)
            {
                ccorr_max_p = ccorr;
            }
        }

        float ccorr_max_n = 0;

        //Compare patch to negative patches
        for (size_t i = 0; i < falsePositives->size(); i++)
        {
            float ccorr = ncc(falsePositives->at(i).values, patch->values);

            if (ccorr > ccorr_max_n)
            {
                ccorr_max_n = ccorr;
            }
        }

        float dN = 1 - ccorr_max_n;
        float dP = 1 - ccorr_max_p;

        float distance = dN / (dN + dP);
        return distance;
    }

    float CFNNClassifier::classifyBB(const Mat &img, Rect *bb)
    {
        CFNormalizedPatch patch;

        tldExtractNormalizedPatchRect(img, bb, patch.values);
        return classifyPatch(&patch);
    }

    float CFNNClassifier::classifyWindow(const Mat &img, int windowIdx)
    {
        CFNormalizedPatch patch;

        int *bbox = &windows[TLD_WINDOW_SIZE * windowIdx];
        tldExtractNormalizedPatchBB(img, bbox, patch.values);

        return classifyPatch(&patch);
    }

    void CFNNClassifier::showWindow(const Mat &img, int windowIdx)
    {
        CFNormalizedPatch patch;

        int *bbox = &windows[TLD_WINDOW_SIZE * windowIdx];
        tldExtractNormalizedPatchBB(img, bbox, patch.values);
        Mat temp(TLD_PATCH_SIZE, TLD_PATCH_SIZE, CV_32F, patch.values);
        normalize(temp, temp, 0, 1, cv::NORM_MINMAX);
        resize(temp, temp, Size(0, 0), 5.0, 5.0);
        imshow("NN positive detection", temp);
    }

    bool CFNNClassifier::filter(const Mat &img, int windowIdx)
    {
        if (!enabled) return true;

        float conf = classifyWindow(img, windowIdx);

        if (conf < thetaTP)
        {
            return false;
        }
        //std::cout << "NN conf: " << conf << std::endl;
        //showWindow(img, windowIdx);
        return true;
    }

    void CFNNClassifier::learn(vector<CFNormalizedPatch> patches)
    {
        //TODO: Randomization might be a good idea here
        for (size_t i = 0; i < patches.size(); i++)
        {
            CFNormalizedPatch patch = patches[i];

            float conf = classifyPatch(&patch);

            if (patch.positive && conf <= thetaTP)
            {
                truePositives->push_back(patch);
            }

            if (!patch.positive && conf >= thetaFP)
            {
                falsePositives->push_back(patch);
            }
        }
    }
} /* namespace CFtld */
