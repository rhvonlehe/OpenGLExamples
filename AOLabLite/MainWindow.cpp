#include <QDesktopWidget>
#include <QMenuBar>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
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

    QPushButton* front = new QPushButton("Front", mainWidget);
    QPushButton* back = new QPushButton("Back", mainWidget);
    QPushButton* left = new QPushButton("Left", mainWidget);
    QPushButton* right = new QPushButton("Right", mainWidget);
    QPushButton* top = new QPushButton("Top", mainWidget);
    QPushButton* bottom = new QPushButton("Bottom", mainWidget);

    QWidget* viewButtonWidget = new QWidget(mainWidget);
    QVBoxLayout* viewButtonLayout = new QVBoxLayout(viewButtonWidget);
    viewButtonLayout->addWidget(front);
    viewButtonLayout->addWidget(back);
    viewButtonLayout->addWidget(left);
    viewButtonLayout->addWidget(right);
    viewButtonLayout->addWidget(top);
    viewButtonLayout->addWidget(bottom);

    m_layout->addWidget(viewButtonWidget, 0, 0, 1, 1);
    m_layout->addWidget(m_scene, 0, 1, 1, 9);
    mainWidget->setLayout(m_layout);

    setCentralWidget(mainWidget);

    connect(front, &QPushButton::clicked, m_scene, &AppGLScene::viewFront);
    connect(back, &QPushButton::clicked, m_scene, &AppGLScene::viewBack);
    connect(left, &QPushButton::clicked, m_scene, &AppGLScene::viewLeft);
    connect(right, &QPushButton::clicked, m_scene, &AppGLScene::viewRight);
    connect(top, &QPushButton::clicked, m_scene, &AppGLScene::viewTop);
    connect(bottom, &QPushButton::clicked, m_scene, &AppGLScene::viewBottom);
}

void MainWindow::importPly(void)
{
    // TODO: Create a modal dialog to do this, but as a first pass
    // just load a hard-coded file
    //
//  PLYReader reader(":/upper.ply");
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
