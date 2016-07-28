#ifndef ABSTRACTGLSCENE_H
#define ABSTRACTGLSCENE_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>


class AbstractGLScene : protected QOpenGLFunctions
{
public:
    AbstractGLScene(QOpenGLWindow *wnd = nullptr);

    virtual ~AbstractGLScene(void);

    QOpenGLWindow* window(void) const
    {
        return m_window;
    }

    QOpenGLContext* context(void);

    const QOpenGLContext* context(void) const;

    virtual void paint(void) = 0;
    virtual void initialize(void) = 0;

private:
    QOpenGLWindow *m_window = nullptr; // C++11 reqd for assignment
};

#endif // ABSTRACTGLSCENE_H
