#ifndef STORAGE_H
#define STORAGE_H

#include <memory>
#include <vector>
#include <cassert>

#include "method.h"
#include "functions.h"

class Storage {

public:

    Storage ();
    ~Storage ();

    /* Getters. */
    const Method &               getMethod () const;
    int                          getMethodIndex () const;
    const func                   getFunc () const;
    int                          getFuncIndex () const;
    bool                         getNeedDrawFunc () const;
    bool                         getNeedDrawApprox () const;
    bool                         getNeedDrawResidual () const;
    int                          getZoom () const;
    double                       getDisturbance () const;
    double                       getA () const;
    double                       getB () const;
    int                          getN () const;
    double                       getXMin () const;
    double                       getXMax () const;
    double                       getYMin () const;
    double                       getYMax () const;
    double                       getResidual () const;
    double                       getXContentMin () const;
    double                       getXContentMax () const;
    double                       getYContentMin () const;
    double                       getYContentMax () const;
    std::vector <double> &       getMethodX ();
    std::vector <double> &       getMethodF ();
    std::vector <double> &       getMethodDf ();
    std::vector <double> &       getMethodDdf ();
    std::vector <double> &       getMethodWorkspace ();
    const std::vector <double> & getMethodX () const;
    const std::vector <double> & getMethodF () const;
    const std::vector <double> & getMethodDf () const;
    const std::vector <double> & getMethodDdf () const;
    const std::vector <double> & getMethodWorkspace () const;

    /* Specific getters. Need only for init input section. */
    int            getMethodsCount () const;
    const Method & getMethodAt (int index) const;
    int            getFuncsCount () const;
    const func &   getFuncAt (int index) const;

    /* Setters. */
    void setMethodIndex (int index);
    void setFuncIndex (int index);
    void setNeedDrawFunc (bool need_draw);
    void setNeedDrawApprox (bool need_draw);
    void setNeedDrawResidual (bool need_draw);
    void setZoom (int zoom);
    void setDisturbance (double disturbance);
    void setA (double a);
    void setB (double b);
    void setN (int n);
    void setYMin (double y_min);
    void setYMax (double y_max);
    void setResidual (double residual);
    void setXContentMin (double c_min);
    void setXContentMax (double c_max);
    void setYContentMin (double c_min);
    void setYContentMax (double c_max);
    
private:
   
    /* input */
    std::vector <std::unique_ptr <Method>> m_methods;
    int                                    m_method_index;
    std::vector <func>                     m_funcs;
    int                                    m_func_index;
    bool                                   m_need_draw_func;
    bool                                   m_need_draw_approx;
    bool                                   m_need_draw_residual;
    int                                    m_zoom;
    double                                 m_disturbance;
    double                                 m_a;
    double                                 m_b;
    int                                    m_n;
    
    /* output */
    double m_y_min;
    double m_y_max;
    double m_residual;
    double m_x_content_min;
    double m_x_content_max;
    double m_y_content_min;
    double m_y_content_max;
    
    /* workspace */
    std::vector <double> m_method_x;
    std::vector <double> m_method_f;
    std::vector <double> m_method_df;
    std::vector <double> m_method_ddf;
    std::vector <double> m_method_w;

};

#endif // STORAGE_H
