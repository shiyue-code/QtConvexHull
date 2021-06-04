#ifndef GLVIEWWIDGET_H
#define GLVIEWWIDGET_H

#include <QOpenGLWidget>

#include <QMatrix4x4>

#include "Camera/Camera.h"

class QOpenGLFunctions;
class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QOpenGLVertexArrayObject;

class GLViewWidget: public QOpenGLWidget
{
public:
    explicit GLViewWidget(QWidget* parent = nullptr);
    ~GLViewWidget();

    void setVertices(float *vertices, int size, int col);

    void setRect(const QRectF &rect);
    void resetRect();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void enterEvent(QEvent *evt) override;
    void mouseMoveEvent(QMouseEvent* evt) override;
    void mousePressEvent(QMouseEvent* evt) override;
    void mouseReleaseEvent(QMouseEvent *evt) override;

    void keyPressEvent(QKeyEvent *evt) override;

    QVector3D View2Scr(const QVector3D &viewPt);
    QVector3D Scr2View(const QVector3D &scrPt);

private:
    QOpenGLFunctions *glFuncs {nullptr};
    QOpenGLShaderProgram *shader {nullptr};

    QOpenGLVertexArrayObject *vao {nullptr};
    QOpenGLBuffer *vbo {nullptr};

    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;

    QMatrix4x4 defaultView;

    Camera camera;

    bool moveView = false;

    float *pointData = nullptr;
    int pointSize;
    int pointStride;
};

#endif // GLVIEWWIDGET_H
