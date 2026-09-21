/*
// License Agreement (3-clause BSD License)
// Copyright (c) 2015, Klaus Haag, all rights reserved.
// Third party copyrights and patents are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the names of the copyright holders nor the names of the contributors
//   may be used to endorse or promote products derived from this software
//   without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall copyright holders or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
*/

/* This class represents a C++ implementation of the Kernelized
Correlation Filter tracker (KCF) [1].

It is implemented closely to the Matlab implementation by the original authors:
http://home.isr.uc.pt/~henriques/circulant/
However, some implementation details differ and some difference in performance
has to be expected.

This specific implementation features the scale adaption, sub-pixel
accuracy for the correlation response evaluation and a more robust
filter update scheme [2] used by Henriques, et al. in the VOT Challenge 2014.

As default scale adaption, the tracker uses the 1D scale filter
presented in [3]. The scale filter can be found in scale_estimator.hpp.
Additionally, target loss detection is implemented according to [4].

Every complex matrix is as default in CCS packed form:
see : https://software.intel.com/en-us/node/504243
and http://docs.opencv.org/modules/core/doc/operations_on_arrays.html

References:
[1] J. Henriques, et al.,
"High-Speed Tracking with Kernelized Correlation Filters,"
PAMI, 2015.

[2] M. Danelljan, et al.,
“Adaptive Color Attributes for Real-Time Visual Tracking,”
in Proc. CVPR, 2014.

[3] M. Danelljan,
"Accurate Scale Estimation for Robust Visual Tracking,"
Proceedings of the British Machine Vision Conference BMVC, 2014.

[4] D. Bolme, et al.,
“Visual Object Tracking using Adaptive Correlation Filters,”
in Proc. CVPR, 2010.
*/

//#ifndef KCF_TRACKER_HPP_
//#define KCF_TRACKER_HPP_
#ifndef OPENCV_KCF_H
#define OPENCV_KCF_H
#include <opencv2/imgproc/imgproc.hpp>
#if CV_MAJOR_VERSION > 2
#include <opencv2/core/traits.hpp>
#endif
#include <opencv2/core/core.hpp>
#include <iostream>
#include <algorithm>

/*#include "cv_ext.hpp"
#include "feature_channels.hpp"
#include "gradientMex.hpp"
#include "mat_consts.hpp"
#include "math_helper.hpp"
#include "cf_tracker.hpp"
#include "kcf_debug.hpp"
#include "scale_estimator.hpp"
#include "psr.hpp"*/
#include "../cf_tracking/src/cf_libs/common/cf_tracker.hpp"
#include "../cf_tracking/src/cf_libs/kcf/kcf_tracker.hpp"
#include "../cf_tracking/src/cf_libs/kcf/kcf_debug.hpp"
namespace cv
{
	namespace kcftracker
	{
		class KCF
		{
		public:

		};
	
	}
}
#endif /* KCF_TRACKER_H_ */
