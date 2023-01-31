#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <functional>
#include <vector>
#include <QString>

struct func {
  QString m_name;
  std::function <double (double)> m_f;
  std::function <double (double)> m_df;
  std::function <double (double)> m_ddf;
};


void add_functions (std::vector <func> & funcs);

#endif // FUNCTIONS_H
