#include "GraphWidget.h"

GraphWidget::GraphWidget(QWidget *parent)
        : QGLWidget(parent)
{
    m_graph = 0;
    m_trackball = TrackBall(0.0f, gfx::Vector3f::vector(1, 1, 1), TrackBall::Sphere);
    m_scroll = 0;
    m_zoom = 600;
    m_title_visible = false;
    m_active = false;
    m_draw_selection = false;

    m_timer = new QTimer(this);
    m_timer->setInterval(40);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start();

    this->setAutoBufferSwap(true);
}

GraphWidget::~GraphWidget()
{
}

//==============================================================
//                      OPENGL
//==============================================================


void GraphWidget::initializeGL()
{
    glEnable( GL_NORMALIZE );
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);
    glDepthMask(GL_FALSE);
    glClearDepth( 1.0f );
    glClearColor( 0.8f, 0.8f, 0.8f, 1.0f );

    glEnable(GL_BLEND);
}

void GraphWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    bool _2d = false;

    // check if there is an active graph waiting to be plotted
    if ( m_graph != 0 ) {

        if ( m_title_visible ) {
            _glColor(0, 0.6, 0.2);
            renderText( width()/2 - 10, 20, tr(m_graph->getPlotData().getTitle().c_str()) );
        }

        if ( m_graph->getMode() == Graph::LineGraph ||
             m_graph->getMode() == Graph::ScatterPlot2D ) {

            _2d = true;

        }
        else {
            gfx::Matrix4x4f view;
            m_trackball.rotation().matrix( view );
            view(3, 2) -= 2.0f * exp( m_zoom / 1200.0f);
            glLoadMatrixf( view.bits() );
        }

        // check graph style
        switch ( m_graph->getMode() ) {

            // LINE GRAPH
        case Graph::LineGraph:
            drawLineGraph(); break;

            // SCATTER PLOT 2D
        case Graph::ScatterPlot2D:
            drawScatterPlot2D(); break;

            // SCATTER PLOT 3D
        case Graph::ScatterPlot3D:
            drawScatterPlot3D(); break;

            // SCATTER PLOT 3D with CONTOUR MAP
        case Graph::ScatterPlotContour3D:
            drawScatterPlotContour3D(); break;

            // SURFACE PLOT
//        case Graph::SurfacePlot:
//            drawSurfacePlot(); break;
//
//            // MESH
//        case Graph::MeshPlot:
//            drawMeshPlot(); break;

        default:;
        }

        // draw selection rectangle above 2D graphs
        // used for zoom function in 2D scatter plot
        if ( _2d && m_draw_selection ) {
            glBegin(GL_LINE_LOOP);

            _glColor(0.2f, 0.5f, 0.6f);

            glVertex2f(1.0*m_select_topleft.x()/this->width(), 1.0*m_select_topleft.y()/this->height());
            glVertex2f(1.0*m_select_topleft.x()/this->width(), 1.0*m_select_bottomright.y()/this->height());
            glVertex2f(1.0*m_select_bottomright.x()/this->width(), 1.0*m_select_bottomright.y()/this->height());
            glVertex2f(1.0*m_select_bottomright.x()/this->width(), 1.0*m_select_topleft.y()/this->height());
            glEnd();
        }
    }
}

