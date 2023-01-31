#include "algorithm.h"


int algorithm::find_index (const std::vector <double> & a, double x) {
  int l, r, s;

  /* Check. */
    if (x < a[0]) {
        return 0;
    }

    if (x > a[a.size () - 1]) {
        return a.size () - 2;
    }

    l = 0;
    r = (int) a.size () - 1;

    while (l != r) {

      s = (l + r) / 2;

      if (a[s] <= x) {
          l = s + 1;
      } else {
          r = s;
      }
    }

    return l - 1;
}

double algorithm::bin_pow (double a, int n) {
    double res = 1.0;

    if (n < 0) {
        return 1.0 / bin_pow (a, -n);
    }

    while (n != 0) {

        if (n & 1) {
            res *= a;
        }

        a *= a;
        n >>= 1;
    }

    return res;
}
