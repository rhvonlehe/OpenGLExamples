#include "SceneGLWindow.h"
#include "AbstractGLScene.h"


SceneGLWindow::SceneGLWindow(QWindow *parent)
    : QOpenGLWindow(NoPartialUpdate, parent)
{

}

void SceneGLWindow::setScene(AbstractGLScene * const s)
{
    m_scene = s;
}

void SceneGLWindow::initializeGL(void)
{
    if (scene())
    {
        scene()->initialize();
    }
}

void SceneGLWindow::paintGL(void)
{
    if (scene())
    {
        scene()->paint();
    }

}
