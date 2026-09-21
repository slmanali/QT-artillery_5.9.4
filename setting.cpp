#include "setting.h"
#include "ui_Setting.h"
#include <QThread>

Setting::Setting(QWidget *parent) : QMainWindow(parent) , ui(new Ui::Setting)
{
    ui->setupUi(this);
    ui->result_home->setVisible(false);
    ui->tabWidget->setCurrentIndex(0);
    ui->norh_labl->setText("نقطة علام");
    ui->n_deg_label->setText("العرض");
    ui->m_lat_label->setText("الطول");
    home_=true;
}

void Setting::on_Home_Mode_toggled(bool checked)
{
    if(checked)
    {
        home_=true;
        north_=false;
        mark_=false;
        ui->result_home->setVisible(false);
        ui->tabWidget->setCurrentIndex(0);
        ui->norh_labl->setText("نقطة علام");
        ui->n_deg_label->setText("العرض");
        ui->m_lat_label->setText("الطول");
        ui->m_lat_label->setVisible(true);
        ui->mark_lat->setVisible(true);
        ui->NorthCalc_bt->setText("حساب الشمال");
        ui->NorthCalc_bt->setVisible(true);
        ui->North_Value->setVisible(true);
    }
}

void Setting::on_North_Mode_toggled(bool checked)
{
    if(checked)
    {
        north_=true;
        home_=false;
        mark_=false;
        ui->result_home->setVisible(false);
        ui->tabWidget->setCurrentIndex(0);
        ui->norh_labl->setText("الشمال");
        ui->n_deg_label->setText("القيمة");
        ui->m_lat_label->setVisible(false);
        ui->mark_lat->setVisible(false);
        ui->NorthCalc_bt->setText("حساب الشمال");
        ui->NorthCalc_bt->setVisible(false);
        ui->North_Value->setVisible(false);
    }
}

void Setting::on_Mark_Mode_toggled(bool checked)
{
    if(checked)
    {
        north_=false;
        home_=false;
        mark_=true;
        ui->result_home->setVisible(true);
        ui->tabWidget->setCurrentIndex(1);
        ui->NorthCalc_bt->setText("حساب الراصد");
        ui->NorthCalc_bt->setVisible(true);
        ui->North_Value->setVisible(true);
    }
}

