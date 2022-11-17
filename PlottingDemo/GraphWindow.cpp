#include <QFile>

#include "GraphWindow.h"
#include "AddGraphDialog.h"

GraphWindow::GraphWindow(QWidget *parent)
        : QWidget(parent), ui(new Ui::GraphWindow), graphs(new vector<Graph>)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::savePlotImage(QString fileName)
{
    ui->graphScene->savePlotImage(fileName.toStdString());
}

void GraphWindow::on_addGraph_clicked()
{
    //
    AddGraphDialog addDialog;
    if ( addDialog.exec() ) {
        Graph graph = addDialog.getGraphData();

        QTableWidgetItem *item1 = new QTableWidgetItem( tr(graph.getPlotData().getTitle().c_str()) );
        QTableWidgetItem *item2 = new QTableWidgetItem( tr(graph.getModeStr().c_str()) );

        int rc = ui->graphTable->rowCount();
        ui->graphTable->insertRow(rc);
        ui->graphTable->setItem( rc, 0, item1 );
        ui->graphTable->setItem( rc, 1, item2 );
        graphs->push_back(graph);
    }
}

void GraphWindow::on_plotGraph_clicked()
{
    int cRow = ui->graphTable->currentRow();
    if (  cRow >= 0 ) {
        // select the graph from table and plot it
        Graph graph = graphs->at(cRow);
        ui->graphScene->plotGraph(graph);

        // hide scrollbar if graph other than linegraph is shown
        ui->hsbLineGraph->setMaximum( graph.getPlotData().getData().getDA().size()-2 );
    }
}

void GraphWindow::on_removeGraph_clicked()
{
    int cRow =ui->graphTable->currentRow();
    if ( cRow >= 0 ) {
        ui->graphTable->removeRow(cRow);
        graphs->erase( graphs->begin() + cRow );
        ui->graphScene->clearScene();
    }
}

void GraphWindow::on_editGraph_clicked()
{
    AddGraphDialog addDialog;
    int cRow =ui->graphTable->currentRow();
    if ( cRow >= 0 ) {
        addDialog.setGraphData( graphs->at(cRow) );
        addDialog.FillUI();
        if ( addDialog.exec() ) {
            graphs->at(cRow) = addDialog.getGraphData();

            QTableWidgetItem *item1 = new QTableWidgetItem( tr(addDialog.getGraphData().getPlotData().getTitle().c_str()) );
            QTableWidgetItem *item2 = new QTableWidgetItem( tr(addDialog.getGraphData().getModeStr().c_str()) );

            ui->graphTable->setItem( cRow, 0, item1 );
            ui->graphTable->setItem( cRow, 1, item2 );
        }
    }
}


void GraphWindow::on_loadGraph_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Graph Data"),
                                                    "", tr("Graph data (*.graph)"));
    if ( !fileName.isEmpty() ) {
        QFile file( fileName );
        if ( file.open( QIODevice::ReadOnly ) ) {
            Graph graph;

            QDomDocument doc("GraphData");
            doc.setContent( file.readAll(), false );
            graph.deserialize(doc.firstChildElement("Graph"));

            QTableWidgetItem *item1 = new QTableWidgetItem( tr(graph.getPlotData().getTitle().c_str()) );
            QTableWidgetItem *item2 = new QTableWidgetItem( tr(graph.getModeStr().c_str()) );

            int rc = ui->graphTable->rowCount();
            ui->graphTable->insertRow(rc);
            ui->graphTable->setItem( rc, 0, item1 );
            ui->graphTable->setItem( rc, 1, item2 );
            graphs->push_back(graph);

            file.close();
        }
    }
}

void GraphWindow::on_saveGraph_clicked()
{
    int cRow = ui->graphTable->currentRow();
    if (  cRow >= 0 ) {
        Graph graph = graphs->at(cRow);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Graph Data"),
                                                        "", tr("Graph data (*.graph)"));

        QFile file( fileName );
        if ( file.open( QIODevice::WriteOnly ) ) {
            QTextStream stream( &file );
            QDomDocument doc("GraphData");
            doc.appendChild(graph.serialize(doc));
            doc.save( stream, 4 );
            file.close();
        }
    }
}

void GraphWindow::on_graphScene_customContextMenuRequested(QPoint pos)
{

    if ( ui->graphScene->isActive() ) {

        QMenu menu(this);

        menu.addAction(ui->actionShowTitle);

        menu.exec(this->mapToGlobal(pos));
    }
}

void GraphWindow::on_actionShowTitle_triggered()
{
    ui->graphScene->showTitle(ui->actionShowTitle->isChecked());
}

void GraphWindow::on_hsbLineGraph_sliderMoved(int position)
{
    ui->graphScene->setScroll( position );
}

void GraphWindow::on_hsbLineGraph_valueChanged(int value)
{
    ui->graphScene->setScroll( value );
}
