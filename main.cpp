#include "main_window.h"
#include "serial_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialWindow w;
    w.show();

    return a.exec();
}
