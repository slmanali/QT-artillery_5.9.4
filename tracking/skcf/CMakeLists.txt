include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})
GET_FILENAME_COMPONENT(CURR_DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

FILE(GLOB files
	"*.h"
	"*.hpp"
	"*.cpp"
)

ADD_LIBRARY("${CURR_DIR_NAME}"  ${files})