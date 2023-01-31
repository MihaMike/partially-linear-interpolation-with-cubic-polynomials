#ifndef INPUTDOCK_H
#define INPUTDOCK_H

#include <QGroupBox>

#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QKeyEvent>

#include "storage.h"

//#define USE_NUM_PAD

class Input : public QGroupBox  {
  Q_OBJECT

public:

    Input (Storage & storage, QWidget * parent = nullptr);

signals:

    void changedMethod ();
    void changedFunc ();
    void changedContent ();
    void changedZoom ();
    void changedDisturbance ();
    void changedBorder ();
    void changedN ();
    void changedK ();

public slots:

    void update ();

#if 0
    void setDisabled ();
    void setEnabled ();
#endif

private:

    Storage & m_storage;

    QComboBox      * m_method;
    QComboBox      * m_func;
    QCheckBox      * m_need_draw_func;
    QCheckBox      * m_need_draw_approx;
    QCheckBox      * m_need_draw_residual;
    QPushButton    * m_zoom_minus;
    QPushButton    * m_zoom_plus;
    QDoubleSpinBox * m_disturbance;
    QDoubleSpinBox * m_a;
    QDoubleSpinBox * m_b;
    QSpinBox       * m_n;

#ifdef USE_NUM_PAD
    QPushButton * m_num_0;
    QPushButton * m_num_1;
    QPushButton * m_num_2;
    QPushButton * m_num_3;
    QPushButton * m_num_4;
    QPushButton * m_num_5;
    QPushButton * m_num_6;
    QPushButton * m_num_7;
    QPushButton * m_num_8;
    QPushButton * m_num_9;
#endif

    bool m_quiet;

private slots:

    void slot_method (int index);
    void slot_func (int index);
    void slot_need_draw_func (int state);
    void slot_need_draw_approx (int state);
    void slot_need_draw_residual (int state);
    void slot_zoom_minus ();
    void slot_zoom_plus ();
    void slot_disturbance (double value);
    void slot_a (double value);
    void slot_b (double value);
    void slot_n (int value);

#ifdef USE_NUM_PAD
    void slot_num_0 ();
    void slot_num_1 ();
    void slot_num_2 ();
    void slot_num_3 ();
    void slot_num_4 ();
    void slot_num_5 ();
    void slot_num_6 ();
    void slot_num_7 ();
    void slot_num_8 ();
    void slot_num_9 ();
#endif

#if 0
public:

    void keyPressEvent (QKeyEvent * event);
#endif

};

#endif // INPUTDOCK_H
