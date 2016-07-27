#ifndef SIMPLEGLWINDOW_H
#define SIMPLEGLWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>

class SimpleGLWindow : public QOpenGLWindow,
        protected QOpenGLFunctions
{
public:
    SimpleGLWindow(QWindow* parent = 0) :
        QOpenGLWindow(NoPartialUpdate, parent)
    {
        // The below optional code sets up 16x sampling to
        // reduce the jagged edges
        //
        QSurfaceFormat fmt = format();
        fmt.setSamples(16);
        setFormat(fmt);
    }

    void paintGL(void);

protected:
    void initializeGL()
    {
        initializeOpenGLFunctions();
        glClearColor(1,1,1,0);
    }
};

#endif // SIMPLEGLWINDOW_H
