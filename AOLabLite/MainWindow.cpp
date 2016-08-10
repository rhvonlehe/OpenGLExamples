#include <QDesktopWidget>
#include <QMenuBar>
#include <QGridLayout>
#include <QLabel> // TEMP
#include "MainWindow.h"
#include "AppGLScene.h"
#include "ScenePoint.h"
#include "PLYReader.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction("&Import PLY file", this, &MainWindow::importPly);
    fileMenu->addAction("E&xit", this, &QWidget::close);

    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    QWidget* mainWidget = new QWidget(this);

    m_layout = new QGridLayout(mainWidget);
    m_scene = new AppGLScene();

    QLabel* label = new QLabel(this);
    label->setText("This is a label");

    m_layout->addWidget(m_scene, 0, 1, 5, 1);
    m_layout->addWidget(label, 0, 0, 1, 1);
    mainWidget->setLayout(m_layout);

    setCentralWidget(mainWidget);
}

void MainWindow::importPly(void)
{
    // TODO: Create a modal dialog to do this, but as a first pass
    // just load a hard-coded file
    //
//    PLYReader reader(":/upper.ply");
    PLYReader reader(":/monkey.ply");
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
