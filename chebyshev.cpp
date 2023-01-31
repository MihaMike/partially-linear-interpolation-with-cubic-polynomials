#include <math.h>

#include "chebyshev.h"
#include "algorithm.h"

QString
Chebyshev::name () const {
    return m_name;
}

void Chebyshev::border_values (int & min, int & max) const {
      min = m_min_n;
      max = m_max_n;
}

bool Chebyshev::need_df () const {
    return m_need_df;
}

bool Chebyshev::need_ddf () const {
    return m_need_ddf;
}

void Chebyshev::build_approximate_function (int n, const std::vector <double> & /* x */,
    const std::vector <double> & f, const std::vector <double> & /* df */,
    const std::vector <double> & /* ddf */, std::vector <double> & workspace) const {
    
    int i, j;

    workspace.resize (2 * n + n * n);

    double * a = &workspace[0];
    double * z = &workspace[n];
    double * g = &workspace[2 * n];

    for (i = 0; i < n; i++) {
        z[i] = 2. * cos(M_PI * (2. * (double(i) + 1.) - 1.) / (2. * double(n)));
    }

    for (j = 0; j < n; j++) {
        g[n * j] = f[j];
        g[1 + n * j] = 0.5 * z[j] * g[n * j];
    }

    if (n > 2) {
        for (j = 0; j < n; j++) {
            for (i = 2; i < n; i++) {
                g[i + n * j] = z[j] * g[i - 1 + n * j] - g[i - 2 + n * j];
            }
        }
    }

    for (i = 0; i < n; i++) {
        a[i] = 0.0;
        for (j = 0; j < n; j++) {
            a[i] += g[i + n * j];
        }
    }

    a[0] = 1./double(n) * a[0];
    for (i = 1; i < n; i++) {
        a[i] = 2./double(n) * a[i];
    }
}

double Chebyshev::calculate_value (double p, double a, double b, int n, const std::vector <double> & x,
                            const std::vector <double> & workspace) const {
    
    int i;
    double z;
    double T0, T1, Ti;
    double Pf;

    if (p < a) {
        return calculate_value (a, a, b, n, x, workspace);
    }

    if (p > b) {
        return calculate_value (b, a, b, n, x, workspace);
    }

    z = 2. * (2. * p - (b + a)) / (b - a);

    T0 = 1.;
    T1 = z / 2.;

    Pf = workspace[0] * T0 + workspace[1] * T1;

    if (n > 2) {
        for (i = 2; i < n; i++) {
            Ti = z * T1 - T0;
            Pf = Pf + workspace[i] * Ti;
            T0 = T1;
            T1 = Ti;
        }
    }

    return Pf;
}
