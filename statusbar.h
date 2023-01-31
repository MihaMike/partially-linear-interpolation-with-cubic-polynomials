#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>

class Status : public QStatusBar
{
    Q_OBJECT

public:

    Status (QWidget * parent = nullptr);

};

#endif // STATUSBAR_H
