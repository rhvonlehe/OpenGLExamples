#include "AbstractGLScene.h"
#include <QOpenGLWindow>

AbstractGLScene::AbstractGLScene(QOpenGLWindow *wnd)
{
    m_window = wnd;
}

AbstractGLScene::~AbstractGLScene()
{

}

QOpenGLContext *AbstractGLScene::context()
{
    return window() ? window()->context() : 0;
}

const QOpenGLContext *AbstractGLScene::context() const
{
    return window() ? window()->context() : 0;
}

void AbstractGLScene::initialize()
{
    initializeOpenGLFunctions();
}
