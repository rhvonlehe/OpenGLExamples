

#include "AppGLScene.h"

AppGLScene::AppGLScene()
{

}

AppGLScene::~AppGLScene()
{
    setMinimumSize(300, 250);
}

void AppGLScene::addScenePoints(const QVector<ScenePoint>& data)
{
    // NB: use a 'move' here to avoid a massive copy operation.  Also
    // it's better than 'swap'
    //
    m_data = std::move(data);
}


void AppGLScene::resizeGL(int w, int h)
{

}

void AppGLScene::paintGL(void)
{

}

void AppGLScene::initializeGL(void)
{

}