void GraphWidget::resizeGL(int width, int height)
{
    //int side = qMin(width, height);
    //glViewport((width - side) / 2, (height - side) / 2, side, side);

    glViewport( 0, 0, width, height );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    if ( m_graph != 0 && ( m_graph->getMode() == Graph::LineGraph ||
                           m_graph->getMode() == Graph::ScatterPlot2D ) ) {

        gluOrtho2D( 0, 1, 0, 1 );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    else {

        gluPerspective(70.0, 1.0, 0.1, 50.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(1.5, 1.5, 1.5,    // looking from
                  0.0, 0.0, 0.0,    // looking at
                  0.0, 0.0, 1.0);   // up direction vector



    }
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    m_zoom += event->delta();
    if (m_zoom < -1500 ) m_zoom = -1500;
    if (m_zoom > 1500) m_zoom = 1500;
    event->accept();
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {

        m_draw_selection = true;
        m_select_topleft = event->pos();
        m_select_topleft.setY( this->height() - m_select_topleft.y() );
        m_select_bottomright = m_select_topleft;

        m_trackball.push( pixelPosToViewPos(event->pos()), gfx::Quaternionf::identity() );
        event->accept();
    }
}

void GraphWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_draw_selection = false;
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event)
{
    //int dx = event->x() - lastPos.x();
    //int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        m_trackball.move(pixelPosToViewPos(event->pos()), gfx::Quaternionf::identity());

        m_select_bottomright = event->pos();
        m_select_bottomright.setY( this->height() - m_select_bottomright.y() );

        event->accept();
    } else {
        //m_trackball.release(pixelPosToViewPos(event->pos()), gfx::Quaternionf::identity());
    }

    //if (event->buttons() & Qt::LeftButton) {
    //   trackball.move( pixelPosToViewPos(event->scenePos()), gfx::Quaternionf::identity() );
    // event->accept();
    //  } else if (event->buttons() & Qt::RightButton) {
    //setXRotation(xRot + dy);
    //setZRotation(zRot + dx);
    //zoomInOut(zoom+0.1*dy);
    //}
    //lastPos = event->pos();
}


//==============================================================
//                      PLOTTING
//==============================================================


void GraphWidget::clearScene()
{
    m_graph = 0;
    m_zoom = 600;
}

void GraphWidget::plotGraph(const Graph& graph)
{
    m_graph = new Graph(graph);

    // init
    m_trackball = TrackBall(0.0f, gfx::Vector3f::vector(1, 1, 1), TrackBall::Sphere);
    m_zoom = 0;
    m_scroll = 0;
    m_title_visible = false;
    m_active = true;

    resizeGL(this->width(), this->height());
}

void GraphWidget::_glColor(const float &r, const float &g, const float &b, const bool& eval)
{
    if ( eval ) {
        QColor c = QColor::fromHsvF( sqrt(r*r+g*g+b*b)/1.75, 1, 1 );
        glColor3f( c.redF(), c.greenF(), c.blueF() );
    }
    else {
        glColor3f( (GLfloat)r, (GLfloat)g, (GLfloat)b );
    }
    //qglColor( QColor(r, g, b, 0) );
}

void GraphWidget::_glCircle3D( const double& radius, const int& slices )
{
    GLfloat x, y, z;
    double delta, alfa;

    alfa = 0.0f;
    delta = 2.0f*PI/slices;

    glBegin( GL_LINE_LOOP );

    for ( int i=0; i<slices; i++ ) {
        x = radius*cos(alfa);
        y = radius*sin(alfa);
        z = 0.0f;
        glVertex3f( x, y, z );

        alfa += delta;
    }

    glEnd();
}

void GraphWidget::_glFullCircle2D( const double& radius, const int& slices )
{
    GLfloat x, y;
    double delta, alfa;

    alfa = 0.0f;
    delta = 2.0f*PI/slices;

    glBegin( GL_TRIANGLE_FAN );

    glVertex2f( 0.0f, 0.0f );

    for ( int i=0; i<=slices; i++ ) {
        x = radius*cos(alfa);
        y = radius*sin(alfa);
        glVertex2f( x, y );

        alfa += delta;
    }

    glEnd();
}

