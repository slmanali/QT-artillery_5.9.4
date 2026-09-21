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
 * CFEnsembleClassifier.cpp
 *
 *  Created on: Nov 16, 2011
 *      Author: Georg Nebehay
 */

#include "CFDetectorCascade.h"

#include <cstdlib>
#include <cmath>
#include <opencv/cv.h>

#include "CFEnsembleClassifier.h"

using namespace std;
using namespace cv;

namespace CFtld
{
    //TODO: Convert this to a function
#define sub2idx(x,y,widthstep) ((int) (floor((x)+0.5) + floor((y)+0.5)*(widthstep)))

    CFEnsembleClassifier::CFEnsembleClassifier() :
        features(NULL),
        featureOffsets(NULL),
        posteriors(NULL),
        positives(NULL),
        negatives(NULL)
    {
        numTrees = 10;
        numFeatures = 13;
        enabled = true;
    }

    CFEnsembleClassifier::~CFEnsembleClassifier()
    {
        release();
    }

    void CFEnsembleClassifier::init(std::shared_ptr<std::mt19937> rng)
    {
        numIndices = static_cast<int>(pow(2.0f, numFeatures));

        initFeatureLocations(rng);
        initFeatureOffsets();
        initPosteriors();
    }

    void CFEnsembleClassifier::release()
    {
        if (features != NULL)
        {
            delete[] features;
            features = NULL;
        }

        if (featureOffsets != NULL)
        {
            delete[] featureOffsets;
            featureOffsets = NULL;
        }

        if (posteriors != NULL)
        {
            delete[] posteriors;
            posteriors = NULL;
        }

        if (positives != NULL)
        {
            delete[] positives;
            positives = NULL;
        }

        if (negatives != NULL)
        {
            delete[] negatives;
            negatives = NULL;
        }
    }

    /*
     * Generates random measurements in the format <x1,y1,x2,y2>
     */
    void CFEnsembleClassifier::initFeatureLocations(std::shared_ptr<std::mt19937> rng)
    {
        int size = 2 * 2 * numFeatures * numTrees;
        std::uniform_real_distribution<float> dist(0, 1);
        features = new float[size];

        for (int i = 0; i < size; i++)
        {
            features[i] = dist(*rng);
        }
    }

    //Creates offsets that can be added to bounding boxes
    //offsets are contained in the form delta11, delta12,... (combined index of dw and dh)
    //Order: scale.tree->feature
    void CFEnsembleClassifier::initFeatureOffsets()
    {
        featureOffsets = new int[numScales * numTrees * numFeatures * 2]{};
        int *off = featureOffsets;

        for (int k = 0; k < numScales; k++)
        {
            Size scale = scales[k];

            for (int i = 0; i < numTrees; i++)
            {
                for (int j = 0; j < numFeatures; j++)
                {
                    float *currentFeature = features + (4 * numFeatures) * i + 4 * j;
                    *off++ = sub2idx((scale.width - 1) * currentFeature[0] + 1, (scale.height - 1) * currentFeature[1] + 1, imgWidthStep); //We add +1 because the index of the bounding box points to x-1, y-1
                    *off++ = sub2idx((scale.width - 1) * currentFeature[2] + 1, (scale.height - 1) * currentFeature[3] + 1, imgWidthStep);
                }
            }
        }
    }

    void CFEnsembleClassifier::initPosteriors()
    {
        posteriors = new float[numTrees * numIndices]{};
        positives = new int[numTrees * numIndices]{};
        negatives = new int[numTrees * numIndices]{};
    }

    void CFEnsembleClassifier::nextIteration(const Mat &img)
    {
        if (!enabled) return;

        this->img = (const unsigned char *)img.data;
    }

    //Classical fern algorithm
    int CFEnsembleClassifier::calcFernFeature(int windowIdx, int treeIdx)
    {
        int index = 0;
        int *bbox = windowOffsets + windowIdx * TLD_WINDOW_OFFSET_SIZE;
        int *off = featureOffsets + bbox[4] + treeIdx * 2 * numFeatures; //bbox[4] is pointer to features for the current scale

        for (int i = 0; i < numFeatures; i++)
        {
            index <<= 1;

            int fp0 = img[bbox[0] + off[0]];
            int fp1 = img[bbox[0] + off[1]];

            if (fp0 > fp1)
            {
                index |= 1;
            }

            off += 2;
        }

        return index;
    }

    void CFEnsembleClassifier::calcFeatureVector(int windowIdx, int *featureVector)
    {
        for (int i = 0; i < numTrees; i++)
        {
            featureVector[i] = calcFernFeature(windowIdx, i);
        }
    }

    float CFEnsembleClassifier::calcConfidence(int *featureVector)
    {
        float conf = 0.0;

        for (int i = 0; i < numTrees; i++)
        {
            conf += posteriors[i * numIndices + featureVector[i]];
        }

        return conf;
    }

    void CFEnsembleClassifier::classifyWindow(int windowIdx)
    {
        int *featureVector = detectionResult->featureVectors + numTrees * windowIdx;
        calcFeatureVector(windowIdx, featureVector);

        detectionResult->posteriors[windowIdx] = calcConfidence(featureVector);
    }

    bool CFEnsembleClassifier::filter(int i)
    {
        if (!enabled) return true;

        classifyWindow(i);

        if (detectionResult->posteriors[i] < 0.5) return false;

        return true;
    }

    void CFEnsembleClassifier::updatePosterior(int treeIdx, int idx, int positive, int amount)
    {
        int arrayIndex = treeIdx * numIndices + idx;
        (positive) ? positives[arrayIndex] += amount : negatives[arrayIndex] += amount;
        posteriors[arrayIndex] = ((float)positives[arrayIndex]) / (positives[arrayIndex] + negatives[arrayIndex]) / (float)numTrees;
    }

    void CFEnsembleClassifier::updatePosteriors(int *featureVector, int positive, int amount)
    {
        for (int i = 0; i < numTrees; i++)
        {
            int idx = featureVector[i];
            updatePosterior(i, idx, positive, amount);
        }
    }

    void CFEnsembleClassifier::learn(int *boundary, int positive, int *featureVector)
    {
        if (!enabled) return;

        float conf = calcConfidence(featureVector);

        //Update if positive patch and confidence < 0.5 or negative and conf > 0.5
        if ((positive && conf < 0.5) || (!positive && conf > 0.5))
        {
            updatePosteriors(featureVector, positive, 1);
        }
    }
} /* namespace CFtld */
