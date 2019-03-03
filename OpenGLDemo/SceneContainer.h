#ifndef SCENECONTAINER_H
#define SCENECONTAINER_H

#include <ScenePoint.h>
#include <QVector>

struct SceneContainer
{
    SceneContainer();

    bool                    hasColor;
    bool                    hasNormal;
    QVector<ScenePoint>     points;
};

#endif // SCENECONTAINER_H