// finds 3 max data from data matrix for x,y and z
void GraphWidget::findDataMinMax( const DataMatrix& coords, DataArray& min, DataArray& max )
{
    if ( coords.getDA().size() > 0 ) {

        min = new double[ARRAY_SIZE];
        max = new double[ARRAY_SIZE];

        for ( int i=0; i<ARRAY_SIZE; i++ ) {
            min[i] = 10000000;
            max[i] = -10000000;
        }

        // find minimium and maximum for coordinates
        for ( int i=0; i<coords.getDA().size(); i++ ) {
            DataArray crd = coords.at(i);

            for ( int j=0; j<ARRAY_SIZE; j++ )
                if ( crd[j] < min[j] )
                    min[j] = crd[j];

            for ( int j=0; j<ARRAY_SIZE; j++ )
                if ( crd[j] > max[j] )
                    max[j] = crd[j];
        }

        for ( int i=0; i<ARRAY_SIZE; i++ )
            if ( max[i] == min[i] ) max[i] = min[i]+1;

    }
}

void GraphWidget::startGraphScene2D(const double& minX, const double& minY, const double& maxX, const double& maxY)
{
    DataMatrix coordinates = m_graph->getPlotData().getData();
    double zoom = 1.0*(m_zoom+1500)/3000;
    int n_zoom = (int)(zoom*coordinates.getDA().size());
    int xN = n_zoom<20?n_zoom:20;
    if ( xN < 2 ) xN = 2;
    int yN = 10;
    double xStep = 1.0/xN;
    double yStep = 1.0/yN;

    glPushMatrix();

    // WHITE BOARD
    glBegin(GL_QUADS);
    glColor3fv( colorWhite );
    // leaving 20% space from sides empty
    glVertex2f( scn2LB[0], scn2LB[1] );
    glVertex2f( scn2RT[0], scn2LB[1] );
    glVertex2f( scn2RT[0], scn2RT[1] );
    glVertex2f( scn2LB[0], scn2RT[1] );
    glEnd();


    // AXIS
    glBegin(GL_LINE_LOOP);
    glColor3fv( colorBlack );
    glVertex2f( scn2LB[0], scn2LB[1] );
    glVertex2f( scn2RT[0], scn2LB[1] );
    glVertex2f( scn2RT[0], scn2RT[1] );
    glVertex2f( scn2LB[0], scn2RT[1] );
    glEnd();


    // DASHED PARALEL AXIS LINES
    glEnable(GL_LINE_STIPPLE);         /* dashed lines */
    glLineStipple(1, 0xF0F0);
    glBegin( GL_LINES );
    _glColor( 0.5f, 0.5f, 0.5f );
    float p, x, y;

    // X
    p = xStep;
    for ( int i=1; i<xN; i++ ) {
        x = scn2LB[0] + (scn2RT[0]-scn2LB[0])*p;
        glVertex2f( x, scn2LB[1] );
        glVertex2f( x, scn2RT[1] );
        p += xStep;
    }
    // Y
    p = yStep;
    for ( int i=1; i<yN; i++ ) {
        y = scn2LB[1] + (scn2RT[1]-scn2LB[1])*p;
        glVertex2f( scn2LB[0], y );
        glVertex2f( scn2RT[0], y );
        p += yStep;
    }
    glEnd();
    glDisable( GL_LINE_STIPPLE );

    _glColor(0, 0, 0);

    // X
    p = 0.0;
    for ( int i=0; i<=xN; i++ ) {
        x = scn2LB[0] + (scn2RT[0]-scn2LB[0])*p;
        float f = minX + p*(maxX-minX);
        renderText( x, 0.01f, 0.0f, QString("%1").arg(f, 0, 'f', 1) );
        p += xStep;
    }
    // Y
    p = 0.0;
    for ( int i=0; i<=yN; i++ ) {
        y = scn2LB[1] + (scn2RT[1]-scn2LB[1])*p;
        float f = minY + p*(maxY-minY);
        renderText( 0.01f, y, 0.0f, QString("%1").arg(f, 0, 'f', 1) );
        p += yStep;
    }

    glTranslatef( scn2LB[0], scn2LB[1], 0.0f );
}

