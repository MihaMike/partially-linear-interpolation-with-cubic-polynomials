#include "input.h"

#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>

#include "algorithm.h"

constexpr double DIST_BORD = 10.0;
constexpr double SEGM_BORD = 1000.0;
constexpr int    SEGM_DEC     = 2;

Input::Input (Storage & storage, QWidget * parent)
  : QGroupBox (parent),
    m_storage (storage)
{
    QGridLayout * grid = new QGridLayout (this);

    setTitle ("Input");
    setLayout (grid);

    /* Allocate. */
    m_method = new QComboBox (this);
    m_func = new QComboBox (this);
    m_need_draw_func = new QCheckBox ("Function", this);
    m_need_draw_approx = new QCheckBox ("Approximation", this);
    m_need_draw_residual = new QCheckBox ("Residual", this);
    m_zoom_minus = new QPushButton ("-", this);
    m_zoom_plus = new QPushButton ("+", this);
    m_disturbance = new QDoubleSpinBox (this);
    m_a = new QDoubleSpinBox (this);
    m_b = new QDoubleSpinBox (this);
    m_n = new QSpinBox (this);

#ifdef USE_NUM_PAD
    m_num_1 = new QPushButton ("1", this);
    m_num_2 = new QPushButton ("2", this);
    m_num_3 = new QPushButton ("3", this);
    m_num_4 = new QPushButton ("4", this);
    m_num_5 = new QPushButton ("5", this);
    m_num_6 = new QPushButton ("6", this);
    m_num_7 = new QPushButton ("7", this);
    m_num_8 = new QPushButton ("8", this);
    m_num_9 = new QPushButton ("9", this);
    m_num_0 = new QPushButton ("0", this);
#endif

    /* Settings. */

    for (int i = 0; i < m_storage.getMethodsCount (); i++) {
        m_method -> addItem (m_storage.getMethodAt (i) .name ());
    }

    for (int i = 0; i < m_storage.getFuncsCount (); i++) {
        m_func -> addItem (m_storage.getFuncAt (i) .m_name);
    }

    m_disturbance -> setDecimals (1);
//  m_disturbance -> setStepType (QAbstractSpinBox::AdaptiveDecimalStepType);

    m_a -> setDecimals (SEGM_DEC);
    m_b -> setDecimals (SEGM_DEC);
//  m_a -> setStepType (QAbstractSpinBox::AdaptiveDecimalStepType);
//  m_b -> setStepType (QAbstractSpinBox::AdaptiveDecimalStepType);

#ifdef USE_NUM_PAD
    m_num_0 -> setToolTip ("Change function");
    m_num_1 -> setToolTip ("Change content");
    m_num_2 -> setToolTip ("Zoom out");
    m_num_3 -> setToolTip ("Zoom in");
    m_num_4 -> setToolTip ("Reduce n");
    m_num_5 -> setToolTip ("Increase n");
    m_num_6 -> setToolTip ("Reduce disturbance");
    m_num_7 -> setToolTip ("Increase disturbance");
    m_num_8 -> setEnabled (false);
    m_num_9 -> setToolTip ("Change method");
#endif

    /* Attach. */
    grid -> addWidget (new QLabel ("Method:", this), 0, 0);
    grid -> addWidget (m_method, 0, 1, 1, 2);

    grid -> addWidget (new QLabel ("Function:", this), 1, 0);
    grid -> addWidget (m_func, 1, 1, 1, 2);

    grid -> addWidget (new QLabel ("Draw:", this), 2, 0);
    grid -> addWidget (m_need_draw_func, 2, 1, 1, 2);
    grid -> addWidget (m_need_draw_approx, 3, 1, 1, 2);
    grid -> addWidget (m_need_draw_residual, 4, 1, 1, 2);

    grid -> addWidget (new QLabel ("Zoom:", this), 5, 0);
    grid -> addWidget (m_zoom_minus, 5, 1);
    grid -> addWidget (m_zoom_plus, 5, 2);

    grid -> addWidget (new QLabel ("Disturbance:", this), 6, 0);
    grid -> addWidget (m_disturbance, 6, 1, 1, 2);

    grid -> addWidget (new QLabel ("a and b:", this), 7, 0);
    grid -> addWidget (m_a, 7, 1);
    grid -> addWidget (m_b, 7, 2);

    grid -> addWidget (new QLabel ("n:", this), 8, 0);
    grid -> addWidget (m_n, 8, 1, 1, 2);

#ifdef USE_NUM_PAD
    QFrame * line = new QFrame (this);
    line -> setFrameShape (QFrame::HLine);
    grid -> addWidget (line, 10, 0, 1, 3);

//  grid -> addWidget (new QLabel ("Numeric keypad", this), 10, 0);

    grid -> addWidget (m_num_1, 10, 0);
    grid -> addWidget (m_num_2, 10, 1);
    grid -> addWidget (m_num_3, 10, 2);
    grid -> addWidget (m_num_4, 11, 0);
    grid -> addWidget (m_num_5, 11, 1);
    grid -> addWidget (m_num_6, 11, 2);
    grid -> addWidget (m_num_7, 12, 0);
    grid -> addWidget (m_num_8, 12, 1);
    grid -> addWidget (m_num_9, 12, 2);
    grid -> addWidget (m_num_0, 13, 1);
#endif

    /* Connect. */
    connect (m_method, SIGNAL (currentIndexChanged (int)), this, SLOT (slot_method (int)));
    connect (m_func, SIGNAL (currentIndexChanged (int)), this, SLOT (slot_func (int)));
    connect (m_need_draw_func, SIGNAL (stateChanged (int)), this, SLOT (slot_need_draw_func (int)));
    connect (m_need_draw_approx, SIGNAL (stateChanged (int)), this, SLOT (slot_need_draw_approx (int)));
    connect (m_need_draw_residual, SIGNAL (stateChanged (int)), this, SLOT (slot_need_draw_residual (int)));
    connect (m_zoom_minus, SIGNAL (released ()), this, SLOT (slot_zoom_minus ()));
    connect (m_zoom_plus, SIGNAL (released ()), this, SLOT (slot_zoom_plus ()));
    connect (m_disturbance, SIGNAL (valueChanged (double)), this, SLOT (slot_disturbance (double)));
    connect (m_a, SIGNAL (valueChanged (double)), this, SLOT (slot_a (double)));
    connect (m_b, SIGNAL (valueChanged (double)), this, SLOT (slot_b (double)));
    connect (m_n, SIGNAL (valueChanged (int)), this, SLOT (slot_n (int)));

#ifdef USE_NUM_PAD
    connect (m_num_0, SIGNAL (released ()), this, SLOT (slot_num_0 ()));
    connect (m_num_1, SIGNAL (released ()), this, SLOT (slot_num_1 ()));
    connect (m_num_2, SIGNAL (released ()), this, SLOT (slot_num_2 ()));
    connect (m_num_3, SIGNAL (released ()), this, SLOT (slot_num_3 ()));
    connect (m_num_4, SIGNAL (released ()), this, SLOT (slot_num_4 ()));
    connect (m_num_5, SIGNAL (released ()), this, SLOT (slot_num_5 ()));
    connect (m_num_6, SIGNAL (released ()), this, SLOT (slot_num_6 ()));
    connect (m_num_7, SIGNAL (released ()), this, SLOT (slot_num_7 ()));
    connect (m_num_8, SIGNAL (released ()), this, SLOT (slot_num_8 ()));
    connect (m_num_9, SIGNAL (released ()), this, SLOT (slot_num_9 ()));
#endif

    /* Connect keyboard buttons */

    m_quiet = false;

    /* Init. */
    update ();

}

