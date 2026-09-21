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
 * CFTLD.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: Georg Nebehay

 * + Author: Klaus Haag
 *  * Replace Median Flow tracker with KCFcpp or DSSTcpp
 *  * Change to self-learning approach instead of semi-supervised
 */

#include "CFTLD.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <random>
#include "../cf_tracking/src/cf_libs/kcf/kcf_tracker.hpp"
#include "../cf_tracking/src/cf_libs/dsst/dsst_tracker.hpp"

#include "CFNNClassifier.h"
#include "CFTLDUtil.h"

using namespace std;
//using namespace cv;
using namespace cf_tracking;

namespace CFtld
{
    CFTLD::CFTLD() :
        hasImageDimensions(false),
        isTrackerValid(false),
        runTracker(true),
        tracker(0)
    {
        trackerEnabled = true;
        detectorEnabled = true;
        learningEnabled = true;
        alternating = false;
        valid = false;
        learning = false;
        currBB = NULL;
        prevBB = new cv::Rect(0, 0, 0, 0);
        seed = 0;
        detectorCascade = new CFDetectorCascade();
        nnClassifier = detectorCascade->nnClassifier;
    }
	void CFTLD::storeCurrentData()
	{
		prevImg.release();
		prevImg = currImg; //Store old image (if any)
		if (currBB)//Store old bounding box (if any)
		{
			prevBB->x = currBB->x;
			prevBB->y = currBB->y;
			prevBB->width = currBB->width;
			prevBB->height = currBB->height;
		}
	/*	else
		{
			prevBB->x = 0;
			prevBB->y = 0;
			prevBB->width = 0;
			prevBB->height = 0;
		}*/

		detectorCascade->cleanPreviousData(); //Reset detector results
	//	medianFlowTracker->cleanPreviousData();
		isTrackerValid = false;
		wasValid = valid;
	}


    void CFTLD::init(bool useDsstTracker)
    {
        if (!tracker)
        {
            if (useDsstTracker)
            {
                DsstParameters dsstParameters;
                dsstParameters.enableTrackingLossDetection = true;
                tracker.reset(new DsstTracker(dsstParameters));
            }
            else
            {
                KcfParameters kcfParameters;
                kcfParameters.enableTrackingLossDetection = true;
                tracker.reset(new KcfTracker(kcfParameters));
            }
        }

        std::cout << "\n\n\n-----------CF_TLD---------------\n";
        std::cout << "---------- " << tracker->getId() << " --------------" << "\n\n\n";
    }

    CFTLD::~CFTLD()
    {
        storeCurrentData();
        deleteCurrentBB();

        if (detectorCascade)
        {
            delete detectorCascade;
            detectorCascade = NULL;
        }
    }

    void CFTLD::release()
    {
        detectorCascade->release();
        deleteCurrentBB();
    }

  /*  void CFTLD::storeCurrentData()
    {
        isTrackerValid = false;
        detectorCascade->cleanPreviousData(); //Reset detector results
    }*/

    void CFTLD::selectObject(const cv::Mat &img, cv::Rect *bb)
    {
        if (!tracker)
            return;

        if (!rng)
        {
            std::random_device rd;
            std::shared_ptr<std::mt19937> g(new std::mt19937(rd()));
            g->seed((unsigned long)seed);
            rng = g;
        }

        rng->seed((unsigned long)seed);

        cv::Mat grayFrame;
        cv::cvtColor(img, grayFrame, CV_BGR2GRAY);

        // initialize the image dimensions once
        if (!hasImageDimensions)
        {
            detectorCascade->imgWidth = grayFrame.cols;
            detectorCascade->imgHeight = grayFrame.rows;
            detectorCascade->imgWidthStep = static_cast<int>(grayFrame.step);
        }

        runTracker = true;
        //Delete old object
        detectorCascade->release();

        detectorCascade->objWidth = bb->width;
        detectorCascade->objHeight = bb->height;

        if (bb->height < detectorCascade->minSize)
            detectorCascade->minSize = bb->height;

        if (bb->width < detectorCascade->minSize)
            detectorCascade->minSize = bb->width;

        //Init detector cascade
        detectorCascade->init(rng);
        tracker->reinit(img, *bb);

        currImg = grayFrame;
        deleteCurrentBB();
        currBB = tldCopyRect(bb);
        currConf = 1;
        valid = true;

        initialLearning();
    }

