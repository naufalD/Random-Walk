#include "include/mainwindow.h"
#include "include/pseudorandom.h"

#include <QwtPlotCurve>
#include <QLayout>
#include <QwtPlotGrid>
#include <cmath>


Plot::Plot( QWidget* parent ) : QwtPlot(parent)
{
    setMinimumSize(300,300);
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Landau 5.4");
    m_previousXRand = std::time(nullptr);
    m_previousYRand = (
                          std::time(nullptr)+100)*2;
    m_currentX = 0;
    m_currentY = 0;

    m_plot = new Plot();
    m_plot->setTitle( "Linear Congruent Random Walk" );
    m_plot->setCanvasBackground( Qt::white );
    m_plot->setAxisScale( QwtAxis::YLeft, -50, 50 );
    m_plot->setAxisScale( QwtAxis::XBottom, -50, 50 );


    QwtPlotGrid* grid = new QwtPlotGrid();
    grid->attach( m_plot );

    m_curve = new QwtPlotCurve();
    m_curve -> setPen(Qt::red, 1);
    //m_curve -> setCurveAttribute(QwtPlotCurve::Fitted, true);
    m_curve -> setRenderHint( QwtPlotItem::RenderAntialiased, true );
    //m_curve -> setStyle( QwtPlotCurve::Dots );

    m_points << QPointF(0, 0);

    m_curve->setSamples(m_points);
    m_curve -> attach(m_plot);

    QHBoxLayout* layout = new QHBoxLayout( this );
    layout->addWidget(m_plot);

    ( void )startTimer( 1 );
}

void MainWindow::timerEvent( QTimerEvent* ){
    double tempX {0};
    double tempY {0};
    double length {0};

    m_previousXRand = linearCongruent(m_previousXRand, 214013, 2531011, pow(2, 31));
    m_previousYRand = linearCongruent(m_previousYRand, 214013, 2531011, pow(2, 31));

    tempX = m_previousXRand/pow(2, 31);
    tempY = m_previousYRand/pow(2, 31);
    length = std::sqrt(pow(tempX, 2) + pow(tempY, 2));
    tempX = tempX/length;
    tempY = tempY/length;

    m_currentX = m_currentX + tempX;
    m_currentY = m_currentY + tempY;

    m_points << QPointF(m_currentX, m_currentY);

    m_curve->setSamples(m_points);

    m_plot->replot();
}


