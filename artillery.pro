#-------------------------------------------------
#
# Project created by QtCreator 2016-04-24T10:40:07
#
#-------------------------------------------------

QT       += core gui opengl sql svg network

CONFIG += c++14
QMAKE_CXXFLAGS +=-msse4.1
CONFIG += force_debug_info
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = artillery
TEMPLATE = app


#####################    Vlc DIR   #####################
INCLUDEPATH += E:\WORK\VLC\include

#####################    Vlc LIB  #####################
LIBS += E:\WORK\VLC\VLC-Qt_1.1.0_win32_mingw\bin\libvlc.dll
LIBS += E:\WORK\VLC\VLC-Qt_1.1.0_win32_mingw\bin\libvlccore.dll

LIBS += -lwsock32

#####################    OPEN_CV_320 MINGW DIR   #####################
INCLUDEPATH += E:\WORK\installQT\include
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\GTL
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\cvblob
#####################    OPEN_CV_320 MINGW LIB  #####################
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_calib3d320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_core320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_features2d320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_flann320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_highgui320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_imgcodecs320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_imgproc320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_ml320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_objdetect320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_photo320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_stitching320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_superres320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_video320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_videoio320.dll
LIBS += E:\WORK\installQT\x86\mingw\bin\libopencv_videostab320.dll

#####################    Tracking DIR   #####################
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\cf_tracking\src\3rdparty\cv_ext
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\cf_tracking\src\3rdparty\piotr
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\cf_tracking\src\3rdparty\piotr\src
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\cf_tracking\src\3rdparty\tclap
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\cf_tracking\src\cf_libs\kcf
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\cf_tracking\src\cf_libs\kcf
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\cf_tracking\src\cf_libs\common
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\cf_tracking\src\main
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\common
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\ObjectTracker
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\OpenTLD
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\eigen.2.0.17
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\CF_tld
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\skcf
INCLUDEPATH += E:\WORK\QT_tracking\artillery_5.9.4\tracking\Threshold_Tracker

#####################    Tracking LIB  #####################
LIBS += E:\WORK\QT_tracking\artillery_5.9.4\Tracking_lib\libcmtlib.a
LIBS += E:\WORK\QT_tracking\artillery_5.9.4\Tracking_lib\libDSSTlib.a
LIBS += E:\WORK\QT_tracking\artillery_5.9.4\Tracking_lib\libKCFlib.a
LIBS += E:\WORK\QT_tracking\artillery_5.9.4\Tracking_lib\liblibObjectTracking.a
LIBS += E:\WORK\QT_tracking\artillery_5.9.4\Tracking_lib\liblibopencftld.a
LIBS += E:\WORK\QT_tracking\artillery_5.9.4\Tracking_lib\liblibopentld.a
LIBS += E:\WORK\QT_tracking\artillery_5.9.4\Tracking_lib\libskcf.a
LIBS += E:\WORK\QT_tracking\artillery_5.9.4\Tracking_lib\libstrucklib.a
LIBS += E:\WORK\QT_tracking\artillery_5.9.4\Tracking_lib\libTracker_Api.a

#####################    BOOST_DIR   #####################
INCLUDEPATH += E:\boost_1_59_32

#####################    Boost_LIB  #####################
LIBS += E:\boost_1_59_32\boost_mingw\lib\libboost_system-mgw53-mt-1_59.a
LIBS += E:\boost_1_59_32\boost_mingw\lib\libboost_thread-mgw53-mt-1_59.a
LIBS += E:\boost_1_59_32\boost_mingw\lib\libboost_date_time-mgw53-mt-1_59.a
LIBS += E:\boost_1_59_32\boost_mingw\lib\libboost_chrono-mgw53-mt-1_59.a
LIBS += -lws2_32# added to solve problem of boost::asio linking

HEADERS += \
    axis_data.h \
    BackgroundSubtract.h \
    capturethread.h \
    Ctracker.h \
    defines.h \
    Detector.h \
    fheap.h \
    HungarianAlg.h \
    Kalman.h \
    LocalTracker.h \
    mainwindow.h \
    mwbmatching.h \
    mygraph.h \
