#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <yrc1000micro_com.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_button_connect_clicked();

    void on_button_servo_clicked();

    void on_button_set_pos_clicked();

    void on_button_gohome_clicked();

    void on_slider_dis_mm_valueChanged(int value);

    void on_slider_dis_deg_valueChanged(int value);

    void on_slider_speed_mm_valueChanged(int value);

    void on_slider_speed_deg_valueChanged(int value);

    void on_nega_x_clicked();

    void on_posi_x_clicked();

    void on_nega_y_clicked();

    void on_posi_y_clicked();

    void on_nega_z_clicked();

    void on_posi_z_clicked();

    void on_nega_roll_clicked();

    void on_posi_roll_clicked();

    void on_nega_pitch_clicked();

    void on_posi_pitch_clicked();

    void on_nega_yaw_clicked();

    void on_posi_yaw_clicked();

    void on_button_get_pos_clicked();

    void on_button_get_joints_clicked();

private:
    Ui::MainWindow *ui;
    YRC1000micro_com yrc1000micro_com;
};
#endif // MAINWINDOW_H
