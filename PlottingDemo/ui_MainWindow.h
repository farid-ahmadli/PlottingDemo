/********************************************************************************
** Form generated from reading ui file 'MainWindow.ui'
**
** Created: Thu 21. Jan 04:23:49 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "BrowserWindow.h"
#include "GraphWindow.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionE_xit;
    QAction *actionAddGraph;
    QAction *actionLoadGraph;
    QAction *actionSaveGraph;
    QAction *actionPlotGraph;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QMdiArea *mdiArea;
    GraphWindow *graphWnd;
    BrowserWindow *browseWnd;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(759, 576);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionE_xit = new QAction(MainWindow);
        actionE_xit->setObjectName(QString::fromUtf8("actionE_xit"));
        actionAddGraph = new QAction(MainWindow);
        actionAddGraph->setObjectName(QString::fromUtf8("actionAddGraph"));
        actionLoadGraph = new QAction(MainWindow);
        actionLoadGraph->setObjectName(QString::fromUtf8("actionLoadGraph"));
        actionSaveGraph = new QAction(MainWindow);
        actionSaveGraph->setObjectName(QString::fromUtf8("actionSaveGraph"));
        actionPlotGraph = new QAction(MainWindow);
        actionPlotGraph->setObjectName(QString::fromUtf8("actionPlotGraph"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setMargin(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        mdiArea->setMinimumSize(QSize(759, 533));
        mdiArea->setFrameShape(QFrame::StyledPanel);
        mdiArea->setActivationOrder(QMdiArea::StackingOrder);
        mdiArea->setViewMode(QMdiArea::SubWindowView);
        graphWnd = new GraphWindow();
        graphWnd->setObjectName(QString::fromUtf8("graphWnd"));
        mdiArea->addSubWindow(graphWnd);
        browseWnd = new BrowserWindow();
        browseWnd->setObjectName(QString::fromUtf8("browseWnd"));
        mdiArea->addSubWindow(browseWnd);

        verticalLayout->addWidget(mdiArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 759, 22));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(actionE_xit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionE_xit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        actionAddGraph->setText(QApplication::translate("MainWindow", "AddGraph", 0, QApplication::UnicodeUTF8));
        actionLoadGraph->setText(QApplication::translate("MainWindow", "LoadGraph", 0, QApplication::UnicodeUTF8));
        actionSaveGraph->setText(QApplication::translate("MainWindow", "SaveGraph", 0, QApplication::UnicodeUTF8));
        actionPlotGraph->setText(QApplication::translate("MainWindow", "PlotGraph", 0, QApplication::UnicodeUTF8));
        graphWnd->setWindowTitle(QApplication::translate("MainWindow", "Graph Plot Demo", 0, QApplication::UnicodeUTF8));
        browseWnd->setWindowTitle(QApplication::translate("MainWindow", "Browser", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
