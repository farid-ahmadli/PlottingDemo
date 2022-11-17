#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui>
#include <QGLWidget>
#include "DataStruct.h"
#include "TrackBall.h"

#define PI 3.1415926536

#define _P2D_

static const GLfloat colorBlack[3] = { 0.0f, 0.0f, 0.0f };
static const GLfloat colorWhite[3] = { 1.0f, 1.0f, 1.0f };
static const GLfloat scn2LB[2] = { 0.1f, 0.05f };
static const GLfloat scn2RT[2] = { 0.9f, 0.95f };

class GraphWidget : public QGLWidget
{
    Q_OBJECT

private:
    QTimer *m_timer;
    TrackBall m_trackball;
    double m_zoom;
    int m_scroll;
    bool m_active;
    bool m_title_visible;
    bool m_draw_selection;
    QPoint m_select_topleft;
    QPoint m_select_bottomright;
    Graph *m_graph;

public:
    GraphWidget(QWidget *parent = 0);
    ~GraphWidget();

protected:
    void initializeGL();    // initializes opengl
    void paintGL(); // called each time the view is refreshed
    void resizeGL(int width, int height);   // called on widget resize
    void wheelEvent(QWheelEvent *event);    // mouse wheel event for zoom
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);   // mouse press event, zoom and scroll functions realized
    void mouseMoveEvent(QMouseEvent *event);    // mouse move event, zoom and scroll functions realized

public slots:

    //
    // SOME GUI FUNCTIONALITY
    //

    bool isActive() const { return m_active; }
    void showTitle(const bool& value) { m_title_visible = value; }

    QPointF pixelPosToViewPos(const QPointF& p) { return QPointF(2.0 * float(p.x()) / width() - 1.0,
                                                                 1.0 - 2.0 * float(p.y()) / height()); }

    void setScroll(const int& scroll) { m_scroll = scroll; }

    // ...
    void clearScene();
    void plotGraph(const Graph&); // create a plot using plot data
    bool savePlotImage(const std::string& filename); // save plot as an image, in specified format
    bool savePlot2SVG(const std::string& filename);   // generate SVG from plot, save to specified file

public:

    //
    // GRAPH PLOTTING
    //
    void _glColor(const float& r, const float& g, const float& b, const bool& eval = false);
    void _glCircle3D( const double& radius, const int& slices );
    void _glFullCircle2D( const double& radius, const int& slices );
    void findDataMinMax( const DataMatrix& coords, DataArray& min, DataArray& max );

    void startGraphScene2D(const double& minX, const double& minY,
                          const double& maxX, const double& maxY);
    void startGraphScene3D(const double& minX, const double& minY, const double& minZ,
                          const double& maxX, const double& maxY, const double& maxZ);
    void endGraphScene();

    void drawLineGraph();
    void drawScatterPlot2D();
    void drawScatterPlot3D();
    void drawScatterPlotContour3D();
    //void drawSurfacePlot();
    //void drawMeshPlot();
};

#endif // GRAPHWIDGET_H
