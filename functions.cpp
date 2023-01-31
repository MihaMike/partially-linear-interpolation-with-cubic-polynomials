#include "functions.h"

#include <math.h>

void add_functions (std::vector <func> & funcs) {

  funcs.push_back (
  { "f(x) = 1",                     /* name */
    [] (double  ) { return 1; },    /*    f */
    [] (double  ) { return 0; },    /*   df */
    [] (double  ) { return 0; } }); /*  ddf */

  funcs.push_back (
  { "f(x) = x",                     /* name */
    [] (double x) { return x; },    /*    f */
    [] (double  ) { return 1; },    /*   df */
    [] (double  ) { return 0; } }); /*  ddf */

  funcs.push_back (
  { "f(x) = x^2",                       /* name */
    [] (double x) { return x * x; },    /*    f */
    [] (double x) { return 2 * x; },    /*   df */
    [] (double  ) { return 2;     } }); /*  ddf */

  funcs.push_back (
  { "f(x) = x^3",                           /* name */
    [] (double x) { return x * x * x; },    /*    f */
    [] (double x) { return 3 * x * x; },    /*   df */
    [] (double x) { return 6 * x;     } }); /*  ddf */

  funcs.push_back (
  { "f(x) = x^4",                               /* name */
    [] (double x) { return x * x * x * x; },    /*    f */
    [] (double x) { return 4 * x * x * x; },    /*   df */
    [] (double x) { return 12 * x * x;    } }); /*  ddf */

  funcs.push_back (
  { "f(x) = exp (x)",                     /* name */
    [] (double x) { return exp (x); },    /*    f */
    [] (double x) { return exp (x); },    /*   df */
    [] (double x) { return exp (x); } }); /*  ddf */

  funcs.push_back (
  { "f(x) = 1 / (25 x^2 + 1)",                      /* name */
    [] (double x) { return 1 / (25 * x * x + 1); }, /*    f */
    [] (double x)                                   /*   df */
    {
      double d = 25 * x * x + 1;
      return -50 * x / (d * d);
    },
    [] (double x)                                   /*  ddf */
    {
      double d = 25 * x * x + 1;
      return 50 * (75 * x * x - 1) / (d * d * d);
    } });

}
