#include <math.h>

#include "algorithm.h"
#include "plotter.h"

constexpr double MIN_DOUBLE = 1e-16;

Plotter::Plotter (const Storage & storage, QWidget * parent)
  : QWidget (parent),
    m_storage (storage)
{
}

void Plotter::handleUpdate () {
  update ();
//  paintEvent ();
}



void Plotter::paintEvent (QPaintEvent * /* event */) {
  /* orange. */
    QPen f_pen (QColor (255, 0, 255), 2, Qt::SolidLine);
    QPen a_pen (QColor (255, 128, 0), 2, Qt::SolidLine);
    QPen r_pen (Qt::green, 2, Qt::SolidLine);


    QPainter painter (this);

    m_x_min = m_storage.getXContentMin ();
    m_x_max = m_storage.getXContentMax ();
    m_y_min = m_storage.getYContentMin ();
    m_y_max = m_storage.getYContentMax ();

    m_y_min = std::min (m_y_min, 0.0);
    m_y_max = std::max (m_y_max, 0.0);

    double d;

    d = (m_y_max - m_y_min);

    if (d < MIN_DOUBLE) {
        d = MIN_DOUBLE;
    }

    m_y_max += d / 100.0;
    m_y_min -= d / 100.0;

    d = (m_x_max - m_x_min);

    if (d < MIN_DOUBLE) {
        d = MIN_DOUBLE;
    }

    m_x_max += d / 100.0;
    m_x_min -= d / 100.0;


    /* Zoom. */

    double a = m_storage.getA ();
    double b = m_storage.getB ();
    int n = m_storage.getN ();
    auto & x = m_storage.getMethodX ();
    auto & w = m_storage.getMethodWorkspace ();

    auto f_ = m_storage.getFunc () .m_f;
    auto a_ = [&] (double p) { return m_storage.getMethod () .calculate_value (p, a, b, n, x, w); };
    auto r_ = [&] (double x) { return fabs (f_ (x) - a_ (x)); };

#if 0
    drawGrid (painter);
#endif

    if (m_storage.getNeedDrawResidual ()) {
          painter.setPen (r_pen);
          drawFunc (r_, painter);
    }

    if (m_storage.getNeedDrawFunc ()) {
          painter.setPen (f_pen);
          drawFunc (f_, painter);
    }

    if (m_storage.getNeedDrawApprox ()) {
          painter.setPen (a_pen);
          drawFunc (a_, painter);
    }

    drawAxis (painter);
}


void Plotter::coordinate (double x, double y, int & x_, int & y_) {
    int w = size () .width () - 1;
    int h = size () .height () - 1;

//  x_ = w * (x - m_x_min_zoom) / (m_x_max_zoom - m_x_min_zoom);
//  y_ = h * (y - m_y_max_zoom) / (m_y_min_zoom - m_y_max_zoom);
    x_ = w * (x - m_x_min) / (m_x_max - m_x_min);
    y_ = h * (y - m_y_max) / (m_y_min - m_y_max);
}

void Plotter::drawLine (double x1, double y1, double x2, double y2, QPainter & painter)
{
    int x1_loc, x2_loc, y1_loc, y2_loc;

    coordinate (x1, y1, x1_loc, y1_loc);
    coordinate (x2, y2, x2_loc, y2_loc);

    painter.drawLine (x1_loc, y1_loc, x2_loc, y2_loc);
}

#if 0
void Plotter::drawGrid (QPainter & painter) {
    QPen pen (Qt::white, 0, Qt::DotLine);
    painter.setPen (pen);

    double grid_step;


    /* Рисуем сетку по оси ординат. */
    grid_step = algorithm::bin_pow (10, (int) log10 (std::max (fabs (m_y_min), fabs (m_y_max))));

    for (int i = -1; i * grid_step >= m_y_min; i--) {
        drawLine (m_x_min, i * grid_step, m_x_max, i * grid_step, painter);
    }

    for (int i = 1; i * grid_step <= m_y_max; i++) {
        drawLine (m_x_min, i * grid_step, m_x_max, i * grid_step, painter);
    }

    /* Рисуем сетку по оси абсцисс. */
    grid_step = algorithm::bin_pow (10, (int) log10 (std::max (fabs (m_x_min), fabs (m_x_max))));

    for (int i = -1; i * grid_step >= m_x_min; i--) {
        drawLine (i * grid_step, m_y_min, i * grid_step, m_y_max, painter);
    }

    for (int i = 1; i * grid_step <= m_x_max; i++) {
        drawLine (i * grid_step, m_y_min, i * grid_step, m_y_max, painter);
    }

}
#endif

void Plotter::drawAxis (QPainter & painter) {

    painter.setPen (QPen (Qt::red, 2, Qt::DashLine));

    if (m_x_min <= 0 && 0 <= m_x_max) {
        drawLine (0, m_y_min, 0, m_y_max, painter);
    }
    drawLine (m_x_min, 0, m_x_max, 0, painter);


    /* Arrows. */
    painter.setPen (QPen (Qt::red, 2, Qt::SolidLine));

    int x, y;

    if (m_x_min <= 0 && 0 <= m_x_max) {
        coordinate (0, m_y_max, x, y);
        painter.drawLine (x, y, x - 3, y + 10);
        painter.drawLine (x, y, x + 3, y + 10);
    }

    coordinate (m_x_max, 0, x, y);
    painter.drawLine (x, y, x - 10, y - 3);
    painter.drawLine (x, y, x - 10, y + 3);
}

void Plotter::drawFunc (const std::function <double (double)> & f, QPainter & painter) {
    double a = m_storage.getXMin ();
    double b = m_storage.getXMax ();
    int h = size () .height ();
    double d = (b - a) / h;

    double x_curr, x_prev;
    double f_curr, f_prev;

    x_prev = a;
    f_prev = f (a);

    for (int i = 1; i < h; i++) {
          x_curr = a + i * d;
          f_curr = f (x_curr);
          drawLine (x_prev, f_prev, x_curr, f_curr, painter);
          x_prev = x_curr;
          f_prev = f_curr;
    }
}
