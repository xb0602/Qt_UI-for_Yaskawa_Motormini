#include "yrc1000micro_com.h"
#include "yrc1000micro_command.h"
#include <iostream>
#include <QMessageBox>
YRC1000micro_com::YRC1000micro_com(QObject *parent) : QObject(parent)
{
    request_id_index = 0;
    response_id_index = 0;
    robot_position.append(0);
    robot_position.append(0);
    robot_position.append(0);
    robot_position.append(0);
    robot_position.append(0);
    robot_position.append(0);
    robot_pulse.append(0);
    robot_pulse.append(0);
    robot_pulse.append(0);
    robot_pulse.append(0);
    robot_pulse.append(0);
    robot_pulse.append(0);
    connect(&udp_server, SIGNAL(dataRecieveSignal()), this,
            SLOT(YRC1000microDataCallback()));
}
YRC1000micro_com::~YRC1000micro_com(){
    udp_server.disconnect();
}
bool YRC1000micro_com::YRC1000microConnect(){
    bool connect_satus = udp_server.udpConnect(udp_address,udp_port);
    return connect_satus;
}
void YRC1000micro_com::YRC1000microDisConnect(){
    udp_server.udpDisConnect();
}

void YRC1000micro_com::YRC1000microSetConnection(QHostAddress address,quint16 port){
    udp_address = address;
    udp_port = port;
}
void YRC1000micro_com::YRC1000microDataCallback(){
    QByteArray data = udp_server.getUdpData();
    qDebug() << "Received Data: " << data;
    quint8 res_id_index = (quint8)data[CMD_REQUEST_ID];
    char response_id = request_code[res_id_index];
    qDebug() << "response_id: " << response_id;
    if(response_id == CMD_ID_READ_ROBOT_POS){
        if (read_position_type == READ_POSITION_XYZ)
            YRC1000microReadPositionResponse(data);
        else if (read_position_type == READ_POSITION_PULSE)
            YRC1000microReadPulseResponse(data);
    }
    emit dataUIRecieveSiUIgnal();
}
void YRC1000micro_com::YRC1000microOnServo(){
    QByteArray data = yrc1000micro_command.setServoOn(request_id_index);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_SERVO_ON;
    request_id_index ++;
}
void YRC1000micro_com::YRC1000microOffServo(){
    QByteArray data = yrc1000micro_command.setServoOff(request_id_index);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_SERVO_ON;
    request_id_index ++;
}
void YRC1000micro_com::YRC1000microReadPosition(){
    QByteArray data = yrc1000micro_command.readRobotPosition(request_id_index);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_READ_ROBOT_POS;
    read_position_type = READ_POSITION_XYZ;
    request_id_index ++;
}
void YRC1000micro_com::YRC1000microReadPulse() {
    QByteArray data = yrc1000micro_command.readRobotPulse(request_id_index);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_READ_ROBOT_POS;
    read_position_type = READ_POSITION_PULSE;
    request_id_index ++;
}
void YRC1000micro_com::YRC1000microReadPositionResponse(QByteArray data){
    qint32 x_axis = 0;
    qint32 y_axis = 0;
    qint32 z_axis = 0;
    qint32 roll_angle = 0;
    qint32 pitch_angle = 0;
    qint32 yaw_angle = 0;
    x_axis = ((quint32)(quint8)data[DATA_X_AXIS+3])<<24 |
             ((quint32)(quint8)data[DATA_X_AXIS+2])<<16 |
             ((quint32)(quint8)data[DATA_X_AXIS+1])<<8 | (quint32)(quint8)data[DATA_X_AXIS];
    y_axis = ((quint32)(quint8)data[DATA_Y_AXIS+3])<<24 |
             ((quint32)(quint8)data[DATA_Y_AXIS+2])<<16 |
             ((quint32)(quint8)data[DATA_Y_AXIS+1])<<8 | (quint32)(quint8)data[DATA_Y_AXIS];
    z_axis = ((quint32)(quint8)data[DATA_Z_AXIS+3])<<24 |
             ((quint32)(quint8)data[DATA_Z_AXIS+2])<<16 |
             ((quint32)(quint8)data[DATA_Z_AXIS+1])<<8 | (quint32)(quint8)data[DATA_Z_AXIS];
    roll_angle = ((quint32)(quint8)data[DATA_ROLL_ANGLE+3])<<24 |
                 ((quint32)(quint8)data[DATA_ROLL_ANGLE+2])<<16 |
                 ((quint32)(quint8)data[DATA_ROLL_ANGLE+1])<<8 |
                 (quint32)(quint8)data[DATA_ROLL_ANGLE];
    pitch_angle = ((quint32)(quint8)data[DATA_PITCH_ANGLE+3])<<24 |
                  ((quint32)(quint8)data[DATA_PITCH_ANGLE+2])<<16 |
                  ((quint32)(quint8)data[DATA_PITCH_ANGLE+1])<<8 |
                  (quint32)(quint8)data[DATA_PITCH_ANGLE];
    yaw_angle = ((quint32)(quint8)data[DATA_YAW_ANGLE+3])<<24 |
                ((quint32)(quint8)data[DATA_YAW_ANGLE+2])<<16 |
                ((quint32)(quint8)data[DATA_YAW_ANGLE+1])<<8 |
                (quint32)(quint8)data[DATA_YAW_ANGLE];
    robot_position[0]=(x_axis/1000.0);
    robot_position[1]=(y_axis/1000.0);
    robot_position[2]=(z_axis/1000.0);
    robot_position[3]=(roll_angle/10000.0);
    robot_position[4]=(pitch_angle/10000.0);
    robot_position[5]=(yaw_angle/10000.0);
}
void YRC1000micro_com::YRC1000microReadPulseResponse(QByteArray data) {
    qint32 j1 = 0;
    qint32 j2 = 0;
    qint32 j3 = 0;
    qint32 j4 = 0;
    qint32 j5 = 0;
    qint32 j6 = 0;
    j1 = ((quint32)(quint8)data[DATA_X_AXIS+3])<<24 |
         ((quint32)(quint8)data[DATA_X_AXIS+2])<<16 |
         ((quint32)(quint8)data[DATA_X_AXIS+1])<<8 | (quint32)(quint8)data[DATA_X_AXIS];
    j2 = ((quint32)(quint8)data[DATA_Y_AXIS+3])<<24 |
         ((quint32)(quint8)data[DATA_Y_AXIS+2])<<16 |
         ((quint32)(quint8)data[DATA_Y_AXIS+1])<<8 | (quint32)(quint8)data[DATA_Y_AXIS];
    j3 = ((quint32)(quint8)data[DATA_Z_AXIS+3])<<24 |
         ((quint32)(quint8)data[DATA_Z_AXIS+2])<<16 |
         ((quint32)(quint8)data[DATA_Z_AXIS+1])<<8 | (quint32)(quint8)data[DATA_Z_AXIS];
    j4 = ((quint32)(quint8)data[DATA_ROLL_ANGLE+3])<<24 |
         ((quint32)(quint8)data[DATA_ROLL_ANGLE+2])<<16 |
         ((quint32)(quint8)data[DATA_ROLL_ANGLE+1])<<8 |
         (quint32)(quint8)data[DATA_ROLL_ANGLE];
    j5 = ((quint32)(quint8)data[DATA_PITCH_ANGLE+3])<<24 |
         ((quint32)(quint8)data[DATA_PITCH_ANGLE+2])<<16 |
         ((quint32)(quint8)data[DATA_PITCH_ANGLE+1])<<8 |
         (quint32)(quint8)data[DATA_PITCH_ANGLE];
    j6 = ((quint32)(quint8)data[DATA_YAW_ANGLE+3])<<24 |
         ((quint32)(quint8)data[DATA_YAW_ANGLE+2])<<16 |
         ((quint32)(quint8)data[DATA_YAW_ANGLE+1])<<8 |
         (quint32)(quint8)data[DATA_YAW_ANGLE];
    robot_pulse[0]=j1;
    robot_pulse[1]=j2;
    robot_pulse[2]=j3;
    robot_pulse[3]=j4;
    robot_pulse[4]=j5;
    robot_pulse[5]=j6;
}
QVector<double> YRC1000micro_com::updateRobotPosition(){
    return robot_position;
}
QVector<double> YRC1000micro_com::updateRobotPulse(){
    return robot_pulse;
}
void YRC1000micro_com::YRC1000microMoveCartesian(quint8 coordinate,quint8
                                                                        move_type, quint8 speed_type, double speed, QVector<double>* position){
    QByteArray data = yrc1000micro_command.setRobotPositionCartesian(
        request_id_index, coordinate, move_type, speed_type, speed, position);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_MOVE_ROBOT_CARTESIAN;
    request_id_index ++;
}
