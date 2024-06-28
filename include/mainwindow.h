#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QwtPlot>
#include <QwtPlotCurve>

class Plot : public QwtPlot{
public:
    Plot(QWidget *parent = nullptr);
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    virtual void timerEvent( QTimerEvent* ) QWT_OVERRIDE;

private:
    int m_previousXRand1;
    int m_previousYRand1;
    int m_previousXRand2;
    int m_previousYRand2;
    int pause = 0;
    int count =0;
    double m_currentX1;
    double m_currentY1;
    double m_currentX2;
    double m_currentY2;
    QPolygonF m_points1;
    QPolygonF m_points2;
    QwtPlotCurve *m_curve1;
    QwtPlotCurve *m_curve2;
    Plot *m_plot;


};
#endif // MAINWINDOW_H
