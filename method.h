#ifndef METHOD_H
#define METHOD_H

#include <cassert>

#include <QString>
#include <vector>

class Method
{
public:

    Method () = default;

    virtual ~Method () = default;

    /* method name. */
    virtual QString
    name () const = 0;

    /* method parameters info. */
    /* Important!
     * This is the number of points on which the method is built.
     * The segment will be divided into n - 1 parts. */
    virtual void border_values (int & min, int & max) const = 0;

    virtual bool need_df () const = 0;

    virtual bool need_ddf () const = 0;

    /* method main functions. */
    virtual void build_approximate_function (int n,const std::vector <double> & x, const std::vector <double> & f,
                              const std::vector <double> & df, const std::vector <double> & ddf,
                              std::vector <double> & workspace) const = 0;

    /* Calc Pf(p). */
    /* a == workspace[0]
    * b == workspace[workspace.size ()]
    */
    virtual double calculate_value (double p, double a, double b, int n, const std::vector <double> & x,
                   const std::vector <double> & workspace) const = 0;

};

#endif // METHOD_H
