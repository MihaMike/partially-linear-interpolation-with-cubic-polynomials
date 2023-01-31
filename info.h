#ifndef INFODOCK_H
#define INFODOCK_H

#include <QGroupBox>
#include <QLabel>

#include "storage.h"

class Info : public QGroupBox {
  Q_OBJECT

public:
    Info (const Storage & storage, QWidget * parent = nullptr);

public slots:

    void handleUpdate ();

private:

    const Storage & m_storage;

    QLabel * m_y_min;
    QLabel * m_y_max;
    QLabel * m_residual;
    QLabel * m_zoom;

};

#endif // INFODOCK_H