#    MySharedData.h \
#    newSerialHeaders.h \
    optoload_constants.h \
    qt_compiler.h \
    qt_utils.h \
    sarab_osdfuncs.h \
    setting.h \
    tokenise.h \
    track.h \
    vibeBG.hpp \
    package_analysis/ForegroundMaskAnalysis.h \
    package_analysis/PerformanceUtils.h \
    package_analysis/PixelUtils.h \
    package_bgs/_template_/amber/amber.h \
    package_bgs/_template_/Amber.h \
    package_bgs/_template_/MyBGS.h \
    package_bgs/dp/AdaptiveMedianBGS.h \
    package_bgs/dp/Bgs.h \
    package_bgs/dp/BgsParams.h \
    package_bgs/dp/Eigenbackground.h \
    package_bgs/dp/Error.h \
    package_bgs/dp/GrimsonGMM.h \
    package_bgs/dp/Image.h \
    package_bgs/dp/MeanBGS.h \
    package_bgs/dp/PratiMediodBGS.h \
    package_bgs/dp/TextureBGS.h \
    package_bgs/dp/WrenGA.h \
    package_bgs/dp/ZivkovicAGMM.h \
    package_bgs/IMBS/IMBS.hpp \
    package_bgs/KDE/KernelTable.h \
    package_bgs/KDE/NPBGmodel.h \
    package_bgs/KDE/NPBGSubtractor.h \
    package_bgs/lb/BGModel.h \
    package_bgs/lb/BGModelFuzzyGauss.h \
    package_bgs/lb/BGModelFuzzySom.h \
    package_bgs/lb/BGModelGauss.h \
    package_bgs/lb/BGModelMog.h \
    package_bgs/lb/BGModelSom.h \
    package_bgs/lb/Types.h \
    package_bgs/LBP_MRF/block.h \
    package_bgs/LBP_MRF/graphh.h \
    package_bgs/LBP_MRF/MEDefs.hpp \
    package_bgs/LBP_MRF/MEHistogram.hpp \
    package_bgs/LBP_MRF/MEImage.hpp \
    package_bgs/LBP_MRF/MotionDetection.hpp \
    package_bgs/LBSP/BackgroundSubtractorLBSP.h \
    package_bgs/LBSP/BackgroundSubtractorLBSP_.h \
    package_bgs/LBSP/BackgroundSubtractorLOBSTER.h \
    package_bgs/LBSP/BackgroundSubtractorPAWCS.h \
    package_bgs/LBSP/BackgroundSubtractorSuBSENSE.h \
    package_bgs/LBSP/DistanceUtils.h \
    package_bgs/LBSP/LBSP.h \
    package_bgs/LBSP/LBSP_.h \
    package_bgs/LBSP/RandUtils.h \
    package_bgs/MultiLayer/BackgroundSubtractionAPI.h \
    package_bgs/MultiLayer/BGS.h \
    package_bgs/MultiLayer/blob.h \
    package_bgs/MultiLayer/BlobExtraction.h \
    package_bgs/MultiLayer/BlobLibraryConfiguration.h \
    package_bgs/MultiLayer/BlobResult.h \
    package_bgs/MultiLayer/CMultiLayerBGS.h \
    package_bgs/MultiLayer/LocalBinaryPattern.h \
    package_bgs/MultiLayer/OpenCvDataConversion.h \
    package_bgs/MultiLayer/OpenCvLegacyIncludes.h \
    package_bgs/PBAS/PBAS.h \
    package_bgs/SigmaDelta/sdLaMa091.h \
    package_bgs/T2F/FuzzyUtils.h \
    package_bgs/T2F/MRF.h \
    package_bgs/T2F/T2FGMM.h \
    package_bgs/T2F/T2FMRF.h \
    package_bgs/TwoPoints/two_points.h \
    package_bgs/ViBe/vibe-background-sequential.h \
    package_bgs/VuMeter/TBackground.h \
    package_bgs/VuMeter/TBackgroundVuMeter.h \
    package_bgs/AdaptiveBackgroundLearning.h \
    package_bgs/AdaptiveSelectiveBackgroundLearning.h \
    package_bgs/bgslibrary.h \
    package_bgs/CodeBook.h \
    package_bgs/DPAdaptiveMedian.h \
    package_bgs/DPEigenbackground.h \
    package_bgs/DPGrimsonGMM.h \
    package_bgs/DPMean.h \
    package_bgs/DPPratiMediod.h \
    package_bgs/DPTexture.h \
    package_bgs/DPWrenGA.h \
    package_bgs/DPZivkovicAGMM.h \
    package_bgs/FrameDifference.h \
    package_bgs/FuzzyChoquetIntegral.h \
    package_bgs/FuzzySugenoIntegral.h \
    package_bgs/GMG.h \
    package_bgs/IBGS.h \
    package_bgs/IndependentMultimodal.h \
    package_bgs/KDE.h \
    package_bgs/KNN.h \
    package_bgs/LBAdaptiveSOM.h \
    package_bgs/LBFuzzyAdaptiveSOM.h \
    package_bgs/LBFuzzyGaussian.h \
    package_bgs/LBMixtureOfGaussians.h \
    package_bgs/LBP_MRF.h \
    package_bgs/LBSimpleGaussian.h \
    package_bgs/LOBSTER.h \
    package_bgs/MixtureOfGaussianV1.h \
    package_bgs/MixtureOfGaussianV2.h \
    package_bgs/MultiCue.h \
    package_bgs/MultiLayer.h \
    package_bgs/PAWCS.h \
    package_bgs/PixelBasedAdaptiveSegmenter.h \
    package_bgs/SigmaDelta.h \
    package_bgs/StaticFrameDifference.h \
    package_bgs/SuBSENSE.h \
    package_bgs/T2FGMM_UM.h \
    package_bgs/T2FGMM_UV.h \
    package_bgs/T2FMRF_UM.h \
    package_bgs/T2FMRF_UV.h \
    package_bgs/TwoPoints.h \
    package_bgs/ViBe.h \
    package_bgs/VuMeter.h \
    package_bgs/WeightedMovingMean.h \
    package_bgs/WeightedMovingVariance.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/Arg.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/ArgException.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/ArgTraits.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/CmdLine.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/CmdLineInterface.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/CmdLineOutput.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/Constraint.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/DocBookOutput.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/HelpVisitor.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/IgnoreRestVisitor.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/MultiArg.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/MultiSwitchArg.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/OptionalUnlabeledTracker.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/StandardTraits.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/StdOutput.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/SwitchArg.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/UnlabeledMultiArg.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/UnlabeledValueArg.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/ValueArg.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/ValuesConstraint.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/VersionVisitor.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/Visitor.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/XorHandler.h \
    tracking/CF_tld/cf_tracking/src/3rdparty/tclap/tclap/ZshCompletionOutput.h \
    tracking/CF_tld/cf_tracking/src/cf_libs/common/cf_tracker.hpp \
    tracking/CF_tld/cf_tracking/src/cf_libs/common/cv_ext.hpp \
    tracking/CF_tld/cf_tracking/src/cf_libs/common/feature_channels.hpp \
    tracking/CF_tld/cf_tracking/src/cf_libs/common/mat_consts.hpp \
    tracking/CF_tld/cf_tracking/src/cf_libs/common/scale_estimator.hpp \
    tracking/CF_tld/cf_tracking/src/cf_libs/common/tracker_debug.hpp \
    tracking/CF_tld/cf_tracking/src/cf_libs/dsst/dsst_debug.hpp \
    tracking/CF_tld/cf_tracking/src/cf_libs/dsst/dsst_tracker.hpp \
    tracking/CF_tld/cf_tracking/src/cf_libs/kcf/kcf_debug.hpp \
    tracking/CF_tld/cf_tracking/src/cf_libs/kcf/kcf_tracker.hpp \
    tracking/CF_tld/CFtld/CFClustering.h \
    tracking/CF_tld/CFtld/CFDetectionResult.h \
    tracking/CF_tld/CFtld/CFDetectorCascade.h \
    tracking/CF_tld/CFtld/CFEnsembleClassifier.h \
    tracking/CF_tld/CFtld/CFIntegralImage.h \
    tracking/CF_tld/CFtld/CFNNClassifier.h \
    tracking/CF_tld/CFtld/CFNormalizedPatch.h \
    tracking/CF_tld/CFtld/CFTLD.h \
    tracking/CF_tld/CFtld/CFTLDUtil.h \
    tracking/CF_tld/CFtld/CFVarianceFilter.h \
    tracking/cf_tracking/src/3rdparty/cv_ext/init_box_selector.hpp \
    tracking/cf_tracking/src/3rdparty/cv_ext/math_spectrums.hpp \
    tracking/cf_tracking/src/3rdparty/cv_ext/psr.hpp \
    tracking/cf_tracking/src/3rdparty/cv_ext/shift.hpp \
    tracking/cf_tracking/src/3rdparty/cv_ext/tracker_run.hpp \
    tracking/cf_tracking/src/3rdparty/piotr/src/sse.hpp \
    tracking/cf_tracking/src/3rdparty/piotr/src/wrappers.hpp \
    tracking/cf_tracking/src/3rdparty/piotr/gradientMex.hpp \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/Arg.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/ArgException.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/ArgTraits.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/CmdLine.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/CmdLineInterface.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/CmdLineOutput.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/Constraint.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/DocBookOutput.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/HelpVisitor.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/IgnoreRestVisitor.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/MultiArg.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/MultiSwitchArg.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/OptionalUnlabeledTracker.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/StandardTraits.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/StdOutput.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/SwitchArg.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/UnlabeledMultiArg.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/UnlabeledValueArg.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/ValueArg.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/ValuesConstraint.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/VersionVisitor.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/Visitor.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/XorHandler.h \
    tracking/cf_tracking/src/3rdparty/tclap/tclap/ZshCompletionOutput.h \
    tracking/cf_tracking/src/cf_libs/common/cf_tracker.hpp \
    tracking/cf_tracking/src/cf_libs/common/cv_ext.hpp \
    tracking/cf_tracking/src/cf_libs/common/feature_channels.hpp \
    tracking/cf_tracking/src/cf_libs/common/mat_consts.hpp \
    tracking/cf_tracking/src/cf_libs/common/math_helper.hpp \
    tracking/cf_tracking/src/cf_libs/common/scale_estimator.hpp \
    tracking/cf_tracking/src/cf_libs/common/tracker_debug.hpp \
    tracking/cf_tracking/src/cf_libs/dsst/dsst_debug.hpp \
    tracking/cf_tracking/src/cf_libs/dsst/dsst_tracker.hpp \
    tracking/cf_tracking/src/cf_libs/kcf/kcf_debug.hpp \
    tracking/cf_tracking/src/cf_libs/kcf/kcf_tracker.hpp \
    tracking/common/tracker_api.h \
    tracking/ObjectTracker/cv_camshift.h \
    tracking/ObjectTracker/cv_cftld.h \
    tracking/ObjectTracker/cv_cmt.h \
    tracking/ObjectTracker/cv_ct.h \
    tracking/ObjectTracker/cv_dsst.h \
    tracking/ObjectTracker/cv_kcf.h \
    tracking/ObjectTracker/cv_mncc.h \
    tracking/ObjectTracker/cv_Mosse.h \
    tracking/ObjectTracker/cv_ncc.h \
    tracking/ObjectTracker/cv_onlineboosting.h \
    tracking/ObjectTracker/cv_onlinemil.h \
    tracking/ObjectTracker/cv_phasecorr.h \
    tracking/ObjectTracker/cv_skcf.h \
    tracking/ObjectTracker/cv_struck.h \
    tracking/ObjectTracker/cv_tld.h \
    tracking/ObjectTracker/cv_tracker_name.h \
    tracking/ObjectTracker/cv_trackerfeatures.h \
    tracking/ObjectTracker/object_tracker.h \
    tracking/OpenStruck/src/GraphUtils/GraphUtils.h \
    tracking/OpenStruck/src/Config.h \
    tracking/OpenStruck/src/Features.h \
    tracking/OpenStruck/src/HaarFeature.h \
    tracking/OpenStruck/src/HaarFeatures.h \
    tracking/OpenStruck/src/HistogramFeatures.h \
    tracking/OpenStruck/src/ImageRep.h \
    tracking/OpenStruck/src/Kernels.h \
    tracking/OpenStruck/src/LaRank.h \
    tracking/OpenStruck/src/MultiFeatures.h \
    tracking/OpenStruck/src/RawFeatures.h \
    tracking/OpenStruck/src/Rect.h \
    tracking/OpenStruck/src/Sample.h \
    tracking/OpenStruck/src/Sampler.h \
    tracking/OpenStruck/src/Tracker.h \
    tracking/OpenStruck/src/vot.hpp \
    tracking/skcf/gradient.h \
    tracking/skcf/ktrackers.h \
    tracking/skcf/skcfdcf.h \
    tracking/skcf/Stracker.h \
    tracking/Threshold_Tracker/alg_Labeling.h \
    tracking/Threshold_Tracker/alg_Stack.h \
    tracking/Threshold_Tracker/Descript.h \
    tracking/Threshold_Tracker/IPLib.h \
    tracking/Threshold_Tracker/KFreqLib.h \
    tracking/Threshold_Tracker/Morphology.h \
    tracking/Threshold_Tracker/Threshold_Tracking.h \
    tracking/Threshold_Tracker/Thresholding.h \
    tracking/cf_tracking/src/cf_libs/dsst/dsst_debug.hpp \
    tracking/cf_tracking/src/cf_libs/dsst/dsst_tracker.hpp \
    Ctracker.h \
    GTL/algorithm.h \
    GTL/bellman_ford.h \
    GTL/bfs.h \
    GTL/biconnectivity.h \
    GTL/bid_dijkstra.h \
    GTL/bin_heap.h \
    GTL/components.h \
    GTL/debug.h \
    GTL/dfs.h \
    GTL/dijkstra.h \
    GTL/edge.h \
    GTL/edge_data.h \
    GTL/edge_map.h \
    GTL/embedding.h \
    GTL/fm_partition.h \
    GTL/gml_parser.h \
    GTL/gml_scanner.h \
    GTL/graph.h \
    GTL/GTL.h \
    GTL/maxflow_ff.h \
    GTL/maxflow_pp.h \
    GTL/maxflow_sap.h \
    GTL/min_tree.h \
    GTL/ne_map.h \
    GTL/node.h \
    GTL/node_data.h \
    GTL/node_map.h \
    GTL/planarity.h \
    GTL/pq_node.h \
    GTL/pq_tree.h \
    GTL/ratio_cut_partition.h \
    GTL/st_number.h \
    GTL/symlist.h \
    GTL/topsort.h \
    GTL/version.h \
    tracking/common/MyTimer.h \
    BlobTracking.h \
    cvblob/cvblob.h \
    Systems-Serial-Headers.h \
    MapWidget.h \
    MapWidget_TestWindow.h \
    UAS_types.h \
    ../../opmapcontrol_ex/mapwidget/gpsitem.h \
    ../../opmapcontrol_ex/mapwidget/homeitem.h \
    ../../opmapcontrol_ex/mapwidget/mapgraphicitem.h \
