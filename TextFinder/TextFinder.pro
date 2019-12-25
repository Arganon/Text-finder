QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model.cpp \
    Presenter.cpp \
    ThreadPool/ClassicThreadPool.cpp \
    ThreadPool/QTThreadPool.cpp \
    Utils/HtmlTextAcquisition.cpp \
    Utils/HtmlVertexHandler.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    DataStructures/DataToStartSearching.hpp \
    DataStructures/Vertex.hpp \
    Enums/Enums.hpp \
    Interfaces/IPresenter.hpp \
    Interfaces/IThreadPool.hpp \
    Interfaces/IView.hpp \
    MainWindow.hpp \
    Model.hpp \
    Presenter.hpp \
    ThreadPool/ClassicThreadPool.hpp \
    ThreadPool/QTThreadPool.hpp \
    Utils/HtmlTextAcquisition.hpp \
    Utils/HtmlVertexHandler.hpp

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -lcurl
