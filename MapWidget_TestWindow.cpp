
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "MapWidget_TestWindow.h"

QTestWin::QTestWin(QWidget *parent,double _lat,double _lon) :    QWidget(parent)
{
    // create configure obj
    m_conf = new QSettings("C:\\data\\demo.ini", QSettings::IniFormat);
    lat=_lat;
    lng=_lon;
    // setup layout
    setupLayout();

    // set window title
    setWindowTitle("MapWidget demo");
}

int QTestWin::setupLayout(void)
{
    // create OPMapWidget
    m_mapWidget = new MapWidget(this);


    int     zoom;

    m_conf->setValue("mapWidget_home_lat", lat);
    m_conf->setValue("mapWidget_home_lng", lng);
    zoom = m_conf->value("lastZoom", 18).toInt();

    internals::PointLatLng p(lat, lng);
    m_mapWidget->SetCurrentPosition(p);
    m_mapWidget->SetZoom(zoom);
    m_mapWidget->setConf(m_conf);

    connect(m_mapWidget, SIGNAL(zoomChanged(int)),
            this, SLOT(mapWidget_zoomChanged(int)));
    connect(m_mapWidget, SIGNAL(GOLOC(double)),
            this, SLOT(gotoloc(double)));
//    connect(m_mapWidget, SIGNAL(mouseMove(QMouseEvent*)),
//            this, SLOT(mapWidget_mouseMoveEvent(QMouseEvent*)));

    // set default UAV item
    m_uav = NULL;

    pan_value=0;
    zoom_value=0;

    // create right pannel
//    QWidget *wLeftPanel = new QWidget(this);
//    wLeftPanel->setMinimumWidth(120);

//    m_btnFatchMap = new QPushButton(wLeftPanel);
//    m_btnFatchMap->setText("Cache map");
//    m_btnFatchMap->setGeometry(10, 10, 90, 30);
//    connect(m_btnFatchMap, SIGNAL(clicked()), this, SLOT(actFatchMap()));

//    m_cbMoveUAV = new QCheckBox("Move UAV", wLeftPanel);
//    m_cbMoveUAV->setGeometry(10, 60, 90, 30);
//    connect(m_cbMoveUAV, SIGNAL(clicked(bool)), this, SLOT(moveUAVStateChanged(bool)));


    // overall layout
    QHBoxLayout *hl = new QHBoxLayout(this);
    this->setLayout(hl);

    hl->addWidget(m_mapWidget, 1);
//    hl->addWidget(wLeftPanel, 0);


    this->startTimer(30);

    return 0;
}

void QTestWin::gotoloc(double a)
{
    emit locgo(a);
}

void QTestWin::actFatchMap(void)
{
    internals::RectLatLng  rect;

    rect = m_mapWidget->SelectedArea();
    if( rect.IsEmpty() ) {
        QMessageBox msgbox(QMessageBox::Warning,
                           "Warning", "Please select an area first!");
        msgbox.exec();

        return;
    }

    m_mapWidget->RipMap();
}


void QTestWin::moveUAVStateChanged(bool state)
{
    if( m_cbMoveUAV->checkState() == Qt::Checked ) {
        m_uav = m_mapWidget->AddUAV(0);
    } else {
        m_mapWidget->DeleteUAV(0);
        m_uav = NULL;
    }
}

void QTestWin::mapWidget_zoomChanged(int newZoom)
{
    printf(">>> zoom to: %d\n", newZoom);
}

void QTestWin::mapWidget_mouseMoveEvent(QMouseEvent *event)
{
    if( m_cbMoveUAV->checkState() == Qt::Checked ) {
        internals::PointLatLng p;

        p = m_mapWidget->currentMousePosition();
        printf("p  = %f %f\n", p.Lat(), p.Lng());

        if( m_uav != NULL ) m_uav->SetUAVPos(p, 460);
    }
}

void QTestWin::timerEvent(QTimerEvent *event)
{

}
void QTestWin::TargetDrawing(double lng,double lat)
{
    m_mapWidget->actWaypoint_addTarget(lng,lat);
}
void QTestWin::save_targets()
{
    m_mapWidget->actWaypoint_save_();
}
void QTestWin::PanDrawing(double pan,double zoom)
{
    double d = 5; // km
    if(m_uav)
    {
        m_mapWidget->DeleteUAV(0);
        m_mapWidget->DeleteUAV(1);
        m_uav = NULL;
    }
    m_uav = m_mapWidget->AddUAV(0);
    double lat_r=lat*M_PI/180;
    double lng_r=lng*M_PI/180;
    double pan_r0=(pan-zoom)*M_PI/180;
    double pan_r1=(pan+zoom)*M_PI/180;
    double xx=lat+(d/6378.1)*cos(pan_r0);
    double yy=lng+(d/6378.1)*sin(pan_r0);
    double xx1=lat+(d/6378.1)*cos(pan_r1);
    double yy1=lng+(d/6378.1)*sin(pan_r1);

//    double lat2=asin(sin(lat_r)*cos(d/6378.1)
//                     +cos(lat_r)*sin(d/6378.1)*cos(pan_r));
//    double lng2=lng_r+atan2(sin(pan_r)*sin(d/6378.1)*cos(lat),
//                          cos(d/6378.1)-sin(lat_r)*sin(lat2));
//    lng2=fmod(lng2+3*M_PI,2*M_PI) - M_PI;
//    internals::PointLatLng p_p(lat2*180/M_PI,lng2*180/M_PI);

    internals::PointLatLng p_p1(xx,yy);
    internals::PointLatLng p_h(lat,lng);
    internals::PointLatLng p_p2(xx1,yy1);
    m_uav->SetUAVPos(p_p1, 10);
    m_uav->SetUAVPos(p_h, 10);
    m_uav = m_mapWidget->AddUAV(1);
    m_uav->SetUAVPos(p_p2, 10);
    m_uav->SetUAVPos(p_h, 10);
}
