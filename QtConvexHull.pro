QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += glm

SOURCES += \
    convexhull/divideconquerconvexhull.cpp \
    convexhull/gramhamconvexhull.cpp \
    convexhull/jarvisconvexhull.cpp \
    convexhull/point.cpp \
    main.cpp \
    view/glviewwidget.cpp \
    view/kwctrlview.cpp \
    view/myctrlview.cpp \
    widget.cpp

HEADERS += \
    convexhull/UtilTool.h \
    convexhull/divideconquerconvexhull.h \
    convexhull/gramhamconvexhull.h \
    convexhull/jarvisconvexhull.h \
    convexhull/point.h \
    view/Camera/Camera.h \
    view/Camera/Camera.h \
    view/glviewwidget.h \
    view/kwctrlview.h \
    view/myctrlview.h \
    widget.h

FORMS += \
    widget.ui

LIBS+= -lopengl32 -lglu32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    shader/shader.qrc


