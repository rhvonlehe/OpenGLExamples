#ifndef CUBEGLSCENE_H
#define CUBEGLSCENE_H

#include <QImage>
#include <QVector3D>
#include <QVector2D>
#include "AbstractGLScene.h"


class QOpenGLTexture;
class SceneGLWindow;

class CubeGLScene : public QObject, public AbstractGLScene
{
    Q_OBJECT
    Q_PROPERTY(float angle READ angle WRITE setAngle)

public:
    CubeGLScene(SceneGLWindow *wnd);
    ~CubeGLScene(void);

    void setTexture(const QImage& img);
    void initialize(void);
    void paint(void);

    float angle(void) const
    {
        return m_angle;
    }

    void setAngle(const float angle)
    {
        m_angle = angle;
        window()->update();
    }

protected:
    void initializeTexture(void);
    void initializeCubeData(void);
    void paintCube(void);

private:
    QImage          m_tex;
    QOpenGLTexture* m_texture;
    bool            m_initialized = false;
    float           m_angle = 0.0;

    struct TexturedPoint
    {
        QVector3D coord;
        QVector2D uv;
        TexturedPoint(const QVector3D& pcoord, const QVector2D& puv)
            : coord(pcoord), uv(puv) {}
    };

    QVector<TexturedPoint> m_data;
};

#endif // CUBEGLSCENE_H
