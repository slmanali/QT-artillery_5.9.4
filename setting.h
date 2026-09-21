#ifndef SETTING_H
#define SETTING_H

#include <QMainWindow>
#include <QtCore>
#include <QPainter>

#include <qmessagebox.h>
//#include "newSerialHeaders.h"

#include "axis_data.h"
#include <fstream>
#include <QMessageBox>
#include <QByteArray>
#include "qmath.h"
#include <unistd.h>
#include <QFileDialog>
#include <QDebug>
#include <limits>

constexpr double precision{ 1e-10 };

namespace Ui {
class Setting;
}
class Setting : public QMainWindow
{
    Q_OBJECT
public:
    explicit Setting(QWidget *parent = 0);

    QString bearing;
    QString lat_home ;
    QString lon_home ;
    bool home_=false;
    bool north_=false;
    bool mark_=false;
    bool set_=false;

signals:

public slots:

private slots:


    void on_Home_Mode_toggled(bool checked);

    void on_North_Mode_toggled(bool checked);

    void on_Mark_Mode_toggled(bool checked);

    void on_NorthCalc_bt_clicked();

    void on_NorthAdjust_bt_clicked();

    void on_Upload_bt_clicked();

    void on_Save_bt_clicked();

private:
    Ui::Setting *ui;
    std::ifstream upload_txt;
    std::ofstream save_txt;

};

#endif // SETTING_H
