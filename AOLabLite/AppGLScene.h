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
    void drawScene(const QMatrix4x4 &mvMatrix);

public slots:
    void viewFront(void);
    void viewBack(void);
    void viewLeft(void);
    void viewRight(void);
    void viewTop(void);
    void viewBottom(void);

protected:
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL(void) Q_DECL_OVERRIDE;
    void initializeGL(void) Q_DECL_OVERRIDE;

private:
    void createGradient(void);
    void drawBackground(QPainter& painter);

    qreal m_angle = 30;
    QOpenGLShaderProgram m_shader;
    QVector<ScenePoint> m_data;

    QVector3D m_eye = {0, 0, 2};
    QVector3D m_center = {0, 0, 0};
    QVector3D m_up = {0, 1, 0};
    QColor m_background;
    QRadialGradient m_gradient;
    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projectionMatrix;
};

#endif // APPGLSCENE_H