#    ../../opmapcontrol_ex/mapwidget/mapripform.h \
#    ../../opmapcontrol_ex/mapwidget/mapripper.h \
    ../../opmapcontrol_ex/mapwidget/omapconfiguration.h \
    ../../opmapcontrol_ex/mapwidget/opmapwidget.h \
    ../../opmapcontrol_ex/mapwidget/trailitem.h \
    ../../opmapcontrol_ex/mapwidget/traillineitem.h \
    ../../opmapcontrol_ex/mapwidget/uavitem.h \
    ../../opmapcontrol_ex/mapwidget/uavmapfollowtype.h \
    ../../opmapcontrol_ex/mapwidget/uavtrailtype.h \
    ../../opmapcontrol_ex/mapwidget/waypointitem.h \
    ../../opmapcontrol_ex/mapwidget/waypointlineitem.h \
    ../../my_tracking_2015/src/artillery_TCP/MySharedData.h


SOURCES += \
    axis_data.cpp \
    BackgroundSubtract.cpp \
    capturethread.cpp \
    Ctracker.cpp \
    Detector.cpp \
    HungarianAlg.cpp \
    Kalman.cpp \
    LocalTracker.cpp \
    main.cpp \
    mainwindow.cpp \
    mwbmatching.cpp \
    mygraph.cpp \
