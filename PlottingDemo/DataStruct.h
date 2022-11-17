#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <vector>
#include <QDomDocument>

#define ARRAY_SIZE 3

typedef double* DataArray;

typedef std::string* StringArray;

class DataMatrix {

private:
    std::vector<DataArray> m_data;
    std::vector<StringArray> str_data;

public:
    DataMatrix() { m_data.clear(); str_data.clear(); }
    DataMatrix(const DataMatrix& dm) {
        this->m_data = std::vector<DataArray>(dm.getDA());
        this->str_data = std::vector<StringArray>(dm.getSA());
    }
    std::vector<DataArray> getDA() const { return m_data; }
    std::vector<StringArray> getSA() const { return str_data; }
    DataArray at(const std::size_t& i) const { return m_data.at(i); }
    void push_back(const DataArray& v, const StringArray& sv) { m_data.push_back(v); str_data.push_back(sv); }
    StringArray getLabels( const int& i ) const { return str_data[i]; }
    DataArray operator[](const int& i) { return m_data[i]; }


      ///////////////////////////////////////////////////////
     //             SERIALIZING                           //
    ///////////////////////////////////////////////////////
    QDomElement serialize(QDomDocument& doc) {
        // dom element node for all lines
        QDomElement dataNode = doc.createElement("DataLines");

        // go through data lines
        for ( int i=0; i<m_data.size(); i++ ) {

            // create string by concatenating data
            std::string str = "";
            StringArray sa = str_data[i];
            for ( int j=0; j<ARRAY_SIZE; j++ ) str += sa[j] + " ";

            // write data line as new Line tag
            QDomElement lineNode = doc.createElement("Line");
            lineNode.appendChild(doc.createTextNode(str.c_str()));

            dataNode.appendChild(lineNode);
        }
        return dataNode;
    }

      ///////////////////////////////////////////////////////
     //             DESERIALIZING                         //
    ///////////////////////////////////////////////////////
    bool deserialize(const QDomElement& in) {
        if ( in.tagName().toUpper() == "DATALINES" ) {

            // initialize
            m_data.clear();
            str_data.clear();

            // get lines
            QDomNodeList list = in.elementsByTagName("Line");

            for ( int i=0; i<in.childNodes().size(); i++ ) {
                // convert to line element
                QDomElement lineNode(list.at(i).toElement());

                if ( lineNode.tagName().toUpper() == "LINE") {

                    // extract data by splitting it
                    QStringList values;
                    values = lineNode.text().split( QRegExp("(\\s+)"), QString::SkipEmptyParts );

                    // parse data and insert into arrays
                    DataArray v = new double[ARRAY_SIZE];
                    StringArray sv = new std::string[ARRAY_SIZE];
                    for ( int j=0; j<ARRAY_SIZE; j++ ) {
                        QString tmp = values[j];
                        bool ok;
                        sv[j] = tmp.toStdString();
                        v[j] = tmp.toDouble(&ok);
                    }

                    m_data.push_back(v);
                    str_data.push_back(sv);
                }
            }

            return true; // ok
        }
        return false; // something went wrong
    }
};

//
class PlotData
{

private:

    std::string m_title;
    std::string m_footer;
    std::string m_xAxisLabel;
    std::string m_yAxisLabel;
    std::string m_zAxisLabel;

    DataMatrix m_data; //data to be plotted

public:
    PlotData() { }
    PlotData(const PlotData& pd) {
        this->m_title = pd.getTitle();
        this->m_footer = pd.getFooter();
        this->m_xAxisLabel = pd.getXAxisLabel();
        this->m_yAxisLabel = pd.getYAxisLabel();
        this->m_zAxisLabel = pd.getZAxisLabel();
        this->m_data = DataMatrix(pd.getData());
    }
    // getters and setters of private variables
    std::string getTitle() const { return m_title; }
    void setTitle(const std::string& value) { m_title = value; }
    std::string getFooter() const { return m_footer; }
    void setFooter(const std::string& value) { m_footer = value; }
    std::string getXAxisLabel() const { return m_xAxisLabel; }
    void setXAxisLabel(const std::string& value) { m_xAxisLabel = value; }
    std::string getYAxisLabel() const { return m_yAxisLabel; }
    void setYAxisLabel(const std::string& value) { m_yAxisLabel = value; }
    std::string getZAxisLabel() const { return m_zAxisLabel; }
    void setZAxisLabel(const std::string& value) { m_zAxisLabel = value; }

    DataMatrix getData() const { return m_data; }
    void setData(const DataMatrix& value) { m_data = DataMatrix(value); }

