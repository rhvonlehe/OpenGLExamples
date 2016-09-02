#ifndef PLYREADER_H
#define PLYREADER_H

#include <QObject>
#include <QVector3D>
#include <QTextStream>
#include <QVector>
#include "ScenePoint.h"

class QIODevice;

class PLYReader : public QObject {
public:
    PLYReader(const QString &fileName);
    PLYReader(QIODevice *device);
    inline QIODevice *device() const { return m_device; }
    bool read();

    inline const QVector<ScenePoint> vertices() const { return m_vertices; }
    inline const QVector<QVector<int> > faces() const { return m_faces; }

protected:
    void readVertices(QTextStream &stream, int vertexCount);
    void readFaces(QTextStream &stream, int faceCount);
    ScenePoint readVertex(QTextStream &stream);
    QVector<int> readFace(QTextStream &stream);

private:
    QIODevice *m_device;
    QVector<ScenePoint> m_vertices;
    QVector<QVector<int> > m_faces;

};

#endif // PLYREADER_H
