#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QDebug>
#include <bitset>

#define SONY_ZOOM_STEP_VALUE	    0x0100
#define SONY_FOCUS_STEP_VALUE       0x0100
#define SONY_BRIGHTNESS_STEP_VALUE  0x0001
#define SONY_CONTRAST_STEP_VALUE    0x0001
#define SONY_BRIGHTNESS_MAX_VALUE   32
#define SONY_CONTRAST_MAX_VALUE     32
#define IR_BRIGHTNESS_MAX_VALUE   128
#define IR_CONTRAST_MAX_VALUE     128
#define VoltMax 24.0

bool startup=false;
bool max_tilt=false;

QString h_lat;
QString h_lon;
float32_t pan_speed;
float32_t tilt_speed;
float32_t pan_sccan;
#define in_range(value, center, radius) ((value >= (center - radius)) && (value <= (center + radius)))
cv::Scalar Colors[] = { cv::Scalar(255, 0, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 0, 255), cv::Scalar(255, 255, 0),
                        cv::Scalar(0, 255, 255), cv::Scalar(255, 0, 255), cv::Scalar(255, 127, 255), cv::Scalar(127, 0, 255),
                        cv::Scalar(127, 0, 127) };

namespace bgslibrary
{

  IBGS* get_alg(std::string alg_name) {
    map_ibgs map;
    map["FrameDifference"] = &createInstance<FrameDifference>;
    map["StaticFrameDifference"] = &createInstance<StaticFrameDifference>;
    map["WeightedMovingMean"] = &createInstance<WeightedMovingMean>;
    map["WeightedMovingVariance"] = &createInstance<WeightedMovingVariance>;
#if CV_MAJOR_VERSION == 2
    map["MixtureOfGaussianV1"] = &createInstance<MixtureOfGaussianV1>; // only for OpenCV 2.x
#endif
    map["MixtureOfGaussianV2"] = &createInstance<MixtureOfGaussianV2>;
    map["AdaptiveBackgroundLearning"] = &createInstance<AdaptiveBackgroundLearning>;
    map["AdaptiveSelectiveBackgroundLearning"] = &createInstance<AdaptiveSelectiveBackgroundLearning>;
#if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION >= 4 && CV_SUBMINOR_VERSION >= 3
    map["GMG"] = &createInstance<GMG>; // only for OpenCV >= 2.4.3
#endif
#if CV_MAJOR_VERSION == 3
    map["KNN"] = &createInstance<KNN>; // only on OpenCV 3.x
#endif
    map["DPAdaptiveMedian"] = &createInstance<DPAdaptiveMedian>;
    map["DPGrimsonGMM"] = &createInstance<DPGrimsonGMM>;
    map["DPZivkovicAGMM"] = &createInstance<DPZivkovicAGMM>;
    map["DPMean"] = &createInstance<DPMean>;
    map["DPWrenGA"] = &createInstance<DPWrenGA>;
    map["DPPratiMediod"] = &createInstance<DPPratiMediod>;
    map["DPEigenbackground"] = &createInstance<DPEigenbackground>;
    map["DPTexture"] = &createInstance<DPTexture>;
    map["T2FGMM_UM"] = &createInstance<T2FGMM_UM>;
    map["T2FGMM_UV"] = &createInstance<T2FGMM_UV>;
    map["T2FMRF_UM"] = &createInstance<T2FMRF_UM>;
    map["T2FMRF_UV"] = &createInstance<T2FMRF_UV>;
    map["FuzzySugenoIntegral"] = &createInstance<FuzzySugenoIntegral>;
    map["FuzzyChoquetIntegral"] = &createInstance<FuzzyChoquetIntegral>;
    map["MultiLayer"] = &createInstance<MultiLayer>;
    map["PixelBasedAdaptiveSegmenter"] = &createInstance<PixelBasedAdaptiveSegmenter>;
    map["LBSimpleGaussian"] = &createInstance<LBSimpleGaussian>;
    map["LBFuzzyGaussian"] = &createInstance<LBFuzzyGaussian>;
    map["LBMixtureOfGaussians"] = &createInstance<LBMixtureOfGaussians>;
    map["LBAdaptiveSOM"] = &createInstance<LBAdaptiveSOM>;
    map["LBFuzzyAdaptiveSOM"] = &createInstance<LBFuzzyAdaptiveSOM>;
    map["LBP_MRF"] = &createInstance<LBP_MRF>;
    map["VuMeter"] = &createInstance<VuMeter>;
    map["KDE"] = &createInstance<KDE>;
    map["IndependentMultimodal"] = &createInstance<IndependentMultimodal>;
    map["MultiCue"] = &createInstance<MultiCue>;
    map["SigmaDelta"] = &createInstance<SigmaDelta>;
    map["SuBSENSE"] = &createInstance<SuBSENSE>;
    map["LOBSTER"] = &createInstance<LOBSTER>;
    map["PAWCS"] = &createInstance<PAWCS>;
    map["TwoPoints"] = &createInstance<TwoPoints>;
    map["ViBe"] = &createInstance<ViBe>;
    map["CodeBook"] = &createInstance<CodeBook>;
    return map[alg_name]();
  }

  QStringList get_algs_name()
  {
    QStringList stringList;
    stringList.append("FrameDifference");
    stringList.append("StaticFrameDifference");
    stringList.append("WeightedMovingMean");
    stringList.append("WeightedMovingVariance");
#if CV_MAJOR_VERSION == 2
    stringList.append("MixtureOfGaussianV1"); // only for OpenCV 2.x
#endif
    stringList.append("MixtureOfGaussianV2");
    stringList.append("AdaptiveBackgroundLearning");
    stringList.append("AdaptiveSelectiveBackgroundLearning");
#if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION >= 4 && CV_SUBMINOR_VERSION >= 3
    stringList.append("GMG"); // only for OpenCV >= 2.4.3
#endif
#if CV_MAJOR_VERSION == 3
    stringList.append("KNN"); // only on OpenCV 3.x
#endif
    stringList.append("DPAdaptiveMedian");
    stringList.append("DPGrimsonGMM");
    stringList.append("DPZivkovicAGMM");
    stringList.append("DPMean");
    stringList.append("DPWrenGA");
    stringList.append("DPPratiMediod");
    stringList.append("DPEigenbackground");
    stringList.append("DPTexture");
    stringList.append("T2FGMM_UM");
    stringList.append("T2FGMM_UV");
    stringList.append("T2FMRF_UM");
    stringList.append("T2FMRF_UV");
    stringList.append("FuzzySugenoIntegral");
    stringList.append("FuzzyChoquetIntegral");
    stringList.append("MultiLayer");
    stringList.append("PixelBasedAdaptiveSegmenter");
    stringList.append("LBSimpleGaussian");
    stringList.append("LBFuzzyGaussian");
    stringList.append("LBMixtureOfGaussians");
    stringList.append("LBAdaptiveSOM");
    stringList.append("LBFuzzyAdaptiveSOM");
    stringList.append("LBP_MRF");
    stringList.append("VuMeter");
    stringList.append("KDE");
    stringList.append("IndependentMultimodal");
    stringList.append("MultiCue");
    stringList.append("SigmaDelta");
    stringList.append("SuBSENSE");
    stringList.append("LOBSTER");
    stringList.append("PAWCS");
    stringList.append("TwoPoints");
    stringList.append("ViBe");
    stringList.append("CodeBook");
    return stringList;
  }
}

namespace Trackerlibrary
{
    tracker_api get_alg(int number)
    {
    tracker_api Tracker1;
    Tracker1.setTrackerAlgorithm(number);
    Tracker1.CreateTracker(number);
    return Tracker1;
  }

  QStringList get_algs_name()
  {
    QStringList stringList;
    stringList.append("Threshold auto");
    stringList.append("Threshold black");
    stringList.append("Threshold white");
    stringList.append("TLD");
    stringList.append("Mosse");
    stringList.append("DSST");
    stringList.append("CFTLD");
    stringList.append("BOOST");
    stringList.append("NCC");
    stringList.append("SKCF");

    return stringList;
  }
}

void info_extract(cv::Mat& src1,DrawingSeaProjectsStruct& Draw)
{
    std::vector<int> im_inf[7];
        std::string im_inf_ch = "";
        int ww = src1.cols;

        for (int i = 5; i < 12; i++)
        {
            int sum_add = 0;
            int indexx = 50;
            for (int ll = 0; ll < 60; ll++)
            {
                cv::Vec3b color = src1.at<cv::Vec3b>(i, ll);
                if (color[0]>245 && color[1]>245 && color[2]>245)
                    sum_add += 1;
                if (ll % 20 == 0)
                {
                    if (sum_add > 18)
                    {
                        indexx = ll;
                        break;
                    }
                    else
                        sum_add = 0;
                }
            }
            for (int j = indexx; j <indexx + 672; j += 7)
            {
                cv::Vec3b color;
                //            Vec3b color1;
                if (ww == 576)
                    color = src1.at<cv::Vec3b>(j + 3, i);
                else
                    color = src1.at<cv::Vec3b>(i, j + 3);
                //cout << im_inf_ch[j] << endl;
                //            color = (color + color1) / 2;
                if (color[0]>190 && color[1]>190 && color[2]>190)
                    im_inf[i - 5].push_back(1);
                else
                    im_inf[i - 5].push_back(0);
            }
        }
        for (int i = 0; i<96; i++)
        {
            //        double op = (double)(im_inf[0].at(i) + im_inf[1].at(i) + im_inf[2].at(i)+im_inf[3].at(i)
            //                      + im_inf[4].at(i)) / 5;
            //        if (op>0.5)
            //            im_inf[0].at(i) = 1;
            //        else
            //            im_inf[0].at(i) = 0;
            im_inf_ch += (std::to_string(im_inf[3].at(i)));
        }
        Draw.P = (double)std::stoi(im_inf_ch.substr(0, 11), nullptr, 2) * 2;
        Draw.T = (double)std::stoi(im_inf_ch.substr(12, 5), nullptr, 2) * 100;
        Draw.zoom = std::stoi(im_inf_ch.substr(17, 6), nullptr, 2);
        Draw.BB.x = (double)std::stoul(im_inf_ch.substr(23, 10), nullptr, 2);
        Draw.BB.y = (double)std::stoul(im_inf_ch.substr(33, 10), nullptr, 2);
        Draw.BB.width = (double)std::stoul(im_inf_ch.substr(43, 9), nullptr, 2);
        Draw.BB.height = (double)std::stoul(im_inf_ch.substr(52, 9), nullptr, 2);
        Draw.Cross.x = 360;// (double)std::stoul(im_inf_ch.substr(84, 9), nullptr, 2);
        Draw.Cross.y = 288;// (double)std::stoul(im_inf_ch.substr(93, 9), nullptr, 2);
        int dx = ((Draw.BB.x + Draw.BB.width / 2) - Draw.Cross.x);
        int dy = ((Draw.BB.y + Draw.BB.height / 2) - Draw.Cross.y);
        Draw.Danglex = dx;// (double)std::stoi(im_inf_ch.substr(23, 10), nullptr, 2);
        /*if (Draw.Danglex>360)
            Draw.Danglex = Draw.Danglex - 512;*/
        Draw.Dangley = dy;// (double)std::stoi(im_inf_ch.substr(33, 10), nullptr, 2);
        /*if (Draw.Dangley>128)
            Draw.Dangley = Draw.Dangley - 256;*/
        Draw.Algo = (int)std::stoi(im_inf_ch.substr(61, 3), nullptr, 2);
        if (Draw.Algo > 7)
            Draw.Algo = 0;
        Draw.toc = (double)std::stoi(im_inf_ch.substr(64, 7), nullptr, 2);
        Draw.DrawTar = (double)std::stoi(im_inf_ch.substr(71, 1), nullptr, 2);
        Draw.LTtar.x = (Draw.BB.x + Draw.BB.width / 2);;// (double)std::stoi(im_inf_ch.substr(72, 9), nullptr, 2);
        Draw.LTtar.y = (Draw.BB.y + Draw.BB.height / 2); // (double)std::stoi(im_inf_ch.substr(119, 9), nullptr, 2);
        Draw.TarColor.val[0] = (double)std::stoi(im_inf_ch.substr(72, 8), nullptr, 2);
        Draw.TarColor.val[1] = (double)std::stoi(im_inf_ch.substr(80, 8), nullptr, 2);
        Draw.TarColor.val[2] = (double)std::stoi(im_inf_ch.substr(88, 8), nullptr, 2);
}

