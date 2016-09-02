#ifndef APPGLSCENE_H
#define APPGLSCENE_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QPoint>
#include "ScenePoint.h"

const float eyeDistance = 3;

class AppGLScene : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    enum Projection {PROJ_PERSP, PROJ_ORTHO, PROJ_FRUST};

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
    void drawPolyline(void);

protected:
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL(void) Q_DECL_OVERRIDE;
    void initializeGL(void) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
    void AppGLScene::mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

private:
    void createGradient(void);
    void drawBackground(QPainter& painter);
    void setProjectionMatrix(void);

    // TEMP
    bool m_once = false;
    // END TEMP

    QPoint m_lastPos;
    float m_initialWinHeight;
    float m_initialWinWidth;
    qreal m_angle = 30;
    float m_scale = 0.1f;
    QOpenGLShaderProgram m_shader;
    QVector<ScenePoint> m_data;

    Projection m_proj = PROJ_PERSP;
    QVector3D m_eye = {0, 0, eyeDistance};
    QVector3D m_center = {0, 0, 0};
    QVector3D m_up = {0, 1, 0};
    QColor m_background;
    QRadialGradient m_gradient;
    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projectionMatrix;
};

#endif // APPGLSCENE_H