void Setting::on_NorthCalc_bt_clicked()
{
    if(home_)
    {
        if(ui->home_lon->text().toStdString()>"9" || ui->home_lat->text().toStdString()>"9"
                || ui->north_degree->text().toStdString()>"9" || ui->mark_lat->text().toStdString()>"9")
        {
            QMessageBox::critical(this,"تحذير",
                            "إدخال خاطئ",
                            QMessageBox::NoIcon,
                            QMessageBox::Ok );
            return;
        }
//        if(ui->home_lon->text().toDouble()<0 || ui->home_lat->text().toDouble()<0
//                || ui->north_degree->text().toDouble()<0 || ui->mark_lat->text().toDouble()<0)
//        {
//            QMessageBox::critical(this,"تحذير",
//                            "إدخال خاطئ",
//                            QMessageBox::NoIcon,
//                            QMessageBox::Ok );
//            return;
//        }
        if(ui->home_lon->text().toStdString().length()==0 || ui->home_lat->text().toStdString().length()==0
                || ui->north_degree->text().toStdString().length()==0 || ui->mark_lat->text().toStdString().length()==0)
        {
            QMessageBox::critical(this,"تحذير",
                            "إدخال فارغ",
                            QMessageBox::NoIcon,
                            QMessageBox::Ok );
            return;
        }
        double R = 6371000; // km

        lat_home=ui->home_lon->text();
        lon_home=ui->home_lat->text();

        double lat=ui->north_degree->text().toDouble();
        double lon=ui->mark_lat->text().toDouble();

        double phi1 = lat_home.toDouble() * (M_PI) / 180.0;
        double phi2 = (lat) * (M_PI) / 180.0;
        double dphi = (lat - lat_home.toDouble()) * (M_PI) / 180.0;
        double dlambda = (lon - lon_home.toDouble()) * (M_PI) / 180.0;
        double a = sin(dphi / 2) * sin(dphi / 2) +
                            cos(phi1) * cos(phi2) *
                            sin(dlambda / 2) * sin(dlambda / 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double b = atan2(sin(dlambda) * cos(phi2), cos(phi1) * sin(phi2) -
                      cos(dlambda) * cos(phi2) * sin(phi1));

        double bb=(b*180.0/M_PI);
        if(bb<0)
            bb+=360;
        bearing=QString::number(bb).rightJustified(6,' ');
        ui->North_Value->setText(bearing);
    }
    if(mark_)
    {
        if(ui->mark1_distance->text().toStdString()>"9" || ui->mark2_distance->text().toStdString()>"9"
                || ui->mark1_lon->text().toStdString()>"9" || ui->mark1_lat->text().toStdString()>"9"
                || ui->mark2_lon->text().toStdString()>"9" || ui->mark2_lat->text().toStdString()>"9")
        {
            QMessageBox::critical(this,"تحذير",
                            "إدخال خاطئ",
                            QMessageBox::NoIcon,
                            QMessageBox::Ok );
            return;
        }
//        if(ui->mark1_distance->text().toDouble()<0 || ui->mark2_distance->text().toDouble()<0
//                || ui->mark1_lon->text().toDouble()<0 || ui->mark1_lat->text().toDouble()<0
//                || ui->mark2_lon->text().toDouble()<0 || ui->mark2_lat->text().toDouble()<0)
//        {
//            QMessageBox::critical(this,"تحذير",
//                            "إدخال خاطئ",
//                            QMessageBox::NoIcon,
//                            QMessageBox::Ok );
//            return;
//        }
        if(ui->mark1_distance->text().toStdString().length()==0 || ui->mark2_distance->text().toStdString().length()==0
                || ui->mark1_lon->text().toStdString().length()==0 || ui->mark1_lat->text().toStdString().length()==0
                || ui->mark2_lon->text().toStdString().length()==0 || ui->mark2_lat->text().toStdString().length()==0)
        {
            QMessageBox::critical(this,"تحذير",
                            "إدخال فارغ",
                            QMessageBox::NoIcon,
                            QMessageBox::Ok );
            return;
        }
        double lat1=ui->mark1_lon->text().toDouble();
        double lat2=ui->mark2_lon->text().toDouble();

        double lon1=ui->mark1_lat->text().toDouble();
        double lon2=ui->mark2_lat->text().toDouble();

        double R1 = 6371; // km
        double dLat = (lat2-lat1) * (M_PI) / 180.0;  // deg2rad below
        double dLon = (lon2-lon1)* (M_PI) / 180.0;
        double aa = sin(dLat/2) * sin(dLat/2) +
        cos((lat1)* (M_PI) / 180.0) * cos((lat2)*(M_PI) / 180.0) *
        sin(dLon/2) * sin(dLon/2)
        ;
        double cc = 2 * atan2(sqrt(aa), sqrt(1-aa));

        double d1=R1 * cc;

        double d2=ui->mark1_distance->text().toDouble();
        double d3=ui->mark2_distance->text().toDouble();

        double phi= acos((pow(d1,2)+pow(d2,2)-pow(d3,2))/(2*d1*d2));

        double phi11= acos((pow(d1,2)+pow(d3,2)-pow(d2,2))/(2*d1*d3));
        double Observer_x=lon1+((d2/d1)*(cos(phi)*(lon2-lon1)-sin(phi)*(lat2-lat1)));
        double Observer_y=lat1+((d2/d1)*(sin(phi)*(lon2-lon1)+cos(phi)*(lat2-lat1)));

        double Observer_x1=lon2+((d3/d1)*(cos(phi11)*(lon1-lon2)-sin(phi11)*(lat1-lat2)));
        double Observer_y1=lat2+((d3/d1)*(sin(phi11)*(lon1-lon2)+cos(phi11)*(lat1-lat2)));

        qDebug()<<Observer_x1;
        qDebug()<<Observer_y1;

        ui->result_home_lat->setText(QString::number(Observer_x).rightJustified(6,' '));
        ui->result_home_lon->setText(QString::number(Observer_y).rightJustified(6,' '));



        lat_home=ui->result_home_lon->text();
        lon_home=ui->result_home_lat->text();

        double lat=ui->mark1_lon->text().toDouble();
        double lon=ui->mark1_lat->text().toDouble();

        double R = 6371000; // km
        double phi1 = lat_home.toDouble() * (M_PI) / 180.0;
        double phi2 = (lat) * (M_PI) / 180.0;
        double dphi = (lat - lat_home.toDouble()) * (M_PI) / 180.0;
        double dlambda = (lon - lon_home.toDouble()) * (M_PI) / 180.0;
        double a = sin(dphi / 2) * sin(dphi / 2) +
                            cos(phi1) * cos(phi2) *
                            sin(dlambda / 2) * sin(dlambda / 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double b = atan2(sin(dlambda) * cos(phi2), cos(phi1) * sin(phi2) -
                      cos(dlambda) * cos(phi2) * sin(phi1));

        double bb=(b*180.0/M_PI)+180.0;
        bearing=QString::number(bb).rightJustified(6,' ');
        ui->North_Value->setText(bearing);

    }
}

void Setting::on_NorthAdjust_bt_clicked()
{
    if(north_)
    {
        if(ui->home_lon->text().toStdString()>"9" || ui->home_lat->text().toStdString()>"9"
                || ui->north_degree->text().toStdString()>"9")
        {
            QMessageBox::critical(this,"تحذير",
                            "إدخال خاطئ",
                            QMessageBox::NoIcon,
                            QMessageBox::Ok );
            return;
        }
//        if(ui->home_lon->text().toDouble()<0 || ui->home_lat->text().toDouble()<0
//                || ui->north_degree->text().toDouble()<0 )
//        {
//            QMessageBox::critical(this,"تحذير",
//                            "إدخال خاطئ",
//                            QMessageBox::NoIcon,
//                            QMessageBox::Ok );
//            return;
//        }
        if(ui->home_lon->text().toStdString().length()==0 || ui->home_lat->text().toStdString().length()==0
                || ui->north_degree->text().toStdString().length()==0 )
        {
            QMessageBox::critical(this,"تحذير",
                            "إدخال فارغ",
                            QMessageBox::NoIcon,
                            QMessageBox::Ok );
            return;
        }
        lat_home=ui->home_lon->text();
        lon_home=ui->home_lat->text();
        bearing=ui->north_degree->text();
    }
    if(bearing==" " || lat_home==" " || lon_home==" ")
    {
        QMessageBox::critical(this,"تحذير",
                        "إدخال خاطئ",
                        QMessageBox::NoIcon,
                        QMessageBox::Ok );
        return;
    }
    if(ui->North_Value->text().isEmpty())
    {
        QMessageBox::critical(this,"تحذير",
                        "لا يوجد مدخلات",
                        QMessageBox::NoIcon,
                        QMessageBox::Ok );
        return;
    }
    set_=true;
//    qDebug()<<lat_home;
    this->close();
}

void Setting::on_Upload_bt_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("تحميل الموقع"), ".", tr("ملفات نصية (*.txt)"));
        if(!fileName.isEmpty())
        {
            fileName =QDir::toNativeSeparators (fileName);
            QByteArray file_name1=fileName.toLocal8Bit();

            upload_txt.open(file_name1.data());

            std::string temp;
            upload_txt>> temp;
            upload_txt>> temp;
            upload_txt>> temp;
            if(home_||north_)
                ui->home_lon->setText(QString::fromStdString(temp));
            if(mark_)
                ui->result_home_lon->setText(QString::fromStdString(temp));
            lat_home=QString::fromStdString(temp);
            upload_txt>> temp;
            upload_txt>> temp;
            if(home_||north_)
                ui->home_lat->setText(QString::fromStdString(temp));
            if(mark_)
                ui->result_home_lat->setText(QString::fromStdString(temp));
            lon_home=QString::fromStdString(temp);
            upload_txt>> temp;
            upload_txt>> temp;
            upload_txt>> temp;
            upload_txt>> temp;
            if(mark_ || home_)
                ui->North_Value->setText(QString::fromStdString(temp));
            if(north_)
                ui->north_degree->setText(QString::fromStdString(temp));
            bearing=QString::fromStdString(temp);
//            qDebug()<<bearing;
            QMessageBox::information(this,"تنويه",
                    "تم الحصول على المعطيات",
                    QMessageBox::NoIcon,
                    QMessageBox::Ok );
            upload_txt.close();
        }
}

void Setting::on_Save_bt_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("حفظ الموقع"), ".", tr("ملفات نصية (*.txt)"));
        if(!fileName.isEmpty()){
            fileName =QDir::toNativeSeparators (fileName);
            QByteArray file_name1=fileName.toLocal8Bit();

            save_txt.open(file_name1.data());
            save_txt<<"احداثيات الراصد"<<"\n";
            if(home_ || north_)
            {
                save_txt<<ui->home_lon->text().toStdString()<<" :الطول"<<"\n";
                save_txt<<ui->home_lat->text().toStdString()<<" :العرض"<<"\n";
            }
            if(mark_)
            {
                save_txt<<ui->result_home_lon->text().toStdString()<<" :الطول"<<"\n";
                save_txt<<ui->result_home_lat->text().toStdString()<<" :العرض"<<"\n";
            }
            save_txt<<"زاوية الشمال"<<"\n";
            if(home_ || mark_)
                save_txt<<ui->North_Value->text().toStdString();
            if(north_)
                save_txt<<ui->north_degree->text().toStdString();
            QMessageBox::information(this,"تنويه",
                    "تم الحفظ",
                    QMessageBox::NoIcon,
                    QMessageBox::Ok );
            save_txt.close();
        }
}