cv::Mat getMedianDarkChannel(cv::Mat src, int patch)
{
        cv::Mat rgbmin = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
        cv::Mat MDCP;
        cv::Vec3b intensity;

    for(int m=0; m<src.rows; m++)
    {
        for(int n=0; n<src.cols; n++)
        {
            intensity = src.at<cv::Vec3b>(m,n);
            rgbmin.at<uchar>(m,n) = cv::min(cv::min(intensity.val[0], intensity.val[1]), intensity.val[2]);
        }
    }
    cv::medianBlur(rgbmin, MDCP, patch);
    return MDCP;

}

int estimateA(cv::Mat DC)
{
    double minDC, maxDC;
    cv::minMaxLoc(DC, &minDC, &maxDC);
    std::cout<<"estimated airlight is:"<<maxDC<<endl;
    return maxDC;
}

cv::Mat estimateTransmission(cv::Mat DCP, int ac)
{
    double w = 0.95;
    cv::Mat transmission = cv::Mat::zeros(DCP.rows, DCP.cols, CV_8UC1);
    //cv::convertScaleAbs(DCP, transmission, -255 * (w / ac), 255);
    cv::Scalar intensity;

    for (int m=0; m<DCP.rows; m++)
    {
        for (int n=0; n<DCP.cols; n++)
        {
            intensity = DCP.at<uchar>(m,n);
            transmission.at<uchar>(m,n) = (1 - w * intensity.val[0] / ac) * 255;
        }
    }
    return transmission;
}

cv::Mat getDehazed(cv::Mat source, cv::Mat t, int al)
{
    double tmin = 0.3;
    double tmax;

    cv::Scalar inttran;
    cv::Vec3b intsrc;
    cv::Mat dehazed = cv::Mat::zeros(source.rows, source.cols, CV_8UC3);

    for(int i=0; i<source.rows; i++)
    {
        for(int j=0; j<source.cols; j++)
        {
            inttran = t.at<uchar>(i,j);
            intsrc = source.at<cv::Vec3b>(i,j);
            tmax = (inttran.val[0]/255) < tmin ? tmin : (inttran.val[0]/255);
            double t;
            t = abs(((double)intsrc.val[0] - al) / tmax + al);
            dehazed.at<cv::Vec3b>(i, j)[0] = t > 255 ? 255 : (uchar)t;
            t = abs(((double)intsrc.val[1] - al) / tmax + al);
            dehazed.at<cv::Vec3b>(i, j)[1] = t > 255 ? 255 : (uchar)t;
            t = abs(((double)intsrc.val[2] - al) / tmax + al);
            dehazed.at<cv::Vec3b>(i, j)[2] = t > 255 ? 255 : (uchar)t;
            /*for(int k=0; k<3; k++)
            {
                dehazed.at<Vec3b>(i,j)[k] = abs((intsrc.val[k] - al) / tmax + al) > 255 ?
                255 : abs((intsrc.val[k] - al) / tmax + al);
            }*/
        }
    }
    return dehazed;
}

uint16_t g_zoomTable[] = {0X0000, 0X166F, 0X1FF0, 0X257D, // X1,  X2,  X3,  X4
                          0X2940, 0X2C02, 0X2E2B, 0X2FEE, // X5,  X6,  X7,  X8
                          0X316A, 0X32B2, 0X33D4, 0X34D9, // X9,  X10, X11, X12
                          0X35C8, 0X36A4, 0X3773, 0X3836, // X13, X14, X15, X16
                          0X38F0, 0X39A0, 0X3A49, 0X3AE8, // X17, X18, X19, X20
                          0X3B7F, 0X3C0C, 0X3C8E, 0X3D06, // X21, X22, X23, X24
                          0X3D73, 0X3DD4, 0X3E2C, 0X3E7C, // X25, X26, X27, X28
                          0X3EC2, 0X3F00, 0X3F38, 0X3F68, // X29, X30, X31, X32
                          0X3F94, 0X3FBD, 0X3FDF, 0X4000};// X33, X34, X35, X36

static uint8_t zoomTableSize = 36;
static uint8_t zoomTableRadius = 3;
std::vector<int> decToBinary(int n)
{
    // Size of an integer is assumed to be 10 bits
    std::vector<int> val;
    for (int i = 9; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            val.push_back(1);
        else
            val.push_back(0);
    }
    return val;
}

static inline uint16_t get_zoomValue(uint8_t zoomX)
{
    return g_zoomTable[zoomX];
}

static inline int16_t get_zoomX(uint16_t zoomValue)
{
    for (uint8_t i = 0; i < zoomTableSize; i++)
    {
        if (in_range(zoomValue, g_zoomTable[i], zoomTableRadius))
        {
            return i;
        }
    }

    // not found
    return -1;
}

static inline int16_t get_zoomX_nearest(uint16_t zoomValue)
{
    if (zoomValue <= g_zoomTable[0])
    {
        return 0;
    }
    else if ((zoomValue >= g_zoomTable[zoomTableSize - 1]))
    {
        return zoomTableSize - 1;
    }
    else
    {
        for (uint8_t i = 1; i < zoomTableSize; i++)
        {
            if (in_range(zoomValue, g_zoomTable[i], zoomTableRadius))
            {
                return i;
            }
            else if (zoomValue < g_zoomTable[i])//in_range(zoomValue, g_zoomTable[i], zoomTableRadius))
            {
                //zoomValue in [zoomTableSize(i-1), zoomTableSize(i)]
                if ((zoomValue - g_zoomTable[i-1]) > (g_zoomTable[i] - zoomValue))
                {
                    return (i-1);
                }
                else
                {
                    return i;
                }
            }
        }
    }
    // not found
    return -1;
}

MainWindow::MainWindow(QWidget *parent) :    QMainWindow(parent),    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //
    //Shared Setting
    MyData=new MySharedData();
    MyData->InitSharedData();
    //
    QStringListModel* listModel = new QStringListModel(bgslibrary::get_algs_name(), NULL);
    listModel->sort(0);

    ui->Motion_Box->setModel(listModel);
    ui->Motion_Box->setCurrentIndex(0);

    QStringListModel* listModel1 = new QStringListModel(Trackerlibrary::get_algs_name(), NULL);

    ui->Track_box->setModel(listModel1);
    ui->Track_box->setCurrentIndex(0);

    tmr=new QTimer(this);
    //Encoder Setting
    panAxis = new Axis_Data(17, 0.08);
    tiltAxis = new Axis_Data(17, 0.08);
    ui->tab->setEnabled(false);
    ui->tab_2->setEnabled(false);
    ui->Video_LF->setWindowFlags(Qt::Window);
    ui->Video_LF->setScaledContents(true);
    ui->Video_LF->showFullScreen();
    ui->Video_LF->hide();
    ui->change_algo->setVisible(false);

}

MainWindow::~MainWindow()
{
    frameorig.release();
    if(IPCamera_open)
        CpThread->release_ip();
    if(Camera_open)
        CpThread->release_cam();
    delete CpThread;
    if(Serial_open)
    {
        system("Taskkill /IM artillery_serial.exe /F");
        QObject::disconnect(tmr,SIGNAL(timeout()),this,SLOT(startread()));
        tmr->stop();
    }
    if(TCP_open)
    {
        socket->close();
        QObject::disconnect(socket,SIGNAL(readyRead()),this,SLOT(startread()));
    }
    if(Motion)
        destroyBGS();
    if(detect)
    {
        detector->~CDetector();
        fix_tracker->~CTracker();
    }
    if(track)
        statictracker.deleteTracker();
    if(record)
        video_rec->release();
    if(is_set)
    {
        map->save_targets();
        delete map;
    }
    delete ui;
}

