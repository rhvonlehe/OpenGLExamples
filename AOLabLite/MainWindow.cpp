#include <QDesktopWidget>
#include <QMenuBar>
#include "MainWindow.h"
#include "AppGLScene.h"
#include "ScenePoint.h"
#include "PLYReader.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction("E&xit", this, &QWidget::close);
    fileMenu->addAction("&Import PLY file", this, &MainWindow::importPly);

    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}

void MainWindow::importPly(void)
{
    // TODO: Create a modal dialog to do this, but as a first pass
    // just load a hard-coded file
    //
    PLYReader reader(":/upper.ply");
    QVector<ScenePoint> plyData;

    if (reader.read())
    {
        const QVector<ScenePoint> vertices = reader.vertices();
        const QVector<QVector<int>> faces = reader.faces();

        foreach(QVector<int> face, faces)
        {
            ScenePoint pt;

            for (int idx = 0; idx < face.count(); ++idx)
            {
                int vertexId = face.at(idx);
                pt = vertices.at(vertexId);

                plyData << pt;
            }
        }

        m_scene->addScenePoints(plyData);
    }
}
