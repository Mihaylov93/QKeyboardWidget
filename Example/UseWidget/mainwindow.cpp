#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>          // Needed to pass the layout file
#include "keyboard.h"     // Include the keyboard itself
#include "keylayout.h"    // Needed to create a layout
//#include "key.h"

#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file;
    file.setFileName(":/en.json");    // Using it from the resource file.

    KeyLayout *kl = new KeyLayout(&file);
    Keyboard *k = new Keyboard(*kl, InputMode::Mouse);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLineEdit *tEdit = new QLineEdit(this);
    layout->addWidget(k);

    ui->centralWidget->layout()->addWidget(tEdit);
    ui->centralWidget->layout()->addWidget(k);
    ui->centralWidget->setLayout(kl->getLayoutAt(0));
    // ui->centralWidget->layout()->addItem(layout);
    // window->show();
    // Key *key = k->findKeyFromString("space", 0);
    // key->setWidth(80);
    // k->repaint();

    k->setFocus();
    k->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
