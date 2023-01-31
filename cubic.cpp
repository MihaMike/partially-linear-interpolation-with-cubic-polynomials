#include <math.h>

#include "cubic.h"
#include "algorithm.h"

QString
Cubic::name () const {
    return m_name;
}

void Cubic::border_values (int & min, int & max) const {
    min = m_min_n;
    max = m_max_n;
}

bool Cubic::need_df () const {
    return m_need_df;
}

bool Cubic::need_ddf () const {
    return m_need_ddf;
}

void Cubic::build_approximate_function (int n, const std::vector <double> & x,
                                    const std::vector <double> & f, const std::vector <double> & df,
                                    const std::vector <double> & /* ddf */,
                                    std::vector <double> & workspace) const {
   
    double h;
    
    workspace.resize (4 * n);
    
    double * d = &workspace[3 * n];
    
    d[0] = df[0];
    d[n - 1] = df[1];
    
//    printf("d[0] = %f, d[n - 1] = %f\n", d[0], d[n - 1]);
    
    if (n > 2) {
        h = (x[n-1] - x[0])/(double(n) - 1.);
        
        for (int i = 1; i < n - 1; i++) {
            d[i] = (f[i + 1] - f[i - 1]) / (2. * h);
//            printf("d[%d] = %f", i, d[i]);
        }
//        printf("\nh = %f\n", h);
    }
    
    for (int i = 0; i < n - 1; i++) {
        double a1, a2, a3, a4;
        double t;
        
        t = x[i + 1] - x[i];
        
        a1 = f[i];
        a2 = d[i];
        a3 = ((f[i + 1] - f[i]) / t - d[i]) / t;
        a4 = (d[i] + d[i + 1] - 2.0 * (f[i + 1] - f[i]) / t) / (t * t);
        
        int j = 4 * i;
        
        workspace[j + 0] = a1;
        workspace[j + 1] = a2;
        workspace[j + 2] = a3;
        workspace[j + 3] = a4;
//        printf("a[1, %d] = %f, a[2, %d] = %f, a[3, %d] = %f, a[4, %d] = %f\n", i + 1, a1, i + 1, a2, i + 1, a3, i + 1, a4);
    }
}

double Cubic::calculate_value (double p, double a, double b, int n, const std::vector <double> & x,
                         const std::vector <double> & workspace) const {
  
    int i, j;
    double c1, c2, c3, c4, d;

    if (p < a) {
        return calculate_value (a, a, b, n, x, workspace);
    }

    if (p > b) {
        return calculate_value (b, a, b, n, x, workspace);
    }

    i = algorithm::find_index (x, p);

    j = 4 * i;

    c4 = workspace[j + 3];
    c3 = workspace[j + 2] - c4 * (x[i + 1] - x[i]);
    c2 = workspace[j + 1];
    c1 = workspace[j + 0];

    d = p - x[i];

    return c1 + c2 * d + c3 * d * d + c4 * d * d * d;
}
