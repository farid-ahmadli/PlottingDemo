#ifndef ADDGRAPHDIALOG_H
#define ADDGRAPHDIALOG_H

#include <QtGui/QDialog>
#include "DataStruct.h"


namespace Ui {
    class AddGraphDialog;
}

class AddGraphDialog : public QDialog {
    Q_OBJECT
public:
    AddGraphDialog(QWidget *parent = 0);
    ~AddGraphDialog();
    void FillUI();

private:
    Ui::AddGraphDialog *m_ui;
    Graph graphData;

public:
    void setGraphData(Graph& graph) {
        graphData = Graph(graph);
    }
    Graph getGraphData() const { return graphData; }
    void StringToDM( const QString& str, DataMatrix& data, const int& graphType );

private slots:
    void on_pushButton_clicked();
};

#endif // ADDGRAPHDIALOG_H