// draws a scene for plot, 3 axis coordinate system
void GraphWidget::startGraphScene3D(const double& minX, const double& minY, const double& minZ,
                          const double& maxX, const double& maxY, const double& maxZ)
{

    glPushMatrix();

    static const int NN = 5;
    double step = 1.0/NN;

    glRotatef( 90.0f, 0.0f, 0.0f, -1.0f );
    glRotatef( 80.0f, 0.0f, -1.0f, 0.0f );
    glRotatef( 40.0f, 0.0f, 0.0f, -1.0f );
    //glRotatef( 90.0f, 0.5f, 0.0f, 0.0f );
    glTranslatef( -0.5f, -0.5f, -0.5f );

    glPushMatrix();


    // drawing axis and planes

    glBegin(GL_QUADS);//==============================================================

    glColor3fv( colorWhite );

    // X constant (Y Z plane)
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( 0.0f, 1.0f, 0.0f );
    glVertex3f( 0.0f, 1.0f, 1.0f );
    glVertex3f( 0.0f, 0.0f, 1.0f );

    // Y constant (X Z plane)
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( 0.0f, 0.0f, 1.0f );
    glVertex3f( 1.0f, 0.0f, 1.0f );
    glVertex3f( 1.0f, 0.0f, 0.0f );

    // Z constant (X Y plane)
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( 1.0f, 0.0f, 0.0f );
    glVertex3f( 1.0f, 1.0f, 0.0f );
    glVertex3f( 0.0f, 1.0f, 0.0f );

    glEnd();    //==============================================================

    // uncomment to see labels of planes
//    _glColor((Qt::black);
//    renderText( 0.0f, 0.5f, 0.5f, "YZ" );
//
//    renderText( 0.5f, 0.0f, 0.5f, "XZ" );
//
//    renderText( 0.5f, 0.5f, 0.0f, "XY" );

    glBegin(GL_LINES);//==============================================================

    // X Axis
    glColor3fv( colorBlack );

    glVertex3f( 0.0f, 1.0f, 0.0f );
    glVertex3f( 1.0f, 1.0f, 0.0f );

    // Y Axis
    glVertex3f( 1.0f, 0.0f, 0.0f );
    glVertex3f( 1.0f, 1.0f, 0.0f );

    // Z Axis
    glVertex3f( 1.0f, 0.0f, 0.0f );
    glVertex3f( 1.0f, 0.0f, 1.0f );

    glEnd();    //==============================================================



    // drawing dashed middle lines

    glEnable(GL_LINE_STIPPLE);         /* dashed lines */
    glLineStipple(1, 0xF0F0);


    glBegin(GL_LINES);//==============================================================

    float p = 0.0;
    for ( int i=0; i<=NN; i++ ) {
        glVertex3f( 0.0f, p, 0.0f );
        glVertex3f( 1.0f, p, 0.0f );
        glVertex3f( 0.0f, p, 0.0f );
        glVertex3f( 0.0f, p, 1.0f );

        glVertex3f( p, 0.0f, 0.0f );
        glVertex3f( p, 1.0f, 0.0f );
        glVertex3f( p, 0.0f, 0.0f );
        glVertex3f( p, 0.0f, 1.0f );

        glVertex3f( 0.0f, 0.0f, p );
        glVertex3f( 0.0f, 1.0f, p );
        glVertex3f( 0.0f, 0.0f, p );
        glVertex3f( 1.0f, 0.0f, p );


        p += step;
    }

    glEnd();    //==============================================================

    glDisable(GL_LINE_STIPPLE);

    // drawing labels

    _glColor(0, 0, 0);

    p = 0.0f;
    for ( int i=0; i<=NN; i++ ) {
        // X
        double xf;
        xf = minX+p*(maxX-minX);
        renderText( p, 1.1f, -0.1f, QString("%1").arg(xf, 0, 'f', 1) );
        // Y
        double yf;
        yf = minY+p*(maxY-minY);
        renderText( 1.1f, p, -0.1f, QString("%1").arg(yf, 0, 'f', 1) );
        // Z
        double zf;
        zf = minZ+p*(maxZ-minZ);
        renderText( 1.1f, -0.1f, p, QString("%1").arg(zf, 0, 'f', 1) );

        p += step;
    }

    glPopMatrix();
}