void MainWindow::mainscenario(cv::Mat src)
{
    if(!startup)
    {
        //camera_TV ON
        Write(RELAY_COMMON, RELAY_USE_TV);
        QThread::msleep(50);
        Write(RELAY_COMMON,RELAY_IR_OFF);
        QThread::msleep(50);
        Write(RELAY_COMMON,RELAY_TV_ON);
        startup=true;
        QThread::msleep(50);
        Write(CAMERA_COMMON, CAMERA_ZOOM_VALUE, 0, 0, 0);
        ui->load_brightness_decrease_pushButton->setEnabled(false);
        ui->load_brightness_increase_pushButton->setEnabled(false);
        ui->load_contrast_decrease_pushButton->setEnabled(false);
        ui->load_contrast_increase_pushButton->setEnabled(false);
        ui->load_polarity_black_pushButton->setEnabled(false);
        ui->load_polarity_white_pushButton->setEnabled(false);
        ui->Video_L->installEventFilter(this);
        ui->Video_LF->installEventFilter(this);
        QThread::msleep(50);
        Write(CAMERA_COMMON, CAMERA_ZOOM_OUT, 0, 0, 0);
    }

    if(IPCamera_open)
    {
        cv::Mat SRCUNDRAW=src.clone();
        cv::Rect rr(50,50,720,576);
        frameorig= cv::Mat(src, rr);
        if(TCP_track)
        {
//            cv::cvtColor(frameorig,frameorig,CV_BGR2RGB);
            if(!myosd->is_initialized)
                myosd->initialize(&Drawings, frameorig);
    //        Drawings.DrawTemp = false;
            info_extract(src,Drawings);
            if(track)
            {
                if(Drawings.Temp.empty())
                {
                    Drawings.DrawTemp = true;
                    Drawings.Temp = cv::Mat(SRCUNDRAW,cv::Rect(Selected->x+50, Selected->y+50,
                                                               Selected->width, Selected->height));
                }
            }
            else
            {
              Drawings.DrawTemp = false;
              Drawings.Temp.release();
            }
            myosd->View();
            int32_t data = 0;
            uint8_t cmd=0x111;
            Write(cmd, (uint8_t *)&data);
        }
    }
    else
    {
        cv::cvtColor(src,frameorig,CV_BGR2RGB);
    }
    if(record)
    {
        cv::cvtColor(src,frameorig,CV_BGR2RGB);
        video_rec->write(frameorig);
    }
    if(Enhancment)
    {
        std::vector<cv::Mat> channels;
        cv::Mat img_hist_equalized;
        if(ui->Enh_Box->currentIndex()==0)
        {
            if(!first_enhacment)
            {
                darkChannel = getMedianDarkChannel(frameorig,5); //omar 5
                Airlight = estimateA(darkChannel);
                T = estimateTransmission(darkChannel, Airlight);
                ad = Airlight;
                fogfree = getDehazed(frameorig, T, Airlight);
//                cv::fastNlMeansDenoisingColored(fogfree, fogfree);
                first_enhacment=true;
            }
            else
            {
                Airlightp = ad;
                //cv::medianBlur(frame, frame, 9);
                darkChannel = getMedianDarkChannel(frameorig, 5);  //omar 5
                Airlight = estimateA(darkChannel);
                T = estimateTransmission(darkChannel, Airlight);
                double alpha = 0.05;
                ad = int(alpha * double(Airlight) + (1 - alpha) * double(Airlightp));//airlight smoothing
                fogfree = getDehazed(frameorig, T, ad);
//                cv::fastNlMeansDenoisingColored(fogfree, fogfree);
            }
        }
        else if(ui->Enh_Box->currentIndex()==1)
        {
            cv::cvtColor(frameorig,img_hist_equalized,CV_RGB2YCrCb);
            cv::split(img_hist_equalized,channels);
            cv::equalizeHist(channels[0], channels[0]);
            cv::equalizeHist(channels[1], channels[1]);
            cv::equalizeHist(channels[2], channels[2]);
            cv::merge(channels,img_hist_equalized);
            cv::cvtColor(img_hist_equalized,frameorig,CV_YCrCb2RGB);
        }
        else if(ui->Enh_Box->currentIndex()==2)
        {
            cv::cvtColor(frameorig,img_hist_equalized,CV_RGB2YCrCb);
            cv::split(img_hist_equalized,channels);
            cv::GaussianBlur(channels[0], channels[0],cv::Size(5,5),1.5);
            cv::GaussianBlur(channels[1], channels[1],cv::Size(5,5),1.5);
            cv::GaussianBlur(channels[2], channels[2],cv::Size(5,5),1.5);
            cv::merge(channels,img_hist_equalized);
            cv::cvtColor(img_hist_equalized,frameorig,CV_YCrCb2RGB);
        }
        else if(ui->Enh_Box->currentIndex()==3)
        {
            cv::cvtColor(frameorig,img_hist_equalized,CV_RGB2YCrCb);
            cv::split(img_hist_equalized,channels);
            cv::blur(channels[0], channels[0],cv::Size(5,5));
            cv::blur(channels[1], channels[1],cv::Size(5,5));
            cv::blur(channels[2], channels[2],cv::Size(5,5));
            cv::merge(channels,img_hist_equalized);
            cv::cvtColor(img_hist_equalized,frameorig,CV_YCrCb2RGB);
        }
        else if(ui->Enh_Box->currentIndex()==4)
        {
            cv::cvtColor(frameorig,img_hist_equalized,CV_RGB2YCrCb);
            cv::split(img_hist_equalized,channels);
            cv::medianBlur(channels[0], channels[0],3);
            cv::medianBlur(channels[1], channels[1],3);
            cv::medianBlur(channels[2], channels[2],3);
            cv::merge(channels,img_hist_equalized);
            cv::cvtColor(img_hist_equalized,frameorig,CV_YCrCb2RGB);
        }
        else
        {
            int alpha=ui->a_spin->value();
            int beta=ui->b_spin->value();
            alpha=alpha/10;
            frameorig=alpha*frameorig+cv::Scalar(beta,beta,beta);
        }
    }

    if(Motion)
        processFrame(frameorig);
    if(detect)
    {
        cv::cvtColor(frameorig,frame,CV_RGB2GRAY);
        const std::vector<Point_t>& centers = detector->Detect(frame);
        const regions_t& regions = detector->GetDetects();
        fix_tracker->Update(centers, regions, frame);
        float area = 0;
        for (size_t i = 0; i < fix_tracker->tracks.size(); i++)
        {
            if (fix_tracker->tracks[i]->IsRobust(fps, 0.75f, cv::Size2f(0.2f, 4.0f)))
            {
                cv::rectangle(frameorig, fix_tracker->tracks[i]->GetLastRect(), cv::Scalar(0, 255, 0), 1, CV_AA);
                if (area < fix_tracker->tracks[i]->GetLastRect().width*fix_tracker->tracks[i]->GetLastRect().height)
                {
                    init_Rect = fix_tracker->tracks[i]->GetLastRect();
                    area = fix_tracker->tracks[i]->GetLastRect().width*fix_tracker->tracks[i]->GetLastRect().height;
                    Selected=new cv::Rect(init_Rect);
                }
                for (size_t j = 0; j < fix_tracker->tracks[i]->trace.size() - 1; j++)
                {
                    cv::line(frameorig, fix_tracker->tracks[i]->trace[j], fix_tracker->tracks[i]->trace[j + 1],
                            Colors[fix_tracker->tracks[i]->track_id % 9], 2, CV_AA);
                }
            }
        }

    }
    if(!IPCamera_open)
    {
        if(init_track || track)
        {
            myosd->initialize(&Drawings, frameorig);
            if(track)
            {
                if (statictracker.UpdateTracker_(frameorig,*Selected,conf))
                {
                    TarColor=TrackOK;
                    std::cout<<conf<<std::endl;
                }
                else
                {
                    TarColor=TrackNotOK;
                    std::cout<<conf<<std::endl;
                }
            }
            Drawings.P =encoder_data_pan.toDouble();
            Drawings.T =encoder_data_tilt.toDouble();
            /*Drawings.dis1=(dis11);
             *                 Drawings.dis2=(dis22);*/
            int Dx=((Selected->x+Selected->width /2)-ScreenCursor.x);
            int Dy=((Selected->y+Selected->height /2)-ScreenCursor.y);
            if(track)
            {
                if(Dx!=0)
                {
                    float xx=(float)(tetex*180*Dx/(720*M_PI));
                    //lattakia
                    //float xx=(float)(-tetex*180*Dx/(720*M_PI));
                    std::cout<<"xx "<<xx<<std::endl;
                    std::cout<<"tetex "<<tetex<<std::endl;
                    if(conf>0.4)
                    {
                        //lattakia
                        panAxis->set_positionRef(encoder_data_pan.toFloat()+xx,ui->pan_positionRef_comboBox->currentText());
                        QString s;
                        s.setNum(panAxis->get_positionRef("rad"));
                        Write(PAN_POSITION_REF, s.toFloat());
                        QThread::msleep(500);
                    }
                }
                if(Dy!=0)
                {
                    float yy=(float)(-tetay*Dy*180/(576*M_PI));
                    //lattakia
//                    float yy=(float)(tetay*Dy*180/(576*M_PI));
                    if(conf>0.4)
                    {
                        tiltAxis->set_positionRef(encoder_data_tilt.toFloat()+yy,ui->tilt_positionRef_comboBox->currentText());
                        QString s;
                        s.setNum(tiltAxis->get_positionRef("rad"));
                        Write(TILT_POSITION_REF, s.toFloat());
                    }
                }
            }
            Drawings.Danglex =Dx;
            Drawings.Dangley =Dy;
            Drawings.BB =*Selected;
            Drawings.Algo =ui->Track_box->currentIndex();
            Drawings.Cross=ScreenCursor;
            double dt2= timer2->toc();
            Drawings.toc =dt2;
            Drawings.DrawTar =true;
            Drawings.LTtar =cv::Point(Selected->x+Selected->width/2,Selected->y+Selected->height/2);
            Drawings.TarColor=TarColor;
            if(Drawings.DrawTemp )
            {
                if(track)
                {
                    if(!statictracker.returnTemp().empty())
                        Drawings.Temp=statictracker.returnTemp();
                }
            }
            myosd->View();
        }
    }
    if(record)
    {
        video_rec1->write(frameorig);
    }
    CvSize ss;
    ss.width=(int)ui->Video_L->size().width();
    ss.height=(int)ui->Video_L->size().height();
    if(IPCamera_open)
        cv::cvtColor(frameorig,frameorig,CV_BGR2RGB);
    cv::resize(frameorig,frameorig,ss);
    QImage Qorg2((uchar*)frameorig.data,frameorig.cols,frameorig.rows,frameorig.step,QImage::Format_RGB888);
    QPixmap pix(QPixmap::fromImage(Qorg2));
    QPainter painter(&pix);
    painter.setPen(Qt::green );

    QPoint p0(ui->Video_L->width()/2-23,ui->Video_L->height()/2);
    QPoint p1(ui->Video_L->width()/2-3,ui->Video_L->height()/2);
    QPoint p2(ui->Video_L->width()/2+3,ui->Video_L->height()/2);
    QPoint p3(ui->Video_L->width()/2+23,ui->Video_L->height()/2);
    QPoint p4(ui->Video_L->width()/2,ui->Video_L->height()/2+3);
    QPoint p5(ui->Video_L->width()/2,ui->Video_L->height()/2+23);

    painter.drawLine(p0,p1);
    painter.drawLine(p2,p3);
    painter.drawLine(p4,p5);

    int diameter=60;
    painter.drawEllipse(QRect(frameorig.cols-diameter-10, 10, diameter, diameter));
    double vv=(encoder_data_pan.toDouble()-tetex*90/M_PI);
    int xx=frameorig.cols-40+(diameter/2)*sin(vv*M_PI/180);
    int yy=40-(diameter/2)*cos(vv*M_PI/180);
    QPoint p6(frameorig.cols-40,40);
    QPoint p7(xx,yy);
    painter.drawLine(p6,p7);
    double vv1=(encoder_data_pan.toDouble()+tetex*90/M_PI);
    int xx1=frameorig.cols-40+(diameter/2)*sin(vv1*M_PI/180);
    int yy1=40-(diameter/2)*cos(vv1*M_PI/180);
    QPoint p88(xx1,yy1);
    painter.drawLine(p6,p88);
    ///
    QRectF FF=QRectF(frameorig.cols-diameter-10, 80, diameter, diameter);
    painter.drawPie(FF,-90*16,180*16);
    vv=(encoder_data_tilt.toDouble()-tetay*90/M_PI);
    int xx2=frameorig.cols-40+(diameter/2)*cos(vv*M_PI/180);
    int yy2=110-(diameter/2)*sin(vv*M_PI/180);
    QPoint p8(frameorig.cols-40,110);
    QPoint p9(xx2,yy2);
    QPoint p10(tilt_old_x,tilt_old_y);
   // if(encoder_data_tilt.toDouble()<90 && encoder_data_tilt.toDouble()>-90)
    {
        painter.drawLine(p8,p9);
        tilt_old_x=xx2;
        tilt_old_y=yy2;
    }
//    else
//         painter.drawLine(p8,p10);
    vv1=(encoder_data_tilt.toDouble()+tetay*90/M_PI);
    int xx3=frameorig.cols-40+(diameter/2)*cos(vv1*M_PI/180);
    int yy3=110-(diameter/2)*sin(vv1*M_PI/180);
    QPoint p11(xx3,yy3);
    QPoint p12(tilt_old_x1,tilt_old_y1);
   // if(encoder_data_tilt.toDouble()<90 && encoder_data_tilt.toDouble()>-90)
    {
        painter.drawLine(p8,p11);
        tilt_old_x1=xx3;
        tilt_old_y1=yy3;
    }
//    else
//         painter.drawLine(p8,p12);
    if(is_set)
    {
        map->PanDrawing(encoder_data_pan.toDouble(),tetex*90/M_PI);
    }

    if(!full)
        ui->Video_L->setPixmap(pix);
    else
    {
         ui->Video_LF->setPixmap(pix);
    }
    if(scanning_pan)
    {
        if(start_scan)
        {
            pan_speed=(scan_phase_pan*M_PI/(180*scan_time_pan));
            QThread::msleep(500);
            pan_sccan=start_phase_pan+scan_phase_pan;
            if(pan_sccan>360)
            {
                start_phase_pan=start_phase_pan-360;
            }
            start_scan=false;
        }
        if(pan_sccan>360)
        {
            if(encoder_data_pan.toDouble()>180)
                encoder_data_pan=QString(QString::number(encoder_data_pan.toDouble()-360).rightJustified(4,' '));
            if(encoder_data_pan.toDouble()<start_phase_pan+scan_phase_pan   && !pan_dir)
            {
                panAxis->set_velocityRef(pan_speed,"0.5");
                Write(PAN_VELOCITY_REF, pan_speed);
                QThread::msleep(500);

            }
            if(encoder_data_pan.toDouble()>start_phase_pan+scan_phase_pan )
            {
                pan_dir=true;
            }
            if(encoder_data_pan.toDouble()>start_phase_pan   && pan_dir)
            {
                panAxis->set_velocityRef(-pan_speed,"0.5");
                Write(PAN_VELOCITY_REF, -pan_speed);
                QThread::msleep(500);

            }

            if(encoder_data_pan.toDouble()<start_phase_pan )
            {
                pan_dir=false;
            }
            if(encoder_data_pan.toDouble()<0)
                encoder_data_pan=QString(QString::number(encoder_data_pan.toDouble()+360).rightJustified(4,' '));
        }
        else
        {
            if(encoder_data_pan.toDouble()<pan_sccan  && !pan_dir)
            {
                panAxis->set_velocityRef(pan_speed,"0.5");
                Write(PAN_VELOCITY_REF, pan_speed);
                QThread::msleep(500);
            }
            if(encoder_data_pan.toDouble()>pan_sccan)
            {
                pan_dir=true;
            }
            if(encoder_data_pan.toDouble()>start_phase_pan && pan_dir)
            {
                panAxis->set_velocityRef(-pan_speed,"0.5");
                Write(PAN_VELOCITY_REF, -pan_speed);
                QThread::msleep(500);
            }
            if(encoder_data_pan.toDouble()<start_phase_pan)
            {
                pan_dir=false;
            }
        }
    }
    if(scanning_tilt)
    {
        if(start_scan)
        {
            tilt_speed=(scan_phase_tilt*M_PI/(180*scan_time_tilt));
            QThread::msleep(500);
            start_scan=false;
        }

        if(encoder_data_tilt.toDouble()<scan_phase_tilt+start_phase_tilt  && !tilt_dir)
        {
            tiltAxis->set_velocityRef(tilt_speed,"0.5");
            Write(TILT_VELOCITY_REF, tilt_speed);
            QThread::msleep(500);
        }
        if(encoder_data_tilt.toDouble()>scan_phase_tilt+start_phase_tilt)
        {
            tilt_dir=true;
        }
        if(encoder_data_tilt.toDouble()>start_phase_tilt && tilt_dir)
        {
            tiltAxis->set_velocityRef(-tilt_speed,"0.5");
            Write(TILT_VELOCITY_REF, -tilt_speed);
            QThread::msleep(500);
        }
        if(encoder_data_tilt.toDouble()<start_phase_tilt)
        {
            tilt_dir=false;
        }
    }

}

