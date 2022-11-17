#include "AddGraphDialog.h"
#include "ui_AddGraphDialog.h"
#include <iostream>

AddGraphDialog::AddGraphDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AddGraphDialog)
{
    m_ui->setupUi(this);
}

AddGraphDialog::~AddGraphDialog()
{
    delete m_ui;
}

void AddGraphDialog::FillUI()
{
    PlotData pd = graphData.getPlotData();
    m_ui->tfPlotTitle->setText( pd.getTitle().c_str() );
    m_ui->tfPlotFooter->setText( pd.getFooter().c_str() );
    m_ui->tfXAxisLabel->setText( pd.getXAxisLabel().c_str() );
    m_ui->tfYAxisLabel->setText( pd.getYAxisLabel().c_str() );
    m_ui->tfZAxisLabel->setText( pd.getZAxisLabel().c_str() );

    std::string str = "";
    StringArray sa;

    for ( int i=0; i<pd.getData().getDA().size(); i++ ) {
        sa = pd.getData().getLabels(i);
        std::string tmp = "";
        for ( int j=0; j<ARRAY_SIZE; j++ ) tmp += sa[j] + " ";
        str += tmp + "\n";
    }

    m_ui->pteGraphData->setPlainText(str.c_str());

    m_ui->cbGraphType->setCurrentIndex( (int)graphData.getMode() );
}

void AddGraphDialog::StringToDM( const QString& str, DataMatrix& data, const int& graphType )
{
    // splitting text into lines
    QStringList lines = str.split( tr("\n"), QString::SkipEmptyParts, Qt::CaseInsensitive );

    int index = graphType;

    // and now parse each line to extract values into dataarray
    //
    for ( int i=0; i<lines.size(); i++ ) {
        QStringList values = lines.at(i).split( QRegExp("(\\s+)"), QString::SkipEmptyParts );

        DataArray v = new double[ARRAY_SIZE];
        StringArray sv = new std::string[ARRAY_SIZE];
        for ( int j=0; j<values.size(); j++ ) {
            QString tmp = values.at(j);
            bool ok;
            sv[j] = tmp.toStdString();
            v[j] =  tmp.toDouble(&ok);

            if ( ( index!=1 && !ok ) || ( index==1 && j==0 ) ) {
                // if scatter plot 2D selected
                // first element of the line must be a string label
                // string label: AAA AAB AAC ... ZZX ZZY ZZZ
                if ( index != 1 ||
                     tmp.size()!=3 ||
                     !tmp[0].isUpper() ||
                     !tmp[1].isUpper() ||
                     !tmp[2].isUpper() ) {
                    this->reject();
                    return;
                }
            }
        }

        data.push_back(v, sv);
    }

    //graphData = 0;
}
void AddGraphDialog::on_pushButton_clicked()
{
    if ( !m_ui->tfPlotTitle->text().isEmpty() && !m_ui->tfPlotFooter->text().isEmpty() ) {

        graphData = Graph();

        // setting graph mode
        graphData.setMode( (Graph::Mode)m_ui->cbGraphType->currentIndex() );

        // getting some text data
        PlotData plotData;
        plotData.setTitle( m_ui->tfPlotTitle->text().toStdString() );
        plotData.setFooter( m_ui->tfPlotFooter->text().toStdString() );
        plotData.setXAxisLabel( m_ui->tfXAxisLabel->text().toStdString() );
        plotData.setYAxisLabel( m_ui->tfYAxisLabel->text().toStdString() );
        plotData.setZAxisLabel( m_ui->tfZAxisLabel->text().toStdString() );

        // parsing coordinates
        DataMatrix coordData;

        StringToDM( m_ui->pteGraphData->toPlainText(), coordData, m_ui->cbGraphType->currentIndex() );

        plotData.setData(coordData);

        // setting plot data of the graph
        graphData.setPlotData(plotData);

        // TODO legend ...



        this->accept();
    }
    else
        this->reject();
}
