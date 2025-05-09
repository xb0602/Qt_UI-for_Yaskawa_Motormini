    #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QHostAddress>
#include <QSlider>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


    void MainWindow::on_button_connect_clicked()
    {
        if(ui->button_connect->text() == "Connect"){
            QHostAddress udp_address;
            quint16 udp_port;
            QString ip_string = ui->txt_ip->text();
            QStringList ip_list = ip_string.split(".");
            quint32 ip_int32 = (ip_list.at(0).toUInt() << 24) |
                               (ip_list.at(1).toUInt() << 16) | (ip_list.at(2).toUInt() << 8) |
                               ip_list.at(3).toUInt();
            udp_address.setAddress(ip_int32);
            udp_port = ui->txt_port->text().toUShort();
            yrc1000micro_com.YRC1000microSetConnection(udp_address,udp_port);
            ui->button_connect->setText("Disconnect");
            yrc1000micro_com.YRC1000microConnect();
        }
        else if(ui->button_connect->text() == "Disconnect"){
            ui->button_connect->setText("Connect");
            yrc1000micro_com.YRC1000microDisConnect();
        }
    }

    void MainWindow::on_button_servo_clicked()
    {
        if(ui->button_servo->text() == "Servo On"){
            yrc1000micro_com.YRC1000microOnServo();
            ui->button_servo->setText("Servo Off");
        }
        else if(ui->button_servo->text() == "Servo Off"){
            yrc1000micro_com.YRC1000microOffServo();
            ui->button_servo->setText("Servo On");
        }
    }



    void MainWindow::on_button_set_pos_clicked()
    {
        double set_speed = ui->txt_setSpeed->text().toDouble();
        QVector<double> set_position;
            set_position.append(ui->txt_setX->text().toDouble());
            set_position.append(ui->txt_setY->text().toDouble());
            set_position.append(ui->txt_setZ->text().toDouble());
            set_position.append(ui->txt_setRoll->text().toDouble());
            set_position.append(ui->txt_setPitch->text().toDouble());
            set_position.append(ui->txt_setYaw->text().toDouble());

            if(ui->rbtn_movj->isChecked()){
                yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                           CMD_HEADER_MOVE_INSTANCE_LINK_ABSOLUTE,CMD_DATA_MOVE_SPEED_TYPE_LINK,set_speed,&set_position);
            }
            else if(ui->rbtn_movl->isChecked()){
                yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                           CMD_HEADER_MOVE_INSTANCE_STRAIGHT_ABSOLUTE,CMD_DATA_MOVE_SPEED_TYPE_V_SPEED,set_speed,&set_position);
            }
            else if(ui->rbtn_movi->isChecked()){
                yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                           CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
            }
        }


    void MainWindow::on_button_get_pos_clicked()
    {
            yrc1000micro_com.YRC1000microReadPosition();
            yrc1000micro_com.YRC1000microDataCallback();

            QVector<double> position = yrc1000micro_com.updateRobotPosition();
            ui->txt_get_X->setText(QString::number(position[0]));
            ui->txt_get_Y->setText(QString::number(position[1]));
            ui->txt_get_Z->setText(QString::number(position[2]));
            ui->txt_get_Roll->setText(QString::number(position[3]));
            ui->txt_get_Pitch->setText(QString::number(position[4]));
            ui->txt_get_Yaw->setText(QString::number(position[5]));
        }


    void MainWindow::on_button_gohome_clicked()
    {
        double set_speed = 10;
        QVector<double> set_position;
        set_position.append(185);
        set_position.append(0); //6.9 min
        set_position.append(80);
        set_position.append(180);
        set_position.append(0);
        set_position.append(0);
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                       CMD_HEADER_MOVE_INSTANCE_LINK_ABSOLUTE,CMD_DATA_MOVE_SPEED_TYPE_LINK,set_speed,&set_position);

    }


    void MainWindow::on_slider_dis_mm_valueChanged(int value)
    {
        ui->dis_mm->setText(QString::number(value));
    }


    void MainWindow::on_slider_dis_deg_valueChanged(int value)
    {
        ui->dis_deg->setText(QString::number(value));
    }


    void MainWindow::on_slider_speed_mm_valueChanged(int value)
    {
        ui->speed_mm->setText(QString::number(value));
    }


    void MainWindow::on_slider_speed_deg_valueChanged(int value)
    {
        ui->speed_deg->setText(QString::number(value));
    }



    void MainWindow::on_nega_x_clicked()
    {
        double set_speed = ui->speed_mm->text().toDouble();
        QVector<double> set_position;
        set_position.append(-ui->dis_mm->text().toDouble());
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                   CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
    }


    void MainWindow::on_posi_x_clicked()
    {
        double set_speed = ui->speed_mm->text().toDouble();
        QVector<double> set_position;
        set_position.append(ui->dis_mm->text().toDouble());
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                   CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
    }




    void MainWindow::on_nega_y_clicked()
    {
        double set_speed = ui->speed_mm->text().toDouble();
        QVector<double> set_position;
        set_position.append(0);
        set_position.append(-ui->dis_mm->text().toDouble());
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                   CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
    }


    void MainWindow::on_posi_y_clicked()
    {
        double set_speed = ui->speed_mm->text().toDouble();
        QVector<double> set_position;
        set_position.append(0);
        set_position.append(ui->dis_mm->text().toDouble());
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                   CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
    }


    void MainWindow::on_nega_z_clicked()
    {
        double set_speed = ui->speed_mm->text().toDouble();
        QVector<double> set_position;
        set_position.append(0);
        set_position.append(0);
        set_position.append(-ui->dis_mm->text().toDouble());
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                   CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
    }


    void MainWindow::on_posi_z_clicked()
    {
        double set_speed = ui->speed_mm->text().toDouble();
        QVector<double> set_position;
        set_position.append(0);
        set_position.append(0);
        set_position.append(ui->dis_mm->text().toDouble());
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                   CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
    }



    void MainWindow::on_nega_roll_clicked()
    {
        double set_speed = ui->speed_deg->text().toDouble();
        QVector<double> set_position;
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(-ui->dis_deg->text().toDouble());
        set_position.append(0);
        set_position.append(0);
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                   CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
    }


    void MainWindow::on_posi_roll_clicked()
    {
        double set_speed = ui->speed_deg->text().toDouble();
        QVector<double> set_position;
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(ui->dis_deg->text().toDouble());
        set_position.append(0);
        set_position.append(0);
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                   CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
    }



    void MainWindow::on_nega_pitch_clicked()
    {
        double set_speed = ui->speed_deg->text().toDouble();
        QVector<double> set_position;
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(-ui->dis_deg->text().toDouble());
        set_position.append(0);
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                   CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
    }


    void MainWindow::on_posi_pitch_clicked()
    {
        double set_speed = ui->speed_deg->text().toDouble();
        QVector<double> set_position;
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(ui->dis_deg->text().toDouble());
        set_position.append(0);
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                   CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
    }



    void MainWindow::on_nega_yaw_clicked()
    {
        double set_speed = ui->speed_deg->text().toDouble();
        QVector<double> set_position;
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(-ui->dis_deg->text().toDouble());
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                   CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
    }


    void MainWindow::on_posi_yaw_clicked()
    {
        double set_speed = ui->speed_deg->text().toDouble();
        QVector<double> set_position;
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(0);
        set_position.append(ui->dis_deg->text().toDouble());
        yrc1000micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                   CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED,set_speed,&set_position);
    }




    void MainWindow::on_button_get_joints_clicked()
    {
        yrc1000micro_com.YRC1000microReadPulse();
        yrc1000micro_com.YRC1000microDataCallback();
        QVector<double> position = yrc1000micro_com.updateRobotPulse();
        ui->txt_get_J1->setText(QString::number(position[0]*30.0/34816.0));     //S
        ui->txt_get_J2->setText(QString::number(position[1]*90.0/102400.0));    //L
        ui->txt_get_J3->setText(QString::number(position[2]*90.0/51200.0));     //U
        ui->txt_get_J4->setText(QString::number(position[3]*30.0/10204.0));     //R
        ui->txt_get_J5->setText(QString::number(position[4]*30.0/10204.0));     //B
        ui->txt_get_J6->setText(QString::number(position[5]*30.0/10204.0));     //T
    }

