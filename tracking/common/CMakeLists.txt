
link_directories(${OpenCV_LIB_DIR})

include_directories(
    ../OpenTLD/TLD
    ../ObjectTracker
    ${OpenCV_INCLUDE_DIRS})

FIND_PACKAGE( OpenCV REQUIRED )

add_definitions(-DUNICODE -D_UNICODE)
#-------------------------------------------------------------------------------
# homing
 add_library(Tracker_Api 
 ../common/tracker_api.cpp
	 ../common/tracker_api.h
	 )
target_link_libraries(Tracker_Api SHARED libObjectTracking libopentld strucklib cmtlib strucklib KCFlib DSSTlib libopencftld skcf ${OpenCV_LIBS})

 add_library(Tracker_Api_com SHARED 
 ../common/tracker_api_com.cpp
	 ../common/tracker_api_com.h
	 )
target_link_libraries(Tracker_Api_com libObjectTracking libopentld strucklib cmtlib strucklib KCFlib DSSTlib libopencftld skcf ${OpenCV_LIBS})