void Input::update () {
    int min, max;
    int quiet = m_quiet;
    m_quiet = true;
    m_method -> setCurrentIndex (m_storage.getMethodIndex ());
    m_func -> setCurrentIndex (m_storage.getFuncIndex ());
    m_need_draw_func -> setCheckState (m_storage.getNeedDrawFunc () ? Qt::Checked : Qt::Unchecked);
    m_need_draw_approx -> setCheckState (m_storage.getNeedDrawApprox () ? Qt::Checked : Qt::Unchecked);
    m_need_draw_residual -> setCheckState (m_storage.getNeedDrawResidual () ? Qt::Checked : Qt::Unchecked);
    m_disturbance -> setRange (-DIST_BORD, DIST_BORD);
    m_disturbance -> setValue (m_storage.getDisturbance ());
    m_a -> setRange (-SEGM_BORD, SEGM_BORD);
    m_a -> setValue (m_storage.getA ());
    m_b -> setRange (-SEGM_BORD, SEGM_BORD);
    m_b -> setValue (m_storage.getB ());
    m_storage.getMethod () .border_values (min, max);
    m_n -> setValue (m_storage.getN ());
    m_n -> setRange (min, max);
    m_quiet = quiet;
}

#if 0
void Input::setDisabled () {

    m_method -> setEnabled (false);
    m_func -> setEnabled (false);
    m_need_draw_func -> setEnabled (false);
    m_need_draw_approx -> setEnabled (false);
    m_need_draw_residual -> setEnabled (false);
    m_zoom_minus -> setEnabled (false);
    m_zoom_plus -> setEnabled (false);
    m_disturbance -> setEnabled (false);
    m_a -> setEnabled (false);
    m_b -> setEnabled (false);
    m_n -> setEnabled (false);

#ifdef USE_NUM_PAD
    m_num_0 -> setEnabled (false);
    m_num_1 -> setEnabled (false);
    m_num_2 -> setEnabled (false);
    m_num_3 -> setEnabled (false);
    m_num_4 -> setEnabled (false);
    m_num_5 -> setEnabled (false);
    m_num_6 -> setEnabled (false);
    m_num_7 -> setEnabled (false);
    m_num_8 -> setEnabled (false);
    m_num_9 -> setEnabled (false);
#endif

}

