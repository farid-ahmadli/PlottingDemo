#include "BrowserWindow.h"
#include "ui_BrowserWindow.h"

BrowserWindow::BrowserWindow(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::BrowserWindow)
{
    m_ui->setupUi(this);
    m_ui->progressBar->setVisible(false);
}

BrowserWindow::~BrowserWindow()
{
    delete m_ui;
}

void BrowserWindow::on_pushButton_clicked()
{
    QString url = m_ui->lineEdit->text().trimmed();

    if ( !url.startsWith("http://") ) {
        url = "http://" + url;
    }
    m_ui->lineEdit->setText( url );
    m_ui->webView->setUrl( url );
    m_ui->webView->load( url );
}

void BrowserWindow::on_webView_loadStarted()
{
    m_ui->progressBar->setVisible(true);
}

void BrowserWindow::on_webView_loadFinished(bool v)
{
    m_ui->progressBar->setVisible(false);
}

void BrowserWindow::on_webView_loadProgress(int progress)
{
    m_ui->progressBar->setMaximum(100);
    m_ui->progressBar->setValue(progress);
}

void BrowserWindow::on_webView_statusBarMessage(QString text)
{
    emit this->statusChanged(text);
}

void BrowserWindow::on_webView_titleChanged(QString title)
{
    emit this->titleChanged(title);
}

void BrowserWindow::on_lineEdit_returnPressed()
{
    emit m_ui->pushButton->click();
}
