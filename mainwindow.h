#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "opencv2/video/video.hpp"
#include "qt_compiler.h"
#include "../../my_tracking_2015/src/artillery_TCP/MySharedData.h"
//#include "newSerialHeaders.h"
#include "Systems-Serial-Headers.h"
#include "setting.h"
#include "axis_data.h"
//#include "optoload_constants.h"
#include <QMessageBox>
#include <QByteArray>
#include <QtCore>
#include <QPainter>
#include "qmath.h"
#include "capturethread.h"
#include <QKeyEvent>
#include <qmessagebox.h>
#include <qcombobox.h>
#include <QTcpSocket>
#include <QTcpServer>
#include <sarab_osdfuncs.h>
#include <QStringList>
#include <QStringListModel>
#include <QCollator>
#include "qt_utils.h"
#include "package_bgs/bgslibrary.h"
#include "BackgroundSubtract.h"
#include "Detector.h"
#include "Ctracker.h"
#include <MyTimer.h>
#include <tracker_api.h>
#include "BlobTracking.h"
#include "MapWidget_TestWindow.h"
#include <limits>

namespace bgslibrary
{
  template<typename T> IBGS * createInstance() { return new T; }
  typedef std::map<std::string, IBGS*(*)()> map_ibgs;

  IBGS* get_alg(std::string alg_name);
  QStringList get_algs_name();
}

namespace Trackerlibrary
{
    static int Algonumber[10] = { 18, 19, 20, 8,17,13,14,1,7,16 };
    tracker_api get_alg(int alg_num);
    QStringList get_algs_name();
}


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTimer* tmr;

    cv::Mat frameorig;
    cv::Mat frame;

    MySharedData *MyData;
    map_shared_data data1;

    bool full=false;
    Setting *settings;
    bool is_set=false;
    Axis_Data *panAxis, *tiltAxis;

    double laser_distance;
    double tilt_old_x=0;
    double tilt_old_y=0;
    double tilt_old_x1=0;
    double tilt_old_y1=0;

    double start_phase_pan;
    double scan_phase_pan;
    double scan_time_pan;
    double scan_tilt_pan;

    double start_phase_tilt;
    double scan_phase_tilt;
    double scan_time_tilt;
    double scan_pan_tilt;

    uint16_t Zoom_Value;
    int Zoom_ind=0;
    bool scanning_pan=false;
    bool scanning_tilt=false;
    bool start_scan=false;

    bool pan_dir=false;
    bool tilt_dir=false;

    QString encoder_data_pan;
    QString encoder_data_tilt;

    QString encoder_data_lat;
    QString encoder_data_lon;

    CaptureThread* CpThread;

    bool Camera_open=false;
    bool IPCamera_open=false;

    DrawingSeaProjectsStruct Drawings;
    OSDT *myosd;

    bool Serial_open=false;

    bool TCP_open=false;
    QTcpSocket *socket;
    bool TCP_track=false;
    bool winup=false;
    bool windn=false;
    bool algo=false;

    bool Enhancment=false;
    cv::Mat darkChannel;
    cv::Mat T;
    int Airlightp;          //airlight value of previous frame
    int Airlight;           //airlight value of current frame
    cv::Mat fogfree;
    int ad;
    bool first_enhacment=false;

    bool Motion=false;
    IBGS *bgs;
    double duration = 0;
    bool blob_tracking=false;
    BlobTracking* blobT;

    cv::Rect* SelectedRect;
    cv::Rect init_Rect;
    bool useLocalTracking = true;
    CDetector* detector;
    CTracker* fix_tracker;
    int fps=0;
    bool detect=false;

    tracker_api statictracker;
    bool track=false;
    bool init_track=false;
    cv::Rect* Selected;
    int initWinWidth=64;
    cv::Point ScreenCursor;
    MyTimer *timer2=new MyTimer();
    cv::Scalar TarColor;
    cv::Scalar TrackOK=cv::Scalar (0,255,255);
    cv::Scalar TrackNotOK=cv::Scalar (0,0,193);
    double focal_length;
    double tetex=0.96,tetay=0.75;
    float conf;

    cv::VideoWriter* video_rec;
    cv::VideoWriter* video_rec1;
    bool record=false;
    //Map
    QTestWin* map;
    char* buffer1={0};
    bool laser_shoot=false;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent *event);

public slots:
    void mainscenario(cv::Mat src);
    void startread();
    void Write(uint8_t cmd, uint8_t *data);
    void Write(uint8_t cmd);
    void Write(uint8_t cmd, int32_t data);
    void Write(uint8_t cmd, uint32_t data);
    void Write(uint8_t cmd, float32_t data);
    void Write(uint8_t cmd, uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3);
    //Motion

    QString getSelectedAlgorithmName();
    void createBGS();
    void destroyBGS();
    QImage cv2qimage(const cv::Mat &cv_frame);
    void processFrame(const cv::Mat &cv_frame);
    void tic();
    void toc();

    //MAP
    void done();
    void gotoloc(double);

