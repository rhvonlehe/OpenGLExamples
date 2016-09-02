#ifndef SCENEPOINT_H
#define SCENEPOINT_H

#include <QVector3D>

struct ScenePoint
{
    QVector3D coords;
    QVector3D normal;

    ScenePoint(const QVector3D &c = QVector3D(),
               const QVector3D &n = QVector3D())
    {
        coords = c; normal=n;
    }
};

#endif // SCENEPOINT_H
