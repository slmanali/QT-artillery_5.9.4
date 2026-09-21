#ifndef QTESTWIN_H
#define QTESTWIN_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>

#include <mapwidget/opmapwidget.h>
#include "MapWidget.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class QTestWin : public QWidget
{
    Q_OBJECT

public:
    explicit QTestWin(QWidget *parent = 0);
    explicit QTestWin(QWidget *parent = 0,double a=0,double b=0);
    double  lat, lng;
    virtual int setupLayout(void);
    
signals:
    void locgo(double);
    
public slots:
    void actFatchMap(void);
    void moveUAVStateChanged(bool state);

    void mapWidget_zoomChanged(int newZoom);
    void mapWidget_mouseMoveEvent(QMouseEvent *event);

    virtual void timerEvent(QTimerEvent *event);

    void gotoloc(double);
    void PanDrawing(double,double);
    void TargetDrawing(double,double);
    void save_targets();

protected:
    QSettings                   *m_conf;
    MapWidget                   *m_mapWidget;
    QPushButton                 *m_btnFatchMap;
    QCheckBox                   *m_cbMoveUAV;
    QLabel                      *pan_label;

    mapcontrol::UAVItem         *m_uav;
    double pan_value;
    double zoom_value;
};

#endif // QTESTWIN_H
