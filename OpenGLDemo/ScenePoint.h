#ifndef SCENEPOINT_H
#define SCENEPOINT_H

#include <QVector3D>

struct ScenePoint
{
    QVector3D coords;
    QVector3D normal;
    QVector3D color;

    ScenePoint() = default;

//    ScenePoint(const QVector3D &crd = QVector3D(),
//               const QVector3D &nrm = QVector3D(),
//               )
//    {
//        coords = crd; normal=nrm; color = col;
//    }
};

#endif // SCENEPOINT_H