void MainWindow::Write(uint8_t cmd, uint8_t *data)
{
    data1.ToStation.command = cmd;
    data1.ToStation.data_pc_0 = data[0];
    data1.ToStation.data_pc_1 = data[1];
    data1.ToStation.data_pc_2= data[2];
    data1.ToStation.data_pc_3 = data[3];
    if(Serial_open)
        MyData->set_ToStation_data(data1.ToStation);
    else if(TCP_open)
    {
        unsigned char buf[11];
        buf[0]=0x55;
        buf[1]=0xAA;
        buf[2]=(cmd);
        buf[3]=(data[0]);
        buf[4]=(data[1]);
        buf[5]=(data[2]);
        buf[6]=(data[3]);
        buf[7]=(Selected->x>>2);
        buf[8]=(Selected->y>>2);
        unsigned char Xbits=Selected->x&0x03;
        unsigned char Ybits=Selected->y&0x03;
        unsigned char Status=0x00;
        if(track) Status|= 0x01;
        if(winup) Status|=0x02;
        if(windn) Status|=0x04;
        if(algo)  Status|=0x08;
        algo=false;
        buf[9]=((((Xbits<<2)+Ybits)<<4)&0xF0)+(Status & 0x0F);
        buf[10]=buf[2]^buf[3]^buf[4]^buf[5]^buf[6]^buf[7]^buf[8]^buf[9];
        try
        {
            socket->write((char*)buf,11);
//            cv::Mat L(800,256,CV_8UC3);
//            L=cv::Mat::zeros (200,600,CV_8UC3);
//            int fontFace =1;//cv::FONT_ITALIC;
//            char buff[255];
//            int len = sprintf(buff, "%.2f %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X  %02X %d",  10.0,
//                              buf[0],
//                              buf[1],
//                              buf[2],
//                              buf[3],
//                              buf[4],
//                              buf[5],
//                              buf[6],
//                              buf[7],
//                              buf[8],
//                              buf[9],buf[10],(unsigned char)Selected->x, 11);
//            putText(L, buff, cv::Point(10,60), fontFace, 1,cv::Scalar(255,255,255) ,1, 4);

//            imshow("SendTCP",L);
            socket->waitForBytesWritten();
        }
        catch(...)
        {

        }

    }

}

void MainWindow::Write(uint8_t cmd)
{
    int32_t data = 0;
    Write(cmd, (uint8_t *)&data);
}

void MainWindow::Write(uint8_t cmd, int32_t data)
{
    Write(cmd, (uint8_t *)&data);
}

void MainWindow::Write(uint8_t cmd, uint32_t data)
{
    Write(cmd, (uint8_t *)&data);
}

void MainWindow::Write(uint8_t cmd, float32_t data)
{
    Write(cmd, (uint8_t *)&data);
}

void MainWindow::Write(uint8_t cmd, uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3)
{
    uint8_t data[4];
    data[0] = data0;
    data[1] = data1;
    data[2] = data2;
    data[3] = data3;
    Write(cmd, data);
}

void MainWindow::on_Config_clicked()
{
    settings=new Setting;
    settings->setAttribute( Qt::WA_DeleteOnClose );
    settings->showNormal();
    QObject::connect(settings, SIGNAL(destroyed(QObject*)),this, SLOT(done()));

}

void MainWindow::done()
{
    if(settings->set_)
    {
       is_set=true;
       std::cout.precision(10);
//       std::cout<<settings->lat_home.toDouble();
//       std::cout<<settings->lon_home.toStdString();
       h_lat=settings->lat_home;
       h_lon=settings->lon_home;
       encoder_data_lat=QString(settings->lat_home);
       encoder_data_lon==QString(settings->lon_home);
       double pan_va=encoder_data_pan.toDouble();
       pan_va=pan_va-(360-settings->bearing.toDouble());
//       pan_va=360-pan_va;
//       qDebug()<<h_lat;
//       qDebug()<<encoder_data_lat;
       QString pan_va_f=QString::number(pan_va);

       panAxis->set_positionRef(pan_va_f.toFloat(),ui->pan_positionRef_comboBox->currentText());
       QString s;
       s.setNum(panAxis->get_positionRef("rad"));
       Write(PAN_POSITION_REF, s.toFloat());
       QThread::msleep(800);
       pan_va_f=QString::number(0);
       tiltAxis->set_positionRef(pan_va_f.toFloat(),ui->tilt_positionRef_comboBox->currentText());

       s.setNum(tiltAxis->get_positionRef("rad"));
       Write(TILT_POSITION_REF, s.toFloat());
       QThread::msleep(800);

       Write(PAN_COMMON,PAN_ENCODER_RESET);
       QThread::msleep(800);

       Write(TILT_COMMON,TILT_ENCODER_RESET);
       map=new QTestWin(ui->map_widget,settings->lat_home.toDouble(),settings->lon_home.toDouble());
       connect(map,SIGNAL(locgo(double)),this,SLOT(gotoloc(double)));
       map->resize(ui->map_widget->size());
       map->show();
       map->activateWindow();
       map->raise();
    }

}

void MainWindow::gotoloc(double a)
{
    QString pan_va_f=QString::number(a);

    panAxis->set_positionRef(pan_va_f.toFloat(),ui->pan_positionRef_comboBox->currentText());
    QString s;
    s.setNum(panAxis->get_positionRef("rad"));
    Write(PAN_POSITION_REF, s.toFloat());
}
void MainWindow::on_ctrl_right_pushButton_2_pressed()
{
    if(Zoom_Value==0)
        Zoom_Value=5743.0f;
    float move_speed=5743.0f/Zoom_Value;
    panAxis->set_velocityRef(move_speed,"20");
    Write(PAN_VELOCITY_REF, move_speed);
}

void MainWindow::on_ctrl_right_pushButton_2_released()
{
//     Write(PAN_VELOCITY_REF, 0.0f);
     Write(PAN_COMMON,PAN_HALT);
}

void MainWindow::on_ctrl_right_pushButton_pressed()
{
//    if(Zoom_Value==0)
//        Zoom_Value=5743.0f;
//    float move_speed=0.5f*5743.0f/Zoom_Value;
//    panAxis->set_velocityRef(move_speed,"1");
//    Write(PAN_VELOCITY_REF, move_speed);
    int Dx=50;
    float xx=(float)(tetex*180*Dx/(720*M_PI));
    panAxis->set_positionRef(encoder_data_pan.toFloat()+xx,ui->pan_positionRef_comboBox->currentText());
    QString s;
    s.setNum(panAxis->get_positionRef("rad"));
    Write(PAN_POSITION_REF, s.toFloat());
}

void MainWindow::on_ctrl_right_pushButton_released()
{
//    Write(PAN_VELOCITY_REF, 0.0f);
    Write(PAN_COMMON,PAN_HALT);
}

void MainWindow::on_ctrl_left_pushButton_pressed()
{
//    if(Zoom_Value==0)
//        Zoom_Value=5743.0f;
//    float move_speed=-0.5f*5743.0f/Zoom_Value;
//    panAxis->set_velocityRef(move_speed,"-1");
//    Write(PAN_VELOCITY_REF, move_speed);
    int Dx=-50;
    float xx=(float)(tetex*180*Dx/(720*M_PI));
    panAxis->set_positionRef(encoder_data_pan.toFloat()+xx,ui->pan_positionRef_comboBox->currentText());
    QString s;
    s.setNum(panAxis->get_positionRef("rad"));
    Write(PAN_POSITION_REF, s.toFloat());
}

void MainWindow::on_ctrl_left_pushButton_released()
{
//     Write(PAN_VELOCITY_REF, 0.0f);
     Write(PAN_COMMON,PAN_HALT);
}

void MainWindow::on_ctrl_left_pushButton_2_pressed()
{
    if(Zoom_Value==0)
        Zoom_Value=5743.0f;
    float move_speed=-5743.0f/Zoom_Value;
    panAxis->set_velocityRef(move_speed,"-20");
    Write(PAN_VELOCITY_REF, move_speed);
}

void MainWindow::on_ctrl_left_pushButton_2_released()
{
//    Write(PAN_VELOCITY_REF, 0.0f);
    Write(PAN_COMMON,PAN_HALT);
}

void MainWindow::on_DayCamera_clicked()
{
    ui->load_brightness_decrease_pushButton->setEnabled(false);
    ui->load_brightness_increase_pushButton->setEnabled(false);
    ui->load_contrast_decrease_pushButton->setEnabled(false);
    ui->load_contrast_increase_pushButton->setEnabled(false);
    ui->load_polarity_black_pushButton->setEnabled(false);
    ui->load_polarity_white_pushButton->setEnabled(false);
    Write(RELAY_COMMON, RELAY_USE_TV);
    QThread::msleep(500);
    Write(RELAY_COMMON,RELAY_IR_OFF);
    QThread::msleep(500);
    Write(RELAY_COMMON,RELAY_TV_ON);
}

void MainWindow::on_NightCamera_clicked()
{
    ui->load_brightness_decrease_pushButton->setEnabled(true);
    ui->load_brightness_increase_pushButton->setEnabled(true);
    ui->load_contrast_decrease_pushButton->setEnabled(true);
    ui->load_contrast_increase_pushButton->setEnabled(true);
    ui->load_polarity_black_pushButton->setEnabled(true);
    ui->load_polarity_white_pushButton->setEnabled(true);
    Write(RELAY_COMMON, RELAY_USE_IR);
    QThread::msleep(700);
    Write(RELAY_COMMON,RELAY_IR_ON);
    QThread::msleep(700);
    Write(RELAY_COMMON,RELAY_TV_OFF);
    QThread::msleep(700);
}

void MainWindow::on_pan_positionRef_lineEdit_returnPressed()
{
    panAxis->set_positionRef(ui->pan_positionRef_lineEdit->text().toFloat(),ui->pan_positionRef_comboBox->currentText());

    QString s;
    s.setNum(panAxis->get_positionRef("rad"));
    Write(PAN_POSITION_REF, s.toFloat());
}

void MainWindow::on_ctrl_up_pushButton_2_pressed()
{
    if(Zoom_Value==0)
        Zoom_Value=5743.0f;
    float move_speed=5743.0f/Zoom_Value;
    tiltAxis->set_velocityRef(move_speed,"0.3");
    Write(TILT_VELOCITY_REF, move_speed);
    //lattakia
//    tiltAxis->set_velocityRef(-0.3f,"0.3");
//    Write(TILT_VELOCITY_REF, -0.3f);
    max_tilt=false;
}

void MainWindow::on_ctrl_up_pushButton_2_released()
{
//    Write(TILT_VELOCITY_REF, 0.0f);
    Write(TILT_COMMON,TILT_HALT);
}

void MainWindow::on_ctrl_up_pushButton_pressed()
{
//    if(Zoom_Value==0)
//        Zoom_Value=5743.0f;
//    float move_speed=0.5f*5743.0f/Zoom_Value;
//    tiltAxis->set_velocityRef(move_speed,"0.05");
//    Write(TILT_VELOCITY_REF,move_speed);
    //lattakia
//    tiltAxis->set_velocityRef(-0.15f,"-0.15");
//    Write(TILT_VELOCITY_REF, -0.15f);
    int Dy=50;
    float yy=(float)(tetay*Dy*180/(576*M_PI));
    tiltAxis->set_positionRef(encoder_data_tilt.toFloat()+yy,ui->tilt_positionRef_comboBox->currentText());
    QString s;
    s.setNum(tiltAxis->get_positionRef("rad"));
    Write(TILT_POSITION_REF, s.toFloat());
    max_tilt=false;
}

void MainWindow::on_ctrl_up_pushButton_released()
{
//    Write(TILT_VELOCITY_REF, 0.0f);
    Write(TILT_COMMON,TILT_HALT);
}

