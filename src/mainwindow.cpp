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
    m_previousXRand1 = std::time(nullptr);
    m_previousYRand1 = (std::time(nullptr)+100)*2;
    m_currentX1 = 0;
    m_currentY1 = 0;
    m_previousXRand2 = (m_previousYRand1+100)*3;
    m_previousYRand2 = (m_previousXRand2+100)*4;
    m_currentX1 = 0;
    m_currentY1 = 0;

    m_plot = new Plot();
    m_plot->setTitle( "Linear Congruent Random Walk" );
    m_plot->setCanvasBackground( Qt::white );
    m_plot->setAxisScale( QwtAxis::YLeft, -50, 50 );
    m_plot->setAxisScale( QwtAxis::XBottom, -50, 50 );


    QwtPlotGrid* grid = new QwtPlotGrid();
    grid->attach( m_plot );

    m_curve1 = new QwtPlotCurve();
    m_curve1 -> setPen(Qt::red, 1);
    //m_curve1 -> setCurveAttribute(QwtPlotCurve::Fitted, true);
    m_curve1 -> setRenderHint( QwtPlotItem::RenderAntialiased, true );

    m_curve2 = new QwtPlotCurve();
    m_curve2 -> setPen(Qt::blue, 1);
    //m_curve2 -> setCurveAttribute(QwtPlotCurve::Fitted, true);
    m_curve2 -> setRenderHint( QwtPlotItem::RenderAntialiased, true );

    m_points1 << QPointF(0, 0);
    m_points2 << QPointF(0, 0);

    m_curve1->setSamples(m_points2);
    m_curve1 -> attach(m_plot);
    m_curve2->setSamples(m_points2);
    m_curve2 -> attach(m_plot);

    QHBoxLayout* layout = new QHBoxLayout( this );
    layout->addWidget(m_plot);

    ( void )startTimer( 1 );
}

void MainWindow::timerEvent( QTimerEvent* ){
    if (pause==0){
        if (count>5000){
            pause=1;
        }
        ++count;
    }
    else{
        double tempX {0};
        double tempY {0};
        double length {0};

        m_previousXRand1 = linearCongruent(m_previousXRand1, 214013, 2531011, pow(2, 31));
        m_previousYRand1 = linearCongruent(m_previousYRand1, 214013, 2531011, pow(2, 31));
        m_previousXRand2 = linearCongruent(m_previousXRand2, 214013, 2531011, pow(2, 31));
        m_previousYRand2 = linearCongruent(m_previousYRand2, 214013, 2531011, pow(2, 31));

        tempX = m_previousXRand1/pow(2, 31);
        tempY = m_previousYRand1/pow(2, 31);
        length = std::sqrt(pow(tempX, 2) + pow(tempY, 2));
        tempX = tempX/length;
        tempY = tempY/length;

        m_currentX1 = m_currentX1 + tempX;
        m_currentY1 = m_currentY1 + tempY;

        tempX = m_previousXRand2/pow(2, 31);
        tempY = m_previousYRand2/pow(2, 31);
        length = std::sqrt(pow(tempX, 2) + pow(tempY, 2));
        tempX = tempX/length;
        tempY = tempY/length;

        m_currentX2 = m_currentX2 + tempX;
        m_currentY2 = m_currentY2 + tempY;

        m_points1 << QPointF(m_currentX1, m_currentY1);
        m_points2 << QPointF(m_currentX2, m_currentY2);

        m_curve1->setSamples(m_points1);
        m_curve2->setSamples(m_points2);

        m_plot->replot();
    }
}


