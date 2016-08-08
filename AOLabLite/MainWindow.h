#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AppGLScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
    void importPly(void);

private:
    AppGLScene* m_scene;

};

#endif // MAINWINDOW_H
