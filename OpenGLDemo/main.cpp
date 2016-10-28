#include <QApplication>
#include <QTranslator>
#include <QDebug>

#include "MainWindow.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );

    QTranslator translator;
    if (translator.load("opengldemo_sp"))
    {
        qDebug() << "Yay";
    }
    else
    {
        qDebug() << "Boo";
    }
    a.installTranslator(&translator);

    MainWindow mw;
    mw.show();

    return a.exec();
}

