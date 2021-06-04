#include "glviewwidget.h"


#include <QMouseEvent>

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

float vertices[] = {
     0.0f, 0.f, 1.0f,
     100.f, 100.f, 1.0f,
     -100.f,  0.0f, 1.0f
};

GLViewWidget::GLViewWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setVertices(vertices, 3, 3);
    setMouseTracking(true);
    grabKeyboard();

    setRect({-100, -100, 200, 200});
}

GLViewWidget::~GLViewWidget()
{

}

void GLViewWidget::setVertices(float *vertices, int size, int stride)
{

    if(vertices != pointData) {
        if(pointData) {
            delete[] pointData;
        }

        pointData = new float[size*stride];
        pointSize = size;
        pointStride = stride;
    }

    memcpy(this->pointData, vertices, size*stride*sizeof(float));

    if(isValid())
    {

        vao->bind();
        vbo->bind();

        vbo->allocate(pointData, pointSize*stride*sizeof(float));

        glFuncs->glVertexAttribPointer(0, stride, GL_FLOAT, GL_FALSE,  stride*sizeof(GLfloat), 0);
        glFuncs->glEnableVertexAttribArray(0);

        vbo->release();
        vao->release();

        delete[] pointData;
        pointData = nullptr;
    }

}

void GLViewWidget::setRect(const QRectF &rect)
{
    double aspectRatio = 1;
    if(height() > 0)
        aspectRatio = float(width())/height();

    double h = rect.height();
    double w = h*aspectRatio;

    if(w < rect.width()) {
        w = rect.width();
        h = w/aspectRatio;
    }

    QRectF realRect(rect.left(), rect.top(), w, h);

    view.setToIdentity();
    view.ortho(realRect);
    update();
}

void GLViewWidget::resetRect()
{
    view = defaultView;
    update();
}

void GLViewWidget::initializeGL()
{
    QOpenGLWidget::initializeGL();

    shader = new QOpenGLShaderProgram();

    glFuncs = this->context()->functions();

    shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vert");
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.frag");
    if (shader->link()) {
       qDebug("Shaders link success.");
    } else {
       qDebug("Shaders link failed!");
       return;
    }
    shader->bind();
    shader->setUniformValue("ourColor", QVector4D(1, 0, 0, 1));
    shader->release();

    vao = new QOpenGLVertexArrayObject();
    vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);

    vao->create();
    vbo->create();

    setVertices(pointData, pointSize, pointStride);

    glFuncs->glEnable(GL_PROGRAM_POINT_SIZE);


}

void GLViewWidget::paintGL()
{
    glFuncs->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFuncs->glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
    vao->bind();
    shader->bind();

//    projection.perspective(camera.Zoom, (float)width() / (float)height(), 0.1f, 1000.f);
    shader->setUniformValue("projection", projection);
    shader->setUniformValue("view", view);
    shader->setUniformValue("model", model);


    glFuncs->glDrawArrays(GL_TRIANGLES, 0, pointSize);
    shader->release();
    vbo->release();
    vao->release();
}

void GLViewWidget::resizeGL(int w, int h)
{
    QOpenGLWidget::resizeGL(w, h);
}

void GLViewWidget::enterEvent(QEvent *evt)
{
    QOpenGLWidget::enterEvent(evt);
}

void GLViewWidget::mouseMoveEvent(QMouseEvent *evt)
{
    static QPoint lastPos;
    static QVector3D translate;

    if(moveView)
    {
        translate = QVector3D(QVector2D(evt->pos()-lastPos));

        view.translate(translate);
    }

    lastPos = evt->pos();

//    camera.ProcessMouseMovement(xoffset, yoffset, false);
    update();
}

void GLViewWidget::mousePressEvent(QMouseEvent *evt)
{
    if(evt->button() == Qt::LeftButton)
    {
        moveView = true;
    }
}

void GLViewWidget::mouseReleaseEvent(QMouseEvent *evt)
{
    if(evt->button() == Qt::LeftButton)
    {
        moveView = false;
    }
}

void GLViewWidget::keyPressEvent(QKeyEvent *evt)
{
    update();
    QOpenGLWidget::keyPressEvent(evt);
}

QVector3D GLViewWidget::View2Scr(const QVector3D &viewPt)
{
    return view*viewPt;
}

QVector3D GLViewWidget::Scr2View(const QVector3D &scrPt)
{
    return view.inverted()*scrPt;
}