#    MySharedData.cpp \
    qt_utils.cpp \
    sarab_osdfuncs.cpp \
    setting.cpp \
    tokenise.cpp \
    vibeBG.cpp \
    fheap.c \
    package_analysis/ForegroundMaskAnalysis.cpp \
    package_analysis/PerformanceUtils.cpp \
    package_analysis/PixelUtils.cpp \
#    package_bgs/_template_/Amber.cpp \
    package_bgs/_template_/MyBGS.cpp \
    package_bgs/dp/AdaptiveMedianBGS.cpp \
    package_bgs/dp/Eigenbackground.cpp \
    package_bgs/dp/Error.cpp \
    package_bgs/dp/GrimsonGMM.cpp \
    package_bgs/dp/Image.cpp \
    package_bgs/dp/MeanBGS.cpp \
    package_bgs/dp/PratiMediodBGS.cpp \
    package_bgs/dp/TextureBGS.cpp \
    package_bgs/dp/WrenGA.cpp \
    package_bgs/dp/ZivkovicAGMM.cpp \
    package_bgs/IMBS/IMBS.cpp \
    package_bgs/KDE/KernelTable.cpp \
    package_bgs/KDE/NPBGmodel.cpp \
    package_bgs/KDE/NPBGSubtractor.cpp \
    package_bgs/lb/BGModel.cpp \
    package_bgs/lb/BGModelFuzzyGauss.cpp \
    package_bgs/lb/BGModelFuzzySom.cpp \
    package_bgs/lb/BGModelGauss.cpp \
    package_bgs/lb/BGModelMog.cpp \
    package_bgs/lb/BGModelSom.cpp \
    package_bgs/LBP_MRF/graphh.cpp \
    package_bgs/LBP_MRF/maxflow.cpp \
    package_bgs/LBP_MRF/MEDefs.cpp \
    package_bgs/LBP_MRF/MEHistogram.cpp \
    package_bgs/LBP_MRF/MEImage.cpp \
    package_bgs/LBP_MRF/MotionDetection.cpp \
    package_bgs/LBSP/BackgroundSubtractorLBSP.cpp \
    package_bgs/LBSP/BackgroundSubtractorLBSP_.cpp \
    package_bgs/LBSP/BackgroundSubtractorLOBSTER.cpp \
    package_bgs/LBSP/BackgroundSubtractorPAWCS.cpp \
    package_bgs/LBSP/BackgroundSubtractorSuBSENSE.cpp \
    package_bgs/LBSP/LBSP.cpp \
    package_bgs/LBSP/LBSP_.cpp \
    package_bgs/MultiLayer/blob.cpp \
    package_bgs/MultiLayer/BlobExtraction.cpp \
    package_bgs/MultiLayer/BlobResult.cpp \
    package_bgs/MultiLayer/CMultiLayerBGS.cpp \
    package_bgs/MultiLayer/LocalBinaryPattern.cpp \
    package_bgs/PBAS/PBAS.cpp \
    package_bgs/SigmaDelta/sdLaMa091.cpp \
    package_bgs/T2F/FuzzyUtils.cpp \
    package_bgs/T2F/MRF.cpp \
    package_bgs/T2F/T2FGMM.cpp \
    package_bgs/T2F/T2FMRF.cpp \
    package_bgs/TwoPoints/two_points.cpp \
    package_bgs/ViBe/vibe-background-sequential.cpp \
    package_bgs/VuMeter/TBackground.cpp \
    package_bgs/VuMeter/TBackgroundVuMeter.cpp \
    package_bgs/AdaptiveBackgroundLearning.cpp \
    package_bgs/AdaptiveSelectiveBackgroundLearning.cpp \
    package_bgs/CodeBook.cpp \
    package_bgs/DPAdaptiveMedian.cpp \
    package_bgs/DPEigenbackground.cpp \
    package_bgs/DPGrimsonGMM.cpp \
    package_bgs/DPMean.cpp \
    package_bgs/DPPratiMediod.cpp \
    package_bgs/DPTexture.cpp \
    package_bgs/DPWrenGA.cpp \
    package_bgs/DPZivkovicAGMM.cpp \
    package_bgs/FrameDifference.cpp \
    package_bgs/FuzzyChoquetIntegral.cpp \
    package_bgs/FuzzySugenoIntegral.cpp \
    package_bgs/GMG.cpp \
    package_bgs/IndependentMultimodal.cpp \
    package_bgs/KDE.cpp \
    package_bgs/KNN.cpp \
    package_bgs/LBAdaptiveSOM.cpp \
    package_bgs/LBFuzzyAdaptiveSOM.cpp \
    package_bgs/LBFuzzyGaussian.cpp \
    package_bgs/LBMixtureOfGaussians.cpp \
    package_bgs/LBP_MRF.cpp \
    package_bgs/LBSimpleGaussian.cpp \
    package_bgs/LOBSTER.cpp \
    package_bgs/MixtureOfGaussianV1.cpp \
    package_bgs/MixtureOfGaussianV2.cpp \
    package_bgs/MultiCue.cpp \
    package_bgs/MultiLayer.cpp \
    package_bgs/PAWCS.cpp \
    package_bgs/PixelBasedAdaptiveSegmenter.cpp \
    package_bgs/SigmaDelta.cpp \
    package_bgs/StaticFrameDifference.cpp \
    package_bgs/SuBSENSE.cpp \
    package_bgs/T2FGMM_UM.cpp \
    package_bgs/T2FGMM_UV.cpp \
    package_bgs/T2FMRF_UM.cpp \
    package_bgs/T2FMRF_UV.cpp \
    package_bgs/TwoPoints.cpp \
    package_bgs/ViBe.cpp \
    package_bgs/VuMeter.cpp \
    package_bgs/WeightedMovingMean.cpp \
    package_bgs/WeightedMovingVariance.cpp \
    tracking/CF_tld/CFtld/CFClustering.cpp \
    tracking/CF_tld/CFtld/CFDetectionResult.cpp \
    tracking/CF_tld/CFtld/CFDetectorCascade.cpp \
    tracking/CF_tld/CFtld/CFEnsembleClassifier.cpp \
    tracking/CF_tld/CFtld/CFNNClassifier.cpp \
    tracking/CF_tld/CFtld/CFTLD.cpp \
    tracking/CF_tld/CFtld/CFTLDUtil.cpp \
    tracking/CF_tld/CFtld/CFVarianceFilter.cpp \
    tracking/cf_tracking/src/3rdparty/cv_ext/init_box_selector.cpp \
    tracking/cf_tracking/src/3rdparty/cv_ext/math_spectrums.cpp \
    tracking/cf_tracking/src/3rdparty/cv_ext/shift.cpp \
    tracking/cf_tracking/src/3rdparty/cv_ext/tracker_run.cpp \
    tracking/cf_tracking/src/3rdparty/piotr/src/gradientMex.cpp \
    tracking/cf_tracking/src/cf_libs/common/math_helper.cpp \
    tracking/common/tracker_api.cpp \
    tracking/ObjectTracker/cv_camshift.cpp \
    tracking/ObjectTracker/cv_cftld.cpp \
    tracking/ObjectTracker/cv_cmt.cpp \
    tracking/ObjectTracker/cv_ct.cpp \
    tracking/ObjectTracker/cv_mncc.cpp \
    tracking/ObjectTracker/cv_Mosse.cpp \
    tracking/ObjectTracker/cv_ncc.cpp \
    tracking/ObjectTracker/cv_onlineboosting.cpp \
    tracking/ObjectTracker/cv_onlinemil.cpp \
    tracking/ObjectTracker/cv_phasecorr.cpp \
    tracking/ObjectTracker/cv_struck.cpp \
    tracking/ObjectTracker/cv_tld.cpp \
    tracking/ObjectTracker/cv_tracker_name.cpp \
    tracking/ObjectTracker/cv_trackerfeatures.cpp \
    tracking/ObjectTracker/object_tracker.cpp \
    tracking/OpenStruck/src/GraphUtils/GraphUtils.cpp \
    tracking/OpenStruck/src/Config.cpp \
    tracking/OpenStruck/src/Features.cpp \
    tracking/OpenStruck/src/HaarFeature.cpp \
    tracking/OpenStruck/src/HaarFeatures.cpp \
    tracking/OpenStruck/src/HistogramFeatures.cpp \
    tracking/OpenStruck/src/ImageRep.cpp \
    tracking/OpenStruck/src/LaRank.cpp \
    tracking/OpenStruck/src/MultiFeatures.cpp \
    tracking/OpenStruck/src/RawFeatures.cpp \
    tracking/OpenStruck/src/Sampler.cpp \
    tracking/OpenStruck/src/Tracker.cpp \
    tracking/skcf/gradient.cpp \
    tracking/skcf/ktrackers.cpp \
    tracking/skcf/skcfdcf.cpp \
    tracking/Threshold_Tracker/alg_Labeling.cpp \
    tracking/Threshold_Tracker/alg_Stack.cpp \
    tracking/Threshold_Tracker/Descript.cpp \
    tracking/Threshold_Tracker/IPLib.cpp \
    tracking/Threshold_Tracker/KFreqLib.cpp \
    tracking/Threshold_Tracker/Morphology.cpp \
    tracking/Threshold_Tracker/Thresholding.cpp \