void GraphWidget::endGraphScene()
{
    glPopMatrix();
}


void GraphWidget::drawLineGraph()
{
    // get data matrix from current graph
    DataMatrix coordinates = m_graph->getPlotData().getData();

    DataArray min, max;
    double x_scale, y_scale;
    double minX, maxX;
    int ai, bi;

    double zoom = 1.0*(m_zoom+1500)/3000;
    int n_zoom = (int)(zoom*coordinates.getDA().size());

    findDataMinMax(coordinates, min, max);

    // find first coord and last coord
    ai = m_scroll;
    bi = ai + n_zoom;
    if ( bi>=coordinates.getDA().size()) bi = coordinates.getDA().size()-1;

    // find X range
    minX = coordinates[ai][0];
    maxX = coordinates[bi][0];

    x_scale = maxX - minX;
    y_scale = max[1] - min[1];

    // STARTING TO DRAW
    startGraphScene2D(minX, min[1], maxX, max[1]);

    //_glColor(1,1,1);

    glBegin( GL_LINE_STRIP );
    for ( int i=ai; i<=bi; i++ ) {

        // get coordinates
        double x, y;
        DataArray coord = coordinates[i];
        // normalized coordinates
        x = (scn2RT[0]-scn2LB[0])*((coord[0]-minX)/(x_scale));
        y = (scn2RT[1]-scn2LB[1])*((coord[1]-min[1])/(y_scale));

        // draw normalized points as little spheres
        _glColor( 0, y, 0, true );
        glVertex2f( x, y );
    }
    glEnd();

    for ( int i=ai; i<=bi; i++ ) {

        // get coordinates
        double x, y;
        DataArray coord = coordinates[i];
        // normalized coordinates.
        x = (scn2RT[0]-scn2LB[0])*((coord[0]-minX)/(x_scale));
        y = (scn2RT[1]-scn2LB[1])*((coord[1]-min[1])/(y_scale));

        glPushMatrix();
        glTranslatef( x, y, 0.0f );
        _glColor( 0, y, 0, true );
        _glFullCircle2D( 0.005f, 16 );
        glPopMatrix();

    }

    // END DRAWING
    endGraphScene();

}

void GraphWidget::drawScatterPlot2D()
{

    // get data matrix from current graph
    DataMatrix coordinates = m_graph->getPlotData().getData();

    DataArray min, max;

    findDataMinMax(coordinates, min, max);

    // START DRAWING
    startGraphScene2D(min[1], min[2], max[1], max[2]);

    for ( int i=0; i<coordinates.getDA().size(); i++ ) {

        double x, y;
        DataArray coord = coordinates[i];
        StringArray label = coordinates.getLabels(i);

        x = (scn2RT[0]-scn2LB[0])*((coord[1]-min[1])/(max[1]-min[1]));
        y = (scn2RT[1]-scn2LB[1])*((coord[2]-min[2])/(max[2]-min[2]));

        glPushMatrix();
        glTranslatef( x, y, 0.0f );
        _glColor( 0, y, 0, true);
        _glFullCircle2D( 0.005f, 16 );
        glPopMatrix();

        _glColor(0, 0, 0);
        renderText(x-0.01, y+0.01, 0, tr(label[0].c_str()) );
    }



    // END DRAWING
    endGraphScene();
}