void MainWindow::on_ctrl_down_pushButton_pressed()
{
//    if(Zoom_Value==0)
//        Zoom_Value=5743.0f;
//    float move_speed=-0.5f*5743.0/Zoom_Value;
//    tiltAxis->set_velocityRef(move_speed,"-0.05");
//    Write(TILT_VELOCITY_REF,move_speed);
    int Dy=-50;
    float yy=(float)(tetay*Dy*180/(576*M_PI));
    tiltAxis->set_positionRef(encoder_data_tilt.toFloat()+yy,ui->tilt_positionRef_comboBox->currentText());
    QString s;
    s.setNum(tiltAxis->get_positionRef("rad"));
    Write(TILT_POSITION_REF, s.toFloat());
    //lattakia
//    tiltAxis->set_velocityRef(0.15f,"0.15");
//    Write(TILT_VELOCITY_REF, 0.15f);
    max_tilt=false;
}

void MainWindow::on_ctrl_down_pushButton_released()
{
//    Write(TILT_VELOCITY_REF, 0.0f);
    Write(TILT_COMMON,TILT_HALT);
}

void MainWindow::on_ctrl_down_pushButton_2_pressed()
{
    if(Zoom_Value==0)
        Zoom_Value=5743.0f;
    float move_speed=-5743.0f/Zoom_Value;
    tiltAxis->set_velocityRef(move_speed,"-0.3");
    Write(TILT_VELOCITY_REF, move_speed);
    //lattakia
//    tiltAxis->set_velocityRef(0.3f,"0.3");
//    Write(TILT_VELOCITY_REF, 0.3f);
    max_tilt=false;
}

void MainWindow::on_ctrl_down_pushButton_2_released()
{
//    Write(TILT_VELOCITY_REF, 0.0f);
    Write(TILT_COMMON,TILT_HALT);
}

void MainWindow::on_tilt_positionRef_lineEdit_returnPressed()
{
    tiltAxis->set_positionRef(ui->tilt_positionRef_lineEdit->text().toFloat(),ui->tilt_positionRef_comboBox->currentText());

    QString s;
    s.setNum(tiltAxis->get_positionRef("rad"));
    Write(TILT_POSITION_REF, s.toFloat());
}

void MainWindow::Popup(const QPoint& pt,int type)
{
    double x_drift=(pt.x()-ui->Video_L->width()/2);
    double y_drift=(pt.y()-ui->Video_L->height()/2);

    float xx_d=(float)(tetex*180*x_drift/(ui->Video_L->width()*M_PI));
    float yy_d=(float)(-tetay*180*y_drift/(ui->Video_L->height()*M_PI));
    //lattakia
//    float xx_d=(float)(-tetex*180*x_drift/(720*M_PI));
//    float yy_d=(float)(tetay*180*y_drift/(576*M_PI));

    float result_x=encoder_data_pan.toDouble()+xx_d;
    if(result_x>=360)
        result_x-=360;
    float result_y=encoder_data_tilt.toDouble()+yy_d;

    if(type==0)
    {
        QPoint global = ui->Video_L->mapToGlobal(pt);
        QMenu* pPopup = new QMenu(ui->Video_L);
        QAction* pAction1 = new QAction("الذهاب إلى", ui->Video_L);
        pPopup ->addAction(pAction1);
        QAction* pItem = pPopup ->exec(global);
        if(pItem == pAction1)
        {
//            while(abs(encoder_data_tilt.toDouble()-result_y)>0.01)
//            {
//                if(result_y>encoder_data_tilt.toDouble())
//                {
//                    tiltAxis->set_velocityRef(0.3f,"0.3");
//                    Write(TILT_VELOCITY_REF, 0.3f);
//                }
//                else
//                {
//                    tiltAxis->set_velocityRef(-0.3f,"-0.3");
//                    Write(TILT_VELOCITY_REF,-0.3f);
//                }
//            }
            tiltAxis->set_positionRef(result_y,ui->tilt_positionRef_comboBox->currentText());
            QString ss;
            ss.setNum(tiltAxis->get_positionRef("rad"));
            Write(TILT_POSITION_REF, ss.toFloat());
            QThread::msleep(700);
            panAxis->set_positionRef(result_x,ui->pan_positionRef_comboBox->currentText());
            QString s;
            s.setNum(panAxis->get_positionRef("rad"));
            Write(PAN_POSITION_REF, s.toFloat());
        }
    }
    else
    {
        QPoint global = ui->Video_L->mapToGlobal(QPoint(ui->Video_L->width()/2,1));
        QMenu* pPopup = new QMenu(ui->Video_L);
        QString xx__drift=QString::number(result_x);
        QString yy__drift=QString::number(result_y);
        QAction* pAction1 = new QAction("PAN  = "+xx__drift, ui->Video_L);
        QAction* pAction2 = new QAction("TILT = "+yy__drift, ui->Video_L);
        pPopup ->addAction(pAction1);
        pPopup ->addAction(pAction2);
        QAction* pItem = pPopup ->exec(global);
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui->Video_L && !scanning_pan && !scanning_tilt)
    {
        switch( event->type() )
        {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button()==Qt::RightButton)
                this ->Popup(mouseEvent->pos(),0);
            if(mouseEvent->button()==Qt::LeftButton)
            {
                if(!init_track)
                    this ->Popup(mouseEvent->pos(),1);
                else
                {
                    if(mouseEvent->pos().x()>Selected->width/2
                            && mouseEvent->pos().x()<ui->Video_L->width()-(Selected->width/2))
                    {
                        if(mouseEvent->pos().y()>Selected->height/2
                                && mouseEvent->pos().y()<ui->Video_L->height()-(Selected->height/2))
                        {
                            Selected->x=mouseEvent->pos().x()-(Selected->width/2);
                            Selected->y=mouseEvent->pos().y()-(Selected->height/2);
                            if(!IPCamera_open)
                            {
                                if(!track)
                                {
                                    track=true;
                                    myosd = new SeaProjectsOSD();
                                    statictracker=Trackerlibrary::get_alg(Trackerlibrary::Algonumber
                                                                          [ui->Track_box->currentIndex()]);
                                    if(!detect)
                                    {
                                        if(!init_track)
                                            Selected=new cv::Rect(frameorig.cols/2-initWinWidth/2,
                                                                  frameorig.rows/2-initWinWidth*3/8,initWinWidth,
                                                                  initWinWidth*3/4);
                                    }
                                    std::cout<<Selected->area()<<std::endl;
                                    statictracker.InitTracker_(frameorig, *Selected);
                                    ui->detect->setEnabled(false);
                                    ui->Track_box->setEnabled(false);
                                    ui->Track->setText("إيقاف");
                                    ScreenCursor.x=frameorig.cols/2;
                                    ScreenCursor.y=frameorig.rows/2;
                                    timer2->tic();
                                }
                            }
                            else
                            {
                                if(!track)
                                {
                                    if(!detect)
                                    {
                                        if(!init_track)
                                            Selected=new cv::Rect(frameorig.cols/2-initWinWidth/2,
                                                                  frameorig.rows/2-initWinWidth*3/8,
                                                                  initWinWidth,initWinWidth*3/4);
                                    }
                                    track=true;
                                    int32_t data = 0;
                                    uint8_t cmd=0x111;
                                    Write(cmd, (uint8_t *)&data);
                                    ui->detect->setEnabled(false);
                                    ui->Track->setText("إيقاف");
                                    ui->Windo_m->setEnabled(false);
                                    ui->Windo_p->setEnabled(false);
                                }
                            }
                        }
                    }

                }
            }
            break;
        }
        default:
            break;
        }
    }
    if(obj==ui->Video_LF)
    {
        switch( event->type() )
        {
        case QEvent::MouseButtonPress:
        {
            ui->Video_LF->hide();
            full=false;
            break;
        }
        default:
            break;
        }
    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Escape:
    {
        ui->Video_LF->hide();
        break;
    }
    default:
        break;
    }
}

void MainWindow::on_AutoScanning_clicked()
{
    if(ui->AutoScanning->isChecked())
    {
        ui->widget->setEnabled(false);
        ui->widget_2->setEnabled(false);
        ui->widget_3->setEnabled(false);
        ui->tab->setEnabled(true);
        ui->tab_2->setEnabled(true);
    }
    else
    {
        ui->widget->setEnabled(true);
        ui->widget_2->setEnabled(true);
        ui->widget_3->setEnabled(true);
        ui->tab->setEnabled(false);
        ui->tab_2->setEnabled(false);
    }
}

void MainWindow::on_pan_positionRef_lineEdit_editingFinished()
{
    if(ui->pan_positionRef_lineEdit->text().toStdString()>"9")
    {
        QMessageBox::critical(this,"تحذير",
                "إدخال خاطئ",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        ui->pan_positionRef_lineEdit->setText("0");
    }
}

void MainWindow::on_tilt_positionRef_lineEdit_editingFinished()
{
    if(ui->tilt_positionRef_lineEdit->text().toStdString()>"9")
    {
        QMessageBox::critical(this,"تحذير",
                "إدخال خاطئ",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        ui->tilt_positionRef_lineEdit->setText("0");
    }
}

void MainWindow::on_ScanPan_clicked()
{
    if(!scanning_pan )
    {
        start_phase_pan=ui->PanStart->text().toDouble() ;
        if(start_phase_pan==0)
            start_phase_pan=0.01;
        panAxis->set_positionRef(float_t(start_phase_pan),ui->pan_positionRef_comboBox->currentText());
        QString ss;
        ss.setNum(panAxis->get_positionRef("rad"));
        Write(PAN_POSITION_REF, ss.toFloat());
        QThread::msleep(500);
        scan_phase_pan=ui->SectorValue->text().toDouble() ;
        scan_time_pan=ui->ScanTimeValue->text().toDouble() ;
        scan_tilt_pan=ui->TiltValue->text().toDouble() ;
        scanning_pan=true;
        ui->ScanPan->setText("توقيف المسح");
        ui->PanStart->setEnabled(false);
        ui->SectorValue->setEnabled(false);
        ui->ScanTimeValue->setEnabled(false);
        ui->TiltValue->setEnabled(false);
        ui->AutoScanning->setEnabled(false);
        start_scan=true;
        tiltAxis->set_positionRef(float_t(scan_tilt_pan),ui->tilt_positionRef_comboBox->currentText());
        QString s;
        s.setNum(tiltAxis->get_positionRef("rad"));
        Write(TILT_POSITION_REF, s.toFloat());
        QThread::msleep(500);
    }
    else
    {
        ui->ScanPan->setText("بدءالمسح");
        scanning_pan=false;
        Write(PAN_VELOCITY_REF, 0.0f);
        ui->PanStart->setEnabled(true);
        ui->SectorValue->setEnabled(true);
        ui->ScanTimeValue->setEnabled(true);
        ui->TiltValue->setEnabled(true);
        ui->AutoScanning->setEnabled(true);

    }
}

void MainWindow::on_PanStart_editingFinished()
{
    if(ui->PanStart->text().toStdString()>"9")
    {
        QMessageBox::critical(this,"تحذير",
                "إدخال خاطئ",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        ui->PanStart->setText("0");
    }
}

void MainWindow::on_SectorValue_editingFinished()
{
    if(ui->SectorValue->text().toStdString()>"9")
    {
        QMessageBox::critical(this,"تحذير",
                "إدخال خاطئ",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        ui->SectorValue->setText("0");
    }
}

void MainWindow::on_SectorValue_2_editingFinished()
{
    if(ui->SectorValue_2->text().toStdString()>"9")
    {
        QMessageBox::critical(this,"تحذير",
                "إدخال خاطئ",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        ui->SectorValue_2->setText("0");
    }
    if(ui->TiltStart->text().toDouble()==0)
    {
        if(ui->SectorValue_2->text().toDouble()>40)
        {
            QMessageBox::critical(this,"تحذير",
                                  "إدخال خاطئ",
                                  QMessageBox::NoIcon,
                                  QMessageBox::Ok );
            ui->SectorValue_2->setText("40");
        }
        if(ui->SectorValue_2->text().toDouble()<-20)
        {
            QMessageBox::critical(this,"تحذير",
                                  "إدخال خاطئ",
                                  QMessageBox::NoIcon,
                                  QMessageBox::Ok );
            ui->SectorValue_2->setText("-20");
        }
    }
    else
    {
        if(ui->TiltStart->text().toDouble()+ui->SectorValue_2->text().toDouble()<-20)
        {
            QMessageBox::critical(this,"تحذير",
                                  "إدخال خاطئ",
                                  QMessageBox::NoIcon,
                                  QMessageBox::Ok );
            int ss=-20-ui->TiltStart->text().toDouble();
            ui->SectorValue_2->setText(QString::number(ss).rightJustified(2,' '));
        }
        if(ui->TiltStart->text().toDouble()+ui->SectorValue_2->text().toDouble()>40)
        {
            QMessageBox::critical(this,"تحذير",
                                  "إدخال خاطئ",
                                  QMessageBox::NoIcon,
                                  QMessageBox::Ok );
            int ss=40-ui->TiltStart->text().toDouble();
            ui->SectorValue_2->setText(QString::number(ss).rightJustified(2,' '));
        }
    }
}

void MainWindow::on_TiltStart_editingFinished()
{
    if(ui->TiltStart->text().toStdString()>"9")
    {
        QMessageBox::critical(this,"تحذير",
                "إدخال خاطئ",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        ui->TiltStart->setText("0");
    }
    if(ui->TiltStart->text().toDouble()==0)
    {
        if(ui->TiltStart->text().toDouble()>40)
        {
            QMessageBox::critical(this,"تحذير",
                                  "إدخال خاطئ",
                                  QMessageBox::NoIcon,
                                  QMessageBox::Ok );
            ui->TiltStart->setText("40");
        }
        if(ui->TiltStart->text().toDouble()<-20)
        {
            QMessageBox::critical(this,"تحذير",
                                  "إدخال خاطئ",
                                  QMessageBox::NoIcon,
                                  QMessageBox::Ok );
            ui->TiltStart->setText("-20");
        }
    }
    else
    {
        if(ui->TiltStart->text().toDouble()+ui->SectorValue_2->text().toDouble()<-20)
        {
            QMessageBox::critical(this,"تحذير",
                                  "إدخال خاطئ",
                                  QMessageBox::NoIcon,
                                  QMessageBox::Ok );
            int ss=-20-ui->SectorValue_2->text().toDouble();
            ui->TiltStart->setText(QString::number(ss).rightJustified(2,' '));
        }
        if(ui->TiltStart->text().toDouble()+ui->SectorValue_2->text().toDouble()>40)
        {
            QMessageBox::critical(this,"تحذير",
                                  "إدخال خاطئ",
                                  QMessageBox::NoIcon,
                                  QMessageBox::Ok );
            int ss=40-ui->SectorValue_2->text().toDouble();
            ui->TiltStart->setText(QString::number(ss).rightJustified(2,' '));
        }
    }
}

void MainWindow::on_load_focus_increase_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_FOCUS_IN, 0, 0, 0);
}

void MainWindow::on_load_focus_increase_pushButton_released()
{
    Write(CAMERA_COMMON, CAMERA_FOCUS_STOP, 0, 0, 0);
}

void MainWindow::on_load_focus_decrease_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_FOCUS_OUT, 0, 0, 0);
}

void MainWindow::on_load_focus_decrease_pushButton_released()
{
    Write(CAMERA_COMMON, CAMERA_FOCUS_STOP, 0, 0, 0);
}

void MainWindow::on_load_contrast_increase_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_CONTRAST_IN);
}

