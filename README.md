# QT-artillery 5.9.4

A legacy C++ / Qt desktop application with an Arabic interface for camera video,
image processing, visual tracking, and mapping. The project also includes
hardware-specific interfaces for pan/tilt equipment and optical devices.

The repository contains application source, bundled computer-vision libraries,
precompiled tracking libraries, and files from the original Windows development
environment. Some external components are missing, so this checkout does not
contain everything required to reproduce the original application.

## Application components

- Camera capture through OpenCV and IP-camera streams through LibVLC.
- Video display, recording, and on-screen overlays.
- Image enhancement and foreground extraction with background-subtraction
  algorithms.
- Blob detection, visual object tracking, and multi-object track association.
- A map interface based on the external OPMapControl library.
- Settings, network communication, and hardware-specific interfaces.

## Source layout

| Path | Contents |
| --- | --- |
| [artillery.pro](artillery.pro) | qmake application project, source lists, and dependency paths |
| [main.cpp](main.cpp) | Qt application entry point |
| [mainwindow.cpp](mainwindow.cpp), [mainwindow.h](mainwindow.h), [mainwindow.ui](mainwindow.ui) | Main interface, image-processing coordination, and application integrations |
| [capturethread.cpp](capturethread.cpp), [capturethread.h](capturethread.h) | OpenCV and LibVLC capture code, with frames delivered through Qt signals |
| [setting.cpp](setting.cpp), [Setting.ui](Setting.ui) | Settings window and persistence code |
| [BackgroundSubtract.cpp](BackgroundSubtract.cpp), [Detector.cpp](Detector.cpp), [BlobTracking.cpp](BlobTracking.cpp) | Foreground extraction, region detection, and blob processing |
| [Ctracker.cpp](Ctracker.cpp), [Kalman.cpp](Kalman.cpp), [HungarianAlg.cpp](HungarianAlg.cpp) | Multi-object tracking, state estimation, and assignment code |
| [sarab_osdfuncs.cpp](sarab_osdfuncs.cpp) | On-screen drawing and overlays |
| [MapWidget.cpp](MapWidget.cpp), [MapWidget_TestWindow.cpp](MapWidget_TestWindow.cpp) | Map widgets and their application wrapper |
| [package_bgs/](package_bgs/), [package_analysis/](package_analysis/) | Background-subtraction implementations and analysis utilities |
| [tracking/](tracking/) | Tracker implementations, adapters, and bundled dependencies |
| [Tracking_lib/](Tracking_lib/) | Precompiled static tracking libraries |
| [cvblob/](cvblob/), [GTL/](GTL/) | Blob-processing and graph-library source |

Most application coordination is in `MainWindow`. Video capture is implemented in
`CaptureThread`; tracking and background subtraction have separate classes and
bundled libraries. The map widgets depend on code outside this repository.

## Original build environment

The following information comes from `artillery.pro` and the committed makefiles
and describes the original build configuration.

| Component | Configuration recorded in the project |
| --- | --- |
| Platform | Windows, 32-bit MinGW build |
| Qt | Qt 5.9.4; Core, GUI, Widgets, OpenGL, SQL, SVG, and Network modules |
| Build system | qmake; application target named `artillery` |
| Compiler | MinGW 5.3 kit; C++14 enabled |
| OpenCV | 3.2.0 libraries built for 32-bit MinGW |
| LibVLC | Headers and runtime libraries referenced through a VLC-Qt 1.1.0 Windows bundle |
| Boost | 1.59; System, Thread, Date Time, and Chrono libraries |
| Mapping | External OPMapControl source, library, and Qt resources |
| Tracking | Bundled source and static libraries for several tracker implementations |

The tracking directories include CMT, KCF, DSST, TLD-related implementations,
Struck, and other adapters.

## Repository state

The source snapshot retains several dependencies on the original development
machine:

- Absolute Windows paths appear throughout the qmake project.
- Shared-data source files, the serial helper executable, and the OPMapControl
  library and resources are referenced but are not included.
- `Tracking_lib/` contains precompiled archives associated with the original
  toolchain.
- Generated makefiles, generated UI headers, and Qt Creator user settings are
  committed alongside the source.

No build, runtime, or hardware tests were performed for this documentation update.
Compatibility with newer Qt or OpenCV versions, 64-bit builds, and non-Windows
systems has not been established.

The qmake application project does not declare an application-level automated
test target. Some bundled third-party directories contain their own examples and
tests; those are separate from validation of this application.

## Third-party code and licenses

The repository includes third-party implementations and their existing notices.
Documentation and license files are present in several component directories:

- [CMT documentation](tracking/OpenCMT/README.md) and [license](tracking/OpenCMT/LICENSE).
- [Struck documentation](tracking/OpenStruck/README.md) and [license](tracking/OpenStruck/LICENSE.txt).
- [ViBe license](package_bgs/ViBe/LICENSE).
- [BGSLibrary source notice](package_bgs/bgslibrary.h).

There is currently no top-level license file for the application as a whole.
