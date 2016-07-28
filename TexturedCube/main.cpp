#include <QGuiApplication>
#include <QSurfaceFormat>
#include <QPropertyAnimation>

#include "SceneGLWindow.h"
#include "CubeGLScene.h"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    SceneGLWindow window;
    QSurfaceFormat fmt;

    fmt.setSamples(16);
    window.setFormat(fmt);

    CubeGLScene scene(&window);
    window.setScene(&scene);
    scene.setTexture(QImage(":/texture.jpg"));
    window.resize(600, 600);
    window.show();

    QPropertyAnimation anim(&scene, "angle");
    anim.setStartValue(0);
    anim.setEndValue(359);
    anim.setDuration(5000);
    anim.setLoopCount(-1);
    anim.start();

    return app.exec();
}
