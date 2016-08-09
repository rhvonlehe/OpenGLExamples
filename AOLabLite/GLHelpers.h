#ifndef GLHELPERS_H
#define GLHELPERS_H

#include <QFile>
#include <QTextStream>

QString fileContent(const QString &filePath, const char *codec = 0)
{
    QFile f(filePath);

    if (!f.open(QFile::ReadOnly|QFile::Text))
    {
        return QString();
    }

    QTextStream stream(&f);

    if (codec != 0)
    {
        stream.setCodec(codec);
    }

    return stream.readAll();
}

#endif // GLHELPERS_H
