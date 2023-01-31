#ifndef CUBIC_H
#define CUBIC_H

#include "method.h"

class Cubic : public Method
{

private:

    const QString m_name      = "Divided-difference cubic polynomials";
    const int     m_min_n     = 2;
    const int     m_max_n     = 1000;
    const bool    m_need_df   = true;
    const bool    m_need_ddf  = false;

public:

    Cubic () = default;

    virtual ~Cubic () override = default;

    virtual QString name () const override;

    virtual void border_values (int & min, int & max) const override;

    virtual bool need_df () const override;

    virtual bool need_ddf () const override;

    virtual void build_approximate_function (int n, const std::vector <double> & x, const std::vector <double> & f,
        const std::vector <double> & df, const std::vector <double> & ddf,
        std::vector <double> & workspace) const override;

  /* Calc Pf(p). */
    virtual double calculate_value (double p, double a, double b, int n, const std::vector <double> & x,
        const std::vector <double> & workspace) const override;

};

#endif // CUBIC_H
