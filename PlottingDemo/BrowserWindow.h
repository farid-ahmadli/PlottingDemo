#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QtGui/QWidget>

namespace Ui {
    class BrowserWindow;
}

class BrowserWindow : public QWidget {
    Q_OBJECT
public:
    BrowserWindow(QWidget *parent = 0);
    ~BrowserWindow();

signals:
    void statusChanged(QString text);
    void titleChanged(QString text);


private:
    Ui::BrowserWindow *m_ui;

private slots:
    void on_lineEdit_returnPressed();
    void on_webView_titleChanged(QString title);
    void on_webView_statusBarMessage(QString text);
    void on_webView_loadProgress(int progress);
    void on_webView_loadFinished(bool );
    void on_webView_loadStarted();
    void on_pushButton_clicked();
};

#endif // BROWSERWINDOW_H
