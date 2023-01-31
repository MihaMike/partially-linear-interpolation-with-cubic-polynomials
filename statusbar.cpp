#include "statusbar.h"

Status::Status (QWidget * parent) : QStatusBar (parent)
{
  showMessage (QString ("Created by Ponomarenko Philipp"));
}