void Input::setEnabled () {

    m_method -> setEnabled (true);
    m_func -> setEnabled (true);
    m_need_draw_func -> setEnabled (true);
    m_need_draw_approx -> setEnabled (true);
    m_need_draw_residual -> setEnabled (true);
    m_zoom_minus -> setEnabled (true);
    m_zoom_plus -> setEnabled (true);
    m_disturbance -> setEnabled (true);
    m_a -> setEnabled (true);
    m_b -> setEnabled (true);
    m_n -> setEnabled (true);

#ifdef USE_NUM_PAD
    m_num_0 -> setEnabled (true);
    m_num_1 -> setEnabled (true);
    m_num_2 -> setEnabled (true);
    m_num_3 -> setEnabled (true);
    m_num_4 -> setEnabled (true);
    m_num_5 -> setEnabled (true);
    m_num_6 -> setEnabled (true);
    m_num_7 -> setEnabled (true);
    m_num_8 -> setEnabled (false);
    m_num_9 -> setEnabled (true);
#endif

}
#endif

void Input::slot_method (int index) {
    int min, max;
    bool quiet = m_quiet;
    m_quiet = true;
    m_storage.setMethodIndex (index);
    m_storage.getMethod () .border_values (min, max);
    m_n -> setRange (min, max);
    m_quiet = quiet;
    if (!m_quiet) {
        emit changedMethod ();
    }
}

void Input::slot_func (int index) {
    bool quiet = m_quiet;
    m_quiet = true;
    m_storage.setFuncIndex (index);
    m_quiet = quiet;
    if (!m_quiet) {
        emit changedFunc ();
    }
}

void Input::slot_need_draw_func (int state) {
    bool quiet = m_quiet;
    m_quiet = true;
    m_storage.setNeedDrawFunc (state == Qt::Checked);
    m_quiet = quiet;
    if (!m_quiet) {
        emit changedContent ();
    }
}

void Input::slot_need_draw_approx (int state) {
    bool quiet = m_quiet;
    m_quiet = true;
    m_storage.setNeedDrawApprox (state == Qt::Checked);
    m_quiet = quiet;
    if (!m_quiet) {
        emit changedContent ();
    }
}

void Input::slot_need_draw_residual (int state) {
    bool quiet = m_quiet;
    m_quiet = true;
    m_storage.setNeedDrawResidual (state == Qt::Checked);
    m_quiet = quiet;
    if (!m_quiet) {
        emit changedContent ();
    }
}

void Input::slot_zoom_minus () {
    bool quiet = m_quiet;
    m_quiet = true;
    m_storage.setZoom (m_storage.getZoom () - 1);
    m_quiet = quiet;
    if (!m_quiet) {
        emit changedZoom ();
    }
}

void Input::slot_zoom_plus () {
    bool quiet = m_quiet;
    m_quiet = true;
    m_storage.setZoom (m_storage.getZoom () + 1);
    m_quiet = quiet;
    if (!m_quiet) {
        emit changedZoom ();
    }
}

void Input::slot_disturbance (double value) {
    bool quiet = m_quiet;
    m_quiet = true;
    m_storage.setDisturbance (value);
    m_quiet = quiet;
    if (!m_quiet) {
        emit changedDisturbance ();
    }
}

void Input::slot_a (double value) {
    bool quiet = m_quiet;
    m_quiet = true;
    m_storage.setA (value);
    if (m_storage.getB () < value + algorithm::bin_pow (1e-1, SEGM_DEC)) {
        m_b -> setValue (value + algorithm::bin_pow (1e-1, SEGM_DEC));
    }
    m_quiet = quiet;
    if (!m_quiet) {
        emit changedBorder ();
    }
}

void Input::slot_b (double value) {
    bool quiet = m_quiet;
    m_quiet = true;
    m_storage.setB (value);
    if (m_storage.getA () > value - algorithm::bin_pow (1e-1, SEGM_DEC)) {
        m_a -> setValue (value - algorithm::bin_pow (1e-1, SEGM_DEC));
    }
    m_quiet = quiet;
    if (!m_quiet) {
        emit changedBorder ();
    }
}