void MainWindow::on_load_contrast_increase_pushButton_released()
{
    Write(GEN_EMPTY);
}

void MainWindow::on_load_contrast_decrease_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_CONTRAST_OUT);
}

void MainWindow::on_load_contrast_decrease_pushButton_released()
{
    Write(GEN_EMPTY);
}

void MainWindow::on_load_brightness_increase_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_BRIGHTNESS_IN);
}

void MainWindow::on_load_brightness_increase_pushButton_released()
{
    Write(GEN_EMPTY);
}

void MainWindow::on_load_brightness_decrease_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_BRIGHTNESS_OUT);
}

void MainWindow::on_load_brightness_decrease_pushButton_released()
{
    Write(GEN_EMPTY);
}

void MainWindow::on_load_polarity_white_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_POLARITY_WHITE);
}

void MainWindow::on_load_polarity_white_pushButton_released()
{
    Write(GEN_EMPTY);
}

void MainWindow::on_load_polarity_black_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_POLARITY_BLACK);
}

void MainWindow::on_load_polarity_black_pushButton_released()
{
    Write(GEN_EMPTY);
}

void MainWindow::on_load_autoMode_off_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_SEMIAUTO);
}

void MainWindow::on_load_autoMode_off_pushButton_released()
{
    Write(GEN_EMPTY);
}

void MainWindow::on_load_autoMode_on_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_AUTO);
}

void MainWindow::on_load_autoMode_on_pushButton_released()
{
    Write(GEN_EMPTY);
}

void MainWindow::on_load_focusMode_manual_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_FOCUS_MANUAL);
}

void MainWindow::on_load_focusMode_manual_pushButton_released()
{
    Write(GEN_EMPTY);
}

void MainWindow::on_load_focusMode_auto_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_FOCUS_AUTO);
}

void MainWindow::on_load_focusMode_auto_pushButton_released()
{
    Write(GEN_EMPTY);
}

void MainWindow::on_load_focusMode_combine_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_FOCUS_AUTO_ONE_TIME);
}

void MainWindow::on_load_focusMode_combine_pushButton_released()
{
    Write(GEN_EMPTY);
}

void MainWindow::on_load_laser_shoot_pushButton_pressed()
{
    Write(RELAY_COMMON, RELAY_LRF_ON);
    QThread::msleep(800);
    Write(LASER_COMMON, LASER_ON);
    QThread::msleep(800);
    ui->latitude->clear();
    ui->Magnitude->clear();
    Write(LASER_COMMON, LASER_CHARGE_AND_SHOOT);
    QThread::msleep(800);
    laser_shoot=true;
}

void MainWindow::on_load_laser_shoot_pushButton_released()
{
//    QThread::msleep(800);
//    Write(RELAY_COMMON, RELAY_LRF_OFF);
//    QThread::msleep(800);
//    Write(LASER_COMMON, LASER_OFF);
}

void MainWindow::on_load_calibration_pushButton_pressed()
{
    Write(CAMERA_COMMON, CAMERA_CALIBRATION);
}

void MainWindow::on_load_calibration_pushButton_released()
{
    Write(GEN_EMPTY);
}

void MainWindow::on_ScanTilt_clicked()
{
    if(!scanning_tilt)
    {
        start_phase_tilt=ui->TiltStart->text().toDouble() ;
        tiltAxis->set_positionRef(float_t(start_phase_tilt),ui->tilt_positionRef_comboBox->currentText());
        QString s;
        s.setNum(tiltAxis->get_positionRef("rad"));
        Write(TILT_POSITION_REF, s.toFloat());
        QThread::msleep(500);
        scan_phase_tilt=ui->SectorValue_2->text().toDouble() ;
        scan_time_tilt=ui->ScanTimeValue_2->text().toDouble() ;
        scan_pan_tilt=ui->PanValue->text().toDouble() ;
        scanning_tilt=true;
        ui->ScanTilt->setText("توقيف المسح");
        ui->TiltStart->setEnabled(false);
        ui->SectorValue_2->setEnabled(false);
        ui->ScanTimeValue_2->setEnabled(false);
        ui->PanValue->setEnabled(false);
        ui->AutoScanning->setEnabled(false);
        start_scan=true;
        panAxis->set_positionRef(float_t(scan_pan_tilt),ui->pan_positionRef_comboBox->currentText());
        QString ss;
        ss.setNum(panAxis->get_positionRef("rad"));
        Write(PAN_POSITION_REF, ss.toFloat());
        QThread::msleep(500);
    }
    else
    {
        ui->ScanTilt->setText("بدءالمسح");
        scanning_tilt=false;        
        Write(TILT_VELOCITY_REF, 0.0f);
        ui->TiltStart->setEnabled(true);
        ui->SectorValue_2->setEnabled(true);
        ui->ScanTimeValue_2->setEnabled(true);
        ui->PanValue->setEnabled(true);
        ui->AutoScanning->setEnabled(true);

    }
}

