#include "PLYReader.h"
#include <QFile>

PLYReader::PLYReader(const QString &fileName)
{
    m_device = new QFile(fileName, this);
    m_device->open(QIODevice::ReadOnly|QIODevice::Text);
}

PLYReader::PLYReader(QIODevice *device)
{
    m_device = device;
}

bool PLYReader::read()
{
    m_hasColor = false;
    m_hasNormal = false;
    m_vertices.clear();
    m_faces.clear();
    QTextStream stream(device());
    QString line = stream.readLine();
    if (line != "ply")
    {
        return false;
    }

    line = stream.readLine();
    int vertexCount = 0, faceCount = 0;

    while (line != "end_header")
    {
        if (line.startsWith("element"))
        {
            QStringList args = line.split(QRegExp("\\s+"));
            if (args.count() < 3)
            {
                break;
            }
            if (args.at(1) == "property")
            {
                if (args.at(3) == "nx")
                {
                    m_hasNormal = true;
                }
                else if (args.at(3) == "red")
                {
                    m_hasColor = true;
                }
            }
            if (args.at(1) == "vertex")
            {
                vertexCount = args.at(2).toInt();
            }
            else if (args.at(1) == "face")
            {
                faceCount = args.at(2).toInt();
            }
        }

        line = stream.readLine();
    }

    readVertices(stream, vertexCount);
    readFaces(stream, faceCount);
    return true;
}

void PLYReader::readVertices(QTextStream &stream, int vertexCount)
{
    m_vertices.reserve(vertexCount);

    for(int i=0; i < vertexCount; ++i)
    {
        m_vertices << readVertex(stream);
    }
}

void PLYReader::readFaces(QTextStream &stream, int faceCount)
{
    m_faces.reserve(faceCount);

    for (int i=0; i < faceCount; ++i)
    {
        m_faces << readFace(stream);
    }
}

ScenePoint PLYReader::readVertex(QTextStream &stream)
{
    ScenePoint pt;
    float xpos{0};
    float ypos{0};
    float zpos{0};
    float nx{0};
    float ny{0};
    float nz{0};
    float red{255};
    float green{255};
    float blue{255};

    stream >> xpos >> ypos >> zpos;

    if (m_hasNormal)
    {
        stream >> nx >> ny >> nz;
    }
    if (m_hasColor)
    {
        stream >> red >> green >> blue;
    }
    pt.coords = QVector3D(xpos, ypos, zpos);
    pt.normal = QVector3D(nx, ny, nz);
    pt.color = QVector3D(red, green, blue);

    return pt;
}

QVector<int> PLYReader::readFace(QTextStream &stream) {
    int cnt, pt;
    stream >> cnt;
    QVector<int> face;
    face.reserve(cnt);

    for (int v=0; v < cnt; ++v)
    {
        stream >> pt;
        face << pt;
    }

    return face;
}

