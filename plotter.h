#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

#include <QPainter>

#include "storage.h"

class Plotter : public QWidget {
    Q_OBJECT

public:

    Plotter (const Storage & storage, QWidget * parent = nullptr);

public slots:

    void handleUpdate ();

private:

    const Storage & m_storage;

    void paintEvent (QPaintEvent * event = nullptr);

    void coordinate (double x, double y, int & x_, int & y_);

    void drawLine (double x1, double y1, double x2, double y2, QPainter & painter);

#if 0
    void drawGrid (QPainter & painter);
#endif
    void drawAxis (QPainter & painter);
    void drawFunc (const std::function <double (double)> & f, QPainter & painter);
 
    double m_x_min, m_x_max;
    double m_y_min, m_y_max;

};

#endif // PLOTWIDGET_H
