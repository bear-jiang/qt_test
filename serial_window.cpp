#include "serial_window.h"
#include <QDebug>

SerialWindow::SerialWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::serial_window)
{
    ui->setupUi(this);
    update_timer = new QTimer(this);
    serialport = new QSerialPort(this);

    connect(update_timer, SIGNAL(timeout()), this, SLOT(scan_serial_port()));
    connect(ui->connect_btn, SIGNAL(clicked(bool)), this, SLOT(serial_port_connect(bool)));
    connect(serialport, SIGNAL(readyRead()), this, SLOT(decode_frame()));
}

void SerialWindow::scan_serial_port()
{
    if (!serialport->isOpen())
    {
        QStringList name;
        name.clear();
        ui->portname->clear();
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            name<<info.portName();
        }
        ui->portname->addItems(name);
    }
    else
    {
        char buf[6] = {1,2,3,4,5,6};
        serialport->write(buf,sizeof(buf));
        serialport->waitForBytesWritten(0);
    }
}

void SerialWindow::decode_frame()
{
    QByteArray serial_data = serialport->readAll();
    qDebug()<<serial_data;
}

void SerialWindow::serial_port_connect(bool pressed)
{
    if (pressed)
    {
        QString port_name = ui->portname->currentText();
        if (port_name == nullptr)
        {
            qDebug("Can not find serial port!");
            ui->connect_btn->setChecked(false);
            return;
        }

        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            if(info.portName() == port_name)
            {
                serialport->setPort(info);
                qDebug()<<"Choose"<<info.portName();
            }
        }

        if(serialport->open(QIODevice::ReadWrite))//打开串口，并配置相应参数
        {
            serialport->setBaudRate(QSerialPort::Baud115200);
            serialport->setParity(QSerialPort::NoParity);
            serialport->setDataBits(QSerialPort::Data8);
            serialport->setStopBits(QSerialPort::OneStop);
            serialport->setFlowControl(QSerialPort::NoFlowControl);

            serialport->clearError();
            serialport->clear();
        }
        else
        {
            qDebug()<<"Can not open serial port" << serialport->portName();
        }
    }
    else
    {
        serialport->close();
    }

    if (serialport->isOpen())
    {
        ui->connect_btn->setChecked(true);
        ui->portname->setEnabled(false);
    }
    else
    {
        ui->connect_btn->setChecked(false);
        ui->portname->setEnabled(true);
    }

}

void SerialWindow::show()
{
    update_timer->start(1000);
    QWidget::show();
}

void SerialWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug("1212");

}

void SerialWindow::closeEvent(QCloseEvent *event)
{
    if (serialport->isOpen())
    {
        serialport->close();
    }
}