void Input::slot_n (int value)
{
    bool quiet = m_quiet;
    m_quiet = true;
    m_storage.setN (value);
    m_quiet = quiet;
    if (!m_quiet) {
        emit changedN ();
    }
}


#if 0
void Input::keyPressEvent (QKeyEvent * event) {
    int count = m_storage.getFuncsCount ();
    int mask;

    /*
    * 0: change func
    * 1: change content
    * 2: zoom --
    * 3: zoom ++
    * 4: n /= 2
    * 5: n *= 2
    * 6: d --
    * 7: d ++
    */

    switch (event -> key ()) {

    case Qt::Key_0:
    // case Qt::Key_F10:
            m_func -> setCurrentIndex ((m_storage.getFuncIndex () + 1) % count);
            break;

    case Qt::Key_1:
    // case Qt::Key_F1:
          mask =   (m_storage.getNeedDrawFunc () << 0)
                 | (m_storage.getNeedDrawApprox () << 1)
                 | (m_storage.getNeedDrawResidual () << 2);
          mask++;
          m_quiet = true;
          m_need_draw_func -> setCheckState ((mask & (1 << 0)) ? Qt::Checked : Qt::Unchecked);
          m_need_draw_approx -> setCheckState ((mask & (1 << 1)) ? Qt::Checked : Qt::Unchecked);
          m_need_draw_residual -> setCheckState ((mask & (1 << 2)) ? Qt::Checked : Qt::Unchecked);
          m_quiet = false;
          emit changedContent ();
          break;

    case Qt::Key_2:
    // case Qt::Key_F2:
          m_storage.setZoom (m_storage.getZoom () - 1);
          emit changedZoom ();
          break;

    case Qt::Key_3:
    // case Qt::Key_F3:
          m_storage.setZoom (m_storage.getZoom () + 1);
          emit changedZoom ();
          break;

    case Qt::Key_4:
    // case Qt::Key_F4:
          m_n -> setValue (m_storage.getN () / 2);
          break;

    case Qt::Key_5:
    // case Qt::Key_F5:
          m_n -> setValue (m_storage.getN () * 2);
          break;

    case Qt::Key_6:
    // case Qt::Key_F6:
          m_disturbance -> setValue (m_storage.getDisturbance () - 1);
          break;

    case Qt::Key_7:
    // case Qt::Key_F7:
          m_disturbance -> setValue (m_storage.getDisturbance () + 1);
          break;

    default:
        break;

    }

}
#endif


#ifdef USE_NUM_PAD

void Input::slot_num_0 () {
    /* change func */
    int count = m_storage.getFuncsCount ();
    m_func -> setCurrentIndex ((m_storage.getFuncIndex () + 1) % count);
}

void Input::slot_num_1 () {
    /* change content */
    int mask =   (m_storage.getNeedDrawFunc () << 0)
                 | (m_storage.getNeedDrawApprox () << 1)
                 | (m_storage.getNeedDrawResidual () << 2);
    mask++;
    m_quiet = true;
    m_need_draw_func -> setCheckState ((mask & (1 << 0)) ? Qt::Checked : Qt::Unchecked);
    m_need_draw_approx -> setCheckState ((mask & (1 << 1)) ? Qt::Checked : Qt::Unchecked);
    m_need_draw_residual -> setCheckState ((mask & (1 << 2)) ? Qt::Checked : Qt::Unchecked);
    m_quiet = false;
    emit changedContent ();
}

void Input::slot_num_2 () {
    /* zoom -- */
    m_storage.setZoom (m_storage.getZoom () - 1);
    emit changedZoom ();
}

void Input::slot_num_3 () {
    /* zoom ++ */
    m_storage.setZoom (m_storage.getZoom () + 1);
    emit changedZoom ();
}

void Input::slot_num_4 () {
    /* n /= 2 */
    m_n -> setValue (m_storage.getN () / 2);
}

void Input::slot_num_5 () {
    /* n *= 2 */
    m_n -> setValue (m_storage.getN () * 2);
}

void Input::slot_num_6 () {
    /* d -- */
    m_disturbance -> setValue (m_storage.getDisturbance () - 1);
}

void Input::slot_num_7 () {
    /* d ++ */
    m_disturbance -> setValue (m_storage.getDisturbance () + 1);
}

void Input::slot_num_8 () {
}

void Input::slot_num_9 () {
    /* change method */
    int count = m_storage.getMethodsCount ();
    m_method -> setCurrentIndex ((m_storage.getMethodIndex () + 1) % count);
}

#endif