    void CFTLD::processImage(cv::Mat &img)
    {
        if (!tracker)
            return;

        storeCurrentData();

        cv::Mat grayFrame;
        cv::cvtColor(img, grayFrame, CV_BGR2GRAY);
        currImg = grayFrame; // Store new image , right after storeCurrentData();

        if (trackerEnabled && runTracker)
        {
            isTrackerValid = tracker->update(img, trackerBB);

            if (!isTrackerValid)
                runTracker = false;
        }

        if (detectorEnabled && (!alternating || !isTrackerValid))
            detectorCascade->detect(grayFrame);

        fuseHypotheses(img);

        learn();
    }

    void CFTLD::fuseHypotheses(const cv::Mat& colorImg)
    {
        int numClusters = detectorCascade->detectionResult->numClusters;
        cv::Rect *detectorBB = detectorCascade->detectionResult->detectorBB;
        deleteCurrentBB();

        currConf = 0;
        valid = false;

        if (!detectorEnabled)
        {
            if (!isTrackerValid)
                return;

            currBB = tldCopyRect(&trackerBB);
            valid = true;
            return;
        }

        float confDetector = 0;

        if (numClusters == 1)
            confDetector = nnClassifier->classifyBB(currImg, detectorBB);

        if (isTrackerValid)
        {
            float confTracker = nnClassifier->classifyBB(currImg, &trackerBB);
            currBB = tldCopyRect(&trackerBB);
            valid = true;
            currConf = confTracker;
        }
        else if (numClusters == 1)
        {
            // reinit tracker
            if (trackerEnabled)
            {
				if (tracker->updateAt(colorImg, *detectorBB))//detectorBB omar
                {
                    currConf = nnClassifier->classifyBB(currImg, detectorBB);
                    currBB = tldCopyRect(detectorBB);
                    valid = true;
                    runTracker = true;
                }
                else
                {
                  //  deleteCurrentBB();
					currBB = tldCopyRect(prevBB);
                    currConf = 0;
                    valid = false;
                }
            }
        }
    }

    void CFTLD::initialLearning()
    {
        learning = true; //This is just for display purposes

        CFDetectionResult *detectionResult = detectorCascade->detectionResult;

        detectorCascade->detect(currImg);

        //This is the positive patch
        CFNormalizedPatch initPatch;
        tldExtractNormalizedPatchRect(currImg, currBB, initPatch.values);
        initPatch.positive = 1;

        float initVar = tldCalcVariance(initPatch.values, TLD_PATCH_SIZE * TLD_PATCH_SIZE);
        detectorCascade->varianceFilter->minVar = initVar / 2;

        float *overlap = new float[detectorCascade->numWindows]{};
        tldOverlapRect(detectorCascade->windows, detectorCascade->numWindows, currBB, overlap);

        //Add all bounding boxes with high overlap
        vector< pair<int, float> > positiveIndices;
        vector<int> negativeIndices;

        //First: Find overlapping positive and negative patches
        for (int i = 0; i < detectorCascade->numWindows; i++)
        {
            if (overlap[i] > 0.7)
            {
                positiveIndices.push_back(pair<int, float>(i, overlap[i]));
            }

            if (overlap[i] < 0.2)
            {
                float variance = detectionResult->variances[i];

                if (!detectorCascade->varianceFilter->enabled || variance > detectorCascade->varianceFilter->minVar)   //TODO: This check is unnecessary if minVar would be set before calling detect.
                {
                    negativeIndices.push_back(i);
                }
            }
        }

        sort(positiveIndices.begin(), positiveIndices.end(), tldSortByOverlapDesc);

        vector<CFNormalizedPatch> patches;

        patches.push_back(initPatch); //Add first patch to patch list

        size_t numIterations = std::min<size_t>(positiveIndices.size(), 10); //Take at most 10 bounding boxes (sorted by overlap)

        for (int i = 0; i < numIterations; i++)
        {
            int idx = positiveIndices.at(i).first;
            //Learn this bounding box
            //TODO: Somewhere here image warping might be possible
            detectorCascade->ensembleClassifier->learn(&detectorCascade->windows[TLD_WINDOW_SIZE * idx], true, &detectionResult->featureVectors[detectorCascade->numTrees * idx]);
        }

        std::shuffle(negativeIndices.begin(), negativeIndices.end(), *rng);

        //Choose 100 random patches for negative examples
        for (size_t i = 0; i < std::min<size_t>(100, negativeIndices.size()); i++)
        {
            int idx = negativeIndices.at(i);

            CFNormalizedPatch patch;
            tldExtractNormalizedPatchBB(currImg, &detectorCascade->windows[TLD_WINDOW_SIZE * idx], patch.values);
            patch.positive = 0;
            patches.push_back(patch);
        }

        detectorCascade->nnClassifier->learn(patches);
        delete[] overlap;
    }