//////////////////////////////////////////////////////////////////////////////////////
// Draws Scatter Plot using data inside currentGraph
// PlotData Matrix must be of size N x 3 ( 3 stands for three coordinates X,Y,Z )
//////////////////////////////////////////////////////////////////////////////////////
void GraphWidget::drawScatterPlot3D()
{
    // get data matrix from current graph
    DataMatrix coordinates = m_graph->getPlotData().getData();

    //GLUquadricObj* pQdr = gluNewQuadric();

    DataArray min, max;
    findDataMinMax(coordinates, min, max);

    // START DRAWING
    startGraphScene3D( min[0], min[1], min[2], max[0], max[1], max[2] );

    //glDepthMask(GL_TRUE);

    // and for each coordinate, we draw something on the screen
    for ( int i=0; i<coordinates.getDA().size(); i++ ) {

        // get coordinates
        double x, y, z;
        DataArray coord = coordinates[i];
        // normalized coordinates, or 0 if max==mi n...
        x = ( coord[0] - min[0] ) / ( max[0] - min[0] );
        y = ( coord[1] - min[1] ) / ( max[1] - min[1] );
        z = ( coord[2] - min[2] ) / ( max[2] - min[2] );

        // draw normalized points as little spheres
        glPushMatrix();
        glTranslatef( x, y, z );
        _glColor( 0, 0, z, true );
        _glCircle3D( 0.03, 10 );
        glPopMatrix();
    }

    // END DRAWING
    endGraphScene();
}


//////////////////////////////////////////////////////////////////////////////////////
// Draws Scatter Plot using data inside currentGraph
// PlotData Matrix must be of size N x 3 ( 3 stands for three coordinates X,Y,Z )
//////////////////////////////////////////////////////////////////////////////////////
void GraphWidget::drawScatterPlotContour3D()
{
        // get data matrix from current graph
    DataMatrix coordinates = m_graph->getPlotData().getData();

    //GLUquadricObj* pQdr = gluNewQuadric();

    DataArray min, max;
    findDataMinMax(coordinates, min, max);

    // START DRAWING
    startGraphScene3D( min[0], min[1], min[2], max[0], max[1], max[2] );

    // and for each coordinate, we draw something on the screen
    for ( int i=0; i<coordinates.getDA().size(); i++ ) {

        // get coordinates
        double x, y, z;
        DataArray coord = coordinates[i];
        // normalized coordinates, or 0 if max==mi n...
        x = ( coord[0] - min[0] ) / ( max[0] - min[0] );
        y = ( coord[1] - min[1] ) / ( max[1] - min[1] );
        z = ( coord[2] - min[2] ) / ( max[2] - min[2] );

        // draw points as small circle
        glPushMatrix();
        glTranslatef( x, y, z );
        _glColor( 0, 0, z, true );
        // gluSphere( pQdr, 0.02, 4, 4 );
        _glCircle3D( 0.03, 10 );
        glPopMatrix();

        // drawing contour
        glPushMatrix();
        glTranslatef( x, y, 0 );
        _glCircle3D( 0.003, 3 );
        glPopMatrix();
    }

    // END DRAWING
    endGraphScene();
}

