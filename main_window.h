#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>

namespace Ui {
class main_window;
}

class main_window : public QWidget
{
    Q_OBJECT

public:
    explicit main_window(QWidget *parent = 0);
    ~main_window();

private:
    Ui::main_window *ui;
};

#endif // MAIN_WINDOW_H
