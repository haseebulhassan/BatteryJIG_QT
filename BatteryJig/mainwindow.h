#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TOTAL_CELLS (30)
#define SerialRx_Packet_Length (100)
#define SerialTx_Packet_Length (10)

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QElapsedTimer>
#include "cell.h"
#include <QtSerialPort/QSerialPort>
#include <QIODevice>
#include <QtMath>
#include "math.h"
#include <QSerialPortInfo>
#include <QBitArray>
#include "ledindicator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();
    void on_pbmode_clicked();
   // void on_pblog_clicked();

    void onSerialData();
    void on_pb_Refresh_clicked();

    void on_charge_all_clicked();

    void on_discharge_all_clicked();

private:
    Ui::MainWindow *ui;

    cell *BattCells[TOTAL_CELLS];

    QSerialPort *sp;
   int s_count;
   char rx_buffer[SerialRx_Packet_Length];
   char tx_buffer[SerialTx_Packet_Length];
   bool header_detected;

   float V_Float[40];


    void InitSerial();
    void InitUI();
    void ParseSerialPacket();
    void InitEverything();
    void updategui();
    void SendPacket();
    float ConvertToVoltage(uint16_t raw);
    void UpdateBattCell(float v, int index);
};
#endif // MAINWINDOW_H
