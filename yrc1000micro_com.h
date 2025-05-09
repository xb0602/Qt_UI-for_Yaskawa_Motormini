#ifndef YRC1000MICRO_COM_H
#define YRC1000MICRO_COM_H
#include <QObject>
#include <QFile>
#include "udp.h"
#include "yrc1000micro_command.h"
class YRC1000micro_com : public QObject
{
    Q_OBJECT
public:
    explicit YRC1000micro_com(QObject *parent = nullptr);
    ~YRC1000micro_com();
    bool YRC1000microConnect();
    void YRC1000microDisConnect();
    void YRC1000microSetConnection(QHostAddress address,quint16 port);
    void YRC1000microOnServo();
    void YRC1000microOffServo();
    void YRC1000microReadPosition();
    void YRC1000microReadPositionResponse(QByteArray data);
    void YRC1000microReadPulse();
    void YRC1000microReadPulseResponse(QByteArray data);
    void YRC1000microMoveCartesian(quint8 coordinate,quint8 move_type, quint8 speed_type, double speed, QVector<double>* position);
    QVector<double> updateRobotPosition();
    QVector<double> updateRobotPulse();
signals:
    void dataUIRecieveSiUIgnal();
public slots:
    void YRC1000microDataCallback();
private:
    UDP udp_server;
    UDP udp_file_control;
    YRC1000micro_command yrc1000micro_command;
    quint8 request_id_index;
    quint8 response_id_index;
    char request_code[256] = {};
    QHostAddress udp_address;
    quint16 udp_port;
    QByteArray header_to_send;
    QByteArray data_to_send;
    QVector<double> robot_position;
    QVector<double> robot_pulse;
    quint32 load_file_block_num;
    int read_position_type;
};
#endif // YRC1000MICRO_COM_H
