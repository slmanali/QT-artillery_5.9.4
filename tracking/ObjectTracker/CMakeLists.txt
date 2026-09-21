if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

file(GLOB Threshold_INC
	"../Threshold_Tracker/*.cpp"
    "../Threshold_Tracker/*.c"
    "../Threshold_Tracker/*.h"
)
include_directories(../OpenTld/TLD
                     ../CF_tld/tld
                     ../OpenTLD
					 ../OpenCMT
					../OpenCMT/fastcluster
					../OpenCMT/logging
					../eigen.2.0.17
					../OpenStruck/src/GraphUtils
					 ${OpenCV_INCLUDE_DIRS}
					 
					  ../cf_tracking/src/cf_libs/kcf
                     ../cf_tracking/src/cf_libs/dsst
                     ../cf_tracking/src/cf_libs/common
					 ../cf_tracking/src/3rdparty/tclap
					 ../cf_tracking/src/3rdparty/cv_ext
					 ../cf_tracking/src/3rdparty/piotr
					 ../cf_tracking/src/3rdparty/piotr/src
					 ../cf_tracking/src/main
					 ../skcf)
######################kcf############################################




					
######################################################################					
IF(WIN32)
ADD_DEFINITIONS(-DNOMINMAX)
 ENDIF()
 
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -DNOMINMAX)
FIND_PACKAGE( OpenCV REQUIRED )

# add platform-specific defines here so code can know which
# OS we're using (WIN32, UNIX, APPLE)
# :TODO:
#ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS )

add_library (libObjectTracking 

       cv_onlineboosting.cpp
	   cv_onlineboosting.h 
	   cv_onlinemil.cpp 
	   cv_onlinemil.h 
	   cv_tld.cpp
	   cv_tld.h
	   cv_ncc.h
	   cv_ncc.cpp
	   cv_camshift.h
	   cv_camshift.cpp
	   cv_phasecorr.h
	   cv_phasecorr.cpp
	   cv_cmt.h
	   cv_cmt.cpp
	   cv_ct.h
	   cv_ct.cpp
	   #cv_tracker_name.h
	   #cv_tracker_name.cpp
	   cv_struck.cpp
	   cv_struck.h
	   object_tracker.cpp 
	   object_tracker.h
        cv_trackerfeatures.cpp
        cv_trackerfeatures.h
		cv_kcf.h
		cv_dsst.h
		cv_cftld.h
		cv_cftld.cpp
		cv_mncc.h
		cv_mncc.cpp
		cv_skcf.h
		${Threshold_INC}
		../skcf/skcfdcf.cpp
		../skcf/skcfdcf.h
		../skcf/ktrackers.cpp
		../skcf/ktrackers.h
		../skcf/gradient.cpp
		../skcf/gradient.h
		cv_Mosse.h
		cv_Mosse.cpp)
   
target_link_libraries(libObjectTracking libopentld cmtlib strucklib KCFlib DSSTlib libopencftld ${OpenCV_LIBRARIES})

#set_target_properties(libObjectTracking PROPERTIES OUTPUT_NAME Tracking)


