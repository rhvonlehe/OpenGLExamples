#ifndef APPGLSCENE_H
#define APPGLSCENE_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include "ScenePoint.h"

class AppGLScene : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    AppGLScene();
    virtual ~AppGLScene();

    void addScenePoints(QVector<ScenePoint>& data);
    void paintScene(const QMatrix4x4 &mvMatrix);

public slots:

protected:
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL(void) Q_DECL_OVERRIDE;
    void initializeGL(void) Q_DECL_OVERRIDE;

private:
    qreal m_angle = 0;
    QOpenGLShaderProgram m_shader;
    QVector<ScenePoint> m_data;

    QColor m_background;
    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projectionMatrix;
};

#endif // APPGLSCENE_H
