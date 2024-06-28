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
    int m_previousXRand;
    int m_previousYRand;
    double m_currentX;
    double m_currentY;
    QPolygonF m_points;
    QwtPlotCurve *m_curve;
    Plot *m_plot;


};
#endif // MAINWINDOW_H
