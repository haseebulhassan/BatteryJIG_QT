#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ledindicator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    InitEverything();
    on_pb_Refresh_clicked();

    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::InitEverything()
{

    s_count =0;
    header_detected = false;

    for (int i=0; i<67; i++)
    {
        rx_buffer[i] =0;
    }
    for (int i=0; i<10; i++)
    {
        tx_buffer[i]=0;
    }



    InitSerial();

    InitUI();

   ui->led->setLedSize(50);
}

void MainWindow::InitSerial()
{

    sp = new QSerialPort();
    sp->setBaudRate(QSerialPort::Baud115200);
    sp->setDataBits(QSerialPort::Data8);
    sp->setParity(QSerialPort::NoParity);
    connect(sp, SIGNAL(readyRead()), this, SLOT(onSerialData()));


}

void MainWindow::onSerialData()
{

       QByteArray qb = sp->readAll();
       uchar c =0;
       uchar c_prev=0;

       foreach (c, qb)
       {
           //qDebug()<<c<<"::"<< s_count;


           if (c == 0x90 && c_prev == 0xEB)
           {

               s_count=2;
               header_detected=true;
               rx_buffer[0] = 0xEB;
               rx_buffer[1] = c;
           }
           else if (header_detected)
           {
               if (s_count == SerialRx_Packet_Length-1)
               {
                   rx_buffer[SerialRx_Packet_Length-1] = c;
                   header_detected= false;
                   s_count = 0;
                // qDebug()<<"Packet Recieved";
                   ParseSerialPacket();

               }
               else
               {
                    rx_buffer[s_count] = c;
                    s_count++;
               }
           }


           c_prev = c;
       }
       //qDebug()<<rx_buffer;

}

void MainWindow::ParseSerialPacket()
{ 
   updategui();
   ui->led->toggle();
}



void MainWindow::on_pushButton_clicked()
{

    if (sp->isOpen())
    {
        sp->close();
        ui->pushButton->setText("OPEN COM");
        QMessageBox::information(this, "Serial", "COM Closed");

    }
    else
    {
        sp->setPortName(ui->cb_comport->currentText());
        ui->pushButton->setText("CLOSE COM");

        if(sp->open(QIODevice::ReadWrite))
        {
            QMessageBox::information(this, "Serial", "COM Opened");
        }

        else QMessageBox::information(this, "Serial", "COM Opening Error");
    }

}

void MainWindow::InitUI()
{
    for (int r=0; r<5; r++)
    {
        for (int c=0; c<6; c++)
        {
            cell *ce = new cell();
            int index = c + (r*6);
            ce->pb_mode->setAccessibleName(QString::number(index));
           // ce->pb_log->setAccessibleName(QString::number(index));
            connect(ce->pb_mode, SIGNAL(released()),this, SLOT(on_pbmode_clicked()));
            //connect(ce->pb_log,SIGNAL(released()),this, SLOT (on_pblog_clicked()));
            BattCells[index] = ce;
            BattCells[index]->mypcb = r;
            BattCells[index]->mycell = c;
            ui->gridLayout->addWidget(ce->gb_main, r, c);

        }

    }


}

void MainWindow::on_pbmode_clicked()
{

    QPushButton *pb = (QPushButton*)sender();

    int index = pb->accessibleName().toInt();

    BattCells[index]->Status_Charging = !BattCells[index]->Status_Charging;

    if (BattCells[index]->Status_Charging)
    {
        BattCells[index]->setbattery_chrg();
    }
    else
    {
        BattCells[index]->setbattery_dischrg();
    }

    SendPacket();
}


void MainWindow::SendPacket()
{


    uint8_t chg[5] = {0,0,0,0,0};

    for (int pcb=0; pcb<5; pcb++)
    {
        for (int cell=0; cell<6; cell++)
        {

            if (BattCells[pcb*6 + cell]->Status_Charging)
            {
                chg[pcb] |= (uint8_t) pow(2,cell);
            }
        }
    }


    tx_buffer[0] =0xEB;
    tx_buffer[1] = 0x90;
    tx_buffer[2] = ~chg[0];
    tx_buffer[3] = ~chg[1];
    tx_buffer[4] = ~chg[2];
    tx_buffer[5] = ~chg[3];
    tx_buffer[6] = ~chg[4];
    tx_buffer[7] =0;
    tx_buffer[8] =0;
    tx_buffer[9] =0;


    sp->write(tx_buffer, 10);



}

/*void MainWindow::on_pblog_clicked()
{
    QPushButton *pb = (QPushButton*)sender();
    // call hashing function




    int index = pb->accessibleName().toInt();

    BattCells[index]->Status_Log = !BattCells[index]->Status_Log;

    BattCells[index]->logging();
 }
*/
void MainWindow::updategui()
{
    uint16_t raw_v =0;
    float v_f =0;
    int index =0;

    for (int i=0; i<40; i++)
    {
       raw_v =  ((rx_buffer[i*2 + 7] & 0xFF) + (rx_buffer[(i*2) + 1 + 7] << 8)) & 0xFFFF;
       v_f = ConvertToVoltage(raw_v);

       if (i==6 || i==7 || i==14 || i==15 || i==22 || i==23 || i==30 || i==31 || i==38 || i==39)
          continue;

       UpdateBattCell(v_f , index);
       index++;

    }


}

void MainWindow::UpdateBattCell(float v , int index)
{

    BattCells[index]->volt= v;
    BattCells[index]->lcd_volt->display(QString::number(v , 'f', 2));
    BattCells[index]->current=v/3.9;
    BattCells[index]->lcd_curr->display(QString::number(v/3.9 , 'f', 2));
    BattCells[index]->time_sec += 5;

    BattCells[index]->UpdateCapacity();

    if(BattCells[index]->volt<=2.5)
    {
       // BattCells[index]->setbattery_lowvoltage();
    }

}

float MainWindow::ConvertToVoltage(uint16_t raw)
{
    if (raw > 32767)
    {
        raw =0;
    }

    float v = (raw * 62.5) * 3.63;
    v = v / 1000000;

    return v;

}


void MainWindow::on_pb_Refresh_clicked()
{
    ui->cb_comport->clear();

       Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts())
       {
           QString p_name = port.portName();
           ui->cb_comport->addItem(p_name);
       }

       ui->cb_comport->setCurrentIndex(0);
}


void MainWindow::on_charge_all_clicked()
{
    for (int i=0;i<30;i++)
    {
        BattCells[i]->setbattery_chrg();
    }


    tx_buffer[0] =0xEB;
    tx_buffer[1] = 0x90;
    tx_buffer[2] = 0;
    tx_buffer[3] = 0;
    tx_buffer[4] = 0;
    tx_buffer[5] = 0;
    tx_buffer[6] = 0;
    tx_buffer[7] =0;
    tx_buffer[8] =0;
    tx_buffer[9] =0;


    sp->write(tx_buffer, 10);


}


void MainWindow::on_discharge_all_clicked()
{
    for (int i=0;i<30;i++)
    {
        BattCells[i]->setbattery_dischrg();
    }

    tx_buffer[0] =0xEB;
    tx_buffer[1] = 0x90;
    tx_buffer[2] = 0xFF;
    tx_buffer[3] = 0xFF;
    tx_buffer[4] = 0xFF;
    tx_buffer[5] = 0xFF;
    tx_buffer[6] = 0xFF;
    tx_buffer[7] =0;
    tx_buffer[8] =0;
    tx_buffer[9] =0;


    sp->write(tx_buffer, 10);




}

