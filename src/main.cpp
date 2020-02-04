//#include "mainwindow.h"
#include <QApplication>

#include <QMainWindow>
#include <QFile>
#include <keylayout.h>
#include "keyboard.h"
int main(int argc, char *argv[])
{
    qSetMessagePattern("[%{type}] %{appname} (%{file}:%{line}) - %{message}");
    QApplication a(argc, argv);
    QMainWindow w;
    QFile file;

    file.setFileName(":/en.json");

    KeyLayout kl(file);
    Keyboard k(kl, InputMode::Mouse);
    // w.setCentralWidget(k);
    w.show();

    return a.exec();
}
