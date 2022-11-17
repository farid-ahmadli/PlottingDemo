#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QWidget>

// UI
#include "DataStruct.h"
#include "ui_GraphWindow.h"
#include "ui_AddGraphDialog.h"

// stl
#include <list>


using namespace std;

namespace Ui
{
    class GraphWindow;
}

class GraphWindow : public QWidget
{
    Q_OBJECT

public:
    GraphWindow(QWidget *parent = 0);
    ~GraphWindow();

//    Graph loadGraph(const QString&);
//    void saveGraph(const QString&, const Graph&);
    void savePlotImage(QString fileName);

private:
    Ui::GraphWindow *ui;
    vector<Graph> *graphs;
    Graph *currentGraph;

private slots:
    void on_hsbLineGraph_valueChanged(int value);
    void on_hsbLineGraph_sliderMoved(int position);
    void on_actionShowTitle_triggered();
    void on_graphScene_customContextMenuRequested(QPoint pos);
    void on_saveGraph_clicked();
    void on_editGraph_clicked();
    void on_removeGraph_clicked();
    void on_plotGraph_clicked();
    void on_addGraph_clicked();
    void on_loadGraph_clicked();
};

#endif // GRAPHWINDOW_H