//////////////////////////////////////////////////////////////////////////////////////
// Draws Surface Plot using data inside currentGraph
// PlotData Matrix can be of size N x M. This Matrix represents heightmap of the area
//////////////////////////////////////////////////////////////////////////////////////
//void GraphWidget::drawSurfacePlot()
//{
//    // get data matrix from current graph
//    DataMatrix map = m_graph->getPlotData().getData();
//
//    double maxV;
//    findDataMax(map, maxV);
//
//    glPushMatrix();
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//    DataArray v1, v2;
//    v2 = map[0);
//
//    // and for each coordinate, we draw something on the screen
//    for ( int i=1; i<map.size(); i++ ) {
//        v1 = v2;
//        v2 = map[i);
//
//        double x1, y1, z1;
//        double x2, y2, z2;
//        double z3, z4;
//
//        glBegin(GL_TRIANGLE_STRIP);
//
//        for ( int j=0; j<v1.size(); j++ ) {
//
//            // one
//            x1 = 1.0*j/v1.size();
//            y1 = 1.0*(i-1)/map.size();
//            z1 = maxV>0 ? v1[j)/maxV : 0;
//
//            // two
//            x2 = 1.0*j/v1.size();
//            y2 = 1.0*i/map.size();
//            z2 = maxV>0 ? v2[j)/maxV : 0;
//
//            // drawing
//            _glColor( 0, 0, z1, true);
//            glVertex3f( x1, y1, z1 );
//            _glColor( 0, 0, z2, true);
//            glVertex3f( x2, y2, z2 );
//        }
//        glEnd();
//
//        glBegin(GL_LINE_STRIP);
//        _glColor( 0, 0, 0 );
//
//        for ( int j=0; j<v1.size()-1; j++ ) {
//            // one
//            x1 = 1.0*j/v1.size();
//            y1 = 1.0*(i-1)/map.size();
//
//            // two
//            x2 = 1.0*(j+1)/v1.size();
//            y2 = 1.0*i/map.size();
//
//            // heights
//            z1 = maxV>0 ? v1[j)/maxV : 0;
//            z2 = maxV>0 ? v2[j)/maxV : 0;
//            z3 = maxV>0 ? v2[j+1)/maxV : 0;
//            z4 = maxV>0 ? v1[j+1)/maxV : 0;
//
//            // drawing
//            glVertex3f( x1, y1, z1 );
//            glVertex3f( x1, y2, z2 );
//            glVertex3f( x2, y2, z3 );
//            glVertex3f( x2, y1, z4 );
//            glVertex3f( x1, y1, z1 );
//        }
//
//        glEnd();
//
//    }
//    glPopMatrix();
//}

//////////////////////////////////////////////////////////////////////////////////////
// Draws Surface Plot with Contour using data inside currentGraph
// PlotData Matrix can be of size N x M. This Matrix represents heightmap of the area
//////////////////////////////////////////////////////////////////////////////////////
//void GraphWidget::drawMeshPlot()
//{
//    // get data matrix from current graph
//    DataMatrix map = m_graph->getPlotData().getData();
//
//    double maxV;
//    findDataMax(map, maxV);
//
//    glPushMatrix();
//
//    DataArray v1, v2;
//    v2 = map[0);
//
//    // and for each coordinate, we draw something on the screen
//    for ( int i=1; i<map.size(); i++ ) {
//        v1 = v2;
//        v2 = map[i);
//
//        double x1, y1, z1;
//        double x2, y2, z2;
//        double z3, z4;
//
//        glBegin(GL_LINE_STRIP);
//
//        for ( int j=0; j<v1.size()-1; j++ ) {
//            // one
//            x1 = 1.0*j/v1.size();
//            y1 = 1.0*(i-1)/map.size();
//
//            // two
//            x2 = 1.0*(j+1)/v1.size();
//            y2 = 1.0*i/map.size();
//
//            // heights
//            z1 = maxV>0 ? v1[j)/maxV : 0;
//            z2 = maxV>0 ? v2[j)/maxV : 0;
//            z3 = maxV>0 ? v2[j+1)/maxV : 0;
//            z4 = maxV>0 ? v1[j+1)/maxV : 0;
//
//            // drawing
//            _glColor( 0, 0, z1, true);
//            glVertex3f( x1, y1, z1 );
//            _glColor( 0, 0, z2, true);
//            glVertex3f( x1, y2, z2 );
//            _glColor( 0, 0, z3, true);
//            glVertex3f( x2, y2, z3 );
//            _glColor( 0, 0, z4, true);
//            glVertex3f( x2, y1, z4 );
//            _glColor( 0, 0, z1, true);
//            glVertex3f( x1, y1, z1 );
//        }
//
//        glEnd();
//
//
//    }
//    glPopMatrix();
//}


bool GraphWidget::savePlotImage(const std::string& filename)
{
    QImage image = this->grabFrameBuffer();
    return image.save( tr(filename.c_str()), filename.substr(filename.length()-3,3).c_str() );
}

bool GraphWidget::savePlot2SVG(const std::string& filename)
{
    return true;
}
