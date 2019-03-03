#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PLYReader.h"


class QGridLayout;
class AppGLScene;
class SceneContainer;


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void importPly(QString filename, AppGLScene* scene);
    void printPly(QString filename, AppGLScene* scene);

private:
    bool populateSceneContainer(PLYReader& reader,
                                SceneContainer& scenePoints);

    QGridLayout* m_layout;
    AppGLScene* m_scene;
    AppGLScene* m_scene2;

};

#endif // MAINWINDOW_H
