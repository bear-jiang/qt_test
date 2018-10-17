#ifndef SERIAL_WINDOW_H
#define SERIAL_WINDOW_H

#include <QWidget>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include "ui_serial_window.h"

class SerialWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SerialWindow(QWidget *parent = nullptr);
    void show();

protected:

    virtual void closeEvent(QCloseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    QTimer *update_timer;
    QSerialPort *serialport;
    Ui::serial_window *ui;

signals:

public slots:


private slots:
    void scan_serial_port();
    void decode_frame();
    void serial_port_connect(bool pressed);

};

#endif // SERIAL_WINDOW_H
