#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setFont(QFont("Microsoft YaHei", 24));
    Widget w;
    w.show();
    return a.exec();
}