    //Do this when current trajectory is valid
    void CFTLD::learn()
    {
        if (!learningEnabled || !valid || !detectorEnabled)
        {
            learning = false;
            return;
        }

        learning = true;

        CFDetectionResult *detectionResult = detectorCascade->detectionResult;

        if (!detectionResult->containsValidData)
            detectorCascade->detect(currImg);

        //This is the positive patch
        CFNormalizedPatch patch;
        tldExtractNormalizedPatchRect(currImg, currBB, patch.values);

        float *overlap = new float[detectorCascade->numWindows]{};
        tldOverlapRect(detectorCascade->windows, detectorCascade->numWindows, currBB, overlap);

        //Add all bounding boxes with high overlap
        vector<pair<int, float> > positiveIndices;
        vector<int> negativeIndices;
        vector<int> negativeIndicesForNN;

        //First: Find overlapping positive and negative patches

        for (int i = 0; i < detectorCascade->numWindows; i++)
        {
            if (overlap[i] > 0.7)
            {
                positiveIndices.push_back(pair<int, float>(i, overlap[i]));
            }

            if (overlap[i] < 0.2)
            {
                if (!detectorCascade->ensembleClassifier->enabled || detectionResult->posteriors[i] > 0.5)   //Should be 0.5 according to the paper
                {
                    negativeIndices.push_back(i);
                }

                if (!detectorCascade->ensembleClassifier->enabled || detectionResult->posteriors[i] > 0.5)
                {
                    negativeIndicesForNN.push_back(i);
                }
            }
        }

        sort(positiveIndices.begin(), positiveIndices.end(), tldSortByOverlapDesc);

        vector<CFNormalizedPatch> patches;

        patch.positive = 1;
        patches.push_back(patch);
        //TODO: Flip

        size_t numIterations = std::min<size_t>(positiveIndices.size(), 10); //Take at most 10 bounding boxes (sorted by overlap)

        for (size_t i = 0; i < negativeIndices.size(); i++)
        {
            int idx = negativeIndices.at(i);
            //TODO: Somewhere here image warping might be possible
            detectorCascade->ensembleClassifier->learn(&detectorCascade->windows[TLD_WINDOW_SIZE * idx], false, &detectionResult->featureVectors[detectorCascade->numTrees * idx]);
        }

        //TODO: Randomization might be a good idea
        for (int i = 0; i < numIterations; i++)
        {
            int idx = positiveIndices.at(i).first;
            //TODO: Somewhere here image warping might be possible
            detectorCascade->ensembleClassifier->learn(&detectorCascade->windows[TLD_WINDOW_SIZE * idx], true, &detectionResult->featureVectors[detectorCascade->numTrees * idx]);
        }

        for (size_t i = 0; i < negativeIndicesForNN.size(); i++)
        {
            int idx = negativeIndicesForNN.at(i);

            CFNormalizedPatch patch;
            tldExtractNormalizedPatchBB(currImg, &detectorCascade->windows[TLD_WINDOW_SIZE * idx], patch.values);
            patch.positive = 0;
            patches.push_back(patch);
        }

        detectorCascade->nnClassifier->learn(patches);

        //cout << "NN has now " << detectorCascade->nnClassifier->truePositives->size() << " positives and " << detectorCascade->nnClassifier->falsePositives->size() << " negatives.\n";

        delete[] overlap;
    }

    inline void CFTLD::deleteCurrentBB()
    {
        if (currBB)
        {
            delete currBB;
            currBB = NULL;
        }
    }
} /* namespace CFtld */
