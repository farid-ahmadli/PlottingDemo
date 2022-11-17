#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->browseWnd, SIGNAL(statusChanged(QString)), this, SLOT(changeStatus(QString)));
    QObject::connect(ui->browseWnd, SIGNAL(titleChanged(QString)), this, SLOT(changeBrowserTitle(QString)));

    ui->mdiArea->tileSubWindows();
    //ui->statusBar->addPermanentWidget( new QLabel("Ready") );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStatus(QString text)
{
    ui->statusBar->showMessage( text, 0 );
}

void MainWindow::changeBrowserTitle(QString text)
{
    ui->browseWnd->setWindowTitle( text );
}
