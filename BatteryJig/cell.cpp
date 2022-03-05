#include "cell.h"

cell::cell()
{

    Init_UI();
    setbattery_dischrg();

    time_sec =0;
    capacity =0;
    ADD_CAPACITY = false;

}

void cell::Init_UI()
{

    mypcb =0;
    mycell =0;


    // GroupBox
    gb_main = new QGroupBox();


    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *layout1 = new QHBoxLayout();
    QVBoxLayout *layout2 = new QVBoxLayout();
    QVBoxLayout *layout3= new QVBoxLayout();
    QHBoxLayout *layout4= new QHBoxLayout();

    lcd_volt = new QLCDNumber();
    lcd_curr = new QLCDNumber();
    lcd_time = new QLCDNumber();
    lcd_capacity= new QLCDNumber();



    auto palette = lcd_volt->palette();
    palette.setColor(palette.WindowText, Qt::black);
    lcd_volt->setPalette(palette);

    auto palette1 = lcd_curr->palette();
    palette1.setColor(palette1.WindowText, Qt::black);
    lcd_curr->setPalette(palette1);

    auto palette2 = lcd_capacity->palette();
    palette2.setColor(palette2.WindowText, Qt::black);
    lcd_capacity->setPalette(palette2);

    auto palette3 = lcd_time->palette();
    palette3.setColor(palette3.WindowText, Qt::black);
    lcd_time->setPalette(palette3);

    lcd_volt->setSegmentStyle(QLCDNumber::Flat );
    lcd_curr->setSegmentStyle(QLCDNumber::Flat );
    lcd_capacity->setSegmentStyle(QLCDNumber::Flat );
    lcd_time->setSegmentStyle(QLCDNumber::Flat );

   // lcd_volt->setDigitCount(4);
    //lcd_curr->setDigitCount(4);
   // lcd_time->setDigitCount(4);


   lcd_volt->setFixedSize(70,24);
   lcd_curr->setFixedSize(70,24);
   lcd_capacity->setFixedSize(70,24);
   //lcd_capacity->setStyleSheet(stylefont);


    //lcd_volt->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
   // lcd_curr->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
   // lcd_time->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
   // lcd_volt->setMaximumHeight(16);





    // Battery Picture
     pic_batt = new QLabel();
     voltage= new QLabel();
     cur= new QLabel();
     time= new QLabel();
     cap= new QLabel();

     pic_batt->setScaledContents(true);




    pb_mode = new QPushButton();
    pb_mode->setFixedSize(160,24);
    lcd_time->setFixedSize(120,23);

    //pb_log = new QPushButton();
    //pb_log->setFixedSize(150,20);


    voltage->setText("V");
    cur->setText("A");
    cap->setText("C");
    cap->setStyleSheet(stylefont);
    voltage->setStyleSheet(stylefont);
    cur->setStyleSheet(stylefont);
    layout2->addWidget(lcd_volt, Qt::AlignLeft);
    layout2->addWidget(lcd_curr, Qt::AlignLeft);
    layout2->addWidget(lcd_capacity,Qt::AlignLeft);
    layout3->addWidget(voltage, Qt::AlignLeft);
    layout3->addWidget(cur,Qt::AlignLeft);
    layout3->addWidget(cap,Qt::AlignLeft);

    //layout2->addWidget(lcd_time, 2, Qt::AlignLeft);
  // layout2->setSizeConstraint(QLayout::SetFixedSize);

    layout1->addLayout(layout3);
    layout1->addLayout(layout2);
    layout1->addWidget(pic_batt, Qt::AlignRight);
    //layout1->setSizeConstraint(QLayout::SetMaximumSize);
    //layout1->setContentsMargins(0,0,0,0);


   layout->addLayout(layout1);

   time->setText("Time");
   time->setStyleSheet(stylefont);

   layout4->addWidget(time,Qt::AlignLeft);;
   layout4->addWidget(lcd_time,Qt::AlignRight);

   layout->addLayout(layout4,Qt::AlignBottom);
   layout->addWidget(pb_mode,0,Qt::AlignCenter);
  // layout->setSizeConstraint(QLayout::SetDefaultConstraint);
layout->setContentsMargins(0,0,0,0);
    gb_main->setLayout(layout);
   // gb_main->setFixedSize(150,110);
    //gb_main->setTitle("Cell");

}


void cell::setbattery_chrg()
{

    QPixmap chrg(":/Resource/Charging Color.png");
    pb_mode->setText("Charging");
    pb_mode->setStyleSheet(styleGreen);

    pic_batt->setPixmap(chrg);
    Status_Charging=true;

    time_sec =0;
    capacity =0;

    lcd_capacity->display(0);
    lcd_time->display(0);
}
void cell::setbattery_dischrg()
{
    pb_mode->setText("Discharging");
    pb_mode->setStyleSheet(styleRed);


    QPixmap dischrg(":/Resource/Discharging color.png");
    pic_batt->setPixmap(dischrg);

    Status_Charging=false;

}
void cell::setbattery_lowvoltage()
{
    QPixmap low(":/Resource/Lowbattery color.png");
    pic_batt->setPixmap(low);
    Flag_LowVoltage=true;


}
void cell::UpdateCapacity()
{
    int t_min =0;


    float cp =0;

    if (!Status_Charging && volt > 2.5)
    {

        cp = current * 1000.0;
        cp = (cp * time_sec) / 60.0;
        cp = cp / 60.0;

       capacity += cp;

       lcd_capacity->display(QString::number(cp, 'f', 2));


       t_min  = time_sec / 60;
       lcd_time->display(QString::number(t_min));
       lcd_time->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else if (!Status_Charging && volt <=2.5)
    {
        lcd_time->setStyleSheet("background-color: rgb(100,100, 0);");
    }
    else
    {
        lcd_time->setStyleSheet("background-color: rgb(200, 0, 0);");

    }
}

/*void cell::logging()
{
    if(Status_Log==true)
    {

        timestart = clock();
        double time = ((double)timeend - timestart) / CLOCKS_PER_SEC;
        lcd_time->display(time);



    pb_log->setText("Logging");
    }
    else
    {



        timeend = clock();





    pb_log->setText("Stopped");

    }

}
*/
