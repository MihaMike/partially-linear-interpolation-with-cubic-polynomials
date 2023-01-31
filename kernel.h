#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>

#include "storage.h"

class Kernel : public QObject {
  Q_OBJECT

public:

    Kernel (Storage & storage, QObject * parent = nullptr);

signals:

    void updated ();

#if 0
    void startCalc ();
    void finishCalc ();
#endif

public slots:

    void update ();

    void handleChangeMethod ();
    void handleChangeFunc ();
    void handleChangeContent ();
    void handleChangeZoom ();
    void handleChangeDisturbance ();
    void handleChangeBorder ();
    void handleChangeN ();
    void handleChangeK ();

private:

    Storage & m_storage;

    void updateWorkspace ();
    void updateContentMinMax ();
    void updateOutInfo ();
    void updateAll ();
    void makeDisturbance ();

};

#endif // KERNEL_H
