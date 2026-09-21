FIND_PACKAGE( OpenCV REQUIRED )

add_definitions(-DUNICODE -D_UNICODE)

include_directories(mftracker
    TLD
    cvblobs
    ${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

add_library(libopentld
    cvblobs/blob.cpp
    cvblobs/BlobContour.cpp
    cvblobs/BlobOperators.cpp
    cvblobs/BlobProperties.h
    cvblobs/BlobProperties.cpp
    cvblobs/BlobResult.cpp
    cvblobs/ComponentLabeling.cpp
    cvblobs/blob.h
    cvblobs/BlobContour.h
    cvblobs/BlobLibraryConfiguration.h
    cvblobs/BlobOperators.h
    cvblobs/BlobResult.h
    cvblobs/ComponentLabeling.h
    mftracker/BB.cpp
    mftracker/BBPredict.cpp
    mftracker/FBTrack.cpp
    mftracker/Lk.cpp
    mftracker/Median.cpp
    TLD/Clustering.cpp
    TLD/DetectionResult.cpp
    TLD/DetectorCascade.cpp
    TLD/EnsembleClassifier.cpp
    TLD/ForegroundDetector.cpp
    TLD/MedianFlowTracker.cpp
    TLD/NNClassifier.cpp
    TLD/TLD.cpp
    TLD/TLDUtil.cpp
    TLD/VarianceFilter.cpp
    mftracker/BB.h
    mftracker/BBPredict.h
    mftracker/FBTrack.h
    mftracker/Lk.h
    mftracker/Median.h
    TLD/Clustering.h
    TLD/DetectionResult.h
    TLD/DetectorCascade.h
    TLD/EnsembleClassifier.h
    TLD/ForegroundDetector.h
    TLD/IntegralImage.h
    TLD/MedianFlowTracker.h
    TLD/NNClassifier.h
    TLD/NormalizedPatch.h
    TLD/TLD.h
    TLD/TLDUtil.h
    TLD/VarianceFilter.h)

target_link_libraries(libopentld ${OpenCV_LIBS})

#set_target_properties(libopentld PROPERTIES OUTPUT_NAME Tracking)