      ///////////////////////////////////////////////////////
     //             SERIALIZING                           //
    ///////////////////////////////////////////////////////
    QDomElement serialize(QDomDocument& doc) {
        // Title
        QDomElement titleNode = doc.createElement("Title");
        titleNode.appendChild(doc.createTextNode(m_title.c_str()));

        // Footer
        QDomElement footerNode = doc.createElement("Footer");
        footerNode.appendChild(doc.createTextNode(m_footer.c_str()));

        // XAxis
        QDomElement xAxisNode = doc.createElement("XLabel");
        xAxisNode.appendChild(doc.createTextNode(m_xAxisLabel.c_str()));

        // YAxis
        QDomElement yAxisNode = doc.createElement("YLabel");
        yAxisNode.appendChild(doc.createTextNode(m_yAxisLabel.c_str()));

        // ZAxis
        QDomElement zAxisNode = doc.createElement("ZLabel");
        zAxisNode.appendChild(doc.createTextNode(m_zAxisLabel.c_str()));

        // Data
        QDomElement dataNode;
        dataNode = m_data.serialize(doc);

        // PlotData
        QDomElement plotDataNode = doc.createElement("PlotData");
        plotDataNode.appendChild(titleNode);
        plotDataNode.appendChild(footerNode);
        plotDataNode.appendChild(xAxisNode);
        plotDataNode.appendChild(yAxisNode);
        plotDataNode.appendChild(zAxisNode);
        plotDataNode.appendChild(dataNode);

        return plotDataNode;
    }


      ///////////////////////////////////////////////////////
     //             DESERIALIZING                         //
    ///////////////////////////////////////////////////////
    bool deserialize(const QDomElement& in) {
        if ( in.tagName().toUpper() == "PLOTDATA") {
            // Title
            m_title = in.firstChildElement("Title").text().toStdString();
            // Footer
            m_footer = in.firstChildElement("Footer").text().toStdString();
            // xAxisLabel
            m_xAxisLabel = in.firstChildElement("XLabel").text().toStdString();
            // yAxisLabel
            m_yAxisLabel = in.firstChildElement("YLabel").text().toStdString();
            // zAxisLabel
            m_zAxisLabel = in.firstChildElement("ZLabel").text().toStdString();
            // Data
            return m_data.deserialize( in.firstChildElement("DataLines") );
        }
        return false;
    }
};

//
struct LegendItem
{

private:
    std::string m_name;
    long m_color;

public:
    LegendItem() {}
    LegendItem(const std::string& name, const long color): m_name(name), m_color(color) {}
    std::string getName() const { return m_name; }
    long getColor() const { return m_color; }

      ///////////////////////////////////////////////////////
     //             SERIALIZING                           //
    ///////////////////////////////////////////////////////
    QDomElement serialize(QDomDocument& doc) {
        // Name
        QDomElement nameNode = doc.createElement("Name");
        nameNode.appendChild(doc.createTextNode(getName().c_str()));

        // Color
        QDomElement colorNode = doc.createElement("Color");
        colorNode.appendChild(doc.createTextNode(QString("%1").arg(getColor()).toStdString().c_str()));

        // Legend Item
        QDomElement liNode = doc.createElement("LegendItem");
        liNode.appendChild(nameNode);
        liNode.appendChild(colorNode);

        return liNode;
    }

       ///////////////////////////////////////////////////////
     //             DESERIALIZING                         //
    ///////////////////////////////////////////////////////
    bool deserialize(const QDomElement& in) {
        if ( in.tagName().toUpper() == "LEGENDITEM") {
            bool ok;

            // Legend Item Name
            m_name = in.firstChildElement("Name").text().toStdString();
            // Legend Item Color
            m_color = in.firstChildElement("Color").text().toLong(&ok, 10);

            return true;
        }

        return false;
    }

};

//
class Legend
{

private:
    long m_bordercolor;
    long m_borderweight;
    bool m_visible;
    std::vector<LegendItem> m_items;

public:
    Legend() {}
    Legend(const long bcolor, const long bweight, const bool vis):
            m_bordercolor(bcolor), m_borderweight(bweight), m_visible(vis) {}

    void addItem(const LegendItem& li) { m_items.push_back( li ); }
    void delItem(const size_t pos) { m_items.erase( m_items.begin()+pos ); }
    LegendItem item(const size_t pos) const { return m_items[pos]; }

