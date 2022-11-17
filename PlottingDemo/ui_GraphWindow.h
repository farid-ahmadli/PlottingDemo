/********************************************************************************
** Form generated from reading ui file 'GraphWindow.ui'
**
** Created: Thu 21. Jan 04:23:49 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_GRAPHWINDOW_H
#define UI_GRAPHWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QScrollBar>
#include <QtGui/QSplitter>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "GraphWidget.h"

QT_BEGIN_NAMESPACE

class Ui_GraphWindow
{
public:
    QAction *actionSavePlotImage;
    QAction *actionGenerateSVG;
    QAction *actionShowTitle;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *addGraph;
    QPushButton *editGraph;
    QPushButton *removeGraph;
    QPushButton *loadGraph;
    QPushButton *saveGraph;
    QPushButton *plotGraph;
    QTableWidget *graphTable;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    GraphWidget *graphScene;
    QScrollBar *hsbLineGraph;

    void setupUi(QWidget *GraphWindow)
    {
        if (GraphWindow->objectName().isEmpty())
            GraphWindow->setObjectName(QString::fromUtf8("GraphWindow"));
        GraphWindow->resize(586, 304);
        GraphWindow->setAutoFillBackground(true);
        GraphWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionSavePlotImage = new QAction(GraphWindow);
        actionSavePlotImage->setObjectName(QString::fromUtf8("actionSavePlotImage"));
        actionGenerateSVG = new QAction(GraphWindow);
        actionGenerateSVG->setObjectName(QString::fromUtf8("actionGenerateSVG"));
        actionShowTitle = new QAction(GraphWindow);
        actionShowTitle->setObjectName(QString::fromUtf8("actionShowTitle"));
        actionShowTitle->setCheckable(true);
        verticalLayout = new QVBoxLayout(GraphWindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setMargin(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(GraphWindow);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setMidLineWidth(4);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(false);
        splitter->setHandleWidth(4);
        splitter->setChildrenCollapsible(false);
        dockWidget = new QDockWidget(splitter);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidget->sizePolicy().hasHeightForWidth());
        dockWidget->setSizePolicy(sizePolicy);
        dockWidget->setMinimumSize(QSize(220, 123));
        dockWidget->setMaximumSize(QSize(220, 524287));
        dockWidget->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setMargin(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_2 = new QWidget(dockWidgetContents);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(0, 30));
        widget_2->setMaximumSize(QSize(16777215, 30));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setMargin(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addGraph = new QPushButton(widget_2);
        addGraph->setObjectName(QString::fromUtf8("addGraph"));
        sizePolicy.setHeightForWidth(addGraph->sizePolicy().hasHeightForWidth());
        addGraph->setSizePolicy(sizePolicy);
        addGraph->setMaximumSize(QSize(40, 16777215));
        addGraph->setAutoDefault(false);
        addGraph->setFlat(false);

        horizontalLayout->addWidget(addGraph);

        editGraph = new QPushButton(widget_2);
        editGraph->setObjectName(QString::fromUtf8("editGraph"));
        editGraph->setEnabled(true);
        sizePolicy.setHeightForWidth(editGraph->sizePolicy().hasHeightForWidth());
        editGraph->setSizePolicy(sizePolicy);
        editGraph->setMaximumSize(QSize(40, 16777215));
        editGraph->setAutoDefault(false);
        editGraph->setFlat(false);

        horizontalLayout->addWidget(editGraph);

        removeGraph = new QPushButton(widget_2);
        removeGraph->setObjectName(QString::fromUtf8("removeGraph"));
        sizePolicy.setHeightForWidth(removeGraph->sizePolicy().hasHeightForWidth());
        removeGraph->setSizePolicy(sizePolicy);
        removeGraph->setMaximumSize(QSize(40, 16777215));
        removeGraph->setAutoDefault(false);
        removeGraph->setFlat(false);

        horizontalLayout->addWidget(removeGraph);

        loadGraph = new QPushButton(widget_2);
        loadGraph->setObjectName(QString::fromUtf8("loadGraph"));
        loadGraph->setEnabled(true);
        sizePolicy.setHeightForWidth(loadGraph->sizePolicy().hasHeightForWidth());
        loadGraph->setSizePolicy(sizePolicy);
        loadGraph->setMaximumSize(QSize(40, 16777215));
        loadGraph->setAutoDefault(false);
        loadGraph->setFlat(false);

        horizontalLayout->addWidget(loadGraph);

        saveGraph = new QPushButton(widget_2);
        saveGraph->setObjectName(QString::fromUtf8("saveGraph"));
        saveGraph->setEnabled(true);
        sizePolicy.setHeightForWidth(saveGraph->sizePolicy().hasHeightForWidth());
        saveGraph->setSizePolicy(sizePolicy);
        saveGraph->setMaximumSize(QSize(40, 16777215));
        saveGraph->setAutoDefault(false);
        saveGraph->setFlat(false);

        horizontalLayout->addWidget(saveGraph);

        plotGraph = new QPushButton(widget_2);
        plotGraph->setObjectName(QString::fromUtf8("plotGraph"));
        plotGraph->setEnabled(true);
        sizePolicy.setHeightForWidth(plotGraph->sizePolicy().hasHeightForWidth());
        plotGraph->setSizePolicy(sizePolicy);
        plotGraph->setMaximumSize(QSize(40, 16777215));
        plotGraph->setAutoDefault(false);
        plotGraph->setFlat(false);

        horizontalLayout->addWidget(plotGraph);


        verticalLayout_2->addWidget(widget_2);

        graphTable = new QTableWidget(dockWidgetContents);
        if (graphTable->columnCount() < 2)
            graphTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        graphTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        graphTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        graphTable->setObjectName(QString::fromUtf8("graphTable"));
        graphTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        graphTable->setAlternatingRowColors(true);
        graphTable->setSelectionMode(QAbstractItemView::SingleSelection);
        graphTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        graphTable->horizontalHeader()->setCascadingSectionResizes(false);
        graphTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_2->addWidget(graphTable);

        dockWidget->setWidget(dockWidgetContents);
        splitter->addWidget(dockWidget);
        frame = new QFrame(splitter);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setMargin(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        graphScene = new GraphWidget(frame);
        graphScene->setObjectName(QString::fromUtf8("graphScene"));
        graphScene->setCursor(QCursor(Qt::ArrowCursor));
        graphScene->setMouseTracking(true);
        graphScene->setContextMenuPolicy(Qt::CustomContextMenu);
        graphScene->setAutoFillBackground(false);

        verticalLayout_3->addWidget(graphScene);

        hsbLineGraph = new QScrollBar(frame);
        hsbLineGraph->setObjectName(QString::fromUtf8("hsbLineGraph"));
        hsbLineGraph->setEnabled(true);
        hsbLineGraph->setAutoFillBackground(false);
        hsbLineGraph->setMaximum(100);
        hsbLineGraph->setOrientation(Qt::Horizontal);
        hsbLineGraph->setInvertedAppearance(false);
        hsbLineGraph->setInvertedControls(true);

        verticalLayout_3->addWidget(hsbLineGraph);

        splitter->addWidget(frame);

        verticalLayout->addWidget(splitter);


        retranslateUi(GraphWindow);

        QMetaObject::connectSlotsByName(GraphWindow);
    } // setupUi

    void retranslateUi(QWidget *GraphWindow)
    {
        GraphWindow->setWindowTitle(QApplication::translate("GraphWindow", "Form", 0, QApplication::UnicodeUTF8));
        actionSavePlotImage->setText(QApplication::translate("GraphWindow", "Save Plot as Image...", 0, QApplication::UnicodeUTF8));
        actionGenerateSVG->setText(QApplication::translate("GraphWindow", "Generate SVG", 0, QApplication::UnicodeUTF8));
        actionShowTitle->setText(QApplication::translate("GraphWindow", "Show Title", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionShowTitle->setToolTip(QApplication::translate("GraphWindow", "Show Title of the Graph", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        dockWidget->setWindowTitle(QApplication::translate("GraphWindow", "Graphs", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        addGraph->setToolTip(QApplication::translate("GraphWindow", "Add a new graph to the list", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addGraph->setText(QApplication::translate("GraphWindow", "Add", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editGraph->setToolTip(QApplication::translate("GraphWindow", "Add a new graph to the list", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editGraph->setText(QApplication::translate("GraphWindow", "Edit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        removeGraph->setToolTip(QApplication::translate("GraphWindow", "Remove existing graph from the list", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        removeGraph->setText(QApplication::translate("GraphWindow", "Del", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        loadGraph->setToolTip(QApplication::translate("GraphWindow", "Load a graph from file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        loadGraph->setText(QApplication::translate("GraphWindow", "Load", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveGraph->setToolTip(QApplication::translate("GraphWindow", "Save the graph in the list to file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveGraph->setText(QApplication::translate("GraphWindow", "Save", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        plotGraph->setToolTip(QApplication::translate("GraphWindow", "Plot graph data", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        plotGraph->setText(QApplication::translate("GraphWindow", "Plot", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = graphTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("GraphWindow", "Title", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = graphTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("GraphWindow", "Type", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(GraphWindow);
    } // retranslateUi

};

namespace Ui {
    class GraphWindow: public Ui_GraphWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHWINDOW_H
