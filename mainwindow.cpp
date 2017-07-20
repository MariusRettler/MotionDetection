#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowState(Qt::WindowMaximized);

    forms = new QStackedWidget();

    deadForm = new DeadForm();
    liveForm = new LiveForm();

    forms->addWidget(deadForm);
    forms->addWidget(liveForm);

    createActions();
    this->setCentralWidget(forms);

    goToDead();

}

MainWindow::~MainWindow()
{
    forms = NULL;
    delete ui;
}

void MainWindow::createActions()
{ 
    connect(ui->actionLoad, SIGNAL(triggered(bool)), this, SLOT(loadPicturesToList()));
    connect(ui->actionDead, SIGNAL(triggered(bool)), this, SLOT(goToDead()));
    connect(ui->actionLive, SIGNAL(triggered(bool)), this, SLOT(goToLive()));
    connect(ui->actionClose, SIGNAL(triggered(bool)), this, SLOT(close()));
}

void MainWindow::goToLive()
{
    ui->actionLoad->setEnabled(false);

    forms->setCurrentIndex(1);

}

void MainWindow::goToDead()
{
    ui->actionLoad->setEnabled(true);

    forms->setCurrentIndex(0);
}

void MainWindow::loadPicturesToList()
{
    deadForm->loadPicturesToList();
}