      ///////////////////////////////////////////////////////
     //             SERIALIZING                           //
    ///////////////////////////////////////////////////////
    QDomElement serialize(QDomDocument& doc) {
        // Border Color
        QDomElement bcNode = doc.createElement("BorderColor");
        bcNode.appendChild(doc.createTextNode(QString("%1").arg(m_bordercolor).toStdString().c_str()));

        // Border Width
        QDomElement bwNode = doc.createElement("BorderWidth");
        bwNode.appendChild(doc.createTextNode(QString("%1").arg(m_bordercolor).toStdString().c_str()));

        // Legend Items
        QDomElement itemNode = doc.createElement("Items");
        for (int i=0; i<m_items.size(); i++)
            itemNode.appendChild(item(i).serialize(doc));

        QDomElement legendNode = doc.createElement("Legend");
        legendNode.appendChild(bcNode);
        legendNode.appendChild(bwNode);
        legendNode.appendChild(itemNode);

        return legendNode;
    }

      ///////////////////////////////////////////////////////
     //             DESERIALIZING                         //
    ///////////////////////////////////////////////////////
    bool deserialize(const QDomElement& in) {
        if ( in.tagName().toUpper() == "LEGEND") {
            bool ok;

            // Border Color
            m_bordercolor = in.firstChildElement("BorderColor").text().toLong(&ok, 10);
            // Border Color
            m_borderweight = in.firstChildElement("BorderWidth").text().toLong(&ok, 10);

            m_items.clear();
            // Plot Data
            QDomNodeList lst = in.firstChildElement("Items").elementsByTagName("LegendItem");
            for ( int i=0; i<lst.size(); i++ ) {
                LegendItem li;
                li.deserialize( lst.at(i).toElement() );
                addItem( li );
            }

            return true;
        }
        return false;
    }
};

//
class Graph
{

public:
    enum Mode { LineGraph = 0, ScatterPlot2D, ScatterPlot3D, ScatterPlotContour3D, SurfacePlot, MeshPlot };
    enum ImageFormat { PngFormat = 0, JpegFormat, GifFormat };
    enum AxisType { xAxis = 0, yAxis, ZAxis };

private:
    Mode     m_mode;
    Legend   m_legend;
    PlotData m_plotdata;

public:
    Graph() {}
    Graph(const Graph& g) { this->m_mode = g.getMode();
        this->m_plotdata = g.getPlotData();
        this->m_legend = g.getLegend(); }

    // ++++++ MODE
    Mode getMode() const { return m_mode; }
    std::string getModeStr() const {
        switch(m_mode){
        case LineGraph: return "Line Graph";
        case ScatterPlot2D: return "2D Scatter Plot";
        case ScatterPlot3D: return "3D Scatter Plot";
        case ScatterPlotContour3D: return "3D Scatter Plot with Contour Map";
        case SurfacePlot: return "Surface Plot";
        case MeshPlot: return "Mesh Plot";
        };
        return "";
    }
    Mode getStrMode( const QString& value ) const {
        QString str = value.toUpper();
        if ( str == "LINE GRAPH" ) return LineGraph;
        if ( str == "2D SCATTER PLOT" ) return ScatterPlot2D;
        if ( str == "3D SCATTER PLOT" ) return ScatterPlot3D;
        if ( str == "3D SCATTER PLOT WITH CONTOUR MAP" ) return ScatterPlotContour3D;
        if ( str == "SURFACE PLOT" ) return SurfacePlot;
        if ( str == "MESH PLOT" ) return MeshPlot;
        return (Mode)0;
    }
    void setMode(const Mode& value) { m_mode = value; }
    // ------ MODE

    Legend getLegend() const { return m_legend; }
    void setLegend(const Legend& value) { m_legend = value; }
    PlotData getPlotData() const { return m_plotdata; }
    void setPlotData(const PlotData& value) { m_plotdata = PlotData(value); }

      ///////////////////////////////////////////////////////
     //             SERIALIZING                           //
    ///////////////////////////////////////////////////////
    QDomElement serialize(QDomDocument& doc) {
        // Mode
        QDomElement modeNode = doc.createElement("Mode");
        modeNode.appendChild(doc.createTextNode(getModeStr().c_str()));

        // Legend
        QDomElement legendNode = m_legend.serialize(doc);

        // PlotData
        QDomElement plotDataNode = m_plotdata.serialize(doc);

        // Graph
        QDomElement graphNode = doc.createElement("Graph");
        graphNode.appendChild(modeNode);
        graphNode.appendChild(legendNode);
        graphNode.appendChild(plotDataNode);

        return graphNode;
    }

      ///////////////////////////////////////////////////////
     //             DESERIALIZING                         //
    ///////////////////////////////////////////////////////
    bool deserialize(const QDomElement& in) {
        if ( in.tagName().toUpper() == "GRAPH") {
            // Mode
            m_mode = getStrMode(in.firstChildElement("Mode").text());

            // Legend
            m_legend.deserialize(in.firstChildElement("Legend"));

            // Plot Data
            m_plotdata.deserialize(in.firstChildElement("PlotData"));

            return true;
        }
        return false;
    }
};

#endif // DATA_STRUCT_H
