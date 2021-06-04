#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "convexhull/UtilTool.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


public slots:
    void randomPoints();
    void gramhamConvexhull();
    void jarvisConvexhull();
    void divideConvexhull();

    void onSizeChagned();

private:
    Shape2D::Path2D points;

    int pointSize = 100;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