void MainWindow::on_TiltValue_editingFinished()
{
    if(ui->TiltValue->text().toStdString()>"9")
    {
        QMessageBox::critical(this,"تحذير",
                "إدخال خاطئ",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        ui->TiltValue->setText("0");
    }
    int ss=ui->TiltValue->text().toInt();
    if(ss>40 )
    {
        QMessageBox::critical(this,"تحذير",
                "إدخال خاطئ",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        ss=40;
        ui->SectorValue_2->setText(QString::number(ss).rightJustified(2,' '));
    }
    if(ss<-20 )
    {
        QMessageBox::critical(this,"تحذير",
                "إدخال خاطئ",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        ss=-20;
        ui->SectorValue_2->setText(QString::number(ss).rightJustified(2,' '));
    }
}

void MainWindow::on_ScanTimeValue_editingFinished()
{
    if(ui->ScanTimeValue->text().toStdString()>"9")
    {
        QMessageBox::critical(this,"تحذير",
                "إدخال خاطئ",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        ui->ScanTimeValue->setText("0");
    }
    if((ui->SectorValue->text().toDouble()*M_PI/(180.0*ui->ScanTimeValue->text().toDouble()))>0.5)
    {
        QMessageBox::critical(this,"تحذير",
                "سريع جداً",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        int scan_timee=(ui->SectorValue->text().toDouble()*M_PI/(180.0*0.5));
        ui->ScanTimeValue->setText(QString::number(scan_timee).rightJustified(2,' '));
    }
    if((ui->SectorValue->text().toDouble()*M_PI/(180.0*ui->ScanTimeValue->text().toDouble()))<0.05)
    {
        QMessageBox::critical(this,"تحذير",
                "بطيء جداً",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        int scan_timee=(ui->SectorValue->text().toDouble()*M_PI/(180.0*0.05));
        ui->ScanTimeValue->setText(QString::number(scan_timee).rightJustified(2,' '));
    }
}

void MainWindow::on_FullScreen_clicked()
{
    full=true;
    ui->Video_LF->showFullScreen();
}

void MainWindow::on_PanValue_editingFinished()
{
    if(ui->PanValue->text().toStdString()>"9")
    {
        QMessageBox::critical(this,"تحذير",
                "إدخال خاطئ",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        ui->PanValue->setText("0");
    }
}

void MainWindow::on_ScanTimeValue_2_editingFinished()
{
    if(ui->ScanTimeValue_2->text().toStdString()>"9")
    {
        QMessageBox::critical(this,"تحذير",
                "إدخال خاطئ",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        ui->ScanTimeValue_2->setText("0");
    }
    if((ui->SectorValue_2->text().toDouble()*M_PI/(180.0*ui->ScanTimeValue_2->text().toDouble()))>0.2)
    {
        QMessageBox::critical(this,"تحذير",
                "سريع جداً",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        int scan_timee=(ui->SectorValue_2->text().toDouble()*M_PI/(180.0*0.2));
        ui->ScanTimeValue_2->setText(QString::number(scan_timee).rightJustified(2,' '));
    }
    if((ui->SectorValue_2->text().toDouble()*M_PI/(180.0*ui->ScanTimeValue_2->text().toDouble()))<0.08)
    {
        QMessageBox::critical(this,"تحذير",
                "بطيء جداً",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
        int scan_timee=(ui->SectorValue_2->text().toDouble()*M_PI/(180.0*0.08));
        ui->ScanTimeValue_2->setText(QString::number(scan_timee).rightJustified(2,' '));
    }
}

void MainWindow::on_load_zoom_increase_pushButton_clicked()
{
    if (Zoom_ind < zoomTableSize)
    {
        Zoom_ind++;
        uint16_t zoomV = get_zoomValue(Zoom_ind);//g_zoomTable[zoomX];
        Write(CAMERA_COMMON, CAMERA_ZOOM_VALUE, zoomV, zoomV >> 8, 0);
//        Write(CAMERA_COMMON, CAMERA_ZOOM_IN, 0, 0, 0);
    }
    else
        QMessageBox::critical(this,"تحذير",
                "أعلى بؤرة",
                QMessageBox::NoIcon,
                QMessageBox::Ok );



}

void MainWindow::on_load_zoom_decrease_pushButton_clicked()
{
    if (Zoom_ind > 0)
    {
        Zoom_ind--;
        uint16_t zoomV = get_zoomValue(Zoom_ind);//g_zoomTable[zoomX];
        Write(CAMERA_COMMON, CAMERA_ZOOM_VALUE, zoomV, zoomV >> 8, 0);
//        Write(CAMERA_COMMON, CAMERA_ZOOM_OUT, 0, 0, 0);
    }
    else
        QMessageBox::critical(this,"تحذير",
                "أقل بؤرة",
                QMessageBox::NoIcon,
                QMessageBox::Ok );
}

void MainWindow::on_LocalControl_clicked(bool checked)
{
    if(checked)
    {
        ui->widget_5->setEnabled(true);
        ui->widget_10->setEnabled(false);
    }
    else
    {
        ui->widget_5->setEnabled(false);
        ui->widget_10->setEnabled(true);
    }
}

void MainWindow::on_RunCamera_clicked()
{
    if(!Camera_open)
    {
        int ind=ui->CameraIndex->text().toInt();
        CpThread=new CaptureThread(ind);
        QObject::connect(CpThread,SIGNAL(frameCaptured(cv::Mat)),this,SLOT(mainscenario(cv::Mat)));
        Camera_open=true;
        ui->RecordVideo->setEnabled(true);
        ui->widget_11->setEnabled(true);
        ui->widget_12->setEnabled(true);        
        ui->widget_13->setEnabled(true);
        ui->RunCamera->setText("إيقاف الكاميرا");
        ui->video_name->setEnabled(true);
    }
    else
    {
        CpThread->release_cam();
        Camera_open=false;
        QObject::disconnect(CpThread,SIGNAL(frameCaptured(cv::Mat)),this,SLOT(mainscenario(cv::Mat)));
        ui->RunCamera->setText("تشغيل الكاميرا");
        ui->Video_L->clear();
        ui->Video_LF->clear();
        ui->RecordVideo->setEnabled(false);
        ui->widget_11->setEnabled(false);
        ui->widget_12->setEnabled(false);
        ui->widget_13->setEnabled(false);
        ui->video_name->setEnabled(false);
        startup=false;
    }
}

void MainWindow::on_RunSerial_clicked()
{
    if(!Serial_open)
    {
        QString ho=QDir::currentPath();
        QDir::setCurrent(ho);
        system("start artillery_serial.exe");
        Serial_open=true;
        ui->RunSerial->setText("إيقاف");
        QObject::connect(tmr,SIGNAL(timeout()),this,SLOT(startread()));
        tmr->start(50);
        ui->widget->setEnabled(true);
        ui->widget_2->setEnabled(true);
        ui->widget_14->setEnabled(true);
        ui->widget_4->setEnabled(true);
        ui->change_algo->setVisible(false);
    }
    else
    {
        system("Taskkill /IM artillery_serial.exe /F");
        Serial_open=false;
        ui->RunSerial->setText("تشغيل البوابة التسلسلية");
        QObject::disconnect(tmr,SIGNAL(timeout()),this,SLOT(startread()));
        tmr->stop();
        ui->widget->setEnabled(false);
        ui->widget_14->setEnabled(false);
        ui->widget_2->setEnabled(false);
        ui->widget_4->setEnabled(false);
    }
}

void MainWindow::on_ConnectTCP_clicked()
{
    if(!TCP_open)
    {
        socket=new QTcpSocket(this);
        TCP_open=true;
        socket->connectToHost(QHostAddress(ui->Ip->text()),4000);
        ui->ConnectTCP->setText("إيقاف الاتصال");
        QObject::connect(socket,SIGNAL(readyRead()),this,SLOT(startread()));
        ui->widget->setEnabled(true);
        ui->widget_14->setEnabled(true);
        ui->widget_2->setEnabled(true);
        ui->widget_4->setEnabled(true);
        ui->Track_box->setVisible(false);
        ui->Track_label->setVisible(false);
        ui->change_algo->setVisible(true);
    }
    else
    {
        socket->close();
        TCP_open=false;
        ui->ConnectTCP->setText("اتصال");
        QObject::disconnect(socket,SIGNAL(readyRead()),this,SLOT(startread()));
        ui->widget->setEnabled(false);
        ui->widget_14->setEnabled(false);
        ui->widget_2->setEnabled(false);
        ui->widget_4->setEnabled(false);

    }
}

void MainWindow::on_RunIPCamera_clicked()
{
    if(!IPCamera_open)
    {
        const std::string videoStreamAddress = "rtsp://"+ui->Ip->text().toStdString()+":8554/usb1";
        cv::Size rtspRes;
        rtspRes.width=1280;
        rtspRes.height=720;
        CpThread=new CaptureThread(QString::fromStdString(videoStreamAddress),rtspRes);
        IPCamera_open=true;
        ui->RunIPCamera->setText("إيقاف الكاميرا");
        myosd = new SeaProjectsOSD();
        QObject::connect(CpThread,SIGNAL(frameCaptured(cv::Mat)),this,SLOT(mainscenario(cv::Mat)));
        ui->RecordVideo->setEnabled(true);
        ui->widget_11->setEnabled(true);
        ui->widget_12->setEnabled(true);
        ui->widget_13->setEnabled(true);
        ui->video_name->setEnabled(true);
    }
    else
    {
        CpThread->release_ip();
        IPCamera_open=false;
        ui->RunIPCamera->setText("تشغيل الكاميرا");
        QObject::disconnect(CpThread,SIGNAL(frameCaptured(cv::Mat)),this,SLOT(mainscenario(cv::Mat)));
        ui->RecordVideo->setEnabled(false);
        ui->widget_11->setEnabled(false);
        ui->widget_12->setEnabled(false);
        ui->widget_13->setEnabled(false);
        ui->video_name->setEnabled(false);
        ui->Video_L->clear();
        ui->Video_LF->clear();

    }
}

void MainWindow::on_RecordVideo_clicked()
{
    if(!record)
    {
        record=true;
        QString ho=ui->video_name->text()+".avi";
        QString ho1=ui->video_name->text()+"1.avi";
        video_rec=new cv::VideoWriter(ho.toStdString(), CV_FOURCC('m','p', '4', 'v'), 15,
                                      cv::Size(frameorig.cols,frameorig.rows));
        video_rec1=new cv::VideoWriter(ho1.toStdString(), CV_FOURCC('m','p', '4', 'v'), 15,
                                       cv::Size(frameorig.cols,frameorig.rows));
        ui->RecordVideo->setText("إيقاف");
        ui->video_name->setEnabled(false);
    }
    else
    {
        record=false;
        video_rec->release();
        video_rec1->release();
        ui->RecordVideo->setText("تسجيل");
        ui->video_name->setEnabled(true);
    }
}

int dec_places( double d )
{
    constexpr double precision{ 1e-7 };

    double temp{}; int decimal_places{};
    do {
        d *= 10;
        temp = d - int( d );

        decimal_places++;
    } while( temp > precision && decimal_places < std::numeric_limits<double>::digits10 );

    return decimal_places;
}
void MainWindow::startread()
{
    if(TCP_open)
    {       
        unsigned char buffer[256];
        qDebug() <<"socket";
        qDebug() << socket->bytesAvailable();
//        buffer=(unsigned char)socket->read(socket->bytesAvailable()).data();
        memcpy( buffer, socket->readAll().data(), sizeof( socket->bytesAvailable() ) );
//        qDebug() << (unsigned)strlen(buffer);
        qDebug() << buffer;
        return;
//        memcpy(bufer,buffer, sizeof(bufer));

        unsigned char b0=buffer[0];
        unsigned char b1=buffer[1];
        unsigned char b2=buffer[2];
        unsigned char b3=buffer[3];
        unsigned char b4=buffer[4];
        unsigned char b5=buffer[5];
        unsigned char b6=buffer[6];
        unsigned char b7=buffer[7];
        unsigned char check_sum;

        check_sum=b2^b3^b4^b5^b6;
        if(b0==85 && b1==170 && b7==check_sum)
        {
            data1.FromStation.command=b2;
            data1.FromStation.data_station_0=b3;
            data1.FromStation.data_station_1=b4;
            data1.FromStation.data_station_2=b5;
            data1.FromStation.data_station_3=b6;
        }
        else
            return;

    }
    else if(Serial_open)
        data1= MyData->get_shared_data();

    uint32_t encoder_data;
    uint8_t state;

    uint8_t data_[4] = { data1.FromStation.data_station_0,
                         data1.FromStation.data_station_1,
                         data1.FromStation.data_station_2,
                         data1.FromStation.data_station_3};
    switch ((uint8_t)data1.FromStation.command)
    {
    case PC_PAN_STATUS:
        state = data_[3];
        data_[3] = 0;
        encoder_data = *(uint32_t *)data_;
        panAxis->set_newEncoderData(encoder_data);
        encoder_data_pan.setNum(panAxis->get_position(ui->pan_positionRef_comboBox->currentText()),'f', 3);        
//        qDebug() <<"encoder_data";
//        qDebug() <<encoder_data;
        qDebug() <<encoder_data_pan;
//        panAxis->set_positionRef(encoder_data_pan.toFloat(),ui->pan_positionRef_comboBox->currentText());
//        QString s;
//        s.setNum(panAxis->get_positionRef("rad"));
//        Write(PAN_POSITION_REF, encoder_data_pan.toFloat());
//       std::cout<<"PAN"<<encoder_data_pan.toDouble()<<std::endl;
        break;

    case PC_TILT_STATUS:

        state = data_[3];
        data_[3] = 0;

        encoder_data = *(uint32_t *)data_;
        tiltAxis->set_newEncoderData(encoder_data);
        encoder_data_tilt.setNum(tiltAxis->get_position(ui->tilt_positionRef_comboBox->currentText()),'f', 3);
//        tiltAxis->set_positionRef(encoder_data_tilt.toFloat(),ui->tilt_positionRef_comboBox->currentText());
//        QString ss;
//        ss.setNum(tiltAxis->get_positionRef("rad"));
//        Write(TILT_POSITION_REF, encoder_data_tilt.toFloat());
//        qDebug() <<"PC_TILT_STATUS";
//        qDebug() <<encoder_data_tilt;

//        if(encoder_data_tilt.toDouble()>300)
//            encoder_data_tilt=QString(QString::number(encoder_data_tilt.toDouble()-360).rightJustified(4,' '));

//        std::cout<<"TILT "<<encoder_data_tilt.toFloat()<<std::endl;
//        if(state & 0x04 && !max_tilt)
//        {
//            max_tilt=true;
//            if(encoder_data_tilt.toDouble()>41)
//                QMessageBox::critical(this,"تحذير",
//                                      "أعلى زاوية",
//                                      QMessageBox::NoIcon,
//                                      QMessageBox::Ok );
//            if(encoder_data_tilt.toDouble()<-72)
//                QMessageBox::critical(this,"تحذير",
//                                      "أخفض زاوية",
//                                      QMessageBox::NoIcon,
//                                      QMessageBox::Ok );
//        }

        break;

    case PAN_MOTOR_STEPS:
        state = data_[3];
        data_[3] = 0;

        encoder_data = *(uint32_t *)data_;
        panAxis->set_positionRef(encoder_data*360.0/56000.0,ui->pan_positionRef_comboBox->currentText());

//        QString ffg=QString::number((double)panAxis->get_position(ui->pan_positionRef_comboBox->currentText()));
//        std::cout<<"get_positionRef "<<ffg.toStdString()<<std::endl;
//        panAxis->get_positionRef(ui->pan_positionRef_comboBox->currentText());
//        QString sp;
//        sp.setNum(panAxis->get_positionRef("rad"));
//        panAxis->set_newEncoderData(encoder_data*2*M_PI/56000);
        encoder_data_pan.setNum(encoder_data*360.0/56000.0
                                /*panAxis->get_position(ui->pan_positionRef_comboBox->currentText())*/);
        std::cout<<"encoder_data_pan"<<encoder_data_pan.toDouble()<<std::endl;
        break;
    case TILT_MOTOR_STEPS:
        state = data_[3];
        data_[3] = 0;

        encoder_data = *(uint32_t *)data_;
//        std::cout<<"PAN_MOTOR_STEPS "<<encoder_data*360/56000<<std::endl;
//        tiltAxis->set_newEncoderData(encoder_data*2*M_PI/56000);
        tiltAxis->set_positionRef(encoder_data*360.0/56000.0,ui->tilt_positionRef_comboBox->currentText());
//        tiltAxis->get_positionRef(ui->tilt_positionRef_comboBox->currentText());
        encoder_data_tilt.setNum(encoder_data*360.0/56000.0
                                 /*tiltAxis->get_position(ui->tilt_positionRef_comboBox->currentText()),'f', 3*/);

        std::cout<<"encoder_data_tilt "<<encoder_data*360.0/56000.0<<std::endl;
        break;
    case PC_LRF_DATA:
        if(data_[0]==0)
            QMessageBox::critical(this,"تحذير",
                                  "لا إصابة",
                                  QMessageBox::NoIcon,
                                  QMessageBox::Ok );
        if(data_[0]==1)
        {
            laser_distance=data_[2]+(data_[3]<<8);
            const double radiusEarthKilometres = 6378137;//km
            double distRatio = laser_distance / radiusEarthKilometres;
            std::cout.precision(10);
//            std::cout<<" map->lat "<<map->lat<<std::endl;
//            std::cout<<" map->lng "<<map->lng<<std::endl;

//            std::cout<<" dec_places"<<dec_places(map->lat)<<std::endl;
//            std::cout<<" dec_places1 "<<dec_places(map->lng)<<std::endl;
            double lat_r=map->lat*M_PI/180;
            double lng_r=map->lng*M_PI/180;
            double pan_r=encoder_data_pan.toDouble()*M_PI/180;

            double lat2=asin(sin(lat_r)*cos(distRatio)
                             +cos(lat_r)*sin(distRatio)*cos(pan_r));
            double lng2=lng_r+atan2(sin(pan_r)*sin(distRatio)*cos(lat_r),
                                  cos(distRatio)-sin(lat_r)*sin(lat2));
            ui->DistanceValue->setText(QString::number(data_[2]+(data_[3]<<8)).rightJustified(5,' '));
            ui->latitude->setText(QString::number(lat2*180/M_PI,'g',8).rightJustified(8,' '));
            ui->Magnitude->setText(QString::number(lng2*180/M_PI,'g',8).rightJustified(8,' '));
            if(is_set && laser_shoot)
            {
                map->TargetDrawing(ui->Magnitude->text().toDouble(),ui->latitude->text().toDouble());
                laser_shoot=false;
            }
        }
        if(data_[0]==3)
            QMessageBox::critical(this,"تحذير",
                                  "خطأ",
                                  QMessageBox::NoIcon,
                                  QMessageBox::Ok );
        break;

    case PC_OPTOLOAD_STATUS:
        uint16_t return_zoom=data_[2]+(data_[3]<<8);
//        std::cout<<"return_zoom "<<return_zoom<<std::endl;
      //  if(Zoom_ind!=get_zoomX_nearest(return_zoom) )
        {
            Zoom_ind=get_zoomX_nearest(return_zoom);
            Zoom_Value=get_zoomValue(Zoom_ind);
//            std::cout<<"Zoom_Value "<<Zoom_Value<<std::endl;
            focal_length=(double)((3.06*Zoom_ind)+3.06);

            tetex=2*atan(1.6/focal_length);
            tetay=2*atan(1.2/focal_length);

        }
        break;

    }
}

void MainWindow::on_Enhancment_clicked()
{
    if(!Enhancment)
    {
        Enhancment=true;
        ui->Enhancment->setText("إيقاف");
        if(ui->Enh_Box->currentIndex()==5)
        {
            ui->Alpha->setEnabled(true);
            ui->Beta->setEnabled(true);
            ui->a_spin->setEnabled(true);
            ui->b_spin->setEnabled(true);
        }
        else
        {
            ui->Alpha->setEnabled(false);
            ui->Beta->setEnabled(false);
            ui->a_spin->setEnabled(false);
            ui->b_spin->setEnabled(false);
        }
        first_enhacment=false;
    }
    else
    {
        Enhancment=false;
        ui->Enhancment->setText("تشغيل");
        if(ui->Enh_Box->currentIndex()==5)
        {
            ui->Alpha->setEnabled(true);
            ui->Beta->setEnabled(true);
            ui->a_spin->setEnabled(true);
            ui->b_spin->setEnabled(true);
        }
        else
        {
            ui->Alpha->setEnabled(false);
            ui->Beta->setEnabled(false);
            ui->a_spin->setEnabled(false);
            ui->b_spin->setEnabled(false);
        }
    }
}

void MainWindow::on_Enh_Box_currentIndexChanged(int index)
{
    if(index==5)
    {
        ui->Alpha->setEnabled(true);
        ui->Beta->setEnabled(true);
        ui->a_spin->setEnabled(true);
        ui->b_spin->setEnabled(true);
    }
    else
    {
        ui->Alpha->setEnabled(false);
        ui->Beta->setEnabled(false);
        ui->a_spin->setEnabled(false);
        ui->b_spin->setEnabled(false);
    }
}

void MainWindow::on_Motion_clicked()
{
    if(!Motion)
    {
        createBGS();
        ui->Motion->setText("إيقاف");
        ui->Motion_Box->setEnabled(false);
        Motion=true;
    }
    else
    {
        destroyBGS();
        ui->Motion->setText("تشغيل");
        ui->Motion_Box->setEnabled(true);
        cv::destroyAllWindows();
        Motion=false;
    }
}

QString MainWindow::getSelectedAlgorithmName()
{

    int row = ui->Motion_Box->currentIndex();
    QModelIndex idx = ui->Motion_Box->model()->index(row, 0); // first column
    QString algorithm_name = idx.data(Qt::DisplayRole).toString();
    return algorithm_name;
}

void MainWindow::createBGS()
{
  QString algorithm_name = getSelectedAlgorithmName();
  bgs = bgslibrary::get_alg(algorithm_name.toStdString());
  bgs->setShowOutput(false);
}

void MainWindow::destroyBGS()
{
  delete bgs;
}

QImage MainWindow::cv2qimage(const cv::Mat &cv_frame)
{
  if (cv_frame.channels() == 3)
    return Mat2QImage(cv_frame);
  else
    return GrayMat2QImage(cv_frame);
}

void MainWindow::processFrame(const cv::Mat &cv_frame)
{
  cv::Mat cv_fg;
  cv::Mat cv_bg;
  tic();
  bgs->process(cv_frame, cv_fg, cv_bg);
  toc();
  cv::imshow("FG",cv_fg);
  cv::imshow("BG",cv_bg);
  cv::Mat img_blob;
  if(blob_tracking)
  {
      blobT = new BlobTracking;
      if(!cv_fg.empty())
      {
          if(cv_fg.channels()==3)
              cv::cvtColor(cv_fg,cv_fg,CV_RGB2GRAY);
          blobT->process(cv_frame, cv_fg, img_blob);
          cv::imshow("BLOBS",img_blob);
      }
  }

//  if(!cv_fg.empty())
//      return cv_fg;
//  else
//      return NULL;

}

void MainWindow::tic()
{
  duration = static_cast<double>(cv::getTickCount());
}

void MainWindow::toc()
{
  duration = (static_cast<double>(cv::getTickCount()) - duration) / cv::getTickFrequency();
  //std::cout << "time(sec):" << std::fixed << std::setprecision(6) << duration << std::endl;
  //std::cout << duration << std::endl;
}

void MainWindow::on_detect_clicked()
{
    if(!detect)
    {
        cv::Mat gray;
        cv::resize(frameorig,gray,cv::Size(720,576));
        cv::cvtColor(gray,gray,CV_RGB2GRAY);
        detector=new CDetector(BackgroundSubtract::ALG_MOG, useLocalTracking, gray);
        detector->SetMinObjectSize(cv::Size(14, 11));
        detect=true;
        ui->detect->setText("إيقاف");
        fps = std::max(1, static_cast<int>(CpThread->capWebam.get(cv::CAP_PROP_FPS) + 0.5));
        fix_tracker=new CTracker (useLocalTracking,
                CTracker::RectsDist,
                CTracker::FilterRect,
                CTracker::MatchHungrian,
                0.2f,                // Delta time for Kalman filter
                0.1f,                // Accel noise magnitude for Kalman filter
                36.0f,               // Distance threshold between two frames
                fps,                 // Maximum allowed skipped frames
                5 * fps              // Maximum trace length
                );
    }
    else
    {
        detector->~CDetector();
        detect=false;
        ui->detect->setText("كشف");
        fix_tracker->~CTracker();
    }
}

void MainWindow::on_Track_clicked()
{
    if(!TCP_open)
    {
        if(!track)
        {
            track=true;
            myosd = new SeaProjectsOSD();
            statictracker=Trackerlibrary::get_alg(Trackerlibrary::Algonumber[ui->Track_box->currentIndex()]);
            if(!detect)
            {
                if(!init_track)
                    Selected=new cv::Rect(frameorig.cols/2-initWinWidth/2,frameorig.rows/2-initWinWidth*3/8,
                                          initWinWidth,initWinWidth*3/4);
            }
            std::cout<<Selected->area()<<std::endl;
            statictracker.InitTracker_(frameorig, *Selected);
            ui->detect->setEnabled(false);
            ui->Track_box->setEnabled(false);
            ui->Track->setText("إيقاف");
            ScreenCursor.x=frameorig.cols/2;
            ScreenCursor.y=frameorig.rows/2;
            timer2->tic();

        }
        else
        {
            track=false;
            ui->detect->setEnabled(true);
            ui->Track_box->setEnabled(true);
            ui->Track->setText("ملاحقة");
            statictracker.deleteTracker();
        }
    }
    else
    {
        if(!track)
        {
            track=true;
            int32_t data = 0;
            uint8_t cmd=0x111;
            Write(cmd, (uint8_t *)&data);
            ui->detect->setEnabled(false);
            ui->Track->setText("إيقاف");
            ui->Windo_m->setEnabled(false);
            ui->Windo_p->setEnabled(false);
        }
        else
        {
            track=false;
            int32_t data = 0;
            uint8_t cmd=0x111;
            Write(cmd, (uint8_t *)&data);
            ui->detect->setEnabled(true);
            ui->Track->setText("ملاحقة");
            ui->Windo_m->setEnabled(true);
            ui->Windo_p->setEnabled(true);
        }
    }
}

void MainWindow::on_check_track_clicked(bool checked)
{
    if(!TCP_open)
    {
        if(checked)
        {
            Selected=new cv::Rect(frameorig.cols/2-initWinWidth/2,frameorig.rows/2-initWinWidth*3/8
                                  ,initWinWidth,initWinWidth*3/4);
            myosd = new SeaProjectsOSD();
            ScreenCursor.x=frameorig.cols/2;
            ScreenCursor.y=frameorig.rows/2;
            init_track=true;
            ui->Windo_m->setEnabled(true);
            ui->Windo_p->setEnabled(true);
        }
        else
        {
            init_track=false;
            ui->Windo_m->setEnabled(false);
            ui->Windo_p->setEnabled(false);
        }
    }
    else
    {
        if(checked)
        {
            TCP_track=true;
            init_track=true;
            Selected=new cv::Rect(frameorig.cols/2-initWinWidth/2,frameorig.rows/2-initWinWidth*3/8,
                                  initWinWidth,initWinWidth*3/4);
            ui->Windo_m->setEnabled(true);
            ui->Windo_p->setEnabled(true);
        }
        else
        {
            TCP_track=false;
            ui->Windo_m->setEnabled(false);
            ui->Windo_p->setEnabled(false);
        }
    }
}

void MainWindow::on_change_algo_clicked()
{
    algo=true;
    int32_t data = 0;
    uint8_t cmd=0x111;
    Write(cmd, (uint8_t *)&data);
}

void MainWindow::on_track_blob_clicked(bool checked)
{
    blob_tracking=checked;
    cv::destroyAllWindows();
}



void MainWindow::on_Windo_p_pressed()
{
    if(!TCP_open)
    {
        Selected->width++;
        if ((Selected->width) > 128)
            Selected->width = 128;
        Selected->height = Selected->width * 3 / 4;
    }
    else
    {
        winup=true;
        int32_t data = 0;
        uint8_t cmd=0x111;
        Write(cmd, (uint8_t *)&data);
    }
}

void MainWindow::on_Windo_p_released()
{
    winup=false;
    int32_t data = 0;
    uint8_t cmd=0x111;
    Write(cmd, (uint8_t *)&data);
}

void MainWindow::on_Windo_m_pressed()
{
    if(!TCP_open)
    {
        Selected->width--;
        if ((Selected->width) <16)
            Selected->width = 16;
        Selected->height = Selected->width * 3 / 4;
    }
    else
    {
        windn=true;
        int32_t data = 0;
        uint8_t cmd=0x111;
        Write(cmd, (uint8_t *)&data);
    }
}

void MainWindow::on_Windo_m_released()
{
    windn=false;
    int32_t data = 0;
    uint8_t cmd=0x111;
    Write(cmd, (uint8_t *)&data);
}

void MainWindow::on_CameraIndex_returnPressed()
{
    ui->RunCamera->animateClick();
}

