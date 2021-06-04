#include "widget.h"
#include "ui_widget.h"

#include <QRandomGenerator>
#include <QTime>

#include "convexhull/gramhamconvexhull.h"
#include "convexhull/jarvisconvexhull.h"
#include "convexhull/divideconquerconvexhull.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->btnGenPoints, SIGNAL(clicked(bool)), this, SLOT(randomPoints()));
    connect(ui->btnGramham, SIGNAL(clicked(bool)), this, SLOT(gramhamConvexhull()));
    connect(ui->btnJarvis, SIGNAL(clicked(bool)), this, SLOT(jarvisConvexhull()));
    connect(ui->btnDivideConquer, SIGNAL(clicked(bool)), this, SLOT(divideConvexhull()));

    ui->lePointSize->setText(QString::number(pointSize));
    connect(ui->lePointSize, SIGNAL(editingFinished()), this, SLOT(onSizeChagned()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::randomPoints()
{
    double coordRange = 10000;
    auto random = QRandomGenerator::system();

    points.clear();

    for(int i = 0; i < pointSize; ++i)
    {
        Shape2D::Point2D pt(random->bounded(coordRange), random->bounded(coordRange));
        points.push_back(pt);
    }

    ui->openGLWidget->setPoints(points);
}

void Widget::gramhamConvexhull()
{
    if(points.empty())
        return;

    ConvexHull::GramhamConvexhull calc(points);
    QTime t;
    t.start();
    auto path = calc.execute();
    ui->lblGramhamTime->setText(QString::number(t.elapsed())+ "ms");
    ui->openGLWidget->setConvexHull(path);
}

void Widget::jarvisConvexhull()
{
    if(points.empty())
        return;

    ConvexHull::JarvisConvexHull calc(points);
    QTime t;
    t.start();
    auto path = calc.execute();
    ui->lblJarvisTime->setText(QString::number(t.elapsed())+ "ms");
    ui->openGLWidget->setConvexHull(path);
}

void Widget::divideConvexhull()
{
    if(points.empty())
        return;

    ConvexHull::DivideConquerConvexHull calc(points);
    QTime t;
    t.start();
    auto path = calc.execute();
    ui->lblbtnDivideConquerTime->setText(QString::number(t.elapsed())+ "ms");
    ui->openGLWidget->setConvexHull(path);
}

void Widget::onSizeChagned()
{
    pointSize = ui->lePointSize->text().toInt();
}

