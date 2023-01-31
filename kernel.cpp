#include <math.h>

#include "kernel.h"
#include "algorithm.h"

constexpr int POINT_COUNT = 10000;

Kernel::Kernel (Storage & storage, QObject * parent)
  : QObject (parent),
    m_storage (storage)
{}

void Kernel::update () {
    updateAll ();
    emit updated ();
}

void Kernel::handleChangeMethod () {
    updateAll ();
    emit updated ();
}

void Kernel::handleChangeFunc () {
    updateAll ();
    emit updated ();
}

void Kernel::handleChangeContent () {
    updateOutInfo ();
    emit updated ();
}

void Kernel::handleChangeZoom () {
    emit updated ();
}

void Kernel::handleChangeDisturbance () {
    makeDisturbance ();
    updateWorkspace ();
    emit updated ();
}

void Kernel::handleChangeBorder () {
    updateAll ();
    emit updated ();
}

void Kernel::handleChangeN () {
    updateAll ();
    emit updated ();
}

void Kernel::handleChangeK () {
    updateWorkspace ();
    emit updated ();
}



void
Kernel::updateWorkspace ()
{
  int n = m_storage.getN ();

  auto & x = m_storage.getMethodX ();
  auto & f = m_storage.getMethodF ();
  auto & df = m_storage.getMethodDf ();
  auto & ddf = m_storage.getMethodDdf ();
  auto & w = m_storage.getMethodWorkspace ();

  auto & method = m_storage.getMethod ();

#if 0
  emit startCalc ();
#endif
  method.build_approximate_function (n, x, f, df, ddf, w);
  updateOutInfo ();
#if 0
  emit finishCalc ();
#endif

}

void
Kernel::updateContentMinMax ()
{
  double a = m_storage.getXMin ();
  double b = m_storage.getXMax ();
  double d = (b - a) / (POINT_COUNT - 1);
  double min, max;
  int n = m_storage.getN ();
  auto & x = m_storage.getMethodX ();
  auto & w = m_storage.getMethodWorkspace ();

  auto & method = m_storage.getMethod ();

  auto & f = m_storage.getFunc () .m_f;
  auto g = [&] (double p) { return method.calculate_value (p, a, b, n, x, w); };

  min = max = 0.0;

  if (m_storage.getNeedDrawFunc ())
    {
      min = max = f (a);
    }

  if (m_storage.getNeedDrawApprox ())
    {
      min = max = g (a);
    }

  if (m_storage.getNeedDrawResidual ())
    {
      min = max = fabs (f (a) - g (a));
    }

  for (int i = 0; i < POINT_COUNT; i++)
    {

      double p = a + d * i;

      double f_p = f (p);
      double g_p = g (p);

      if (m_storage.getNeedDrawFunc ())
        {
          min = std::min (min, f_p);
          max = std::max (max, f_p);
        }

      if (m_storage.getNeedDrawApprox ())
        {
          min = std::min (min, g_p);
          max = std::max (max, g_p);
        }

      if (m_storage.getNeedDrawResidual ())
        {
          min = std::min (min, fabs (f_p - g_p));
          max = std::max (max, fabs (f_p - g_p));
        }

    }

  double c;

  c = (m_storage.getA () + m_storage.getB ()) * 0.5;
  d = (m_storage.getB () - m_storage.getA ())
      * algorithm::bin_pow (0.5, m_storage.getZoom () + 1);

  m_storage.setXContentMin (c - d);
  m_storage.setXContentMax (c + d);
  m_storage.setYContentMin (min);
  m_storage.setYContentMax (max);

}

void
Kernel::updateOutInfo ()
{
  double a = m_storage.getA ();
  double b = m_storage.getB ();
  double d = (b - a) / (POINT_COUNT - 1);
  int n = m_storage.getN ();
  auto & x = m_storage.getMethodX ();
  auto & w = m_storage.getMethodWorkspace ();

  auto & method = m_storage.getMethod ();

  auto & f = m_storage.getFunc () .m_f;
  auto g = [&] (double p) { return method.calculate_value (p, a, b, n, x, w); };

  double min, max;
  double residual = 0.0;

  min = max = f (a);

  for (int i = 0; i < POINT_COUNT; i++)
    {

      double p = a + d * i;

      double f_p = f (p);
      double g_p = g (p);

      min = std::min (min, f_p);
      max = std::max (max, f_p);
      residual = std::max (residual, fabs (f_p - g_p));

    }

  m_storage.setYMin (min);
  m_storage.setYMax (max);
  m_storage.setResidual (residual);

  updateContentMinMax ();

}

void
Kernel::updateAll ()
{
  double a = m_storage.getA ();
  double b = m_storage.getB ();
  int n = m_storage.getN ();
  double d = (b - a) / (n - 1);

  auto & x = m_storage.getMethodX ();
  auto & f = m_storage.getMethodF ();
  auto & df = m_storage.getMethodDf ();
  auto & ddf = m_storage.getMethodDdf ();

  auto _f = m_storage.getFunc () .m_f;
  auto _df = m_storage.getFunc () .m_df;
  auto _ddf = m_storage.getFunc () .m_ddf;

  auto & method = m_storage.getMethod ();

  x.resize (n);
  f.resize (n);

  if (method.need_ddf ()) {
      for (int i = 0; i < n; i++)
      {
          double p = (a + b) / 2. + (b - a) / 2. * cos(M_PI * (2. * (double(i) + 1.) - 1.) / (2. * double(n)));
          x[i] = p;
          f[i] = _f (p);
//          printf("p = %f, x[%d] = %f, f[%d] = %f\n", p, i, x[i], i, f[i]);
      }
  } else {
      for (int i = 0; i < n; i++)
      {
          double p = a + i * d;
          x[i] = p;
          f[i] = _f (p);
//          printf("p = %f, x[%d] = %f, f[%d] = %f\n", p, i, x[i], i, f[i]);
      }
  }

  if (method.need_df ())
    {

//      df.resize (n);

//      for (int i = 0; i < n; i++)
//        {
//          df[i] = _df (x[i]);
//        }

      df.resize (2);
      df[0] = _df (a);
      df[1] = _df (b);
//        printf("a = %f, b = %f\n", a, b);
//        printf("df[0] = %f, df[1] = %f\n", df[0], df[1]);
    }
  else
    {
      df.clear ();
    }

  if (method.need_ddf ())
    {

//      ddf.resize (n);

//      for (int i = 0; i < n; i++)
//        {
//          ddf[i] = _ddf (x[i]);
//        }

      ddf.resize (2);
      ddf[0] = _ddf (a);
      ddf[1] = _ddf (b);

    }
  else
    {
      ddf.clear ();
    }

  makeDisturbance ();
  updateWorkspace ();

}

void
Kernel::makeDisturbance ()
{
  int n = m_storage.getN ();
  std::vector <double> & x_vec = m_storage.getMethodX ();
  std::vector <double> & f_vec = m_storage.getMethodF ();
  double dist = m_storage.getDisturbance ();
  double min = m_storage.getYMin ();
  double max = m_storage.getYMax ();
  auto & f = m_storage.getFunc () .m_f;

  f_vec[n / 2] = f (x_vec[n / 2]) + dist * std::max (fabs (min), fabs (max));

}