private slots:
    void on_Config_clicked();
    void on_ctrl_right_pushButton_2_pressed();
    void on_ctrl_right_pushButton_2_released();
    void on_ctrl_right_pushButton_pressed();
    void on_ctrl_right_pushButton_released();
    void on_ctrl_left_pushButton_pressed();
    void on_ctrl_left_pushButton_released();
    void on_ctrl_left_pushButton_2_pressed();
    void on_ctrl_left_pushButton_2_released();
    void on_DayCamera_clicked();
    void on_NightCamera_clicked();
    void on_pan_positionRef_lineEdit_returnPressed();
    void on_ctrl_up_pushButton_2_pressed();
    void on_ctrl_up_pushButton_2_released();
    void on_ctrl_up_pushButton_pressed();
    void on_ctrl_up_pushButton_released();
    void on_ctrl_down_pushButton_pressed();
    void on_ctrl_down_pushButton_released();
    void on_ctrl_down_pushButton_2_pressed();
    void on_ctrl_down_pushButton_2_released();
    void on_tilt_positionRef_lineEdit_returnPressed();
    void Popup(const QPoint& pt,int type);
    void on_AutoScanning_clicked();
    void on_pan_positionRef_lineEdit_editingFinished();
    void on_tilt_positionRef_lineEdit_editingFinished();
    void on_ScanPan_clicked();
    void on_PanStart_editingFinished();
    void on_SectorValue_editingFinished();
    void on_SectorValue_2_editingFinished();
    void on_TiltStart_editingFinished();
    void on_load_focus_increase_pushButton_pressed();
    void on_load_focus_increase_pushButton_released();
    void on_load_focus_decrease_pushButton_pressed();
    void on_load_focus_decrease_pushButton_released();
    void on_load_contrast_increase_pushButton_pressed();
    void on_load_contrast_increase_pushButton_released();
    void on_load_contrast_decrease_pushButton_pressed();
    void on_load_contrast_decrease_pushButton_released();
    void on_load_brightness_increase_pushButton_pressed();
    void on_load_brightness_increase_pushButton_released();
    void on_load_brightness_decrease_pushButton_pressed();
    void on_load_brightness_decrease_pushButton_released();
    void on_load_polarity_white_pushButton_pressed();
    void on_load_polarity_white_pushButton_released();
    void on_load_polarity_black_pushButton_pressed();
    void on_load_polarity_black_pushButton_released();
    void on_load_autoMode_off_pushButton_pressed();
    void on_load_autoMode_off_pushButton_released();
    void on_load_autoMode_on_pushButton_pressed();
    void on_load_autoMode_on_pushButton_released();
    void on_load_focusMode_manual_pushButton_pressed();
    void on_load_focusMode_manual_pushButton_released();
    void on_load_focusMode_auto_pushButton_pressed();
    void on_load_focusMode_auto_pushButton_released();
    void on_load_focusMode_combine_pushButton_pressed();
    void on_load_focusMode_combine_pushButton_released();
    void on_load_laser_shoot_pushButton_pressed();
    void on_load_laser_shoot_pushButton_released();
    void on_load_calibration_pushButton_pressed();
    void on_load_calibration_pushButton_released();
    void on_ScanTilt_clicked();
    void on_TiltValue_editingFinished();
    void on_ScanTimeValue_editingFinished();
    void on_FullScreen_clicked();
    void on_PanValue_editingFinished();
    void on_ScanTimeValue_2_editingFinished();
    void on_load_zoom_increase_pushButton_clicked();
    void on_load_zoom_decrease_pushButton_clicked();
    void on_LocalControl_clicked(bool checked);
    void on_RunCamera_clicked();
    void on_RunSerial_clicked();
    void on_ConnectTCP_clicked();
    void on_RunIPCamera_clicked();
    void on_RecordVideo_clicked();
    void on_Enhancment_clicked();
    void on_Enh_Box_currentIndexChanged(int index);
    void on_Motion_clicked();
    void on_detect_clicked();
    void on_Track_clicked();
    void on_check_track_clicked(bool checked);
    void on_change_algo_clicked();
    void on_track_blob_clicked(bool checked);
    void on_Windo_p_pressed();
    void on_Windo_p_released();
    void on_Windo_m_pressed();
    void on_Windo_m_released();
    void on_CameraIndex_returnPressed();
};

#endif // MAINWINDOW_H
