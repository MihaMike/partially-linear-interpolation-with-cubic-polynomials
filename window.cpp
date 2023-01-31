#include "window.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <stdlib.h>

#include "info.h"
#include "input.h"
#include "kernel.h"
#include "plotter.h"
#include "statusbar.h"
#include "storage.h"


static void set_font_size (QWidget * w, int size) {
    QFont font = w -> font ();
    font.setFamily ("Monospace");
    font.setPointSize (size);
    w -> setFont (font);
}


Window::Window (int argc, char * argv [], QWidget * parent)
  : QMainWindow (parent) {

//  setWindowFlags (Qt::Window
//                  | Qt::WindowMinMaxButtonsHint
//                  | Qt::WindowFullscreenButtonHint
//                  | Qt::WindowCloseButtonHint);

    parse_command_line (argc, argv);

    m_info = new Info (m_storage, this);
    m_input = new Input (m_storage, this);
    m_kernel = new Kernel (m_storage, this);
    m_plotter = new Plotter (m_storage, this);
    m_statusbar = new Status (this);

    /* Central windget */
    QHBoxLayout * space = new QHBoxLayout (this);
    QWidget * bar = new QWidget (this);
    QVBoxLayout * layout = new QVBoxLayout (bar);
    
    layout -> addWidget (m_input);
    layout -> addWidget (m_info);

    bar -> setLayout (layout);
    space -> addWidget (bar);

    /* Set left bar policy. */
    QSizePolicy policy;
    policy.setHorizontalStretch (QSizePolicy::Minimum);
    policy.setVerticalStretch (QSizePolicy::Maximum);
    bar -> setSizePolicy (policy);

    QFrame * line = new QFrame (this);
    line -> setFrameShape (QFrame::VLine);
    space -> addWidget (line);

    space -> addWidget (m_plotter);

    setCentralWidget (new QWidget (this));
    centralWidget () -> setLayout (space);

    /* Set status bar. */
    setStatusBar (m_statusbar);

    /* Set font sizes. */
    set_font_size (m_info, 10);
    set_font_size (m_input, 10);
    set_font_size (m_plotter, 10);
    set_font_size (m_statusbar, 9);

    setMinimumSize (800, 600);
    resize (1000, 600);

    /* Connect. */
    connect (m_input, SIGNAL (changedMethod ()), m_kernel, SLOT (handleChangeMethod ()));
    connect (m_input, SIGNAL (changedFunc ()), m_kernel, SLOT (handleChangeFunc ()));
    connect (m_input, SIGNAL (changedContent ()), m_kernel, SLOT (handleChangeContent ()));
    connect (m_input, SIGNAL (changedZoom ()), m_kernel, SLOT (handleChangeZoom ()));
    connect (m_input, SIGNAL (changedDisturbance ()), m_kernel, SLOT (handleChangeDisturbance ()));
    connect (m_input, SIGNAL (changedBorder ()), m_kernel, SLOT (handleChangeBorder ()));
    connect (m_input, SIGNAL (changedN ()), m_kernel, SLOT (handleChangeN ()));
    connect (m_input, SIGNAL (changedK ()), m_kernel, SLOT (handleChangeK ()));

    connect (m_kernel, SIGNAL (updated ()), m_plotter, SLOT (handleUpdate ()));
    connect (m_kernel, SIGNAL (updated ()), m_info, SLOT (handleUpdate ()));

#if 0
    connect (m_kernel, SIGNAL (startCalc ()), m_input, SLOT (setDisabled ()));
    connect (m_kernel, SIGNAL (finishCalc ()), m_input, SLOT (setEnabled ()));
#endif

    m_input -> update ();
    m_kernel -> update ();
}

Window::~Window() {}

void Window::parse_command_line (int argc, char * argv []) {
    if (argc != 5) {
        return;
    }

    double a, b;
    int n, t;

    a = atof (argv[1]);
    b = atof (argv[2]);
    n = atoi (argv[3]);
    t = atoi (argv[3]);

    int min, max;
    int count;

    m_storage.getMethod () .border_values (min, max);
    count = m_storage.getFuncsCount ();

    if (a < b && min <= n && n <= max && 0 <= t && t < count) {
        m_storage.setA (a);
        m_storage.setB (b);
        m_storage.setN (n);
        m_storage.setFuncIndex (t);
    }
}