#    package_bgs/_template_/amber/amber.c \
    tracking/OpenCMT/getopt/getopt.c \
    GTL/bellman_ford.cpp \
    GTL/bfs.cpp \
    GTL/biconnectivity.cpp \
    GTL/bid_dijkstra.cpp \
    GTL/components.cpp \
    GTL/debug.cpp \
    GTL/dfs.cpp \
    GTL/dijkstra.cpp \
    GTL/edge.cpp \
    GTL/embedding.cpp \
    GTL/fm_partition.cpp \
    GTL/gml_parser.cpp \
    GTL/gml_scanner.cpp \
    GTL/graph.cpp \
    GTL/maxflow_ff.cpp \
    GTL/maxflow_pp.cpp \
    GTL/maxflow_sap.cpp \
    GTL/min_tree.cpp \
    GTL/node.cpp \
    GTL/planarity.cpp \
    GTL/pq_node.cpp \
    GTL/pq_tree.cpp \
    GTL/ratio_cut_partition.cpp \
    GTL/st_number.cpp \
    GTL/topsort.cpp \
    tracking/common/MyTimer.cpp \
    BlobTracking.cpp \
    cvblob/cvaux.cpp \
    cvblob/cvblob.cpp \
    cvblob/cvcolor.cpp \
    cvblob/cvcontour.cpp \
    cvblob/cvlabel.cpp \
    cvblob/cvtrack.cpp \
    MapWidget.cpp \
    MapWidget_TestWindow.cpp \
    UAS_types.cpp \
    ../../opmapcontrol_ex/mapwidget/configuration.cpp \
    ../../opmapcontrol_ex/mapwidget/gpsitem.cpp \
    ../../opmapcontrol_ex/mapwidget/homeitem.cpp \
    ../../opmapcontrol_ex/mapwidget/mapgraphicitem.cpp \
