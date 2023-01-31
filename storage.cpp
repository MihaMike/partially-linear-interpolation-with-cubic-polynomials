#include "storage.h"

#include "chebyshev.h"
#include "cubic.h"

#include "algorithm.h"

constexpr double default_a = 0.0;
constexpr double default_b = 1.0;
constexpr int    default_n = 3;

Storage::Storage () {
    m_methods.push_back (std::make_unique <Chebyshev> ());
    m_methods.push_back (std::make_unique <Cubic> ());
    m_method_index = 0;
    add_functions (m_funcs);
    m_func_index = 0;
    m_need_draw_func = true;
    m_need_draw_approx = true;
    m_need_draw_residual = false;
    m_zoom = 0;
    m_disturbance = 0.0;
    m_a = default_a;
    m_b = default_b;
    m_n = default_n;
    m_y_min = 0.0;
    m_y_max = 0.0;
    m_residual = 0.0;
    m_x_content_min = 0.0;
    m_x_content_max = 0.0;
    m_y_content_min = 0.0;
    m_y_content_max = 0.0;
}

Storage::~Storage () {}

/* ============================================================================================= */
/* ========================================== setters ========================================== */
/* ============================================================================================= */

const Method & Storage::getMethod () const  {
    return *m_methods[m_method_index];
}

int Storage::getMethodIndex () const {
    return m_method_index;
}

const func Storage::getFunc () const {
    return m_funcs[m_func_index];
}

int Storage::getFuncIndex () const {
    return m_func_index;
}

bool Storage::getNeedDrawFunc () const {
    return m_need_draw_func;
}

bool Storage::getNeedDrawApprox () const {
    return m_need_draw_approx;
}

bool Storage::getNeedDrawResidual () const {
    return m_need_draw_residual;
}

int Storage::getZoom () const {
    return m_zoom;
}

double Storage::getDisturbance () const {
    return m_disturbance;
}

double Storage::getA () const {
    return m_a;
}

double Storage::getB () const {
    return m_b;
}

int Storage::getN () const {
    return m_n;
}

double Storage::getXMin () const {
    return std::max (m_a, getXContentMin ());
}

double Storage::getXMax () const {
    return std::min (m_b, getXContentMax ());
}

double Storage::getYMin () const {
    return m_y_min;
}

double Storage::getYMax () const {
    return m_y_max;
}

double Storage::getResidual () const {
    return m_residual;
}

double Storage::getXContentMin () const {
    double c = (m_a + m_b) / 2.0;
    double d = (m_b - m_a) / 2.0;
    return c - d * algorithm::bin_pow (0.5, m_zoom);
}

double Storage::getXContentMax () const {
    double c = (m_a + m_b) / 2.0;
    double d = (m_b - m_a) / 2.0;
    return c + d * algorithm::bin_pow (0.5, m_zoom);
}

double Storage::getYContentMin () const {
    return m_y_content_min;
}

double Storage::getYContentMax () const {
    return m_y_content_max;
}

std::vector <double> & Storage::getMethodX () {
    return m_method_x;
}

std::vector <double> & Storage::getMethodF () {
    return m_method_f;
}

std::vector <double> & Storage::getMethodDf () {
    return m_method_df;
}

std::vector <double> & Storage::getMethodDdf () {
    return m_method_ddf;
}

std::vector <double> & Storage::getMethodWorkspace () {
    return m_method_w;
}

const std::vector <double> & Storage::getMethodX () const {
    return m_method_x;
}

const std::vector <double> & Storage::getMethodF () const {
    return m_method_f;
}

const std::vector <double> & Storage::getMethodDf () const {
    return m_method_df;
}

const std::vector <double> & Storage::getMethodDdf () const {
    return m_method_ddf;
}

const std::vector <double> & Storage::getMethodWorkspace () const {
    return m_method_w;
}

/* ============================================================================================= */

int Storage::getMethodsCount () const {
    return (int) m_methods.size ();
}

const Method & Storage::getMethodAt (int index) const {
//  assert (index >= 0 && index < (int) m_methods.size ());
    return *m_methods[index];
}

int Storage::getFuncsCount () const {
    return (int) m_funcs.size ();
}

const func & Storage::getFuncAt (int index) const   {
//  assert (index >= 0 && index < (int) m_funcs.size ());
    return m_funcs[index];
}

/* ============================================================================================= */
/* ========================================== getters ========================================== */
/* ============================================================================================= */

void Storage::setMethodIndex (int index) {
//  assert (index >= 0 && index < (int) m_methods.size ());
    m_method_index = index;
}

void Storage::setFuncIndex (int index) {
//  assert (index >= 0 && index < (int) m_funcs.size ());
    m_func_index = index;
}

void Storage::setNeedDrawFunc (bool need_draw) {
    m_need_draw_func = need_draw;
}

void Storage::setNeedDrawApprox (bool need_draw) {
    m_need_draw_approx = need_draw;
}

void Storage::setNeedDrawResidual (bool need_draw) {
    m_need_draw_residual = need_draw;
}

void Storage::setZoom (int zoom) {
//  assert (zoom > 0.0);
    m_zoom = zoom;
}

void Storage::setDisturbance (double disturbance) {
    m_disturbance = disturbance;
}

void Storage::setA (double a) {
//  assert (a < m_b);
    m_a = a;
}

void Storage::setB (double b) {
//  assert (m_a < b);
    m_b = b;
}

void Storage::setN (int n) {
//  int min, max;
//  m_methods[m_method_index] -> first_parameter_border_values (min, max);
//  assert (n >= min && n <= max);
    m_n = n;
}

void Storage::setYMin (double y_min) {
    m_y_min = y_min;
}

void Storage::setYMax (double y_max) {
    m_y_max = y_max;
}

void Storage::setResidual (double residual) {
//  assert (residual >= 0.0);
    m_residual = residual;
}

void Storage::setXContentMin (double c_min) {
    m_x_content_min = c_min;
}

void Storage::setXContentMax (double c_max) {
    m_x_content_max = c_max;
}

void Storage::setYContentMin (double c_min) {
    m_y_content_min = c_min;
}

void Storage::setYContentMax (double c_max) {
    m_y_content_max = c_max;
}
