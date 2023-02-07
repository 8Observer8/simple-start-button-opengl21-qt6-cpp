/* Create a .pro file:
QT += core gui openglwidgets widgets
win32: LIBS += -lopengl32
SOURCES += main.cpp
TARGET = app
-------------------------------
Build and run commands for CMD:
> qmake -makefile
> mingw32-make
> "release/app"
*/

#ifdef _WIN32
#include <windows.h>
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
extern "C" __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
#endif

#include <QtCore/QSize>
#include <QtGui/QOpenGLFunctions>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include <iostream>

class OpenGLWidget : public QOpenGLWidget, QOpenGLFunctions
{
    Q_OBJECT;

public:
    OpenGLWidget()
    {
        setFixedSize(QSize(300, 300));
        setWindowTitle("OpenGL21 Qt6 C++");

        QVBoxLayout *vbox = new QVBoxLayout();
        QPushButton *startButton = new QPushButton("Start Game");
        vbox->addWidget(startButton);
        setLayout(vbox);

        connect(startButton, &QPushButton::clicked, this,
            &OpenGLWidget::onStartButtonClick);
    }

private slots:
    void onStartButtonClick()
    {
        std::cout << "Start game" << std::endl;
    }

private:

    void initializeGL() override
    {
        initializeOpenGLFunctions();
        glClearColor(0.1f, 0.3f, 0.2f, 1.f);
    }

    void resizeGL(int w, int h) override
    {
        glViewport(0, 0, w, h);
    }

    void paintGL() override
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
#ifdef _WIN32
    if (AttachConsole(ATTACH_PARENT_PROCESS))
    {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
#endif
    std::cout << std::endl;

    QApplication app(argc, argv);
    OpenGLWidget w;
    w.show();
    return app.exec();
}