#    ../../opmapcontrol_ex/mapwidget/mapripform.cpp \
#    ../../opmapcontrol_ex/mapwidget/mapripper.cpp \
    ../../opmapcontrol_ex/mapwidget/opmapwidget.cpp \
    ../../opmapcontrol_ex/mapwidget/trailitem.cpp \
    ../../opmapcontrol_ex/mapwidget/traillineitem.cpp \
    ../../opmapcontrol_ex/mapwidget/uavitem.cpp \
    ../../opmapcontrol_ex/mapwidget/waypointitem.cpp \
    ../../opmapcontrol_ex/mapwidget/waypointlineitem.cpp \
    ../../my_tracking_2015/src/artillery_TCP/MySharedData.cpp
################################################################################
# opmapcontrol
################################################################################
OPMAPCONTROL_DIR = E:\\WORK\\opmapcontrol_ex

INCLUDEPATH +=  $$OPMAPCONTROL_DIR \
                $$OPMAPCONTROL_DIR/core \
                $$OPMAPCONTROL_DIR/internals \
#                $$OPMAPCONTROL_DIR/mapwidget
#LIBS += D:\\opmapcontrol_ex\\libopmapwidget.lib
LIBS += E:\\WORK\\opmapcontrol_ex\\libopmapwidget.a#opmapwidget.lib
RESOURCES   += $$OPMAPCONTROL_DIR/mapwidget/mapresources.qrc
LIBS += E:\\WORK\\opmapcontrol_ex\\libopmapwidget.a#opmapwidget.lib
RESOURCES   += $$OPMAPCONTROL_DIR/mapwidget/mapresources.qrc

FORMS    += mainwindow.ui \
            Setting.ui

