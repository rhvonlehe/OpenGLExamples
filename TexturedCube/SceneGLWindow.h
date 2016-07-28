#ifndef SCENEGLWINDOW_H
#define SCENEGLWINDOW_H

#include <QOpenGLWindow>

class AbstractGLScene;
class SceneGLWindow : public QOpenGLWindow
{
public:
    SceneGLWindow(QWindow *parent = 0);

    // Getter
    AbstractGLScene* scene(void) const
    {
        return m_scene;
    }

    void setScene(AbstractGLScene* const scene);

    virtual void initializeGL(void);
    virtual void paintGL(void);



private:
    AbstractGLScene* m_scene = nullptr;
};

#endif // SCENEGLWINDOW_H
