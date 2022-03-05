#ifndef CELL_H
#define CELL_H


#define BATT_HEIGHT (100)
#define BATT_WIDTH   (50)

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLCDNumber>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include<QTime>
class cell
{

public:
    cell();

private:
        void Init_UI();       
public:


    const QString styleRed = "background-color: rgb(85,0, 0);color: rgb(255, 255, 255);";
    const QString styleGreen = "background-color: rgb(0, 85, 0);color: rgb(255, 255, 255);";
    const QString stylefont = "font: 11pt MS Shell Dlg 2;";

    bool Status_Charging;
    bool Status_Log;
    bool Flag_LowVoltage;
    float volt;
    float current;
    float capacity;
    float Resistance=9.9;

    clock_t timestart,timeend;
    uint16_t raw_v;
    QPixmap chrg,dischrg,low;

    void setbattery_chrg();
    void setbattery_dischrg();
    void setbattery_lowvoltage();
    void logging();
    void UpdateCapacity();


    // UI Elements

    QGroupBox *gb_main;
    QLabel *pic_batt;
    QLabel *voltage;
    QLabel *cur;
    QLabel *time;
    QLabel *cap;

    QLCDNumber *lcd_volt;
    QLCDNumber *lcd_curr;
    QLCDNumber *lcd_time;
    QLCDNumber *lcd_capacity;

    QPushButton *pb_mode;
    //QPushButton *pb_log;

    int mypcb;
    int mycell;

    uint32_t time_sec;
    uint32_t time_min;

    bool ADD_CAPACITY;

};

#endif // CELL_H
