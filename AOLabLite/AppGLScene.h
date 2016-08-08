#ifndef APPGLSCENE_H
#define APPGLSCENE_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include "ScenePoint.h"

class AppGLScene : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    AppGLScene();
    virtual ~AppGLScene();

    void addScenePoints(const QVector<ScenePoint>& data);

public slots:

protected:
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL(void) Q_DECL_OVERRIDE;
    void initializeGL(void) Q_DECL_OVERRIDE;

private:
    QColor m_background;
    QVector<ScenePoint> m_data;
};

#endif // APPGLSCENE_H
